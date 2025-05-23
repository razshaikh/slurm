/*****************************************************************************\
 *  pam_slurm_adopt/helper.c
 *****************************************************************************
 *  Useful portions extracted from pam_slurm.c by Ryan Cox <ryan_cox@byu.edu>
 *
 *  Copyright (C) 2002-2007 The Regents of the University of California.
 *  Copyright (C) 2008-2009 Lawrence Livermore National Security.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  UCRL-CODE-2002-040.
 *
 *  Written by Chris Dunlap <cdunlap@llnl.gov>
 *         and Jim Garlick  <garlick@llnl.gov>
 *         modified for Slurm by Moe Jette <jette@llnl.gov>.
 *
 *  This file is part of pam_slurm, a PAM module for restricting access to
 *  the compute nodes within a cluster based on information obtained from
 *  Simple Linux Utility for Resource Management (Slurm).  For details, see
 *  <http://www.llnl.gov/linux/slurm/>.
 *
 *  pam_slurm is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  pam_slurm is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with pam_slurm; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
\*****************************************************************************/

#ifndef PAM_MODULE_NAME
#  define PAM_MODULE_NAME "pam_slurm_adopt"
#endif

#if HAVE_CONFIG_H
#  include "config.h"
#endif

#include <ctype.h>
#include <dlfcn.h>
#include <errno.h>
#include <pwd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

#include "slurm/slurm.h"
#include "src/common/slurm_xlator.h"

#include "src/common/log.h"

/*  Define the externally visible functions in this file.
 */
#define PAM_SM_ACCOUNT
#include <security/pam_modules.h>
#include <security/_pam_macros.h>


/* Define the functions to be called before and after load since _init
 * and _fini are obsolete, and their use can lead to unpredictable
 * results.
 */
void __attribute__ ((constructor)) libpam_slurm_init(void);
void __attribute__ ((destructor)) libpam_slurm_fini(void);

/*
 *  Handle for libslurm.so
 *
 *  We open libslurm.so via dlopen () in order to pass the
 *   flag RTDL_GLOBAL so that subsequently loaded modules have
 *   access to libslurm symbols. This is pretty much only needed
 *   for dynamically loaded modules that would otherwise be
 *   linked against libslurm.
 *
 */
static void * slurm_h = NULL;

/* This function is necessary because libpam_slurm_init is called without access
 * to the pam handle.
 */
static void
_log_msg(int level, const char *format, ...)
{
	va_list args;

	openlog(PAM_MODULE_NAME, LOG_CONS | LOG_PID, LOG_AUTHPRIV);
	va_start(args, format);
	vsyslog(level, format, args);
	va_end(args);
	closelog();
	return;
}

/*
 * pam 1.5.3 stopped providing _pam_drop_reply().  Our use does not currently
 * fetch sensitive data so simply free this structure.
 */
static void _pam_slurm_drop_response(struct pam_response *reply, int replies)
{
	for (int i = 0; i < replies; i++) {
		if (reply[i].resp)
			free(reply[i].resp);
	}
	free(reply);
}

/*
 *  Sends a message to the application informing the user
 *  that access was denied due to Slurm.
 */
extern void
send_user_msg(pam_handle_t *pamh, const char *mesg)
{
	int retval;
	struct pam_conv *conv;
	void *dummy;    /* needed to eliminate warning:
			 * dereferencing type-punned pointer will
			 * break strict-aliasing rules */
	struct pam_message msg[1];
	const struct pam_message *pmsg[1];
	struct pam_response *prsp;

	info("send_user_msg: %s", mesg);
	/*  Get conversation function to talk with app.
	 */
	retval = pam_get_item(pamh, PAM_CONV, (const void **) &dummy);
	conv = (struct pam_conv *) dummy;
	if (retval != PAM_SUCCESS) {
		_log_msg(LOG_ERR, "unable to get pam_conv: %s",
			 pam_strerror(pamh, retval));
		return;
	}

	/*  Construct msg to send to app.
	 */
	msg[0].msg_style = PAM_ERROR_MSG;
	msg[0].msg = mesg;
	pmsg[0] = &msg[0];
	prsp = NULL;

	/*  Send msg to app and free the (meaningless) rsp.
	 */
	retval = conv->conv(1, pmsg, &prsp, conv->appdata_ptr);
	if (retval != PAM_SUCCESS)
		_log_msg(LOG_ERR, "unable to converse with app: %s",
			 pam_strerror(pamh, retval));
	if (prsp != NULL)
		_pam_slurm_drop_response(prsp, 1);

	return;
}

/*
 * Dynamically open system's libslurm.so with RTLD_GLOBAL flag.
 * This allows subsequently loaded modules access to libslurm symbols.
 */
extern void libpam_slurm_init (void)
{
	char libslurmname[64];

	if (slurm_h)
		return;

	/* First try to use the same libslurm version ("libslurm.so.24.0.0"),
	 * Second try to match the major version number ("libslurm.so.24"),
	 * Otherwise use "libslurm.so" */
	if (snprintf(libslurmname, sizeof(libslurmname),
			"libslurm.so.%d.%d.%d", SLURM_API_CURRENT,
			SLURM_API_REVISION, SLURM_API_AGE) >=
			(signed) sizeof(libslurmname) ) {
		_log_msg (LOG_ERR, "Unable to write libslurmname\n");
	} else if ((slurm_h = dlopen(libslurmname, RTLD_NOW|RTLD_GLOBAL))) {
		return;
	} else {
		_log_msg (LOG_INFO, "Unable to dlopen %s: %s\n",
			libslurmname, dlerror ());
	}

	if (snprintf(libslurmname, sizeof(libslurmname), "libslurm.so.%d",
			SLURM_API_CURRENT) >= (signed) sizeof(libslurmname) ) {
		_log_msg (LOG_ERR, "Unable to write libslurmname\n");
	} else if ((slurm_h = dlopen(libslurmname, RTLD_NOW|RTLD_GLOBAL))) {
		return;
	} else {
		_log_msg (LOG_INFO, "Unable to dlopen %s: %s\n",
			libslurmname, dlerror ());
	}

	if (!(slurm_h = dlopen("libslurm.so", RTLD_NOW|RTLD_GLOBAL))) {
		_log_msg (LOG_ERR, "Unable to dlopen libslurm.so: %s\n",
			  dlerror ());
	}

	return;
}

extern void libpam_slurm_fini (void)
{
	if (slurm_h)
		dlclose (slurm_h);
	return;
}

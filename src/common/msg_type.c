/*****************************************************************************\
 *  msg_type.c
 *****************************************************************************
 *  Copyright (C) SchedMD LLC.
 *
 *  This file is part of Slurm, a resource management program.
 *  For details, see <https://slurm.schedmd.com/>.
 *  Please also read the included file: DISCLAIMER.
 *
 *  Slurm is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  In addition, as a special exception, the copyright holders give permission
 *  to link the code of portions of this program with the OpenSSL library under
 *  certain conditions as described in each individual source file, and
 *  distribute linked combinations including the two. You must obey the GNU
 *  General Public License in all respects for all of the code used other than
 *  OpenSSL. If you modify file(s) with this exception, you may extend this
 *  exception to your version of the file(s), but you are not obligated to do
 *  so. If you do not wish to do so, delete this exception statement from your
 *  version.  If you delete this exception statement from all source files in
 *  the program, then also delete it here.
 *
 *  Slurm is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Slurm; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
\*****************************************************************************/

#include <stdint.h>

#include "src/common/msg_type.h"
#include "src/common/xassert.h"
#include "src/common/xstring.h"

typedef struct {
	uint16_t msg_type;
	const char *str;
} entry_t;

/*
 * Avoid repeating the string representation alongside the enum.
 * This should prevent them from ever getting out-of-sync.
 */
#define ENTRY(_e) { _e, #_e }

const static entry_t msg_types[] = {
	ENTRY(REQUEST_NODE_REGISTRATION_STATUS),
	ENTRY(MESSAGE_NODE_REGISTRATION_STATUS),
	ENTRY(REQUEST_RECONFIGURE),
	ENTRY(REQUEST_RECONFIGURE_WITH_CONFIG),
	ENTRY(REQUEST_SHUTDOWN),
	ENTRY(REQUEST_RECONFIGURE_SACKD),
	ENTRY(REQUEST_PING),
	ENTRY(REQUEST_CONTROL),
	ENTRY(REQUEST_SET_DEBUG_LEVEL),
	ENTRY(REQUEST_HEALTH_CHECK),
	ENTRY(REQUEST_TAKEOVER),
	ENTRY(REQUEST_SET_SCHEDLOG_LEVEL),
	ENTRY(REQUEST_SET_DEBUG_FLAGS),
	ENTRY(REQUEST_REBOOT_NODES),
	ENTRY(RESPONSE_PING_SLURMD),
	ENTRY(REQUEST_ACCT_GATHER_UPDATE),
	ENTRY(RESPONSE_ACCT_GATHER_UPDATE),
	ENTRY(REQUEST_ACCT_GATHER_ENERGY),
	ENTRY(RESPONSE_ACCT_GATHER_ENERGY),
	ENTRY(REQUEST_LICENSE_INFO),
	ENTRY(RESPONSE_LICENSE_INFO),
	ENTRY(REQUEST_SET_FS_DAMPENING_FACTOR),
	ENTRY(RESPONSE_NODE_REGISTRATION),
	ENTRY(REQUEST_SET_SUSPEND_EXC_NODES),
	ENTRY(REQUEST_SET_SUSPEND_EXC_PARTS),
	ENTRY(REQUEST_SET_SUSPEND_EXC_STATES),
	ENTRY(REQUEST_DBD_RELAY),
	ENTRY(PERSIST_RC),
	ENTRY(REQUEST_BUILD_INFO),
	ENTRY(RESPONSE_BUILD_INFO),
	ENTRY(REQUEST_JOB_INFO),
	ENTRY(RESPONSE_JOB_INFO),
	ENTRY(REQUEST_JOB_STEP_INFO),
	ENTRY(RESPONSE_JOB_STEP_INFO),
	ENTRY(REQUEST_NODE_INFO),
	ENTRY(RESPONSE_NODE_INFO),
	ENTRY(REQUEST_PARTITION_INFO),
	ENTRY(RESPONSE_PARTITION_INFO),
	ENTRY(REQUEST_JOB_ID),
	ENTRY(RESPONSE_JOB_ID),
	ENTRY(REQUEST_CONFIG),
	ENTRY(RESPONSE_CONFIG),
	ENTRY(REQUEST_TRIGGER_SET),
	ENTRY(REQUEST_TRIGGER_GET),
	ENTRY(REQUEST_TRIGGER_CLEAR),
	ENTRY(RESPONSE_TRIGGER_GET),
	ENTRY(REQUEST_JOB_INFO_SINGLE),
	ENTRY(REQUEST_SHARE_INFO),
	ENTRY(RESPONSE_SHARE_INFO),
	ENTRY(REQUEST_RESERVATION_INFO),
	ENTRY(RESPONSE_RESERVATION_INFO),
	ENTRY(REQUEST_PRIORITY_FACTORS),
	ENTRY(RESPONSE_PRIORITY_FACTORS),
	ENTRY(REQUEST_TOPO_INFO),
	ENTRY(RESPONSE_TOPO_INFO),
	ENTRY(REQUEST_TRIGGER_PULL),
	ENTRY(REQUEST_STATS_INFO),
	ENTRY(RESPONSE_STATS_INFO),
	ENTRY(REQUEST_BURST_BUFFER_INFO),
	ENTRY(RESPONSE_BURST_BUFFER_INFO),
	ENTRY(REQUEST_JOB_USER_INFO),
	ENTRY(REQUEST_NODE_INFO_SINGLE),
	ENTRY(REQUEST_ASSOC_MGR_INFO),
	ENTRY(RESPONSE_ASSOC_MGR_INFO),
	ENTRY(REQUEST_FED_INFO),
	ENTRY(RESPONSE_FED_INFO),
	ENTRY(REQUEST_BATCH_SCRIPT),
	ENTRY(RESPONSE_BATCH_SCRIPT),
	ENTRY(REQUEST_CONTROL_STATUS),
	ENTRY(RESPONSE_CONTROL_STATUS),
	ENTRY(REQUEST_BURST_BUFFER_STATUS),
	ENTRY(RESPONSE_BURST_BUFFER_STATUS),
	ENTRY(REQUEST_JOB_STATE),
	ENTRY(RESPONSE_JOB_STATE),
	ENTRY(REQUEST_CRONTAB),
	ENTRY(RESPONSE_CRONTAB),
	ENTRY(REQUEST_UPDATE_CRONTAB),
	ENTRY(RESPONSE_UPDATE_CRONTAB),
	ENTRY(REQUEST_TLS_CERT),
	ENTRY(RESPONSE_TLS_CERT),
	ENTRY(REQUEST_UPDATE_JOB),
	ENTRY(REQUEST_UPDATE_NODE),
	ENTRY(REQUEST_CREATE_PARTITION),
	ENTRY(REQUEST_DELETE_PARTITION),
	ENTRY(REQUEST_UPDATE_PARTITION),
	ENTRY(REQUEST_CREATE_RESERVATION),
	ENTRY(RESPONSE_CREATE_RESERVATION),
	ENTRY(REQUEST_DELETE_RESERVATION),
	ENTRY(REQUEST_UPDATE_RESERVATION),
	ENTRY(REQUEST_DELETE_NODE),
	ENTRY(REQUEST_CREATE_NODE),
	ENTRY(REQUEST_NODE_ALIAS_ADDRS),
	ENTRY(RESPONSE_NODE_ALIAS_ADDRS),
	ENTRY(REQUEST_RESOURCE_ALLOCATION),
	ENTRY(RESPONSE_RESOURCE_ALLOCATION),
	ENTRY(REQUEST_SUBMIT_BATCH_JOB),
	ENTRY(RESPONSE_SUBMIT_BATCH_JOB),
	ENTRY(REQUEST_BATCH_JOB_LAUNCH),
	ENTRY(REQUEST_CANCEL_JOB),
	ENTRY(REQUEST_JOB_WILL_RUN),
	ENTRY(RESPONSE_JOB_WILL_RUN),
	ENTRY(REQUEST_JOB_ALLOCATION_INFO),
	ENTRY(RESPONSE_JOB_ALLOCATION_INFO),
	ENTRY(REQUEST_JOB_READY),
	ENTRY(RESPONSE_JOB_READY),
	ENTRY(REQUEST_JOB_END_TIME),
	ENTRY(REQUEST_JOB_NOTIFY),
	ENTRY(REQUEST_JOB_SBCAST_CRED),
	ENTRY(REQUEST_SBCAST_CRED_NO_JOB),
	ENTRY(RESPONSE_JOB_SBCAST_CRED),
	ENTRY(REQUEST_HET_JOB_ALLOCATION),
	ENTRY(RESPONSE_HET_JOB_ALLOCATION),
	ENTRY(REQUEST_HET_JOB_ALLOC_INFO),
	ENTRY(REQUEST_SUBMIT_BATCH_HET_JOB),
	ENTRY(REQUEST_CTLD_MULT_MSG),
	ENTRY(RESPONSE_CTLD_MULT_MSG),
	ENTRY(REQUEST_SIB_MSG),
	ENTRY(REQUEST_SIB_JOB_LOCK),
	ENTRY(REQUEST_SIB_JOB_UNLOCK),
	ENTRY(REQUEST_SEND_DEP),
	ENTRY(REQUEST_UPDATE_ORIGIN_DEP),
	ENTRY(REQUEST_JOB_STEP_CREATE),
	ENTRY(RESPONSE_JOB_STEP_CREATE),
	ENTRY(REQUEST_CANCEL_JOB_STEP),
	ENTRY(REQUEST_UPDATE_JOB_STEP),
	ENTRY(REQUEST_STEP_BY_CONTAINER_ID),
	ENTRY(RESPONSE_STEP_BY_CONTAINER_ID),
	ENTRY(REQUEST_SUSPEND),
	ENTRY(REQUEST_STEP_COMPLETE),
	ENTRY(REQUEST_COMPLETE_JOB_ALLOCATION),
	ENTRY(REQUEST_COMPLETE_BATCH_SCRIPT),
	ENTRY(REQUEST_JOB_STEP_STAT),
	ENTRY(RESPONSE_JOB_STEP_STAT),
	ENTRY(REQUEST_STEP_LAYOUT),
	ENTRY(RESPONSE_STEP_LAYOUT),
	ENTRY(REQUEST_JOB_REQUEUE),
	ENTRY(REQUEST_DAEMON_STATUS),
	ENTRY(RESPONSE_SLURMD_STATUS),
	ENTRY(REQUEST_JOB_STEP_PIDS),
	ENTRY(RESPONSE_JOB_STEP_PIDS),
	ENTRY(REQUEST_FORWARD_DATA),
	ENTRY(REQUEST_SUSPEND_INT),
	ENTRY(REQUEST_KILL_JOB),
	ENTRY(RESPONSE_JOB_ARRAY_ERRORS),
	ENTRY(REQUEST_NETWORK_CALLERID),
	ENTRY(RESPONSE_NETWORK_CALLERID),
	ENTRY(REQUEST_TOP_JOB),
	ENTRY(REQUEST_AUTH_TOKEN),
	ENTRY(RESPONSE_AUTH_TOKEN),
	ENTRY(REQUEST_KILL_JOBS),
	ENTRY(RESPONSE_KILL_JOBS),
	ENTRY(REQUEST_LAUNCH_TASKS),
	ENTRY(RESPONSE_LAUNCH_TASKS),
	ENTRY(MESSAGE_TASK_EXIT),
	ENTRY(REQUEST_SIGNAL_TASKS),
	ENTRY(REQUEST_TERMINATE_TASKS),
	ENTRY(REQUEST_REATTACH_TASKS),
	ENTRY(RESPONSE_REATTACH_TASKS),
	ENTRY(REQUEST_KILL_TIMELIMIT),
	ENTRY(REQUEST_TERMINATE_JOB),
	ENTRY(MESSAGE_EPILOG_COMPLETE),
	ENTRY(REQUEST_ABORT_JOB),
	ENTRY(REQUEST_FILE_BCAST),
	ENTRY(REQUEST_KILL_PREEMPTED),
	ENTRY(REQUEST_LAUNCH_PROLOG),
	ENTRY(REQUEST_COMPLETE_PROLOG),
	ENTRY(RESPONSE_PROLOG_EXECUTING),
	ENTRY(REQUEST_PERSIST_INIT),
	ENTRY(REQUEST_PERSIST_INIT_TLS),
	ENTRY(SRUN_PING),
	ENTRY(SRUN_TIMEOUT),
	ENTRY(SRUN_NODE_FAIL),
	ENTRY(SRUN_JOB_COMPLETE),
	ENTRY(SRUN_USER_MSG),
	ENTRY(SRUN_STEP_MISSING),
	ENTRY(SRUN_REQUEST_SUSPEND),
	ENTRY(SRUN_STEP_SIGNAL),
	ENTRY(SRUN_NET_FORWARD),
	ENTRY(PMI_KVS_PUT_REQ),
	ENTRY(PMI_KVS_GET_REQ),
	ENTRY(PMI_KVS_GET_RESP),
	ENTRY(RESPONSE_SLURM_RC),
	ENTRY(RESPONSE_SLURM_RC_MSG),
	ENTRY(RESPONSE_SLURM_REROUTE_MSG),
	ENTRY(RESPONSE_FORWARD_FAILED),
	ENTRY(ACCOUNTING_UPDATE_MSG),
	ENTRY(ACCOUNTING_FIRST_REG),
	ENTRY(ACCOUNTING_REGISTER_CTLD),
	ENTRY(ACCOUNTING_TRES_CHANGE_DB),
	ENTRY(ACCOUNTING_NODES_CHANGE_DB),
	ENTRY(SLURMSCRIPTD_REQUEST_FLUSH),
	ENTRY(SLURMSCRIPTD_REQUEST_FLUSH_JOB),
	ENTRY(SLURMSCRIPTD_REQUEST_RUN_SCRIPT),
	ENTRY(SLURMSCRIPTD_REQUEST_SCRIPT_COMPLETE),
	ENTRY(SLURMSCRIPTD_REQUEST_UPDATE_DEBUG_FLAGS),
	ENTRY(SLURMSCRIPTD_REQUEST_UPDATE_LOG),
	ENTRY(SLURMSCRIPTD_SHUTDOWN),
	ENTRY(SLURMSCRIPTD_REQUEST_BB_SCRIPT_INFO),
	ENTRY(REQUEST_CONTAINER_START),
	ENTRY(RESPONSE_CONTAINER_START),
	ENTRY(REQUEST_CONTAINER_PTY),
	ENTRY(RESPONSE_CONTAINER_PTY),
	ENTRY(REQUEST_CONTAINER_EXEC),
	ENTRY(RESPONSE_CONTAINER_EXEC),
	ENTRY(REQUEST_CONTAINER_KILL),
	ENTRY(RESPONSE_CONTAINER_KILL),
	ENTRY(REQUEST_CONTAINER_DELETE),
	ENTRY(RESPONSE_CONTAINER_DELETE),
	ENTRY(REQUEST_CONTAINER_STATE),
	ENTRY(RESPONSE_CONTAINER_STATE),
	ENTRY(PROXY_TO_NODE_SEND_RECV),
	ENTRY(PROXY_TO_NODE_SEND_ONLY),
	ENTRY(PROXY_TO_CTLD_SEND_RECV),
	ENTRY(PROXY_TO_CTLD_SEND_ONLY),
};

extern const char *rpc_num2string(uint16_t msg_type)
{
	static char buf[16];

	for (int i = 0; i < ARRAY_SIZE(msg_types); i++) {
		if (msg_types[i].msg_type == msg_type)
			return msg_types[i].str;
	}

	/* lookup failed, print the number instead */
	(void) snprintf(buf, sizeof(buf), "%u", msg_type);
	return buf;
}

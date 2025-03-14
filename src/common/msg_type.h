/*****************************************************************************\
 *  msg_type.h
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

#ifndef _MSG_TYPE_H
#define _MSG_TYPE_H

#include <stdint.h>

/*
 * Slurm message types.
 *
 * NOTE: Never alter the enum value of an existing message.
 *       That would break backwards-compatibility.
 */
typedef enum {
	REQUEST_NODE_REGISTRATION_STATUS = 1001,
	MESSAGE_NODE_REGISTRATION_STATUS,
	REQUEST_RECONFIGURE,
	REQUEST_RECONFIGURE_WITH_CONFIG,
	REQUEST_SHUTDOWN,
	REQUEST_RECONFIGURE_SACKD,
	DEFUNCT_RPC_1007,
	REQUEST_PING,
	REQUEST_CONTROL,
	REQUEST_SET_DEBUG_LEVEL,	/* 1010 */
	REQUEST_HEALTH_CHECK,
	REQUEST_TAKEOVER,
	REQUEST_SET_SCHEDLOG_LEVEL,
	REQUEST_SET_DEBUG_FLAGS,
	REQUEST_REBOOT_NODES,
	RESPONSE_PING_SLURMD,
	REQUEST_ACCT_GATHER_UPDATE,
	RESPONSE_ACCT_GATHER_UPDATE,
	REQUEST_ACCT_GATHER_ENERGY,
	RESPONSE_ACCT_GATHER_ENERGY,	/* 1020 */
	REQUEST_LICENSE_INFO,
	RESPONSE_LICENSE_INFO,
	REQUEST_SET_FS_DAMPENING_FACTOR,
	RESPONSE_NODE_REGISTRATION,
	REQUEST_SET_SUSPEND_EXC_NODES,
	REQUEST_SET_SUSPEND_EXC_PARTS,
	REQUEST_SET_SUSPEND_EXC_STATES,
	REQUEST_DBD_RELAY,

	DBD_MESSAGES_START	= 1400,
	PERSIST_RC = 1433, /* To mirror the DBD_RC this is replacing */
	/* Don't make any messages in this range as this is what the DBD uses
	 * unless mirroring */
	DBD_MESSAGES_END	= 2000,

	REQUEST_BUILD_INFO	= 2001,
	RESPONSE_BUILD_INFO,
	REQUEST_JOB_INFO,
	RESPONSE_JOB_INFO,
	REQUEST_JOB_STEP_INFO,
	RESPONSE_JOB_STEP_INFO,
	REQUEST_NODE_INFO,
	RESPONSE_NODE_INFO,
	REQUEST_PARTITION_INFO,
	RESPONSE_PARTITION_INFO,	/* 2010 */
	DEFUNCT_RPC_2011,
	DEFUNCT_RPC_2012,
	REQUEST_JOB_ID,
	RESPONSE_JOB_ID,
	REQUEST_CONFIG,
	RESPONSE_CONFIG,
	REQUEST_TRIGGER_SET,
	REQUEST_TRIGGER_GET,
	REQUEST_TRIGGER_CLEAR,
	RESPONSE_TRIGGER_GET,		/* 2020 */
	REQUEST_JOB_INFO_SINGLE,
	REQUEST_SHARE_INFO,
	RESPONSE_SHARE_INFO,
	REQUEST_RESERVATION_INFO,
	RESPONSE_RESERVATION_INFO,
	REQUEST_PRIORITY_FACTORS,
	RESPONSE_PRIORITY_FACTORS,
	REQUEST_TOPO_INFO,
	RESPONSE_TOPO_INFO,
	REQUEST_TRIGGER_PULL,		/* 2030 */
	REQUEST_FRONT_END_INFO,
	RESPONSE_FRONT_END_INFO,
	DEFUNCT_RPC_2033,
	DEFUNCT_RPC_2034,
	REQUEST_STATS_INFO,
	RESPONSE_STATS_INFO,
	REQUEST_BURST_BUFFER_INFO,
	RESPONSE_BURST_BUFFER_INFO,
	REQUEST_JOB_USER_INFO,
	REQUEST_NODE_INFO_SINGLE,	/* 2040 */
	DEFUNCT_RPC_2041,
	DEFUNCT_RPC_2042,
	REQUEST_ASSOC_MGR_INFO,
	RESPONSE_ASSOC_MGR_INFO,
	DEFUNCT_RPC_2045,
	DEFUNCT_RPC_2046, /* free for reuse */
	DEFUNCT_RPC_2047,
	DEFUNCT_RPC_2048,
	REQUEST_FED_INFO,
	RESPONSE_FED_INFO,		/* 2050 */
	REQUEST_BATCH_SCRIPT,
	RESPONSE_BATCH_SCRIPT,
	REQUEST_CONTROL_STATUS,
	RESPONSE_CONTROL_STATUS,
	REQUEST_BURST_BUFFER_STATUS,
	RESPONSE_BURST_BUFFER_STATUS,
	REQUEST_JOB_STATE,
	RESPONSE_JOB_STATE,

	REQUEST_CRONTAB = 2200,
	RESPONSE_CRONTAB,
	REQUEST_UPDATE_CRONTAB,
	RESPONSE_UPDATE_CRONTAB,

	REQUEST_TLS_CERT = 2300,
	RESPONSE_TLS_CERT,

	REQUEST_UPDATE_JOB = 3001,
	REQUEST_UPDATE_NODE,
	REQUEST_CREATE_PARTITION,
	REQUEST_DELETE_PARTITION,
	REQUEST_UPDATE_PARTITION,
	REQUEST_CREATE_RESERVATION,
	RESPONSE_CREATE_RESERVATION,
	REQUEST_DELETE_RESERVATION,
	REQUEST_UPDATE_RESERVATION,
	DEFUNCT_RPC_3010,  /* free for reuse */
	DEFUNCT_RPC_3011,
	DEFUNCT_RPC_3012,
	DEFUNCT_RPC_3013,
	REQUEST_DELETE_NODE,
	REQUEST_CREATE_NODE,
	REQUEST_NODE_ALIAS_ADDRS,
	RESPONSE_NODE_ALIAS_ADDRS,

	REQUEST_RESOURCE_ALLOCATION = 4001,
	RESPONSE_RESOURCE_ALLOCATION,
	REQUEST_SUBMIT_BATCH_JOB,
	RESPONSE_SUBMIT_BATCH_JOB,
	REQUEST_BATCH_JOB_LAUNCH,
	REQUEST_CANCEL_JOB,
	DEFUNCT_RPC_4007,
	DEFUNCT_RPC_4008,
	DEFUNCT_RPC_4009,
	DEFUNCT_RPC_4010,		/* 4010 */
	DEFUNCT_RPC_4011,
	REQUEST_JOB_WILL_RUN,
	RESPONSE_JOB_WILL_RUN,
	REQUEST_JOB_ALLOCATION_INFO,
	RESPONSE_JOB_ALLOCATION_INFO,
	DEFUNCT_RPC_4016, /* free for reuse */
	DEFUNCT_RPC_4017, /* free for reuse */
	DEFUNCT_RPC_4018,
	REQUEST_JOB_READY,
	RESPONSE_JOB_READY,		/* 4020 */
	REQUEST_JOB_END_TIME,
	REQUEST_JOB_NOTIFY,
	REQUEST_JOB_SBCAST_CRED,
	RESPONSE_JOB_SBCAST_CRED,
	REQUEST_HET_JOB_ALLOCATION,
	RESPONSE_HET_JOB_ALLOCATION,
	REQUEST_HET_JOB_ALLOC_INFO,
	REQUEST_SUBMIT_BATCH_HET_JOB,
	REQUEST_SBCAST_CRED_NO_JOB,

	REQUEST_CTLD_MULT_MSG = 4500,
	RESPONSE_CTLD_MULT_MSG,
	REQUEST_SIB_MSG,
	REQUEST_SIB_JOB_LOCK,
	REQUEST_SIB_JOB_UNLOCK,
	REQUEST_SEND_DEP,
	REQUEST_UPDATE_ORIGIN_DEP,

	REQUEST_JOB_STEP_CREATE = 5001,
	RESPONSE_JOB_STEP_CREATE,
	DEFUNCT_RPC_5003,
	DEFUNCT_RPC_5004,
	REQUEST_CANCEL_JOB_STEP,
	DEFUNCT_RPC_5006,
	REQUEST_UPDATE_JOB_STEP,
	REQUEST_STEP_BY_CONTAINER_ID,
	RESPONSE_STEP_BY_CONTAINER_ID,
	DEFUNCT_RPC_5010,		/* 5010 */
	DEFUNCT_RPC_5011,
	DEFUNCT_RPC_5012,
	DEFUNCT_RPC_5013,
	REQUEST_SUSPEND,
	DEFUNCT_RPC_5015,
	REQUEST_STEP_COMPLETE,
	REQUEST_COMPLETE_JOB_ALLOCATION,
	REQUEST_COMPLETE_BATCH_SCRIPT,
	REQUEST_JOB_STEP_STAT,
	RESPONSE_JOB_STEP_STAT,		/* 5020 */
	REQUEST_STEP_LAYOUT,
	RESPONSE_STEP_LAYOUT,
	REQUEST_JOB_REQUEUE,
	REQUEST_DAEMON_STATUS,
	RESPONSE_SLURMD_STATUS,
	DEFUNCT_RPC_5026,
	REQUEST_JOB_STEP_PIDS,
	RESPONSE_JOB_STEP_PIDS,
	REQUEST_FORWARD_DATA,
	DEFUNCT_RPC_5030,		/* 5030 */
	REQUEST_SUSPEND_INT,
	REQUEST_KILL_JOB,		/* 5032 */
	DEFUNCT_RPC_5033,
	RESPONSE_JOB_ARRAY_ERRORS,
	REQUEST_NETWORK_CALLERID,
	RESPONSE_NETWORK_CALLERID,
	DEFUNCT_RPC_5037,
	REQUEST_TOP_JOB,		/* 5038 */
	REQUEST_AUTH_TOKEN,
	RESPONSE_AUTH_TOKEN,
	REQUEST_KILL_JOBS,		/* 5040 */
	RESPONSE_KILL_JOBS,

	REQUEST_LAUNCH_TASKS = 6001,
	RESPONSE_LAUNCH_TASKS,
	MESSAGE_TASK_EXIT,
	REQUEST_SIGNAL_TASKS,
	DEFUNCT_RPC_6005,
	REQUEST_TERMINATE_TASKS,
	REQUEST_REATTACH_TASKS,
	RESPONSE_REATTACH_TASKS,
	REQUEST_KILL_TIMELIMIT,
	DEFUNCT_RPC_6010, /* free for reuse */
	REQUEST_TERMINATE_JOB,		/* 6011 */
	MESSAGE_EPILOG_COMPLETE,
	REQUEST_ABORT_JOB,	/* job shouldn't be running, kill it without
				 * job/step/task complete responses */
	REQUEST_FILE_BCAST,
	DEFUNCT_RPC_6015,
	REQUEST_KILL_PREEMPTED,

	REQUEST_LAUNCH_PROLOG,
	REQUEST_COMPLETE_PROLOG,
	RESPONSE_PROLOG_EXECUTING,	/* 6019 */

	REQUEST_PERSIST_INIT = 6500,
	REQUEST_PERSIST_INIT_TLS = 6501,

	SRUN_PING = 7001,
	SRUN_TIMEOUT,
	SRUN_NODE_FAIL,
	SRUN_JOB_COMPLETE,
	SRUN_USER_MSG,
	DEFUNCT_RPC_7006,
	SRUN_STEP_MISSING,
	SRUN_REQUEST_SUSPEND,
	SRUN_STEP_SIGNAL,	/* for launch plugins aprun and poe,
				 * srun forwards signal to the launch command */
	SRUN_NET_FORWARD,

	PMI_KVS_PUT_REQ = 7201,
	DEFUNCT_RPC_7202,
	PMI_KVS_GET_REQ,
	PMI_KVS_GET_RESP,

	RESPONSE_SLURM_RC = 8001,
	RESPONSE_SLURM_RC_MSG,
	RESPONSE_SLURM_REROUTE_MSG,

	RESPONSE_FORWARD_FAILED = 9001,

	ACCOUNTING_UPDATE_MSG = 10001,
	ACCOUNTING_FIRST_REG,
	ACCOUNTING_REGISTER_CTLD,
	ACCOUNTING_TRES_CHANGE_DB,
	ACCOUNTING_NODES_CHANGE_DB,

	SLURMSCRIPTD_REQUEST_FLUSH = 11001,
	SLURMSCRIPTD_REQUEST_FLUSH_JOB,
	SLURMSCRIPTD_REQUEST_RUN_SCRIPT,
	SLURMSCRIPTD_REQUEST_SCRIPT_COMPLETE,
	SLURMSCRIPTD_REQUEST_UPDATE_DEBUG_FLAGS,
	SLURMSCRIPTD_REQUEST_UPDATE_LOG,
	SLURMSCRIPTD_SHUTDOWN,
	SLURMSCRIPTD_REQUEST_BB_SCRIPT_INFO,

	/* scrun specific RPCs */
	REQUEST_CONTAINER_START = 12001, /* empty */
	RESPONSE_CONTAINER_START, /* container_started_msg_t */
	REQUEST_CONTAINER_PTY, /* empty */
	RESPONSE_CONTAINER_PTY, /* return_code_msg_t */
	REQUEST_CONTAINER_EXEC, /* container_exec_msg_t */
	RESPONSE_CONTAINER_EXEC, /* return_code_msg_t */
	REQUEST_CONTAINER_KILL, /* container_signal_msg_t */
	RESPONSE_CONTAINER_KILL, /* return_code_msg_t */
	REQUEST_CONTAINER_DELETE, /* container_delete_msg_t */
	RESPONSE_CONTAINER_DELETE, /* return_code_msg_t */
	REQUEST_CONTAINER_STATE, /* empty */
	RESPONSE_CONTAINER_STATE, /* return_code_msg_t */

	/* stepd proxy */
	PROXY_TO_NODE_SEND_RECV = 13001,
	PROXY_TO_NODE_SEND_ONLY,
	PROXY_TO_CTLD_SEND_RECV,
	PROXY_TO_CTLD_SEND_ONLY,

	/* reserve 64000 for SACK API codes */
} slurm_msg_type_t;

/*
 * Map slurm_msg_type_t values back to the enum name.
 *
 * WARNING: Strings are not xmalloc()'d. Do NOT xfree().
 */
extern const char *rpc_num2string(uint16_t msg_type);

#endif

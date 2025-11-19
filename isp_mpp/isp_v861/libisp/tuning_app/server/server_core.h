/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef _SERVER_CORE_H_V100_
#define _SERVER_CORE_H_V100_

#include "capture_image.h"

#define BUILD_VERSION        "4.3.1"
#define BUILD_VERSION_NUM    "431"

#define EMBED_DATA_MODE 1

#if EMBED_DATA_MODE
#define EMBED_DATA_SIZE_2IN1 (((8+8+8+8+192+192) << 2) * 2)
#define EMBED_DATA_SIZE ((8+8+8+8+192+192) << 2)
#else
#define EMBED_DATA_SIZE_2IN1 0
#define EMBED_DATA_SIZE 0
#endif

struct ToolsIniTuning_cfg {
	int enable;
	char base_path[50];
	char capture_path[50];
	sensor_input sensor_cfg;
	struct isp_param_config *params;
};

struct SpecialTuning_cfg {
	char command[50];
	int params[50];
};
void SetIniTuningEn(struct ToolsIniTuning_cfg cfg);
struct ToolsIniTuning_cfg GetIniTuningEn(void);

/*
 * socket handle threads for heart jump, preview, capture, tuning, statistics, shell script and so on
 * params: client socket fd
 */
void *sock_handle_heart_jump_thread(void *sock_th_params);
void *sock_handle_preview_thread(void *sock_th_params);
void *sock_handle_capture_thread(void *sock_th_params);
void *sock_handle_blockinfo_thread(void *sock_th_params);
void *sock_handle_tuning_thread(void *sock_th_params);
void *sock_handle_log_thread(void *params);
void *sock_handle_special_tuning_thread(void *sock_th_params);
void *sock_handle_offline_tuning_thread(void *sock_th_params);
void *sock_handle_statistics_thread(void *sock_th_params);
void *sock_handle_script_thread(void *sock_th_params);
void *sock_handle_register_thread(void *sock_th_params);
void *sock_handle_aelv_thread(void *sock_th_params);
void *sock_handle_set_input_thread(void *sock_th_params);
void *sock_handle_raw_flow_thread(void *sock_th_params);
void *sock_handle_isp_version_thread(void *sock_th_params);
void *sock_handle_preview_vencode_thread(void *params);
void *sock_handle_encoder_online_thread(void *params);

/*
 * check all threads status
 * one thread uses a bit, 0 - not run/exit, 1 - running
 * returns all threads status
 *    bit[0] - heart jump
 *    bit[1] - preview
 *    ......
 *    bit[24] - 1 to quit server
 *    others reserved
 */
typedef enum _thread_status_flag_e {
	TH_STATUS_HEART_JUMP               = 0x00000001,
	TH_STATUS_PREVIEW                  = 0x00000002,
	TH_STATUS_CAPTURE                  = 0x00000004,
	TH_STATUS_TUNING                   = 0x00000008,
	TH_STATUS_STATISTICS               = 0x00000010,
	TH_STATUS_SCRIPT                   = 0x00000020,
	TH_STATUS_REGISTER                 = 0x00000040,
	TH_STATUS_AELV                     = 0x00000080,
	TH_STATUS_SET_INPUT                = 0x00000100,
	TH_STATUS_RAW_FLOW                 = 0x00000200,
	TH_STATUS_VENC_TUNING              = 0x00000400,
	TH_STATUS_PREVIEW_VENCODE          = 0x00000800,
	TH_STATUS_BLOCK_INFO               = 0x00001000,
	TH_STATUS_LOG                      = 0x00002000,
	TH_STATUS_ENCODER_ONLINE           = 0x00004000,
	TH_STATUS_OFFLINE_TUNING           = 0x00008000,
	// others
	//...
	TH_STATUS_SERVER_QUIT              = 0x01000000,
} eThreadStatusFlag;

int CheckThreadsStatus();

#endif /* _SERVER_CORE_H_V100_ */


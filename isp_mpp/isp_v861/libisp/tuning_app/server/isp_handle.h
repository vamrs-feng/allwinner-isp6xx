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
#ifndef _ISP_HANDLE_H_V100_
#define _ISP_HANDLE_H_V100_

#include "../../isp.h"
#include "../../include/isp_tuning.h"
#include "capture_image.h"

/*
 * get current isp id
 * returns isp id, <0 if not init yet
 */
int get_isp_id();
/*
 * get isp version
 */
 void get_isp_version(char* version);

/*
 * init
 * returns 0 if init success, <0 if something went wrong
 */
int init_isp_module(int isp_id);
/*
 * exit
 * returns 0 if init success, <0 if something went wrong
 */
int exit_isp_module();
/*
 * select isp node
 * returns 0 if init success, <0 if something went wrong
 */
int select_isp(int id, int init_flag);
/*
 * select isp stitch
 * returns 0 if init success, <0 if something went wrong
 */
int select_isp_stitch_mode(int isp_id, enum stitch_mode_t stitch_mode);
/*
 * convert tuning configs from network to local
 */
void convert_tuning_cfg_to_local(HW_U8 group_id, HW_U32 cfg_ids, unsigned char *cfg_data);
/*
 * convert tuning configs from local to network
 */
void convert_tuning_cfg_to_network(HW_U8 group_id, HW_U32 cfg_ids, unsigned char *cfg_data);
/*
 * convert 3a statistics from local to network
 */
//void hton_3a_info(void *stat_info, int type);
/*
 * convert 3a statistics from network to local
 */
//void ntoh_3a_info(void *stat_info, int type);
/*
 * print 3a statistics
 */

void get_statistics_tbl_size(int type, int *tbl_w, int *tbl_h);

void output_3a_info(const void *stat_info, int type);

HW_S32 ini_tuning_get_cfg(HW_U8 group_id, HW_U32 cfg_ids, void *cfg_data);

HW_S32 ini_tuning_set_cfg(HW_U8 group_id, HW_U32 cfg_ids, void *cfg_data);

HW_S32 ini_tuning_update_cfg(void);

HW_S32 ini_tuning_get_frame(capture_format *cap_fmt, sock_packet *comm_packet, int sock_fd);

HW_S32 ini_tuning_get_raw(capture_format *cap_fmt, sock_packet *comm_packet, int sock_fd);

HW_S32 ini_tuning_get_encpp_frame(capture_format *cap_fmt, sock_packet *comm_packet, int sock_fd);

HW_S32 ini_tuning_get_3a_stat(struct isp_stats_context *stats_ctx);

HW_S32 get_log_params(int dev_id, unsigned char *buffer);

#endif /* _ISP_HANDLE_H_V100_ */

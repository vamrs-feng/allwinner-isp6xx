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
#ifndef _CAPTURE_IMAGE_H_V100_
#define _CAPTURE_IMAGE_H_V100_

#include "../socket_protocol.h"
#include "../../isp_math/isp_math_util.h"
#ifdef ANDROID_VENCODE
#include "../isp_vencode/ispSimpleCode.h"
#endif

typedef enum _capture_error_e {
	CAP_ERR_NONE               = 0x00,
	CAP_ERR_MPI_INIT,
	CAP_ERR_MPI_EXIT,
	CAP_ERR_CH_INIT,
	CAP_ERR_CH_EXIT,
	CAP_ERR_CH_SET_FMT,
	CAP_ERR_CH_GET_FMT,
	CAP_ERR_CH_ENABLE,
	CAP_ERR_CH_DISABLE,
	CAP_ERR_GET_FRAME,
	CAP_ERR_RELEASE_FRAME,
	CAP_ERR_INVALID_PARAMS,
	CAP_ERR_NOT_READY,
	CAP_ERR_NOT_SET_INPUT,
	CAP_ERR_START_RAW_FLOW,
	CAP_ERR_STOP_RAW_FLOW,
	CAP_ERR_RAW_FLOW_NOT_RUN,
	CAP_ERR_GET_RAW_FLOW,
	CAP_ERR_VENCODE_PPSSPS,
	CAP_ERR_VENCODE_STREAM,
	CAP_ERR_VENCODE_FREEBUFFER,
} capture_error;

typedef struct _capture_format_s {
	int                      channel; // for input
	unsigned char            *buffer; // for input and output
	int                      length;  // for output
	int                      width;   // for intpu and output
	int                      height;  // for input and output
	int                      fps;     // for input
	int                      wdr;     // for input
	int                      format;  // for input
	int                      planes_count; // planes count
	int                      framecount;//frame count
	int                      width_stride[3]; // width stride for each plane
	int                      index; //rear:0 front:1
	int                      isp;
	int                      stitch_mode;
	int                      ptn_en;
} capture_format;

typedef struct _sensor_input_s {
	int                      isp;
	int                      channel;
	int                      width;
	int                      height;
	int                      fps;
	int                      wdr;
	int                      format;
	int                      index; //rear:0 front:1
	int                      stitch_mode;
	int                      ptn_en;
} sensor_input;

typedef struct _region_s
{
	int                                   left;
	int                                   top;
	int                                   right;
	int                                   bottom;
} SRegion, *pSRegion;

/*
 * init
 * returns capture_error code
 */
int init_capture_module();
/*
 * exit
 * returns capture_error code
 */
int exit_capture_module();
/*
 * get vich channel status
 * bit[i] - vich i status, 0 - not open, 1 - opened
 * returns all vich channels status
 */
int get_vich_status();
/*
 * update vich channel ptn ptn_type, start&end count
 * returns 0 or -1
 */
int update_ptn_count(int vich, unsigned char ptn_type, unsigned int start_frame, unsigned int end_frame);
/*
 * set sensor input
 * returns capture_error code
 */
int set_sensor_input(const sensor_input *sensor_in);
/*
 * get capture buffer
 * cap_fmt->buffer should alloc in advance
 * returns capture_error code
 */
int get_capture_buffer(capture_format *cap_fmt, sock_packet *comm_packet, int sock_fd);

/*
 * get capture blockinfo
 * cap_fmt->buffer should alloc in advance
 * returns capture_error code
 */
int get_capture_blockinfo(capture_format *cap_fmt, int GrayBlocksFlag, SRegion *region);

#ifdef ANDROID_VENCODE
/*
 * update vencode config
 * return capture_error code
 */
int set_vencode_config(capture_format *cap_fmt, encode_param_t *encode_param, int type);
/*
 * get capture-video encoder buffer
 * cap_fmt->buffer should alloc in advance
 * returns capture_error code
 */
int get_capture_vencode_buffer(capture_format *cap_fmt, encode_param_t *encode_param, int type);
#endif

/*
 * get capture buffer to transfer
 * cap_fmt->buffer should alloc in advance
 * returns capture_error code
 */
int get_capture_buffer_transfer(capture_format *cap_fmt);
/*
 * start raw flow
 * returns capture_error code
 */
 int start_raw_flow(capture_format *cap_fmt);
/*
 * stop raw flow
 * returns capture_error code
 */
int stop_raw_flow(int channel);
/*
 * get one raw flow data
 * cap_fmt->buffer should alloc in advance
 * returns capture_error code
 */
int get_raw_flow_frame(capture_format *cap_fmt);
/*
 * save raw data to local
 */
void save_raw_flow(const char *file_name);
/*
 * set & get flip mode
 */
int video_set_flip(int vich, int hflip, int vflip);
int video_get_flip(int vich, int *hflip, int *vflip);

int video_cancel_ae_roi(int vich);
#endif /* _CAPTURE_IMAGE_H_V100_ */

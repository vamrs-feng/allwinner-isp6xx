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
#ifndef _RAW_FLOW_OPT_H_V100_
#define _RAW_FLOW_OPT_H_V100_

#include "capture_image.h"

typedef enum _raw_flow_err_e {
	ERR_RAW_FLOW_NONE                  = 0,
	ERR_RAW_FLOW_INVALID_PARAMS,
	ERR_RAW_FLOW_EXIT,
	ERR_RAW_FLOW_NOT_INIT,
	ERR_RAW_FLOW_FORMAT,
	ERR_RAW_FLOW_QUEUE_FULL,
	ERR_RAW_FLOW_QUEUE_EMPTY,
} eRawFlowErr;

/*
 * init raw flow queue
 * the size of memory to alloc is: sizeof(capture_format) * queue_length
 * raw_fmt: queue node format, raw_fmt->buffer is not used
 * queue_length: queue length
 * returns eRawFlowErr code
 */
int init_raw_flow(const capture_format *raw_fmt, int queue_length);
/*
 * exit raw flow
 * free queue data
 * returns eRawFlowErr code
 */
int exit_raw_flow();
/*
 * queue operation
 * queue one node to the head
 * node: raw data, format must be matched and data buffer is ready
 * returns eRawFlowErr code
 */
int queue_raw_flow(const capture_format *node);
/*
 * dequeue operation
 * dequeue one node from the tail
 * node: raw data, data buffer should alloc in advance
 * returns eRawFlowErr code
 */
int dequeue_raw_flow(capture_format *node);



#endif /* _RAW_FLOW_OPT_H_V100_ */


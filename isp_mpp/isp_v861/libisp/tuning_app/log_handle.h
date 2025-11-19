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
#ifndef _LOG_HANDLE_H_V100_
#define _LOG_HANDLE_H_V100_

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define DO_LOG_EN            1
#define LOG_TYPE_CONSOLE     0xfefdfcf1
#define LOG_TYPE_WRITE_FILE  0xfefdfcf2
#define LOG_TYPE             LOG_TYPE_CONSOLE

#if DO_LOG_EN
#if (LOG_TYPE_WRITE_FILE == LOG_TYPE)
#define INIT_LOG(log, mode)  init_log(log, mode);
#define CLOSE_LOG()          close_log();
#define LOG(format, ...)     write_log(format, ##__VA_ARGS__);
#else
#define INIT_LOG(log, mode)
#define CLOSE_LOG()
#define LOG(format, ...)     printf("%s"format, get_sys_time_label(), ##__VA_ARGS__);
#endif
#else
#define INIT_LOG(log, mode)
#define CLOSE_LOG()
#define LOG(format, ...)
#endif


/*
 * init log file
 * returns 0 if ok, <0 if something went wrong
 */
int init_log(const char *log_file, const char *mode);

/*
 * write log
 */
void write_log(const char *format, ...);

/*
 * close  log
 */
void close_log();

/*
 * get time label from system starts
 * returns format "<%6d.%09d>"
 */
const char *get_sys_time_label();

/*
 * get system time
 * default format: "%04d-%02d-%02d_%02d:%02d:%02d"
 */
void get_sys_time(char *time_str, const char *format);

#endif /* _LOG_HANDLE_H_V100_ */


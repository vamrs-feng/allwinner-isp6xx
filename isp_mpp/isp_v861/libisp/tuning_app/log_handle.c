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
#include <pthread.h>
#include <sys/file.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdarg.h>

#include "log_handle.h"

static FILE                  *g_log_file = NULL;
static pthread_mutex_t       g_log_locker;
static int                   g_log_locker_init_flag = 0;  // 0 - not init, 1 - inited

static char                  g_log_buffer[512];
static int                   g_log_buffer_length;
static struct timespec       g_log_time;
static char                  g_log_time_buffer[32];


int init_log(const char *log_file, const char *mode)
{
	if (!log_file || !mode) {
		return -1;
	}

	if (!g_log_locker_init_flag) {
		pthread_mutex_init(&g_log_locker, NULL);
		g_log_locker_init_flag = 1;
	}

	if (g_log_file) {
		fclose(g_log_file);
		g_log_file = NULL;
	}

	g_log_file = fopen(log_file, mode);
	if (!g_log_file) {
		printf("%s: failed to open %s\n", __FUNCTION__, log_file);
		return -2;
	}

	return 0;
}

void write_log(const char *format, ...)
{
    if (format && g_log_file && g_log_locker_init_flag) {
		pthread_mutex_lock(&g_log_locker);
		g_log_buffer_length = sprintf(g_log_buffer, "%s", get_sys_time_label());

		va_list ap;
		va_start(ap, format);
		g_log_buffer_length += vsprintf((g_log_buffer + g_log_buffer_length), format, ap);
		va_end(ap);

		fwrite(g_log_buffer, g_log_buffer_length, 1, g_log_file);
		fflush(g_log_file);
		pthread_mutex_unlock(&g_log_locker);
	}
}

void close_log()
{
	if (g_log_locker_init_flag) {
		pthread_mutex_lock(&g_log_locker);
		if (g_log_file) {
			fclose(g_log_file);
			g_log_file = NULL;
		}
		pthread_mutex_unlock(&g_log_locker);
		pthread_mutex_destroy(&g_log_locker);
		g_log_locker_init_flag = 0;
	}
}

const char *get_sys_time_label()
{
	clock_gettime(CLOCK_MONOTONIC, &g_log_time);
	sprintf(g_log_time_buffer, "<%6lu.%09lu>", (unsigned long)g_log_time.tv_sec, g_log_time.tv_nsec);
	return g_log_time_buffer;
}

void get_sys_time(char *time_str, const char *format)
{
	time_t t_sec;
	struct tm *local;

	if (time_str) {
		t_sec = time(NULL);
		local = localtime(&t_sec);
		if (format) {
			sprintf(time_str, format,
				local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
				local->tm_hour, local->tm_min, local->tm_sec);
		} else {
			sprintf(time_str, "%04d-%02d-%02d_%02d:%02d:%02d",
				local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
				local->tm_hour, local->tm_min, local->tm_sec);
		}
	}
}



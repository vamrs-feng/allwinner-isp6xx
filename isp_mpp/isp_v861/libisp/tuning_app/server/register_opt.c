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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#include "../log_handle.h"

#include "register_opt.h"


char   g_fd_addr_width[256];
char   g_fd_data_width[256];
char   g_fd_read_flag[256];
char   g_fd_cci_client[256];
char   g_fd_read_value[256];
int    g_reg_addr_width = 0;
int    g_reg_data_width = 0;

int write_file_opt(const char *file_name, void *data, int data_length)
{
	if (file_name && data_length > 0) {
		int fd = open(file_name, O_WRONLY|O_CREAT|O_TRUNC|O_SYNC, 0600);
		if (fd < 0 ) {
			return -1;
		} else {
			write(fd, data, data_length);
			close(fd);
			return 0;
		}
	}
	return -1;
}

int read_file_opt(const char *file_name, void *data, int *data_length)
{
	if (file_name && data_length) {
		int fd = open(file_name, O_RDONLY|O_NONBLOCK);
		if (fd < 0) {
			LOG("%s: failed to open %s(%d, %d, %s)\n", __FUNCTION__, file_name, fd, errno, strerror(errno));
			return -1;
		} else {
			*data_length = lseek(fd, 0, SEEK_END);
			lseek(fd, 0, SEEK_SET);
			read(fd, data, *data_length);
			close(fd);
			return 0;
		}
	}
	return -1;
}

/*
 * set register config
 * returns 0 if OK, others if something went wrong
 */
int set_reg_opt(const char *sensor_name, int addr_width, int data_width)
{
	char buffer[320];
	//int length = 0;

	if (sensor_name) {
		sprintf(g_fd_addr_width, "/sys/devices/%s/addr_width", sensor_name);
		sprintf(g_fd_data_width, "/sys/devices/%s/data_width", sensor_name);
		sprintf(g_fd_read_flag, "/sys/devices/%s/read_flag", sensor_name);
		sprintf(g_fd_cci_client, "/sys/devices/%s/cci_client", sensor_name);
		sprintf(g_fd_read_value, "/sys/devices/%s/read_value", sensor_name);
		g_reg_addr_width = addr_width;
		g_reg_data_width = data_width;

		// addr width
		//length = sprintf(buffer, "%x", g_reg_addr_width);
		//if (write_file_opt(g_fd_addr_width, buffer, length)) {
		//	return -1;
		//}
		sprintf(buffer, "echo %x > %s", g_reg_addr_width, g_fd_addr_width);
		system(buffer);

		// data width
		//length = sprintf(buffer, "%x", g_reg_data_width);
		//if (write_file_opt(g_fd_data_width, buffer, length)) {
		//	return -1;
		//}
		sprintf(buffer, "echo %x > %s", g_reg_data_width, g_fd_data_width);
		system(buffer);

		return 0;
	}
	return -1;
}

/*
 * read register
 * returns data, -1 if something went wrong
 */
int read_reg(int reg_addr, int data_width)
{
	char buffer[320];
	int length = 0;

	// set read flag
	//length = sprintf(buffer, "1");
	//if (write_file_opt(g_fd_read_flag, buffer, length)) {
	//	return -1;
	//}
	sprintf(buffer, "echo 1 > %s", g_fd_read_flag);
	system(buffer);

	// write addr
	//length = sprintf(buffer, "%04x0000", reg_addr);
	//if (write_file_opt(g_fd_cci_client, buffer, length)) {
	//	return -1;
	//}
	sprintf(buffer, "echo %04x0000 > %s", reg_addr, g_fd_cci_client);
	system(buffer);

	// read data
	usleep(10000);  // 10 ms
	if (read_file_opt(g_fd_read_value, buffer, &length)) {
		return -1;
	}
	buffer[data_width/4 + 2] = '\0';
	length = strtol(buffer, NULL, 16);
	//LOG("%s: read data %s, %d\n", __FUNCTION__, buffer, length);

	return length;
}

/*
 * write register
 * returns 0 if OK, others if something went wrong
 */
int write_reg(int reg_addr, int reg_data)
{
	char buffer[320];
	//int length = 0;

	// set read flag
	//length = sprintf(buffer, "0");
	//if (write_file_opt(g_fd_read_flag, buffer, length)) {
	//	return -1;
	//}
	sprintf(buffer, "echo 0 > %s", g_fd_read_flag);
	system(buffer);

	// write addr and data
	//length = sprintf(buffer, "%04x%04x", reg_addr, reg_data);
	//if (write_file_opt(g_fd_cci_client, buffer, length)) {
	//	return -1;
	//}
	sprintf(buffer, "echo %04x%04x > %s", reg_addr, reg_data, g_fd_cci_client);
	system(buffer);

	return 0;
}


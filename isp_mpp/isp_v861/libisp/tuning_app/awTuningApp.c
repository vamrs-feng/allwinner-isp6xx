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
#include "log_handle.h"
#include "./server/server_api.h"
#include "./server/server_core.h"
#include "./server/isp_handle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT          8848
int main(int argc, const char *argv[])
{
	int ret = -1;
	int port = SERVER_PORT;
	char path[70];
	struct ToolsIniTuning_cfg ini_cfg;
	memset(&ini_cfg, 0, sizeof(ini_cfg));
	ini_cfg.enable = 0;
	FILE *fd = NULL;
	sprintf(ini_cfg.base_path, "%s", INI_PATH);
	sprintf(ini_cfg.capture_path, "%s", INI_PATH);
	sprintf(path, "%sisp_tuning", ini_cfg.base_path);

#if SERVER_DEBUG_EN
	if (argc >= 2) {
		init_logger(argv[1], "wb");
	} else {
		init_logger("/data/hawkview_server.log", "wb");
	}
#endif

	LOG(                  "==================================================================================\n"
		"                  ==========   Welcome to Hawkview Tools Tuning Server                    ==========\n"
		"                  ==========   Build Version: %s, %s %s                 ==========\n"
		"                  ==========   Copyright (c) 2022 by Allwinnertech Co., Ltd.              ==========\n"
		"                  ==========   http://www.allwinnertech.com                               ==========\n",
		BUILD_VERSION, __TIME__, __DATE__
		);

	if (argc == 2) {
		port = atoi(argv[1]);
	} else if (argc == 3) {
		port = atoi(argv[1]);
		ini_cfg.enable = atoi(argv[2]);
	} else if (argc == 4) {
		port = atoi(argv[1]);
		ini_cfg.enable = atoi(argv[2]);
		sprintf(ini_cfg.base_path, "%s", argv[3]);
		sprintf(ini_cfg.capture_path, "%s", argv[3]);
		sprintf(path, "%sisp_tuning", ini_cfg.base_path);
	} else if (argc >= 5) {
		port = atoi(argv[1]);
		ini_cfg.enable = atoi(argv[2]);
		sprintf(ini_cfg.base_path, "%s", argv[3]);
		sprintf(ini_cfg.capture_path, "%s", argv[4]);
		sprintf(path, "%sisp_tuning", ini_cfg.base_path);
	}
	SetIniTuningEn(ini_cfg);

	if (ini_cfg.enable) {
		if (access(path, F_OK) != 0) {
			//sprintf(command, "touch %s", path);
			//system(command);
			fd = fopen(path, "w+");
			if (!fd) {
				LOG("can not create file: %s\n", path);
				return -1;
			}
			fclose(fd);
			fd = NULL;
			LOG("Create isptuning file: %s\n", path);
		} else {
			LOG("isptuning file already existed\n");
		}
		LOG("base_path = %s , capture_path = %s\n", ini_cfg.base_path, ini_cfg.capture_path);
	}

	ret = init_server(port);
	if (!ret) {
		LOG(              "==========   Hawkview Tools Tuning Server Starts up, Enjoy tuning now!  ==========\n"
		//"                  ==================================================================================\n"
			);
		ret = run_server();
	}

	exit_server();
	LOG(                  "==========   Hawkview Tools Tuning Server Exits, Bye-bye!               ==========\n"
		"                  ==================================================================================\n"
		);

#if SERVER_DEBUG_EN
	close_logger();
#endif

	return 0;
}


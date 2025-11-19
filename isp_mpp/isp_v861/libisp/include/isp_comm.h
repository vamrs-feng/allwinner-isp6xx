
/*
 * Hawkview ISP - isp_comm.h module
 * Copyright (c) 2018 by Allwinnertech Co., Ltd.  http://www.allwinnertech.com
 * Version: 1.0
 * Author: zhaowei
 * Date: 2018/07/11
 * Description isp500 && isp520 register header file
 */

#ifndef __BSP__ISP__COMM__H
#define __BSP__ISP__COMM__H

#include "isp_type.h"
#include "../isp_version.h"

#define ISP_REG_TBL_LENGTH_33         33
#define ISP_REG_TBL_LENGTH_32         32
#define ISP_REG_TBL_LENGTH_17         17
#define ISP_REG_TBL_LENGTH_16         16

#if (ISP_VERSION == 610)
#define USE_ENCPP
#endif
#define ISP_SHARP_GAMMA_TBL_LENGTH    64
#define ISP_GAMMA_TBL_LENGTH          (3*1024)

//ISP LOAD DRAM
#define ISP_LOAD_DRAM_SIZE            0x10200 //(AHB_SIZE + LOAD_SIZE + FE_TABLE_SIZE + BAYER_TABLE_SIZE + RGB_TABLE_SIZE + YUV_TABLE_SIZE)
#define ISP_AHB_REG_SIZE              0x40
#define ISP_LOAD_REG_SIZE             0xf00
#define ISP_FE_TABLE_SIZE             0x1800
#define ISP_BAYER_TABLE_SIZE          0x8580
#define ISP_RGB_TABLE_SIZE            0x500
#define ISP_YUV_TABLE_SIZE            0x5040

/*fe table*/
#define ISP_CH0_MSC_FE_MEM_OFS        0x0000
#define ISP_CH1_MSC_FE_MEM_OFS        0x0800
#define ISP_CH2_MSC_FE_MEM_OFS        0x1000

#define ISP_CH0_MSC_FE_TBL_SIZE       0x0800
#define ISP_CH1_MSC_FE_TBL_SIZE       0x0800
#define ISP_CH2_MSC_FE_TBL_SIZE       0x0800

/*bayer table*/
#define ISP_LSC_MEM_OFS             0x0000
#define ISP_MSC_MEM_OFS             0x0800
#define ISP_D2D_EBDNR_OFS           0x1000
#define ISP_D3D_DK_MEM_OFS          0x1400
#define ISP_D3D_EBDNR_OFS           0x1c00
#define ISP_DPC_SDP_TBL_OFS         0x2600
#define ISP_DPC_SPG_POS_TBL_OFS     0x3600
#define ISP_GCA_RB_CH_TBL_OFS       0x3800
#define ISP_FPN_CFPN_CORR_TBL_OFS   0x4580
#define ISP_PLTM_GTM_LM_TBL_OFS     0x6580

#define ISP_RSC_TBL_SIZE            0x0800
//#define ISP_MSC_TBL_SIZE          0x0800
#define ISP_D2D_EBDNR_SIZE          0x0300
#define ISP_D3D_DK_TBL_SIZE         0x0800
#define ISP_D3D_EBDNR_SIZE          0x0300
#define ISP_DPC_SDP_TBL_SIZE        0x1000
#define ISP_DPC_SPG_POS_TBL_SIZE    0x01e0
#define ISP_GCA_RB_CH_TBL_SIZE      0x0d48
#define ISP_FPN_CFPN_CORR_TBL_SIZE  0x2000
#define ISP_PLTM_GTM_LM_SIZE        0x2000

/*rgbtable*/
#define ISP_GAMMA_MEM_OFS           0x0000
#define ISP_SHARP_MOT_TEX_TBL_OFS   0x0400

#define ISP_GAMMA_TBL_SIZE          0x0400
#define ISP_SHARP_MOT_TEX_TBL_SIZE  0x0100

/*yuv table*/
#define ISP_CEM_MEM_OFS             0x0000
#define ISP_DRC_MEM_OFS             0x4f40

#define ISP_CEM_TBL0_SIZE           0x1700
#define ISP_CEM_TBL1_SIZE           0x1440
#define ISP_CEM_TBL2_SIZE           0x1200
#define ISP_CEM_TBL3_SIZE           0x1200
#define ISP_CEM_MEM_SIZE (ISP_CEM_TBL0_SIZE + ISP_CEM_TBL1_SIZE + ISP_CEM_TBL2_SIZE + ISP_CEM_TBL3_SIZE)
#define ISP_RGB_DRC_TBL_SIZE        0x0100

//ISP SAVE DRAM
#define ISP_SAVE_DRAM_SIZE          0x26500
#define ISP_SAVE_REG_SIZE           0x0100
#define ISP_STAT_TOTAL_SIZE         0x26500
#define ISP_STATISTIC_SIZE          0x26400

#define ISP_STAT_AFK_MEM_OFS        0x0100
#define ISP_STAT_D3D_MOT_MEM_OFS    0x0300
#define ISP_STAT_SHARP_TEX_OFS      0x0600
#define ISP_STAT_HIST0_MEM_OFS      0x0900
#define ISP_STAT_HIST1_MEM_OFS      0x0d00
#define ISP_STAT_PLTM_LUM_OFS       0x1100
#define ISP_STAT_AF_MEM_OFS         0x2900
#define ISP_STAT_AE_MEM_OFS         0x6500
#define ISP_STAT_AWB_MEM_OFS        0xe500

#define ISP_STAT_AFK_MEM_SIZE       0x0200
#define ISP_STAT_D3D_MOT_MEM_SIZE   0x0300
#define ISP_STAT_SHARP_TEX_SIZE     0x0300
#define ISP_STAT_HIST0_MEM_SIZE     0x0400
#define ISP_STAT_HIST1_MEM_SIZE     0x0400
#define ISP_STAT_PLTM_LUM_SIZE      0x1800
#define ISP_STAT_AF_HL_CNT_SIZE     0x0c00
#define ISP_STAT_AF_IIR0_SIZE       0x0c00
#define ISP_STAT_AE_MEM_SIZE        0x8000
#define ISP_STAT_AWB_RGB_MEM_SIZE   0x18000

//ISP SAVE_LOAD DRAM
#define ISP_SAVE_LOAD_DRAM_SIZE      0x1600
#define ISP_SAVE_LOAD_REG_SIZE       0x100
#define ISP_SAVE_LOAD_STATISTIC_SIZE 0x1500

#define ISP_SAVE_LOAD_PLTM_PKX_SIZE  0xc00
#define ISP_SAVE_LOAD_D3D_K_SIZE     0x300
#define ISP_SAVE_LOAD_D3D_MOT_SIZE   0x300
#define ISP_SAVE_LOAD_SHARP_TEX_SIZE 0x300

#define ISP_SAVE_LOAD_PLTM_PKX_OFS   ISP_STAT_TOTAL_SIZE
#define ISP_SAVE_LOAD_D3D_K_OFS (ISP_STAT_TOTAL_SIZE + ISP_SAVE_LOAD_PLTM_PKX_SIZE)
#define ISP_SAVE_LOAD_D3D_MOT_OFS (ISP_STAT_TOTAL_SIZE + ISP_SAVE_LOAD_PLTM_PKX_SIZE + ISP_SAVE_LOAD_D3D_K_SIZE)
#define ISP_SAVE_LOAD_SHARP_TEX_OFS (ISP_STAT_TOTAL_SIZE + ISP_SAVE_LOAD_PLTM_PKX_SIZE + ISP_SAVE_LOAD_D3D_K_SIZE + ISP_SAVE_LOAD_D3D_MOT_SIZE)

//ISP LDCI BUFFER
#define ISP_LDCI_BUFFER_OFS (ISP_STAT_TOTAL_SIZE + ISP_SAVE_LOAD_STATISTIC_SIZE)

/*
 *  update table
 */
#define GAMMA_UPDATE         (1 << 9)
#define DRC_UPDATE           (1 << 10)
#define D3D_UPDATE           (1 << 13)
#define PLTM_UPDATE          (1 << 14)
#define CEM_UPDATE           (1 << 15)
#define MSC_UPDATE           (1 << 16)
#define D2D_UPDATE           (1 << 18)
#define DPC_UPDATE           (1 << 21)
#define GCA_UPDATE           (1 << 22)
#define FPN_UPDATE           (1 << 23)
#define SHARP_MOT_TXT_UPDATE (1 << 24)

#define TABLE_UPDATE_ALL 0xffffffff

/*
 *  ISP Module enable
 */
#define WDR_EN         (1 << 0)
#define WDR_SPLIT_EN   (1 << 1)
#define CH0_DG_EN      (1 << 8)
#define CH1_DG_EN      (1 << 9)
#define CH2_DG_EN      (1 << 10)

#define WDR_STITCH_EN  (1 << 0)
#define DPC_EN         (1 << 1)
#define CTC_EN         (1 << 2)
#define GCA_EN         (1 << 3)
#define D2D_EN         (1 << 4)
#define D3D_EN         (1 << 5)
#define BLC_EN         (1 << 6)
#define WB_EN          (1 << 7)
#define DG_EN          (1 << 8)
#define MSC_EN         (1 << 10)
#define PLTM_EN        (1 << 11)
#define LCA_EN         (1 << 12)
#define SHARP_EN       (1 << 13)
#define CCM_EN         (1 << 14)
#define DRC_EN         (1 << 16)
#define GAMMA_EN       (1 << 17)
#define CEM_EN         (1 << 18)
#define FPN_EN         (1 << 20)
#define AE0_EN         (1 << 22)
#define AE2_EN         (1 << 24)
#define AF_EN          (1 << 25)
#define AWB_EN         (1 << 26)
#define AFS_EN         (1 << 27)
#define HIST0_EN       (1 << 28)
#define HIST1_EN       (1 << 29)
#define SHARP_TXT_INFO_INIT_EN (1 << 30)
#define D3D_MOT_INFO_INIT_EN   (1 << 31)

#define ISP_MODULE0_EN_ALL  (0xffffffff)
#define ISP_MODULE1_EN_ALL  (0xffffffff)

/* ISP module config */

/* TABLE */
#define ISP_LUT_TBL_SIZE        256
#define ISP_LENS_TBL_SIZE       256
#define ISP_MSC_TBL_SIZE        484
#define ISP_DRC_TBL_SIZE        256
#define ISP_TDNF_TBL_SIZE       256
#define ISP_PLTM_GTM_TBL_SIZE   4096
#define ISP_PLTM_LM_TBL_SIZE    128
#define ISP_SHARP_RT_TBL_SIZE   128

#define ISP_MSC_TBL_LENGTH      (3*ISP_MSC_TBL_SIZE)
#define ISP_LSC_TBL_LENGTH      (3*ISP_LENS_TBL_SIZE)

#define ISP_MSC_TBL_LUT_DLT_SIZE    12
#define ISP_MSC_TBL_LUT_SIZE        11
#define ISP_AF_SQUARE_TBL_LUT_SIZE  16
#define ISP_WDR_TBL_SIZE            24
#define ISP_PFPN_TBL_SIZE           8
#define ISP_CFPN_GAIN_CORR_TBL_SIZE 4096

#define ISP_GAMMA_TRIGGER_POINTS    5

#define ISP_CCM_TEMP_NUM            3
#define ISP_LSC_TEMP_NUM            6
#define ISP_MSC_TEMP_NUM            6

#define FE_CHN_NUM                  3

enum lensmode {
	FF_MODE = 1,
	AF_MODE = 2,
};

enum colorspace {
	BT601_FULL_RANGE = 0,
	BT709_FULL_RANGE,
	BT2020_FULL_RANGE,
	BT601_PART_RANGE,
	BT709_PART_RANGE,
	BT2020_PART_RANGE,
};

enum isp_raw_ch {
	ISP_RAW_CH_R =  0,
	ISP_RAW_CH_GR,
	ISP_RAW_CH_GB,
	ISP_RAW_CH_G,
	ISP_RAW_CH_MAX,
};

enum isp_ir_status {
	ISP_COLOR_MODE = 0,
	ISP_IR_MODE = 1,
	ISP_AIISP_MODE = 2,
};

enum isp_sharp_cfg {
	ISP_SHARP_DIR_HS_DTH_EDGE_TH = 0,//DIR-HS
	ISP_SHARP_DIR_HS_DTH_FLAT_TH = 1,
	ISP_SHARP_DIR_HS_DTH_EDGE_NSR = 2,
	ISP_SHARP_DIR_HS_DTH_FLAT_NSR = 3,
	ISP_SHARP_DIR_HS_BLK_STREN = 4,
	ISP_SHARP_DIR_HS_WHT_STREN = 5,
	ISP_SHARP_DIR_HS_BLK_CLIP_RATIO = 6,
	ISP_SHARP_DIR_HS_WHT_CLIP_RATIO = 7,
	ISP_SHARP_HS_SMTH_RATIO = 8,
	ISP_SHARP_HS_LUM_BLK_RATIO = 9,
	ISP_SHARP_HS_LUM_WHT_RATIO = 10,
	ISP_SHARP_NDIR_HS_EDGE_TH = 11,//NDIR-HS
	ISP_SHARP_NDIR_HS_FLAT_TH = 12,
	ISP_SHARP_NDIR_HS_BLK_STREN = 13,
	ISP_SHARP_NDIR_HS_WHT_STREN = 14,
	ISP_SHARP_NDIR_HS_BLK_CLIP = 15,
	ISP_SHARP_NDIR_HS_WHT_CLIP = 16,
	ISP_SHARP_DIR_MS_DTH_EDGE_TH = 17,//DIR-MS
	ISP_SHARP_DIR_MS_DTH_FLAT_TH = 18,
	ISP_SHARP_DIR_MS_DTH_EDGE_NSR = 19,
	ISP_SHARP_DIR_MS_DTH_FLAT_NSR = 20,
	ISP_SHARP_DIR_MS_BLK_STREN = 21,
	ISP_SHARP_DIR_MS_WHT_STREN = 22,
	ISP_SHARP_DIR_MS_BLK_CLIP_RATIO = 23,
	ISP_SHARP_DIR_MS_WHT_CLIP_RATIO = 24,
	ISP_SHARP_MS_LUM_BLK_RATIO = 25,
	ISP_SHARP_MS_LUM_WHT_RATIO = 26,
	ISP_SHARP_NDIR_MS_EDGE_TH = 27,//NDIR-MS
	ISP_SHARP_NDIR_MS_FLAT_TH = 28,
	ISP_SHARP_NDIR_MS_BLK_STREN = 29,
	ISP_SHARP_NDIR_MS_WHT_STREN = 30,
	ISP_SHARP_NDIR_MS_BLK_CLIP = 31,
	ISP_SHARP_NDIR_MS_WHT_CLIP = 32,
	ISP_SHARP_DIR_LS_DTH_EDGE_TH = 33,//DIR-LS
	ISP_SHARP_DIR_LS_DTH_FLAT_TH = 34,
	ISP_SHARP_DIR_LS_DTH_EDGE_NSR = 35,
	ISP_SHARP_DIR_LS_DTH_FLAT_NSR = 36,
	ISP_SHARP_DIR_LS_BLK_STREN = 37,
	ISP_SHARP_DIR_LS_WHT_STREN = 38,
	ISP_SHARP_DIR_LS_BLK_CLIP_RATIO = 39,
	ISP_SHARP_DIR_LS_WHT_CLIP_RATIO = 40,
	ISP_SHARP_LS_LUM_BLK_RATIO = 41,
	ISP_SHARP_LS_LUM_WHT_RATIO = 42,
	ISP_SHARP_NDIR_LS_EDGE_TH = 43,//NDIR-LS
	ISP_SHARP_NDIR_LS_FLAT_TH = 44,
	ISP_SHARP_NDIR_LS_BLK_STREN = 45,
	ISP_SHARP_NDIR_LS_WHT_STREN = 46,
	ISP_SHARP_NDIR_LS_BLK_CLIP = 47,
	ISP_SHARP_NDIR_LS_WHT_CLIP = 48,
	ISP_SHARP_NDIR_HS_MIX_LW_CLIP = 49,//COMM
	ISP_SHARP_NDIR_HS_MIX_HI_CLIP = 50,
	ISP_SHARP_NDIR_MS_MIX_LW_CLIP = 51,
	ISP_SHARP_NDIR_MS_MIX_HI_CLIP = 52,
	ISP_SHARP_NDIR_LS_MIX_LW_CLIP = 53,
	ISP_SHARP_NDIR_LS_MIX_HI_CLIP = 54,
	ISP_SHARP_BLK_CLIP_RATIO = 55,
	ISP_SHARP_WHT_CLIP_RATIO = 56,
	ISP_SHARP_MOTION_RATIO = 57,
	ISP_SHARP_STATIC_RATIO = 58,
	ISP_SHARP_FLAT_RATIO = 59,
	ISP_SHARP_TEXTURE_RATIO = 60,
	ISP_SHARP_MAX,
};

enum isp_sharp_comm_cfg {
	ISP_SHARP_TXT_INFO_EN = 0,
	ISP_SHARP_MOT_INFO_EN = 1,
	ISP_SHARP_DIR_HS_VAL_CV_EN = 2,
	ISP_SHARP_DIR_MS_VAL_CV_EN = 3,
	ISP_SHARP_DIR_LS_VAL_CV_EN = 4,
	ISP_SHARP_DIR_HS_LUM_CV_EN = 5,
	ISP_SHARP_DIR_MS_LUM_CV_EN = 6,
	ISP_SHARP_DIR_LS_LUM_CV_EN = 7,
	ISP_SHARP_NDIR_HS_VAL_CV_EN = 8,
	ISP_SHARP_NDIR_MS_VAL_CV_EN = 9,
	ISP_SHARP_NDIR_LS_VAL_CV_EN = 10,
	ISP_SHARP_NDIR_HS_LUM_CV_EN = 11,
	ISP_SHARP_NDIR_MS_LUM_CV_EN = 12,
	ISP_SHARP_NDIR_LS_LUM_CV_EN = 13,
	ISP_SHARP_SHARP_SENSITIVE = 14,
	ISP_SHARP_OUT_SEL = 15,
	ISP_SHARP_STAT_SRC = 16,
	ISP_SHARP_STAT_RATIO = 17,
	ISP_SHARP_HS_AA_RATIO = 18,
	ISP_SHARP_HS_AT_RATIO = 19,
	ISP_SHARP_HSV_SATU_SLOPE = 20,
	ISP_SHARP_MOT_SENS_RATIO = 21,
	ISP_SHARP_DIR_HS_VN_RATIO = 22,
	ISP_SHARP_DIR_MS_VN_RATIO = 23,
	ISP_SHARP_DIR_LS_VN_RATIO = 24,
	ISP_SHARP_DIR_HS_NMS_RATIO = 25,
	ISP_SHARP_DIR_MS_NMS_RATIO = 26,
	ISP_SHARP_DIR_HS_NMS_LW_CLIP = 27,
	ISP_SHARP_DIR_MS_NMS_LW_CLIP = 28,
	ISP_SHARP_NDIR_HS_EDGE_SLOPE = 29,
	ISP_SHARP_NDIR_MS_EDGE_SLOPE = 30,
	ISP_SHARP_NDIR_LS_EDGE_SLOPE = 31,
	ISP_SHARP_NDIR_HS_FLAT_SLOPE = 32,
	ISP_SHARP_NDIR_MS_FLAT_SLOPE = 33,
	ISP_SHARP_NDIR_LS_FLAT_SLOPE = 34,
	ISP_SHARP_NDIR_HS_VN_RATIO = 35,
	ISP_SHARP_NDIR_MS_VN_RATIO = 36,
	ISP_SHARP_NDIR_LS_VN_RATIO = 37,
	ISP_SHARP_COMM_MAX,
};

enum enc_encpp_top_cfg {
	ENCPP_TOP_CNR_RATIO = 0,
	ENCPP_TOP_SS_MAP_STREN = 1,
	ENCPP_TOP_LS_FUS_RATIO = 2,
	ENCPP_TOP_MAX,
};

enum enc_encpp_top_comm_cfg {
	ENCPP_TOP_ISPBE_OUT_SEL = 0,
	ENCPP_TOP_TEXTURE_IIR_EN = 1,
	ENCPP_TOP_TEXTURE_IIR_STREN = 2,
	ENCPP_TOP_MOTION_IIR_EN = 3,
	ENCPP_TOP_MOTION_IIR_STREN = 4,
	ENCPP_TOP_MOT_SENS_RATIO = 5,
	ENCPP_TOP_COMM_MAX,
};

enum enc_encpp_sharp_cfg {
	ENCPP_SHARP_DIR_HS_DTH_EDGE_TH = 0,//DIR-HS
	ENCPP_SHARP_DIR_HS_DTH_FLAT_TH = 1,
	ENCPP_SHARP_DIR_HS_DTH_EDGE_NSR = 2,
	ENCPP_SHARP_DIR_HS_DTH_FLAT_NSR = 3,
	ENCPP_SHARP_DIR_HS_BLK_STREN = 4,
	ENCPP_SHARP_DIR_HS_WHT_STREN = 5,
	ENCPP_SHARP_DIR_HS_BLK_CLIP_RATIO = 6,
	ENCPP_SHARP_DIR_HS_WHT_CLIP_RATIO = 7,
	ENCPP_SHARP_HS_SMTH_RATIO = 8,
	ENCPP_SHARP_HS_LUM_BLK_RATIO = 9,
	ENCPP_SHARP_HS_LUM_WHT_RATIO = 10,
	ENCPP_SHARP_NDIR_HS_EDGE_TH = 11,//NDIR-HS
	ENCPP_SHARP_NDIR_HS_FLAT_TH = 12,
	ENCPP_SHARP_NDIR_HS_BLK_STREN = 13,
	ENCPP_SHARP_NDIR_HS_WHT_STREN = 14,
	ENCPP_SHARP_NDIR_HS_BLK_CLIP = 15,
	ENCPP_SHARP_NDIR_HS_WHT_CLIP = 16,
	ENCPP_SHARP_DIR_MS_DTH_EDGE_TH = 17,//DIR-MS
	ENCPP_SHARP_DIR_MS_DTH_FLAT_TH = 18,
	ENCPP_SHARP_DIR_MS_DTH_EDGE_NSR = 19,
	ENCPP_SHARP_DIR_MS_DTH_FLAT_NSR = 20,
	ENCPP_SHARP_DIR_MS_BLK_STREN = 21,
	ENCPP_SHARP_DIR_MS_WHT_STREN = 22,
	ENCPP_SHARP_DIR_MS_BLK_CLIP_RATIO = 23,
	ENCPP_SHARP_DIR_MS_WHT_CLIP_RATIO = 24,
	ENCPP_SHARP_MS_LUM_BLK_RATIO = 25,
	ENCPP_SHARP_MS_LUM_WHT_RATIO = 26,
	ENCPP_SHARP_NDIR_MS_EDGE_TH = 27,//NDIR-MS
	ENCPP_SHARP_NDIR_MS_FLAT_TH = 28,
	ENCPP_SHARP_NDIR_MS_BLK_STREN = 29,
	ENCPP_SHARP_NDIR_MS_WHT_STREN = 30,
	ENCPP_SHARP_NDIR_MS_BLK_CLIP = 31,
	ENCPP_SHARP_NDIR_MS_WHT_CLIP = 32,
	ENCPP_SHARP_NDIR_HS_MIX_LW_CLIP = 33,//COMM
	ENCPP_SHARP_NDIR_HS_MIX_HI_CLIP = 34,
	ENCPP_SHARP_NDIR_MS_MIX_LW_CLIP = 35,
	ENCPP_SHARP_NDIR_MS_MIX_HI_CLIP = 36,
	ENCPP_SHARP_BLK_CLIP_RATIO = 37,
	ENCPP_SHARP_WHT_CLIP_RATIO = 38,
	ENCPP_SHARP_MOTION_RATIO = 39,
	ENCPP_SHARP_STATIC_RATIO = 40,
	ENCPP_SHARP_FLAT_RATIO = 41,
	ENCPP_SHARP_TEXTURE_RATIO = 42,
	ENCPP_SHARP_MAX,
};

enum enc_encpp_sharp_comm_cfg {
	ENCPP_SHARP_TXT_INFO_EN = 0,
	ENCPP_SHARP_MOT_INFO_EN = 1,
	ENCPP_SHARP_DIR_HS_VAL_CV_EN = 2,
	ENCPP_SHARP_DIR_MS_VAL_CV_EN = 3,
	ENCPP_SHARP_DIR_HS_LUM_CV_EN = 4,
	ENCPP_SHARP_DIR_MS_LUM_CV_EN = 5,
	ENCPP_SHARP_NDIR_HS_VAL_CV_EN = 6,
	ENCPP_SHARP_NDIR_MS_VAL_CV_EN = 7,
	ENCPP_SHARP_NDIR_HS_LUM_CV_EN = 8,
	ENCPP_SHARP_NDIR_MS_LUM_CV_EN = 9,
	ENCPP_SHARP_SHARP_SENSITIVE = 10,
	ENCPP_SHARP_OUT_SEL = 11,
	ENCPP_SHARP_STAT_SRC = 12,
	ENCPP_SHARP_HS_AA_RATIO = 13,
	ENCPP_SHARP_HS_AT_RATIO = 14,
	ENCPP_SHARP_HSV_SATU_SLOPE = 15,
	ENCPP_SHARP_DIR_HS_VN_RATIO = 16,
	ENCPP_SHARP_DIR_MS_VN_RATIO = 17,
	ENCPP_SHARP_DIR_HS_NMS_RATIO = 18,
	ENCPP_SHARP_DIR_MS_NMS_RATIO = 19,
	ENCPP_SHARP_DIR_HS_NMS_LW_CLIP = 20,
	ENCPP_SHARP_DIR_MS_NMS_LW_CLIP = 21,
	ENCPP_SHARP_NDIR_HS_EDGE_SLOPE = 22,
	ENCPP_SHARP_NDIR_MS_EDGE_SLOPE = 23,
	ENCPP_SHARP_NDIR_HS_FLAT_SLOPE = 24,
	ENCPP_SHARP_NDIR_MS_FLAT_SLOPE = 25,
	ENCPP_SHARP_NDIR_HS_VN_RATIO = 26,
	ENCPP_SHARP_NDIR_MS_VN_RATIO = 27,
	ENCPP_SHARP_COMM_MAX,
};

enum enc_encpp_ldci_cfg {
	ENCPP_LDCI_STRENGTH = 0,
	ENCPP_LDCI_DW_SLOPE_DARK = 1,
	ENCPP_LDCI_DW_SLOPE_BRIGHT = 2,
	ENCPP_LDCI_UP_SLOPE_DARK = 3,
	ENCPP_LDCI_UP_SLOPE_BRIGHT = 4,
	ENCPP_LDCI_GAIN_LOWER = 5,
	ENCPP_LDCI_GAIN_UPPER = 6,
	ENCPP_LDCI_MAD_RATIO = 7,
	ENCPP_LDCI_EQ_NEG_ENHANCE_STREN = 8,
	ENCPP_LDCI_EQ_POS_ENHANCE_STREN = 9,
	ENCPP_LDCI_EQ_ADJ_RATIO = 10,
	ENCPP_LDCI_MAX,
};

enum enc_encpp_ldci_comm_cfg {
	ENCPP_LDCI_MOT0_EN = 0,
	ENCPP_LDCI_MOT1_EN = 1,
	ENCPP_LDCI_TXT_EN = 2,
	ENCPP_LDCI_LUM_DIFF_SUP_EN = 3,
	ENCPP_LDCI_MIN_MAD = 4,
	ENCPP_LDCI_FLT_RATIO0 = 5,
	ENCPP_LDCI_FLT_RATIO1 = 6,
	ENCPP_LDCI_FLT_RATIO2 = 7,
	ENCPP_LDCI_FLT_RATIO3 = 8,
	ENCPP_LDCI_FLT_RATIO4 = 9,
	ENCPP_LDCI_FLT_RATIO5 = 10,
	ENCPP_LDCI_BLOCK_W_NUM = 11,
	ENCPP_LDCI_BLOCK_H_NUM = 12,
	ENCPP_LDCI_COMM_MAX,
};

enum encoder_denoise_cfg {
	ENCODER_DENOISE_3D_ADJ_PIX_LV_EN,//3DNR
	ENCODER_DENOISE_3D_SMT_FILT_EN,
	ENCODER_DENOISE_3D_MAX_PIX_DF_TH,
	ENCODER_DENOISE_3D_MAX_MAD_TH,
	ENCODER_DENOISE_3D_MAX_MV_TH,
	ENCODER_DENOISE_3D_MIN_COEF,
	ENCODER_DENOISE_3D_MAX_COEF,
	ENCODER_DENOISE_2D_FILT_STREN_UV,//2DNR
	ENCODER_DENOISE_2D_FILT_STREN_Y,
	ENCODER_DENOISE_2D_FILT_TH_UV,
	ENCODER_DENOISE_2D_FILT_TH_Y,
	ENCODER_DENOISE_MAX,
};

enum isp_denoise_cfg {
	ISP_DENOISE_BLACK_GAIN = 0,//DNR
	ISP_DENOISE_WHITE_GAIN = 1,
	ISP_DENOISE_FLTPD_Y_THR = 2,
	ISP_DENOISE_FLTPD_C_THR = 3,
	ISP_DENOISE_FLTPC_Y_THR = 4,
	ISP_DENOISE_FLTPC_C_THR = 5,
	ISP_DENOISE_FLTPC_C_STR = 6,
	ISP_DENOISE_NR_C_GAIN = 7,
	ISP_DENOISE_LYR0_NR_YBK_GAIN = 8,
	ISP_DENOISE_LYR1_NR_YBK_GAIN = 9,
	ISP_DENOISE_LYR2_NR_YBK_GAIN = 10,
	ISP_DENOISE_MOT_SENS_RATIO = 11,
	ISP_DENOISE_BLOCK_DNR_RT = 12,
	ISP_DENOISE_Y_MOTION = 13,
	ISP_DENOISE_Y_STATIC = 14,
	ISP_DENOISE_DTC_HF_WHT_STR = 15,//DTC
	ISP_DENOISE_DTC_HF_BLK_STR = 16,
	ISP_DENOISE_DTC_HF_WHT_CLP = 17,
	ISP_DENOISE_DTC_HF_BLK_CLP = 18,
	ISP_DENOISE_DTC_COR_RT = 19,
	ISP_DENOISE_DTC_LYR0_NR_DLT_CLP = 20,
	ISP_DENOISE_DTC_LYR1_NR_DLT_CLP = 21,
	ISP_DENOISE_DTC_LYR2_NR_DLT_CLP = 22,
	ISP_DENOISE_LYR0_DNR_LM_AMP = 23,//WDR
	ISP_DENOISE_LYR1_DNR_LM_AMP = 24,
	ISP_DENOISE_LYR2_DNR_LM_AMP = 25,
	ISP_DENOISE_LYR0_DNR_LMS_AMP = 26,
	ISP_DENOISE_LYR1_DNR_LMS_AMP = 27,
	ISP_DENOISE_LYR2_DNR_LMS_AMP = 28,
	ISP_DENOISE_MAX,
};

enum isp_denoise_comm_cfg {
	ISP_DENOISE_MOT_INFO_EN = 0,
	ISP_DENOISE_BLOCK_DNR_EN = 1,
	ISP_DENOISE_BLOCK_DNR_APPLY_AT = 2,
	ISP_DENOISE_LL_SCALE_SEL = 3,
	ISP_DENOISE_LYR0_NR_Y_EN = 4,
	ISP_DENOISE_LYR1_NR_Y_EN = 5,
	ISP_DENOISE_LYR2_NR_Y_EN = 6,
	ISP_DENOISE_OUT_SEL = 7,
	ISP_DENOISE_OUT_SEL_MODE = 8,
	ISP_DENOISE_CNR_CV_MODE = 9,
	ISP_DENOISE_FLTPD_Y_STR = 10,
	ISP_DENOISE_FLTPD_CB_STR = 11,
	ISP_DENOISE_FLTPD_CR_STR = 12,
	ISP_DENOISE_LYR0_NR_CRT = 13,
	ISP_DENOISE_LYR1_NR_CRT = 14,
	ISP_DENOISE_LYR2_NR_CRT = 15,
	ISP_DENOISE_CNT_RATIO0 = 16,
	ISP_DENOISE_CNT_RATIO1 = 17,
	ISP_DENOISE_CNT_RATIO2 = 18,
	ISP_DENOISE_WDR_LM_LW_SLP = 19,
	ISP_DENOISE_WDR_LM_HI_SLP = 20,
	ISP_DENOISE_WDR_LM_MAX_CLIP = 21,
	ISP_DENOISE_WDR_MS_LW_SLP = 22,
	ISP_DENOISE_WDR_MS_HI_SLP = 23,
	ISP_DENOISE_WDR_MS_MAX_CLIP = 24,
	ISP_DENOISE_COMM_MAX,
};

enum black_level {
	ISP_BLC_R_OFFSET = 0,
	ISP_BLC_GR_OFFSET = 1,
	ISP_BLC_GB_OFFSET = 2,
	ISP_BLC_B_OFFSET = 3,
	ISP_BLC_MAX,
};

enum dpc_cfg {
	ISP_DPC_HOT_RATIO = 0,
	ISP_DPC_COLD_RATIO = 1,
	ISP_DPC_HOT_NS_TH = 2,
	ISP_DPC_COLD_NS_TH = 3,
	ISP_DPC_NBHD_SMAD_RATIO = 4,
	ISP_DPC_NEAREST_SMAD_RATIO = 5,
	ISP_DPC_COLD_ABS_TH = 6,
	ISP_DPC_SUP_TWINKLE_THR_H = 7,
	ISP_DPC_SUP_TWINKLE_THR_L = 8,
	ISP_DPC_SATU_LUM_THR = 9,
	ISP_DPC_SATU_MIN_VAL = 10,
	ISP_DPC_SATU_PROT_RATIO = 11,
	ISP_DPC_MAX,
};

enum dpc_comm_cfg {
	ISP_DPC_DYNAMIC_CORR_EN = 0,
	ISP_DPC_STATIC_CORR_EN = 1,
	ISP_DPC_WEAK_MODE = 2,
	ISP_DPC_SUP_TWINKLE_EN = 3,
	ISP_DPC_STATIC_CALIBRATE_EN = 4,
	ISP_DPC_STATIC_CALIBRATE_TYPE = 5,
	ISP_DPC_STATIC_CALIBRATE_HIGHTLIGHT_EN = 6,
	ISP_DPC_FORCE_MEDIAN_FILTER_EN = 7,
	ISP_DPC_EDGE_PROT_SCALE = 8,
	ISP_DPC_STATIC_CNT_CALIBRA = 9,
	ISP_DPC_COMM_MAX,
};

enum pltm_dynamic_cfg {
	ISP_PLTM_DYNAMIC_AUTO_STREN = 0,
	ISP_PLTM_DYNAMIC_MANUL_STREN = 1,
	ISP_PLTM_DYNAMIC_LUM_RATIO = 2,
	ISP_PLTM_DYNAMIC_DCC_LW_RT = 3,
	ISP_PLTM_DYNAMIC_DSC_LW_RT = 4,
	ISP_PLTM_DYNAMIC_MIN_STREN_STEP = 5,
	ISP_PLTM_DYNAMIC_MAX_STREN_CLIP = 6,
	ISP_PLTM_DYNAMIC_SHP_HS_COMP = 7,
	ISP_PLTM_DYNAMIC_SHP_MS_COMP = 8,
	ISP_PLTM_DYNAMIC_SHP_LS_COMP = 9,
	ISP_PLTM_DYNAMIC_D2D_COMP = 10,
	ISP_PLTM_DYNAMIC_D3D_COMP = 11,
	ISP_PLTM_DYNAMIC_DARKNEST_RT = 12,
	ISP_PLTM_DYNAMIC_GTM_ALPHA = 13,
	ISP_PLTM_DYNAMIC_MAX,
};


enum isp_tdf_cfg {
	ISP_TDF_BLACK_GAIN = 0,//DNR
	ISP_TDF_WHITE_GAIN = 1,
	ISP_TDF_FLT1_THR_GAIN = 2,
	ISP_TDF_SS_MV_DNR = 3,
	ISP_TDF_SS_STL_DNR = 4,
	ISP_TDF_LS_MV_DNR = 5,
	ISP_TDF_LS_STL_DNR = 6,
	ISP_TDF_HF_CR_STR = 7,
	ISP_TDF_HF_CB_STR = 8,
	ISP_TDF_MF_CR_STR = 9,
	ISP_TDF_MF_CB_STR = 10,
	ISP_TDF_NR_LM_AMP = 11,
	ISP_TDF_NR_LMS_AMP = 12,
	ISP_TDF_BLOCK_DNR_RT = 13,
	ISP_TDF_DIFF_INTRA_SENS = 14,//MTD
	ISP_TDF_DIFF_INTER_SENS = 15,
	ISP_TDF_THR_INTRA_SENS = 16,
	ISP_TDF_THR_INTER_SENS = 17,
	ISP_TDF_STL_CYC_VAL = 18,
	ISP_TDF_MOT_CYC_VAL = 19,
	ISP_TDF_CYC_DEC_SLP = 20,
	ISP_TDF_REC_RTO_CLP = 21,
	ISP_TDF_MOT_SENS_RATIO = 22,
	ISP_TDF_DTC_HF_COR = 23,//DTC
	ISP_TDF_DTC_HF_BLK_CLP = 24,
	ISP_TDF_DTC_HF_WHT_CLP = 25,
	ISP_TDF_DTC_MF_COR = 26,
	ISP_TDF_DTC_MF_BLK_CLP = 27,
	ISP_TDF_DTC_MF_WHT_CLP = 28,
	ISP_TDF_HF_MOTION = 29,
	ISP_TDF_HF_STATIC = 30,
	ISP_TDF_MF_MOTION = 31,
	ISP_TDF_MF_STATIC = 32,
	ISP_TDF_HF_FLAT = 33,
	ISP_TDF_HF_TEXTURE = 34,
	ISP_TDF_MF_FLAT = 35,
	ISP_TDF_MF_TEXTURE = 36,
	ISP_TDF_D2D0_CNR_STREN = 37,//SRD
	ISP_TDF_MV_SATU = 38,
	ISP_TDF_MV_K_MIN = 39,
	ISP_TDF_MV_K_RATIO = 40,
	ISP_TDF_MV_R_MIN = 41,
	ISP_TDF_MV_R_RATIO = 42,
	ISP_TDF_DIFF_MIN_CLIP = 43,
	ISP_TDF_DIFF_CV_CLP = 44,
	ISP_TDF_NPU_FACE_NR = 45,
	ISP_TDF_MAX,
};

enum isp_tdf_comm_cfg {
	ISP_TDF_MOT_INFO_SCALE_SEL = 0,
	ISP_TDF_TEXTURE_CTRL_EN = 1,
	ISP_TDF_MOTION_CTRL_EN = 2,
	ISP_TDF_BLOCK_DNR_EN = 3,
	ISP_TDF_BLOCK_DNR_APPLY_AT = 4,
	ISP_TDF_FILT_OUT_SEL = 5,
	ISP_TDF_MOT_SEL = 6,
	ISP_TDF_OUT_SEL = 7,
	ISP_TDF_OUT_SEL_MODE = 8,
	ISP_TDF_DIFF_INTRA_AMP = 9,
	ISP_TDF_DIFF_INTER_AMP = 10,
	ISP_TDF_THR_INTRA_AMP = 11,
	ISP_TDF_THR_INTER_AMP = 12,
	ISP_TDF_WDR_LM_HI_SLP = 13,
	ISP_TDF_WDR_MS_HI_SLP = 14,
	ISP_TDF_WDR_LM_LW_SLP = 15,
	ISP_TDF_WDR_MS_LW_SLP = 16,
	ISP_TDF_WDR_LM_MAX_CLP = 17,
	ISP_TDF_WDR_MS_MAX_CLP = 18,
	ISP_TDF_STL_STG_CTH_0 = 19,
	ISP_TDF_STL_STG_CTH_1 = 20,
	ISP_TDF_STL_STG_CTH_2 = 21,
	ISP_TDF_STL_STG_CTH_3 = 22,
	ISP_TDF_STL_STG_CTH_4 = 23,
	ISP_TDF_STL_STG_CTH_5 = 24,
	ISP_TDF_STL_STG_CTH_6 = 25,
	ISP_TDF_STL_STG_CTH_7 = 26,
	ISP_TDF_STL_STG_KTH_0 = 27,
	ISP_TDF_STL_STG_KTH_1 = 28,
	ISP_TDF_STL_STG_KTH_2 = 29,
	ISP_TDF_STL_STG_KTH_3 = 30,
	ISP_TDF_STL_STG_KTH_4 = 31,
	ISP_TDF_STL_STG_KTH_5 = 32,
	ISP_TDF_STL_STG_KTH_6 = 33,
	ISP_TDF_STL_STG_KTH_7 = 34,
	ISP_TDF_MOT_STG_CTH_0 = 35,
	ISP_TDF_MOT_STG_CTH_1 = 36,
	ISP_TDF_MOT_STG_CTH_2 = 37,
	ISP_TDF_MOT_STG_CTH_3 = 38,
	ISP_TDF_MOT_STG_CTH_4 = 39,
	ISP_TDF_MOT_STG_CTH_5 = 40,
	ISP_TDF_MOT_STG_CTH_6 = 41,
	ISP_TDF_MOT_STG_CTH_7 = 42,
	ISP_TDF_MOT_STG_KTH_0 = 43,
	ISP_TDF_MOT_STG_KTH_1 = 44,
	ISP_TDF_MOT_STG_KTH_2 = 45,
	ISP_TDF_MOT_STG_KTH_3 = 46,
	ISP_TDF_MOT_STG_KTH_4 = 47,
	ISP_TDF_MOT_STG_KTH_5 = 48,
	ISP_TDF_MOT_STG_KTH_6 = 49,
	ISP_TDF_MOT_STG_KTH_7 = 50,
	ISP_TDF_COMM_MAX,
};

enum isp_ae_hist_cfg {
	ISP_AE_HIST_DARK_WEIGHT_MIN = 0,
	ISP_AE_HIST_DARK_WEIGHT_MAX = 1,
	ISP_AE_HIST_BRIGHT_WEIGHT_MIN = 2,
	ISP_AE_HIST_BRIGHT_WEIGHT_MAX = 3,
	ISP_AE_HIST_CFG_MAX,
};

enum isp_awb_cfg {
	ISP_AWB_RGAIN_FAVOR = 0,
	ISP_AWB_BGAIN_FAVOR = 1,
	ISP_AWB_MAX,
};

enum isp_gtm_comm_cfg {
	ISP_GTM_EQ_STREN = 0,
	ISP_GTM_CDF_RATIO = 1,
	ISP_GTM_GBL_EQ_LIMIT = 2,
	ISP_GTM_LOCAL_EQ_LIMIT = 3,
	ISP_GTM_DARK_UP_CLIP = 4,
	ISP_GTM_BRTGHT_UP_CLIP = 5,
	ISP_GTM_DARK_DOWN_CLIP = 6,
	ISP_GTM_BRTGHT_DOWN_CLIP = 7,
	ISP_GTM_SPEED = 8,
	ISP_GTM_RESERVE0 = 9,
	ISP_GTM_RESERVE1 = 10,
	ISP_GTM_RESERVE2 = 11,
	ISP_GTM_HEQ_MAX,
};

enum isp_pltm_comm_cfg {
	ISP_PLTM_MODE           = 0,
	ISP_PLTM_SPEED          = 1,
	ISP_PLTM_TOLERANCE      = 2,
	ISP_PLTM_GTM_EN         = 3,
	ISP_PLTM_LTF_EN         = 4,
	ISP_PLTM_DCC_EN         = 5,
	ISP_PLTM_DCC_SHF_BIT    = 6,
	ISP_PLTM_DCC_LW_TH      = 7,
	ISP_PLTM_DCC_HI_TH      = 8,
	ISP_PLTM_DSC_EN         = 9,
	ISP_PLTM_DSC_SHF_BIT    = 10,
	ISP_PLTM_DSC_LW_TH      = 11,
	ISP_PLTM_DSC_HI_TH      = 12,
	ISP_PLTM_MGC_INT_SMTH   = 13,
	ISP_PLTM_MGC_LUM_ADPT   = 14,
	ISP_PLTM_STS_CEIL_SLP   = 15,
	ISP_PLTM_STS_FLOOR_SLP  = 16,
	ISP_PLTM_STS_GD_RT      = 17,
	ISP_PLTM_ADJK_CRCT_RT   = 18,
	ISP_PLTM_INTERVAL       = 19,
	ISP_PLTM_DARK_LOW_TH    = 20,
	ISP_PLTM_DARK_HIGH_TH   = 21,
	ISP_PLTM_DARKNEST_NUM   = 22,
	ISP_PLTM_COMM_RESERVE0  = 23,
	ISP_PLTM_COMM_RESERVE1  = 24,
	ISP_PLTM_COMM_RESERVE2  = 25,
	ISP_PLTM_MAX,
};

enum isp_gca_cfg {
	ISP_GCA_MODE = 0,
	ISP_GCA_BLOCK_W = 1,
	ISP_GCA_BLOCK_H = 2,
	ISP_GCA_START_W = 3,
	ISP_GCA_START_H = 4,
	ISP_GCA_MAX,
};

enum isp_cem_cfg {
	ISP_CEM_RATIO = 0,
	ISP_CEM_DARK_SATU = 1,
	ISP_CEM_LOW_LI_SATU = 2,
	ISP_CEM_MID_LI_SATU = 3,
	ISP_CEM_HIGH_LI_SATU = 4,
	ISP_CEM_MAX,
};

enum isp_lca_cfg {
	ISP_LCA_GF_COR_RATIO = 0,
	ISP_LCA_PF_COR_RATIO = 1,
	ISP_LCA_LUM_LOW_TH = 2,
	ISP_LCA_LUM_HIGH_TH = 3,
	ISP_LCA_GRAD_LOW_TH = 4,
	ISP_LCA_GRAD_HIGH_TH = 5,
	ISP_LCA_PF_WEIGHT = 6,
	ISP_LCA_GF_WEIGHT = 7,
	ISP_LCA_PF_RSHF = 8,
	ISP_LCA_PF_BSLP = 9,
	ISP_LCA_LUM_GAIN_SLOPE = 10,
	ISP_LCA_GF_LUM_MAX = 11,
	ISP_LCA_PF_LUM_MAX = 12,
	ISP_LCA_MAX,
};

enum isp_lca_comm_cfg {
	ISP_LCA_GRAD_GAIN1_EN = 0,
	ISP_LCA_GRAD_GAIN2_EN = 1,
	ISP_LCA_CLR_GTH = 2,
	ISP_LCA_CLRS_LUM_TH = 3,
	ISP_LCA_PF_CLRC_RATIO = 4,
	ISP_LCA_GF_CLRC_RATIO = 5,
	ISP_LCA_PF_DECR_RATIO = 6,
	ISP_LCA_COMM_MAX,
};

enum isp_cfa_cfg {
	ISP_CFA_AFC_CNR_STREN = 0,
	ISP_CFA_AFC_RGB_STREN = 1,
	ISP_CFA_AFC_BAYER_STREN = 2,
	ISP_CFA_AFC_CNR_ADJUST_STREN = 3,
	ISP_CFA_AFC_RGB_ADJUST_STREN = 4,
	ISP_CFA_AFC_BAYER_ADJUST_STREN = 5,
	ISP_CFA_AFC_SATU_GAIN = 6,
	ISP_CFA_MAX,
};

enum isp_nrp_cfg {
	ISP_NRP_DLE_MF_CLIP = 0,
	ISP_NRP_DLE_Y_RATIO = 1,
	ISP_NRP_MAX,
};

enum isp_nrp_comm_cfg {
	ISP_NRP_DLE_EN = 0,
	ISP_NRP_DLE_WIN_SEL = 1,
	ISP_NRP_DLE_NEG_RATIO = 2,
	ISP_NRP_DLE_HF_RT_LW = 3,
	ISP_NRP_DLE_HF_RT_HI = 4,
	ISP_NRP_COMM_MAX,
};

enum isp_platform {
	ISP_PLATFORM_SUN8IW12P1,
	ISP_PLATFORM_SUN8IW16P1,
	ISP_PLATFORM_SUN8IW21P1,

	ISP_PLATFORM_NUM,
};

struct isp_size {
	HW_U32 width;
	HW_U32 height;
};

enum enable_flag {
	DISABLE    = 0,
	ENABLE     = 1,
};

enum wdr_mode {
	WDR_1FCH = 0,
	WDR_2FCH = 1,
	WDR_3FCH = 2,
	WDR_4FCH = 3,
};

enum channl_data_mode {
	CHN_DISABLE = 0,
	CHN_LINEAR,

	CHN_WDR_ORIGINAL_LM,
	CHN_WDR_ORIGINAL_L,
	CHN_WDR_ORIGINAL_M,
	CHN_WDR_ORIGINAL_S,
	CHN_WDR_ORIGINAL_MS,

	CHN_WDR_SPLIT_LM,
	CHN_WDR_SPLIT_L,
	CHN_WDR_SPLIT_M,
	CHN_WDR_SPLIT_S,
	CHN_WDR_SPLIT_MS,
	CHN_WDR_LMS,
};

enum isp_wdr_stitch_mode {
	ISP_WDR_STITCH_LINEAR = 0,
	ISP_WDR_STITCH_2F_LM,
	ISP_WDR_STITCH_3F_LMS,
};

enum attribute_of_channl_t {
	LINEAR_FROM_ONE_CHN = 0,
	WDR_2F_FROM_ONE_CHN = 4,
	WDR_2F_FROM_TWO_CHN = 5,
	WDR_3F_FROM_ONE_CHN = 8,
	WDR_3F_FROM_TWO_CHN = 9,
	WDR_3F_FROM_THREE_CHN = 10,
};

enum attribute_of_fe_channl_t {
	DATA_FROM_TDMTX0 = 0,
	DATA_FROM_TDMTX1 = 1,
	DATA_FROM_TDMTX2 = 2,
	DATA_FROM_RESERVED = 3,
	DATA_FROM_SPLITL = 4,
	DATA_FROM_SPLITM = 5,
	DATA_FROM_SPLITS = 6,
};

enum split_output_mode_t {
	SPLITO_LINEAR = 0,
	SPLITO_LM_TO_L_M = 4,
	SPLITO_LM_TO_LM_M = 5,
	SPLITO_MS_TO_M_MS = 6,
	SPLITO_LMS_TO_L_M_S = 8,
	SPLITO_LMS_TO_LM_M_S = 9,
	SPLITO_LMS_TO_L_M_MS = 10,
};

enum split_input_mode_t {
	SPLITI_LINEAR = 0,
	SPLITI_SENSOR_BUILD_IN = 1,
	SPLITI_16LOG = 2,
};

enum isp_dmsc_mode {
	DMSC_NORMAL = 0,
	DMSC_BW = 1,
};

enum isp_ccm_sel {
	CCM_BEFORE_DENOISE = 0,
	CCM_BEFORE_LCA = 1,
	CCM_AFTER_LCA = 2,
};

enum isp_d3d_ref_frame_mode {
	D3D_REF_FRAME_LBC = 0,
	D3D_REF_FRAME_PACKAGE = 1,
};

enum isp_gain_src {
	GAIN_BEFORE_DN = 0,
	GAIN_AFTER_DN = 1,
};

enum isp_wb_src {
	WB_BEFORE_DN = 0,
	WB_AFTER_DN = 1,
};

enum isp_hist_mode {
	HIST_ONE_FRAME_CH0 = 0,
	HIST_ONE_FRAME_CH1 = 1,
	HIST_ONE_FRAME_CH2 = 2,
};

enum isp_hist_src {
	HIST_ST_FE_MSC = 0,
	HIST_ST_DPC = 1,
	HIST_ST_MSC = 2,
	HIST_ST_CCM = 3,
	HIST_ST_CSC = 4,
	HIST_ST_DRC = 5,
	HIST_ST_CEM = 6,
};

enum isp_af_src {
	AF_ST_FE_MSC = 0,
	AF_BEFORE_D2D = 1,
	AF_AFTER_D2D = 2,
	AF_ST_PLTM = 3,
	AF_ST_CSC = 4,
};

enum isp_af_mode {
	AF_ONE_FRAME_CH0 = 0,
	AF_ONE_FRAME_CH1 = 1,
	AF_ONE_FRAME_CH2 = 2,
	AF_ONE_FRAME_CH3 = 3,
};

enum isp_afk_src {
	AFK_ST_NRP_BLC = 0,
	AFK_ST_INV_GAMMA = 1,
	AFK_ST_MSC = 2,
};

enum isp_awb_src {
	AWB_ST_FE_MSC = 0,
	AWB_ST_FPN = 1,
	AWB_ST_MSC = 2,
	AWB_ST_PLTM = 3,
};

enum isp_awb_mode {
	AWB_ONE_FRAME_CH0 = 0,
	AWB_ONE_FRAME_CH1 = 1,
	AWB_ONE_FRAME_CH2 = 2,
	AWB_ONE_FRAME_CH3 = 3,
	AWB_TWO_FRAME_CH01 = 4,
	AWB_THREE_FRAME_CH012 = 5,
	AWB_FOUR_FRAME_CH0123 = 6,
};

enum isp_ae_src {
	AE_ST_FE0_MSC = 0,
	AE_ST_FE1_MSC = 1,
	AE_ST_FE2_MSC = 2,
	AE_ST_MSC = 3,
	AE_ST_CCM = 4,
	AE_ST_CSC = 5,
	AE_ST_DRC = 6,
	AE_ST_CEM = 7,
};

enum isp_dg_mode {
	DG_AFTER_WDR = 0,
	DG_BEFORE_WDR = 1,
	DG_AFTER_WDR_ADAPT = 2, /* Use for low-end sensors with very low analog gain, such as f37 */
};

enum isp_proc_mode { /*wdr stitch input*/
	PROC_LINEAR = 0,
	PROC_LM_FOR_L_M = 4,
	PROC_LMS_FOR_L_M_S = 8,
	PROC_LMS_FOR_LM_M_S = 9,
	PROC_LMS_FOR_L_M_MS = 10,
};

enum isp_input_seq {
	ISP_BGGR = 4,
	ISP_RGGB = 5,
	ISP_GBRG = 6,
	ISP_GRBG = 7,
};

struct isp_ctc_config {
	HW_U16 ctc_low_th;
	HW_U16 ctc_high_th;
	HW_U16 ctc_low_th_slope;
	HW_U16 ctc_high_th_slope;
	HW_U8 ctc_dir_wt;
	HW_U16 ctc_dir_th;
};

struct video_input_config {
	HW_U8 input_cfg;
	HW_U8 output_cfg;
	HW_U8 output_ch0_data;
	HW_U8 output_ch1_data;
	HW_U8 output_ch2_data;
};

struct isp_wdr_split_config {
	HW_U8 blc_en;
	HW_U8 inv_blc_en;
	HW_U8 ch_sel;
	HW_U8 input_mode;
	HW_U8 decomp_input_bit;
	HW_U8 output_mode;
	HW_U8 bitexp_output_bit;
	HW_U8 input_nrml;
	HW_U16 nrml_ratio[2];
	HW_U16 decomp_range[5];
	HW_U16 decomp_slope[5];
	HW_U16 decomp_offset[4];
};

struct isp_offset {
	HW_S16 r_offset;
	HW_S16 gr_offset;
	HW_S16 gb_offset;
	HW_S16 b_offset;
};

struct isp_dg_gain {
	HW_U16 r_gain;
	HW_U16 gr_gain;
	HW_U16 gb_gain;
	HW_U16 b_gain;
};

struct isp_front_end_config {
	HW_U8 chn_data_mode;
	HW_U8 blc_en;
	HW_U8 inv_blc_en;
	HW_U8 input_bit;
	HW_U8 output_bit;
	struct isp_offset offset;
	struct isp_dg_gain gain;
};

struct isp_wdr_config {
	HW_U8 wdr_stitch_mode;
	HW_U8 wdr_lexp_blc_en;
	HW_U8 wdr_wb_l_en;
	HW_U8 wdr_wb_m_en;
	HW_U8 wdr_wb_s_en;
	HW_U8 wdr_sexp_chk_lm_en;
	HW_U8 wdr_sexp_chk_ms_en;
	HW_U8 wdr_lecc_lm_en;
	HW_U8 wdr_lecc_ms_en;
	HW_U8 wdr_de_purpl_lm_en;
	HW_U8 wdr_de_purpl_ms_en;
	HW_U8 wdr_mv_chk_lm_en;
	HW_U8 wdr_mv_chk_ms_en;
	HW_U8 wdr_wb_l_mode;
	HW_U8 wdr_wb_m_mode;
	HW_U8 wdr_wb_s_mode;
	HW_U8 wdr_out_sel;
	HW_U8 wdr_lwb_nratio;
	HW_U32 wdr_lms_exp_ratio;

	HW_U16 lm_cmp_slp;
	HW_U16 lm_exp_ratio;
	HW_U16 lm_cmp_lth;
	HW_U16 lm_cmp_hth;
	HW_U16 lm_sexp_chk_slp;
	HW_U16 lm_sexp_chk_lth;
	HW_U16 lm_lecc_jdg_slp;
	HW_U16 lm_lecc_jdg_lth;
	HW_U16 lm_lecc_crc_rth;
	HW_U16 lm_lecc_crc_lth;
	HW_U16 lm_de_purpl_lrt;
	HW_U16 lm_de_purpl_lth;
	HW_U16 lm_mv_chk_slp;
	HW_U16 lm_mv_chk_lth;
	HW_U16 lm_mv_fcl_slp;
	HW_U16 lm_mv_fcl_lth;

	HW_U16 ms_cmp_slp;
	HW_U16 ms_exp_ratio;
	HW_U16 ms_cmp_lth;
	HW_U16 ms_cmp_hth;
	HW_U16 ms_sexp_chk_slp;
	HW_U16 ms_sexp_chk_lth;
	HW_U16 ms_lecc_jdg_slp;
	HW_U16 ms_lecc_jdg_lth;
	HW_U16 ms_lecc_crc_rth;
	HW_U16 ms_lecc_crc_lth;
	HW_U16 ms_de_purpl_lrt;
	HW_U16 ms_de_purpl_lth;
	HW_U16 ms_mv_chk_slp;
	HW_U16 ms_mv_chk_lth;
	HW_U16 ms_mv_fcl_slp;
	HW_U16 ms_mv_fcl_lth;

	HW_U8 wdr_de_purpl_hsv_tbl[ISP_WDR_TBL_SIZE];
};

struct isp_fpn_config {
	HW_U8 fpn_pfpn_en;
	HW_U8 fpn_cfpn_en;
	HW_U8 fpn_pfpn_cluster_size;

	HW_S8 fpn_pfpn_phase_lut[ISP_PFPN_TBL_SIZE];
	HW_U8 fpn_pfpn_period_lut[ISP_PFPN_TBL_SIZE];
	HW_U8 fpn_cfpn_coeff_lut[ISP_REG_TBL_LENGTH_17];
	HW_S8 fpn_pfpn_offset_lut[ISP_PFPN_TBL_SIZE];
	HW_U8 fpn_pfpn_scale_coeff_lut[ISP_PFPN_TBL_SIZE];
};

struct isp_dpc_config {
	HW_U8 dynamic_corr_en;
	HW_U8 static_corr_en;
	HW_U8 weak_mode;
	HW_U8 sup_twinkle_en;
	HW_U8 static_calibrate_en;
	HW_U8 static_calibrate_type;
	HW_U8 static_highlight_en;
	HW_U8 static_force_median_filter_en;
	HW_U16 hot_noise_th;
	HW_U16 cold_noise_th;
	HW_U16 hot_ratio;
	HW_U16 cold_ratio;
	HW_U8 sup_twinkle_thr_h;
	HW_S8 sup_twinkle_thr_l;
	HW_U16 slope_prec_coeff;
	HW_U16 nbhd_smad_ratio;
	HW_U16 nearest_smad_ratio;
	HW_U8 smad_remove_idx;
	HW_U16 satu_lum_thr;
	HW_U16 satu_prot_ratio;
	HW_U8 satu_min_val;
	HW_U16 static_count_calibra;
	HW_U16 cold_abs_th;
};

struct isp_nrp_config {
	HW_U8 blc0_en;
	HW_U8 gamma_en;
	HW_U8 inv_blc0_en;
	HW_U8 inv_gamma_en;
	HW_U8 gm_neg_ratio;
	HW_U8 dle_en;
	HW_U8 dle_win_sel;
	HW_U8 dle_neg_ratio;
	HW_U8 blc1_en;
	HW_U8 inv_blc1_en;
	HW_S16 blc_r_offset;
	HW_S16 blc_gr_offset;
	HW_S16 blc_gb_offset;
	HW_S16 blc_b_offset;
	HW_U8 cb_hf_rt_lw;
	HW_U8 cb_hf_rt_hi;
	HW_U8 cr_hf_rt_lw;
	HW_U8 cr_hf_rt_hi;
	HW_U16 cb_mf_clp;
	HW_U16 cr_mf_clp;
	HW_U8 y_ratio;
};

struct isp_nr_config {
	HW_U8 wdr_nrml;
	HW_U8 wdr_blc;
	HW_U16 nrml_ratio[2];
	HW_U16 wdr_lm_cmp_hth;
	HW_U16 wdr_lm_cmp_lth;
	HW_U16 wdr_ms_cmp_hth;
	HW_U16 wdr_ms_cmp_lth;
	HW_U16 wdr_lm_cmp_slp;
	HW_U16 wdr_ms_cmp_slp;
};

struct isp_gca_config {
	HW_U16 gca_block_w;
	HW_U16 gca_block_h;
	HW_U16 gca_div_num_w;
	HW_U16 gca_div_num_h;
	HW_U8 gca_start_w;
	HW_U8 gca_start_h;

	HW_S8 gca_hor_r_offset[825];
	HW_S8 gca_ver_r_offset[825];
	HW_S8 gca_hor_b_offset[825];
	HW_S8 gca_ver_b_offset[825];
};

struct isp_lca_config {
	HW_U16 lca_lum_low_th;
	HW_U16 lca_lum_slope;
	HW_U16 lca_grad_low_th;
	HW_U16 lca_grad_slope;
	HW_U8 lca_grad_gain1_en;
	HW_U8 lca_grad_gain2_en;
	HW_U8 lca_gf_weight;
	HW_U8 lca_pf_weight;
	HW_U16 lca_clr_gth;
	HW_U8 lca_pf_rshf;
	HW_U16 lca_pf_bslp;
	HW_U16 lca_gf_cor_ratio;
	HW_U16 lca_pf_cor_ratio;
	HW_U8 lca_clrs_lum_th;
	HW_U8 lca_pf_clrc_ratio;
	HW_U8 lca_gf_clrc_ratio;
	HW_U8 lca_pf_decr_ratio;
	HW_U8 lca_lum_gain_slope;
	HW_U8 lca_gf_lum_max;
	HW_U8 lca_pf_lum_max;

	HW_U8 lca_pf_satu_lut[ISP_REG_TBL_LENGTH_33];
	HW_U8 lca_gf_satu_lut[ISP_REG_TBL_LENGTH_33];
};

struct isp_cnr_config {
	HW_U16 c_threshold;
	HW_U16 y_threshold;
	HW_U16 st_v_yth;
	HW_U16 st_h_yth;
};

struct isp_d2d_config {
	HW_U8 d2d_recr_en;
	HW_U8 d2d_recw_en;
	HW_U8 d2d_mot_info_en;
	HW_U8 d2d_bnr_en;
	HW_U8 d2d_bnr_sel;
	HW_U8 d2d_ll_ups_type;
	HW_U8 lyr0_nr_y_en;
	HW_U8 lyr1_nr_y_en;
	HW_U8 lyr2_nr_y_en;
	HW_U8 d2d_out_sel;
	HW_U8 d2d_out_mode;
	HW_U16 wdr_lm_max_clp;
	HW_U16 wdr_ms_max_clp;
	HW_U8 wdr_lm_lw_slp;
	HW_U8 wdr_lm_hi_slp;
	HW_U8 wdr_ms_lw_slp;
	HW_U8 wdr_ms_hi_slp;
	HW_U8 filtpd_y_thr;
	HW_U8 filtpd_c_thr;
	HW_U8 filtpd_y_str;
	HW_U8 filtpd_cb_str;
	HW_U8 filtpd_cr_str;
	HW_U8 filtpc_y_thr;
	HW_U8 filtpc_c_thr;
	HW_U8 filtpc_cb_str;
	HW_U8 filtpc_cr_str;
	HW_U8 cnt_ratio[3];
	HW_U16 dtc_hf_blk_clp;
	HW_U16 dtc_hf_wht_clp;
	HW_U16 dtc_hf_blk_str;
	HW_U16 dtc_hf_wht_str;
	HW_U8 dtc_cor_ratio;
	HW_U8 mot_sens_ratio;
	HW_U16 lyr_nr_lm_amp[3];
	HW_U16 lyr_nr_lms_amp[3];
	HW_U16 lyr_nr_crt[3];
	HW_U16 lyr_nr_dlt_clp[3];
	HW_U32 d2d_div_num;

	HW_U16 d2d_lp0_nr_yth[ISP_REG_TBL_LENGTH_32];
	HW_U16 d2d_lp1_nr_yth[ISP_REG_TBL_LENGTH_32];
	HW_U16 d2d_lp2_nr_yth[ISP_REG_TBL_LENGTH_32];
	HW_U16 d2d_nr_crth[ISP_REG_TBL_LENGTH_32];
	HW_U16 d2d_nr_cbth[ISP_REG_TBL_LENGTH_32];
	HW_U8 d2d_lp0_nr_ybk[ISP_REG_TBL_LENGTH_16];
	HW_U8 d2d_lp1_nr_ybk[ISP_REG_TBL_LENGTH_16];
	HW_U8 d2d_lp2_nr_ybk[ISP_REG_TBL_LENGTH_16];

	HW_U8 ext_block_d2d[ISP_D2D_EBDNR_SIZE];
};

struct isp_tdnf_config {
	HW_U8 mot_info_init_en;

	HW_U8 rec_en;
	HW_U8 d3d_mot_sel;
	HW_U8 flt_out_sel;
	HW_U8 blk_dnr_en;
	HW_U8 blk_dnr_sel;
	HW_U8 motion_en;
	HW_U8 texture_en;
	HW_U8 d3d_ctr_sel;
	HW_U8 d3d_mot_sens_ratio;
	HW_U8 d3d_out_sel;
	HW_U8 d3d_out_mode;
	HW_U16 nr_lm_amp;
	HW_U16 nr_lms_amp;
	HW_U8 cyc_dec_slp;
	HW_U8 stl_cyc_val;
	HW_U8 mot_cyc_val;
	HW_U8 diff_min_clp;
	HW_U16 flt1_thr_gain;
	HW_U16 rec_rto_clp;
	HW_U16 kb_wnum;
	HW_U16 kb_hnum;
	HW_U8 hf_cb_str;
	HW_U8 hf_cr_str;
	HW_U8 mf_cb_str;
	HW_U8 mf_cr_str;
	HW_U8 diff_intra_sens;
	HW_U8 diff_inter_sens;
	HW_U8 diff_intra_amp;
	HW_U8 diff_inter_amp;
	HW_U8 thr_intra_sens;
	HW_U8 thr_inter_sens;
	HW_U8 thr_intra_amp;
	HW_U8 thr_inter_amp;
	HW_U8 mv_k_min;
	HW_U8 mv_k_ratio;
	HW_U8 mv_r_min;
	HW_U8 mv_r_ratio;
	HW_U8 dtc_hf_cor;
	HW_U16 dtc_hf_blk_clp;
	HW_U16 dtc_hf_wht_clp;
	HW_U8 dtc_mf_cor;
	HW_U16 dtc_mf_blk_clp;
	HW_U16 dtc_mf_wht_clp;
	HW_U16 wdr_lm_max_clp;
	HW_U16 wdr_ms_max_clp;
	HW_U8 wdr_lm_hi_slp;
	HW_U8 wdr_ms_hi_slp;
	HW_U8 wdr_lm_lw_slp;
	HW_U8 wdr_ms_lw_slp;
	HW_U8 stl_stg_kth[8];
	HW_U8 stl_stg_cth[8];
	HW_U8 mot_stg_kth[8];
	HW_U8 mot_stg_cth[8];

	HW_U8 d2d0_cnr_bk[ISP_REG_TBL_LENGTH_16];
	HW_U8 sat_ctrl_bk[ISP_REG_TBL_LENGTH_16];
	HW_U8 ct_rt_bk[ISP_REG_TBL_LENGTH_16];
	HW_U8 k_mg_bk[ISP_REG_TBL_LENGTH_16];
	HW_U8 r_mg_bk[ISP_REG_TBL_LENGTH_16];
	HW_U8 df_shp_bk[ISP_REG_TBL_LENGTH_16];
	HW_U8 r_amp_bk[ISP_REG_TBL_LENGTH_16];
	HW_U8 k_dlt_bk[ISP_REG_TBL_LENGTH_16];
	HW_U8 lay0_d2d0_rt_br[ISP_REG_TBL_LENGTH_16];
	HW_U8 lay1_d2d0_rt_br[ISP_REG_TBL_LENGTH_16];
	HW_U8 lay0_nrd_rt_br[ISP_REG_TBL_LENGTH_16];
	HW_U8 lay1_nrd_rt_br[ISP_REG_TBL_LENGTH_16];
	HW_U16 dtc_hf_bk[ISP_REG_TBL_LENGTH_16];
	HW_U16 dtc_mf_bk[ISP_REG_TBL_LENGTH_16];
	HW_U8 dtc_hf_ba[ISP_REG_TBL_LENGTH_16];
	HW_U8 dtc_mf_ba[ISP_REG_TBL_LENGTH_16];
	HW_U16 flt0_thr_vc[ISP_REG_TBL_LENGTH_32];

	HW_U8 ext_block_d3d[ISP_D3D_EBDNR_SIZE];
};

struct isp_pltm_config {
	HW_U8 dsc_en;
	HW_U8 dcc_en;
	HW_U8 lft_en;
	HW_U8 gtm_en;
	HW_U8 cal_stg_en;
	HW_U8 lum_ratio;
	HW_U16 nrm_ratio;
	HW_U16 strength;

	HW_U16 sts_flt_stren[3];
	HW_U16 sts_ceil_slp;
	HW_U16 sts_floor_slp;
	HW_U8 sts_gd_ratio;
	HW_U8 mgc_smth;
	HW_U8 mgc_lum_adpt;
	HW_U8 adj1_asym_ratio;
	HW_U8 adjk_crct_ratio;

	HW_U32 gtm_ipoi[7];
	HW_U16 gtm_opoi[7];
	HW_U8 gtm_shift[7];

	HW_U16 dsc_lw_th;
	HW_U16 dsc_hi_th;
	HW_U8 dsc_shf_bit;
	HW_U8 dsc_lw_ratio;
	HW_U16 dsc_slp;
	HW_U16 dcc_lw_th;
	HW_U16 dcc_hi_th;
	HW_U8 dcc_shf_bit;
	HW_U8 dcc_lw_ratio;
	HW_U16 dcc_slp;

	HW_U8 stat_gd_cv[15];
	HW_U8 adj_k_df_cv[ISP_REG_TBL_LENGTH_33];

 	HW_U16 pltm_gtm_table[ISP_PLTM_GTM_TBL_SIZE];
	HW_U8 pltm_lm_table[ISP_PLTM_LM_TBL_SIZE];
};

struct isp_cfa_config {
	HW_U8 cfa_grad_th;
	HW_U16 cfa_dir_v_th;
	HW_U16 cfa_dir_h_th;
	HW_U8 afc_bayer_adjust_stren;
	HW_U8 afc_rgb_adjust_stren;
	HW_U8 afc_cnr_adjust_stren;
	HW_U8 afc_satu_gain;
	HW_U8 res_smth_high;
	HW_U8 res_smth_low;
	HW_U8 afc_cnr_stren;
	HW_U8 afc_rgb_stren;
	HW_U8 afc_bayer_stren;
	HW_U16 res_high_th;
	HW_U16 res_low_th;
	HW_U8 res_dir_a;
	HW_U8 res_dir_d;
	HW_U8 res_dir_v;
	HW_U8 res_dir_h;
};

struct isp_stat_config {
	HW_U8 stat_valid_block_w_num;
	HW_U8 stat_valid_block_h_num;
	HW_U16 stat_valid_block_width;
	HW_U16 stat_valid_block_height;
	HW_U16 stat_intp_w_step;
	HW_U16 stat_intp_h_step;
	HW_U16 stat_valid_block_num;
	HW_U32 stat_div_para;
	HW_U16 stat_last_block_w_start;
	HW_U16 stat_last_block_h_comp;
	HW_U8 stat_last_block_h_comp_line;
};

struct isp_sharp_config {
	HW_U8 txt_info_init_en;

	HW_U8 dir_hs_val_cv_en;
	HW_U8 dir_ms_val_cv_en;
	HW_U8 dir_ls_val_cv_en;
	HW_U8 dir_hs_lum_cv_en;
	HW_U8 dir_ms_lum_cv_en;
	HW_U8 dir_ls_lum_cv_en;
	HW_U8 ndir_hs_val_cv_en;
	HW_U8 ndir_ms_val_cv_en;
	HW_U8 ndir_ls_val_cv_en;
	HW_U8 ndir_hs_lum_cv_en;
	HW_U8 ndir_ms_lum_cv_en;
	HW_U8 ndir_ls_lum_cv_en;
	HW_U8 val_shift;
	HW_U8 out_sel;
	HW_U8 stat_src;
	HW_U8 txt_info_intp_en;
	HW_U8 mot_info_intp_en;
	HW_U8 stat_ratio;
	HW_U8 hs_aa_ratio;
	HW_U8 hs_at_ratio;
	HW_U16 hs_smth_ratio;
	HW_U8 hsv_satu_slope;
	HW_U16 wht_clip_ratio;
	HW_U16 blk_clip_ratio;
	HW_U8 mot_sens_ratio;

	HW_U16 dir_hs_dth_edge_th;
	HW_U16 dir_hs_dth_edge_nsr;
	HW_U16 dir_hs_dth_flat_th;
	HW_U16 dir_hs_dth_flat_nsr;
	HW_U16 dir_hs_dth_slope;
	HW_U8 dir_hs_vn_ratio;
	HW_U8 dir_hs_nms_ratio;
	HW_U16 dir_hs_wht_stren;
	HW_U16 dir_hs_blk_stren;
	HW_U16 dir_hs_wht_clip_ratio;
	HW_U16 dir_hs_blk_clip_ratio;
	HW_U8 dir_hs_nms_lw_clip;

	HW_U16 dir_ms_dth_edge_th;
	HW_U16 dir_ms_dth_edge_nsr;
	HW_U16 dir_ms_dth_flat_th;
	HW_U16 dir_ms_dth_flat_nsr;
	HW_U16 dir_ms_dth_slope;
	HW_U8 dir_ms_vn_ratio;
	HW_U8 dir_ms_nms_ratio;
	HW_U16 dir_ms_wht_stren;
	HW_U16 dir_ms_blk_stren;
	HW_U16 dir_ms_wht_clip_ratio;
	HW_U16 dir_ms_blk_clip_ratio;
	HW_U8 dir_ms_nms_lw_clip;

	HW_U16 dir_ls_dth_edge_th;
	HW_U16 dir_ls_dth_edge_nsr;
	HW_U16 dir_ls_dth_flat_th;
	HW_U16 dir_ls_dth_flat_nsr;
	HW_U16 dir_ls_dth_slope;
	HW_U8 dir_ls_vn_ratio;
	HW_U16 dir_ls_wht_stren;
	HW_U16 dir_ls_blk_stren;
	HW_U16 dir_ls_wht_clip_ratio;
	HW_U16 dir_ls_blk_clip_ratio;

	HW_U8 ndir_hs_edge_th;
	HW_U8 ndir_hs_edge_slope;
	HW_U8 ndir_hs_flat_th;
	HW_U8 ndir_hs_flat_slope;
	HW_U16 ndir_hs_wht_stren;
	HW_U16 ndir_hs_blk_stren;
	HW_U16 ndir_hs_wht_clip;
	HW_U16 ndir_hs_blk_clip;
	HW_U8 ndir_hs_mix_lw_clip;
	HW_U8 ndir_hs_mix_hi_clip;
	HW_U8 ndir_hs_vn_ratio;

	HW_U8 ndir_ms_edge_th;
	HW_U8 ndir_ms_edge_slope;
	HW_U8 ndir_ms_flat_th;
	HW_U8 ndir_ms_flat_slope;
	HW_U16 ndir_ms_wht_stren;
	HW_U16 ndir_ms_blk_stren;
	HW_U16 ndir_ms_wht_clip;
	HW_U16 ndir_ms_blk_clip;
	HW_U8 ndir_ms_mix_lw_clip;
	HW_U8 ndir_ms_mix_hi_clip;
	HW_U8 ndir_ms_vn_ratio;

	HW_U8 ndir_ls_edge_th;
	HW_U8 ndir_ls_edge_slope;
	HW_U8 ndir_ls_flat_th;
	HW_U8 ndir_ls_flat_slope;
	HW_U16 ndir_ls_wht_stren;
	HW_U16 ndir_ls_blk_stren;
	HW_U16 ndir_ls_wht_clip;
	HW_U16 ndir_ls_blk_clip;
	HW_U8 ndir_ls_mix_lw_clip;
	HW_U8 ndir_ls_mix_hi_clip;
	HW_U8 ndir_ls_vn_ratio;

	HW_U16 sharp_hs_value[ISP_REG_TBL_LENGTH_32];
	HW_U16 sharp_ms_value[ISP_REG_TBL_LENGTH_32];
	HW_U16 sharp_ls_value[ISP_REG_TBL_LENGTH_32];
	HW_U16 sharp_hs_lum[ISP_REG_TBL_LENGTH_32];
	HW_U16 sharp_ms_lum[ISP_REG_TBL_LENGTH_32];
	HW_U16 sharp_ls_lum[ISP_REG_TBL_LENGTH_32];
	HW_U16 sharp_hsv[46];
	HW_U16 sharp_gm_tbl[ISP_SHARP_GAMMA_TBL_LENGTH];
	HW_U16 sharp_invgm_tbl[ISP_SHARP_GAMMA_TBL_LENGTH];
	HW_U8 sharp_ratio_by_mot[ISP_SHARP_RT_TBL_SIZE];
	HW_U8 sharp_ratio_by_tex[ISP_SHARP_RT_TBL_SIZE];
};

struct encpp_top_config {
	HW_U8 ispbe_out_sel;
	HW_U8 texture_iir_en;
	HW_U8 texture_iir_stren;
	HW_U8 motion_iir_en;
	HW_U8 motion_iir_stren;
	HW_U8 sharp_en;
	HW_U8 ldci_en;
	HW_U8 mot_sens_ratio;
	HW_U8 cnr_ratio;

	HW_U16 gbl_satu_adj_lut[ISP_REG_TBL_LENGTH_16];
};

struct encpp_sharp_config {
	HW_U8 mot_info_intp_en;
	HW_U8 txt_info_intp_en;
	HW_U8 dir_hs_val_cv_en;
	HW_U8 dir_ms_val_cv_en;
	HW_U8 dir_hs_lum_cv_en;
	HW_U8 dir_ms_lum_cv_en;
	HW_U8 ndir_hs_val_cv_en;
	HW_U8 ndir_ms_val_cv_en;
	HW_U8 ndir_hs_lum_cv_en;
	HW_U8 ndir_ms_lum_cv_en;
	HW_U8 val_shift;
	HW_U8 out_sel;
	HW_U8 stat_src;
	HW_U8 hs_aa_ratio;
	HW_U8 hs_at_ratio;
	HW_U16 hs_smth_ratio;
	HW_U8 hsv_satu_slope;
	HW_U16 wht_clip_ratio;
	HW_U16 blk_clip_ratio;
	HW_U8 ss_map_stren;
	HW_U8 ls_fus_ratio;

	HW_U16 dir_hs_dth_edge_th;
	HW_U16 dir_hs_dth_edge_nsr;
	HW_U16 dir_hs_dth_flat_th;
	HW_U16 dir_hs_dth_flat_nsr;
	HW_U16 dir_hs_dth_slope;
	HW_U8 dir_hs_vn_ratio;
	HW_U8 dir_hs_nms_ratio;
	HW_U16 dir_hs_wht_stren;
	HW_U16 dir_hs_blk_stren;
	HW_U16 dir_hs_wht_clip_ratio;
	HW_U16 dir_hs_blk_clip_ratio;
	HW_U8 dir_hs_nms_lw_clip;

	HW_U16 dir_ms_dth_edge_th;
	HW_U16 dir_ms_dth_edge_nsr;
	HW_U16 dir_ms_dth_flat_th;
	HW_U16 dir_ms_dth_flat_nsr;
	HW_U16 dir_ms_dth_slope;
	HW_U8 dir_ms_vn_ratio;
	HW_U8 dir_ms_nms_ratio;
	HW_U16 dir_ms_wht_stren;
	HW_U16 dir_ms_blk_stren;
	HW_U16 dir_ms_wht_clip_ratio;
	HW_U16 dir_ms_blk_clip_ratio;
	HW_U8 dir_ms_nms_lw_clip;

	HW_U8 ndir_hs_edge_th;
	HW_U8 ndir_hs_edge_slope;
	HW_U8 ndir_hs_flat_th;
	HW_U8 ndir_hs_flat_slope;
	HW_U16 ndir_hs_wht_stren;
	HW_U16 ndir_hs_blk_stren;
	HW_U16 ndir_hs_wht_clip;
	HW_U16 ndir_hs_blk_clip;
	HW_U8 ndir_hs_mix_lw_clip;
	HW_U8 ndir_hs_mix_hi_clip;
	HW_U8 ndir_hs_vn_ratio;

	HW_U8 ndir_ms_edge_th;
	HW_U8 ndir_ms_edge_slope;
	HW_U8 ndir_ms_flat_th;
	HW_U8 ndir_ms_flat_slope;
	HW_U16 ndir_ms_wht_stren;
	HW_U16 ndir_ms_blk_stren;
	HW_U16 ndir_ms_wht_clip;
	HW_U16 ndir_ms_blk_clip;
	HW_U8 ndir_ms_mix_lw_clip;
	HW_U8 ndir_ms_mix_hi_clip;
	HW_U8 ndir_ms_vn_ratio;

	HW_U16 sharp_hs_value[ISP_REG_TBL_LENGTH_32];
	HW_U16 sharp_ms_value[ISP_REG_TBL_LENGTH_32];
	HW_U16 sharp_hs_lum[ISP_REG_TBL_LENGTH_32];
	HW_U16 sharp_ms_lum[ISP_REG_TBL_LENGTH_32];
	HW_U16 sharp_hsv[46];
	HW_U8 sharp_ls_map_lut[ISP_REG_TBL_LENGTH_32];
	HW_U8 sharp_texture_lut[ISP_REG_TBL_LENGTH_32];
	HW_U8 sharp_ratio_by_mot[ISP_SHARP_RT_TBL_SIZE];
	HW_U8 sharp_ratio_by_tex[ISP_SHARP_RT_TBL_SIZE];
};

struct encpp_ldci_config {
	HW_U8 ldci_mot0_en;
	HW_U8 ldci_mot1_en;
	HW_U8 ldci_txt_en;
	HW_U8 ldci_lum_diff_sup_en;
	HW_U8 ldci_mad_ratio;
	HW_U8 ldci_min_mad;
	HW_U8 ldci_up_slope_dark;
	HW_U8 ldci_up_slope_bright;
	HW_U8 ldci_dw_slope_dark;
	HW_U8 ldci_dw_slope_bright;
	HW_U8 ldci_eq_neg_enhance_stren;
	HW_U8 ldci_eq_pos_enhance_stren;
	HW_U8 ldci_eq_adj_ratio;
	HW_U16 ldci_strength;
	HW_U16 ldci_gain_lower;
	HW_U16 ldci_gain_upper;
	HW_U8 ldci_flt_ratio[6];
	HW_U8 ldci_stat_valid_block_w_num;
	HW_U8 ldci_stat_valid_block_h_num;

	HW_U8 ldci_txt_ratio_lut[ISP_REG_TBL_LENGTH_32];
	HW_U8 ldci_mot_ratio_lut[ISP_REG_TBL_LENGTH_32];
	HW_U8 ldci_lum_diff_lut[ISP_REG_TBL_LENGTH_32];
	HW_U8 ldci_map_pos_lut[ISP_REG_TBL_LENGTH_16];
	HW_U8 ldci_map_neg_lut[ISP_REG_TBL_LENGTH_16];
};

struct encoder_3dnr_config {
	unsigned char enable_3d_fliter;
	unsigned char adjust_pix_level_enable; // adjustment of coef pix level enable
	unsigned char smooth_filter_enable;    //* 3x3 smooth filter enable
	unsigned char max_pix_diff_th;         //* range[0~31]: maximum threshold of pixel difference
	unsigned char max_mad_th;              //* range[0~63]: maximum threshold of mad
	unsigned char max_mv_th;               //* range[0~63]: maximum threshold of motion vector
	unsigned char min_coef;                //* range[0~16]: minimum weight of 3d filter
	unsigned char max_coef;                //* range[0~16]: maximum weight of 3d filter,
};

struct encoder_2dnr_config {
	unsigned char enable_2d_fliter;
	unsigned char filter_strength_uv; //* range[0~255], 0 means close 2d filter, advice: 32
	unsigned char filter_strength_y;  //* range[0~255], 0 means close 2d filter, advice: 32
	unsigned char filter_th_uv;       //* range[0~15], advice: 2
	unsigned char filter_th_y;        //* range[0~15], advice: 2
};

struct enc_MovingLevelInfo {
	unsigned char is_overflow;
	unsigned short moving_level_table[ISP_D2D_EBDNR_SIZE];//32x24
};

struct enc_VencVe2IspParam {
	int d2d_level; //[1,1024], 256 means 1X
	int d3d_level; //[1,1024], 256 means 1X
	struct enc_MovingLevelInfo mMovingLevelInfo;
};

struct isp_h3a_coor_win {
	HW_S32 x1;
	HW_S32 y1;
	HW_S32 x2;
	HW_S32 y2;
};

struct npu_face_nr_config {
	unsigned char roi_num;
	struct isp_h3a_coor_win face_roi[20];
};

struct target_val {
	HW_S32 ae_forced;
	HW_S32 lum_forced;
};

struct isp_af_en_config {
	unsigned char af_iir0_en;
	unsigned char af_iir0_sec0_en;
	unsigned char af_iir0_sec1_en;
	unsigned char af_iir0_sec2_en;
	unsigned char af_iir0_ldg_en;
	unsigned char af_iir_ds_en;
	unsigned char af_offset_en;
	unsigned char af_peak_en;
	unsigned char af_squ_en;
};

struct isp_af_filter_config {
	short af_iir0_g0;
	short af_iir0_g1;
	short af_iir0_g2;
	short af_iir0_g3;
	short af_iir0_g4;
	short af_iir0_g5;
	unsigned short af_iir0_s0;
	unsigned short af_iir0_s1;
	unsigned short af_iir0_s2;
	unsigned short af_iir0_s3;
	unsigned char af_iir0_dilate;
	unsigned char af_iir0_ldg_lgain;
	unsigned char af_iir0_ldg_hgain;
	unsigned char af_iir0_ldg_lth;
	unsigned char af_iir0_ldg_hth;
	unsigned char af_iir0_ldg_lslope;
	unsigned char af_iir0_ldg_hslope;
	unsigned char af_iir0_core_th;
	unsigned char af_iir0_core_peak;
	unsigned char af_iir0_core_slope;
	unsigned char af_hlt_th;
	short af_r_offset;
	short af_gr_offset;
	short af_gb_offset;
	short af_b_offset;
};

struct isp_bayer_gain_offset {
	HW_U16 r_gain;
	HW_U16 gr_gain;
	HW_U16 gb_gain;
	HW_U16 b_gain;

	HW_S16 r_offset;
	HW_S16 gr_offset;
	HW_S16 gb_offset;
	HW_S16 b_offset;
};

struct isp_wb_gain {
	HW_U16 r_gain;
	HW_U16 gr_gain;
	HW_U16 gb_gain;
	HW_U16 b_gain;
};

/**
 * struct isp_rgb2rgb_gain_offset - RGB to RGB Blending
 * @matrix:
 *              [RR] [GR] [BR]
 *              [RG] [GG] [BG]
 *              [RB] [GB] [BB]
 * @offset: Blending offset value for R,G,B.
 */
struct isp_rgb2rgb_gain_offset {
	HW_S16 matrix[3][3];
	HW_S16 offset[3];
};

struct isp_rgb2yuv_gain_offset {
	HW_S16 matrix[3][3];
	HW_S16 offset[3];
};

struct isp_lsc_config {
	HW_U16 ct_x;
	HW_U16 ct_y;
	HW_U16 rs_val;
};

struct isp_disc_config {
	HW_U16 disc_ct_x;
	HW_U16 disc_ct_y;
	HW_U16 disc_rs_val;
};

struct isp_h3a_reg_win {
	HW_U8 hor_num;
	HW_U8 ver_num;
	HW_U16 hor_start;
	HW_U16 ver_start;
	HW_U16 width;
	HW_U16 height;
	HW_U8 shift_bit0;
	HW_U8 shift_bit2;
	HW_U8 shift_flag0;
};

typedef struct isp_sensor_info {
	/*frome sensor*/
	char *name;
	HW_U8 hflip;
	HW_U8 vflip;
	HW_U32 hts;
	HW_U32 vts;
	HW_U32 pclk;
	HW_U16 fps_fixed;
	HW_U32 bin_factor;
	HW_U32 gain_min;
	HW_U32 gain_max;
	HW_U32 exp_min;
	HW_U32 exp_max;
	HW_U32 exp_mid_min;
	HW_U32 exp_mid_max;
	HW_U32 exp_short_min;
	HW_U32 exp_short_max;
	HW_U16 width_overlayer;
	HW_S16 sensor_width;
	HW_S16 sensor_height;
	HW_U16 hoffset;
	HW_U16 voffset;
	HW_U8 input_seq;
	HW_U8 wdr_mode;
	HW_U8 color_space;
	HW_U8 bayer_bit;
	HW_S16 temperature;

	/*from ae*/
	HW_U32 exp_line;
	HW_U32 ang_gain;
	HW_U32 dig_gain;
	HW_U32 total_gain;

	HW_U32 ae_tbl_idx;
	HW_U32 ae_tbl_idx_max;

	HW_U16 fps;
	HW_U32 frame_time;
	HW_S32 ae_gain;
	HW_U8 is_ae_done;
	HW_U8 backlight;

	/*from motion detect*/
	HW_S32 motion_flag;

	/*awb*/
	HW_S32 ae_lv;
	struct isp_bayer_gain_offset gain_offset;

	/*from af*/
	HW_S32 is_af_busy;
} isp_sensor_info_t;

enum exposure_cfg_type {
	ANTI_EXP_WIN_OVER     = 0,
	ANTI_EXP_WIN_UNDER = 1,
	ANTI_EXP_HIST_OVER = 2,
	ANTI_EXP_HIST_UNDER = 3,

	AE_PREVIEW_SPEED = 4,
	AE_CAPTURE_SPEED = 5,
	AE_VIDEO_SPEED = 6,
	AE_TOUCH_SPEED = 7,
	AE_TOLERANCE = 8,
	AE_TARGET = 9,

	AE_HIST_DARK_WEIGHT_MIN = 10,
	AE_HIST_DARK_WEIGHT_MAX = 11,
	AE_HIST_BRIGHT_WEIGHT_MIN = 12,
	AE_HIST_BRIGHT_WEIGHT_MAX = 13,

	AE_WDR_RATIO_SPEED = 14,
	AE_FACE_TARGET = 15,
	AE_DYNAMIC_RESERVE_1 = 16,
	AE_DYNAMIC_RESERVE_2 = 17,
	AE_DYNAMIC_RESERVE_3 = 18,
	ISP_EXP_CFG_MAX,
};

enum wdr_cfg_type {
	WDR_CMP_LM_LTH = 0, //LM
	WDR_CMP_LM_HTH,
	WDR_SEXP_CHK_LM_LTH,
	WDR_SEXP_CHK_LM_HTH,
	WDR_LECC_JDG_LM_LTH,
	WDR_LECC_JDG_LM_HTH,
	WDR_LECC_CRC_LM_LTH,
	WDR_LECC_CRC_LM_RTH,
	WDR_DE_PURPL_LM_LTH,
	WDR_DE_PURPL_LM_LRT,
	WDR_MV_CHK_LM_LTH,
	WDR_MV_CHK_LM_HTH,
	WDR_MV_FCL_LM_LTH,
	WDR_MV_FCL_LM_HTH,

	WDR_CMP_MS_LTH, //MS
	WDR_CMP_MS_HTH,
	WDR_SEXP_CHK_MS_LTH,
	WDR_SEXP_CHK_MS_HTH,
	WDR_LECC_JDG_MS_LTH,
	WDR_LECC_JDG_MS_HTH,
	WDR_LECC_CRC_MS_LTH,
	WDR_LECC_CRC_MS_RTH,
	WDR_DE_PURPL_MS_LTH,
	WDR_DE_PURPL_MS_LRT,
	WDR_MV_CHK_MS_LTH,
	WDR_MV_CHK_MS_HTH,
	WDR_MV_FCL_MS_LTH,
	WDR_MV_FCL_MS_HTH,
	ISP_WDR_CFG_MAX,
};

enum wdr_output_mode {
	WDR_OUTPUT_STITCH = 0,
	WDR_OUTPUT_STITCH_LONG,
	WDR_OUTPUT_STITCH_MIDDLE,
	WDR_OUTPUT_STITCH_SHORT,
	WDR_OUTPUT_RESERVED,
	WDR_OUTPUT_LONG,
	WDR_OUTPUT_MIDDLE,
	WDR_OUTPUT_SHORT,
	ISP_WDR_OUTPUT_MODE_MAX,
};

enum wdr_split_cfg_type {
	WDR_SPLIT_INPUT_NRML = 0,
	WDR_SPLIT_INPUT_MODE,
	WDR_SPLIT_BLC_EN,
	WDR_SPLIT_DECOMP_INPUT_BIT,
	WDR_SPLIT_BITEXP_OUTPUT_BIT,
	WDR_SPLIT_DECOMP_ELM_RATIO,
	WDR_SPLIT_DECOMP_EMS_RATIO,
	WDR_SPLIT_DECOMP_RANGE0,
	WDR_SPLIT_DECOMP_RANGE1,
	WDR_SPLIT_DECOMP_RANGE2,
	WDR_SPLIT_DECOMP_RANGE3,
	WDR_SPLIT_DECOMP_RANGE4,
	WDR_SPLIT_DECOMP_SLOPE0,
	WDR_SPLIT_DECOMP_SLOPE1,
	WDR_SPLIT_DECOMP_SLOPE2,
	WDR_SPLIT_DECOMP_SLOPE3,
	WDR_SPLIT_DECOMP_SLOPE4,
	WDR_SPLIT_DECOMP_OFFSET0,
	WDR_SPLIT_DECOMP_OFFSET1 ,
	WDR_SPLIT_DECOMP_OFFSET2,
	WDR_SPLIT_DECOMP_OFFSET3,
	ISP_WDR_SPLIT_CFG_MAX,
};

enum wdr_comm_cfg_type {
	WDR_COMM_OUT_SEL = 0,
	WDR_COMM_MODE,
	WDR_COMM_LM_EXP_RATIO,
	WDR_COMM_MS_EXP_RATIO,
	WDR_COMM_LWB_NRATIO,
	WDR_COMM_SEXP_CHK_LM_EN,
	WDR_COMM_LECC_LM_EN,
	WDR_COMM_DE_PURPL_LM_EN,
	WDR_COMM_MV_CHK_LM_EN,
	WDR_COMM_SEXP_CHK_MS_EN,
	WDR_COMM_LECC_MS_EN,
	WDR_COMM_DE_PURPL_MS_EN,
	WDR_COMM_MV_CHK_MS_EN,
	ISP_WDR_COMM_CFG_MAX,
};

enum ae_table_mode {
	SCENE_MODE_PREVIEW = 0,
	SCENE_MODE_CAPTURE,
	SCENE_MODE_VIDEO,

	SCENE_MODE_BACKLIGHT,
	SCENE_MODE_BEACH_SNOW,
	SCENE_MODE_FIREWORKS,
	SCENE_MODE_LANDSCAPE,
	SCENE_MODE_NIGHT,
	SCENE_MODE_SPORTS,

	SCENE_MODE_USER_DEF0,
	SCENE_MODE_USER_DEF1,
	SCENE_MODE_USER_DEF2,
	SCENE_MODE_USER_DEF3,
	SCENE_MODE_USER_DEF4,
	SCENE_MODE_USER_DEF5,
	SCENE_MODE_SENSOR_DRIVER,

	SCENE_MODE_MAX,
};

enum temperture_comp_type {
	TEMP_COMP_2D_BLACK = 0,
	TEMP_COMP_2D_WHITE,
	TEMP_COMP_3D_BLACK,
	TEMP_COMP_3D_WHITE,
	TEMP_COMP_EDGE_NSR,
	TEMP_COMP_FLAT_NSR,
	TEMP_COMP_DTC_STREN,
	TEMP_COMP_BLC_R,
	TEMP_COMP_BLC_G,
	TEMP_COMP_BLC_B,
	TEMP_COMP_SHARP,
	TEMP_COMP_SATU_LOW,
	TEMP_COMP_SATU_MID,
	TEMP_COMP_SATU_HIGH,
	TEMP_COMP_MAX,
};

struct sensor_temp_info {
	HW_U8 enable;
	HW_S16 temperature_param[TEMP_COMP_MAX];
};

struct sensor_flip_info {
	HW_U8 enable;
	HW_U8 hflip;
	HW_U8 vflip;
};

struct ae_table {
	HW_U32 min_exp;  //us
	HW_U32 max_exp;
	HW_U32 min_gain;
	HW_U32 max_gain;
	HW_U32 min_iris;
	HW_U32 max_iris;
};

struct ae_table_info {
	struct ae_table ae_tbl[10];
	HW_S32 length;
	HW_S32 ev_step;
	HW_S32 shutter_shift;
};

struct isp_initial_status {
	HW_U8 wb_mode_en;
	HW_U8 wb_mgain_en;
	HW_U8 exp_mode_en;
	HW_U8 iso_mode_en;
	HW_U8 iso_sensitivity_en;
	HW_U8 exposure_metering_en;
	HW_U8 exp_compensation_en;
	HW_U8 exp_absolute_en;
	HW_U8 flicker_mode_en;
	HW_U8 brightness_level_en;
	HW_U8 contrast_level_en;
	HW_U8 saturation_level_en;
	HW_U8 sharpness_level_en;
	HW_U8 effect_en;
	HW_U8 ai_scene_en;
};

struct isp_initial_cfg {
	struct isp_initial_status enable;

	HW_U8 wb_mode;
	struct isp_wb_gain wb_gain_manual;
	HW_U8 exp_mode;
	HW_U8 iso_mode;
	HW_S32 iso_sensitivity;
	HW_U8 ae_metering_mode;
	HW_S32 exp_compensation;
	HW_U32 exp_absolute;
	HW_U8 flicker_mode;
	HW_S32 brightness_level;
	HW_S32 contrast_level;
	HW_S32 saturation_level;
	HW_S32 sharpness_level;
	HW_U8 effect;
	HW_U8 ai_scene;

	//ctx save init
	HW_U8 isp_ctx_save_init_flag;
	HW_U8 effect_hold_cnt;
};

enum stitch_mode_t {
	STITCH_NONE = 0,
	STITCH_2IN1_LINEAR,
	STITCH_MODE_MAX,
};

typedef enum isp_win_mode {
	WIN_FULL = 0,
	WIN_STITCH_LEFT = 1,
	WIN_STITCH_RIGHT = 2,
} isp_win_mode_t;

#endif //__BSP__ISP__COMM__H


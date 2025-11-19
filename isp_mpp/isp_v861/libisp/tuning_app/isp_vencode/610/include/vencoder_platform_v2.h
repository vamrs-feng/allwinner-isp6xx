/*
* Copyright (c) 2008-2016 Allwinner Technology Co. Ltd.
* All rights reserved.
*
* File : ve_interface_ext.h
* Description :
* History :
*   Author  : xyliu <xyliu@allwinnertech.com>
*   Date    : 2016/04/13
*   Comment :
*
*
*/


#ifndef _VENCODER_EXT_V2_H
#define _VENCODER_EXT_V2_H

#ifdef CONFIG_AW_VIDEO_KERNEL_ENC
#else
#include <stddef.h>
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define VCU_ONLINE_MODE 3

#define MAX_RC_GOP_SIZE                   256

#define JPEG_MAX_SEG_LEN (65523)
typedef struct VencBinImageParam {
	unsigned int enable;
	unsigned int moving_th;//range[1,31], 1:all frames are moving,
                           //            31:have no moving frame, default: 20
}VencBinImageParam;

typedef struct VencGetBinImageBufInfo {
	unsigned int   max_size;
	unsigned char* buf;
}VencGetBinImageBufInfo;

typedef struct VencGetMvInfoBufInfo {
	unsigned int   max_size;
	unsigned char* buf;
}VencGetMvInfoBufInfo;

typedef struct VencEnvLvRange {
    int env_lv_high_th;
    int env_lv_low_th;
    int env_lv_coef;  //range[0,15]
}VencEnvLvRange;

typedef union {
    unsigned char val;
    struct {
        unsigned char qp    : 6;
        unsigned char skip  : 1;
        unsigned char en    : 1;
    }reg;
}uMbQpMap;

typedef union {
    unsigned int val;
    uMbQpMap     mb[4];
}uCtuQpMap;

typedef struct {
    unsigned int  sad_th;
    unsigned int  sad_num;
    int           hor_expand;
    int           ver_expand;

    unsigned int  mse_th[4];
    int           mse_qp[5];
    int           max_mse_qp;
    int           min_mse_qp;

    float         force_qp_ratio_th0;
    float         force_qp_ratio_th1;
}sQpMapPara;

typedef struct {
    unsigned int is_move    : 1;
    unsigned int is_expand  : 1;
    unsigned int en_mad     : 1;
    unsigned int r0         : 5;
    unsigned int mad_val    : 8;
    unsigned int mse_val    : 16;
}sCtuQpInfo;

typedef struct {
    // all these average value is for mb16x16
    unsigned int avg_mad;
    unsigned int avg_sse;
    unsigned int avg_qp;
    double avg_psnr;
}VencMBSumInfo_V2;

typedef enum eWARPTYPE
{

    Warp_LDC,

    Warp_LDC_Pro,

    Warp_Pano180,

    Warp_Pano360,

    Warp_Normal,

    Warp_Fish2Wide,

    Warp_Perspective,

    Warp_BirdsEye,

    Warp_User,
    Warp_Zoom,
} eWarpType;

typedef struct {
	char  src_file[256];
	char  dst_file[256];
//Top
	int img_format;
	int yuv_dns_en;
	int frame_num;
	int input_width;
	int input_height;
	int output_width;
	int output_height;
	int bTop_en;
	int rotAngle;
	int bMirror;
	int bLBC_en;
    int lbc_scale_mode;  //0 USE SMALLER RATIO   1:use bigger ratio
	int bSC_en;
	int bCrop_en;
	int crop_x;
	int crop_y;
	int crop_width;
	int crop_height;
//GDC
	int bGDC_en;
	int bByPass;
	int warpMode;
	int mountMode;
	int calib_pic_w;
	int calib_pic_h;
	float fx;
	float fy;
	float cx;
	float cy;
	float fx_scale;
	float fy_scale;
	float cx_scale;
	float cy_scale;
	char path_lut_ldc_pro[256];
	int  eLensDistModel;
	float distCoef_wide_ra[3];
	float distCoef_wide_ta[2];
	float distCoef_fish_k[4];
	int centerOffsetX;
	int centerOffsetY;
	int rotateAngle;
	int radialDistortCoef;
	int trapezoidDistortCoef;
	int fanDistortCoef;
	int pan;
	int tilt;
	int zoomH;
	int zoomV;
	int scale;
	int innerRadius;
	float roll;
	float pitch;
	float yaw;
	int perspFunc;
	float perspectiveProjMat[9];
	char  birds_file[256];
	int birdsImg_width;
	int birdsImg_height;
	float mountHeight;
	float roiDist_ahead;
	float roiDist_left;
	float roiDist_right;
	float roiDist_bottom;
//Adscaler
	int peaking_en;
	int peaking_clamp;
	int peak_m;
	int th_strong_edge;
	int peak_weights_strength;

//debug
	int blk_format;//0=16x16,1=32x32,2=16x8,3=8x8
	//for user mode
	short *lut_x;
	short *lut_y;
}sInputPara;

typedef enum eMOUNTTYPE
{

	Mount_Top,

	Mount_Wall,

	Mount_Bottom
}eMountType;

typedef enum eLENSDISTMODEL
{
	DistModel_WideAngle,
	DistModel_FishEye
}eLensDistModel;

typedef enum  ePERSPFUNC
{
	Persp_Only,
	Persp_LDC
}ePerspFunc;

/* add define for v861-e214 */
#define VE_ISP_REG_TBL_LENGTH_33         33
#define VE_ISP_REG_TBL_LENGTH_32         32
#define VE_ISP_REG_TBL_LENGTH_17         17
#define VE_ISP_REG_TBL_LENGTH_16         16
#define VE_ISP_REG_LS_MAP_LUT_SIZE_46    46
#define VE_ISP_SHARP_RT_TBL_SIZE   128

typedef unsigned char           U8;
typedef unsigned short          U16;

typedef struct sEncppIspbeTopConfig {
	U8 ispbe_out_sel;
	U8 texture_iir_en;
	U8 texture_iir_stren;
	U8 motion_iir_en;
	U8 motion_iir_stren;
	U8 sharp_en;
	U8 ldci_en;
	U8 mot_sens_ratio;
	U8 cnr_ratio;

	U16 gbl_satu_adj_lut[VE_ISP_REG_TBL_LENGTH_16];
}sEncppIspbeTopConfig;


typedef struct sEncppIspbeSharpConfig {
	U8 mot_info_intp_en;
	U8 txt_info_intp_en;
	U8 dir_hs_val_cv_en;
	U8 dir_ms_val_cv_en;
	U8 dir_hs_lum_cv_en;
	U8 dir_ms_lum_cv_en;
	U8 ndir_hs_val_cv_en;
	U8 ndir_ms_val_cv_en;
	U8 ndir_hs_lum_cv_en;
	U8 ndir_ms_lum_cv_en;
	U8 val_shift;
	U8 out_sel;
	U8 stat_src;

	U8 hs_aa_ratio;
	U8 hs_at_ratio;
	U16 hs_smth_ratio;
	U8 hsv_satu_slope;

	U16 wht_clip_ratio;
	U16 blk_clip_ratio;

	U8 ss_map_stren;
	U8 ls_fus_ratio;

	U16 dir_hs_dth_edge_th;
	U16 dir_hs_dth_edge_nsr;

	U16 dir_hs_dth_flat_th;
	U16 dir_hs_dth_flat_nsr;

	U16 dir_hs_dth_slope;
	U8 dir_hs_vn_ratio;
	U8 dir_hs_nms_ratio;

	U16 dir_hs_wht_stren;
	U16 dir_hs_blk_stren;

	U16 dir_hs_wht_clip_ratio;
	U16 dir_hs_blk_clip_ratio;
	U8 dir_hs_nms_lw_clip;

	U16 dir_ms_dth_edge_th;
	U16 dir_ms_dth_edge_nsr;

	U16 dir_ms_dth_flat_th;
	U16 dir_ms_dth_flat_nsr;

	U16 dir_ms_dth_slope;
	U8 dir_ms_vn_ratio;
	U8 dir_ms_nms_ratio;

	U16 dir_ms_wht_stren;
	U16 dir_ms_blk_stren;

	U16 dir_ms_wht_clip_ratio;
	U16 dir_ms_blk_clip_ratio;
	U8 dir_ms_nms_lw_clip;

	U8 ndir_hs_edge_th;
	U8 ndir_hs_edge_slope;
	U8 ndir_hs_flat_th;
	U8 ndir_hs_flat_slope;

	U16 ndir_hs_wht_stren;
	U16 ndir_hs_blk_stren;

	U16 ndir_hs_wht_clip;
	U16 ndir_hs_blk_clip;

	U8 ndir_hs_mix_lw_clip;
	U8 ndir_hs_mix_hi_clip;
	U8 ndir_hs_vn_ratio;

	U8 ndir_ms_edge_th;
	U8 ndir_ms_edge_slope;
	U8 ndir_ms_flat_th;
	U8 ndir_ms_flat_slope;

	U16 ndir_ms_wht_stren;
	U16 ndir_ms_blk_stren;

	U16 ndir_ms_wht_clip;
	U16 ndir_ms_blk_clip;

	U8 ndir_ms_mix_lw_clip;
	U8 ndir_ms_mix_hi_clip;
	U8 ndir_ms_vn_ratio;

	U16 sharp_hs_value[VE_ISP_REG_TBL_LENGTH_32];
	U16 sharp_ms_value[VE_ISP_REG_TBL_LENGTH_32];
	U16 sharp_hs_lum[VE_ISP_REG_TBL_LENGTH_32];
	U16 sharp_ms_lum[VE_ISP_REG_TBL_LENGTH_32];
	U16 sharp_hsv[VE_ISP_REG_LS_MAP_LUT_SIZE_46];
	U8 sharp_ls_map_lut[VE_ISP_REG_TBL_LENGTH_32];
	U8 sharp_texture_lut[VE_ISP_REG_TBL_LENGTH_32];
	U8 sharp_ratio_by_mot[VE_ISP_SHARP_RT_TBL_SIZE];//* todo: save to dram buffer
	U8 sharp_ratio_by_tex[VE_ISP_SHARP_RT_TBL_SIZE];//* todo: save to dram buffer
}sEncppIspbeSharpConfig;

typedef struct sEncppIspbeLdciConfig {
	U8 ldci_mot0_en;
	U8 ldci_mot1_en;
	U8 ldci_txt_en;
	U8 ldci_lum_diff_sup_en;
	U8 ldci_mad_ratio;
	U8 ldci_min_mad;
	U8 ldci_up_slope_dark;
	U8 ldci_up_slope_bright;
	U8 ldci_dw_slope_dark;
	U8 ldci_dw_slope_bright;
	U8 ldci_eq_neg_enhance_stren;
	U8 ldci_eq_pos_enhance_stren;
	U8 ldci_eq_adj_ratio;
	U16 ldci_strength;
	U16 ldci_gain_lower;
	U16 ldci_gain_upper;
	U8 ldci_flt_ratio[6];
	U8 ldci_stat_valid_block_w_num; //* can write to reg, the REAL_W_NUM - 1
	U8 ldci_stat_valid_block_h_num; //* can write to reg, the REAL_H_NUM - 1

	U8 ldci_txt_ratio_lut[VE_ISP_REG_TBL_LENGTH_32];
	U8 ldci_mot_ratio_lut[VE_ISP_REG_TBL_LENGTH_32];
	U8 ldci_lum_diff_lut[VE_ISP_REG_TBL_LENGTH_32];
	U8 ldci_map_pos_lut[VE_ISP_REG_TBL_LENGTH_16];
	U8 ldci_map_neg_lut[VE_ISP_REG_TBL_LENGTH_16];
}sEncppIspbeLdciConfig;

typedef struct sIspbeParam {
	unsigned int mIspbeEnable;
	sEncppIspbeTopConfig mTopParam;
	sEncppIspbeSharpConfig mSharpParam;
	sEncppIspbeLdciConfig mLdciParam;
} sIspbeParam;
/* end of add define for v861-e214 */

typedef enum VENC_INDEXTYPE_PLATFORM_V2 {

    VENC_IndexParam_PlatformV2_Start = 0x3f000000,

    /**< reference type: VencMBSumInfo_V2 */
    VENC_IndexParamMBSumInfoOutput_V2,

    /**< reference type: unsigned int; 0: sp2305 1: c2398*/
    VENC_IndexParamSensorType,

    /**< reference type: VencBinImageParam */
    VENC_IndexParamEnableGetBinImage,

    /**< reference type: unsigned char* */
    VENC_IndexParamGetBinImageData,

    /**< reference type: unsigned int; 0: disable, 1: enable*/
    VENC_IndexParamEnableMvInfo,

    /**< reference type: unsigned char* */
    VENC_IndexParamGetMvInfoData,

    /**< reference type: unsigned int */
    VENC_IndexParamSetLVAdjTh,

    /**< reference type: VencEnvLvRange */
    VENC_IndexParamSetEnvLvTh,

    /**< reference type: VencVbrParam */
    VENC_IndexParamSetVbrParam,

    /**< reference type: Set or Get VencMotionSearchParam* */
    VENC_IndexParamMotionSearchParam,

    /**< reference type: Get VencMotionSearchRegin* */
    VENC_IndexParamMotionSearchResult,

    /**< reference type: TEST WB YUV* */
    VENC_IndexParamEnableWbYuv,

    /**< reference type: sGdcParam*/
    VENC_IndexParamGdcConfig,
    /**< reference type: sGdcParam*/
    VENC_IndexParamCropConfig,

    /**< reference type: unsinged int */
    VENC_IndexParamIspbeEn,

	/**< reference type: unsinged int */
	VENC_IndexParamIspbeEmbedEn,

    VENC_IndexParamIspbeTopConfig,

    VENC_IndexParamIspbeSharpConfig,

    VENC_IndexParamIspbeLdciConfig,

	/**< reference type: unsigned int; 0: have enought vbv buf, 1: vbv buf is full*/
	VENC_IndexParamBSbufIsFull,

	/**< reference type: int */
	VENC_IndexParamEnvLv,

	/**< reference type: int */
	VENC_IndexParamAeWeightLum,

	/**< reference type: eCameraStatus */
	VENC_IndexParamEnCameraMove,

	/**< reference type: sIspAeStatus */
	VENC_IndexParamIspAeStatus,

	/**< reference type: VencVe2IspParam */
	VENC_IndexParamVe2IspParam,

	/**< reference type: VencIspVeLinkParam*/
	VENC_IndexParamIspVeLinkParam, /*0x3F00001B*/

	/**< reference type: unsigned int; 0: disbale, 1: enable*/
	VENC_IndexParamEnableCheckOnlineStatus,

	/**< reference type: unsigned int; 0: not ready, 1: ready*/
	VENC_IndexParamCheckOnlineStatus,

    /**< reference type: int [0,1]*/
    /*every reg of frame start with 0xffffffff, and add some important info, such as:
      0xffffffff      0x00020001,          0x00010001       0x00000041
      startCode       channelId & bOnline  bkId & sensorId  frameCnt
    */
    VENC_IndexParamDebugSetupDumpRegInfo,

    /**< reference type: unsigned int* */
    VENC_IndexParamDebugGetRegInfoData,

	/**< reference type: int [0,1] */
	VENC_IndexParamEncAndDecCase, /*encoder and decoder run at the same time. need reset the whole ve*/

	/* set RecRef buf reduce function; type: int; 0: disbale, 1: enable*/
	VENC_IndexParamEnableRecRefBufReduceFunc,

	VENC_IndexParamCheckIsReadyToEncode,

	/**< reference type: unsigned int */
	/* not encode some frame, such as: not encode the begining 10 frames */
	VENC_IndexParamDropFrame,

	/**< reference type: VencAdvFgProject* */
	VENC_IndexParamAdvanceFgProject,

	/**< reference type: VencAdvCuPred* */
	VENC_IndexParamAdvanceCuPred,

	/**< reference type: VencAdvSkipBias* */
	VENC_IndexParamAdvanceSkipBias,

	/**< reference type: VencAdvHierarchicalQp* */
	VENC_IndexParamAdvanceHierarchicalQp,

	/**< reference type: VencAdvSvcParam* */
	VENC_IndexParamAdvanceSvcParam,

	/**< reference type: VencAdvDeblur* */
	VENC_IndexParamAdvanceDeblur,

}VENC_INDEXTYPE_PLATFORM_V2;

#ifdef __cplusplus
}
#endif

#endif


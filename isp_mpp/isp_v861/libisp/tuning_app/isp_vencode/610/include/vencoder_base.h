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
/* SPDX-License-Identifier: GPL-2.0-or-later WITH Linux-syscall-note */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */
/**
  This file is used to export some structs of vencoder to user space, mainly for rt_media.

  @author eric_wang
  @date 20241011
*/
#ifndef _VENCODER_BASE_H_
#define _VENCODER_BASE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define FACTOR_MAX_NUM 8

typedef struct VencRect {
	int nLeft;
	int nTop;
	int nWidth;
	int nHeight;
} VencRect;

typedef struct VencCropCfg {
	int      bEnable;
	VencRect Rect;
} VencCropCfg;

typedef enum E_ISP_SCALER_RATIO {
	VENC_ISP_SCALER_0		= 0, //no write back
	VENC_ISP_SCALER_EIGHTH	= 1, //scaler 1/8 write back
	VENC_ISP_SCALER_HALF	= 2, //scaler 1/2 write back
	VENC_ISP_SCALER_QUARTER = 3, //scaler 1/4 write back
} E_ISP_SCALER_RATIO;

typedef struct sWbYuvParam {
	unsigned int bEnableWbYuv;
	unsigned int nWbBufferNum;
	unsigned int bEnableCrop;
	VencRect     sWbYuvcrop;
	E_ISP_SCALER_RATIO scalerRatio;
} sWbYuvParam;

typedef struct {
	unsigned char ulargeFrameFlag;
	unsigned char useIntraRatioFlag;
	unsigned int ulargeFrameIdx;
	unsigned int uFrameRegionLevelNum[4];
} VencRegion3dResult;

typedef struct {
	//for region strategy
	unsigned int  uRegionWidth;                 // range[16~width], RegionWidth = regionHeightDiv16 << 4
	unsigned int  uRegionHeight;                // range[16~height], RegionHeight = regionHeightDiv16 << 4
	unsigned int  uRegionHorNum;                // range[1~16], RegionHorNum = width / RegionWidth
	unsigned int  uRegionVerNum;                // range[1~height/RegionHeight], RegionVerNum = height / RegionHeight
	unsigned int  uRegionTotalNum;              // range[1~], Total number of region area
	unsigned char e3dRegionEnable;              // range[0~1], region 3d enable
	unsigned char e3dRegionAutoMode;            // range[0~1], region auto mode
	unsigned char e3dRegionUpDownExpandEn;      // range[0~1], region 3d up and down area expand enable
	unsigned char e3dRegionLeftRightExpandEn;   // range[0~1], region 3d left and right area expand enable
	unsigned char e3dRegionParamEnable;         // range[0~1], 0: mv/avg/coef use e3dMoveStrengthMvTh/e3dAutoModeAvgTh/e3dAutoModeCoef
															// 1: mv/avg/coef use regionmvlevel select e3dMoveStrengthMvThLut/e3dMoveStrengthAvgThLut/e3dMoveStrengthCoefLut
	unsigned char histogramRegionMvLevelReadEn; // range[0~1], enable to read mv level of the region histogram
	unsigned char histogramRegionMvLevelWriteEn;// range[0~1], enable to write mv level of the region histogram
	unsigned char regionHeightDiv16;            // range[1~255], the height of the region histogram in mb size
	unsigned char regionWidthDiv16;             // range[1~255], the width of the region histogram in mb size
	unsigned char smallMvLevelMaxnum[2];        // range[0~3], the maximun number of small mv, [0]:hor,[1]:ver
	unsigned int  regionMvLevelRatioTh[3];      // range[0~256], move strength level threshold for region mv histogram statistics
												// 8bit decimal, equal to 256 means the integer 1
} VencRegion3dParam;

typedef struct Venc3dFilterParam{
	unsigned char e3dEn;                    // range[0~1], enc 3d total enable
	unsigned char e3dDefaultDis;            // range[0~1], 0:default parameters, 1:setting parameters
	unsigned char e3dLumaEn;                // range[0~1], 3d luma enable, only use for P frame (if Idr frame is incorrectly opened, it will not cause an exception, not valid)
	unsigned char e3dChromaEn;              // range[0~1], 3d chroma enable, v861 not support, default value 0
	unsigned char e3dMoveStatusEn;          // range[0~1], use move status enable
	unsigned char e3dPixDiffEn;             // range[0~1], adjustment of coef pix level enable
	unsigned char e3dCoefAutoMode;          // range[0~1], ref coef auto mode
	unsigned char e3dMaxCoef;               // range[0~16], maximum weight of ref block 3d filter
	unsigned char e3dMinCoef;               // range[0~16], minimum weight of ref block 3d filter
	unsigned char noiseModeEn;              // range[0~1], denoise mode enable, v861 not support, default value 0
	int           lambdaOffset;             // range[-8~7], lambda offset use for Ime search, v861 not support, default value 0
											// denoise mode: lambda = lambda + lambda_offset * noise_estimate_val
	unsigned char noiseEstVal;              // range[0~127], noise estimate value, v861 not support, default value 0
	unsigned char e3dStatusTh[3];           // range[0~3], move status threshold when e3dMoveStatusEn is 1
	unsigned char e3dMoveStrengthMvTh[3];   // range[0~255], move strength level mv threshold
	unsigned char e3dAutoModeAvgTh[10];     // range[0~255], residual avg threshold when e3dCoefAutoMode is 1
	unsigned char e3dAutoModeCoef[11];      // range[0~16], ref block coefficient when e3dCoefAutoMode is 1
	unsigned char e3dMoveStrengthMvThLut[9];   // range[0~255], move strength level mv threshold when e3dRegionParamEnable is 1
	unsigned char e3dMoveStrengthAvgLut[9];    // range[0~255], residual avg threshold when e3dRegionParamEnable is 1
	unsigned char e3dMoveStrengthCoefLut[9];   // range[0~16], ref block coefficient when e3dRegionParamEnable is 1

	VencRegion3dParam  sParam;
} Venc3dFilterParam;

typedef struct s2DfilterParam{
	unsigned char enable_2d_filter;
	unsigned char filter_strength_uv; //* range[0~255], 0 means close 2d filter, advice: 32
	unsigned char filter_strength_y;  //* range[0~255], 0 means close 2d filter, advice: 32
	unsigned char filter_th_uv;       //* range[0~15], advice: 2
	unsigned char filter_th_y;        //* range[0~15], advice: 2
} s2DfilterParam;

typedef struct {
	int en_d2d_limit;
	int d2d_level[6];
} VencVe2IspD2DLimit;

typedef struct {
	int dis_default_d2d;
	int d2d_min_lv_th;
	int d2d_max_lv_th;
	int d2d_min_lv_level;
	int d2d_max_lv_level;
	int dis_default_d3d;
	int d3d_min_lv_th;
	int d3d_max_lv_th;
	int d3d_min_lv_level;
	int d3d_max_lv_level;
} VencRotVe2Isp;

typedef struct {
	int dis_default_para;
	int mode;
	int en_gop_clip;
	float gop_bit_ratio_th[3];
	float coef_th[5][2];
} VencTargetBitsClipParam;

typedef enum  eGdcPerspFunc {
	Gdc_Persp_Only,
	Gdc_Persp_LDC
} eGdcPerspFunc;

typedef enum eGdcLensDistModel {
	Gdc_DistModel_WideAngle,
	Gdc_DistModel_FishEye
} eGdcLensDistModel;

typedef enum eGdcMountType {
	Gdc_Mount_Top,
	Gdc_Mount_Wall,
	Gdc_Mount_Bottom
} eGdcMountType;

typedef enum eGdcWarpType {
	Gdc_Warp_LDC,
	Gdc_Warp_LDC_Pro, //* new warp type
	Gdc_Warp_Pano180,
	Gdc_Warp_Pano360,
	Gdc_Warp_Normal,
	Gdc_Warp_Fish2Wide,
	Gdc_Warp_Perspective,
	Gdc_Warp_BirdsEye,
	Gdc_Warp_User,
	Gdc_Warp_Zoom,
} eGdcWarpType;

typedef enum {
	CAMERA_ADAPTIVE_STATIC = 0,
	CAMERA_FORCE_STATIC = 1,
	CAMERA_FORCE_MOVING = 2,
	CAMERA_ADAPTIVE_MOVING_AND_STATIC = 3,
	CAMERA_STATUS_NUM
} eCameraStatus;

typedef enum eRotationType {
	RotAngle_0 = 0x0,
	RotAngle_90,
	RotAngle_180,
	RotAngle_270,
} eRotationType;

typedef struct {
	unsigned char  bGDC_en;
	eGdcWarpType   eWarpMode;
	eGdcMountType  eMountMode;
	unsigned int *lut_data_buf;  //* just valid when eWarpMode is Gdc_Warp_LDC_Pro
	unsigned int   lut_data_size; //* just valid when eWarpMode is Gdc_Warp_LDC_Pro
	unsigned char  bMirror;
	unsigned int   calib_widht;
	unsigned int   calib_height;
	float fx;
	float fy;
	float cx;
	float cy;
	float fx_scale;
	float fy_scale;
	float cx_scale;
	float cy_scale;
	eGdcLensDistModel  eLensDistModel;
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
	eGdcPerspFunc  perspFunc;
	float perspectiveProjMat[9];
	int birdsImg_width;
	int birdsImg_height;
	float mountHeight;
	float roiDist_ahead;
	float roiDist_left;
	float roiDist_right;
	float roiDist_bottom;

	int peaking_en;
	int peaking_clamp;
	int peak_m;
	int th_strong_edge;
	int peak_weights_strength;
} sGdcParam;

#define REGIONLINK_REG_TBL_LENGTH 21

typedef struct sRegionLinkParamDynamic{
	unsigned short mad_cmp_th[3];                    // range[0~4095]
	unsigned short tex_mtb_max_val;                  // range[0~4095]
	unsigned short motion_mtb_max_val;               // range[0~4095]
	unsigned short motion_recover_berfore_i_max_val; // range[0~4095]
	unsigned short motion_recover_after_i_max_val;   // range[0~4095]

	unsigned short tex_mtb_curve[REGIONLINK_REG_TBL_LENGTH];    // range[0~4095]
	unsigned short motion_mtb_curve[REGIONLINK_REG_TBL_LENGTH]; // range[0~4095]
	unsigned char  stepX;                           // range[1, 16], use for motionsearch,enc3d,regionlink and jpeg
													// unit 16x16 for h264, unit 32x32 for h265, unit 1x1 for jpeg
	unsigned char  stepY;                           // range[1, 16], use for motionsearch,enc3d,regionlink and jpeg
													// unit 16x16 for h264, unit 32x32 for h265, unit 1x1 for jpeg
} sRegionLinkParamDynamic;

typedef struct sRegionLinkParamStatic{
	unsigned char link_print_en;
	unsigned char region_link_en;            // equal to mIspAndVeLinkageEnable
	unsigned char tex_detect_en;
	unsigned char motion_detect_en;
	unsigned char updateInterVal;            // range[0~10] default value is 0
	unsigned char regionLinkAdaptParamEn;
	unsigned char motion_hor_dir_expand_en;
	unsigned char motion_ver_dir_expand_en;
	unsigned char motion_dir_expand_adp_en;
	unsigned char motion_soft_th_en;
	unsigned char motion_recover_en;
	unsigned char motion_recover_grad_en;
	unsigned char temporal_w_i_en;
	unsigned char temporal_w_p_en;
	unsigned char tex_para_select_mode;        // 0:default, 1:define
	unsigned char motion_para_select_mode;     // 0:default, 1:define
	unsigned char tex_ratio_th[2];             // range[0~100]
	unsigned char motion_hor_l_expand_num;     // range[0~7]
	unsigned char motion_hor_r_expand_num;     // range[0~7]
	unsigned char motion_ver_u_expand_num;     // range[0~7]
	unsigned char motion_ver_d_expand_num;     // range[0~7]
	unsigned char motion_soft_ratio_th[2];     // range[0~100], [0]: motion soft low th, [1]: motion soft up th
	unsigned char motion_recover_speed;        // range[0~50]
	unsigned char motion_recover_before_i_num; // range[0~idrPeroid-1], idrPeroid-1 < 255
	unsigned char motion_recover_after_i_num;  // range[0~idrPeroid-1], idrPeroid-1 < 255
	unsigned char motion_recover_grad_ratio;   // range[0~100]
	unsigned short texture_weight[3];          // range[0~256], [0]: flat, [1]: normal, [2]: complex
	unsigned short cur_frame_ratio;            // range[0~256]
	unsigned short motion_largemv_th;
} sRegionLinkParamStatic;

typedef struct sRegionLinkParam{
	sRegionLinkParamDynamic mDynamicParam;
	sRegionLinkParamStatic  mStaticParam;
} sRegionLinkParam;

typedef enum VENC_CODING_MODE {
	VENC_FRAME_CODING         = 0,
	VENC_FIELD_CODING         = 1,
} VENC_CODING_MODE;

typedef enum VENC_CODEC_TYPE {
	VENC_CODEC_H264,
	VENC_CODEC_JPEG,
	VENC_CODEC_H264_VER2,
	VENC_CODEC_H265,
	VENC_CODEC_VP8,
	VENC_CODEC_CNT,
} VENC_CODEC_TYPE;

typedef enum VENC_PIXEL_FMT {
	VENC_PIXEL_YUV420SP,// NV12
	VENC_PIXEL_YVU420SP,// NV21
	VENC_PIXEL_YUV420P,
	VENC_PIXEL_YVU420P,
	//VENC_PIXEL_YUV422_BEGIN,
	VENC_PIXEL_YUV422SP,
	VENC_PIXEL_YVU422SP,
	VENC_PIXEL_YUV422P,
	VENC_PIXEL_YVU422P,
	VENC_PIXEL_YUYV422,
	VENC_PIXEL_UYVY422,
	VENC_PIXEL_YVYU422,
	VENC_PIXEL_VYUY422,
	//VENC_PIXEL_YUV422_END,
	VENC_PIXEL_ARGB,
	VENC_PIXEL_RGBA,
	VENC_PIXEL_ABGR,
	VENC_PIXEL_BGRA,
	VENC_PIXEL_TILE_32X32,
	VENC_PIXEL_TILE_128X32,
	VENC_PIXEL_AFBC_AW,
	VENC_PIXEL_LBC_AW, //* for v5v200 and newer ic
} VENC_PIXEL_FMT;

typedef enum VENC_OUTPUT_FMT {
	VENC_OUTPUT_SAME_AS_INPUT = 0,
	VENC_OUTPUT_YUV420,
	VENC_OUTPUT_YUV444,
	VENC_OUTPUT_YUV422,
} VENC_OUTPUT_FMT;

/**
 * H264 profile types
 */
typedef enum VENC_H264PROFILETYPE {
	VENC_H264ProfileBaseline  = 66,         /**< Baseline profile */
	VENC_H264ProfileMain      = 77,         /**< Main profile */
	VENC_H264ProfileHigh      = 100,           /**< High profile */
} VENC_H264PROFILETYPE;

/**
 * H264 level types
 */
typedef enum VENC_H264LEVELTYPE {
	VENC_H264Level1   = 10,     /**< Level 1 */
	VENC_H264Level11  = 11,     /**< Level 1.1 */
	VENC_H264Level12  = 12,     /**< Level 1.2 */
	VENC_H264Level13  = 13,     /**< Level 1.3 */
	VENC_H264Level2   = 20,     /**< Level 2 */
	VENC_H264Level21  = 21,     /**< Level 2.1 */
	VENC_H264Level22  = 22,     /**< Level 2.2 */
	VENC_H264Level3   = 30,     /**< Level 3 */
	VENC_H264Level31  = 31,     /**< Level 3.1 */
	VENC_H264Level32  = 32,     /**< Level 3.2 */
	VENC_H264Level4   = 40,     /**< Level 4 */
	VENC_H264Level41  = 41,     /**< Level 4.1 */
	VENC_H264Level42  = 42,     /**< Level 4.2 */
	VENC_H264Level5   = 50,     /**< Level 5 */
	VENC_H264Level51  = 51,     /**< Level 5.1 */
	VENC_H264Level52  = 52,     /**< Level 5.2 */
	VENC_H264LevelDefault = 0
} VENC_H264LEVELTYPE;

typedef struct VencH264ProfileLevel {
	VENC_H264PROFILETYPE    nProfile;
	VENC_H264LEVELTYPE        nLevel;
} VencH264ProfileLevel;

typedef struct VencQPRange {
	int    nMaxqp;
	int    nMinqp;

	//*just support VE_ENCODER_VERSION_2, please check the comment in base/include/CdcPlatformConfig.h
	int    nMaxPqp;
	int    nMinPqp;
	int    nQpInit;
	int    bEnMbQpLimit;
	//*end
} VencQPRange;

/* support 4 ROI region */
typedef struct VencROIConfig {
	int                    bEnable;
	int                    index; /* (0~7) */
	int                    nQPoffset;
	unsigned char          roi_abs_flag;
	VencRect               sRect;
} VencROIConfig;

typedef struct VencFixQP {
	int                     bEnable;
	int                     nIQp;
	int                     nPQp;
} VencFixQP;

typedef enum {
	AW_CBR = 0,
	AW_VBR = 1,
	AW_AVBR = 2,
	AW_QPMAP = 3,
	AW_FIXQP = 4,
	AW_ABR = 5,
	AW_CVBR = 6,
	AW_QVBR = 7,
} VENC_RC_MODE;

typedef enum  VENC_VIDEO_GOP_MODE {
	AW_NORMALP                    = 1,   //one p ref frame
	AW_ADVANCE_SINGLE             = 2,
	AW_DOUBLEP                    = 3,
	AW_SPECIAL_DOUBLE            = 4,
	AW_SPECIAL_SMARTP            = 5,   //double p ref frames and use virtual i frame,but virtual i ref virtual i
	AW_SMARTP                    = 6,   //double p ref frames and use virtual i frame
} VENC_VIDEO_GOP_MODE;

typedef enum {
	 VENC_H264_NALU_PSLICE = 1,                         /*PSLICE types*/
	 VENC_H264_NALU_ISLICE = 5,                         /*ISLICE types*/
	 VENC_H264_NALU_SEI    = 6,                         /*SEI types*/
	 VENC_H264_NALU_SPS    = 7,                         /*SPS types*/
	 VENC_H264_NALU_PPS    = 8,                         /*PPS types*/
	 VENC_H264_NALU_IPSLICE = 9,
	 VENC_H264_NALU_SVC    = 14,                        /*SVC Prefix types*/
} VENC_H264_NALU_TYPE;

typedef enum {
	 VENC_H265_NALU_PSLICE = 1,                         /*P SLICE types*/
	 VENC_H265_NALU_ISLICE = 19,                        /*I SLICE types*/
	 VENC_H265_NALU_VPS    = 32,                        /*VPS types*/
	 VENC_H265_NALU_SPS    = 33,                        /*SPS types*/
	 VENC_H265_NALU_PPS    = 34,                        /*PPS types*/
	 VENC_H265_NALU_SEI    = 39,                        /*SEI types*/
} VENC_H265_NALU_TYPE;

typedef enum {
	 VENC_JPEG_PACK_ECS = 5,                            /*ECS types*/
	 VENC_JPEG_PACK_APP = 6,                            /*APP types*/
	 VENC_JPEG_PACK_VDO = 7,                            /*VDO types*/
	 VENC_JPEG_PACK_PIC = 8,                            /*PIC types*/
} VENC_JPEGE_PACK_TYPE;

typedef union {
	VENC_H264_NALU_TYPE    eH264Type;               /*H264E NALU types*/
	VENC_JPEGE_PACK_TYPE   eJpegType;               /*JPEGE pack types*/
	VENC_H265_NALU_TYPE    eH265Type;               /*H264E NALU types*/
} VENC_OUTPUT_PACK_TYPE;

typedef struct {
	VENC_OUTPUT_PACK_TYPE  uType;
	unsigned int           nOffset;
	unsigned int           nLength;
} VencPackInfo;

#define MAX_OUTPUT_PACK_NUM (8)

typedef enum VENC_COLOR_SPACE {
	RESERVED0			= 0,
	VENC_BT709          = 1,  // include BT709-5, BT1361, IEC61966-2-1 IEC61966-2-4
	RESERVED1           = 2,
	RESERVED2           = 3,
	VENC_BT470          = 4,  // include BT470-6_SystemM,
	VENC_BT601          = 5,  // include BT470-6_SystemB, BT601-6_625, BT1358_625, BT1700_625
	VENC_SMPTE_170M     = 6,  // include SMPTE_170M, BT601-6_525, BT1358_525, BT1700_NTSC
	VENC_SMPTE_240M     = 7,  // include SMPTE_240M
	VENC_YCC            = 8,  // include GENERIC_FILM
	VENC_BT2020         = 9,  // include BT2020
	VENC_ST_428         = 10, // include SMPTE_428-1
	VENC_BT601_525      = 11, // bt601-525
} VENC_COLOR_SPACE;

typedef enum VENC_VIDEO_FORMAT {
	COMPONENT       = 0,                 /* component */
	PAL             = 1,                 /* pal*/
	NTSC            = 2,                 /* ntsc */
	SECAM           = 3,                /* secam  */
	MAC             = 4,                /* mac  */
	DEFAULT         = 5,                /* Unspecified video format  */
} VENC_VIDEO_FORMAT;

typedef enum VENC_INTRA_REFRESH_MODE {
	VENC_INTRA_REFRESH_ROW = 0,
	VENC_INTRA_REFRESH_COLUMN,
	VENC_INTRA_REFRESH_BUTT
} VENC_INTRA_REFRESH_MODE;

typedef struct VencJpegVideoSignal {
	VENC_COLOR_SPACE src_colour_primaries;
	VENC_COLOR_SPACE dst_colour_primaries;
} VencJpegVideoSignal;

typedef struct VencH264VideoSignal {
	VENC_VIDEO_FORMAT video_format;

	unsigned char full_range_flag;
	unsigned char transfer_characteristics;
	unsigned char matrix_coefficients;

	VENC_COLOR_SPACE src_colour_primaries;
	VENC_COLOR_SPACE dst_colour_primaries;
} VencH264VideoSignal;

typedef struct VencH264VideoTiming {
	  unsigned long num_units_in_tick;
	  unsigned long time_scale;
	  unsigned int fixed_frame_rate_flag;

} VencH264VideoTiming;

typedef struct VencCyclicIntraRefresh {
	int                     bEnable;
	int                     nBlockNumber;
	VENC_INTRA_REFRESH_MODE mode;
	unsigned int            ReqIQp;
} VencCyclicIntraRefresh;

typedef struct VencAdvancedRefParam {
	unsigned char              bAdvancedRefEn;   //advanced ref frame mode, 0:not use , 1:use
	unsigned int               nBase;       //base frame num
	unsigned int               nEnhance;    //enhance frame num
	unsigned char              bRefBaseEn;  //ctrl base frame ref base frame, 0:enable, 1:disable
} VencAdvancedRefParam;

typedef struct VencGopParam {
	unsigned char              bUseGopCtrlEn;   //use user set gop mode
	VENC_VIDEO_GOP_MODE        eGopMode;        //gop mode
	unsigned int               nVirtualIFrameInterval;
	unsigned int               nSpInterval;     //user set special p frame ref interval
	VencAdvancedRefParam       sRefParam;       //user set advanced ref frame mode
} VencGopParam;

typedef enum VENC_SUPERFRAME_MODE {
	VENC_SUPERFRAME_NONE,
	VENC_SUPERFRAME_DISCARD,
	VENC_SUPERFRAME_REENCODE,
} VENC_SUPERFRAME_MODE;

typedef enum VENC_SUPERFRAME_PRIORITY {
	VENC_SUPERF_RPQ_BALANCE = 0,
	VENC_SUPERF_BIT_RATE_FIRST,
	VENC_SUPERF_FRAME_BITS_FIRST,
	VENC_SUPERFE_BUTT,
} VENC_SUPERFRAME_PRIORITY;

typedef struct VencSuperFrameConfig {
	VENC_SUPERFRAME_MODE    eSuperFrameMode;
	unsigned int            nMaxIFrameBits;
	unsigned int            nMaxPFrameBits;
	unsigned int            nMaxBFrameBits;
	VENC_SUPERFRAME_PRIORITY eSuperPriority;
	int                     nMaxRencodeTimes;
	float                   nMaxP2IFrameBitsRatio;
} VencSuperFrameConfig;

typedef struct VencBitRateRange {
	int            bitRateMax;
	int            bitRateMin;
	float          fRangeRatioTh;
	int            nQualityTh;
	int            nQualityStep[2];
	int            nSubQualityDelay;
	int            nAddQualityDelay;
	int            nMinQuality;
	int            nMaxQuality;
} VencBitRateRange;

typedef struct VencH265TimingS {
	//0:stream without timing info; 1:stream with timing info
	unsigned char       timing_info_present_flag;
	unsigned int        num_units_in_tick;       //time_scale/frameRate
	unsigned int        time_scale;             //1second is  average divided by time_scale
	unsigned int        num_ticks_poc_diff_one; //num ticks of diff frame
} VencH265TimingS;

typedef enum VENC_OVERLAY_ARGB_TYPE {
	VENC_OVERLAY_ARGB_MIN    = -1,
	VENC_OVERLAY_ARGB8888    = 0,
	VENC_OVERLAY_ARGB4444   = 1,
	VENC_OVERLAY_ARGB1555   = 2,
	VENC_OVERLAY_ARGB_MAX    = 3,
} VENC_OVERLAY_ARGB_TYPE;

typedef enum VENC_OVERLAY_TYPE {
	NORMAL_OVERLAY          = 0,    //normal overlay
	COVER_OVERLAY           = 1,    //use the setting yuv to cover region
	LUMA_REVERSE_OVERLAY    = 2,    //normal overlay and luma reverse
} VENC_OVERLAY_TYPE;

typedef struct VencOverlayCoverYuvS {
	 unsigned char       use_cover_yuv_flag; //1:use the cover yuv; 0:transform the argb data to yuv ,then cover
	 unsigned char       cover_y; //the value of cover y
	 unsigned char       cover_u; //the value of cover u
	 unsigned char       cover_v; //the value of cover v
} VencOverlayCoverYuvS;

typedef struct {
	unsigned char                 reserve_zero : 2;
	unsigned char                 constraint_5 : 1;
	unsigned char                 constraint_4 : 1;
	unsigned char                 constraint_3 : 1;
	unsigned char                 constraint_2 : 1;
	unsigned char                 constraint_1 : 1;
	unsigned char                 constraint_0 : 1;
} VencH264ConstraintFlag;

typedef struct {
	unsigned int                  en_force_conf;
	unsigned int                  left_offset;
	unsigned int                  right_offset;
	unsigned int                  top_offset;
	unsigned int                  bottom_offset;
} VencForceConfWin;

typedef struct {
	unsigned char *pBuffer;
	unsigned int  nBufLen;
	unsigned int  nDataLen;
	unsigned int  nType;
} VencSeiData;

typedef struct {
	unsigned int nSeiNum;
	VencSeiData  *pSeiData;
} VencSeiParam;

typedef enum {
	BUF_IDLE,
	BUF_STANDBY,
	BUF_OCCUPY,
} VENC_BUF_STATUS;

typedef struct {
	unsigned char *pBuffer;
	unsigned int  nBufLen;
	unsigned int  nDataLen;
	unsigned int  nFrameRate;
	VENC_BUF_STATUS eStatus;
} VencInsertData;

typedef enum {
	PRODUCT_STATIC_IPC = 0,
	PRODUCT_MOVING_IPC = 1,
	PRODUCT_DOORBELL = 2,
	PRODUCT_CDR = 3,
	PRODUCT_SDV = 4,
	PRODUCT_PROJECTION = 5,
	PRODUCT_UAV = 6,       // Unmanned Aerial Vehicle
	PRODUCT_NUM,
} eVencProductMode;

typedef enum {
	VENC_H265ProfileMain        = 1,
	VENC_H265ProfileMain10      = 2,
	VENC_H265ProfileMainStill   = 3
} VENC_H265PROFILETYPE;

typedef enum {
	VENC_H265Level1   = 30,     /**< Level 1 */
	VENC_H265Level2  = 60,     /**< Level 2 */
	VENC_H265Level21  = 63,     /**< Level 2.1 */
	VENC_H265Level3  = 90,     /**< Level 3 */
	VENC_H265Level31   = 93,     /**< Level 3.1 */
	VENC_H265Level4  = 120,      /**< Level 4 */
	VENC_H265Level41  = 123,     /**< Level 4.1 */
	VENC_H265Level5  = 150,     /**< Level 5 */
	VENC_H265Level51   = 153,     /**< Level 5.1 */
	VENC_H265Level52  = 156,     /**< Level 5.2 */
	VENC_H265Level6  = 180,     /**< Level 6 */
	VENC_H265Level61   = 183,     /**< Level 6.1 */
	VENC_H265Level62  = 186,     /**< Level 6.2 */
	VENC_H265LevelDefault = 0
} VENC_H265LEVELTYPE;

typedef enum {
	VENC_ST_DIS_WDR      = 0,
	VENC_ST_EN_WDR       = 1,
	VENC_ST_NONE
} eSensorType;

typedef struct {
	VENC_H265PROFILETYPE    nProfile;
	VENC_H265LEVELTYPE        nLevel;
} VencH265ProfileLevel;

typedef struct {
	unsigned int            uMaxBitRate;
	unsigned int            nMovingTh;      //range[1,31], 1:all frames are moving,
										    //			  31:have no moving frame, default: 20
	int                     nQuality;       //range[1,20], 1:worst quality, 20:best quality

	//*just support VE_ENCODER_VERSION_2, please check the comment in base/include/CdcPlatformConfig.h
	int                     nIFrmBitsCoef;   //range[1, 20], 1:worst quality, 20:best quality
	int                     nPFrmBitsCoef;   //range[1, 50], 1:worst quality, 50:best quality
	//*end
} VencVbrParam;

// bNegQpEn == 0: MbQp = SliceQp + nDeltaQp;
// bNegQpEn == 1: MbQp = SliceQp - nDeltaQp;
typedef struct {
	unsigned char nDeltaQp         : 5;  // [04:00]
	unsigned char bNegQpEn         : 1;  // [05]
	unsigned char bSkipEn          : 1;  // [06]
	unsigned char bMapEn           : 1;  // [07]
} VencMbQpMapParcel;

typedef struct {
	VencMbQpMapParcel sMbMap[4];
} VencQpMapParcel;

typedef struct {
	unsigned int nBestMvComBias    : 6;  // [05:00]
	unsigned int bBestMvComEn      : 1;  // [06]
	unsigned int bSaoDis           : 1;  // [07]
	unsigned int nReserve_14_08    : 7;  // [14:08]
	unsigned int nInterBias        : 6;  // [20:15]
	unsigned int bInterBiasEn      : 1;  // [21]
	unsigned int nReserve_31_22    : 10; // [31:22]
} VencModeMapParcel;

typedef struct {
	unsigned int nInter16Factor    : 6;  // [05:00]
	unsigned int nInter32Factor    : 6;  // [11:06]
	unsigned int bInterFactorEn    : 1;  // [12]
	unsigned int nIntra8Factor     : 6;  // [18:13]
	unsigned int nIntra16Factor    : 6;  // [24:19]
	unsigned int nIntra32Factor    : 6;  // [30:25]
	unsigned int bIntraFactorEn    : 1;  // [31]
} VencSplitMapParcel;

typedef struct {
	unsigned int nFactor           : 8;  // [07:00]
	unsigned int nSaoFactor        : 8;  // [15:08]
	unsigned int nSqrtFactor       : 8;  // [23:16]
	unsigned int nImeFactor        : 8;  // [31:24]
} VencLambdaMapParcel;

typedef struct {
	// mode_ctrl_en & (0x01:QpMapEn | 0x02:ModeMapEn | 0x04:SplitMapEn | 0x08:LambdaMapEn)
	unsigned char mode_ctrl_en;
	unsigned char *p_info;

	//*just support VE_ENCODER_VERSION_2, please check the comment in base/include/CdcPlatformConfig.h
	unsigned int  last_slice_type;
	unsigned int  est_bit_rate;
	unsigned int  pre_est_bits;
	unsigned int  cur_est_bits;
	unsigned int  frm_mad;
	unsigned int  frm_mse;
	int           mad_mb_num;
	int           mse_mb_num;
	int           force_qp_num;
	int           en_chn_mse_qp;
	float         mad_qp_ratio;
	float         mse_qp_ratio;
	float         force_qp_ratio;
	sQpMapPara    qp_map_para;
	sCtuQpInfo    *p_ctu_info;
	//*end
} VencMBModeCtrl;

typedef struct {
	VENC_RC_MODE            eRcMode;
	unsigned char           bLowBitrateBeginFlag;
	unsigned char           bUseSetMadThrdFlag;
	unsigned char           uMadThrdI[12]; //range 0-255
	unsigned char           uMadThrdP[12]; //range 0-255
	unsigned char           uMadThrdB[12]; //no support
	unsigned int            uStatTime;      //range [1,10], default:1
	unsigned int            uMinIQp;
	int                     nMaxReEncodeTimes; //default use one time

	VencVbrParam            sVbrParam;      //valid only at AW_VBR/AW_AVBR
	VencFixQP               sFixQp;         //valid only at AW_FIXQP
	VencMBModeCtrl          sQpMap;         //valid only at AW_QPMAP

	unsigned int            uRowQpDelta; //no support
	unsigned int            uDirectionThrd; //no support
	unsigned int            uQpDeltaLevelI; //no support
	unsigned int            uQpDeltaLevelP; //no support
	unsigned int            uQpDeltaLevelB; //no support
	unsigned int            uInputFrmRate;  //no support
	unsigned int            uOutputFrmRate; //no support
	unsigned int            uFluctuateLevel;//no support
	unsigned int            uMinIprop;      //no support
	unsigned int            uMaxIprop;      //no support
} VencRcParam;

typedef struct VencH264Param {
	VencH264ProfileLevel    sProfileLevel;
	int                     bEntropyCodingCABAC; /* 0:CAVLC 1:CABAC*/
	VencQPRange               sQPRange;
	int                     nFramerate; /* fps*/
	int                     nSrcFramerate; /* fps*/
	int                     nBitrate;   /* bps*/
	int                     nMaxKeyInterval;
	VENC_CODING_MODE        nCodingMode;
	VencGopParam            sGopParam;
	VencRcParam             sRcParam;
} VencH264Param;

typedef struct {
	int                     idr_period;
	VencH265ProfileLevel    sProfileLevel;
	VencQPRange               sQPRange;
	int                     nFramerate; /* fps*/
	int                     nSrcFramerate; /* fps*/
	int                     nBitrate;   /* bps*/
	int                     nIntraPeriod;
	int                     nGopSize;
	int                     nQPInit; /* qp of first IDR_frame if use rate control */
	VencRcParam             sRcParam;
	VencGopParam            sGopParam;
} VencH265Param;

typedef struct {
	// all these average value is for mb16x16
	unsigned int avg_mad;
	unsigned int avg_sse;
	unsigned int avg_qp;
	double avg_psnr;
	unsigned char *p_mb_mad_qp_sse;
	unsigned char *p_mb_mv;
} VencMBSumInfo;

typedef struct {
	int pix_x_bgn;
	int pix_x_end;
	int pix_y_bgn;
	int pix_y_end;
	int thumb_x_bgn;
	int thumb_x_end;
	int thumb_y_bgn;
	int thumb_y_end;
	int thumb_pix_num;
	int total_num;
	int intra_num;
	int large_mv_num;
	int small_mv_num;
	int zero_mv_num;
	int large_mad_num;
	int is_motion;
} VencMotionSearchRegion;

typedef struct {
	int total_region_num;
	int motion_region_num;
	VencMotionSearchRegion *region;
} VencMotionSearchResult;

typedef struct {
	int en_motion_search;
	int update_interval;        // range[1, inf] frames, only update if(frame_idx % interval == 0)
	int dis_default_para;
	int hor_region_num;
	int ver_region_num;
	int en_check_mv;            // range[0, 1]
	int en_check_mad;           // range[0, 1]
	int en_morpholog;           // range[0, 1]
	int large_mv_th;            // range[0, 511]
	int large_mad_th;           // range[0, 255]
	int background_weight;      // range[0, 15]
	float large_mv_ratio_th;    // range[0, 100.0f] include intra and large mv
	float non_zero_mv_ratio_th; // range[0, 100.0f] include intra, large mv and samll mv
	float large_mad_ratio_th;   // range[0, 100.0f]
} VencMotionSearchParam;

#define DIR_MV_REGION_NUM 22

typedef struct {
	int mvX;
	int mvY;
} MvInfo;

typedef struct {
	int dir_mv_en;                  // range[0, 1], 0:disable, 1:enable, default value is 0
	int update_interval;            // range[0, 20], default value is 0
} VencDirMvParam;

typedef struct {
	MvInfo region_dir_mv[DIR_MV_REGION_NUM*DIR_MV_REGION_NUM];    // divide the entire frame into 22x22 regions,
									// and output the vertical and horizontal integer-pixel motion vector (MV) information with direction for each region.
	MvInfo line_abs_mv_sum[DIR_MV_REGION_NUM];         // The sum of absolute values of motion vectors in the horizontal direction for each of the 22 regions.
	MvInfo col_abs_mv_sum[DIR_MV_REGION_NUM];         // The sum of absolute values of motion vectors in the vertical direction for each of the 22 regions.
	MvInfo line_dir_mv_sum[DIR_MV_REGION_NUM];         // The sum of values of motion vectors in the horizontal direction for each of the 22 regions.
	MvInfo col_dir_mv_sum[DIR_MV_REGION_NUM];         // The sum of values of motion vectors in the vertical direction for each of the 22 regions.
	long long nCurFramePts;                           // Get the timestamp of the current frame
} VencDirMvInfoResult;

typedef void *VideoEncoder;



typedef struct InsideVbrKeyPar{
	unsigned int         uVbrOptEn;             // range[0, 1], follow the vbr(New) enable, internal automatic setting, use default
	unsigned int         uPrintVbrTraceInfoEn;  // range[0, 1], print vbr trace info enable, default value 0, use default
	unsigned int         uPrintLogInfoEn;       // range[0, 1], print vbr log enable, default value 0, use default
	int                  PrintRegInfoFrameNum;  // range[0~], print register value of a certain frame, use default
	int                  nIFrameRcInfoNum;      // range[1, 16], number of saved I-frame historical vbr info, use default
	int                  nPFrameRcInfoNum;      // range[1, 16], number of saved P-frame historical vbr info, use default
	int                  nSaveBitQpTh;          // range[minqp, maxqp], no more need to save bit allocation threshold, use default
	int                  nBoostBitQpTh;         // range[minqp, maxqp], no longer increase bit number allocation, use defalut
	int                  nBppLevelNum;          // range[1, 8], total number of bpp level, use default
	int                  nIPSliceQpMaxGap;      // range[1, 15], maximun interval of P-I frame sliceQp, the large the value, the worse the image quality stability
	int                  nMvStaLevelNum;        // range[1, 7], number of integer pixel mv statistical intervals, use default
	int                  nStaMvTh[FACTOR_MAX_NUM]; // range[1, 128], thresholds for each interval of integer pixel mv, use default
	int                  nAvgMvFactor;          // range[1,2^N], N<=10, mv mean precision, use default
	int                  nAvgQpRatio;           // range[0, 16], avgqp mean weight coefficient, use default
	int                  nDeltaQp;              // range[0, 10], the large the value, the worse the image quality stability, use default
	int                  nMaxHistoryFrameNum[2];// range[1, maxKeyI - 1], use default
	float                fInitAvgMovingLevel;   // range[0.0f, 0.5f], initial move level, the larger the value, the stronger the move, use defalut
	float                fAvgMoveLevelRatio;    // range[0.0f, 1.0f], AvgMoveLevel mean weight coefficient, use default
	float                fMinRatio[2];          // range[0.0f, 3.0f], fMinRatio[0]:use for I slice,fMinRatio[1]:use for P slice, use default
	float                fMaxRatio[2];          // range[0.0f, 3.0f], fMaxRatio[0]:use for I slice,fMaxRatio[1]:use for P slice, use default
	float                fMinRaioTh[2];         // range[0.0f, 3.0f], fMinRaioTh[0]:use for I slice,fMinRaioTh[1]:use for P slice, use default
	float                fMaxRatioTh[2];        // range[0.0f, 3.0f], fMaxRatioTh[0]:use for I slice,fMaxRatioTh[1]:use for P slice, use default
	float                fBppLevel[2][FACTOR_MAX_NUM];      // range[0.0f, 256.0f], bpp level threshold, use default
	float                fAdjustQpBppTh[2][FACTOR_MAX_NUM]; // range[0.0f, 1.0f], bpp threshold used for adjust sliceqp, use default
	float                fAdjustMaxQp[2][FACTOR_MAX_NUM];   // range[0.0f, 7.0f], adjust maximun of delta qp based on bpp level, use default
	float                fMoveFrameLevelTh;                 // range[0.0f, 0.5f], large motion scene threshold, use default
	float                fStaticFrameLevelTh;               // range[0.0f, 0.5f], static scene threshold, use default
	float                fluctuationFactorTh;               // range[1, 30], the large the value, the worse the image quality stability, default value 10
	unsigned char        uIframeMadThOpt[16];               // range[0, 255], adjust qp based on mad (I slice), ternal automatic setting, use default
	unsigned char        uPframeMadThOpt[16];               // range[0, 255], adjust qp based on mad (P slice), ternal automatic setting, use default
} InsideVbrKeyPar;

typedef struct InsideVbrMosAicOptPar{
	//mosaic opt param
	unsigned int         uConstantLargeMoveNumTh;   // range[2, maxKeyI - 1], continuous motion frame number threshold, use default
	unsigned int         uConstantStaticNumTh;      // range[1, maxKeyI - 1], continuous static frame number threshold, use default
	unsigned int         uMethodSelect;             // range[0, 3], default value 1
													// 0:constand move frame adjust sliceqp;
													// 1:constand move frame and MoveToStatic frame adjust slice qp
													// 2:adjust target bits
													// 3:no opeartion
	unsigned int         uAdjustSliceQpPeriod;      // range[1, maxKeyI - 1], slice Qp adjust period, use default
	unsigned int         uSliceQpLimitTh;           // range[minqp, maxqp], adjusrt sliceQp upper limit threshold, use default
	int                  nMosAicSliceDeltaQp;       // range[-10, 10], sliceQp adjustment range, the smaller the value, the bset the image quality, default value -6
	float                nScaleDeltaRatio;          // range[0.0f, 3.0f], scale ratio for bit, use default
	unsigned char        uCameraMoveMosaicEn;       // range[0, 1], used together with lens_moving_max_qp, defaule value is 0
} InsideVbrMosAicOptPar;

typedef enum VENC_RC_PRIORITY {
	VENC_RC_RPQ_BALANCE_Q = 0,       // balance bit rate and quality, slightly more focused on quality, default value
	VENC_RC_RPQ_BALANCE_R,           // balance bit rate and quality, slightly more focused on bit rate
	VENC_RC_AVERAGE_BIT_RATE_FIRST,  // Average bitrate is guaranteed first
	VENC_RC_RT_BIT_RATE_FIRST,       // Instantaneous bitrate is guaranteed first
	VENC_RC_BUTT,
} VENC_RC_PRIORITY;

typedef enum VENC_QUALITY_LEVEL {
	VENC_QUALITY_LOW_LEVEL = 0,		// use with VENC_RC_PRIORITY, low peak bitrate and quality, suitable for low bit rate application, default value
	VENC_QUALITY_MIDDLE_LEVEL,		// use with VENC_RC_PRIORITY, middle peak bitrate and quality
	VENC_QUALITY_HIGH_LEVEL,		// use with VENC_RC_PRIORITY, high peak bitrate and quality
	VENC_QUALITY_LEVEL_NUM,
} VENC_QUALITY_LEVEL;

typedef enum VENC_PARAM_MODE {
	VENC_PARAM_CLOSE = 0,
	VENC_PARAM_DEFINE,
	VENC_PARAM_ADAPTIVE,
	VENC_VENC_PARAM_MODE_NUM,
} VENC_PARAM_MODE;

typedef struct InsideVbrMoveToStaticPar{
	unsigned int         uConstandMoveToStaticNumTh;                // range[1, maxKeyI - 1], not use
	int                  nMoveToStaticSliceQpDelta[FACTOR_MAX_NUM]; // range[-10,10], adjustment range of sliceQp from different motion level to static scene, use default
																	// the smaller the value, the bset the image quality
	int                  nMoveToStaticDelayNum[4];                  // range[0, maxKeyI - 1], adjust the sliceQp period frame number for different motion level to statis scene, use default
	float                fFrameMvLevelTh[FACTOR_MAX_NUM];           // range[0.0f, 1.0f], motion level judgment threshold, use default
} InsideVbrMoveToStaticPar;

typedef struct InsideClipQpFunc{
	unsigned char closeMbRcEn;      // range[0, 1], when closeMbRcEn = 1, the best quality, default value 1
	unsigned char MoveStatusTh;     // range[0, 4], motion status threshold, use default
	unsigned int  MbQpTightLimitEn; // range[0, 1], enable macroblock qp narrowing adjustment amplitude, when MbQpTightLimitEn = 1, the best quality, default value 1
	int           uAddDeltaQp;      // range[0, 10], limit classify adjustment qp amplitude, the large the value, the best the image quality, use default
	unsigned int  uSliceQpMaxTh;    // range[minqp, maxqp], the smaller the value, the best the image quality, use default
} InsideClipQpFunc;

typedef struct InsideInstaneousBitRatePar{
	int           nFactorLevelNum;  // range[1, 8], the number of adjustment intervals, use default
	float         ExceedTarBrRatio; // range[0.1f, 3.0f], exceed max target bitrate*ExceedTarBrRatio need to save bits, use default
	float         SmallTarBrRatio;  // range[0.1f, 3.0f], increase bits if the intantenus bitrate is less than target bitrate*smallTarBrRatio, use default
	float         recodeExceedTarBrRatio; // range[0.1f, 3.0f], the smaller the value, the best the image quality, use default
	float         fgAdjustFactorTh[FACTOR_MAX_NUM]; // range[0.01f, 3.0f], InstaneousBitRate exceed ratio, use default
	float         fgAdjustFactor[FACTOR_MAX_NUM];   // range[0.01f, 1.0f], target bit adjust ratio, use default
	unsigned char  dynamic_frame_qp_en;             // range[0, 1], 0: no need, 1: dynamic modify qp base on real time rt, default value 0
	unsigned char  frame_qp_limit;                  // range[minqp, maxqp], default value 45
	unsigned char  clpParamMode;                    // range[0, 2], 0: use soft param calc, 1: use hard param calc, 2: close func, default value 0
	unsigned short clpStep;                         // range[4, 512], adjust sharp white and black clp, use default, vaild when clpParamMode = 1
	unsigned short clplimitLowTh;                   // range[1, 1023]
	float          clpRtlimitFactor[2];             // range[0.1, 5], vaild when clpParamMode = 0
} InsideInstaneousBitRatePar;

typedef struct InsideBreathFunc {
	unsigned char breathEn;        // range[0,1], 0: close breath effect optimize, 1:open (default)
	unsigned char updateParamMode; // range[0,3], 0: sliceQp update is last I, 1:sliceQp update is avg(default), 2: stable value, 3:define
	unsigned int  uIFrameSizeTh;   // range[5,bitrate*framerate/8*0.7], unit byte,need bitrate and framerate calc, use default
	int           sliceIIQpGap;    // range[0,5], the smaller the value, the best the image quality, instantaneous rate control will be incearse
	int           sliceIPQpGap;    // range[0,10], the smaller the value, the best the image quality, instantaneous rate control will be incearse
	int           rtBitrateFactor; // range[0,200], the larger the value, the best the image quality, instantaneous rate control will be incearse
	int           uAdaptUseFilterFactor;  // range[100,300], the larger the value, the best the image quality, instantaneous rate control will be incearse
	unsigned char uAdaptFilterEn;  // range[0,1], 0: close(default), 1:open
	unsigned char uDefineValue;    // range[minqp,maxqp]
	unsigned char uLimitQValue;    // range[minqp,maxqp]
	unsigned char uSpeed;          // range[0,100], the larger the value, adjust speed will be fast
	unsigned char uIPSliceClipEn;  // range[0,1], use for clip I and P sliceqp, defalue value 0
} InsideBreathFunc;

typedef struct InsideClassifyPar {
	unsigned int uParaUseMode; // range[0, 1], 0: close, 1: use define parameter 1: adaptive adjustment
	unsigned int uReverseParaTuningEn; //range [0, 1], 0: close, 1: open
	int deltaQp[6]; // range [-7, 7]
} InsideClassifyPar;

typedef struct InsideAdapQpLimit {
	VENC_PARAM_MODE uParaUseMode;           // range[0, 1], 0: close, 1: user define, 2: adaptive adjustment
	unsigned char increase_rt_slice_qp_low; // range[10, 51], default value 25, use for cbr, define when use_param_mode is 1 or 2
	unsigned char decrease_rt_slice_qp_up;  // range[increase_rt_slice_qp_low, 51], default value 40, define when use_param_mode is 1 or 2
	int rt_bitrate_factor[8];               // range[1, 300], define when uParaUseMode is 1 or 2
	int delta_qp[8];                        // range[-20, 20], default value 1, use for cbr, define when use_param_mode is 1 or 2
	int envlvTh;                            // range[10, 1000], default value 50
} InsideAdapQpLimit;

typedef struct InsideVbrOptPar{
	InsideVbrKeyPar            vbrKeyPar;
	InsideVbrMosAicOptPar      vbrMosAicOptPar;
	InsideVbrMoveToStaticPar   vbrMoveToStaticPar;
	InsideInstaneousBitRatePar vbrInstaneousBRPar;
	InsideClipQpFunc           mclipQpOpt;
	InsideBreathFunc           mBreathOpt;
	InsideClassifyPar          mClassifyPar;
	InsideAdapQpLimit          mAdapQpLimit;
} InsideVbrOptPar;

typedef struct VencVbrOptParam {
	int                  nIPratio;               // range[10, 100], the larger the value of nIPratio, the larger the size of IDR, use default
	int                  nIntraPeriodNumInVbv;   // range[1, 10], use default
	unsigned char        enable_instaneousBR;    // range[0, 1], Instantaneous rate control strategy enabled
	unsigned int         max_instaneousBR;       // range[104857, 104857600], unit bps
	unsigned int         peroid_instaneousBR;    // range[20, 120], as an integer multiple of tha frame rate, use default
	unsigned char        recodeIsliceQpEn;       // range[0, 1], modify I slice Qp enable
	unsigned int         uMosAicOptEn;           // range[0, 1], mosaic opt enable
	unsigned int         uSaveBitRateEn;         // range[0, 1], save bit rate enable
	unsigned int         uClassifyMadThAdjustEn; // range[0, 1], modify mad threshold enable, use default
	unsigned int         uMoveToStaticOptEn;     // range[0, 1], motion to still video quality improve enable
	InsideVbrOptPar      pVbrOptPar;
	VENC_RC_PRIORITY     sRcPriority;            // range[0, 3], rate control priority
	VENC_QUALITY_LEVEL   eQualityLevel;          // range[0, 2], quality level, the larger the value, the best the image quality
} VencVbrOptParam;

typedef struct VencSplitParam {
	unsigned char uMode; // range[0, 3], 0: default value, 1: user define, 2: adaptive mode PQ, 3: adaptive mode balance, default value 2
	unsigned short updateIntervel; // range[0, idrPeriod - 1], when uMode = 2
	unsigned char ImeResiSadDir;   // range[0, 1], 0: tend to small block, 1: tend to large block, defalut value 1
	unsigned char ImeResiSadMode;  // range[0, 1], 0: only first p after idr frame, 1: all p frame, defalut value 0
	// tend to small block
	// intra
	unsigned char bSCCSceneEn;              // range[0, 1]
	unsigned char bComplexTexEn;            // range[0, 1]
	unsigned char bIntraSplitSubFlagEnable[2]; // range[0, 1], 0: use for idr frame, 1: use for p frame
	unsigned char ImeResiSadAvgEn;          // range[0, 1]
	unsigned char IntraMinMaxNoedgeMagn[3]; // range[0, 127], 0:32x32, 1:16x16, 2:8x8
	unsigned char IntraMinMaxMagn[3];       // range[0,31], 0:32x32, 1:16x16, 2:8x8
	unsigned char IntraNoedgeMagn[3];       // range[0,31], 0:32x32, 1:16x16, 2:8x8
	// inter
	unsigned char bLastFrameIsPEn;    // range[0,1]
	unsigned char QsearchCoef;        // range[0,63], default 26
	unsigned char interScalerCoef[2]; // range[0,63], 0:32x32, 1:16x16, parcost * coef >> 3
	unsigned char ThMaxMvAbs;         // range[0,255]
	// texture
	unsigned char ThMadMin[3];    // range[0,31], 0:32x32, 1:16x16, 2:8x8
	unsigned char ThMadMax[3];    // range[0,63], 0:32x32, 1:16x16, 2:8x8
	unsigned char ThMadNoise[3];  // range[0,31], 0:32x32, 1:16x16, 2:8x8
	unsigned char ThCostNoise[3]; // range[0,127], 0:32x32, 1:16x16, 2:8x8

	// tend to large block
	// intra
	unsigned char IntraCoef[3];       // range[0,63], 0:32x32, 1:16x16, 2:8x8
	// inter
	unsigned char InterMinMaxMagn[2]; // range[0,31], 0:32x32, 1:16x16
	unsigned char InterCoef[2];       // range[0,63], 0:32x32, 1:16x16
	unsigned char ImeSadMaxMinMagn;   // range[0,63]
	unsigned char ThColMvAbs;         // range[0,63]
	unsigned char ThColMvAbsSmallMotion; // range[0,15]。
	unsigned char ThMinMvAbs;            // range[0,15]
	int ImeResiSadTh[2][6]; // range[0,127], [0][x]:32x32, [1][x]:16x16
	int DeltaCoef[2];                 // range[-8,7], 0:32x32, 1:16x16
	int ImeResiSadComplexDeltaTh[6];  // range[-15,0]
	int ImeResiSadNormalDeltaTh[6];   // range[-15,0]
	int FristPImeResiSadDeltaTh[2];   // range[-50,50], 0:32x32, 1:16x16, for first p after idr
	// texture
	unsigned char ThMadMagn[3];     // range[0,31], 0:32x32, 1:16x16, 2:8x8
	unsigned char ThMadTex[3];      // range[0,127], 0:32x32, 1:16x16, 2:8x8
	unsigned char ThMadPlat[3];     // range[0,31], 0:32x32, 1:16x16, 2:8x8
	unsigned char ThMagnNoise[3];   // range[0,15], 0:32x32, 1:16x16, 2:8x8
	unsigned char ThMagnAngle[3];   // range[0,15], 0:32x32, 1:16x16, 2:8x8
	unsigned char ThMadAngle[3];    // range[0,31], 0:32x32, 1:16x16, 2:8x8
	unsigned char TextureTypeTh[3]; // range[0,15]
} VencSplitParam;

typedef struct VencSaoParam {
	unsigned char		mode; // range[0, 1], 0: adaptive mode, 1: user define
	unsigned char		bSaoDenoiseEn; // range[0, 1]
	unsigned char		nFilStrMode[4]; // range[0, 9], 0:TexFil, 1:UncerFil, 2:NoiseFil, 3:MotionFil.
										// value=0: user define filter strength, 0~8: apply the default Gaussian filter, with strength varying from low to high. 9 : close filter;
	unsigned char		nTexFilStrTh[2]; // range[0, 63]
	unsigned char		nUncerFilStrTh[2]; // range[0, 63]
	unsigned char		nNoiseFilStrTh[2]; // range[0, 63]
	unsigned char		nMotionFilStrTh[2]; // range[0, 63]
	unsigned char		nSaoDenoiseBoundCopyType; // range[0, 1]
	unsigned char		bComplexTexJudgeEn; // range[0, 1]
	unsigned char		nSaoDenoiseUncerTexTh; // range[0, 15]
	unsigned char		bComplexJudgeUseNeighborEn; // range[0, 1]
	unsigned char		bComplexTexFilDis; // range[0, 1]
	unsigned char		bComplexTexSaoDis; // range[0, 1]
	unsigned char		nComplexTexMadth; // range[0, 255]
	unsigned char		bSaoDeMotionAreaFirstEn; // range[0, 1]
	unsigned char		nTexMadTh; // range[0, 255]
	unsigned char		nTexEdgeTh[4]; // range[0, 255]
	unsigned char		nUncerEdgeTh[4]; // range[0, 255]
	unsigned char		nNoiseEdgeTh[4]; // range[0, 255]
	unsigned char		nMotionEdgeTh[4]; // range[0, 255]
	unsigned int		nSaoDenoiseMotionRatio; // range[0, 255]
	unsigned int		nSaoDenoiseNoiseRatio; // range[0, 255]
	unsigned int		nSaoDenoiseUncerRatio; // range[0, 255]
} VencSaoParam;

typedef struct VencLambdaFactorParam {
	unsigned char	ctrlMode; // range[0, 1], 0: adaptive mode, 1: user define
	unsigned int	qSearchSqrtLambdaFactor;
	unsigned int	dSearchSqrtLambdaFactor;
	unsigned int	pSearchSqrtLambdaFactor;
	unsigned int	fmeSqrtLambdaFactor;
	unsigned int	iptitSqrtLambdaFactor;
	unsigned int	iptitLambdaFactor;
	unsigned int	saoLumaLambdaFactor;
	unsigned int	saoChromaLambdaFactor;
} VencLambdaFactorParam;

typedef struct VencPQLineRateCtrlParam {
	unsigned char		paramCtrlMode;	// range[0, 1], 0: adaptive mode, 1: user define
	unsigned char		lineRateCtrlEn; // range[0, 1]
	unsigned char		superFrameLRCtrlEn; // range[0, 1], Line rate control handling for extremely large frames
	unsigned char		superFrameLRDeltaQp[8]; // range[0, 31]
	unsigned char		superFrameBitsTimes[8]; // range[0, 31]
} VencPQLineRateCtrlParam;


typedef struct VencPQualityParam {
	VencSplitParam splitParam;
	VencSaoParam   saoParam;
	VencLambdaFactorParam lambdaFactorParam;
	VencPQLineRateCtrlParam lineRcParam;
} VencPQualityParam;


typedef struct {
	int is_static;
	VideoEncoder *pVideoEnc;
	VENC_CODEC_TYPE codecType;
	int parsingStatic;
	int parsingDynamic;
	int channnel_id;
	unsigned int        nInputWidth;
	unsigned int        nInputHeight;
	unsigned int        nDstWidth;
	unsigned int        nDstHeight;
	VENC_PIXEL_FMT      eInputFormat;
	VENC_OUTPUT_FMT     eOutputFormat;
	unsigned int        fps;
	VencQPRange qp_range;
	int bit_rate;
	VencH264Param       h264Param;
	unsigned int vbv_size;
	VencForceConfWin conf_win;
	int jpeg_quality;
	VencFixQP           fixQP;
	VencTargetBitsClipParam bits_clip_param;
	VencVbrParam            sVbrParam;
	s2DfilterParam m2DfilterParam;
	Venc3dFilterParam m3DfilterParam;
	int mb_rc_level;
	float        weak_text_th;
	VencH264VideoTiming mH264VideoTiming;
	VENC_COLOR_SPACE color_space;
	int rotate;
	int sharp_en;
	unsigned char isp2VeEn;
	unsigned char ve2IspEn;
	int profile;
	int level;
	int productMode;
	int online_en;
	int online_share_buf_num;
	int ve_rec_ref_buf_reduce_enable;
	int ve_ref_frame_lbc_mode;
	int chroma_qp_offset;
	int vbr_opt_en;
	int idr_period;
	VencVbrOptParam vbrOptParam;
	sRegionLinkParam vencRegionLink;
	VencSuperFrameConfig venSuperFrame;
	eCameraStatus mEnCameraMove;
	VencPQualityParam mPQualityParam;
} VencParamFromFiles;

typedef struct VencSetVbvBufInfo {
	int   nSetVbvBufEnable;
	int   nVbvBufSize;
	char *pVbvBuf;
	char *pVbvPhyBuf;
} VencSetVbvBufInfo;

#define VENC_TEXTURE_THRESHOLD_SIZE 16
#define VENC_MAX_HIERARCHY_NUM 4

typedef struct VencAdvFgProject {
	unsigned char uEnable; // range:[0, 1]
	unsigned int  mDirection;       // range:[0, 16]
	unsigned int  mGain;            // range:[0, 15]
	unsigned int  mOffset;          // range:[0, 255]
	unsigned int  mThresholdI[VENC_TEXTURE_THRESHOLD_SIZE]; // range:[0, 255]
	unsigned int  mthresholdP[VENC_TEXTURE_THRESHOLD_SIZE]; // range:[0, 255]
	unsigned int  mthresholdB[VENC_TEXTURE_THRESHOLD_SIZE]; // range:[0, 255]
} VencAdvFgProject;

typedef enum  {
	VENC_PRED_MODE_AUTO   = 0,
	VENC_PRED_MODE_MANUAL = 1,
	VENC_PRED_MODE_BUTT
} VENC_PRED_MODE;

typedef struct VencAdvCuPred {
	VENC_PRED_MODE pred_mode;
	unsigned int intra64_cost;
	unsigned int intra32_cost;
	unsigned int intra16_cost;
	unsigned int intra8_cost;
	unsigned int intra4_cost;
	unsigned int inter64_cost;
	unsigned int inter32_cost;
	unsigned int inter16_cost;
	unsigned int inter8_cost;
} VencAdvCuPred;

typedef struct VencAdvSkipBias {
	unsigned char enable;
	unsigned int  gain;
	unsigned int  offset;
	unsigned int  bg_cost;
	unsigned int  fg_cost;
} VencAdvSkipBias;

typedef struct VencAdvHierarchicalQp {
	unsigned char enable;
	int qp_delta[VENC_MAX_HIERARCHY_NUM];
	int frame_num[VENC_MAX_HIERARCHY_NUM];
} VencAdvHierarchicalQp;

typedef struct VencAdvSvcParam {
	unsigned int enable;
} VencAdvSvcParam;

typedef struct VencAdvDeblurParam {
	unsigned char deblur_en;
	unsigned char deblur_adaptive_en;
} VencAdvDeblurParam;

typedef struct VencAdvDeblurNearBg {
	unsigned int gain;
	unsigned int offset;
	int qp_delta;
	int min_qp;
	int max_qp;
} VencAdvDeblurNearBg;

typedef struct VencAdvDeblurFarBg {
	int qp_delta;
	int min_qp;
	int max_qp;
} VencAdvDeblurFarBg;

typedef struct VencAdvDeblur {
	VencAdvDeblurParam param;
	unsigned char near_bg_en;
	unsigned char far_bg_en;
	VencAdvDeblurNearBg near_bg;
	VencAdvDeblurFarBg far_bg;
} VencAdvDeblur;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* _VENCODER_BASE_H_ */

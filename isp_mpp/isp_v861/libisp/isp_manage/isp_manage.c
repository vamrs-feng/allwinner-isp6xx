/*
 ******************************************************************************
 *
 * isp_manage.c
 *
 * Hawkview ISP - isp_manage.c module
 *
 * Copyright (c) 2016 by Allwinnertech Co., Ltd.  http://www.allwinnertech.com
 *
 * Version		  Author         Date		    Description
 *
 *   3.0		  Yang Feng   	2016/06/06	VIDEO INPUT
 *
 *****************************************************************************
 */

#include "../include/isp_comm.h"
#include "../include/isp_module_cfg.h"
#include "../include/isp_manage.h"
#include "../include/isp_debug.h"
#include "../include/isp_base.h"
#include "../isp_math/isp_math_util.h"
#include "isp_otp_golden.h"

#if ISP_AI_SCENE_CONF
#include "../include/ai_scene_param.h"
#endif
unsigned int isp_lib_log_param = 0;//0xffffffff;

void isp_get_saved_regs(struct isp_lib_context *isp_gen)
{
	FUNCTION_LOG;
	//isp_gen->stat.min_rgb_saved = bsp_isp_get_saved_cfa_min_rgb();
	//isp_gen->stat.c_noise_saved = bsp_isp_get_saved_cnr_noise();
	FUNCTION_LOG;
}

void isp_rolloff_set_params_helper(isp_rolloff_entity_context_t *isp_rolloff_cxt, rolloff_param_type_t cmd_type)
{
	if (!isp_rolloff_cxt->rolloff_entity || !isp_rolloff_cxt->ops || !isp_rolloff_cxt->rolloff_param)
		return;

	isp_rolloff_cxt->rolloff_param->type = cmd_type;
	isp_rolloff_cxt->ops->isp_rolloff_set_params(isp_rolloff_cxt->rolloff_entity,
			isp_rolloff_cxt->rolloff_param, &isp_rolloff_cxt->rolloff_result);
}

void isp_afs_set_params_helper(isp_afs_entity_context_t *isp_afs_cxt, afs_param_type_t cmd_type)
{
	if (!isp_afs_cxt->afs_entity || !isp_afs_cxt->ops || !isp_afs_cxt->afs_param)
		return;

	isp_afs_cxt->afs_param->type = cmd_type;
	isp_afs_cxt->ops->isp_afs_set_params(isp_afs_cxt->afs_entity, isp_afs_cxt->afs_param, &isp_afs_cxt->afs_result);
}

void isp_iso_set_params_helper(isp_iso_entity_context_t *isp_iso_cxt, iso_param_type_t cmd_type)
{
	if (!isp_iso_cxt->iso_entity || !isp_iso_cxt->ops || !isp_iso_cxt->iso_param)
		return;

	isp_iso_cxt->iso_param->type = cmd_type;
	isp_iso_cxt->ops->isp_iso_set_params(isp_iso_cxt->iso_entity, isp_iso_cxt->iso_param, &isp_iso_cxt->iso_result);
}

void isp_md_set_params_helper(isp_md_entity_context_t *isp_md_cxt, md_param_type_t cmd_type)
{
	if (!isp_md_cxt->md_entity || !isp_md_cxt->ops || !isp_md_cxt->md_param)
		return;

	isp_md_cxt->md_param->type = cmd_type;
	isp_md_cxt->ops->isp_md_set_params(isp_md_cxt->md_entity, isp_md_cxt->md_param, &isp_md_cxt->md_result);
}

void isp_af_set_params_helper(isp_af_entity_context_t *isp_af_cxt, af_param_type_t cmd_type)
{
	if (!isp_af_cxt->af_entity || !isp_af_cxt->ops || !isp_af_cxt->af_param)
		return;

	isp_af_cxt->af_param->type = cmd_type;
	isp_af_cxt->ops->isp_af_set_params(isp_af_cxt->af_entity, isp_af_cxt->af_param, &isp_af_cxt->af_result);
}

void isp_awb_set_params_helper(isp_awb_entity_context_t *isp_awb_cxt, awb_param_type_t cmd_type)
{
	if (!isp_awb_cxt->awb_entity || !isp_awb_cxt->ops || !isp_awb_cxt->awb_param)
		return;

	isp_awb_cxt->awb_param->type = cmd_type;
	isp_awb_cxt->ops->isp_awb_set_params(isp_awb_cxt->awb_entity, isp_awb_cxt->awb_param, &isp_awb_cxt->awb_result);
}

void isp_ae_set_params_helper(isp_ae_entity_context_t *isp_ae_cxt, ae_param_type_t cmd_type)
{
	if (!isp_ae_cxt->ae_entity || !isp_ae_cxt->ops || !isp_ae_cxt->ae_param)
		return;

	isp_ae_cxt->ae_param->type = cmd_type;
	isp_ae_cxt->ops->isp_ae_set_params(isp_ae_cxt->ae_entity, isp_ae_cxt->ae_param, &isp_ae_cxt->ae_result);
}

void isp_gtm_set_params_helper(isp_gtm_entity_context_t *isp_gtm_cxt, gtm_param_type_t cmd_type)
{
	if (!isp_gtm_cxt->gtm_entity || !isp_gtm_cxt->ops || !isp_gtm_cxt->gtm_param)
		return;

	isp_gtm_cxt->gtm_param->type = cmd_type;
	isp_gtm_cxt->ops->isp_gtm_set_params(isp_gtm_cxt->gtm_entity, isp_gtm_cxt->gtm_param, &isp_gtm_cxt->gtm_result);
}

void isp_pltm_set_params_helper(isp_pltm_entity_context_t *isp_pltm_cxt, pltm_param_type_t cmd_type)
{
	if (!isp_pltm_cxt->pltm_entity || !isp_pltm_cxt->ops || !isp_pltm_cxt->pltm_param)
		return;

	isp_pltm_cxt->pltm_param->type = cmd_type;
	isp_pltm_cxt->ops->isp_pltm_set_params(isp_pltm_cxt->pltm_entity, isp_pltm_cxt->pltm_param, &isp_pltm_cxt->pltm_result);
}

void isp_ae_update_touch_cfg(struct isp_lib_context *isp_gen)
{
	static enum auto_focus_status af_status[5];
	static unsigned char cnt = 1;
	static unsigned char last_cnt = 0;
	unsigned char focus_change = 1;
	HW_U32 ae_gain = isp_gen->ae_entity_ctx.ae_result.ae_gain;
	unsigned char isp_ae_change_flags = 0;
	struct isp_d3d_k_stats_s *d3d_k_stats = &isp_gen->stats_ctx.stats.d3d_k_stats;
	HW_S16 af_stable_max = isp_gen->isp_ini_cfg.isp_3a_settings.af_stable_max;
	HW_S16 af_stable_min = isp_gen->isp_ini_cfg.isp_3a_settings.af_stable_min;
	HW_U32 i, j, mov_cnt = 0, mov = 0;
	unsigned char isp_mv_change_flags = 0;

	if (isp_gen->isp_ini_cfg.isp_test_settings.af_en == 1 && isp_gen->ae_settings.exp_metering_mode == AE_METERING_MODE_SPOT) {
		af_status[cnt] = isp_gen->af_entity_ctx.af_result.af_status_output;
		if (cnt == 0)
			last_cnt = 5 - 1;
		else
			last_cnt = cnt - 1;
		if (af_status[last_cnt] == AUTO_FOCUS_STATUS_REACHED && af_status[cnt] == AUTO_FOCUS_STATUS_BUSY)
			focus_change = 1;
		else
			focus_change = 0;
		cnt++;
		if (cnt == 5)
			cnt = 0;
		if (!focus_change)
			return;
	} else if (isp_gen->isp_ini_cfg.isp_test_settings.af_en == 0 && isp_gen->ae_settings.exp_metering_mode == AE_METERING_MODE_SPOT) {
		if (af_stable_max == 0 || af_stable_min == 0) {
			af_stable_max = 256 + 15;
			af_stable_min = 256 - 15;
		}
		if (ae_gain > af_stable_max || ae_gain < af_stable_min)
			isp_ae_change_flags = 1;
		else
			isp_ae_change_flags = 0;

		for (i = 0; i < ISP_D3D_K_ROW; i++) {
			for (j = 0; j < ISP_D3D_K_COL; j++) {
				mov_cnt += d3d_k_stats->k_stat[i][j];
			}
		}
		mov = 255 - (mov_cnt / (ISP_D3D_K_ROW * ISP_D3D_K_COL));
		if (mov > (isp_gen->isp_ini_cfg.isp_3a_settings.af_scene_motion_th * 3))
			isp_mv_change_flags = 1;
		else
			isp_mv_change_flags = 0;

		if (isp_mv_change_flags && !isp_ae_change_flags)
			ISP_PRINT("RESET TOUCH AE\n");
		else
			return;
	}

	if (isp_gen->ae_settings.exp_metering_mode == AE_METERING_MODE_SPOT) {
		isp_gen->ae_settings.exp_metering_mode = AE_METERING_MODE_MATRIX;
		isp_gen->ae_settings.ae_coor.x1 = H3A_PIC_OFFSET;
		isp_gen->ae_settings.ae_coor.y1 = H3A_PIC_OFFSET;
		isp_gen->ae_settings.ae_coor.x2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
		isp_gen->ae_settings.ae_coor.y2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
		isp_gen->ae_entity_ctx.ae_param->ae_setting = isp_gen->ae_settings;
		isp_ae_set_params_helper(&isp_gen->ae_entity_ctx, ISP_AE_BUILD_TOUCH_WEIGHT);
		//isp_gen->isp_3a_change_flags |= ISP_SET_AE_METERING_MODE;
		if (!isp_gen->ae_settings.exp_compensation) {
			isp_gen->pltm_entity_ctx.pltm_param->pltm_enable = 1;
			isp_gen->gtm_entity_ctx.gtm_param->gtm_enable = 1;
		}
	}
}

void isp_af_update_touch_cfg(struct isp_lib_context *isp_gen)
{
	static enum auto_focus_status af_status[5];
	static unsigned char cnt = 1;
	static unsigned char last_cnt = 0;
	unsigned char focus_change = 1;

	if (isp_gen->isp_ini_cfg.isp_test_settings.af_en == 1 && isp_gen->af_settings.af_mode == AUTO_FOCUS_TOUCH)  {
		af_status[cnt] = isp_gen->af_entity_ctx.af_result.af_status_output;
		if (cnt == 0)
			last_cnt = 5 - 1;
		else
			last_cnt = cnt - 1;
		if (af_status[last_cnt] == AUTO_FOCUS_STATUS_REACHED && af_status[cnt] == AUTO_FOCUS_STATUS_BUSY)
			focus_change = 1;
		else
			focus_change = 0;
		cnt++;
		if (cnt == 5)
			cnt = 0;
		if (!focus_change)
			return;
		else
			ISP_PRINT("RESET TOUCH AF\n");

	}

	if (isp_gen->af_settings.af_mode == AUTO_FOCUS_TOUCH) {
		isp_gen->af_settings.af_metering_mode = AUTO_FOCUS_METERING_CENTER_WEIGHTED;
		isp_gen->af_settings.af_mode = AUTO_FOCUS_CONTINUEOUS;
		isp_gen->af_settings.af_coor.x1 = H3A_PIC_OFFSET;
		isp_gen->af_settings.af_coor.y1 = H3A_PIC_OFFSET;
		isp_gen->af_settings.af_coor.x2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
		isp_gen->af_settings.af_coor.y2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
		isp_gen->af_entity_ctx.af_param->af_settings = isp_gen->af_settings;
		isp_af_set_params_helper(&isp_gen->af_entity_ctx, ISP_AF_BUILD_TOUCH_WEIGHT);
		//isp_gen->isp_3a_change_flags |= ISP_SET_AF_METERING_MODE;
	}
}

void __isp_iso_set_params(struct isp_lib_context *isp_gen)
{
	isp_gen->iso_entity_ctx.iso_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	isp_gen->iso_entity_ctx.iso_param->iso_frame_id = isp_gen->iso_frame_cnt;
}

void __isp_iso_run(struct isp_lib_context *isp_gen)
{
	isp_iso_entity_context_t *isp_iso_cxt = &isp_gen->iso_entity_ctx;

	if (isp_gen->stitch_mode == STITCH_2IN1_LINEAR && isp_gen->isp_id == 0) {
		return;
	}

	isp_iso_cxt->ops->isp_iso_run(isp_iso_cxt->iso_entity, &isp_iso_cxt->iso_result);
}

void __isp_rolloff_set_params(struct isp_lib_context *isp_gen)
{
	isp_gen->rolloff_entity_ctx.rolloff_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	isp_gen->rolloff_entity_ctx.rolloff_param->rolloff_frame_id = isp_gen->rolloff_frame_cnt;
	//rolloff_sensor_info.
	isp_gen->rolloff_entity_ctx.rolloff_param->rolloff_sensor_info = isp_gen->sensor_info;
	//rolloff lsc_cfg.
	isp_gen->rolloff_entity_ctx.rolloff_param->rolloff_ctrl = isp_gen->alsc_settings;
}

void __isp_rolloff_run(struct isp_lib_context *isp_gen)
{
	unsigned short *lens_tbl = (unsigned short *)isp_gen->module_cfg.lens_table;
	int i;
	isp_rolloff_entity_context_t *isp_rolloff_cxt = &isp_gen->rolloff_entity_ctx;

	isp_rolloff_cxt->ops->isp_rolloff_run(isp_rolloff_cxt->rolloff_entity,
		&isp_rolloff_cxt->rolloff_stats, &isp_rolloff_cxt->rolloff_result);
}

void __isp_afs_set_params(struct isp_lib_context *isp_gen)
{
	isp_gen->afs_entity_ctx.afs_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	isp_gen->afs_entity_ctx.afs_param->afs_frame_id = isp_gen->af_frame_cnt;
	isp_gen->afs_entity_ctx.afs_param->afs_sensor_info = isp_gen->sensor_info;
}

void __isp_afs_run(struct isp_lib_context *isp_gen)
{
	isp_afs_entity_context_t *isp_afs_cxt = &isp_gen->afs_entity_ctx;
	int ret = 0;

	if (isp_gen->ops->afs_done) {
		ret = isp_gen->ops->afs_done(isp_gen, &isp_afs_cxt->afs_result);
	}

	if (!ret) {
		isp_afs_cxt->ops->isp_afs_run(isp_afs_cxt->afs_entity, &isp_afs_cxt->afs_stats, &isp_afs_cxt->afs_result);
	}

	isp_gen->ae_settings.flicker_type = isp_afs_cxt->afs_result.flicker_type_output;
}

void __isp_md_set_params(struct isp_lib_context *isp_gen)
{
	isp_gen->md_entity_ctx.md_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	isp_gen->md_entity_ctx.md_param->md_frame_id = isp_gen->md_frame_cnt;
	isp_gen->sensor_info.is_af_busy = (isp_gen->af_entity_ctx.af_result.af_status_output ==	AUTO_FOCUS_STATUS_BUSY) ? 1 : 0;
	isp_gen->md_entity_ctx.md_param->md_sensor_info = isp_gen->sensor_info;
}

void __isp_md_run(struct isp_lib_context *isp_gen)
{
	isp_md_entity_context_t *isp_md_cxt = &isp_gen->md_entity_ctx;
	int ret = 0;

	if (isp_gen->ops->md_done) {
		ret = isp_gen->ops->md_done(isp_gen, &isp_md_cxt->md_result);
	}
	if (!ret) {
		isp_md_cxt->ops->isp_md_run(isp_md_cxt->md_entity,
				&isp_md_cxt->md_stats, &isp_md_cxt->md_result);
	}
	isp_gen->sensor_info.motion_flag = isp_md_cxt->md_result.motion_flag;
}

void __isp_af_set_params(struct isp_lib_context *isp_gen)
{
	struct isp_d3d_k_stats_s *d3d_k_stats = &isp_gen->stats_ctx.stats.d3d_k_stats;
	HW_U32 i, j, mov_cnt = 0;
	isp_gen->af_entity_ctx.af_param->af_frame_id = isp_gen->af_frame_cnt;
	isp_gen->af_entity_ctx.af_param->focus_absolute = isp_gen->af_settings.focus_absolute;
	isp_gen->af_entity_ctx.af_param->focus_relative = isp_gen->af_settings.focus_relative;
	isp_gen->af_entity_ctx.af_param->af_run_mode = isp_gen->af_settings.af_mode;
	isp_gen->af_entity_ctx.af_param->af_metering_mode = isp_gen->af_settings.af_metering_mode;
	isp_gen->af_entity_ctx.af_param->af_range = isp_gen->af_settings.af_range;
	isp_gen->af_entity_ctx.af_param->focus_lock = isp_gen->af_settings.focus_lock;
	isp_gen->af_entity_ctx.af_param->sensor_info =	isp_gen->sensor_info;

	for (i = 0; i < ISP_D3D_K_ROW; i++) {
		for (j = 0; j < ISP_D3D_K_COL; j++) {
			mov_cnt += d3d_k_stats->k_stat[i][j];
		}
	}
	isp_gen->af_entity_ctx.af_param->mov = 255 - (mov_cnt / (ISP_D3D_K_ROW * ISP_D3D_K_COL));
	isp_af_update_touch_cfg(isp_gen);
}

void __isp_af_run(struct isp_lib_context *isp_gen)
{
	isp_af_entity_context_t *isp_af_cxt = &isp_gen->af_entity_ctx;
	int ret = 0;

	if (isp_gen->ops->af_done) {
		ret = isp_gen->ops->af_done(isp_gen, &isp_af_cxt->af_result);
	}

	if (!ret) {
		isp_af_cxt->ops->isp_af_run(isp_af_cxt->af_entity,
				&isp_af_cxt->af_stats, &isp_af_cxt->af_result);
	}

	isp_gen->module_cfg.af_cfg.af_sap_lim = isp_af_cxt->af_result.af_sap_lim_output;
}

void __isp_awb_set_params(struct isp_lib_context *isp_gen)
{
	isp_gen->awb_entity_ctx.awb_param->awb_frame_id = isp_gen->awb_frame_cnt;
	isp_gen->awb_entity_ctx.awb_param->awb_ctrl = isp_gen->awb_settings;
	//sensor info.
	isp_gen->awb_entity_ctx.awb_param->awb_sensor_info = isp_gen->sensor_info;
}

#if 0
static void __awb_comp(struct isp_lib_context *isp_gen, awb_stats_t *stats, awb_result_t *result) {
	HW_U32 i = 0, j = 0, n = 0, avg_r, avg_g, avg_b, satu, max_rgb, min_rgb;
	HW_U32 rgain = 256, bgain = 256;
	HW_U32 rg_sum_0 = 0, bg_sum_0 = 0, rg_sum_1 = 0, bg_sum_1 = 0, cnt_0 = 0, cnt_1 = 0;
	HW_U16 rg_avg_0, bg_avg_0, rg_avg_1, bg_avg_1, rgain_comp = 0, bgain_comp = 0;
	static HW_U16 rgain_comp_cur = 256, bgain_comp_cur = 256;

	if (isp_gen->awb_frame_cnt < 30 && isp_gen->isp_id != 0)
		return;

	rgain = div_round(isp_gen->stats_ctx.wb_gain_saved.r_gain << 8, isp_gen->stats_ctx.wb_gain_saved.gr_gain);
	bgain = div_round(isp_gen->stats_ctx.wb_gain_saved.b_gain << 8, isp_gen->stats_ctx.wb_gain_saved.gr_gain);

	for (n = 0; n < ISP_AWB_ROW*ISP_AWB_COL; n++) {
		i = n / ISP_AWB_COL;
		j = n % ISP_AWB_COL;

		avg_r = stats->awb_stats->awb_avg_r[i][j] * rgain >> 8;
		avg_g = stats->awb_stats->awb_avg_g[i][j];
		avg_b = stats->awb_stats->awb_avg_b[i][j] * bgain >> 8;
		max_rgb = max(avg_r, max(avg_g, avg_b));
		min_rgb = min(avg_r, min(avg_g, avg_b));
		if (max_rgb)
			satu = (max_rgb - min_rgb) * 100 / max_rgb;
		else
			satu = 0;

		if (max_rgb > 40 && max_rgb < 100 && satu < 10) {
			if (j < ISP_AWB_COL/2) {
				rg_sum_0 += div_round(avg_r << 8, avg_g);
				bg_sum_0 += div_round(avg_b << 8, avg_g);
				cnt_0++;
			} else {
				rg_sum_1 += div_round(avg_r << 8, avg_g);
				bg_sum_1 += div_round(avg_b << 8, avg_g);
				cnt_1++;
			}
		}
	}

	if (cnt_0 >= 50 && cnt_1 >= 50) {
		rg_avg_0 = rg_sum_0 / cnt_0;
		bg_avg_0 = bg_sum_0 / cnt_0;
		rg_avg_1 = rg_sum_1 / cnt_1;
		bg_avg_1 = bg_sum_1 / cnt_1;

		rgain_comp = div_round(rg_avg_0 << 8, rg_avg_1);
		bgain_comp = div_round(bg_avg_0 << 8, bg_avg_1);

		if (rgain_comp_cur > rgain_comp)
			rgain_comp_cur -= min(rgain_comp_cur - rgain_comp, 2);
		else
			rgain_comp_cur += min(rgain_comp - rgain_comp_cur, 2);

		if (bgain_comp_cur > bgain_comp)
			bgain_comp_cur -= min(bgain_comp_cur - bgain_comp, 2);
		else
			bgain_comp_cur += min(bgain_comp - bgain_comp_cur, 2);
	}

	result->wb_gain_output.r_gain = result->wb_gain_output.r_gain * rgain_comp_cur >> 8;
	result->wb_gain_output.b_gain = result->wb_gain_output.b_gain * bgain_comp_cur >> 8;

	ISP_LIB_LOG(ISP_LOG_AWB, "isp%d: cnt: %d, %d ; comp: %d %d -> %d %d\n", isp_gen->isp_id, cnt_0, cnt_1, rgain_comp_cur, bgain_comp_cur, rgain_comp, bgain_comp);
}
#endif

void __isp_awb_run(struct isp_lib_context *isp_gen)
{
	isp_awb_entity_context_t *isp_awb_cxt = &isp_gen->awb_entity_ctx;
	struct isp_param_config *param = &isp_gen->isp_ini_cfg;
	struct isp_module_config *mod_cfg = &isp_gen->module_cfg;
	int ret = 0;

	if (isp_gen->ops->awb_done) {
		ret = isp_gen->ops->awb_done(isp_gen, &isp_awb_cxt->awb_result);
	}

	if (!ret) {
		isp_awb_cxt->ops->isp_awb_run(isp_awb_cxt->awb_entity, &isp_awb_cxt->awb_stats, &isp_awb_cxt->awb_result);
	} else {
		if (!isp_awb_cxt->awb_result.wb_gain_output.r_gain && !isp_awb_cxt->awb_result.wb_gain_output.gr_gain
			&& !isp_awb_cxt->awb_result.wb_gain_output.gb_gain && !isp_awb_cxt->awb_result.wb_gain_output.b_gain) {
			//Forced to do once awb
			isp_awb_cxt->ops->isp_awb_run(isp_awb_cxt->awb_entity, &isp_awb_cxt->awb_stats, &isp_awb_cxt->awb_result);
		}

		//awb dynamic compensation, use for two camera stitching camera
		//__awb_comp(isp_gen, &isp_awb_cxt->awb_stats, &isp_awb_cxt->awb_result);
	}

	if (isp_gen->isp_ini_cfg.isp_3a_settings.awb_ext_light_num == 1) {
		if (isp_gen->ops->awb_limit) {
			isp_gen->ops->awb_limit(isp_gen, &isp_awb_cxt->awb_result);
		}
	}

	if (param->isp_test_settings.nrp_en && mod_cfg->nrp_cfg.gamma_en &&
			!mod_cfg->nrp_cfg.inv_gamma_en && mod_cfg->mode_cfg.wb_sel) {
		isp_gen->module_cfg.wb_gain_cfg.wb_gain.r_gain = (HW_U16)(powf((float)isp_awb_cxt->awb_result.wb_gain_output.r_gain / 256.0, 1/1.3) * 256.0);
		isp_gen->module_cfg.wb_gain_cfg.wb_gain.gr_gain = (HW_U16)(powf((float)isp_awb_cxt->awb_result.wb_gain_output.gr_gain / 256.0, 1/1.3) * 256.0);
		isp_gen->module_cfg.wb_gain_cfg.wb_gain.gb_gain = (HW_U16)(powf((float)isp_awb_cxt->awb_result.wb_gain_output.gb_gain / 256.0, 1/1.3) * 256.0);
		isp_gen->module_cfg.wb_gain_cfg.wb_gain.b_gain = (HW_U16)(powf((float)isp_awb_cxt->awb_result.wb_gain_output.b_gain / 256.0, 1/1.3) * 256.0);
	} else {
		isp_gen->module_cfg.wb_gain_cfg.wb_gain = isp_awb_cxt->awb_result.wb_gain_output;
	}

	isp_gen->stats_ctx.wb_gain_saved = isp_awb_cxt->awb_result.wb_gain_output;
}

void __isp_ae_set_params(struct isp_lib_context *isp_gen)
{
	isp_gen->ae_entity_ctx.ae_param->ae_frame_id = isp_gen->ae_frame_cnt;
	isp_gen->ae_entity_ctx.ae_param->ae_isp_id = isp_gen->isp_id;
	isp_gen->ae_entity_ctx.ae_param->ae_setting = isp_gen->ae_settings;
	//ae_sensor_info.
	isp_gen->ae_entity_ctx.ae_param->ae_sensor_info = isp_gen->sensor_info;
	isp_gen->ae_entity_ctx.ae_param->ae_target_comp = 0;
	isp_ae_update_touch_cfg(isp_gen);
}

static void __isp_fpn_set_params(struct isp_lib_context *isp_gen)
{
	struct isp_param_config *param = &isp_gen->isp_ini_cfg;
	struct isp_module_config *mod_cfg = &isp_gen->module_cfg;
	int i;

	if (param->isp_tunning_settings.fpn_cfpn_lw_th > param->isp_tunning_settings.fpn_cfpn_hi_th)
		ISP_ERR("cfpn_lw_th > cfpn_hi_th, please check this value.\n");

	for (i = 0; i < ISP_REG_TBL_LENGTH_17; i++) {
		mod_cfg->fpn_cfg.fpn_cfpn_coeff_lut[i] = ValueInterp(isp_gen->ae_entity_ctx.ae_result.sensor_set.ev_set_curr.ev_total_gain,
			param->isp_tunning_settings.fpn_cfpn_lw_th, param->isp_tunning_settings.fpn_cfpn_hi_th,
			0, param->isp_tunning_settings.fpn_cfpn_coeff_lut[i]);
	}
}

#if ISP_AI_SCENE_CONF
void __isp_set_scene_param(struct isp_lib_context *isp_gen)
{
	if (isp_gen->ai_scene.scene_change_flag) {
		isp_gen->ai_scene.scene_frame_cnt++;
		if (isp_gen->ai_scene.cur_scene == BLUE_SKY) {
#ifdef AI_SCENE_SMOOTH
			isp_gen->ae_entity_ctx.ae_param->ae_setting.scene_mode = SCENE_MODE_PREVIEW;
			if (isp_gen->ai_scene.scene_frame_cnt <= blue_sky_tune_settings.isp_ai_smooth_frames) {
				isp_gen->tune.saturation_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, blue_sky_tune_settings.isp_ai_smooth_frames, last_tune_settings.saturation_level, blue_sky_tune_settings.saturation_level);
				isp_gen->tune.hue_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, blue_sky_tune_settings.isp_ai_smooth_frames, last_tune_settings.hue_level, blue_sky_tune_settings.hue_level);
				isp_gen->tune.contrast_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, blue_sky_tune_settings.isp_ai_smooth_frames, last_tune_settings.contrast_level, blue_sky_tune_settings.contrast_level);
				isp_gen->tune.sharpness_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, blue_sky_tune_settings.isp_ai_smooth_frames, last_tune_settings.sharpness_level, blue_sky_tune_settings.sharpness_level);
				isp_gen->tune.brightness_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, blue_sky_tune_settings.isp_ai_smooth_frames, last_tune_settings.brightness_level, blue_sky_tune_settings.brightness_level);
				isp_gen->tune.denoise_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, blue_sky_tune_settings.isp_ai_smooth_frames, last_tune_settings.denoise_level, blue_sky_tune_settings.denoise_level);
				isp_gen->tune.tdf_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, blue_sky_tune_settings.isp_ai_smooth_frames, last_tune_settings.tdf_level, blue_sky_tune_settings.tdf_level);
				isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, blue_sky_tune_settings.isp_ai_smooth_frames, last_tune_settings.r_gain, blue_sky_tune_settings.r_gain);
				isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, blue_sky_tune_settings.isp_ai_smooth_frames, last_tune_settings.b_gain, blue_sky_tune_settings.b_gain);
			}
			if (isp_gen->ai_scene.scene_frame_cnt == blue_sky_tune_settings.isp_ai_smooth_frames) {
				last_tune_settings.saturation_level = isp_gen->tune.saturation_level;
				last_tune_settings.hue_level = isp_gen->tune.hue_level;
				last_tune_settings.contrast_level = isp_gen->tune.contrast_level;
				last_tune_settings.sharpness_level = isp_gen->tune.sharpness_level;
				last_tune_settings.denoise_level = isp_gen->tune.denoise_level;
				last_tune_settings.brightness_level = isp_gen->tune.brightness_level;
				last_tune_settings.tdf_level = isp_gen->tune.tdf_level;
				last_tune_settings.r_gain = isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor;
				last_tune_settings.b_gain = isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor;
				// last_tune_settings.ae_table_night_length = blue_sky_tune_settings.ae_table_night_length;
				// memcpy(&last_tune_settings.ae_ai_night_table[0], &blue_sky_tune_settings.ae_ai_night_table[0], 42*sizeof(int));
				isp_gen->ai_scene.scene_change_flag = 0;
				isp_gen->ai_scene.scene_frame_cnt = 0;
			}
#else
			isp_gen->ae_entity_ctx.ae_param->ae_setting.scene_mode = SCENE_MODE_PREVIEW;
			isp_gen->tune.saturation_level = blue_sky_tune_settings.saturation_level;
			isp_gen->tune.hue_level = blue_sky_tune_settings.hue_level;
			isp_gen->tune.contrast_level = blue_sky_tune_settings.contrast_level;
			isp_gen->tune.sharpness_level = blue_sky_tune_settings.sharpness_level;
			isp_gen->tune.brightness_level = blue_sky_tune_settings.brightness_level;
			isp_gen->tune.denoise_level = blue_sky_tune_settings.denoise_level;
			isp_gen->tune.tdf_level = blue_sky_tune_settings.tdf_level;
			isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor = blue_sky_tune_settings.r_gain;
			isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor = blue_sky_tune_settings.b_gain;
			isp_gen->ai_scene.scene_change_flag = 0;
			isp_gen->ai_scene.scene_frame_cnt = 0;
#endif
		}

		if (isp_gen->ai_scene.cur_scene == NIGHT_VIEW) {
#ifdef AI_SCENE_SMOOTH
			if (isp_gen->ai_scene.scene_frame_cnt == 1) {
				isp_gen->ae_entity_ctx.ae_param->ae_setting.scene_mode = SCENE_MODE_CAPTURE;
				isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].length = night_view_tune_settings.ae_table_night_length;
				memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].ae_tbl[0],
					&night_view_tune_settings.ae_ai_night_table[0], 42*sizeof(int));
				isp_ae_set_params_helper(&isp_gen->ae_entity_ctx, ISP_AE_UPDATE_AE_TABLE);
			}
			if (isp_gen->ai_scene.scene_frame_cnt <= night_view_tune_settings.isp_ai_smooth_frames) {
				isp_gen->tune.saturation_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, night_view_tune_settings.isp_ai_smooth_frames, last_tune_settings.saturation_level, night_view_tune_settings.saturation_level);
				isp_gen->tune.hue_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, night_view_tune_settings.isp_ai_smooth_frames, last_tune_settings.hue_level, night_view_tune_settings.hue_level);
				isp_gen->tune.contrast_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, night_view_tune_settings.isp_ai_smooth_frames, last_tune_settings.contrast_level, night_view_tune_settings.contrast_level);
				isp_gen->tune.sharpness_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, night_view_tune_settings.isp_ai_smooth_frames, last_tune_settings.sharpness_level, night_view_tune_settings.sharpness_level);
				isp_gen->tune.brightness_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, night_view_tune_settings.isp_ai_smooth_frames, last_tune_settings.brightness_level, night_view_tune_settings.brightness_level);
				isp_gen->tune.denoise_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, night_view_tune_settings.isp_ai_smooth_frames, last_tune_settings.denoise_level, night_view_tune_settings.denoise_level);
				isp_gen->tune.tdf_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, night_view_tune_settings.isp_ai_smooth_frames, last_tune_settings.tdf_level, night_view_tune_settings.tdf_level);
				isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, night_view_tune_settings.isp_ai_smooth_frames, last_tune_settings.r_gain, night_view_tune_settings.r_gain);
				isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, night_view_tune_settings.isp_ai_smooth_frames, last_tune_settings.b_gain, night_view_tune_settings.b_gain);
			}
			if (isp_gen->ai_scene.scene_frame_cnt == night_view_tune_settings.isp_ai_smooth_frames) {
				last_tune_settings.saturation_level = isp_gen->tune.saturation_level;
				last_tune_settings.hue_level = isp_gen->tune.hue_level;
				last_tune_settings.contrast_level = isp_gen->tune.contrast_level;
				last_tune_settings.sharpness_level = isp_gen->tune.sharpness_level;
				last_tune_settings.denoise_level = isp_gen->tune.denoise_level;
				last_tune_settings.brightness_level = isp_gen->tune.brightness_level;
				last_tune_settings.tdf_level = isp_gen->tune.tdf_level;
				last_tune_settings.r_gain = isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor;
				last_tune_settings.b_gain = isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor;
				last_tune_settings.ae_table_night_length =
					night_view_tune_settings.ae_table_night_length;
				memcpy(&last_tune_settings.ae_ai_night_table[0],
					&night_view_tune_settings.ae_ai_night_table[0], 42*sizeof(int));
				isp_gen->ai_scene.scene_change_flag = 0;
				isp_gen->ai_scene.scene_frame_cnt = 0;
			}
#else
			isp_gen->tune.saturation_level = night_view_tune_settings.saturation_level;
			isp_gen->tune.hue_level = night_view_tune_settings.hue_level;
			isp_gen->tune.contrast_level = night_view_tune_settings.contrast_level;
			isp_gen->tune.sharpness_level = night_view_tune_settings.sharpness_level;
			isp_gen->tune.brightness_level = night_view_tune_settings.brightness_level;
			isp_gen->tune.denoise_level = night_view_tune_settings.denoise_level;
			isp_gen->tune.tdf_level = night_view_tune_settings.tdf_level;
			isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor = night_view_tune_settings.r_gain;
			isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor = night_view_tune_settings.b_gain;
			isp_gen->ae_entity_ctx.ae_param->ae_setting.scene_mode = SCENE_MODE_CAPTURE;
			isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].length =
				night_view_tune_settings.ae_table_night_length;
			memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].ae_tbl[0],
				&night_view_tune_settings.ae_ai_night_table[0], 42*sizeof(int));
			isp_ae_set_params_helper(&isp_gen->ae_entity_ctx, ISP_AE_UPDATE_AE_TABLE);

			isp_gen->ai_scene.scene_change_flag = 0;
			isp_gen->ai_scene.scene_frame_cnt = 0;
#endif
		}

		if (isp_gen->ai_scene.cur_scene == PORTRAIT) {
#ifdef AI_SCENE_SMOOTH
			isp_gen->ae_entity_ctx.ae_param->ae_setting.scene_mode = SCENE_MODE_PREVIEW;
			if (isp_gen->ai_scene.scene_frame_cnt <= portrait_tune_settings.isp_ai_smooth_frames) {
				isp_gen->tune.saturation_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, portrait_tune_settings.isp_ai_smooth_frames, last_tune_settings.saturation_level, portrait_tune_settings.saturation_level);
				isp_gen->tune.hue_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, portrait_tune_settings.isp_ai_smooth_frames, last_tune_settings.hue_level, portrait_tune_settings.hue_level);
				isp_gen->tune.contrast_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, portrait_tune_settings.isp_ai_smooth_frames, last_tune_settings.contrast_level, portrait_tune_settings.contrast_level);
				isp_gen->tune.sharpness_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, portrait_tune_settings.isp_ai_smooth_frames, last_tune_settings.sharpness_level, portrait_tune_settings.sharpness_level);
				isp_gen->tune.brightness_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, portrait_tune_settings.isp_ai_smooth_frames, last_tune_settings.brightness_level, portrait_tune_settings.brightness_level);
				isp_gen->tune.denoise_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, portrait_tune_settings.isp_ai_smooth_frames, last_tune_settings.denoise_level, portrait_tune_settings.denoise_level);
				isp_gen->tune.tdf_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, portrait_tune_settings.isp_ai_smooth_frames, last_tune_settings.tdf_level, portrait_tune_settings.tdf_level);
				isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, portrait_tune_settings.isp_ai_smooth_frames, last_tune_settings.r_gain, portrait_tune_settings.r_gain);
				isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, portrait_tune_settings.isp_ai_smooth_frames, last_tune_settings.b_gain, portrait_tune_settings.b_gain);
			}
			if(isp_gen->ai_scene.scene_frame_cnt == portrait_tune_settings.isp_ai_smooth_frames) {
				last_tune_settings.saturation_level = isp_gen->tune.saturation_level;
				last_tune_settings.hue_level = isp_gen->tune.hue_level;
				last_tune_settings.contrast_level = isp_gen->tune.contrast_level;
				last_tune_settings.sharpness_level = isp_gen->tune.sharpness_level;
				last_tune_settings.denoise_level = isp_gen->tune.denoise_level;
				last_tune_settings.brightness_level = isp_gen->tune.brightness_level;
				last_tune_settings.tdf_level = isp_gen->tune.tdf_level;
				last_tune_settings.r_gain = isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor;
				last_tune_settings.b_gain = isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor;
				last_tune_settings.ae_table_night_length = portrait_tune_settings.ae_table_night_length;
				memcpy(&last_tune_settings.ae_ai_night_table[0], &portrait_tune_settings.ae_ai_night_table[0], 42*sizeof(int));
				isp_gen->ai_scene.scene_change_flag = 0;
				isp_gen->ai_scene.scene_frame_cnt = 0;
			}
#else
			isp_gen->tune.saturation_level = portrait_tune_settings.saturation_level;
			isp_gen->tune.hue_level = portrait_tune_settings.hue_level;
			isp_gen->tune.contrast_level = portrait_tune_settings.contrast_level;
			isp_gen->tune.sharpness_level = portrait_tune_settings.sharpness_level;
			isp_gen->tune.brightness_level = portrait_tune_settings.brightness_level;
			isp_gen->tune.denoise_level = portrait_tune_settings.denoise_level;
			isp_gen->tune.tdf_level = portrait_tune_settings.tdf_level;
			isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor = portrait_tune_settings.r_gain;
			isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor = portrait_tune_settings.b_gain;
			isp_gen->ai_scene.scene_change_flag = 0;
			isp_gen->ai_scene.scene_frame_cnt = 0;
#endif
		}

		if (isp_gen->ai_scene.cur_scene == NORMAL) {
#ifdef AI_SCENE_SMOOTH
			isp_gen->ae_entity_ctx.ae_param->ae_setting.scene_mode = SCENE_MODE_PREVIEW;
			if (isp_gen->ai_scene.scene_frame_cnt == 1) {
				if (memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[0],
					&normal_tune_settings.ae_ai_night_table[0], 42*sizeof(int))) {
					isp_ae_set_params_helper(&isp_gen->ae_entity_ctx, ISP_AE_UPDATE_AE_TABLE);
				}
			}
			if (isp_gen->ai_scene.scene_frame_cnt <= normal_tune_settings.isp_ai_smooth_frames) {
				isp_gen->tune.saturation_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, normal_tune_settings.isp_ai_smooth_frames, last_tune_settings.saturation_level, normal_tune_settings.saturation_level);
				isp_gen->tune.hue_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, normal_tune_settings.isp_ai_smooth_frames, last_tune_settings.hue_level, normal_tune_settings.hue_level);
				isp_gen->tune.contrast_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, normal_tune_settings.isp_ai_smooth_frames, last_tune_settings.contrast_level, normal_tune_settings.contrast_level);
				isp_gen->tune.sharpness_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, normal_tune_settings.isp_ai_smooth_frames, last_tune_settings.sharpness_level, normal_tune_settings.sharpness_level);
				isp_gen->tune.brightness_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, normal_tune_settings.isp_ai_smooth_frames, last_tune_settings.brightness_level, normal_tune_settings.brightness_level);
				isp_gen->tune.denoise_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, normal_tune_settings.isp_ai_smooth_frames, last_tune_settings.denoise_level, normal_tune_settings.denoise_level);
				isp_gen->tune.tdf_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, normal_tune_settings.isp_ai_smooth_frames, last_tune_settings.tdf_level, normal_tune_settings.tdf_level);
				isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, normal_tune_settings.isp_ai_smooth_frames, last_tune_settings.r_gain, normal_tune_settings.r_gain);
				isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, normal_tune_settings.isp_ai_smooth_frames, last_tune_settings.b_gain, normal_tune_settings.b_gain);
			}
			if (isp_gen->ai_scene.scene_frame_cnt == normal_tune_settings.isp_ai_smooth_frames) {
				last_tune_settings.saturation_level = isp_gen->tune.saturation_level;
				last_tune_settings.hue_level = isp_gen->tune.hue_level;
				last_tune_settings.contrast_level = isp_gen->tune.contrast_level;
				last_tune_settings.sharpness_level = isp_gen->tune.sharpness_level;
				last_tune_settings.denoise_level = isp_gen->tune.denoise_level;
				last_tune_settings.brightness_level = isp_gen->tune.brightness_level;
				last_tune_settings.tdf_level = isp_gen->tune.tdf_level;
				last_tune_settings.r_gain = isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor;
				last_tune_settings.b_gain = isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor;
				last_tune_settings.ae_table_night_length = normal_tune_settings.ae_table_night_length;
				memcpy(&last_tune_settings.ae_ai_night_table[0], &normal_tune_settings.ae_ai_night_table[0], 42*sizeof(int));
				isp_gen->ai_scene.scene_change_flag = 0;
				isp_gen->ai_scene.scene_frame_cnt = 0;
			}
#else
			isp_gen->ae_entity_ctx.ae_param->ae_setting.scene_mode = SCENE_MODE_PREVIEW;
			isp_gen->tune.saturation_level = normal_tune_settings.saturation_level;
			isp_gen->tune.hue_level = normal_tune_settings.hue_level;
			isp_gen->tune.contrast_level = normal_tune_settings.contrast_level;
			isp_gen->tune.sharpness_level = normal_tune_settings.sharpness_level;
			isp_gen->tune.brightness_level = normal_tune_settings.brightness_level;
			isp_gen->tune.denoise_level = normal_tune_settings.denoise_level;
			isp_gen->tune.tdf_level = normal_tune_settings.tdf_level;
			isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor = normal_tune_settings.r_gain;
			isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor = normal_tune_settings.b_gain;
			memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[0],
				&normal_tune_settings.ae_ai_night_table[0], 42*sizeof(int));
			isp_ae_set_params_helper(&isp_gen->ae_entity_ctx, ISP_AE_UPDATE_AE_TABLE);
			isp_gen->ai_scene.scene_change_flag = 0;
			isp_gen->ai_scene.scene_frame_cnt = 0;
#endif
		}

		if (isp_gen->ai_scene.cur_scene == GREEN_PLANTS) {
#ifdef AI_SCENE_SMOOTH
			// isp_gen->ae_entity_ctx.ae_param->ae_setting.scene_mode = SCENE_MODE_PREVIEW;
			if (isp_gen->ai_scene.scene_frame_cnt <= green_plants_tune_settings.isp_ai_smooth_frames) {
				isp_gen->tune.saturation_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, green_plants_tune_settings.isp_ai_smooth_frames, last_tune_settings.saturation_level, green_plants_tune_settings.saturation_level);
				isp_gen->tune.hue_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, green_plants_tune_settings.isp_ai_smooth_frames, last_tune_settings.hue_level, green_plants_tune_settings.hue_level);
				isp_gen->tune.contrast_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, green_plants_tune_settings.isp_ai_smooth_frames, last_tune_settings.contrast_level, green_plants_tune_settings.contrast_level);
				isp_gen->tune.sharpness_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, green_plants_tune_settings.isp_ai_smooth_frames, last_tune_settings.sharpness_level, green_plants_tune_settings.sharpness_level);
				isp_gen->tune.brightness_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, green_plants_tune_settings.isp_ai_smooth_frames, last_tune_settings.brightness_level, green_plants_tune_settings.brightness_level);
				isp_gen->tune.denoise_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, green_plants_tune_settings.isp_ai_smooth_frames, last_tune_settings.denoise_level, green_plants_tune_settings.denoise_level);
				isp_gen->tune.tdf_level =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, green_plants_tune_settings.isp_ai_smooth_frames, last_tune_settings.tdf_level, green_plants_tune_settings.tdf_level);
				isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, green_plants_tune_settings.isp_ai_smooth_frames, last_tune_settings.r_gain, green_plants_tune_settings.r_gain);
				isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor =
					ValueInterp(isp_gen->ai_scene.scene_frame_cnt, 0, green_plants_tune_settings.isp_ai_smooth_frames, last_tune_settings.b_gain, green_plants_tune_settings.b_gain);
			}
			if (isp_gen->ai_scene.scene_frame_cnt == green_plants_tune_settings.isp_ai_smooth_frames) {
				last_tune_settings.saturation_level = isp_gen->tune.saturation_level;
				last_tune_settings.hue_level = isp_gen->tune.hue_level;
				last_tune_settings.contrast_level = isp_gen->tune.contrast_level;
				last_tune_settings.sharpness_level = isp_gen->tune.sharpness_level;
				last_tune_settings.denoise_level = isp_gen->tune.denoise_level;
				last_tune_settings.brightness_level = isp_gen->tune.brightness_level;
				last_tune_settings.tdf_level = isp_gen->tune.tdf_level;
				last_tune_settings.r_gain = isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor;
				last_tune_settings.b_gain = isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor;
				last_tune_settings.ae_table_night_length = green_plants_tune_settings.ae_table_night_length;
				memcpy(&last_tune_settings.ae_ai_night_table[0],
					&green_plants_tune_settings.ae_ai_night_table[0], 42*sizeof(int));
				isp_gen->ai_scene.scene_change_flag = 0;
				isp_gen->ai_scene.scene_frame_cnt = 0;
			}
#else
			isp_gen->ae_entity_ctx.ae_param->ae_setting.scene_mode = SCENE_MODE_PREVIEW;
			isp_gen->tune.saturation_level = green_plants_tune_settings.saturation_level;
			isp_gen->tune.hue_level = green_plants_tune_settings.hue_level;
			isp_gen->tune.contrast_level = normal_tune_settings.contrast_level;
			isp_gen->tune.sharpness_level = green_plants_tune_settings.sharpness_level;
			isp_gen->tune.brightness_level = green_plants_tune_settings.brightness_level;
			isp_gen->tune.denoise_level = green_plants_tune_settings.denoise_level;
			isp_gen->tune.tdf_level = green_plants_tune_settings.tdf_level;
			isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor = green_plants_tune_settings.r_gain;
			isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor = green_plants_tune_settings.b_gain;
			isp_gen->ai_scene.scene_change_flag = 0;
			isp_gen->ai_scene.scene_frame_cnt = 0;
#endif
		}
		__isp_ctx_update_awb_cfg(isp_gen);
		ISP_PRINT("#### cur_scene_frame_cnt:%d saturation_level:%d hue_level:%d contrast_level:%d sharpness_level:%d"
		          " denoise_level:%d brightness_level:%d tdf_level:%d r_gain:%d b_gain:%d scene_mode:%d \n",
			      isp_gen->ai_scene.scene_frame_cnt, isp_gen->tune.saturation_level,isp_gen->tune.hue_level,isp_gen->tune.contrast_level,
			      isp_gen->tune.sharpness_level, isp_gen->tune.denoise_level,isp_gen->tune.brightness_level, isp_gen->tune.tdf_level,
			      isp_gen->isp_ini_cfg.isp_3a_settings.awb_rgain_favor, isp_gen->isp_ini_cfg.isp_3a_settings.awb_bgain_favor, isp_gen->ae_settings.scene_mode);
	}
}
#endif

void __isp_ae_update_sensor_info(struct isp_lib_context *isp_gen)
{
	isp_sensor_info_t *sensor_info = &isp_gen->sensor_info;
	ae_result_t *result = &isp_gen->ae_entity_ctx.ae_result;
	HW_U32 total_vts = isp_gen->sensor_info.exp_line / 16;

	sensor_info->exp_line = result->sensor_set.ev_set_curr.ev_sensor_exp_line;
	sensor_info->ang_gain = result->sensor_set.ev_set_curr.ev_analog_gain;
	sensor_info->dig_gain = result->sensor_set.ev_set_curr.ev_digital_gain;
	sensor_info->total_gain = result->sensor_set.ev_set_curr.ev_total_gain;

	sensor_info->ae_tbl_idx = result->sensor_set.ev_set_curr.ev_idx;
	sensor_info->ae_tbl_idx_max = result->sensor_set.ev_idx_max;

	sensor_info->is_ae_done = (result->ae_status == AE_STATUS_DONE) ? 1 : 0;
	sensor_info->backlight = result->backlight;
	sensor_info->ae_gain = result->ae_gain;
	sensor_info->ae_lv = result->sensor_set.ev_set_curr.ev_lv;

	if (sensor_info->vts && sensor_info->hts && sensor_info->pclk) {
		total_vts = sensor_info->vts > total_vts ? sensor_info->vts : total_vts;
		sensor_info->fps = sensor_info->pclk / (total_vts * sensor_info->hts);
	} else {
		sensor_info->fps = 30;
	}
	sensor_info->fps = clamp(sensor_info->fps, 1, 1000);
	sensor_info->frame_time = 1000 / sensor_info->fps; /*ms*/
}

void __isp_ae_run(struct isp_lib_context *isp_gen)
{
	isp_ae_entity_context_t *isp_ae_cxt = &isp_gen->ae_entity_ctx;
	int ret = 0;

	if (isp_gen->ops->ae_done) {
		ret = isp_gen->ops->ae_done(isp_gen, &isp_ae_cxt->ae_result);
	}

	if (isp_gen->ae_settings.ae_face_disappear_flag &&
		(!isp_gen->ae_settings.ae_face_disappear_job_done)) {
		if (--isp_gen->ae_settings.ae_face_delay_cnt < 1) {
			/* reset disappear_flag and delay_cnt */
			isp_gen->ae_settings.ae_face_disappear_job_done = 1;
			isp_gen->ae_settings.ae_face_disappear_flag = 0;
			isp_gen->ae_settings.ae_face_for_detect_flag = 1;
			isp_gen->ae_settings.ae_face_appear_cnt = 0;
			isp_gen->ae_settings.ae_face_delay_cnt = isp_gen->ae_settings.face_cfg.face_ae_delay_cnt;
			/* reset exp_metering_mode to AE_METERING_MODE_MATRIX */
			isp_gen->ae_settings.exp_metering_mode = AE_METERING_MODE_MATRIX;
			isp_gen->ae_settings.exposure_lock = false;
			isp_gen->isp_3a_change_flags |= ISP_SET_AE_METERING_MODE;
			ISP_PRINT("[done] ae_face_for_detect_flag = %d, ae_face_disappear_flag = %d, entity->ae_face_delay_cnt = %d, ae_face_disappear_job_done = %d\n",
			isp_gen->ae_settings.ae_face_for_detect_flag,
			isp_gen->ae_settings.ae_face_disappear_flag,
			isp_gen->ae_settings.ae_face_delay_cnt,
			isp_gen->ae_settings.ae_face_disappear_job_done);
			return;
		}
		/* output save target */
		isp_gen->ae_entity_ctx.ae_result.ae_target = isp_gen->ae_settings.ae_face_last_target;
		return;
	} else {
		if (!ret || !isp_gen->ae_frame_cnt) {
			isp_ae_cxt->ops->isp_ae_run(isp_ae_cxt->ae_entity,
					&isp_ae_cxt->ae_stats, &isp_ae_cxt->ae_result);
		}
	}

	__isp_ae_update_sensor_info(isp_gen);
	config_gamma(isp_gen);
	config_dig_gain(isp_gen, isp_ae_cxt->ae_result.sensor_set.ev_set_curr.ev_digital_gain,
		isp_ae_cxt->ae_result.sensor_set_short.ev_set_curr.ev_digital_gain);
	config_wdr(isp_gen, 0);
}

void __isp_gtm_set_params(struct isp_lib_context *isp_gen)
{
	isp_gen->gtm_entity_ctx.gtm_param->gtm_frame_id = isp_gen->gtm_frame_cnt;
	isp_gen->gtm_entity_ctx.gtm_param->contrast = isp_gen->adjust.contrast;
	isp_gen->gtm_entity_ctx.gtm_param->brightness = isp_gen->adjust.brightness;
	isp_gen->gtm_entity_ctx.gtm_param->BrightPixellValue =	isp_gen->ae_entity_ctx.ae_result.BrightPixellValue;
	isp_gen->gtm_entity_ctx.gtm_param->DarkPixelValue = isp_gen->ae_entity_ctx.ae_result.DarkPixelValue;
	//gtm_ini_cfg.
	isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_hist_sel = isp_gen->isp_ini_cfg.isp_tunning_settings.gtm_hist_sel;
	isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_type = isp_gen->isp_ini_cfg.isp_tunning_settings.gtm_type;
	isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_bright_dn_limit = isp_gen->isp_ini_cfg.isp_tunning_settings.gtm_bright_dn_limit;
	isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_interval = isp_gen->isp_ini_cfg.isp_tunning_settings.gtm_interval;
	isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_reserve0 = isp_gen->isp_ini_cfg.isp_tunning_settings.gtm_reserve0;
	isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_reserve1 = isp_gen->isp_ini_cfg.isp_tunning_settings.gtm_reserve1;
	isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_reserve2 = isp_gen->isp_ini_cfg.isp_tunning_settings.gtm_reserve2;
	isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_reserve3 = isp_gen->isp_ini_cfg.isp_tunning_settings.gtm_reserve3;
	memcpy(&isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_cfg[0], &isp_gen->ae_settings.ae_hist_eq_cfg[0], ISP_GTM_HEQ_MAX * sizeof(HW_S16));
	isp_gtm_set_params_helper(&isp_gen->gtm_entity_ctx, ISP_GTM_INI_DATA);
}

void __isp_gtm_run(struct isp_lib_context *isp_gen)
{
	isp_gtm_entity_context_t *isp_gtm_cxt = &isp_gen->gtm_entity_ctx;
	int ret = 0;

	if (isp_gen->ops->gtm_done) {
		ret = isp_gen->ops->gtm_done(isp_gen, &isp_gtm_cxt->gtm_result);
	}

	if (!ret || !isp_gen->gtm_frame_cnt) {
		isp_gtm_cxt->ops->isp_gtm_run(isp_gtm_cxt->gtm_entity,
					&isp_gtm_cxt->gtm_stats,
					&isp_gtm_cxt->gtm_result);
	}
}

void __isp_pltm_set_params(struct isp_lib_context *isp_gen)
{
	struct isp_param_config *param = &isp_gen->isp_ini_cfg;
	isp_gen->pltm_entity_ctx.pltm_param->pltm_frame_id = isp_gen->ae_frame_cnt;

	//pltm_ini_cfg.
	isp_gen->pltm_entity_ctx.pltm_param->wdr_stitch_en = isp_gen->isp_ini_cfg.isp_test_settings.wdr_stitch_en;
	isp_gen->pltm_entity_ctx.pltm_param->wdr_ratio_real = isp_gen->ae_entity_ctx.ae_result.ae_wdr_ratio.real;
	memcpy(&isp_gen->pltm_entity_ctx.pltm_param->pltm_ini.pltm_cfg[0],
			&param->isp_tunning_settings.pltm_cfg[0], ISP_PLTM_MAX * sizeof(HW_S32));
	memcpy(&isp_gen->pltm_entity_ctx.pltm_param->pltm_ini.pltm_dynamic_cfg[0],
		&isp_gen->ae_settings.pltm_dynamic_cfg[0], ISP_PLTM_DYNAMIC_MAX*sizeof(HW_S16));
}

void __isp_pltm_run(struct isp_lib_context *isp_gen)
{
	pltm_result_t *result = &isp_gen->pltm_entity_ctx.pltm_result;
	struct isp_pltm_config *pltm_cfg = &isp_gen->module_cfg.pltm_cfg;
	isp_pltm_entity_context_t *isp_pltm_ctx = &isp_gen->pltm_entity_ctx;
	int ret = 0;

	if (isp_gen->ops->pltm_done) {
		ret = isp_gen->ops->pltm_done(isp_gen, &isp_pltm_ctx->pltm_result);
	}
	if (!ret) {
		isp_pltm_ctx->ops->isp_pltm_run(isp_pltm_ctx->pltm_entity,
			&isp_pltm_ctx->pltm_stats, &isp_pltm_ctx->pltm_result);
	}

	pltm_cfg->strength = result->pltm_auto_stren;
	if (pltm_cfg->dcc_hi_th != pltm_cfg->dcc_lw_th)
		pltm_cfg->dcc_slp = ((256 - pltm_cfg->dcc_lw_ratio) << 8) / (pltm_cfg->dcc_hi_th - pltm_cfg->dcc_lw_th);
	else
		pltm_cfg->dcc_slp = 132;

	ISP_LIB_LOG(ISP_LOG_PLTM, "dcc_lw_ratio = %d, hdr dcc_lw_ratio = %d\n", isp_pltm_ctx->pltm_param->pltm_ini.pltm_dynamic_cfg[ISP_PLTM_DYNAMIC_DCC_LW_RT], pltm_cfg->dcc_lw_ratio);
}

void __isp_ctx_cfg_lib(struct isp_lib_context *isp_gen)
{
	// isp_lib_context def settings
	isp_gen->adjust.contrast   = 0;
	isp_gen->adjust.brightness = 0;
	isp_gen->adjust.defog_value = 0;

	isp_gen->tune.contrast_level = 256;
	isp_gen->tune.brightness_level = 256;
	isp_gen->tune.sharpness_level = 256;
	isp_gen->tune.saturation_level = 256;
	isp_gen->tune.tdf_level = 256;
	isp_gen->tune.denoise_level = 256;
	isp_gen->tune.pltmwdr_level = 0;
	isp_gen->tune.effect = ISP_COLORFX_NONE;
	isp_gen->VencVe2IspParam.d2d_level = 256;
	isp_gen->VencVe2IspParam.d3d_level = 256;
	isp_gen->VencVe2IspParam.mMovingLevelInfo.is_overflow = 0;
	isp_gen->npu_nr_cfg.roi_num = 0;

	isp_gen->awb_settings.wb_gain_manual.r_gain = 256;
	isp_gen->awb_settings.wb_gain_manual.gr_gain = 256;
	isp_gen->awb_settings.wb_gain_manual.gb_gain = 256;
	isp_gen->awb_settings.wb_gain_manual.b_gain = 256;

	// exp settings
	isp_gen->ae_settings.exp_mode = EXP_AUTO;
	isp_gen->ae_settings.exp_metering_mode = AE_METERING_MODE_MATRIX;
	isp_gen->ae_settings.flash_mode = FLASH_MODE_NONE;
	isp_gen->ae_settings.flash_switch_flag = false;
	isp_gen->ae_settings.flash_open = 0;
	isp_gen->ae_settings.flicker_mode = FREQUENCY_AUTO;
	isp_gen->ae_settings.iso_mode = ISO_AUTO;
	isp_gen->ae_settings.exposure_lock = false;
	isp_gen->ae_settings.exp_compensation = 0;
	isp_gen->ae_settings.ae_face_for_detect_flag = 1;
	isp_gen->ae_settings.exp_absolute = 250000; /* default max exp for exp manual */

	// af settings
	isp_gen->af_settings.af_mode = AUTO_FOCUS_CONTINUEOUS;
	isp_gen->af_settings.af_metering_mode = AUTO_FOCUS_METERING_CENTER_WEIGHTED;
	isp_gen->af_settings.focus_lock = false;
	isp_gen->af_settings.af_range = AUTO_FOCUS_RANGE_AUTO;

	// awb settings
	isp_gen->awb_settings.wb_mode = WB_AUTO;
	isp_gen->awb_settings.white_balance_lock = false;
	//isp_gen->awb_settings.awb_coor.x1 = H3A_PIC_OFFSET;
	//isp_gen->awb_settings.awb_coor.y1 = H3A_PIC_OFFSET;
	//isp_gen->awb_settings.awb_coor.x2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
	//isp_gen->awb_settings.awb_coor.y2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
	isp_gen->ae_settings.ae_coor.x1 = H3A_PIC_OFFSET;
	isp_gen->ae_settings.ae_coor.y1 = H3A_PIC_OFFSET;
	isp_gen->ae_settings.ae_coor.x2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
	isp_gen->ae_settings.ae_coor.y2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
	memset(&(isp_gen->ae_settings.face_cfg), 0, sizeof(struct ae_face_cfg));

	isp_gen->af_settings.af_coor.x1 = H3A_PIC_OFFSET;
	isp_gen->af_settings.af_coor.y1 = H3A_PIC_OFFSET;
	isp_gen->af_settings.af_coor.x2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
	isp_gen->af_settings.af_coor.y2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;

	isp_gen->stat.min_rgb_saved = 1023;
	isp_gen->stat.c_noise_saved = 20;

	isp_gen->stats_ctx.wb_gain_saved.r_gain = 256;
	isp_gen->stats_ctx.wb_gain_saved.gr_gain = 256;
	isp_gen->stats_ctx.wb_gain_saved.gb_gain = 256;
	isp_gen->stats_ctx.wb_gain_saved.b_gain = 256;

	//alsc settings
	isp_gen->alsc_settings.correct_freqs = 6;
	isp_gen->alsc_settings.correct_start = isp_gen->alsc_settings.correct_freqs * 5;
	isp_gen->alsc_settings.gain_pool_size = 16;
	isp_gen->alsc_settings.table_switch = 2;
	isp_gen->alsc_settings.pre_lowBright = 35;
	isp_gen->alsc_settings.pre_complex = 141;
	isp_gen->alsc_settings.pre_highSatu = 161;
	isp_gen->alsc_settings.rgb_semiflat = 6;
	isp_gen->alsc_settings.rch_semiflat = 0;

	//sensor temp
	isp_gen->temp_info.enable = 1;  //default is enable

	//sensor flip
	isp_gen->flip_info.enable = 1;
	isp_gen->flip_info.hflip = 0;
	isp_gen->flip_info.vflip = 0;
	//sensor_mipi_switch
	isp_gen->switch_info.mipi_switch_enable = 0;
	isp_gen->switch_info.bgain_comp = 10000;
	isp_gen->switch_info.rgain_comp = 10000;
	isp_gen->switch_info.bgain_comp_last = 10000;
	isp_gen->switch_info.rgain_comp_last = 10000;
	isp_gen->switch_info.sensorA_awb_stats = NULL;
	isp_gen->switch_info.sensorB_awb_stats = NULL;

	//wdr setting
	isp_gen->ae_entity_ctx.ae_result.ae_wdr_ratio.tmp = 16<<10;
	isp_gen->ae_entity_ctx.ae_result.ae_wdr_ratio.real = isp_gen->ae_entity_ctx.ae_result.ae_wdr_ratio.tmp;
	isp_gen->ae_entity_ctx.ae_result.ae_wdr_ratio.isp_hardware = isp_gen->ae_entity_ctx.ae_result.ae_wdr_ratio.tmp;

	//algo save variable
	isp_gen->algo_save.wb_rgain_last[0] = 256;
	isp_gen->algo_save.wb_rgain_last[1] = 256;
	isp_gen->algo_save.wb_bgain_last[0] = 256;
	isp_gen->algo_save.wb_bgain_last[1] = 256;
	isp_gen->algo_save.wb_l_shift = 0;
	isp_gen->algo_save.lsc_color_temp_save = 5500;
	isp_gen->algo_save.lsc_comp_save = 256;
	isp_gen->algo_save.lsc_vcm_std_pos_save = 300;
	isp_gen->algo_save.lsc_hflip_save = 0;
	isp_gen->algo_save.lsc_vflip_save = 0;
	isp_gen->algo_save.d3d_k_cnt = 10;
	isp_gen->algo_save.d3d_k_tdnf_en_last = 1;
	isp_gen->algo_save.d3d_k_cal_start_avg = 0;

	// 1 -> gamma 2.2
	// 2 -> gamma 1.69
	// 3 -> gamma 1.3
	//isp_gen->ai_isp_en = 0;

	//user initial setting
	if (isp_gen->initial_cfg.enable.exp_mode_en) {
		isp_gen->initial_cfg.enable.exp_mode_en = false;
		isp_gen->ae_settings.exp_mode = isp_gen->initial_cfg.exp_mode;
	}
	if (isp_gen->initial_cfg.enable.flicker_mode_en) {
		isp_gen->initial_cfg.enable.flicker_mode_en = false;
		isp_gen->ae_settings.flicker_mode = isp_gen->initial_cfg.flicker_mode;
	}
	if (isp_gen->initial_cfg.enable.iso_mode_en) {
		isp_gen->initial_cfg.enable.iso_mode_en = false;
		isp_gen->ae_settings.iso_mode = isp_gen->initial_cfg.iso_mode;
	}
	if (isp_gen->initial_cfg.enable.exp_compensation_en) {
		isp_gen->initial_cfg.enable.exp_compensation_en = false;
		isp_gen->ae_settings.exp_compensation = isp_gen->initial_cfg.exp_compensation;
	}
	if (isp_gen->initial_cfg.enable.iso_sensitivity_en) {
		isp_gen->initial_cfg.enable.iso_sensitivity_en = false;
		isp_gen->ae_settings.iso_sensitivity = isp_gen->initial_cfg.iso_sensitivity;
	}
	if (isp_gen->initial_cfg.enable.exposure_metering_en) {
		isp_gen->initial_cfg.enable.exposure_metering_en = false;
		isp_gen->ae_settings.exp_metering_mode = isp_gen->initial_cfg.ae_metering_mode;
	}
	if (isp_gen->initial_cfg.enable.exp_absolute_en) {
		isp_gen->initial_cfg.enable.exp_absolute_en = false;
		isp_gen->ae_settings.exp_absolute = isp_gen->initial_cfg.exp_absolute;
	}
	if (isp_gen->initial_cfg.enable.wb_mode_en) {
		isp_gen->initial_cfg.enable.wb_mode_en = false;
		isp_gen->awb_settings.wb_mode = isp_gen->initial_cfg.wb_mode;
	}
	if (isp_gen->initial_cfg.enable.brightness_level_en) {
		isp_gen->initial_cfg.enable.brightness_level_en = false;
		isp_gen->tune.brightness_level = isp_gen->initial_cfg.brightness_level;
	}
	if (isp_gen->initial_cfg.enable.contrast_level_en) {
		isp_gen->initial_cfg.enable.contrast_level_en = false;
		isp_gen->tune.contrast_level = isp_gen->initial_cfg.contrast_level;
	}
	if (isp_gen->initial_cfg.enable.saturation_level_en) {
		isp_gen->initial_cfg.enable.saturation_level_en = false;
		isp_gen->tune.saturation_level = isp_gen->initial_cfg.saturation_level;
	}
	if (isp_gen->initial_cfg.enable.sharpness_level_en) {
		isp_gen->initial_cfg.enable.sharpness_level_en = false;
		isp_gen->tune.sharpness_level = isp_gen->initial_cfg.sharpness_level;
	}
	if (isp_gen->initial_cfg.enable.effect_en) {
		isp_gen->initial_cfg.enable.effect_en = false;
		isp_gen->tune.effect = isp_gen->initial_cfg.effect;
	}
	if (isp_gen->initial_cfg.enable.ai_scene_en) {
		isp_gen->initial_cfg.enable.ai_scene_en = false;
		isp_gen->ai_scene.cur_scene = isp_gen->initial_cfg.ai_scene;
		isp_gen->ai_scene.scene_change_flag = 1;
	} else {
		isp_gen->ai_scene.cur_scene = NORMAL;
		isp_gen->ai_scene.scene_change_flag = 0;
	}

#if ISP_AI_SCENE_CONF
	// for ai scene param
	isp_gen->ai_scene.last_tune_settings.contrast_level = isp_gen->tune.contrast_level;
	isp_gen->ai_scene.last_tune_settings.saturation_level = isp_gen->tune.saturation_level;
	isp_gen->ai_scene.last_tune_settings.brightness_level = isp_gen->tune.brightness_level;
	isp_gen->ai_scene.last_tune_settings.sharpness_level = isp_gen->tune.sharpness_level;
	isp_gen->ai_scene.last_tune_settings.tdf_level = isp_gen->tune.tdf_level;
	isp_gen->ai_scene.last_tune_settings.denoise_level = isp_gen->tune.denoise_level;
	isp_gen->ai_scene.last_tune_settings.hue_level = isp_gen->tune.hue_level;
	normal_tune_settings.contrast_level = isp_gen->tune.contrast_level;
	normal_tune_settings.saturation_level = isp_gen->tune.saturation_level;
	normal_tune_settings.brightness_level = isp_gen->tune.brightness_level;
	normal_tune_settings.sharpness_level = isp_gen->tune.sharpness_level;
	normal_tune_settings.tdf_level = isp_gen->tune.tdf_level;
	normal_tune_settings.denoise_level = isp_gen->tune.denoise_level;
	normal_tune_settings.hue_level = isp_gen->tune.hue_level;
	isp_gen->ai_scene.scene_frame_cnt = 0;
	//isp_gen->ae_settings.scene_mode = SCENE_MODE_PREVIEW;
#endif
}

#define ISP_CTX_MODULE_EN(en_bit, ISP_FEATURES) \
{ \
	if (en_bit) {\
		mod_cfg->module_enable_flag |= ISP_FEATURES;\
	} else {\
		mod_cfg->module_enable_flag &= ~ISP_FEATURES;\
	}\
}

int __isp_ctx_apply_enable(struct isp_lib_context *isp_gen)
{
	struct isp_module_config *mod_cfg = &isp_gen->module_cfg;
	struct isp_param_config *param = &isp_gen->isp_ini_cfg;


	if (isp_gen->sensor_info.wdr_mode == 0)
		param->isp_test_settings.wdr_stitch_en = 0;

	ISP_CTX_MODULE_EN(param->isp_test_settings.sharp_en       , ISP_FEATURES_SHARP);
	ISP_CTX_MODULE_EN(param->isp_test_settings.denoise_en     , ISP_FEATURES_D2D);
	ISP_CTX_MODULE_EN(param->isp_test_settings.drc_en         , ISP_FEATURES_DRC);
//	ISP_CTX_MODULE_EN(param->isp_test_settings.lsc_en         , ISP_FEATURES_LSC);
	ISP_CTX_MODULE_EN(param->isp_test_settings.msc_en         , ISP_FEATURES_MSC);
	ISP_CTX_MODULE_EN(param->isp_test_settings.gamma_en       , ISP_FEATURES_GAMMA);
	ISP_CTX_MODULE_EN(param->isp_test_settings.ccm_en         , ISP_FEATURES_RGB2RGB);
	ISP_CTX_MODULE_EN(param->isp_test_settings.blc_en         , ISP_FEATURES_BLC);
	ISP_CTX_MODULE_EN(param->isp_test_settings.wb_en          , ISP_FEATURES_WB);
	ISP_CTX_MODULE_EN(param->isp_test_settings.dpc_en         , ISP_FEATURES_DPC);
	ISP_CTX_MODULE_EN(param->isp_test_settings.cfa_en         , ISP_FEATURES_CFA);
	ISP_CTX_MODULE_EN(param->isp_test_settings.tdf_en         , ISP_FEATURES_D3D);
	ISP_CTX_MODULE_EN(param->isp_test_settings.fpn_en         , ISP_FEATURES_FPN);
	ISP_CTX_MODULE_EN(param->isp_test_settings.lca_en         , ISP_FEATURES_LCA);
	ISP_CTX_MODULE_EN(param->isp_test_settings.gca_en         , ISP_FEATURES_GCA);
 	ISP_CTX_MODULE_EN(param->isp_test_settings.dig_gain_en    , ISP_FEATURES_DG);
	ISP_CTX_MODULE_EN(param->isp_test_settings.cem_en         , ISP_FEATURES_CEM);
	ISP_CTX_MODULE_EN(param->isp_test_settings.pltm_en        , ISP_FEATURES_PLTM);
	ISP_CTX_MODULE_EN(param->isp_test_settings.wdr_stitch_en  , ISP_FEATURES_WDR_STITCH);
	ISP_CTX_MODULE_EN(param->isp_test_settings.wdr_split_en   , ISP_FEATURES_WDR_SPLIT);
 	ISP_CTX_MODULE_EN(param->isp_test_settings.ctc_en         , ISP_FEATURES_CTC);

	// Colorspace open in hardware as default.
	ISP_CTX_MODULE_EN(1, ISP_FEATURES_RGB2YUV);
	ISP_CTX_MODULE_EN(1, ISP_FEATURES_WDR);
	ISP_CTX_MODULE_EN(1, ISP_FEATURES_NRP);
	ISP_CTX_MODULE_EN(1, ISP_FEATURES_NR);
	ISP_CTX_MODULE_EN(1, ISP_FEATURES_VIN);

	ISP_CTX_MODULE_EN(param->isp_test_settings.afs_en        , ISP_FEATURES_AFS);
	ISP_CTX_MODULE_EN(param->isp_test_settings.ae_en         , ISP_FEATURES_AE);
	ISP_CTX_MODULE_EN(param->isp_test_settings.awb_en        , ISP_FEATURES_AWB);
	ISP_CTX_MODULE_EN(param->isp_test_settings.af_en         , ISP_FEATURES_AF);
	ISP_CTX_MODULE_EN(param->isp_test_settings.hist_en       , ISP_FEATURES_HIST);

	mod_cfg->module_enable_flag |= ISP_FEATURES_MODE;

	isp_lib_log_param = param->isp_test_settings.isp_log_param;

	return 0;
}
#if 0
static void __build_sharp_anti_tbl(HW_U16 *gm_in, HW_U16 *inv_gm_out)
{
	int i, j, max, min;
	int tmp = 0;

	//anti gamma
	inv_gm_out[0] = 0;
	for(i = 1; i < 64; i++) {
		for(j = tmp; j < 64; j++) {
			min = gm_in[j];
			max = gm_in[j+1];
			if((i*64) >= min && (i*64) <= max) {
				inv_gm_out[i] = (j*64 + 64*(i*64-min)/(max-min));
				tmp = j;
				break;
			}
			inv_gm_out[i] = 4095;
		}
	}
	inv_gm_out[64] = 4095;
}
#endif
static void __isp_ctx_cfg_mod(struct isp_lib_context *isp_gen)
{
	//after __isp_ctx_cfg_lib
	struct isp_module_config *mod_cfg = &isp_gen->module_cfg;
	struct isp_param_config *param = &isp_gen->isp_ini_cfg;
	int i = 0, j = 0, msc_w_count = 0, msc_h_count = 0;
	//HW_U8 isp_tdnf_k_mg_bk[ISP_REG1_TBL_LENGTH] = {0, 8, 16, 24, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128};
	//HW_U8 isp_tdnf_r_mg_bk[ISP_REG1_TBL_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 5, 9, 19, 37, 71, 255};
	HW_U8 isp_tdnf_df_bd_tbl[ISP_TDNF_TBL_SIZE] = {
		255,   255,   255,   255,   255,   255,   255,   255,
		255,   255,   255,   255,   255,   255,   255,   255,
		255,   254,   254,   254,   254,   254,   254,   253,
		253,   253,   253,   253,   252,   252,   252,   252,
		252,   251,   251,   251,   250,   250,   250,   250,
		249,   249,   249,   248,   248,   248,   247,   247,
		247,   246,   246,   245,   245,   245,   244,   244,
		243,   243,   242,   242,   241,   241,   240,   240,
		240,   239,   238,   238,   237,   237,   236,   236,
		235,   235,   234,   234,   233,   232,   232,   231,
		231,   230,   229,   229,   228,   227,   227,   226,
		225,   225,   224,   223,   222,   222,   221,   220,
		220,   219,   218,   217,   216,   216,   215,   214,
		213,   212,   212,   211,   210,   209,   208,   207,
		207,   206,   205,   204,   203,   202,   201,   200,
		199,   198,   197,   196,   195,   194,   193,   192,
		192,   190,   189,   188,   187,   186,   185,   184,
		183,   182,   181,   180,   179,   178,   177,   176,
		175,   173,   172,   171,   170,   169,   168,   166,
		165,   164,   163,   162,   160,   159,   158,   157,
		156,   154,   153,   152,   150,   149,   148,   147,
		145,   144,   143,   141,   140,   139,   137,   136,
		135,   133,   132,   130,   129,   128,   126,   125,
		123,   122,   120,   119,   117,   116,   114,   113,
		112,   110,   108,   107,   105,   104,   102,   101,
		99,    98,    96,    95,    93,    91,    90,    88,
		87,    85,    83,    82,    80,    78,    77,    75,
		73,    72,    70,    68,    66,    65,    63,    61,
		60,    58,    56,    54,    52,    51,    49,    47,
		45,    43,    42,    40,    38,    36,    34,    32,
		31,    29,    27,    25,    23,    21,    19,    17,
		15,    13,    11,     9,     7,     5,     3,     1
	};

	//WDR
	if (isp_gen->sensor_info.wdr_mode == ISP_2FCMD_WDR_MODE || isp_gen->sensor_info.wdr_mode == ISP_3FCMD_WDR_MODE) { /* one ch data input */
		mod_cfg->mode_cfg.wdr_mode = WDR_1FCH;
		isp_gen->ae_settings.ae_mode = AE_NORM;
		mod_cfg->mode_cfg.dg_mode = DG_AFTER_WDR;
	} else if (isp_gen->sensor_info.wdr_mode == ISP_2FDOL_WDR_MODE || isp_gen->sensor_info.wdr_mode == ISP_2FCMD1FDOL_WDR_MODE
			|| isp_gen->sensor_info.wdr_mode == ISP_1FDOL2FCMD_WDR_MODE) { /* two ch data input */
		mod_cfg->mode_cfg.wdr_mode = WDR_2FCH;
		isp_gen->ae_settings.ae_mode = clamp(param->isp_3a_settings.wdr_comm_cfg[WDR_COMM_MODE], AE_WDR, AE_WDR_AUTO_DG);
		if (isp_gen->ae_settings.ae_mode == AE_WDR_DG || isp_gen->ae_settings.ae_mode == AE_WDR_AUTO_DG) {
			mod_cfg->mode_cfg.dg_mode = DG_BEFORE_WDR;
		} else {
			mod_cfg->mode_cfg.dg_mode = DG_AFTER_WDR;
		}
	} else if (isp_gen->sensor_info.wdr_mode == ISP_3FDOL_WDR_MODE) { /* three ch data input */
		mod_cfg->mode_cfg.wdr_mode = WDR_3FCH;
		isp_gen->ae_settings.ae_mode = AE_WDR;
		if (isp_gen->ae_settings.ae_mode == AE_WDR_DG || isp_gen->ae_settings.ae_mode == AE_WDR_AUTO_DG) {
			mod_cfg->mode_cfg.dg_mode = DG_BEFORE_WDR;
		} else {
			mod_cfg->mode_cfg.dg_mode = DG_AFTER_WDR;
		}
	} else {
		mod_cfg->mode_cfg.wdr_mode = WDR_1FCH;
		isp_gen->ae_settings.ae_mode = AE_NORM;
		mod_cfg->mode_cfg.dg_mode = DG_AFTER_WDR;
	}

	config_wdr_split(isp_gen);
	config_fe_channel(isp_gen);
	config_wdr(isp_gen, 1);

	isp_gen->databit.st_fpn = 12;
	isp_gen->databit.st_dpc = 12;
	isp_gen->databit.st_pltm = 12;/*10/12*/
	isp_gen->databit.st_ccm = isp_gen->databit.st_pltm;
	isp_gen->databit.st_csc = 10;
	isp_gen->databit.st_drc = 8;
	isp_gen->databit.st_cem = 8;

	//awb
	if (param->isp_test_settings.wb_en == 0 ||
	    mod_cfg->wb_gain_cfg.wb_gain.r_gain == 0 ||
	    mod_cfg->wb_gain_cfg.wb_gain.gr_gain == 0 ||
	    mod_cfg->wb_gain_cfg.wb_gain.gb_gain == 0 ||
	    mod_cfg->wb_gain_cfg.wb_gain.b_gain == 0) {
		mod_cfg->wb_gain_cfg.wb_gain.r_gain  = 468;
		mod_cfg->wb_gain_cfg.wb_gain.gr_gain = 256;
		mod_cfg->wb_gain_cfg.wb_gain.gb_gain = 256;
		mod_cfg->wb_gain_cfg.wb_gain.b_gain  = 482;
	}

	if (isp_gen->initial_cfg.enable.wb_mgain_en) {//wb manual gain user initial setting
		isp_gen->initial_cfg.enable.wb_mgain_en = false;
		mod_cfg->wb_gain_cfg.wb_gain = isp_gen->initial_cfg.wb_gain_manual;
		isp_gen->awb_entity_ctx.awb_result.wb_gain_output = isp_gen->initial_cfg.wb_gain_manual;
		isp_gen->awb_settings.wb_gain_manual = isp_gen->initial_cfg.wb_gain_manual;
	}

	mod_cfg->awb_cfg.awb_stat_low_lim = param->isp_3a_settings.awb_stat_low_lim;
	mod_cfg->awb_cfg.awb_stat_high_lim = param->isp_3a_settings.awb_stat_high_lim;
	isp_gen->awb_settings.wb_stat_combine_mode = WB_STAT_NONE;

	if (isp_gen->isp_ini_cfg.isp_3a_settings.awb_stat_mode == 2) {
		isp_gen->awb_settings.awb_coor.x1 = H3A_PIC_OFFSET;
		isp_gen->awb_settings.awb_coor.y1 = H3A_PIC_OFFSET;
		isp_gen->awb_settings.awb_coor.x2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
		isp_gen->awb_settings.awb_coor.y2 = 0;
	} else if (isp_gen->isp_ini_cfg.isp_3a_settings.awb_stat_mode == 1) {
		isp_gen->awb_settings.awb_coor.x1 = H3A_PIC_OFFSET;
		isp_gen->awb_settings.awb_coor.y1 = 0;
		isp_gen->awb_settings.awb_coor.x2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
		isp_gen->awb_settings.awb_coor.y2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
	} else {
		isp_gen->awb_settings.awb_coor.x1 = H3A_PIC_OFFSET;
		isp_gen->awb_settings.awb_coor.y1 = H3A_PIC_OFFSET;
		isp_gen->awb_settings.awb_coor.x2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
		isp_gen->awb_settings.awb_coor.y2 = H3A_PIC_SIZE + H3A_PIC_OFFSET;
	}
	isp_gen->isp_3a_change_flags |= ISP_SET_AWB_MODE;

	//af
	mod_cfg->af_cfg.af_sap_lim = ISP_AF_DIR_TH;

	//ae
	isp_gen->ae_entity_ctx.ae_param->ae_save_delay_en = 1;
	memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.wdr_cfg[0], &param->isp_3a_settings.wdr_comm_cfg[0], ISP_WDR_COMM_CFG_MAX*sizeof(HW_U16));

	mod_cfg->mode_cfg.input_fmt = isp_gen->sensor_info.input_seq;
	mod_cfg->mode_cfg.rgb_cfg_bit = clamp(isp_gen->databit.st_pltm, 10, 12);
	mod_cfg->mode_cfg.hist0_sel = param->isp_3a_settings.ae_hist0_sel;
	mod_cfg->mode_cfg.hist1_sel = param->isp_3a_settings.ae_hist1_sel;
	mod_cfg->mode_cfg.hist0_mode = HIST_ONE_FRAME_CH0;
	mod_cfg->mode_cfg.hist1_mode = HIST_ONE_FRAME_CH0;
	mod_cfg->mode_cfg.ae0_sel = param->isp_3a_settings.ae_stat_sel;
	mod_cfg->mode_cfg.ae2_sel = param->isp_3a_settings.ae_stat2_sel;
	mod_cfg->mode_cfg.awb_sel = param->isp_3a_settings.awb_stat_sel;
	mod_cfg->mode_cfg.awb_mode = AWB_ONE_FRAME_CH0;
	if (mod_cfg->mode_cfg.ae2_sel == AE_ST_FE0_MSC) {
		ISP_ERR("ae2_sel can not set to 0.\n");
		mod_cfg->mode_cfg.ae2_sel = AE_ST_FE1_MSC;
	} else if (mod_cfg->mode_cfg.ae2_sel < mod_cfg->mode_cfg.ae0_sel) {
		ISP_ERR("ae2_sel must be > ae0_sel.\n");
		mod_cfg->mode_cfg.ae2_sel = mod_cfg->mode_cfg.ae0_sel;
	}

	//shift bit
	if (mod_cfg->mode_cfg.ae0_sel <= AE_ST_FE2_MSC) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit0 = isp_gen->databit.st_femsc[0] - 12;
	} else if (mod_cfg->mode_cfg.ae0_sel == AE_ST_MSC) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit0 = isp_gen->databit.st_msc - 12;
	} else if (mod_cfg->mode_cfg.ae0_sel == AE_ST_CCM) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit0 = 12 - isp_gen->databit.st_ccm;
	} else if (mod_cfg->mode_cfg.ae0_sel == AE_ST_CSC) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit0 = 12 - isp_gen->databit.st_csc;
	} else if (mod_cfg->mode_cfg.ae0_sel == AE_ST_DRC) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit0 = 12 - isp_gen->databit.st_drc;
	} else if (mod_cfg->mode_cfg.ae0_sel == AE_ST_CEM) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit0 = 12 - isp_gen->databit.st_cem;
	} else {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit0 = 12 - isp_gen->databit.st_cem;
		ISP_ERR("ae0_sel setting %d error.\n", mod_cfg->mode_cfg.ae0_sel);
	}
	if (mod_cfg->mode_cfg.ae2_sel <= AE_ST_FE2_MSC) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit2 = isp_gen->databit.st_femsc[1] - 12;
	} else if (mod_cfg->mode_cfg.ae2_sel == AE_ST_MSC) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit2 = isp_gen->databit.st_msc - 12;
	} else if (mod_cfg->mode_cfg.ae2_sel == AE_ST_CCM) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit2 = 12 - isp_gen->databit.st_ccm;
	} else if (mod_cfg->mode_cfg.ae2_sel == AE_ST_CSC) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit2 = 12 - isp_gen->databit.st_csc;
	} else if (mod_cfg->mode_cfg.ae2_sel == AE_ST_DRC) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit2 = 12 - isp_gen->databit.st_drc;
	} else if (mod_cfg->mode_cfg.ae2_sel == AE_ST_CEM) {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit2 = 12 - isp_gen->databit.st_cem;
	} else {
		mod_cfg->ae_cfg.ae_reg_win.shift_bit2 = 12 - isp_gen->databit.st_cem;
		ISP_ERR("ae2_sel setting %d error.\n", mod_cfg->mode_cfg.ae2_sel);
	}

	if (mod_cfg->mode_cfg.awb_sel == AWB_ST_FE_MSC) {
		mod_cfg->awb_cfg.awb_reg_win.shift_flag0 = 1;
		mod_cfg->awb_cfg.awb_reg_win.shift_bit0 = isp_gen->databit.st_femsc[0] - 12;
	} else if (mod_cfg->mode_cfg.awb_sel == AWB_ST_FPN) {
		mod_cfg->awb_cfg.awb_reg_win.shift_flag0 = 1;
		mod_cfg->awb_cfg.awb_reg_win.shift_bit0 = isp_gen->databit.st_fpn - 12;
	} else if (mod_cfg->mode_cfg.awb_sel == AWB_ST_MSC) {
		mod_cfg->awb_cfg.awb_reg_win.shift_flag0 = 1;
		mod_cfg->awb_cfg.awb_reg_win.shift_bit0 = isp_gen->databit.st_msc - 12;
	} else if (mod_cfg->mode_cfg.awb_sel == AWB_ST_PLTM) {
		mod_cfg->awb_cfg.awb_reg_win.shift_flag0 = 0;
		mod_cfg->awb_cfg.awb_reg_win.shift_bit0 = 12 - isp_gen->databit.st_pltm;
	} else {
		mod_cfg->awb_cfg.awb_reg_win.shift_flag0 = 0;
		mod_cfg->awb_cfg.awb_reg_win.shift_bit0 = 12 - isp_gen->databit.st_pltm;
		ISP_ERR("awb_sel setting %d error.\n", mod_cfg->mode_cfg.awb_sel);
	}

	if (mod_cfg->mode_cfg.hist0_sel == HIST_ST_FE_MSC) {
		mod_cfg->hist_cfg.hist0_reg_win.shift_bit0 = isp_gen->databit.st_femsc[0] - 8;
	} else if (mod_cfg->mode_cfg.hist0_sel == HIST_ST_DPC) {
		mod_cfg->hist_cfg.hist0_reg_win.shift_bit0 = isp_gen->databit.st_dpc - 8;
	} else if (mod_cfg->mode_cfg.hist0_sel == HIST_ST_MSC) {
		mod_cfg->hist_cfg.hist0_reg_win.shift_bit0 = isp_gen->databit.st_msc - 8;
	} else if (mod_cfg->mode_cfg.hist0_sel == HIST_ST_CCM) {
		mod_cfg->hist_cfg.hist0_reg_win.shift_bit0 = isp_gen->databit.st_ccm - 8;
	} else if (mod_cfg->mode_cfg.hist0_sel == HIST_ST_CSC) {
		mod_cfg->hist_cfg.hist0_reg_win.shift_bit0 = isp_gen->databit.st_csc - 8;
	} else if (mod_cfg->mode_cfg.hist0_sel == HIST_ST_DRC) {
		mod_cfg->hist_cfg.hist0_reg_win.shift_bit0 = isp_gen->databit.st_drc - 8;
	} else if (mod_cfg->mode_cfg.hist0_sel == HIST_ST_CEM) {
		mod_cfg->hist_cfg.hist0_reg_win.shift_bit0 = isp_gen->databit.st_cem - 8;
	} else {
		mod_cfg->hist_cfg.hist0_reg_win.shift_bit0 = isp_gen->databit.st_cem - 8;
		ISP_ERR("hist0_sel setting %d error.\n", mod_cfg->mode_cfg.hist0_sel);
	}

	if (mod_cfg->mode_cfg.hist1_sel == HIST_ST_FE_MSC) {
		mod_cfg->hist_cfg.hist1_reg_win.shift_bit0 = isp_gen->databit.st_femsc[1] - 8;
	} else if (mod_cfg->mode_cfg.hist1_sel == HIST_ST_DPC) {
		mod_cfg->hist_cfg.hist1_reg_win.shift_bit0 = isp_gen->databit.st_dpc - 8;
	} else if (mod_cfg->mode_cfg.hist1_sel == HIST_ST_MSC) {
		mod_cfg->hist_cfg.hist1_reg_win.shift_bit0 = isp_gen->databit.st_msc - 8;
	} else if (mod_cfg->mode_cfg.hist1_sel == HIST_ST_CCM) {
		mod_cfg->hist_cfg.hist1_reg_win.shift_bit0 = isp_gen->databit.st_ccm - 8;
	} else if (mod_cfg->mode_cfg.hist1_sel == HIST_ST_CSC) {
		mod_cfg->hist_cfg.hist1_reg_win.shift_bit0 = isp_gen->databit.st_csc - 8;
	} else if (mod_cfg->mode_cfg.hist1_sel == HIST_ST_DRC) {
		mod_cfg->hist_cfg.hist1_reg_win.shift_bit0 = isp_gen->databit.st_drc - 8;
	} else if (mod_cfg->mode_cfg.hist1_sel == HIST_ST_CEM) {
		mod_cfg->hist_cfg.hist1_reg_win.shift_bit0 = isp_gen->databit.st_cem - 8;
	} else {
		mod_cfg->hist_cfg.hist1_reg_win.shift_bit0 = isp_gen->databit.st_cem - 8;
		ISP_ERR("hist1_sel setting %d error.\n", mod_cfg->mode_cfg.hist1_sel);
	}

	config_dig_gain(isp_gen, 1024, 1024);

	//dpc
	mod_cfg->dpc_cfg.dynamic_corr_en = param->isp_tunning_settings.dpc_comm_cfg[ISP_DPC_DYNAMIC_CORR_EN];
	mod_cfg->dpc_cfg.static_corr_en = param->isp_tunning_settings.dpc_comm_cfg[ISP_DPC_STATIC_CORR_EN];
	mod_cfg->dpc_cfg.weak_mode = param->isp_tunning_settings.dpc_comm_cfg[ISP_DPC_WEAK_MODE];
	mod_cfg->dpc_cfg.sup_twinkle_en = param->isp_tunning_settings.dpc_comm_cfg[ISP_DPC_SUP_TWINKLE_EN];
	mod_cfg->dpc_cfg.static_calibrate_en = param->isp_tunning_settings.dpc_comm_cfg[ISP_DPC_STATIC_CALIBRATE_EN];
	mod_cfg->dpc_cfg.static_calibrate_type = param->isp_tunning_settings.dpc_comm_cfg[ISP_DPC_STATIC_CALIBRATE_TYPE];
	mod_cfg->dpc_cfg.static_highlight_en = param->isp_tunning_settings.dpc_comm_cfg[ISP_DPC_STATIC_CALIBRATE_HIGHTLIGHT_EN];
	mod_cfg->dpc_cfg.static_force_median_filter_en = param->isp_tunning_settings.dpc_comm_cfg[ISP_DPC_FORCE_MEDIAN_FILTER_EN];
	mod_cfg->dpc_cfg.smad_remove_idx = param->isp_tunning_settings.dpc_comm_cfg[ISP_DPC_EDGE_PROT_SCALE];
	mod_cfg->dpc_cfg.static_count_calibra = param->isp_tunning_settings.dpc_comm_cfg[ISP_DPC_STATIC_CNT_CALIBRA];
	if (mod_cfg->dpc_sdp_table != NULL) {
		HW_U32 *dpc_sdp_tbl = (HW_U32 *)mod_cfg->dpc_sdp_table;
		memcpy(dpc_sdp_tbl, &param->isp_tunning_settings.dpc_static_dead_pix_tbl[0], 1024 * sizeof(HW_U32));
	} else {
		ISP_ERR("dpc_sdp_table is NULL.\n");
	}

	//nrp
	mod_cfg->nrp_cfg.gm_neg_ratio = 0;
	if (param->isp_test_settings.nrp_en) {
		if (isp_gen->sensor_info.wdr_mode) {
			//ISP_WARN("close nrp when input data is wdr\n");
			mod_cfg->mode_cfg.gain_sel = 1;
			mod_cfg->mode_cfg.wb_sel = 1;
			mod_cfg->mode_cfg.ccm_sel = 1;
			mod_cfg->nrp_cfg.gamma_en = 0;
			mod_cfg->nrp_cfg.inv_gamma_en = 0;
			mod_cfg->nrp_cfg.blc0_en = 0;
			mod_cfg->nrp_cfg.inv_blc0_en = 0;
		} else {
			mod_cfg->mode_cfg.gain_sel = 0;
			mod_cfg->mode_cfg.wb_sel = 0;
			mod_cfg->mode_cfg.ccm_sel = 1;
			mod_cfg->nrp_cfg.gamma_en = 1;
			mod_cfg->nrp_cfg.inv_gamma_en = 1;
			if (((!mod_cfg->mode_cfg.gain_sel && (param->isp_test_settings.dig_gain_en || param->isp_test_settings.lsc_en || param->isp_test_settings.msc_en)) ||
				(!mod_cfg->mode_cfg.wb_sel && param->isp_test_settings.wb_en) || mod_cfg->nrp_cfg.gamma_en) && param->isp_test_settings.blc_en) {
				mod_cfg->nrp_cfg.blc0_en = 1;
				mod_cfg->nrp_cfg.inv_blc0_en = 1;
			} else {
				mod_cfg->nrp_cfg.blc0_en = 0;
				mod_cfg->nrp_cfg.inv_blc0_en = 0;
			}
		}
		if (!mod_cfg->mode_cfg.ccm_sel) {
			mod_cfg->nrp_cfg.blc1_en = 1;
			mod_cfg->nrp_cfg.inv_blc1_en = 1;
		} else {
			mod_cfg->nrp_cfg.blc1_en = 0;
			mod_cfg->nrp_cfg.inv_blc1_en = 0;
		}
	} else {
		mod_cfg->mode_cfg.gain_sel = 1;
		mod_cfg->mode_cfg.wb_sel = 1;
		mod_cfg->mode_cfg.ccm_sel = 2;
		mod_cfg->nrp_cfg.gamma_en = 0;
		mod_cfg->nrp_cfg.inv_gamma_en = 0;
		mod_cfg->nrp_cfg.blc0_en = 0;
		mod_cfg->nrp_cfg.inv_blc0_en = 0;
		mod_cfg->nrp_cfg.blc1_en = 0;
		mod_cfg->nrp_cfg.inv_blc1_en = 0;
	}
	//nrp-dle
	mod_cfg->nrp_cfg.dle_en = param->isp_tunning_settings.nrp_comm_cfg[ISP_NRP_DLE_EN];
	mod_cfg->nrp_cfg.dle_win_sel = param->isp_tunning_settings.nrp_comm_cfg[ISP_NRP_DLE_WIN_SEL];
	mod_cfg->nrp_cfg.dle_neg_ratio = param->isp_tunning_settings.nrp_comm_cfg[ISP_NRP_DLE_NEG_RATIO];
	mod_cfg->nrp_cfg.cb_hf_rt_lw = param->isp_tunning_settings.nrp_comm_cfg[ISP_NRP_DLE_HF_RT_LW];
	mod_cfg->nrp_cfg.cb_hf_rt_hi = param->isp_tunning_settings.nrp_comm_cfg[ISP_NRP_DLE_HF_RT_HI];
	mod_cfg->nrp_cfg.cr_hf_rt_lw = param->isp_tunning_settings.nrp_comm_cfg[ISP_NRP_DLE_HF_RT_LW];
	mod_cfg->nrp_cfg.cr_hf_rt_hi = param->isp_tunning_settings.nrp_comm_cfg[ISP_NRP_DLE_HF_RT_HI];

	//denoise
	if (isp_gen->sensor_info.width_overlayer)
		mod_cfg->bdnf_cfg.d2d_div_num = isp_gen->sensor_info.width_overlayer * isp_gen->sensor_info.sensor_height;
	else
		mod_cfg->bdnf_cfg.d2d_div_num = isp_gen->sensor_info.sensor_width * isp_gen->sensor_info.sensor_height;
	mod_cfg->bdnf_cfg.d2d_mot_info_en = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_MOT_INFO_EN];
	mod_cfg->bdnf_cfg.d2d_bnr_en = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_BLOCK_DNR_EN];
	mod_cfg->bdnf_cfg.d2d_bnr_sel = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_BLOCK_DNR_APPLY_AT];
	mod_cfg->bdnf_cfg.d2d_ll_ups_type = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_LL_SCALE_SEL];
	mod_cfg->bdnf_cfg.lyr0_nr_y_en = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_LYR0_NR_Y_EN];
	mod_cfg->bdnf_cfg.lyr1_nr_y_en = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_LYR1_NR_Y_EN];
	mod_cfg->bdnf_cfg.lyr2_nr_y_en = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_LYR2_NR_Y_EN];
	mod_cfg->bdnf_cfg.d2d_out_sel = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_OUT_SEL];
	mod_cfg->bdnf_cfg.d2d_out_mode = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_OUT_SEL_MODE];
	mod_cfg->bdnf_cfg.filtpd_y_str = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_FLTPD_Y_STR];
	mod_cfg->bdnf_cfg.filtpd_cb_str = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_FLTPD_CB_STR];
	mod_cfg->bdnf_cfg.filtpd_cr_str = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_FLTPD_CR_STR];
	mod_cfg->bdnf_cfg.cnt_ratio[0] = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_CNT_RATIO0];
	mod_cfg->bdnf_cfg.cnt_ratio[1] = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_CNT_RATIO1];
	mod_cfg->bdnf_cfg.cnt_ratio[2] = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_CNT_RATIO2];
	mod_cfg->bdnf_cfg.wdr_lm_lw_slp = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_WDR_LM_LW_SLP];
	mod_cfg->bdnf_cfg.wdr_lm_hi_slp = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_WDR_LM_HI_SLP];
	mod_cfg->bdnf_cfg.wdr_lm_max_clp = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_WDR_LM_MAX_CLIP];
	mod_cfg->bdnf_cfg.wdr_ms_lw_slp = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_WDR_MS_LW_SLP];
	mod_cfg->bdnf_cfg.wdr_ms_hi_slp = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_WDR_MS_HI_SLP];
	mod_cfg->bdnf_cfg.wdr_ms_max_clp = param->isp_tunning_settings.denoise_comm_cfg[ISP_DENOISE_WDR_MS_MAX_CLIP];

	//tdf
	mod_cfg->tdf_cfg.mot_info_init_en = 1;
	mod_cfg->tdf_cfg.d3d_ctr_sel = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_INFO_SCALE_SEL];
	mod_cfg->tdf_cfg.texture_en = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_TEXTURE_CTRL_EN];
	mod_cfg->tdf_cfg.motion_en = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOTION_CTRL_EN];
	mod_cfg->tdf_cfg.blk_dnr_en = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_BLOCK_DNR_EN];
	mod_cfg->tdf_cfg.blk_dnr_sel = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_BLOCK_DNR_APPLY_AT];
	mod_cfg->tdf_cfg.flt_out_sel = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_FILT_OUT_SEL];
	mod_cfg->tdf_cfg.d3d_mot_sel = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_SEL];
	mod_cfg->tdf_cfg.d3d_out_sel = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_OUT_SEL];
	mod_cfg->tdf_cfg.d3d_out_mode = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_OUT_SEL_MODE];
	if (isp_gen->sensor_info.width_overlayer)
		mod_cfg->tdf_cfg.kb_wnum = isp_gen->sensor_info.width_overlayer / 9;
	else
		mod_cfg->tdf_cfg.kb_wnum = isp_gen->sensor_info.sensor_width / 9;
	mod_cfg->tdf_cfg.kb_hnum = isp_gen->sensor_info.sensor_height / 9;
	mod_cfg->tdf_cfg.diff_intra_amp = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_DIFF_INTRA_AMP];
	mod_cfg->tdf_cfg.diff_inter_amp = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_DIFF_INTER_AMP];
	mod_cfg->tdf_cfg.thr_intra_amp = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_THR_INTRA_AMP];
	mod_cfg->tdf_cfg.thr_inter_amp = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_THR_INTER_AMP];
	mod_cfg->tdf_cfg.wdr_lm_hi_slp = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_WDR_LM_HI_SLP];
	mod_cfg->tdf_cfg.wdr_ms_hi_slp = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_WDR_MS_HI_SLP];
	mod_cfg->tdf_cfg.wdr_lm_lw_slp = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_WDR_LM_LW_SLP];
	mod_cfg->tdf_cfg.wdr_ms_lw_slp = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_WDR_MS_LW_SLP];
	mod_cfg->tdf_cfg.wdr_lm_max_clp = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_WDR_LM_MAX_CLP];
	mod_cfg->tdf_cfg.wdr_ms_max_clp = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_WDR_MS_MAX_CLP];
	mod_cfg->tdf_cfg.stl_stg_cth[0] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_CTH_0];
	mod_cfg->tdf_cfg.stl_stg_cth[1] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_CTH_1];
	mod_cfg->tdf_cfg.stl_stg_cth[2] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_CTH_2];
	mod_cfg->tdf_cfg.stl_stg_cth[3] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_CTH_3];
	mod_cfg->tdf_cfg.stl_stg_cth[4] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_CTH_4];
	mod_cfg->tdf_cfg.stl_stg_cth[5] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_CTH_5];
	mod_cfg->tdf_cfg.stl_stg_cth[6] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_CTH_6];
	mod_cfg->tdf_cfg.stl_stg_cth[7] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_CTH_7];
	mod_cfg->tdf_cfg.stl_stg_kth[0] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_KTH_0];
	mod_cfg->tdf_cfg.stl_stg_kth[1] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_KTH_1];
	mod_cfg->tdf_cfg.stl_stg_kth[2] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_KTH_2];
	mod_cfg->tdf_cfg.stl_stg_kth[3] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_KTH_3];
	mod_cfg->tdf_cfg.stl_stg_kth[4] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_KTH_4];
	mod_cfg->tdf_cfg.stl_stg_kth[5] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_KTH_5];
	mod_cfg->tdf_cfg.stl_stg_kth[6] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_KTH_6];
	mod_cfg->tdf_cfg.stl_stg_kth[7] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_STL_STG_KTH_7];
	mod_cfg->tdf_cfg.mot_stg_cth[0] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_CTH_0];
	mod_cfg->tdf_cfg.mot_stg_cth[1] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_CTH_1];
	mod_cfg->tdf_cfg.mot_stg_cth[2] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_CTH_2];
	mod_cfg->tdf_cfg.mot_stg_cth[3] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_CTH_3];
	mod_cfg->tdf_cfg.mot_stg_cth[4] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_CTH_4];
	mod_cfg->tdf_cfg.mot_stg_cth[5] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_CTH_5];
	mod_cfg->tdf_cfg.mot_stg_cth[6] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_CTH_6];
	mod_cfg->tdf_cfg.mot_stg_cth[7] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_CTH_7];
	mod_cfg->tdf_cfg.mot_stg_kth[0] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_KTH_0];
	mod_cfg->tdf_cfg.mot_stg_kth[1] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_KTH_1];
	mod_cfg->tdf_cfg.mot_stg_kth[2] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_KTH_2];
	mod_cfg->tdf_cfg.mot_stg_kth[3] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_KTH_3];
	mod_cfg->tdf_cfg.mot_stg_kth[4] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_KTH_4];
	mod_cfg->tdf_cfg.mot_stg_kth[5] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_KTH_5];
	mod_cfg->tdf_cfg.mot_stg_kth[6] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_KTH_6];
	mod_cfg->tdf_cfg.mot_stg_kth[7] = param->isp_tunning_settings.tdf_comm_cfg[ISP_TDF_MOT_STG_KTH_7];
	HW_U8 *tdnf_table = (HW_U8 *)mod_cfg->tdnf_table;
	for (i = 0; i < ISP_TDNF_TBL_SIZE; i++) {
		tdnf_table[8*i + 0] = isp_tdnf_df_bd_tbl[i];
	}
	memcpy(&mod_cfg->tdf_cfg.df_shp_bk[0], &isp_gen->isp_ini_cfg.isp_tunning_settings.isp_tdnf_df_shape[0], ISP_REG_TBL_LENGTH_16);
	memcpy(&mod_cfg->tdf_cfg.r_amp_bk[0], &isp_gen->isp_ini_cfg.isp_tunning_settings.isp_tdnf_ratio_amp[0], ISP_REG_TBL_LENGTH_16);
	memcpy(&mod_cfg->tdf_cfg.k_dlt_bk[0], &isp_gen->isp_ini_cfg.isp_tunning_settings.isp_tdnf_k_dlt_bk[0], ISP_REG_TBL_LENGTH_16);
	memcpy(&mod_cfg->tdf_cfg.ct_rt_bk[0], &isp_gen->isp_ini_cfg.isp_tunning_settings.isp_tdnf_ct_rt_bk[0], ISP_REG_TBL_LENGTH_16);
	memcpy(&mod_cfg->tdf_cfg.lay0_d2d0_rt_br[0], &isp_gen->isp_ini_cfg.isp_tunning_settings.isp_tdnf_lay0_d2d0_rt_br[0], ISP_REG_TBL_LENGTH_16);
	memcpy(&mod_cfg->tdf_cfg.lay1_d2d0_rt_br[0], &isp_gen->isp_ini_cfg.isp_tunning_settings.isp_tdnf_lay1_d2d0_rt_br[0], ISP_REG_TBL_LENGTH_16);

	//CFA
	mod_cfg->mode_cfg.dmsc_mode = DMSC_NORMAL;
	mod_cfg->cfa_cfg.cfa_grad_th = param->isp_tunning_settings.grad_th;
	mod_cfg->cfa_cfg.cfa_dir_v_th = param->isp_tunning_settings.dir_v_th;
	mod_cfg->cfa_cfg.cfa_dir_h_th = param->isp_tunning_settings.dir_h_th;
	mod_cfg->cfa_cfg.res_smth_high = param->isp_tunning_settings.res_smth_high;
	mod_cfg->cfa_cfg.res_smth_low = param->isp_tunning_settings.res_smth_low;
	mod_cfg->cfa_cfg.res_high_th = param->isp_tunning_settings.res_high_th;
	mod_cfg->cfa_cfg.res_low_th = param->isp_tunning_settings.res_low_th;
	mod_cfg->cfa_cfg.res_dir_a = param->isp_tunning_settings.res_dir_a;
	mod_cfg->cfa_cfg.res_dir_d = param->isp_tunning_settings.res_dir_d;
	mod_cfg->cfa_cfg.res_dir_v = param->isp_tunning_settings.res_dir_v;
	mod_cfg->cfa_cfg.res_dir_h = param->isp_tunning_settings.res_dir_h;

	//ccm
	if(!isp_gen->initial_cfg.isp_ctx_save_init_flag)
		mod_cfg->rgb2rgb_cfg.color_matrix = param->isp_tunning_settings.color_matrix_ini[0];

	//ctc
	mod_cfg->ctc_cfg.ctc_low_th = param->isp_tunning_settings.ctc_low_th;
	mod_cfg->ctc_cfg.ctc_high_th = param->isp_tunning_settings.ctc_high_th;
	if (param->isp_tunning_settings.ctc_low_th > param->isp_tunning_settings.ctc_low_th_min) {
		mod_cfg->ctc_cfg.ctc_low_th_slope = 65520 / (param->isp_tunning_settings.ctc_low_th - param->isp_tunning_settings.ctc_low_th_min);
	} else {
		ISP_ERR("ctc low slope error. need ctc_low_th > ctc_low_th_min\n");
		mod_cfg->ctc_cfg.ctc_low_th_slope = 65520;
	}
	if (param->isp_tunning_settings.ctc_high_th_max > param->isp_tunning_settings.ctc_high_th) {
		mod_cfg->ctc_cfg.ctc_high_th_slope = 65520 / (param->isp_tunning_settings.ctc_high_th_max - param->isp_tunning_settings.ctc_high_th);
	} else {
		ISP_ERR("ctc high slope error. need ctc_high_th_max > ctc_high_th\n");
		mod_cfg->ctc_cfg.ctc_high_th_slope = 65520;
	}
	mod_cfg->ctc_cfg.ctc_dir_wt = param->isp_tunning_settings.ctc_dir_wt;//64;
	mod_cfg->ctc_cfg.ctc_dir_th = param->isp_tunning_settings.ctc_dir_th;//80;

	//pltm
	if(!isp_gen->initial_cfg.isp_ctx_save_init_flag) {
		mod_cfg->pltm_cfg.strength = 256;
		mod_cfg->pltm_cfg.nrm_ratio = 2048;
	}
	mod_cfg->pltm_cfg.gtm_en = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_GTM_EN];
	mod_cfg->pltm_cfg.lft_en = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_LTF_EN];
	mod_cfg->pltm_cfg.dsc_en = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_DSC_EN];
	mod_cfg->pltm_cfg.dcc_en = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_DCC_EN];
	mod_cfg->pltm_cfg.dsc_shf_bit = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_DSC_SHF_BIT];
	mod_cfg->pltm_cfg.dsc_lw_th = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_DSC_LW_TH];
	mod_cfg->pltm_cfg.dsc_hi_th = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_DSC_HI_TH];
	mod_cfg->pltm_cfg.dcc_shf_bit = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_DCC_SHF_BIT];
	mod_cfg->pltm_cfg.dcc_lw_th = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_DCC_LW_TH];
	mod_cfg->pltm_cfg.dcc_hi_th = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_DCC_HI_TH];
	mod_cfg->pltm_cfg.mgc_smth = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_MGC_INT_SMTH];
	mod_cfg->pltm_cfg.mgc_lum_adpt = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_MGC_LUM_ADPT];
	mod_cfg->pltm_cfg.sts_ceil_slp = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_STS_CEIL_SLP];
	mod_cfg->pltm_cfg.sts_floor_slp = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_STS_FLOOR_SLP];
	mod_cfg->pltm_cfg.sts_gd_ratio = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_STS_GD_RT];
	mod_cfg->pltm_cfg.adjk_crct_ratio = param->isp_tunning_settings.pltm_cfg[ISP_PLTM_ADJK_CRCT_RT];
	mod_cfg->pltm_cfg.sts_flt_stren[0] = 384;//384
	mod_cfg->pltm_cfg.sts_flt_stren[1] = 256;//256
	mod_cfg->pltm_cfg.sts_flt_stren[2] = 64;//128
	mod_cfg->pltm_cfg.adj1_asym_ratio = 0;
	memcpy(&mod_cfg->pltm_cfg.stat_gd_cv[0], &param->isp_tunning_settings.isp_pltm_stat_gd_cv[0], 15 * sizeof(HW_U8));
	memcpy(&mod_cfg->pltm_cfg.adj_k_df_cv[0], &param->isp_tunning_settings.isp_pltm_df_cv[0], ISP_REG_TBL_LENGTH_33 * sizeof(HW_U8));

	//gca
	mod_cfg->mode_cfg.gca_mode = param->isp_tunning_settings.gca_cfg[ISP_GCA_MODE];
	mod_cfg->gca_cfg.gca_block_w = param->isp_tunning_settings.gca_cfg[ISP_GCA_BLOCK_W];
	mod_cfg->gca_cfg.gca_block_h = param->isp_tunning_settings.gca_cfg[ISP_GCA_BLOCK_H];
	mod_cfg->gca_cfg.gca_div_num_w = 16384 / mod_cfg->gca_cfg.gca_block_w;
	mod_cfg->gca_cfg.gca_div_num_h = 16384 / mod_cfg->gca_cfg.gca_block_h;
	mod_cfg->gca_cfg.gca_start_w = param->isp_tunning_settings.gca_cfg[ISP_GCA_START_W];
	mod_cfg->gca_cfg.gca_start_h = param->isp_tunning_settings.gca_cfg[ISP_GCA_START_H];
	memcpy(&mod_cfg->gca_cfg.gca_hor_r_offset[0], &param->isp_tunning_settings.gca_hor_r_offset[0], 825 * sizeof(HW_S8));
	memcpy(&mod_cfg->gca_cfg.gca_ver_r_offset[0], &param->isp_tunning_settings.gca_ver_r_offset[0], 825 * sizeof(HW_S8));
	memcpy(&mod_cfg->gca_cfg.gca_hor_b_offset[0], &param->isp_tunning_settings.gca_hor_b_offset[0], 825 * sizeof(HW_S8));
	memcpy(&mod_cfg->gca_cfg.gca_ver_b_offset[0], &param->isp_tunning_settings.gca_ver_b_offset[0], 825 * sizeof(HW_S8));

	//lca
	mod_cfg->lca_cfg.lca_grad_gain1_en = param->isp_tunning_settings.lca_comm_cfg[ISP_LCA_GRAD_GAIN1_EN];
	mod_cfg->lca_cfg.lca_grad_gain2_en = param->isp_tunning_settings.lca_comm_cfg[ISP_LCA_GRAD_GAIN2_EN];
	mod_cfg->lca_cfg.lca_clr_gth = param->isp_tunning_settings.lca_comm_cfg[ISP_LCA_CLR_GTH];
	mod_cfg->lca_cfg.lca_clrs_lum_th = param->isp_tunning_settings.lca_comm_cfg[ISP_LCA_CLRS_LUM_TH];
	mod_cfg->lca_cfg.lca_pf_clrc_ratio = param->isp_tunning_settings.lca_comm_cfg[ISP_LCA_PF_CLRC_RATIO];
	mod_cfg->lca_cfg.lca_gf_clrc_ratio = param->isp_tunning_settings.lca_comm_cfg[ISP_LCA_GF_CLRC_RATIO];
	mod_cfg->lca_cfg.lca_pf_decr_ratio = param->isp_tunning_settings.lca_comm_cfg[ISP_LCA_PF_DECR_RATIO];
	for(i = 0; i < 9; i++) {
		for(j = 0; j < 4; j++) {
			if((4*i+j) >= ISP_REG_TBL_LENGTH_33)
				break;
			mod_cfg->lca_cfg.lca_pf_satu_lut[4*i+j] = param->isp_tunning_settings.lca_pf_satu_lut[4*i+j];
		}
	}
	for(i = 0; i < 9; i++) {
		for(j = 0; j < 4; j++) {
			if((4*i+j) >= ISP_REG_TBL_LENGTH_33)
				break;
			mod_cfg->lca_cfg.lca_gf_satu_lut[4*i+j] = param->isp_tunning_settings.lca_gf_satu_lut[4*i+j];
		}
	}

	// lsc
	if (param->isp_test_settings.lsc_en) {
		mod_cfg->mode_cfg.rsc_mode = param->isp_tunning_settings.lsc_mode;
	}

	// msc
	if (param->isp_test_settings.msc_en) {
		for (i = 0; i < ISP_MSC_TBL_LUT_SIZE; i++) {
			msc_w_count += param->isp_tunning_settings.msc_blw_lut[i];
			msc_h_count += param->isp_tunning_settings.msc_blh_lut[i];
		}
		if (isp_gen->sensor_info.width_overlayer) {
			if (msc_w_count != isp_gen->sensor_info.width_overlayer / 2 || msc_h_count != isp_gen->sensor_info.sensor_height / 2) {
				ISP_WARN("msc_blw_lut or msc_blh_lut abnormal, can not enable msc.(%d,%d)(%d,%d)\n", msc_w_count, msc_h_count,
					isp_gen->sensor_info.width_overlayer / 2, isp_gen->sensor_info.sensor_height / 2);
				ISP_CTX_MODULE_EN(0, ISP_FEATURES_MSC);
			}
		} else {
			if (msc_w_count != isp_gen->sensor_info.sensor_width / 2 || msc_h_count != isp_gen->sensor_info.sensor_height / 2) {
				ISP_WARN("msc_blw_lut or msc_blh_lut abnormal, can not enable msc.(%d,%d)(%d,%d)\n", msc_w_count, msc_h_count,
					isp_gen->sensor_info.sensor_width / 2, isp_gen->sensor_info.sensor_height / 2);
				ISP_CTX_MODULE_EN(0, ISP_FEATURES_MSC);
			}
		}

		mod_cfg->mode_cfg.msc_mode = param->isp_tunning_settings.msc_mode;
		for (i = 0; i < ISP_MSC_TBL_LUT_SIZE; i++) {
			mod_cfg->msc_cfg.msc_blw_lut[i] = clamp(param->isp_tunning_settings.msc_blw_lut[i], 2, 1023);
		}
		for (i = 0; i < ISP_MSC_TBL_LUT_SIZE; i++) {
			mod_cfg->msc_cfg.msc_blh_lut[i] = clamp(param->isp_tunning_settings.msc_blh_lut[i], 2, 1023);
		}
		if (param->isp_tunning_settings.msc_mode >= 4) {
			mod_cfg->msc_cfg.msc_blw_dlt_lut[0] = clamp(4096/max(mod_cfg->msc_cfg.msc_blw_lut[0], 1), 0, 4095);
			mod_cfg->msc_cfg.msc_blw_dlt_lut[ISP_MSC_TBL_LUT_DLT_SIZE -1] = clamp(4096/max(mod_cfg->msc_cfg.msc_blw_lut[ISP_MSC_TBL_LUT_SIZE-1], 1), 4, 2048);
			for (i = 1; i < ISP_MSC_TBL_LUT_DLT_SIZE - 1; i++) {
				mod_cfg->msc_cfg.msc_blw_dlt_lut[i] = clamp(8192/max(mod_cfg->msc_cfg.msc_blw_lut[i] + mod_cfg->msc_cfg.msc_blw_lut[i-1], 1), 4, 2048);
			}
			mod_cfg->msc_cfg.msc_blh_dlt_lut[0] = clamp(4096/max(mod_cfg->msc_cfg.msc_blh_lut[0], 1), 4, 2048);
			mod_cfg->msc_cfg.msc_blh_dlt_lut[ISP_MSC_TBL_LUT_DLT_SIZE -1] = clamp(4096/max(mod_cfg->msc_cfg.msc_blh_lut[ISP_MSC_TBL_LUT_SIZE-1], 1), 4, 2048);
			for(i = 1; i < ISP_MSC_TBL_LUT_DLT_SIZE - 1; i++) {
				mod_cfg->msc_cfg.msc_blh_dlt_lut[i] = clamp(8192/max(mod_cfg->msc_cfg.msc_blh_lut[i] + mod_cfg->msc_cfg.msc_blh_lut[i-1], 1), 4, 2048);
			}
		} else {
			mod_cfg->msc_cfg.msc_blw_dlt_lut[0] = clamp(4096/max(mod_cfg->msc_cfg.msc_blw_lut[0], 1), 4, 2048);
			mod_cfg->msc_cfg.msc_blw_dlt_lut[8] = clamp(4096/max(mod_cfg->msc_cfg.msc_blw_lut[7], 1), 4, 2048);
			for (i = 1; i < 8; i++) {
				mod_cfg->msc_cfg.msc_blw_dlt_lut[i] = clamp(8192/max(mod_cfg->msc_cfg.msc_blw_lut[i] + mod_cfg->msc_cfg.msc_blw_lut[i-1], 1), 4, 2048);
			}
			mod_cfg->msc_cfg.msc_blh_dlt_lut[0] = clamp(4096/max(mod_cfg->msc_cfg.msc_blh_lut[0], 1), 4, 2048);
			mod_cfg->msc_cfg.msc_blh_dlt_lut[8] = clamp(4096/max(mod_cfg->msc_cfg.msc_blh_lut[7], 1), 4, 2048);
			for(i = 1; i < 8; i++) {
				mod_cfg->msc_cfg.msc_blh_dlt_lut[i] = clamp(8192/max(mod_cfg->msc_cfg.msc_blh_lut[i] + mod_cfg->msc_cfg.msc_blh_lut[i-1], 1), 4, 2048);
			}
		}
	}

	//fpn
	if (param->isp_test_settings.fpn_en) {
		mod_cfg->fpn_cfg.fpn_pfpn_en = param->isp_tunning_settings.fpn_pfpn_en;
		mod_cfg->fpn_cfg.fpn_cfpn_en = param->isp_tunning_settings.fpn_cfpn_en;
		mod_cfg->fpn_cfg.fpn_pfpn_cluster_size = param->isp_tunning_settings.fpn_pfpn_cluster_size;
		memcpy(&mod_cfg->fpn_cfg.fpn_pfpn_phase_lut[0], &param->isp_tunning_settings.fpn_pfpn_phase_lut[0], ISP_PFPN_TBL_SIZE * sizeof(HW_S8));
		memcpy(&mod_cfg->fpn_cfg.fpn_pfpn_period_lut[0], &param->isp_tunning_settings.fpn_pfpn_period_lut[0], ISP_PFPN_TBL_SIZE * sizeof(HW_U8));
		memcpy(&mod_cfg->fpn_cfg.fpn_pfpn_offset_lut[0], &param->isp_tunning_settings.fpn_pfpn_offset_lut[0], ISP_PFPN_TBL_SIZE * sizeof(HW_S8));
		//memcpy(&mod_cfg->fpn_cfg.fpn_cfpn_coeff_lut[0], &param->isp_tunning_settings.fpn_cfpn_coeff_lut[0], ISP_REG_TBL_LENGTH_17 * sizeof(HW_U8));
		memcpy(&mod_cfg->fpn_cfg.fpn_pfpn_scale_coeff_lut[0], &param->isp_tunning_settings.fpn_pfpn_scale_coeff_lut[0], ISP_PFPN_TBL_SIZE * sizeof(HW_U8));
		if (mod_cfg->fpn_table != NULL) {
			HW_U8 *fpn_cfpn_gain_corr_tbl = mod_cfg->fpn_table;
			memcpy(fpn_cfpn_gain_corr_tbl, &param->isp_tunning_settings.fpn_cfpn_gain_corr_tbl[0], ISP_CFPN_GAIN_CORR_TBL_SIZE * sizeof(HW_U8));
		} else {
			ISP_ERR("fpn_table is NULL.\n");
		}
	}

	// update otp infomation
	if (isp_gen->sensor_otp.otp_enable) {
		if (isp_gen->sensor_otp.otp_info && isp_gen->sensor_otp.pmsc_table &&
			isp_gen->sensor_otp.pwb_table && isp_gen->sensor_otp.paf_table) {
			/* msc */
			if (isp_gen->stitch_mode == STITCH_2IN1_LINEAR) {
				for(i = 0; i < OTP_MSC_SIZE_2IN1; i++) {
					isp_gen->sensor_otp.otp_info->msc_golden_ratio[i] = (float)max(isp_gen->sensor_otp.pmsc_table[i], 1) / max(msc_golden[i], 1);
				}
				isp_gen->sensor_otp.otp_info->msc_r_ratio = (float)max(isp_gen->sensor_otp.pmsc_table[0] + isp_gen->sensor_otp.pmsc_table[OTP_MSC_SIZE + 15] + isp_gen->sensor_otp.pmsc_table[15*16] + isp_gen->sensor_otp.pmsc_table[OTP_MSC_SIZE + 16*16 - 1], 1) /
					max(msc_golden[0] + msc_golden[OTP_MSC_SIZE + 15] + msc_golden[15*16] + msc_golden[OTP_MSC_SIZE + 16*16 - 1], 1);
			} else {
				for(i = 0; i < OTP_MSC_SIZE; i++) {
					isp_gen->sensor_otp.otp_info->msc_golden_ratio[i] = (float)max(isp_gen->sensor_otp.pmsc_table[i], 1) / max(msc_golden[i], 1);
				}
				isp_gen->sensor_otp.otp_info->msc_r_ratio = (float)max(isp_gen->sensor_otp.pmsc_table[0] + isp_gen->sensor_otp.pmsc_table[15] + isp_gen->sensor_otp.pmsc_table[15*16] + isp_gen->sensor_otp.pmsc_table[16*16 - 1], 1) /
					max(msc_golden[0] + msc_golden[15] + msc_golden[15*16] + msc_golden[16*16 - 1], 1);
			}
			for (i = 0; i < OTP_MSC_SIZE / 3; i++) {
				if (isp_gen->sensor_otp.otp_info->msc_r_ratio > 1.0) {
					isp_gen->sensor_otp.otp_info->msc_golden_flag[i] = 1;
				} else {
					isp_gen->sensor_otp.otp_info->msc_golden_flag[i] = 0;
				}
			}
			//printf("isp%d ratio\n", isp_gen->isp_id);
			//for(i = 0; i < OTP_MSC_SIZE; i++) {
			//	if (i % 16 == 0)
			//		printf("\n");
			//	printf("%.4f, ", isp_gen->sensor_otp.otp_info->msc_golden_ratio[i]);
			//}
			//printf("\n");

			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[0] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[1] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[2] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[3] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[4] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[5] = 0;// more less more green

			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[0] = 0;// more less more red
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[1] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[2] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[3] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[4] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[5] = 0;
#if 0
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[0] = 5;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[1] = 5;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[2] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[3] = 10;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[4] = 11;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio[5] = 11;// more less more green

			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[0] = -5;// more less more red
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[1] = -5;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[2] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[3] = 0;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[4] = -6;
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[5] = -8;
#endif
#if 0
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[0] = isp_gen->isp_ini_cfg.isp_3a_settings.af_tolerance_value_tbl[0];
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[1] = isp_gen->isp_ini_cfg.isp_3a_settings.af_tolerance_value_tbl[1];
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[2] = isp_gen->isp_ini_cfg.isp_3a_settings.af_tolerance_value_tbl[2];
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[3] = isp_gen->isp_ini_cfg.isp_3a_settings.af_tolerance_value_tbl[3];
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[4] = isp_gen->isp_ini_cfg.isp_3a_settings.af_tolerance_value_tbl[4];
			isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[5] = isp_gen->isp_ini_cfg.isp_3a_settings.af_tolerance_value_tbl[5];

			ISP_LIB_LOG(ISP_LOG_LSC, "%f, %f, %f, %f, %f, %f. \n",
				isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[0],
				isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[1],
				isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[2],
				isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[3],
				isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[4],
				isp_gen->sensor_otp.otp_info->msc_adjust_ratio_less[5]);
#endif

			/* wb */
			for(i = 0; i < ISP_RAW_CH_MAX; i++) {
				ISP_LIB_LOG(ISP_LOG_AWB, "awb corner :%5d, golden: %d. \n", isp_gen->sensor_otp.pwb_table[i], isp_gen->sensor_otp.pwb_table[i+4]);
			}
			isp_gen->sensor_otp.otp_info->wb_golden_ratio[0] = (float)max(isp_gen->sensor_otp.pwb_table[0], 1) / (float)max(isp_gen->sensor_otp.pwb_table[0+4], 1);
			isp_gen->sensor_otp.otp_info->wb_golden_ratio[1] = (float)max(isp_gen->sensor_otp.pwb_table[1] + isp_gen->sensor_otp.pwb_table[2], 1)
				/ (float)max(isp_gen->sensor_otp.pwb_table[1+4] + isp_gen->sensor_otp.pwb_table[2+4], 1);
			isp_gen->sensor_otp.otp_info->wb_golden_ratio[2] = (float)max(isp_gen->sensor_otp.pwb_table[3], 1) / (float)max(isp_gen->sensor_otp.pwb_table[3+4], 1);

			ISP_LIB_LOG(ISP_LOG_AWB, "awb otp ratio r :%5f, g: %5f, b: %5f. \n", isp_gen->sensor_otp.otp_info->wb_golden_ratio[0], isp_gen->sensor_otp.otp_info->wb_golden_ratio[1], isp_gen->sensor_otp.otp_info->wb_golden_ratio[2]);

			for(i = 0; i < param->isp_3a_settings.awb_light_num; i++) {
				ISP_LIB_LOG(ISP_LOG_AWB, "Before awb otp adjust %5d %5d %5d \n",param->isp_3a_settings.awb_light_info[10*i + 0], param->isp_3a_settings.awb_light_info[10*i + 1], param->isp_3a_settings.awb_light_info[10*i + 2]);
				param->isp_3a_settings.awb_light_info[10*i + 0] = (HW_S32)(param->isp_3a_settings.awb_light_info[10*i + 0]*isp_gen->sensor_otp.otp_info->wb_golden_ratio[0]);
				param->isp_3a_settings.awb_light_info[10*i + 1] = (HW_S32)(param->isp_3a_settings.awb_light_info[10*i + 1]*isp_gen->sensor_otp.otp_info->wb_golden_ratio[1]);
				param->isp_3a_settings.awb_light_info[10*i + 2] = (HW_S32)(param->isp_3a_settings.awb_light_info[10*i + 2]*isp_gen->sensor_otp.otp_info->wb_golden_ratio[2]);
				ISP_LIB_LOG(ISP_LOG_AWB, "Before awb otp adjust %5d %5d %5d \n",param->isp_3a_settings.awb_light_info[10*i + 0], param->isp_3a_settings.awb_light_info[10*i + 1], param->isp_3a_settings.awb_light_info[10*i + 2]);
			}

			/* af */
			if (param->isp_test_settings.af_en) {
				if ((!isp_gen->sensor_otp.paf_table[0] && !isp_gen->sensor_otp.paf_table[1]) || (isp_gen->sensor_otp.paf_table[1] > isp_gen->sensor_otp.paf_table[0]) ||
					(isp_gen->sensor_otp.paf_table[0] > 1023) || (isp_gen->sensor_otp.paf_table[1] > 1023) ||
					(!af_golden[0] && !af_golden[1]) || (af_golden[1] > af_golden[0]) || (af_golden[0] > 1023) || (af_golden[1] > 1023)) {
					ISP_PRINT("AF_OTP data failed, disable AF_OTP. (gd_max = %d, gd_min = %d, otp_max = %d, otp_min = %d)\n",
						af_golden[0], af_golden[1], isp_gen->sensor_otp.paf_table[0], isp_gen->sensor_otp.paf_table[1]);
					isp_gen->sensor_otp.otp_info->af_max_code_offset = 0;
					isp_gen->sensor_otp.otp_info->af_min_code_offset = 0;
				} else {
					isp_gen->sensor_otp.otp_info->af_max_code_offset = (int)isp_gen->sensor_otp.paf_table[0] - af_golden[0];
					isp_gen->sensor_otp.otp_info->af_min_code_offset = (int)isp_gen->sensor_otp.paf_table[1] - af_golden[1];
					ISP_LIB_LOG(ISP_LOG_AF, "otp af max offset = %d, af min offset = %d. \n", isp_gen->sensor_otp.otp_info->af_max_code_offset, isp_gen->sensor_otp.otp_info->af_min_code_offset);
				}
			} else {
				isp_gen->sensor_otp.otp_info->af_max_code_offset = 0;
				isp_gen->sensor_otp.otp_info->af_min_code_offset = 0;
			}
		} else {
			ISP_ERR("otp enable, buf otp pointer error, disable OTP.(otp_info=%p, pmsc_table=%p, pwb_table=%p, paf_table%p)\n", isp_gen->sensor_otp.otp_info,
				isp_gen->sensor_otp.pmsc_table, isp_gen->sensor_otp.pwb_table, isp_gen->sensor_otp.paf_table);
			isp_gen->sensor_otp.otp_enable = 0;
		}
	}

	/*sharp*/
	mod_cfg->sharp_cfg.txt_info_init_en = 1;
	mod_cfg->sharp_cfg.txt_info_intp_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_TXT_INFO_EN];
	mod_cfg->sharp_cfg.mot_info_intp_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_MOT_INFO_EN];
	mod_cfg->sharp_cfg.dir_hs_val_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_HS_VAL_CV_EN];
	mod_cfg->sharp_cfg.dir_ms_val_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_MS_VAL_CV_EN];
	mod_cfg->sharp_cfg.dir_ls_val_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_LS_VAL_CV_EN];
	mod_cfg->sharp_cfg.dir_hs_lum_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_HS_LUM_CV_EN];
	mod_cfg->sharp_cfg.dir_ms_lum_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_MS_LUM_CV_EN];
	mod_cfg->sharp_cfg.dir_ls_lum_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_LS_LUM_CV_EN];
	mod_cfg->sharp_cfg.ndir_hs_val_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_HS_VAL_CV_EN];
	mod_cfg->sharp_cfg.ndir_ms_val_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_MS_VAL_CV_EN];
	mod_cfg->sharp_cfg.ndir_ls_val_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_LS_VAL_CV_EN];
	mod_cfg->sharp_cfg.ndir_hs_lum_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_HS_LUM_CV_EN];
	mod_cfg->sharp_cfg.ndir_ms_lum_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_MS_LUM_CV_EN];
	mod_cfg->sharp_cfg.ndir_ls_lum_cv_en = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_LS_LUM_CV_EN];
	mod_cfg->sharp_cfg.val_shift = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_SHARP_SENSITIVE];
	mod_cfg->sharp_cfg.out_sel = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_OUT_SEL];
	mod_cfg->sharp_cfg.stat_src = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_STAT_SRC];
	mod_cfg->sharp_cfg.stat_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_STAT_RATIO];
	mod_cfg->sharp_cfg.hs_aa_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_HS_AA_RATIO];
	mod_cfg->sharp_cfg.hs_at_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_HS_AT_RATIO];
	mod_cfg->sharp_cfg.hsv_satu_slope = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_HSV_SATU_SLOPE];
	mod_cfg->sharp_cfg.mot_sens_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_MOT_SENS_RATIO];
	mod_cfg->sharp_cfg.dir_hs_vn_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_HS_VN_RATIO];
	mod_cfg->sharp_cfg.dir_ms_vn_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_MS_VN_RATIO];
	mod_cfg->sharp_cfg.dir_ls_vn_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_LS_VN_RATIO];
	mod_cfg->sharp_cfg.dir_hs_nms_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_HS_NMS_RATIO];
	mod_cfg->sharp_cfg.dir_ms_nms_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_MS_NMS_RATIO];
	mod_cfg->sharp_cfg.dir_hs_nms_lw_clip = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_HS_NMS_LW_CLIP];
	mod_cfg->sharp_cfg.dir_ms_nms_lw_clip = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_DIR_MS_NMS_LW_CLIP];
	mod_cfg->sharp_cfg.ndir_hs_edge_slope = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_HS_EDGE_SLOPE];
	mod_cfg->sharp_cfg.ndir_ms_edge_slope = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_MS_EDGE_SLOPE];
	mod_cfg->sharp_cfg.ndir_ls_edge_slope = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_LS_EDGE_SLOPE];
	mod_cfg->sharp_cfg.ndir_hs_flat_slope = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_HS_FLAT_SLOPE];
	mod_cfg->sharp_cfg.ndir_ms_flat_slope = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_MS_FLAT_SLOPE];
	mod_cfg->sharp_cfg.ndir_ls_flat_slope = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_LS_FLAT_SLOPE];
	mod_cfg->sharp_cfg.ndir_hs_vn_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_HS_VN_RATIO];
	mod_cfg->sharp_cfg.ndir_ms_vn_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_MS_VN_RATIO];
	mod_cfg->sharp_cfg.ndir_ls_vn_ratio = param->isp_tunning_settings.sharp_comm_cfg[ISP_SHARP_NDIR_LS_VN_RATIO];
	memcpy(&mod_cfg->sharp_cfg.sharp_hs_value[0], &param->isp_tunning_settings.isp_sharp_hs_value[0],
		ISP_REG_TBL_LENGTH_32 * sizeof(HW_U16));
	memcpy(&mod_cfg->sharp_cfg.sharp_ms_value[0], &param->isp_tunning_settings.isp_sharp_ms_value[0],
		ISP_REG_TBL_LENGTH_32 * sizeof(HW_U16));
	memcpy(&mod_cfg->sharp_cfg.sharp_ls_value[0], &param->isp_tunning_settings.isp_sharp_ls_value[0],
		ISP_REG_TBL_LENGTH_32 * sizeof(HW_U16));
	memcpy(&mod_cfg->sharp_cfg.sharp_hsv[0], &param->isp_tunning_settings.isp_sharp_hsv[0],
		46 * sizeof(HW_U16));

#ifdef USE_ENCPP
	/*encpp_top*/
	isp_gen->encpp_top_cfg.ispbe_out_sel = param->isp_tunning_settings.encpp_top_comm_cfg[ENCPP_TOP_ISPBE_OUT_SEL];
	isp_gen->encpp_top_cfg.texture_iir_en = param->isp_tunning_settings.encpp_top_comm_cfg[ENCPP_TOP_TEXTURE_IIR_EN];
	isp_gen->encpp_top_cfg.texture_iir_stren = param->isp_tunning_settings.encpp_top_comm_cfg[ENCPP_TOP_TEXTURE_IIR_STREN];
	isp_gen->encpp_top_cfg.motion_iir_en = param->isp_tunning_settings.encpp_top_comm_cfg[ENCPP_TOP_MOTION_IIR_EN];
	isp_gen->encpp_top_cfg.motion_iir_stren = param->isp_tunning_settings.encpp_top_comm_cfg[ENCPP_TOP_MOTION_IIR_STREN];
	isp_gen->encpp_top_cfg.sharp_en = param->isp_test_settings.encpp_sharp_en;
	isp_gen->encpp_top_cfg.ldci_en = param->isp_test_settings.encpp_ldci_en;
	isp_gen->encpp_top_cfg.mot_sens_ratio = param->isp_tunning_settings.encpp_top_comm_cfg[ENCPP_TOP_MOT_SENS_RATIO];
	memcpy(&isp_gen->encpp_top_cfg.gbl_satu_adj_lut[0], &param->isp_tunning_settings.encpp_gbl_satu_adj_lut[0], ISP_REG_TBL_LENGTH_16 * sizeof(HW_U16));

	/*encpp sharp*/
	isp_gen->encpp_sharp_cfg.txt_info_intp_en = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_TXT_INFO_EN];
	isp_gen->encpp_sharp_cfg.mot_info_intp_en = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_MOT_INFO_EN];
	isp_gen->encpp_sharp_cfg.dir_hs_val_cv_en = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_DIR_HS_VAL_CV_EN];
	isp_gen->encpp_sharp_cfg.dir_ms_val_cv_en = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_DIR_MS_VAL_CV_EN];
	isp_gen->encpp_sharp_cfg.dir_hs_lum_cv_en = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_DIR_HS_LUM_CV_EN];
	isp_gen->encpp_sharp_cfg.dir_ms_lum_cv_en = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_DIR_MS_LUM_CV_EN];
	isp_gen->encpp_sharp_cfg.ndir_hs_val_cv_en = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_NDIR_HS_VAL_CV_EN];
	isp_gen->encpp_sharp_cfg.ndir_ms_val_cv_en = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_NDIR_MS_VAL_CV_EN];
	isp_gen->encpp_sharp_cfg.ndir_hs_lum_cv_en = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_NDIR_HS_LUM_CV_EN];
	isp_gen->encpp_sharp_cfg.ndir_ms_lum_cv_en = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_NDIR_MS_LUM_CV_EN];
	isp_gen->encpp_sharp_cfg.val_shift = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_SHARP_SENSITIVE];
	isp_gen->encpp_sharp_cfg.out_sel = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_OUT_SEL];
	isp_gen->encpp_sharp_cfg.stat_src = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_STAT_SRC];
	isp_gen->encpp_sharp_cfg.hs_aa_ratio = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_HS_AA_RATIO];
	isp_gen->encpp_sharp_cfg.hs_at_ratio = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_HS_AT_RATIO];
	isp_gen->encpp_sharp_cfg.hsv_satu_slope = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_HSV_SATU_SLOPE];
	isp_gen->encpp_sharp_cfg.dir_hs_vn_ratio = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_DIR_HS_VN_RATIO];
	isp_gen->encpp_sharp_cfg.dir_ms_vn_ratio = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_DIR_MS_VN_RATIO];
	isp_gen->encpp_sharp_cfg.dir_hs_nms_ratio = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_DIR_HS_NMS_RATIO];
	isp_gen->encpp_sharp_cfg.dir_ms_nms_ratio = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_DIR_MS_NMS_RATIO];
	isp_gen->encpp_sharp_cfg.dir_hs_nms_lw_clip = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_DIR_HS_NMS_LW_CLIP];
	isp_gen->encpp_sharp_cfg.dir_ms_nms_lw_clip = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_DIR_MS_NMS_LW_CLIP];
	isp_gen->encpp_sharp_cfg.ndir_hs_edge_slope = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_NDIR_HS_EDGE_SLOPE];
	isp_gen->encpp_sharp_cfg.ndir_ms_edge_slope = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_NDIR_MS_EDGE_SLOPE];
	isp_gen->encpp_sharp_cfg.ndir_hs_flat_slope = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_NDIR_HS_FLAT_SLOPE];
	isp_gen->encpp_sharp_cfg.ndir_ms_flat_slope = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_NDIR_MS_FLAT_SLOPE];
	isp_gen->encpp_sharp_cfg.ndir_hs_vn_ratio = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_NDIR_HS_VN_RATIO];
	isp_gen->encpp_sharp_cfg.ndir_ms_vn_ratio = param->isp_tunning_settings.encpp_sharp_comm_cfg[ENCPP_SHARP_NDIR_MS_VN_RATIO];
	memcpy(&isp_gen->encpp_sharp_cfg.sharp_hs_value[0], &param->isp_tunning_settings.encpp_sharp_hs_value[0],
		ISP_REG_TBL_LENGTH_32 * sizeof(HW_U16));
	memcpy(&isp_gen->encpp_sharp_cfg.sharp_ms_value[0], &param->isp_tunning_settings.encpp_sharp_ms_value[0],
		ISP_REG_TBL_LENGTH_32 * sizeof(HW_U16));
	memcpy(&isp_gen->encpp_sharp_cfg.sharp_hsv[0], &param->isp_tunning_settings.encpp_sharp_hsv[0],
		46 * sizeof(HW_U16));
	memcpy(&isp_gen->encpp_sharp_cfg.sharp_ls_map_lut[0], &param->isp_tunning_settings.encpp_sharp_ls_map_lut[0],
		ISP_REG_TBL_LENGTH_32 * sizeof(HW_U8));
	memcpy(&isp_gen->encpp_sharp_cfg.sharp_texture_lut[0], &param->isp_tunning_settings.encpp_sharp_texture_lut[0],
		ISP_REG_TBL_LENGTH_32 * sizeof(HW_U8));

	/*encpp ldci*/
	isp_gen->encpp_ldci_cfg.ldci_mot0_en = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_MOT0_EN];
	isp_gen->encpp_ldci_cfg.ldci_mot1_en = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_MOT1_EN];
	isp_gen->encpp_ldci_cfg.ldci_txt_en = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_TXT_EN];
	isp_gen->encpp_ldci_cfg.ldci_lum_diff_sup_en = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_LUM_DIFF_SUP_EN];
	isp_gen->encpp_ldci_cfg.ldci_min_mad = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_MIN_MAD];
	isp_gen->encpp_ldci_cfg.ldci_flt_ratio[0] = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_FLT_RATIO0];
	isp_gen->encpp_ldci_cfg.ldci_flt_ratio[1] = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_FLT_RATIO1];
	isp_gen->encpp_ldci_cfg.ldci_flt_ratio[2] = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_FLT_RATIO2];
	isp_gen->encpp_ldci_cfg.ldci_flt_ratio[3] = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_FLT_RATIO3];
	isp_gen->encpp_ldci_cfg.ldci_flt_ratio[4] = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_FLT_RATIO4];
	isp_gen->encpp_ldci_cfg.ldci_flt_ratio[5] = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_FLT_RATIO5];
	isp_gen->encpp_ldci_cfg.ldci_stat_valid_block_w_num = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_BLOCK_W_NUM];
	isp_gen->encpp_ldci_cfg.ldci_stat_valid_block_h_num = param->isp_tunning_settings.encpp_ldci_comm_cfg[ENCPP_LDCI_BLOCK_H_NUM];
	memcpy(&isp_gen->encpp_ldci_cfg.ldci_txt_ratio_lut[0], &param->isp_tunning_settings.encpp_ldci_txt_ratio_lut[0], ISP_REG_TBL_LENGTH_32 * sizeof(HW_U8));
	memcpy(&isp_gen->encpp_ldci_cfg.ldci_mot_ratio_lut[0], &param->isp_tunning_settings.encpp_ldci_mot_ratio_lut[0], ISP_REG_TBL_LENGTH_32 * sizeof(HW_U8));
	memcpy(&isp_gen->encpp_ldci_cfg.ldci_lum_diff_lut[0], &param->isp_tunning_settings.encpp_ldci_lum_diff_lut[0], ISP_REG_TBL_LENGTH_32 * sizeof(HW_U8));
	memcpy(&isp_gen->encpp_ldci_cfg.ldci_map_pos_lut[0], &param->isp_tunning_settings.encpp_ldci_map_pos_lut[0], ISP_REG_TBL_LENGTH_16 * sizeof(HW_U8));
	memcpy(&isp_gen->encpp_ldci_cfg.ldci_map_neg_lut[0], &param->isp_tunning_settings.encpp_ldci_map_neg_lut[0], ISP_REG_TBL_LENGTH_16 * sizeof(HW_U8));
#endif

	//afs
	config_band_step(isp_gen);

	//gamma table
	if (param->isp_test_settings.gamma_en) {
		config_gamma(isp_gen);
	} else {
		for (i = 0; i < 1024; i++) {
			mod_cfg->gamma_cfg.gamma_tbl[i] = i * 4;
			mod_cfg->gamma_cfg.gamma_tbl[i + 1024] = i * 4;
			mod_cfg->gamma_cfg.gamma_tbl[i + 2048] = i * 4;
		}
	}

	if (param->isp_test_settings.lsc_en) {
		config_lens_table(isp_gen, 512);
		config_lens_center(isp_gen);
	}

	if (param->isp_test_settings.msc_en) {
		config_msc_table(isp_gen, 512, 256);
	}

	config_block_nr_table(isp_gen, 1);

	//stat
	int x_start, y_start;
	mod_cfg->stat_cfg.stat_valid_block_w_num = 32;
	mod_cfg->stat_cfg.stat_valid_block_h_num = 24;
	if (isp_gen->sensor_info.width_overlayer)
		mod_cfg->stat_cfg.stat_valid_block_width = clamp(isp_gen->sensor_info.width_overlayer / mod_cfg->stat_cfg.stat_valid_block_w_num, 1, 256);
	else
		mod_cfg->stat_cfg.stat_valid_block_width = clamp(isp_gen->sensor_info.sensor_width / mod_cfg->stat_cfg.stat_valid_block_w_num, 1, 256);
	mod_cfg->stat_cfg.stat_valid_block_height = clamp(isp_gen->sensor_info.sensor_height / mod_cfg->stat_cfg.stat_valid_block_h_num, 1, 256);
	mod_cfg->stat_cfg.stat_intp_w_step = div_round(4096, mod_cfg->stat_cfg.stat_valid_block_width);
	mod_cfg->stat_cfg.stat_intp_h_step = div_round(4096, mod_cfg->stat_cfg.stat_valid_block_height);
	mod_cfg->stat_cfg.stat_valid_block_num = clamp(mod_cfg->stat_cfg.stat_valid_block_w_num * mod_cfg->stat_cfg.stat_valid_block_h_num, 0, 768);
	mod_cfg->stat_cfg.stat_div_para = clamp(mod_cfg->stat_cfg.stat_valid_block_width * mod_cfg->stat_cfg.stat_valid_block_height, 1, 65536);
	x_start = mod_cfg->stat_cfg.stat_valid_block_w_num * mod_cfg->stat_cfg.stat_valid_block_width;
	y_start = mod_cfg->stat_cfg.stat_valid_block_h_num * mod_cfg->stat_cfg.stat_valid_block_height;
	if (isp_gen->sensor_info.width_overlayer) {
		if (x_start < isp_gen->sensor_info.width_overlayer)
			mod_cfg->stat_cfg.stat_last_block_w_start = x_start - mod_cfg->stat_cfg.stat_valid_block_width;
		else
			mod_cfg->stat_cfg.stat_last_block_w_start = isp_gen->sensor_info.width_overlayer - mod_cfg->stat_cfg.stat_valid_block_width;
	} else {
		if (x_start < isp_gen->sensor_info.sensor_width)
			mod_cfg->stat_cfg.stat_last_block_w_start = x_start - mod_cfg->stat_cfg.stat_valid_block_width;
		else
			mod_cfg->stat_cfg.stat_last_block_w_start = isp_gen->sensor_info.sensor_width - mod_cfg->stat_cfg.stat_valid_block_width;
	}
	mod_cfg->stat_cfg.stat_last_block_h_comp_line = clamp(y_start - isp_gen->sensor_info.sensor_height, 0, 255);
	if (y_start < isp_gen->sensor_info.sensor_height)
		mod_cfg->stat_cfg.stat_last_block_h_comp = 0;
	else
		mod_cfg->stat_cfg.stat_last_block_h_comp = mod_cfg->stat_cfg.stat_last_block_h_comp_line * mod_cfg->stat_cfg.stat_valid_block_width;

	memcpy(&mod_cfg->cem_cfg.cem_table[0], &param->isp_tunning_settings.isp_cem_table[0], ISP_CEM_MEM_SIZE);
}

int __isp_alloc_reg_tbl(struct isp_lib_context *isp_gen)
{
	unsigned int isp_default_reg[ISP_LOAD_REG_SIZE >> 2] = {
#if (ISP_VERSION >= 610)
	0x000c00c4, 0x00000051, 0x0fa0002a, 0x00000000, /* 0x0400 */
	0x00130013, 0x00130013, 0x00000000, 0x00000000, /* 0x0410 */
	0x04380780, 0x04380780, 0x00000000, 0x00000000, /* 0x0420 */
	0x00000000, 0x00000000, 0x32040030, 0x000010eb, /* 0x0430 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0440 */
	0x00000000, 0x00000000, 0x32723232, 0x00140180, /* 0x0450 */
	0x18321432, 0x02410180, 0x04380072, 0x00000000, /* 0x0460 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0470 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0480 */
	0x1fc01fc0, 0x1fc01fc0, 0x000c00c0, 0x00000000, /* 0x0490 */
	0x04000400, 0x04000400, 0x00000000, 0x00000000, /* 0x04a0 */
	0x1fc01fc0, 0x1fc01fc0, 0x000c00c0, 0x00000000, /* 0x04b0 */
	0x04000400, 0x04000400, 0x00000000, 0x00000000, /* 0x04c0 */
	0x1fc01fc0, 0x1fc01fc0, 0x000c00c0, 0x00000000, /* 0x04d0 */
	0x04000400, 0x04000400, 0x00000000, 0x00000000, /* 0x04e0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x04f0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0500 */
	0x07033371, 0x0fffff0f, 0x00000000, 0x00000000, /* 0x0510 */
	0xffff0013, 0x0f000200, 0x00400015, 0x0f000333, /* 0x0520 */
	0x04000040, 0x08000010, 0x08000002, 0x04000004, /* 0x0530 */
	0xffff0013, 0x0f000200, 0x00400015, 0x0f000333, /* 0x0540 */
	0x04000040, 0x08000010, 0x08000002, 0x04000004, /* 0x0550 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0560 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0570 */
	0x00000010, 0x00000000, 0x00000000, 0x00000000, /* 0x0580 */
	0x00000000, 0x00400040, 0x01c00140, 0x0aaa06ee, /* 0x0590 */
	0x031a019a, 0x2c100400, 0x01000400, 0x00000f0f, /* 0x05a0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x05b0 */
	0x00000020, 0x00000000, 0x00000000, 0x00000000, /* 0x05c0 */
	0x003c0000, 0x01060106, 0x00005040, 0x00000000, /* 0x05d0 */
	0x00640064, 0x00a400a4, 0x00000000, 0x00000000, /* 0x05e0 */
	0x01000000, 0x00000000, 0x1fc01fc0, 0x1fc01fc0, /* 0x05f0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0600 */
	0x00000000, 0x00000000, 0xff00ff00, 0x40020020, /* 0x0610 */
	0x00000000, 0x00000000, 0x00000000, 0x80008000, /* 0x0620 */
	0x0f000200, 0x0f000200, 0x00130013, 0x00000000, /* 0x0630 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0640 */
	0x00700000, 0x00000000, 0x00000000, 0x42108080, /* 0x0650 */
	0x00008040, 0x0004060a, 0x00100010, 0x01000100, /* 0x0660 */
	0x007f0020, 0x40000400, 0x0fff0100, 0x40000400, /* 0x0670 */
	0x0fff0100, 0x40000400, 0x0fff0100, 0x001fa400, /* 0x0680 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0690 */
	0x0040000c, 0x40000100, 0x20ff0008, 0x00200400, /* 0x06a0 */
	0x00d50078, 0xffffffff, 0x00000000, 0x00000000, /* 0x06b0 */
	0x50185050, 0x20401010, 0x00000001, 0x00000000, /* 0x06c0 */
	0x02002020, 0x02002020, 0x00800080, 0x00000000, /* 0x06d0 */
	0x010100c0, 0x011001e0, 0x011801e8, 0x012001f0, /* 0x06e0 */
	0x012c01f8, 0x013801fa, 0x013c01fc, 0x013f01ff, /* 0x06f0 */
	0x028c5a83, 0x0000003c, 0x0f8c1000, 0x0e603600, /* 0x0700 */
	0x0c002d00, 0x40000000, 0x000002d0, 0x00000000, /* 0x0710 */
	0x1fc01fc0, 0x00001fc0, 0x00000000, 0x00000000, /* 0x0720 */
	0x01000100, 0x01000100, 0x00000fff, 0x00000000, /* 0x0730 */
	0x04000400, 0x04000400, 0x00000000, 0x00000000, /* 0x0740 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0750 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0760 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0770 */
	0x80008000, 0x000003ff, 0x00000000, 0x00000000, /* 0x0780 */
	0x00800080, 0x08010200, 0xff008020, 0x00000000, /* 0x0790 */
	0x00000040, 0x00000080, 0x00000100, 0x00000200, /* 0x07a0 */
	0x00000400, 0x00000800, 0x00000c00, 0x00000000, /* 0x07b0 */
	0x00800040, 0x02000100, 0x08000400, 0x00000c00, /* 0x07c0 */
	0x00800000, 0x0024f000, 0x02000010, 0x0084c000, /* 0x07d0 */
	0xffffff74, 0x00101010, 0x00001010, 0x0fa00fff, /* 0x07e0 */
	0x01010101, 0x00000000, 0x00000000, 0x00000000, /* 0x07f0 */
	0x00010140, 0xc0010060, 0x00ff0080, 0x008c9200, /* 0x0800 */
	0x03000200, 0x000ffb20, 0xff000020, 0x00000000, /* 0x0810 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0820 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0830 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0840 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0850 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0860 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0870 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0880 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0890 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x08a0 */
	0x00000100, 0x00000000, 0x00000100, 0x00000000, /* 0x08b0 */
	0x00000100, 0x00000000, 0x00000000, 0x00000000, /* 0x08c0 */
	0x00000008, 0x00000000, 0x00000000, 0x00000000, /* 0x08d0 */
	0x02040107, 0x07680064, 0x01c206d6, 0x068701c2, /* 0x08e0 */
	0x004007b7, 0x02000200, 0x00000000, 0x00000000, /* 0x08f0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0900 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0910 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0920 */
	0x00040000, 0x00180020, 0x00000000, 0x00600080, /* 0x0930 */
	0x000012c0, 0x00000000, 0x01000100, 0x01000100, /* 0x0940 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0950 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0960 */
	0x01080000, 0x008600f0, 0x00000000, 0x39ccf1ac, /* 0x0970 */
	0x00029391, 0x00000000, 0x00000000, 0x00000035, /* 0x0980 */
	0x0000027b, 0x0000009d, 0x00000088, 0x00000000, /* 0x0990 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x09a0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x09b0 */
	0x00000000, 0x00000000, 0x00000000, 0x000000f0, /* 0x09c0 */
	0x00000000, 0x00000000, 0x00000004, 0x00000000, /* 0x09d0 */
	0x00100400, 0x00180020, 0x00000000, 0x003c0050, /* 0x09e0 */
	0x0fff0000, 0x0fff0000, 0x0fff0000, 0x00000000, /* 0x09f0 */
	0x00000000, 0x0fff0000, 0x00000000, 0x00000000, /* 0x0a00 */
	0x00000000, 0x04380780, 0x00000004, 0x00000000, /* 0x0a10 */
	0x00000000, 0x04380780, 0x00000004, 0x00000000, /* 0x0a20 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0a30 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0a40 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0a50 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0a60 */
	0x0300171f, 0x00000744, 0x2c3b0a8c, 0x0005b044, /* 0x0a70 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0a80 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0a90 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0aa0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0ab0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0ac0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0ad0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0ae0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0af0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0b00 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0b10 */
	0x00310057, 0x00310057, 0x00310057, 0x00310057, /* 0x0b20 */
	0x00310057, 0x00310057, 0x00310057, 0x00310057, /* 0x0b30 */
	0x00310057, 0x00310057, 0x00310057, 0x00000000, /* 0x0b40 */
	0x0053002f, 0x0053002f, 0x0053002f, 0x0053002f, /* 0x0b50 */
	0x0053002f, 0x0053002f, 0x0053002f, 0x0053002f, /* 0x0b60 */
	0x0053002f, 0x0053002f, 0x0053002f, 0x0053002f, /* 0x0b70 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0b80 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0b90 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0ba0 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0bb0 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0bc0 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0bd0 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0be0 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0bf0 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0c00 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0c10 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0c20 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0c30 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0c40 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0c50 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0c60 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0c70 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0c80 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0c90 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0ca0 */
	0x00100010, 0x00100010, 0x00100010, 0x00100010, /* 0x0cb0 */
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, /* 0x0cc0 */
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, /* 0x0cd0 */
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, /* 0x0ce0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0cf0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0d00 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x0d10 */
	0x01010101, 0x01010101, 0x01010101, 0x01010101, /* 0x0d20 */
	0x01010101, 0x01010101, 0x01010101, 0x01010101, /* 0x0d30 */
	0x01010101, 0x00000000, 0x00000000, 0x00000000, /* 0x0d40 */
	0x01010101, 0x01010101, 0x01010101, 0x01010101, /* 0x0d50 */
	0x01010101, 0x01010101, 0x01010101, 0x01010101, /* 0x0d60 */
	0x01010101, 0x00000000, 0x00000000, 0x00000000, /* 0x0d70 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0d80 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0d90 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0da0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0db0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0dc0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0dd0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0de0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0df0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0e00 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0e10 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0e20 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0e30 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0e40 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0e50 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0e60 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0e70 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0e80 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0e90 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0ea0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0eb0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0ec0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0ed0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0ee0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0ef0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0f00 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0f10 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0f20 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0f30 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x0f40 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00000000, /* 0x0f50 */
	0x003f0000, 0x00bf007f, 0x013f00ff, 0x01bf017f, /* 0x0f60 */
	0x023f01ff, 0x02bf027f, 0x033f02ff, 0x03bf037f, /* 0x0f70 */
	0x043f03ff, 0x04bf047f, 0x053f04ff, 0x05bf057f, /* 0x0f80 */
	0x063f05ff, 0x06bf067f, 0x073f06ff, 0x07bf077f, /* 0x0f90 */
	0x083f07ff, 0x08bf087f, 0x093f08ff, 0x09bf097f, /* 0x0fa0 */
	0x0a3f09ff, 0x0abf0a7f, 0x0b3f0aff, 0x0bbf0b7f, /* 0x0fb0 */
	0x0c3f0bff, 0x0cbf0c7f, 0x0d3f0cff, 0x0dbf0d7f, /* 0x0fc0 */
	0x0e3f0dff, 0x0ebf0e7f, 0x0f3f0eff, 0x0fbf0f7f, /* 0x0fd0 */
	0x003f0000, 0x00bf007f, 0x013f00ff, 0x01bf017f, /* 0x0fe0 */
	0x023f01ff, 0x02bf027f, 0x033f02ff, 0x03bf037f, /* 0x0ff0 */
	0x043f03ff, 0x04bf047f, 0x053f04ff, 0x05bf057f, /* 0x1000 */
	0x063f05ff, 0x06bf067f, 0x073f06ff, 0x07bf077f, /* 0x1010 */
	0x083f07ff, 0x08bf087f, 0x093f08ff, 0x09bf097f, /* 0x1020 */
	0x0a3f09ff, 0x0abf0a7f, 0x0b3f0aff, 0x0bbf0b7f, /* 0x1030 */
	0x0c3f0bff, 0x0cbf0c7f, 0x0d3f0cff, 0x0dbf0d7f, /* 0x1040 */
	0x0e3f0dff, 0x0ebf0e7f, 0x0f3f0eff, 0x0fbf0f7f, /* 0x1050 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1060 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1070 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1080 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1090 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x10a0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x10b0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x10c0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x10d0 */
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, /* 0x10e0 */
	0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, /* 0x10f0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1100 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1110 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1120 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1130 */
	0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, /* 0x1140 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1150 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1160 */
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, /* 0x1170 */
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, /* 0x1180 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x1190 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x11a0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x11b0 */
	0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff, /* 0x11c0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x11d0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x11e0 */
	0x000f000f, 0x000f000f, 0x000f000f, 0x000f000f, /* 0x11f0 */
	0x000f000f, 0x000f000f, 0x000f000f, 0x000f000f, /* 0x1200 */
	0x000f000f, 0x000f000f, 0x000f000f, 0x000f000f, /* 0x1210 */
	0x000f000f, 0x000f000f, 0x000f000f, 0x000f000f, /* 0x1220 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1230 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1240 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1250 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1260 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1270 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x1280 */
	0x33331100, 0xd9755533, 0x77776544, 0xfddcba98, /* 0x1290 */
	0x02b2014a, 0x05700400, 0x08700700, 0x0af009c0, /* 0x12a0 */
	0x0cf00c00, 0x0f000e70, 0x0fc00f70, 0x10000ff0, /* 0x12b0 */
	0x00c000c0, 0x00c000c0, 0x00c000c0, 0x00c000c0, /* 0x12c0 */
	0x00c000c0, 0x00c000c0, 0x00c000c0, 0x00c000c0, /* 0x12d0 */
	0x100c1020, 0x00000000, 0x00000000, 0x00000000, /* 0x12e0 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* 0x12f0 */
#endif
	};

	/* REG LOAD*/
	isp_gen->load_reg_base = malloc(ISP_LOAD_DRAM_SIZE);
	if(isp_gen->load_reg_base == NULL) {
		ISP_ERR("load_reg_base alloc failed, no memory!");
		return -1;
	}
	memset(isp_gen->load_reg_base, 0, ISP_AHB_REG_SIZE);
	memcpy(isp_gen->load_reg_base + ISP_AHB_REG_SIZE, &isp_default_reg[0], ISP_LOAD_REG_SIZE);

	isp_gen->module_cfg.isp_dev_id = isp_gen->isp_id;
	isp_gen->module_cfg.isp_platform_id = ISP_PLATFORM_SUN8IW21P1;

	isp_map_addr(&isp_gen->module_cfg, (unsigned long)isp_gen->load_reg_base);
#if (ISP_VERSION >= 610)
	/*FE TABLE*/
	isp_gen->module_cfg.fe_table = isp_gen->load_reg_base + ISP_AHB_REG_SIZE + ISP_LOAD_REG_SIZE;
	memset(isp_gen->module_cfg.fe_table, 0, ISP_FE_TABLE_SIZE);

	isp_gen->module_cfg.ch0_msc_table = isp_gen->module_cfg.fe_table + ISP_CH0_MSC_FE_MEM_OFS;
	isp_gen->module_cfg.ch1_msc_table = isp_gen->module_cfg.fe_table + ISP_CH1_MSC_FE_MEM_OFS;
	isp_gen->module_cfg.ch2_msc_table = isp_gen->module_cfg.fe_table + ISP_CH2_MSC_FE_MEM_OFS;

	/*BAYER TABLE*/
	isp_gen->module_cfg.bayer_table = isp_gen->module_cfg.fe_table + ISP_FE_TABLE_SIZE;
	memset(isp_gen->module_cfg.bayer_table, 0, ISP_BAYER_TABLE_SIZE);

	isp_gen->module_cfg.lens_table = isp_gen->module_cfg.bayer_table + ISP_LSC_MEM_OFS;
	isp_gen->module_cfg.msc_table = isp_gen->module_cfg.bayer_table + ISP_MSC_MEM_OFS;
	isp_gen->module_cfg.d2d_extb_table = isp_gen->module_cfg.bayer_table + ISP_D2D_EBDNR_OFS;
	isp_gen->module_cfg.tdnf_table = isp_gen->module_cfg.bayer_table + ISP_D3D_DK_MEM_OFS;
	isp_gen->module_cfg.tdnf_extb_table = isp_gen->module_cfg.bayer_table + ISP_D3D_EBDNR_OFS;
	isp_gen->module_cfg.dpc_sdp_table = isp_gen->module_cfg.bayer_table + ISP_DPC_SDP_TBL_OFS;
	isp_gen->module_cfg.gca_table = isp_gen->module_cfg.bayer_table + ISP_GCA_RB_CH_TBL_OFS;
	isp_gen->module_cfg.fpn_table = isp_gen->module_cfg.bayer_table + ISP_FPN_CFPN_CORR_TBL_OFS;
	isp_gen->module_cfg.pltm_table = isp_gen->module_cfg.bayer_table + ISP_PLTM_GTM_LM_TBL_OFS;

	/*RGB TABLE*/
	isp_gen->module_cfg.rgb_table = isp_gen->module_cfg.bayer_table + ISP_BAYER_TABLE_SIZE;
	memset(isp_gen->module_cfg.rgb_table, 0, ISP_RGB_TABLE_SIZE);

	isp_gen->module_cfg.gamma_table = isp_gen->module_cfg.rgb_table + ISP_GAMMA_MEM_OFS;
	isp_gen->module_cfg.sharp_table = isp_gen->module_cfg.rgb_table + ISP_SHARP_MOT_TEX_TBL_OFS;

	/*YUV TABLE*/
	isp_gen->module_cfg.yuv_table = isp_gen->module_cfg.rgb_table + ISP_RGB_TABLE_SIZE;
	memset(isp_gen->module_cfg.yuv_table, 0, ISP_YUV_TABLE_SIZE);

	isp_gen->module_cfg.cem_table = isp_gen->module_cfg.yuv_table + ISP_CEM_MEM_OFS;
	isp_gen->module_cfg.drc_table = isp_gen->module_cfg.yuv_table + ISP_DRC_MEM_OFS;
#endif
	return 0;
}

int __isp_dump_reg(struct isp_lib_context *isp_gen)
{
	int i, *reg;
	printf("dump ISP%d regs :\n", isp_gen->isp_id);
	for(i = 0; i < 0x40; i = i + 4)
	{
		reg = (int*)(isp_gen->load_reg_base + i);
		if(i % 0x10 == 0)
			printf("0x%08x:  ", i);
		printf("0x%08x, ", reg[0]);
		if(i % 0x10 == 0xc)
			printf("\n");
	}
	for(i = 0x40; i < 0x400; i = i + 4)
	{
		reg = (int*)(isp_gen->load_reg_base + i);

		if(i % 0x10 == 0)
			printf("0x%08x:  ", i);
		printf("0x%08x, ", reg[0]);
		if(i % 0x10 == 0xc)
			printf("\n");
	}

	return 0;
}

HW_S32 isp_ctx_stats_prepare(struct isp_lib_context *isp_gen, const void *buffer)
{	FUNCTION_LOG;

	pthread_mutex_lock(&(isp_gen->ctx_lock));
	isp_handle_stats(isp_gen, buffer);
	pthread_mutex_unlock(&(isp_gen->ctx_lock));

	return 0;
}
HW_S32 isp_ctx_stats_prepare_sync(struct isp_lib_context *isp_gen, const void *buffer0, const void *buffer1)
{	FUNCTION_LOG;

	pthread_mutex_lock(&(isp_gen->ctx_lock));
	isp_handle_stats_sync(isp_gen, buffer0, buffer1);
	pthread_mutex_unlock(&(isp_gen->ctx_lock));

	return 0;
}


HW_S32 isp_ctx_stats_req(struct isp_lib_context *isp_gen,
					struct isp_stats_context *stats_ctx)
{	FUNCTION_LOG;

	pthread_mutex_lock(&(isp_gen->ctx_lock));
	*stats_ctx = isp_gen->stats_ctx;
	pthread_mutex_unlock(&(isp_gen->ctx_lock));

	return 0;
}

HW_S32 __isp_ctx_update_iso_cfg(struct isp_lib_context *isp_gen)
{
	isp_iso_entity_context_t *isp_iso_cxt = &isp_gen->iso_entity_ctx;

	if (!isp_gen->iso_entity_ctx.iso_param) {
		return -1;
	}

	isp_gen->iso_entity_ctx.iso_param->isp_gen = isp_gen;

	isp_gen->iso_entity_ctx.iso_param->sharpness_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->brightness_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->contrast_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->cem_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->denoise_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->black_level_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->dpc_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->defog_value_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->pltm_dynamic_cfg_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->tdnr_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->ae_cfg_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->gtm_cfg_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->lca_cfg_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->wdr_cfg_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->cfa_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->shading_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->encoder_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->awb_adjust = true;
	isp_gen->iso_entity_ctx.iso_param->nrp_adjust = true;

	if((isp_gen->isp_ini_cfg.isp_test_settings.af_en == 1) || (isp_gen->isp_ini_cfg.isp_test_settings.isp_test_focus == 1))
		isp_gen->iso_entity_ctx.iso_param->af_cfg_adjust = true;
	else
		isp_gen->iso_entity_ctx.iso_param->af_cfg_adjust = false;

	isp_gen->iso_entity_ctx.iso_param->test_cfg.isp_test_mode = isp_gen->isp_ini_cfg.isp_test_settings.isp_test_mode;

	isp_iso_set_params_helper(&isp_gen->iso_entity_ctx, ISP_ISO_UPDATE_PARAMS);

	isp_iso_cxt->ops->isp_iso_run(isp_iso_cxt->iso_entity, &isp_iso_cxt->iso_result);

	return 0;
}

HW_S32 __isp_ctx_update_af_cfg(struct isp_lib_context *isp_gen)
{
	if (!isp_gen->af_entity_ctx.af_param) {
		return -1;
	}

	//af_ini_cfg.
	isp_gen->af_entity_ctx.af_param->af_ini.af_use_otp = isp_gen->isp_ini_cfg.isp_3a_settings.af_use_otp;
	if (isp_gen->sensor_otp.otp_enable && isp_gen->sensor_otp.otp_info) {
		isp_gen->af_entity_ctx.af_param->af_ini.vcm_min_code = clamp(isp_gen->isp_ini_cfg.isp_3a_settings.vcm_min_code + isp_gen->sensor_otp.otp_info->af_min_code_offset, 0, 1023);
		isp_gen->af_entity_ctx.af_param->af_ini.vcm_max_code = clamp(isp_gen->isp_ini_cfg.isp_3a_settings.vcm_max_code + isp_gen->sensor_otp.otp_info->af_max_code_offset, 0, 1023);
	} else {
		isp_gen->af_entity_ctx.af_param->af_ini.vcm_min_code = isp_gen->isp_ini_cfg.isp_3a_settings.vcm_min_code;
		isp_gen->af_entity_ctx.af_param->af_ini.vcm_max_code = isp_gen->isp_ini_cfg.isp_3a_settings.vcm_max_code;
	}
	isp_gen->af_entity_ctx.af_param->vcm.vcm_min_code = isp_gen->af_entity_ctx.af_param->af_ini.vcm_min_code;
	isp_gen->af_entity_ctx.af_param->vcm.vcm_max_code = isp_gen->af_entity_ctx.af_param->af_ini.vcm_max_code;

	isp_gen->af_entity_ctx.af_param->af_ini.af_interval_time = isp_gen->isp_ini_cfg.isp_3a_settings.af_interval_time;
	isp_gen->af_entity_ctx.af_param->af_ini.af_speed_ind = isp_gen->isp_ini_cfg.isp_3a_settings.af_speed_ind;
	isp_gen->af_entity_ctx.af_param->af_ini.af_auto_fine_en = isp_gen->isp_ini_cfg.isp_3a_settings.af_auto_fine_en;
	isp_gen->af_entity_ctx.af_param->af_ini.af_single_fine_en = isp_gen->isp_ini_cfg.isp_3a_settings.af_single_fine_en;
	isp_gen->af_entity_ctx.af_param->af_ini.af_fine_step = isp_gen->isp_ini_cfg.isp_3a_settings.af_fine_step;
	isp_gen->af_entity_ctx.af_param->af_ini.af_move_cnt = isp_gen->isp_ini_cfg.isp_3a_settings.af_move_cnt;
	isp_gen->af_entity_ctx.af_param->af_ini.af_still_cnt = isp_gen->isp_ini_cfg.isp_3a_settings.af_still_cnt;
	isp_gen->af_entity_ctx.af_param->af_ini.af_move_monitor_cnt = isp_gen->isp_ini_cfg.isp_3a_settings.af_move_monitor_cnt;
	isp_gen->af_entity_ctx.af_param->af_ini.af_still_monitor_cnt = isp_gen->isp_ini_cfg.isp_3a_settings.af_still_monitor_cnt;
	isp_gen->af_entity_ctx.af_param->af_ini.af_stable_min = isp_gen->isp_ini_cfg.isp_3a_settings.af_stable_min;
	isp_gen->af_entity_ctx.af_param->af_ini.af_stable_max = isp_gen->isp_ini_cfg.isp_3a_settings.af_stable_max;
	isp_gen->af_entity_ctx.af_param->af_ini.af_low_light_lv = isp_gen->isp_ini_cfg.isp_3a_settings.af_low_light_lv;
	isp_gen->af_entity_ctx.af_param->af_ini.af_near_tolerance = isp_gen->isp_ini_cfg.isp_3a_settings.af_near_tolerance;
	isp_gen->af_entity_ctx.af_param->af_ini.af_far_tolerance = isp_gen->isp_ini_cfg.isp_3a_settings.af_far_tolerance;
	isp_gen->af_entity_ctx.af_param->af_ini.af_tolerance_off = isp_gen->isp_ini_cfg.isp_3a_settings.af_tolerance_off;
	isp_gen->af_entity_ctx.af_param->af_ini.af_peak_th = isp_gen->isp_ini_cfg.isp_3a_settings.af_peak_th;
	isp_gen->af_entity_ctx.af_param->af_ini.af_dir_th = isp_gen->isp_ini_cfg.isp_3a_settings.af_dir_th;
	isp_gen->af_entity_ctx.af_param->af_ini.af_change_ratio = isp_gen->isp_ini_cfg.isp_3a_settings.af_change_ratio;
	isp_gen->af_entity_ctx.af_param->af_ini.af_move_minus = isp_gen->isp_ini_cfg.isp_3a_settings.af_move_minus;
	isp_gen->af_entity_ctx.af_param->af_ini.af_still_minus = isp_gen->isp_ini_cfg.isp_3a_settings.af_still_minus;
	isp_gen->af_entity_ctx.af_param->af_ini.af_scene_motion_th = isp_gen->isp_ini_cfg.isp_3a_settings.af_scene_motion_th;
	isp_gen->af_entity_ctx.af_param->af_ini.af_tolerance_tbl_len = isp_gen->isp_ini_cfg.isp_3a_settings.af_tolerance_tbl_len;
	memcpy(&isp_gen->af_entity_ctx.af_param->af_ini.af_std_code_tbl[0],
		&isp_gen->isp_ini_cfg.isp_3a_settings.af_std_code_tbl[0], 20*sizeof(int));
	memcpy(&isp_gen->af_entity_ctx.af_param->af_ini.af_tolerance_value_tbl[0],
		&isp_gen->isp_ini_cfg.isp_3a_settings.af_tolerance_value_tbl[0], 20*sizeof(int));
	isp_gen->af_entity_ctx.af_param->af_ini.af_delay_frame = isp_gen->isp_ini_cfg.isp_3a_settings.af_reserve_0;
	isp_gen->af_entity_ctx.af_param->af_ini.af_touch_dist_ind = isp_gen->isp_ini_cfg.isp_3a_settings.af_reserve_1;
	isp_af_set_params_helper(&isp_gen->af_entity_ctx, ISP_AF_INI_DATA);

	isp_gen->af_entity_ctx.af_param->test_cfg.isp_test_mode = isp_gen->isp_ini_cfg.isp_test_settings.isp_test_mode;
	isp_gen->af_entity_ctx.af_param->test_cfg.isp_test_focus = isp_gen->isp_ini_cfg.isp_test_settings.isp_test_focus;
	isp_gen->af_entity_ctx.af_param->test_cfg.focus_start = isp_gen->isp_ini_cfg.isp_test_settings.focus_start;
	isp_gen->af_entity_ctx.af_param->test_cfg.focus_step = isp_gen->isp_ini_cfg.isp_test_settings.focus_step;
	isp_gen->af_entity_ctx.af_param->test_cfg.focus_end = isp_gen->isp_ini_cfg.isp_test_settings.focus_end;
	isp_gen->af_entity_ctx.af_param->test_cfg.focus_change_interval = isp_gen->isp_ini_cfg.isp_test_settings.focus_change_interval;
	isp_gen->af_entity_ctx.af_param->test_cfg.af_en = isp_gen->isp_ini_cfg.isp_test_settings.af_en;

	return 0;
}
HW_S32 __isp_ctx_update_awb_cfg(struct isp_lib_context *isp_gen)
{
	if (!isp_gen->awb_entity_ctx.awb_param) {
		return -1;
	}

	//awb_ini_cfg.
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_interval = isp_gen->isp_ini_cfg.isp_3a_settings.awb_interval;
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_speed = isp_gen->isp_ini_cfg.isp_3a_settings.awb_speed;
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_color_temper_low = isp_gen->isp_ini_cfg.isp_3a_settings.awb_color_temper_low;
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_color_temper_high = isp_gen->isp_ini_cfg.isp_3a_settings.awb_color_temper_high;
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_base_temper = isp_gen->isp_ini_cfg.isp_3a_settings.awb_base_temper;
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_green_zone_dist = isp_gen->isp_ini_cfg.isp_3a_settings.awb_green_zone_dist;
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_blue_sky_dist = isp_gen->isp_ini_cfg.isp_3a_settings.awb_blue_sky_dist;
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_light_num = isp_gen->isp_ini_cfg.isp_3a_settings.awb_light_num;
	//isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_ext_light_num = isp_gen->isp_ini_cfg.isp_3a_settings.awb_ext_light_num;
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_ext_light_num = 0;
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_skin_color_num = isp_gen->isp_ini_cfg.isp_3a_settings.awb_skin_color_num;
	isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_special_color_num = isp_gen->isp_ini_cfg.isp_3a_settings.awb_special_color_num;

	memcpy(&isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_light_info[0],
		&isp_gen->isp_ini_cfg.isp_3a_settings.awb_light_info[0], 160*sizeof(int));
	memcpy(&isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_ext_light_info[0],
		&isp_gen->isp_ini_cfg.isp_3a_settings.awb_ext_light_info[0], 80*sizeof(int));
	memcpy(&isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_skin_color_info[0],
		&isp_gen->isp_ini_cfg.isp_3a_settings.awb_skin_color_info[0], 40*sizeof(int));
	memcpy(&isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_special_color_info[0],
		&isp_gen->isp_ini_cfg.isp_3a_settings.awb_special_color_info[0], 80*sizeof(int));
	memcpy(&isp_gen->awb_entity_ctx.awb_param->awb_ini.awb_preset_gain[0],
		&isp_gen->isp_ini_cfg.isp_3a_settings.awb_preset_gain[0], 22*sizeof(int));

	isp_awb_set_params_helper(&isp_gen->awb_entity_ctx, ISP_AWB_INI_DATA);

	//test cfg.
	isp_gen->awb_entity_ctx.awb_param->test_cfg.awb_en = isp_gen->isp_ini_cfg.isp_test_settings.awb_en;
	isp_gen->awb_entity_ctx.awb_param->test_cfg.isp_color_temp = isp_gen->isp_ini_cfg.isp_test_settings.isp_color_temp;
	isp_gen->awb_entity_ctx.awb_param->test_cfg.isp_test_mode = 0;

	return 0;
}

HW_S32 __isp_ctx_update_ae_cfg(struct isp_lib_context *isp_gen)
{
	//struct isp_param_config *param = &isp_gen->isp_ini_cfg;

	if (!isp_gen->ae_entity_ctx.ae_param) {
		return -1;
	}

	//ae_sensor_info.
	isp_gen->ae_entity_ctx.ae_param->ae_sensor_info = isp_gen->sensor_info;
	//ae_ini_cfg.
	isp_gen->ae_entity_ctx.ae_param->ae_ini.define_ae_table = isp_gen->isp_ini_cfg.isp_3a_settings.define_ae_table;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_max_lv = isp_gen->isp_ini_cfg.isp_3a_settings.ae_max_lv;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].length = isp_gen->isp_ini_cfg.isp_3a_settings.ae_table_preview_length;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].length = isp_gen->isp_ini_cfg.isp_3a_settings.ae_table_capture_length;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_VIDEO].length = isp_gen->isp_ini_cfg.isp_3a_settings.ae_table_video_length;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_hist_mod_en = isp_gen->isp_ini_cfg.isp_3a_settings.ae_hist_mod_en;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_ev_step = isp_gen->isp_ini_cfg.isp_3a_settings.ae_ev_step;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_ConvDataIndex = isp_gen->isp_ini_cfg.isp_3a_settings.ae_ConvDataIndex;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_blowout_pre_en = isp_gen->isp_ini_cfg.isp_3a_settings.ae_blowout_pre_en;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_blowout_attr = isp_gen->isp_ini_cfg.isp_3a_settings.ae_blowout_attr;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_delay_frame = isp_gen->isp_ini_cfg.isp_3a_settings.ae_delay_frame;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.exp_delay_frame = isp_gen->isp_ini_cfg.isp_3a_settings.exp_delay_frame;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.gain_delay_frame = isp_gen->isp_ini_cfg.isp_3a_settings.gain_delay_frame;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.exp_comp_step = isp_gen->isp_ini_cfg.isp_3a_settings.exp_comp_step;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_touch_dist_ind = isp_gen->isp_ini_cfg.isp_3a_settings.ae_touch_dist_ind;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_iso2gain_ratio = isp_gen->isp_ini_cfg.isp_3a_settings.ae_iso2gain_ratio;
	isp_gen->ae_settings.flicker_type = isp_gen->isp_ini_cfg.isp_tunning_settings.flicker_type;

	// wdr mode: 0 is default, use 256
	//isp_gen->isp_ini_cfg.isp_3a_settings.wdr_cfg[WDR_MODE] = 0;

	// gain_ratio: 0
	//isp_gen->ae_entity_ctx.ae_param->ae_ini.gain_ratio = isp_gen->isp_ini_cfg.isp_3a_settings.gain_ratio;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.gain_ratio = 0;

	memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_analog_gain_range[0], &isp_gen->isp_ini_cfg.isp_3a_settings.ae_analog_gain_range[0], 2*sizeof(int));
	memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_digital_gain_range[0], &isp_gen->isp_ini_cfg.isp_3a_settings.ae_digital_gain_range[0], 2*sizeof(int));
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_digital_gain_range[0] = 1024;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_digital_gain_range[1] = 1024 * 63;

	memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_fno_step[0], &isp_gen->isp_ini_cfg.isp_3a_settings.ae_fno_step[0], 16*sizeof(int));
	memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[0],
		&isp_gen->isp_ini_cfg.isp_3a_settings.ae_table_preview[0], 42*sizeof(int));
	memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].ae_tbl[0],
		&isp_gen->isp_ini_cfg.isp_3a_settings.ae_table_capture[0], 42*sizeof(int));
	memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_VIDEO].ae_tbl[0],
		&isp_gen->isp_ini_cfg.isp_3a_settings.ae_table_video[0], 42*sizeof(int));
	memcpy(&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_win_weight[0], &isp_gen->isp_ini_cfg.isp_3a_settings.ae_win_weight[0], 64*sizeof(int));

	isp_gen->ae_entity_ctx.ae_param->ae_ini.underexp_thres = 30;
	isp_gen->ae_entity_ctx.ae_param->ae_ini.overexp_thres = 190;

	isp_ae_set_params_helper(&isp_gen->ae_entity_ctx, ISP_AE_INI_DATA);

#if ISP_AI_SCENE_CONF
	// for ai scene param
	isp_gen->ai_scene.last_tune_settings.ae_table_night_length =
		isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].length;
	memcpy(&isp_gen->ai_scene.last_tune_settings.ae_ai_night_table[0],
		&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[0], 42*sizeof(int));
	normal_tune_settings.ae_table_night_length =
		isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].length;
	memcpy(&normal_tune_settings.ae_ai_night_table[0],
		&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[0], 42*sizeof(int));
	blue_sky_tune_settings.ae_table_night_length =
		isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].length;
	memcpy(&blue_sky_tune_settings.ae_ai_night_table[0],
		&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[0], 42*sizeof(int));
	green_plants_tune_settings.ae_table_night_length =
		isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].length;
	memcpy(&green_plants_tune_settings.ae_ai_night_table[0],
		&isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[0], 42*sizeof(int));
#endif

	//test cfg.
	isp_gen->ae_entity_ctx.ae_param->test_cfg.isp_test_mode = isp_gen->isp_ini_cfg.isp_test_settings.isp_test_mode;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.isp_gain = isp_gen->isp_ini_cfg.isp_test_settings.isp_gain;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.isp_exp_line = isp_gen->isp_ini_cfg.isp_test_settings.isp_exp_line;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.ae_forced = isp_gen->isp_ini_cfg.isp_test_settings.ae_forced;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.lum_forced = isp_gen->isp_ini_cfg.isp_test_settings.lum_forced;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.isp_test_exptime = isp_gen->isp_ini_cfg.isp_test_settings.isp_test_exptime;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.exp_line_start = isp_gen->isp_ini_cfg.isp_test_settings.exp_line_start;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.exp_line_step = isp_gen->isp_ini_cfg.isp_test_settings.exp_line_step;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.exp_line_end = isp_gen->isp_ini_cfg.isp_test_settings.exp_line_end;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.exp_change_interval = isp_gen->isp_ini_cfg.isp_test_settings.exp_change_interval;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.isp_test_gain = isp_gen->isp_ini_cfg.isp_test_settings.isp_test_gain;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.gain_start = isp_gen->isp_ini_cfg.isp_test_settings.gain_start;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.gain_step = isp_gen->isp_ini_cfg.isp_test_settings.gain_step;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.gain_end = isp_gen->isp_ini_cfg.isp_test_settings.gain_end;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.gain_change_interval = isp_gen->isp_ini_cfg.isp_test_settings.gain_change_interval;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.ae_en = isp_gen->isp_ini_cfg.isp_test_settings.ae_en;

	// Check ae hardware delay.
	// When check isp wdr/dg delay, we should set ae_stat_sel equals 2, because the stat date before the wdr dealt was not changed.
	// When check sensor exp/ag delay, we should set ae_stat_sel equals 0, because the stat date after the wdr dealt was not accurate.
	isp_gen->ae_entity_ctx.ae_param->test_cfg.ae_check_delay_en = 0;
	isp_gen->ae_entity_ctx.ae_param->test_cfg.ae_delay_type = ISP_AE_DELAY_WDR_AGAIN;

	isp_gen->ae_entity_ctx.ae_param->ae_setting = isp_gen->ae_settings;
	isp_ae_set_params_helper(&isp_gen->ae_entity_ctx, ISP_AE_UPDATE_AE_TABLE);

	//get gain range
	isp_gen->tune.gains.ana_gain_min = isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_analog_gain_range[0];
	isp_gen->tune.gains.ana_gain_max = isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_analog_gain_range[1];
	isp_gen->tune.gains.dig_gain_min = isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_digital_gain_range[0]/4; /*Q10 -> Q8*/
	isp_gen->tune.gains.dig_gain_max = isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_digital_gain_range[1]/4;

	if (isp_gen->ae_settings.exp_metering_mode == AE_METERING_MODE_SPOT)
		isp_ae_set_params_helper(&isp_gen->ae_entity_ctx, ISP_AE_BUILD_TOUCH_WEIGHT);
	return 0;
}

HW_S32 __isp_ctx_update_afs_cfg(struct isp_lib_context *isp_gen)
{
	if (!isp_gen->afs_entity_ctx.afs_param) {
		return -1;
	}

	isp_gen->afs_entity_ctx.afs_param->flicker_ratio = isp_gen->isp_ini_cfg.isp_tunning_settings.flicker_ratio;
	isp_gen->afs_entity_ctx.afs_param->flicker_type_ini = isp_gen->isp_ini_cfg.isp_tunning_settings.flicker_type;
	isp_gen->afs_entity_ctx.afs_param->test_cfg.isp_test_mode = isp_gen->isp_ini_cfg.isp_test_settings.isp_test_mode;
	isp_gen->afs_entity_ctx.afs_param->test_cfg.afs_en = isp_gen->isp_ini_cfg.isp_test_settings.afs_en;

	return 0;
}

HW_S32 __isp_ctx_update_md_cfg(struct isp_lib_context *isp_gen)
{
	if (!isp_gen->md_entity_ctx.md_param) {
		return -1;
	}

	isp_gen->md_entity_ctx.md_param->af_scene_motion_th = isp_gen->isp_ini_cfg.isp_3a_settings.af_scene_motion_th;
	isp_gen->md_entity_ctx.md_param->test_cfg.isp_test_mode = isp_gen->isp_ini_cfg.isp_test_settings.isp_test_mode;

	return 0;
}

HW_S32 __isp_ctx_update_rolloff_cfg(struct isp_lib_context *isp_gen)
{
	int m;

	if (!isp_gen->rolloff_entity_ctx.rolloff_param) {
		return -1;
	}

	//rolloff_sensor_info.
	isp_gen->rolloff_entity_ctx.rolloff_param->rolloff_sensor_info = isp_gen->sensor_info;
	isp_gen->rolloff_entity_ctx.rolloff_param->stitch_mode = isp_gen->stitch_mode;

	for (m = 0; m < 11 * ROLLOFF_WIN_SIZE; m++)
		isp_gen->rolloff_entity_ctx.rolloff_param->rolloff_ini.Rgain[m]
			= isp_gen->isp_ini_cfg.isp_tunning_settings.msc_tbl[(m / ROLLOFF_WIN_SIZE) + 1][m % ROLLOFF_WIN_SIZE];

	isp_rolloff_set_params_helper(&isp_gen->rolloff_entity_ctx, ISP_ROLLOFF_INI_DATA);

	return 0;
}
HW_S32 __isp_ctx_update_gtm_cfg(struct isp_lib_context *isp_gen)
{
	if (!isp_gen->gtm_entity_ctx.gtm_param) {
		return -1;
	}

	isp_gen->gtm_entity_ctx.gtm_param->gtm_enable = isp_gen->isp_ini_cfg.isp_test_settings.gtm_en;
	isp_gen->gtm_entity_ctx.gtm_param->gamma_tbl =	&isp_gen->module_cfg.gamma_cfg.gamma_tbl[0];
	isp_gen->gtm_entity_ctx.gtm_param->drc_table =	&isp_gen->module_cfg.drc_cfg.drc_table[0];
	isp_gen->gtm_entity_ctx.gtm_param->drc_table_last = &isp_gen->module_cfg.drc_cfg.drc_table_last[0];
	isp_gen->gtm_entity_ctx.gtm_param->ae_hist0_sel = isp_gen->isp_ini_cfg.isp_3a_settings.ae_hist0_sel;
	isp_gen->gtm_entity_ctx.gtm_param->ae_hist1_sel = isp_gen->isp_ini_cfg.isp_3a_settings.ae_hist1_sel;
	//gtm_ini_cfg.
	isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_type = isp_gen->isp_ini_cfg.isp_tunning_settings.gtm_type;
	memcpy(&isp_gen->gtm_entity_ctx.gtm_param->gtm_ini.gtm_cfg[0], &isp_gen->ae_settings.ae_hist_eq_cfg[0], ISP_GTM_HEQ_MAX * sizeof(HW_S16));
	isp_gtm_set_params_helper(&isp_gen->gtm_entity_ctx, ISP_GTM_INI_DATA);

	//test cfg.
	isp_gen->gtm_entity_ctx.gtm_param->test_cfg.isp_test_mode = isp_gen->isp_ini_cfg.isp_test_settings.isp_test_mode;

	return 0;
}

HW_S32 __isp_ctx_update_pltm_cfg(struct isp_lib_context *isp_gen)
{
	if (!isp_gen->pltm_entity_ctx.pltm_param) {
		return -1;
	}

	isp_gen->pltm_entity_ctx.pltm_param->pltm_enable = isp_gen->isp_ini_cfg.isp_test_settings.pltm_en;
	//pltm_ini_cfg.
	memcpy(&isp_gen->pltm_entity_ctx.pltm_param->pltm_ini.pltm_cfg[0],
		&isp_gen->isp_ini_cfg.isp_tunning_settings.pltm_cfg[0], ISP_PLTM_MAX*sizeof(HW_S32));
	memcpy(&isp_gen->pltm_entity_ctx.pltm_param->pltm_ini.pltm_dynamic_cfg[0],
		&isp_gen->ae_settings.pltm_dynamic_cfg[0], ISP_PLTM_DYNAMIC_MAX*sizeof(HW_S16));
	return 0;
}

void __get_sensor_temp_param(struct isp_lib_context *isp_gen)
{
	HW_S16 temperature;
	HW_S16 temp_mapping[14] = {55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120};
	HW_U8 i, index;
	if (isp_gen->temp_info.enable) {
		if (isp_gen->sensor_info.temperature >= temp_mapping[13]) {
			for (i = 0; i < TEMP_COMP_MAX; i++) {
				isp_gen->temp_info.temperature_param[i] = isp_gen->isp_ini_cfg.isp_tunning_settings.sensor_temp[13*TEMP_COMP_MAX + i];
			}
		} else {
			for (i = 0; i < 13; i++) {
				index = i;
				if (isp_gen->sensor_info.temperature <= temp_mapping[i+1]) {
					break;
				}
			}
			temperature = clamp(isp_gen->sensor_info.temperature, temp_mapping[0], temp_mapping[13]);
			for (i = 0; i < TEMP_COMP_MAX; i++) {
				isp_gen->temp_info.temperature_param[i] = ValueInterp(temperature, temp_mapping[index], temp_mapping[index+1],
					isp_gen->isp_ini_cfg.isp_tunning_settings.sensor_temp[index*TEMP_COMP_MAX + i], isp_gen->isp_ini_cfg.isp_tunning_settings.sensor_temp[(index+1)*TEMP_COMP_MAX + i]);
			}
		}
		ISP_LIB_LOG(ISP_LOG_ISO, "sensor temperature=%d.  temperature_param = %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", isp_gen->sensor_info.temperature,
					isp_gen->temp_info.temperature_param[TEMP_COMP_2D_BLACK], isp_gen->temp_info.temperature_param[TEMP_COMP_2D_WHITE],
					isp_gen->temp_info.temperature_param[TEMP_COMP_3D_BLACK], isp_gen->temp_info.temperature_param[TEMP_COMP_3D_WHITE],
					isp_gen->temp_info.temperature_param[TEMP_COMP_EDGE_NSR], isp_gen->temp_info.temperature_param[TEMP_COMP_FLAT_NSR],
					isp_gen->temp_info.temperature_param[TEMP_COMP_DTC_STREN], isp_gen->temp_info.temperature_param[TEMP_COMP_BLC_R],
					isp_gen->temp_info.temperature_param[TEMP_COMP_BLC_G], isp_gen->temp_info.temperature_param[TEMP_COMP_BLC_B],
					isp_gen->temp_info.temperature_param[TEMP_COMP_SHARP], isp_gen->temp_info.temperature_param[TEMP_COMP_SATU_LOW],
					isp_gen->temp_info.temperature_param[TEMP_COMP_SATU_MID], isp_gen->temp_info.temperature_param[TEMP_COMP_SATU_HIGH]);
	} else {
		isp_gen->temp_info.temperature_param[TEMP_COMP_2D_BLACK] = 256;
		isp_gen->temp_info.temperature_param[TEMP_COMP_2D_WHITE] = 256;
		isp_gen->temp_info.temperature_param[TEMP_COMP_3D_BLACK] = 256;
		isp_gen->temp_info.temperature_param[TEMP_COMP_3D_WHITE] = 256;
		isp_gen->temp_info.temperature_param[TEMP_COMP_EDGE_NSR] = 256;
		isp_gen->temp_info.temperature_param[TEMP_COMP_FLAT_NSR] = 256;
		isp_gen->temp_info.temperature_param[TEMP_COMP_DTC_STREN] = 256;
		isp_gen->temp_info.temperature_param[TEMP_COMP_BLC_R] = 0;
		isp_gen->temp_info.temperature_param[TEMP_COMP_BLC_G] = 0;
		isp_gen->temp_info.temperature_param[TEMP_COMP_BLC_B] = 0;
		isp_gen->temp_info.temperature_param[TEMP_COMP_SHARP] = 256;
		isp_gen->temp_info.temperature_param[TEMP_COMP_SATU_LOW] = 256;
		isp_gen->temp_info.temperature_param[TEMP_COMP_SATU_MID] = 256;
		isp_gen->temp_info.temperature_param[TEMP_COMP_SATU_HIGH] = 256;
	}
}

void isp_get_software_ir_param(struct isp_lib_context *isp_gen)
{
	int light_stat_num[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int awb_stat_distance[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int awb_stat_distance_sum = 0, normal_win_cnt = 0, extra_win_cnt = 0, irlight_win_cnt = 0;
	int awb_dx = 0, awb_dy = 0;
	HW_U32 i = 0, j = 0, n = 0, k = 0, m = 0;
	HW_S32 rgain_ir = 0, bgain_ir = 0, rgain_ir_sum = 0, bgain_ir_sum = 0, cnt = 0;
	struct isp_awb_stats_s *awb_stats = &isp_gen->stats_ctx.stats.awb_stats;
	struct isp_param_config *param = &isp_gen->isp_ini_cfg;

	if (isp_gen->isp_ir_flag != ISP_IR_MODE)
		return;

	for (n = 0; n < ISP_AWB_ROW * ISP_AWB_COL; n++) {
		i = n / ISP_AWB_COL;
		j = n % ISP_AWB_COL;

		rgain_ir = awb_stats->awb_avg_r[i][j] * 256 / max(1, awb_stats->awb_avg_g[i][j]);
		bgain_ir = awb_stats->awb_avg_b[i][j] * 256 / max(1, awb_stats->awb_avg_g[i][j]);
		rgain_ir_sum += (rgain_ir - 256);
		bgain_ir_sum += (bgain_ir - 256);
		cnt++;

		for (k = 0; k < param->isp_3a_settings.awb_light_num; k++) {
			awb_dx = abs(param->isp_3a_settings.awb_light_info[k * 10 + 0] - rgain_ir);
			awb_dy = abs(param->isp_3a_settings.awb_light_info[k * 10 + 2] - bgain_ir);
			awb_stat_distance[k] = sqrtf(awb_dx*awb_dx + awb_dy*awb_dy);

			if(awb_stat_distance[k] < (param->isp_3a_settings.awb_light_info[k * 10 + 6] >> 1)) {
				light_stat_num[k] +=  10;
				break;
			} else {
				if(awb_stat_distance[k] < ISP_IR_DISTANCE_THRESHOLD)
					awb_stat_distance_sum += awb_stat_distance[k];
			}

			if(k == param->isp_3a_settings.awb_light_num - 1) {
				for(m = 0 ; m < param->isp_3a_settings.awb_light_num ; m++) {
					if(awb_stat_distance[m] < ISP_IR_DISTANCE_THRESHOLD && awb_stat_distance_sum > 0) {
						light_stat_num[m] += (awb_stat_distance[m] * 10) / awb_stat_distance_sum ;
					}
					if(awb_stat_distance_sum == 0) {
						light_stat_num[param->isp_3a_settings.awb_light_num] += 10;
						break;
					}
				}
			}
		}
		awb_stat_distance_sum = 0;
	}

	isp_gen->software_ir_info.rgain_ir = rgain_ir_sum / (cnt + 1);
	isp_gen->software_ir_info.bgain_ir = bgain_ir_sum / (cnt + 1);

	for(m = 0 ; m < param->isp_3a_settings.awb_light_num; m++) {
		if (param->isp_3a_settings.awb_light_info[m * 10 + 7] == ISP_IRLIGHT_COLOR_TEMP) {
			irlight_win_cnt = light_stat_num[m] / 10;
		} else {
			normal_win_cnt += light_stat_num[m] / 10;
		}
	}
	extra_win_cnt = light_stat_num[param->isp_3a_settings.awb_light_num] / 10;
	isp_gen->software_ir_info.irlight_win_cnt = irlight_win_cnt;
	isp_gen->software_ir_info.normal_win_cnt = normal_win_cnt;
	isp_gen->software_ir_info.extra_win_cnt = extra_win_cnt;
}

void __isp_ctx_config(struct isp_lib_context *isp_gen)
{
	__isp_ctx_apply_enable(isp_gen);
	FUNCTION_LOG;

	__isp_ctx_cfg_lib(isp_gen);
	FUNCTION_LOG;

	__isp_ctx_cfg_mod(isp_gen);
	FUNCTION_LOG;

	__get_sensor_temp_param(isp_gen);

	__isp_ctx_update_iso_cfg(isp_gen);
	FUNCTION_LOG;

	__isp_ctx_update_af_cfg(isp_gen);
	FUNCTION_LOG;

	__isp_ctx_update_ae_cfg(isp_gen);
	FUNCTION_LOG;

	__isp_ctx_update_awb_cfg(isp_gen);
	FUNCTION_LOG;

	__isp_ctx_update_gtm_cfg(isp_gen);
	FUNCTION_LOG;

	__isp_ctx_update_pltm_cfg(isp_gen);
	FUNCTION_LOG;

	__isp_ctx_update_afs_cfg(isp_gen);
	FUNCTION_LOG;

#if ISP_LIB_USE_MD
	__isp_ctx_update_md_cfg(isp_gen);
	FUNCTION_LOG;
#endif

	__isp_ctx_update_rolloff_cfg(isp_gen);
	FUNCTION_LOG;
}

void __isp_ctx_update(struct isp_lib_context *isp_gen)
{
	__isp_ctx_apply_enable(isp_gen);

	__isp_ctx_cfg_mod(isp_gen);

	__isp_ctx_update_iso_cfg(isp_gen);

	__isp_ctx_update_af_cfg(isp_gen);

	__isp_ctx_update_ae_cfg(isp_gen);

	__isp_ctx_update_awb_cfg(isp_gen);

	__isp_ctx_update_gtm_cfg(isp_gen);

	__isp_ctx_update_pltm_cfg(isp_gen);

	__isp_ctx_update_afs_cfg(isp_gen);

#if ISP_LIB_USE_MD
	__isp_ctx_update_md_cfg(isp_gen);
#endif

	__isp_ctx_update_rolloff_cfg(isp_gen);
}

int isp_ctx_algo_init(struct isp_lib_context *isp_gen, const struct isp_ctx_operations *ops)
{
	//ISO init
	isp_gen->iso_entity_ctx.iso_entity = iso_init(&isp_gen->iso_entity_ctx.ops);
	if (isp_gen->iso_entity_ctx.iso_entity == NULL || NULL == isp_gen->iso_entity_ctx.ops) {
		ISP_ERR("ISO Entity is BUSY or NULL!\n");
		return -1;
	} else {
		isp_gen->iso_entity_ctx.ops->isp_iso_get_params(isp_gen->iso_entity_ctx.iso_entity, &isp_gen->iso_entity_ctx.iso_param);
		isp_gen->iso_entity_ctx.iso_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	}
#if ISP_LIB_USE_AF
	//AF init
	isp_gen->af_entity_ctx.af_entity = af_init(&isp_gen->af_entity_ctx.ops);
	if (isp_gen->af_entity_ctx.af_entity == NULL ||	NULL == isp_gen->af_entity_ctx.ops) {
		ISP_ERR("AF Entity is BUSY or NULL!\n");
		return -1;
	} else {
		isp_gen->af_entity_ctx.ops->isp_af_get_params(isp_gen->af_entity_ctx.af_entity, &isp_gen->af_entity_ctx.af_param);
		isp_gen->af_entity_ctx.af_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	}
#endif
	//AFS init
	isp_gen->afs_entity_ctx.afs_entity = afs_init(&isp_gen->afs_entity_ctx.ops);
	if (isp_gen->afs_entity_ctx.afs_entity == NULL || NULL == isp_gen->afs_entity_ctx.ops) {
		ISP_ERR("AFS Entity is BUSY or NULL!\n");
		return -1;
	} else {
		isp_gen->afs_entity_ctx.ops->isp_afs_get_params(isp_gen->afs_entity_ctx.afs_entity, &isp_gen->afs_entity_ctx.afs_param);
		isp_gen->afs_entity_ctx.afs_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	}

#if ISP_LIB_USE_MD
	//MD init
	isp_gen->md_entity_ctx.md_entity = md_init(&isp_gen->md_entity_ctx.ops);
	if (isp_gen->md_entity_ctx.md_entity == NULL ||	NULL == isp_gen->md_entity_ctx.ops) {
		ISP_ERR("MD Entity is BUSY or NULL!\n");
		return -1;
	} else {
		isp_gen->md_entity_ctx.ops->isp_md_get_params(isp_gen->md_entity_ctx.md_entity, &isp_gen->md_entity_ctx.md_param);
		isp_gen->md_entity_ctx.md_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	}
#endif

	//AWB init
	isp_gen->awb_entity_ctx.awb_entity = awb_init(&isp_gen->awb_entity_ctx.ops);
	if (isp_gen->awb_entity_ctx.awb_entity == NULL || NULL == isp_gen->awb_entity_ctx.ops) {
		ISP_ERR("AWB Entity is BUSY or NULL!\n");
		return -1;
	} else {
		isp_gen->awb_entity_ctx.ops->isp_awb_get_params(isp_gen->awb_entity_ctx.awb_entity, &isp_gen->awb_entity_ctx.awb_param);
		isp_gen->awb_entity_ctx.awb_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	}

	//AE init
	isp_gen->ae_entity_ctx.ae_entity = ae_init(&isp_gen->ae_entity_ctx.ops);
	if (isp_gen->ae_entity_ctx.ae_entity == NULL ||	NULL == isp_gen->ae_entity_ctx.ops) {
		ISP_ERR("AE Entity is BUSY or NULL!\n");
		return -1;
	} else {
		isp_gen->ae_entity_ctx.ops->isp_ae_get_params(isp_gen->ae_entity_ctx.ae_entity, &isp_gen->ae_entity_ctx.ae_param);
		isp_gen->ae_entity_ctx.ae_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	}

	//GTM init
	isp_gen->gtm_entity_ctx.gtm_entity = gtm_init(&isp_gen->gtm_entity_ctx.ops);
	if (isp_gen->gtm_entity_ctx.gtm_entity == NULL || NULL == isp_gen->gtm_entity_ctx.ops) {
		ISP_ERR("GTM Entity is BUSY or NULL!\n");
		return -1;
	} else {
		isp_gen->gtm_entity_ctx.ops->isp_gtm_get_params(isp_gen->gtm_entity_ctx.gtm_entity, &isp_gen->gtm_entity_ctx.gtm_param);
		isp_gen->gtm_entity_ctx.gtm_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	}
	//PLTM init
	isp_gen->pltm_entity_ctx.pltm_entity = pltm_init(&isp_gen->pltm_entity_ctx.ops);
	if (isp_gen->pltm_entity_ctx.pltm_entity == NULL || NULL == isp_gen->pltm_entity_ctx.ops) {
		ISP_ERR("PLTM Entity is BUSY or NULL!\n");
		return -1;
	} else {
		isp_gen->pltm_entity_ctx.ops->isp_pltm_get_params(isp_gen->pltm_entity_ctx.pltm_entity, &isp_gen->pltm_entity_ctx.pltm_param);
		isp_gen->pltm_entity_ctx.pltm_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	}

	isp_gen->module_cfg.module_entity = isp_module_init();
	if (isp_gen->module_cfg.module_entity == NULL) {
		ISP_ERR("isp module Entity is BUSY or NULL!\n");
		return -1;
	}

#if ISP_LIB_USE_ROLLOFF
	//ROLLOFF init
	isp_gen->rolloff_entity_ctx.rolloff_entity = rolloff_init(&isp_gen->rolloff_entity_ctx.ops);
	if (isp_gen->rolloff_entity_ctx.rolloff_entity == NULL || NULL == isp_gen->rolloff_entity_ctx.ops) {
		ISP_ERR("ROLLOFF Entity is BUSY or NULL!\n");
		return -1;
	} else {
		isp_gen->rolloff_entity_ctx.ops->isp_rolloff_get_params(isp_gen->rolloff_entity_ctx.rolloff_entity, &isp_gen->rolloff_entity_ctx.rolloff_param);
		isp_gen->rolloff_entity_ctx.rolloff_param->isp_platform_id = isp_gen->module_cfg.isp_platform_id;
	}
#endif

	//other algorithm buffer alloc
	isp_gen->algo_save.local_wb_save = malloc(sizeof(struct local_wb_data_save));
	if (isp_gen->algo_save.local_wb_save == NULL) {
		ISP_ERR("local_wb_save alloc failed, no memory!\n");
		return -1;
	} else {
		memset(isp_gen->algo_save.local_wb_save, 0, sizeof(struct local_wb_data_save));
		isp_gen->algo_save.local_wb_save->gain_max = 1.0;
	}

	isp_gen->ops = ops;

	isp_gen->af_frame_cnt  = 0;
	isp_gen->ae_frame_cnt  = 0;
	isp_gen->awb_frame_cnt = 0;
	isp_gen->gtm_frame_cnt = 0;

	isp_gen->md_frame_cnt  = 0;
	isp_gen->afs_frame_cnt  = 0;
	isp_gen->iso_frame_cnt = 0;
	isp_gen->rolloff_frame_cnt = 0;
	isp_gen->alg_frame_cnt = 0;

	if (__isp_alloc_reg_tbl(isp_gen))
		return -1;

	pthread_mutex_init(&(isp_gen->ctx_lock), NULL);
	return 0;
}

HW_S32 isp_ctx_front_algo_run(struct isp_lib_context *isp_gen)
{
	pthread_mutex_lock(&(isp_gen->ctx_lock));

	isp_get_saved_regs(isp_gen);

#if ISP_AI_SCENE_CONF
	__isp_set_scene_param(isp_gen);
#endif

	isp_apply_settings(isp_gen);

	__isp_ae_set_params(isp_gen);
	__isp_ae_run(isp_gen);

#if ISP_LIB_USE_AF
	__isp_af_set_params(isp_gen);
	__isp_af_run(isp_gen);
#endif

	isp_gen->ae_frame_cnt++;
	isp_gen->af_frame_cnt++;
	FUNCTION_LOG;
	pthread_mutex_unlock(&(isp_gen->ctx_lock));
	FUNCTION_LOG;
	return 0;
}

HW_S32 isp_ctx_rear_algo_run(struct isp_lib_context *isp_gen)
{
	pthread_mutex_lock(&(isp_gen->ctx_lock));

	__get_sensor_temp_param(isp_gen);

	__isp_iso_set_params(isp_gen);
	__isp_iso_run(isp_gen);

	if (isp_gen->isp_ini_cfg.isp_test_settings.gtm_en) {
		__isp_gtm_set_params(isp_gen);
		__isp_gtm_run(isp_gen);
	}

	if (isp_gen->isp_ini_cfg.isp_test_settings.pltm_en) {
		__isp_pltm_set_params(isp_gen);
		__isp_pltm_run(isp_gen);
	}
	if (isp_gen->isp_ini_cfg.isp_test_settings.afs_en) {
		__isp_afs_set_params(isp_gen);
		__isp_afs_run(isp_gen);
	}
#if ISP_LIB_USE_MD
	if (isp_gen->isp_ini_cfg.isp_test_settings.af_en) {
		__isp_md_set_params(isp_gen);
		__isp_md_run(isp_gen);
	}
#endif

	if(isp_gen->isp_ir_flag != ISP_IR_MODE) {
		__isp_awb_set_params(isp_gen);
		__isp_awb_run(isp_gen);
	}

	if (isp_gen->isp_ini_cfg.isp_test_settings.lsc_en)
		config_lens_table(isp_gen, isp_gen->af_entity_ctx.af_result.std_code_output);

	if (isp_gen->isp_ini_cfg.isp_test_settings.msc_en) {
#if ISP_LIB_USE_ROLLOFF
		if (isp_gen->isp_ini_cfg.isp_tunning_settings.mff_mod >= 3) {
			__isp_rolloff_set_params(isp_gen);
			__isp_rolloff_run(isp_gen);
		}
#endif
		config_msc_table(isp_gen, isp_gen->af_entity_ctx.af_result.std_code_output, isp_gen->iso_entity_ctx.iso_result.shading_comp);
	}

	if (isp_gen->isp_ini_cfg.isp_test_settings.denoise_en || isp_gen->isp_ini_cfg.isp_test_settings.tdf_en) {
		config_block_nr_table(isp_gen, 0);
	}

	if (isp_gen->isp_ini_cfg.isp_test_settings.fpn_en) {
		__isp_fpn_set_params(isp_gen);
	}

	isp_apply_colormatrix(isp_gen);

	//isp_gen->module_cfg.cfa_cfg.min_rgb = isp_gen->isp_ini_cfg.isp_test_settings.defog_en ? 1023 : 0;

	FUNCTION_LOG;

	isp_hardware_update(isp_gen);

	isp_gen->awb_frame_cnt++;
	isp_gen->alg_frame_cnt ++;
	isp_gen->gtm_frame_cnt++;
	isp_gen->md_frame_cnt++;
	isp_gen->afs_frame_cnt ++;
	isp_gen->iso_frame_cnt++;
	isp_gen->rolloff_frame_cnt++;
	FUNCTION_LOG;
	//if (isp_gen->awb_frame_cnt % 10 == 0)
	//	__isp_dump_reg(isp_gen);
	pthread_mutex_unlock(&(isp_gen->ctx_lock));
	FUNCTION_LOG;
	return 0;
}

int isp_ctx_algo_exit(struct isp_lib_context *isp_gen)
{
	pthread_mutex_lock(&(isp_gen->ctx_lock));
#if ISP_LIB_USE_AF
	af_exit(isp_gen->af_entity_ctx.af_entity);
#endif
	afs_exit(isp_gen->afs_entity_ctx.afs_entity);
#if ISP_LIB_USE_MD
	md_exit(isp_gen->md_entity_ctx.md_entity);
#endif
	awb_exit(isp_gen->awb_entity_ctx.awb_entity);
	ae_exit(isp_gen->ae_entity_ctx.ae_entity);
	gtm_exit(isp_gen->gtm_entity_ctx.gtm_entity);
	pltm_exit(isp_gen->pltm_entity_ctx.pltm_entity);
	iso_exit(isp_gen->iso_entity_ctx.iso_entity);
	isp_module_exit(isp_gen->module_cfg.module_entity);
#if ISP_LIB_USE_ROLLOFF
	rolloff_exit(isp_gen->rolloff_entity_ctx.rolloff_entity);
#endif
	if(isp_gen->load_reg_base != NULL) {
		free(isp_gen->load_reg_base);
		isp_gen->load_reg_base = NULL;
	}

	//other algorithm buffer free
	if (isp_gen->algo_save.local_wb_save != NULL) {
		free(isp_gen->algo_save.local_wb_save);
		isp_gen->algo_save.local_wb_save = NULL;
	}

	pthread_mutex_unlock(&(isp_gen->ctx_lock));

	pthread_mutex_destroy(&(isp_gen->ctx_lock));

	return 0;
}

HW_S32 isp_ctx_update_ae_tbl(struct isp_lib_context *isp_gen, int sensor_fps)
{
	int i = 0;

	pthread_mutex_lock(&(isp_gen->ctx_lock));

	for(i = 0; i < isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].length; i++) {
		if(isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[i].max_exp < sensor_fps)
			isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[i].max_exp = sensor_fps;
		if(isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[i].min_exp < sensor_fps)
			isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_PREVIEW].ae_tbl[i].min_exp = sensor_fps;
	}
	for(i = 0; i < isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].length; i++) {
		if(isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].ae_tbl[i].max_exp < sensor_fps)
			isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].ae_tbl[i].max_exp = sensor_fps;
		if(isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].ae_tbl[i].min_exp < sensor_fps)
			isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_CAPTURE].ae_tbl[i].min_exp = sensor_fps;
	}
	for(i = 0; i < isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_VIDEO].length; i++) {
		if(isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_VIDEO].ae_tbl[i].max_exp < sensor_fps)
			isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_VIDEO].ae_tbl[i].max_exp = sensor_fps;
		if(isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_VIDEO].ae_tbl[i].min_exp < sensor_fps)
			isp_gen->ae_entity_ctx.ae_param->ae_ini.ae_tbl_scene[SCENE_MODE_VIDEO].ae_tbl[i].min_exp = sensor_fps;
	}
	isp_ae_set_params_helper(&isp_gen->ae_entity_ctx, ISP_AE_INI_DATA);
	isp_ae_set_params_helper(&isp_gen->ae_entity_ctx, ISP_AE_UPDATE_AE_TABLE);

	pthread_mutex_unlock(&(isp_gen->ctx_lock));

	return 0;
}

#if ISP_AI_SCENE_CONF
HW_S32 isp_ctx_set_scene(struct isp_lib_context *isp_gen, scene_mode_t scene_mode)
{
	pthread_mutex_lock(&(isp_gen->ctx_lock));

	if(scene_mode != isp_gen->ai_scene.cur_scene) {
		isp_gen->ai_scene.cur_scene = scene_mode;
		isp_gen->ai_scene.scene_change_flag = 1;
		isp_gen->ai_scene.scene_frame_cnt = 0;
	}

	pthread_mutex_unlock(&(isp_gen->ctx_lock));

	return 0;
}
#endif

int isp_ctx_config_update(struct isp_lib_context *isp_gen)
{
	pthread_mutex_lock(&(isp_gen->ctx_lock));

	__isp_ctx_update(isp_gen);

	pthread_mutex_unlock(&(isp_gen->ctx_lock));

	return 0;
}

int isp_ctx_config_reset(struct isp_lib_context *isp_gen)
{
	isp_ctx_config_init(isp_gen);
	return 0;
}

int isp_ctx_config_init(struct isp_lib_context *isp_gen)
{
	pthread_mutex_lock(&(isp_gen->ctx_lock));
	if (isp_gen->sensor_info.sensor_height == 0) {
		pthread_mutex_unlock(&(isp_gen->ctx_lock));
		ISP_ERR("sensor attribute is not init.\n");
		return -1;
	}
	FUNCTION_LOG;

	__isp_ctx_config(isp_gen);

	//for isp_apply_settings
	isp_gen->isp_3a_change_flags = 0xffffffff;
	isp_gen->isp_3a_change_flags &= ~ISP_SET_BRIGHTNESS;
	isp_gen->isp_3a_change_flags &= ~ISP_SET_CONTRAST;
	isp_gen->isp_3a_change_flags &= ~ISP_SET_GAIN_STR;
	isp_gen->isp_3a_change_flags &= ~ISP_SET_SCENE_MODE;

	if (isp_gen->isp_ir_flag == ISP_IR_MODE)
		isp_gen->tune.effect = ISP_COLORFX_GRAY;

	if (isp_gen->tune.effect != ISP_COLORFX_NONE)
		isp_gen->isp_3a_change_flags &= ~ISP_SET_HUE;

	if (isp_gen->initial_cfg.effect_hold_cnt) {
		isp_gen->isp_3a_change_flags &= ~ISP_SET_HUE;
		isp_gen->isp_3a_change_flags &= ~ISP_SET_EFFECT;
	}

	isp_apply_settings(isp_gen);

	isp_hardware_update(isp_gen);

	memset(&isp_gen->defog_ctx.min_rgb_pre[0], 0, 8*sizeof(int));
	pthread_mutex_unlock(&(isp_gen->ctx_lock));
	FUNCTION_LOG;

	return 0;
}

HW_S32 isp_ctx_config_exit(struct isp_lib_context *isp_gen)
{
	pthread_mutex_lock(&(isp_gen->ctx_lock));
	pthread_mutex_unlock(&(isp_gen->ctx_lock));
	return 0;
}


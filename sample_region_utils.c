#include "sample_comm.h"

/* 可放在 sample_region_utils.c / sample_vio.c */
td_s32 sample_region_attach_red_cover_to_venc0(td_void)
{
    /**************** 0. 句柄 & 目标通道 ****************/
    const ot_rgn_handle handle = 0;                   /* Region 句柄 */
    ot_mpp_chn chn = { OT_ID_VPSS, 1, 0 };            /* VENC dev 0 / chn 0 */

    /**************** 1. 创建 Region（只需 type） ****************/
    ot_rgn_attr rgn_attr;
    memset(&rgn_attr, 0, sizeof(rgn_attr));
    rgn_attr.type = OT_RGN_COVER;                     /* 只指定类型 */

    td_s32 ret = ss_mpi_rgn_create(handle, &rgn_attr);
    if (ret != TD_SUCCESS) {
        sample_print("ss_mpi_rgn_create failed %#x\n", ret);
        return ret;
    }

    /**************** 2. 填通道属性 & Attach ****************/
    ot_rgn_chn_attr chn_attr;
    memset(&chn_attr, 0, sizeof(chn_attr));

    chn_attr.is_show = TD_TRUE;                      /* 显示开关 */
    chn_attr.type    = OT_RGN_COVER;                 /* 必须一致 */

    /* --- cover_chn --- */
    chn_attr.attr.cover_chn.layer  = 0;              /* 层号 */
    chn_attr.attr.cover_chn.coord  = OT_COORD_ABS;   /* 绝对坐标 */

    /* -------------- cover 具体形状 -------------- */
    chn_attr.attr.cover_chn.cover.type                     = OT_COVER_RECT;
    chn_attr.attr.cover_chn.cover.rect_attr.is_solid       = TD_TRUE;
    chn_attr.attr.cover_chn.cover.rect_attr.thick          = 0;      /* 实心时无意义 */
    chn_attr.attr.cover_chn.cover.rect_attr.rect.x         = 200;
    chn_attr.attr.cover_chn.cover.rect_attr.rect.y         = 120;
    chn_attr.attr.cover_chn.cover.rect_attr.rect.width     = 320;
    chn_attr.attr.cover_chn.cover.rect_attr.rect.height    = 180;
    chn_attr.attr.cover_chn.cover.color                    = 0xFF0000; /* RRGGBB */

    ret = ss_mpi_rgn_attach_to_chn(handle, &chn, &chn_attr);
    if (ret != TD_SUCCESS) {
        sample_print("ss_mpi_rgn_attach_to_chn failed %#x\n", ret);
        (td_void)ss_mpi_rgn_destroy(handle);
    }
    return ret;
}



/* 可放在 sample_region_utils.c / sample_vio.c */
td_s32 sample_region_attach_red_cover_to_venc1(td_void)
{
    /**************** 0. 句柄 & 目标通道 ****************/
    const ot_rgn_handle handle = 0;                   /* Region 句柄 */
    ot_mpp_chn chn = { OT_ID_VPSS, 1, 1 };            /* VENC dev 0 / chn 0 */

    /**************** 1. 创建 Region（只需 type） ****************/
    ot_rgn_attr rgn_attr;
    memset(&rgn_attr, 0, sizeof(rgn_attr));
    rgn_attr.type = OT_RGN_COVER;                     /* 只指定类型 */

    td_s32 ret = ss_mpi_rgn_create(handle, &rgn_attr);
    if (ret != TD_SUCCESS) {
        sample_print("ss_mpi_rgn_create failed %#x\n", ret);
        return ret;
    }

    /**************** 2. 填通道属性 & Attach ****************/
    ot_rgn_chn_attr chn_attr;
    memset(&chn_attr, 0, sizeof(chn_attr));

    chn_attr.is_show = TD_TRUE;                      /* 显示开关 */
    chn_attr.type    = OT_RGN_COVER;                 /* 必须一致 */

    /* --- cover_chn --- */
    chn_attr.attr.cover_chn.layer  = 0;              /* 层号 */
    chn_attr.attr.cover_chn.coord  = OT_COORD_ABS;   /* 绝对坐标 */

    /* -------------- cover 具体形状 -------------- */
    chn_attr.attr.cover_chn.cover.type                     = OT_COVER_RECT;
    chn_attr.attr.cover_chn.cover.rect_attr.is_solid       = TD_TRUE;
    chn_attr.attr.cover_chn.cover.rect_attr.thick          = 0;      /* 实心时无意义 */
    chn_attr.attr.cover_chn.cover.rect_attr.rect.x         = 200;
    chn_attr.attr.cover_chn.cover.rect_attr.rect.y         = 120;
    chn_attr.attr.cover_chn.cover.rect_attr.rect.width     = 320;
    chn_attr.attr.cover_chn.cover.rect_attr.rect.height    = 180;
    chn_attr.attr.cover_chn.cover.color                    = 0xFF0000; /* RRGGBB */

    ret = ss_mpi_rgn_attach_to_chn(handle, &chn, &chn_attr);
    if (ret != TD_SUCCESS) {
        sample_print("ss_mpi_rgn_attach_to_chn failed %#x\n", ret);
        (td_void)ss_mpi_rgn_destroy(handle);
    }
    return ret;
}

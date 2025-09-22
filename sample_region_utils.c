#include "sample_comm.h"

#define SAMPLE_REGION_OSD_CANVAS_WIDTH           512U
#define SAMPLE_REGION_OSD_CANVAS_HEIGHT          128U
#define SAMPLE_REGION_OSD_FONT_WIDTH             16U
#define SAMPLE_REGION_OSD_FONT_HEIGHT            32U
#define SAMPLE_REGION_OSD_COLUMN_SPACING         4U
#define SAMPLE_REGION_OSD_ROW_SPACING            8U
#define SAMPLE_REGION_OSD_ALPHA_MASK             0x8000
#define SAMPLE_REGION_OSD_COLOR_TRANSPARENT      0x0000
#define SAMPLE_REGION_OSD_COLOR_FOREGROUND       (SAMPLE_REGION_OSD_ALPHA_MASK | 0x7FFF)

static const td_u16 g_sample_region_osd_glyph_0[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x07c0,     0x0c30,     0x1830,     0x1818,
    0x3818,     0x301c,     0x300c,     0x300c,     0x700c,     0x700c,     0x700c,     0x700c,
    0x700c,     0x300c,     0x300c,     0x301c,     0x3018,     0x1818,     0x1818,     0x0c30,
    0x0660,     0x0180,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_1[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0080,     0x0380,     0x0780,     0x0180,
    0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,
    0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,
    0x07f0,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_2[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x07e0,     0x1830,     0x1018,     0x3018,
    0x301c,     0x381c,     0x3818,     0x0018,     0x0018,     0x0030,     0x0060,     0x0040,
    0x0080,     0x0100,     0x0200,     0x0400,     0x0804,     0x1004,     0x300c,     0x2038,
    0x3ff8,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_3[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0fc0,     0x1830,     0x3030,     0x3018,
    0x3818,     0x1018,     0x0018,     0x0030,     0x0060,     0x03c0,     0x01e0,     0x0030,
    0x0018,     0x0018,     0x000c,     0x000c,     0x300c,     0x381c,     0x3018,     0x3030,
    0x0c60,     0x0380,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_4[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0020,     0x0060,     0x00e0,     0x00e0,
    0x0160,     0x0360,     0x0260,     0x0460,     0x0460,     0x0860,     0x1060,     0x1060,
    0x2060,     0x6060,     0x7ffe,     0x0060,     0x0060,     0x0060,     0x0060,     0x0060,
    0x01fc,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_5[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x1ff8,     0x1ff8,     0x1000,     0x1000,
    0x1000,     0x1000,     0x1000,     0x1000,     0x17e0,     0x1830,     0x1018,     0x0018,
    0x000c,     0x000c,     0x000c,     0x100c,     0x380c,     0x3018,     0x3018,     0x1030,
    0x0c60,     0x0380,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_6[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x03f0,     0x0418,     0x0818,     0x1818,
    0x1000,     0x3000,     0x3000,     0x3000,     0x33f0,     0x7438,     0x7818,     0x700c,
    0x700c,     0x700c,     0x300c,     0x300c,     0x300c,     0x300c,     0x1808,     0x1c18,
    0x0e70,     0x0180,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_7[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x1ffc,     0x3ffc,     0x3008,     0x2010,
    0x2010,     0x0020,     0x0020,     0x0060,     0x0040,     0x00c0,     0x0080,     0x0180,
    0x0180,     0x0180,     0x0300,     0x0300,     0x0300,     0x0300,     0x0300,     0x0700,
    0x0300,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_8[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0fe0,     0x1810,     0x3018,     0x300c,
    0x300c,     0x300c,     0x3008,     0x3818,     0x1e30,     0x0fe0,     0x07e0,     0x18f0,
    0x3038,     0x3018,     0x600c,     0x600c,     0x600c,     0x600c,     0x3008,     0x1018,
    0x0c70,     0x0380,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_9[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0fc0,     0x1830,     0x3018,     0x3018,
    0x7018,     0x600c,     0x600c,     0x600c,     0x700c,     0x301c,     0x302c,     0x386c,
    0x0fcc,     0x001c,     0x001c,     0x0018,     0x0018,     0x1030,     0x3830,     0x3860,
    0x18c0,     0x0700,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_I[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0ff0,     0x0ff0,     0x0180,     0x0180,
    0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,
    0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,     0x0180,
    0x0180,     0x0180,     0x0ff0,     0x0ff0,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_N[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x1e18,     0x1e18,     0x1e18,     0x1e18,
    0x1b18,     0x1b18,     0x1b18,     0x1b18,     0x1998,     0x1998,     0x1998,     0x1998,
    0x18d8,     0x18d8,     0x18d8,     0x18d8,     0x1878,     0x1878,     0x1878,     0x1878,
    0x1838,     0x1838,     0x1838,     0x1818,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_O[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0fc0,     0x1860,     0x3030,     0x3030,
    0x6018,     0x6018,     0x6018,     0x6018,     0x6018,     0x6018,     0x6018,     0x6018,
    0x6018,     0x6018,     0x6018,     0x6018,     0x6018,     0x6018,     0x6018,     0x6018,
    0x3030,     0x3030,     0x1860,     0x0fc0,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_U[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x1818,     0x1818,     0x1818,     0x1818,
    0x1818,     0x1818,     0x1818,     0x1818,     0x1818,     0x1818,     0x1818,     0x1818,
    0x1818,     0x1818,     0x1818,     0x1818,     0x1818,     0x1818,     0x1818,     0x1818,
    0x1860,     0x1860,     0x1860,     0x0fc0,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_T[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x3ffc,     0x3ffc,     0x3ffc,     0x03c0,
    0x03c0,     0x03c0,     0x03c0,     0x03c0,     0x03c0,     0x03c0,     0x03c0,     0x03c0,
    0x03c0,     0x03c0,     0x03c0,     0x03c0,     0x03c0,     0x03c0,     0x03c0,     0x03c0,
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_colon[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x03c0,     0x03c0,
    0x03c0,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
    0x0000,     0x03c0,     0x03c0,     0x03c0,     0x0000,     0x0000,     0x0000,     0x0000,
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_space[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

typedef struct {
    char ch;
    const td_u8 *glyph;
} sample_region_osd_glyph_entry;

static const sample_region_osd_glyph_entry g_sample_region_osd_glyph_map[] = {
    { '0', (const td_u8 *)g_sample_region_osd_glyph_0 },
    { '1', (const td_u8 *)g_sample_region_osd_glyph_1 },
    { '2', (const td_u8 *)g_sample_region_osd_glyph_2 },
    { '3', (const td_u8 *)g_sample_region_osd_glyph_3 },
    { '4', (const td_u8 *)g_sample_region_osd_glyph_4 },
    { '5', (const td_u8 *)g_sample_region_osd_glyph_5 },
    { '6', (const td_u8 *)g_sample_region_osd_glyph_6 },
    { '7', (const td_u8 *)g_sample_region_osd_glyph_7 },
    { '8', (const td_u8 *)g_sample_region_osd_glyph_8 },
    { '9', (const td_u8 *)g_sample_region_osd_glyph_9 },
    { 'I', (const td_u8 *)g_sample_region_osd_glyph_I },
    { 'N', (const td_u8 *)g_sample_region_osd_glyph_N },
    { 'O', (const td_u8 *)g_sample_region_osd_glyph_O },
    { 'U', (const td_u8 *)g_sample_region_osd_glyph_U },
    { 'T', (const td_u8 *)g_sample_region_osd_glyph_T },
    { ':', (const td_u8 *)g_sample_region_osd_glyph_colon },
    { ' ', (const td_u8 *)g_sample_region_osd_glyph_space },
};

static const td_u16 *sample_region_osd_find_glyph(char ch)
{
    td_u32 i;

    for (i = 0; i < (sizeof(g_sample_region_osd_glyph_map) / sizeof(g_sample_region_osd_glyph_map[0])); ++i) {
        if (g_sample_region_osd_glyph_map[i].ch == ch) {
            return (const td_u16 *)(const td_void *)g_sample_region_osd_glyph_map[i].glyph;
        }
    }

    return TD_NULL;
}

static td_void sample_region_osd_clear_canvas(td_u16 *dst, td_u32 stride_pixels, td_u32 width, td_u32 height)
{
    td_u32 row;

    if (dst == TD_NULL) {
        return;
    }

    for (row = 0; row < height; ++row) {
        td_u32 col;
        td_u16 *line = dst + row * stride_pixels;

        for (col = 0; col < width; ++col) {
            line[col] = SAMPLE_REGION_OSD_COLOR_TRANSPARENT;
        }
    }
}

static td_void sample_region_osd_draw_glyph(td_u16 *dst, td_u32 stride_pixels, td_u32 canvas_width,
    td_u32 canvas_height, td_u32 origin_x, td_u32 origin_y, const td_u16 *glyph, td_u16 color)
{
    td_u32 row;
    td_u16 pixel_color;

    if ((dst == TD_NULL) || (glyph == TD_NULL)) {
        return;
    }

    if ((origin_x + SAMPLE_REGION_OSD_FONT_WIDTH > canvas_width) ||
        (origin_y + SAMPLE_REGION_OSD_FONT_HEIGHT > canvas_height)) {
        return;
    }

    pixel_color = color | SAMPLE_REGION_OSD_ALPHA_MASK;

    for (row = 0; row < SAMPLE_REGION_OSD_FONT_HEIGHT; ++row) {
        td_u32 col;
        td_u16 bits = glyph[row];
        td_u16 *line = dst + (origin_y + row) * stride_pixels + origin_x;

        for (col = 0; col < SAMPLE_REGION_OSD_FONT_WIDTH; ++col) {
            td_u16 mask = (td_u16)(1U << (SAMPLE_REGION_OSD_FONT_WIDTH - 1 - col));

            if ((bits & mask) != 0) {
                line[col] = pixel_color;
            }
        }
    }
}

static td_void sample_region_osd_draw_line(td_u16 *dst, td_u32 stride_pixels, td_u32 canvas_width,
    td_u32 canvas_height, td_u32 start_x, td_u32 start_y, const char *text, td_u16 color)
{
    td_u32 cursor_x;
    td_u32 cursor_y;

    if ((dst == TD_NULL) || (text == TD_NULL)) {
        return;
    }

    cursor_x = start_x;
    cursor_y = start_y;

    while (*text != '\0') {
        const char ch = *text++;

        if (ch == '\n') {
            cursor_x = start_x;
            cursor_y += SAMPLE_REGION_OSD_FONT_HEIGHT + SAMPLE_REGION_OSD_ROW_SPACING;
            if (cursor_y + SAMPLE_REGION_OSD_FONT_HEIGHT > canvas_height) {
                break;
            }
            continue;
        }

        const td_u16 *glyph = sample_region_osd_find_glyph(ch);
        if (glyph == TD_NULL) {
            glyph = sample_region_osd_find_glyph(' ');
        }

        if (glyph == TD_NULL) {
            continue;
        }

        if (cursor_x + SAMPLE_REGION_OSD_FONT_WIDTH > canvas_width) {
            cursor_x = start_x;
            cursor_y += SAMPLE_REGION_OSD_FONT_HEIGHT + SAMPLE_REGION_OSD_ROW_SPACING;
            if (cursor_y + SAMPLE_REGION_OSD_FONT_HEIGHT > canvas_height) {
                break;
            }
        }

        sample_region_osd_draw_glyph(dst, stride_pixels, canvas_width, canvas_height, cursor_x, cursor_y, glyph,
            color);
        cursor_x += SAMPLE_REGION_OSD_FONT_WIDTH + SAMPLE_REGION_OSD_COLUMN_SPACING;
    }
}

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

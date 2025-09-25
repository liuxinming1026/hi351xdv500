#include <string.h>
#include <time.h>

#include "sample_comm.h"

#define SAMPLE_REGION_OSD_CANVAS_WIDTH           512U
#define SAMPLE_REGION_OSD_CANVAS_HEIGHT          128U
#define SAMPLE_REGION_OSD_FONT_WIDTH             16U
#define SAMPLE_REGION_OSD_FONT_HEIGHT            32U
#define SAMPLE_REGION_OSD_COLUMN_SPACING         4U
#define SAMPLE_REGION_OSD_ROW_SPACING            8U
#define SAMPLE_REGION_OSD_PADDING_X              (SAMPLE_REGION_OSD_COLUMN_SPACING * 5)
#define SAMPLE_REGION_OSD_PADDING_Y              (SAMPLE_REGION_OSD_ROW_SPACING * 2)
#define SAMPLE_REGION_OSD_CLOCK_PADDING_X        (SAMPLE_REGION_OSD_COLUMN_SPACING * 2)
#define SAMPLE_REGION_OSD_CLOCK_PADDING_Y        (SAMPLE_REGION_OSD_ROW_SPACING)
#define SAMPLE_REGION_OSD_CLOCK_MARGIN_X         16U
#define SAMPLE_REGION_OSD_CLOCK_MARGIN_Y         16U
#define SAMPLE_REGION_OSD_CLOCK_TEMPLATE         "0000-00-00 00-00-00"
#define SAMPLE_REGION_OSD_ALPHA_MASK             0x8000
#define SAMPLE_REGION_OSD_COLOR_TRANSPARENT      0x0000
#define SAMPLE_REGION_OSD_COLOR_FOREGROUND       (SAMPLE_REGION_OSD_ALPHA_MASK | 0x7C00)

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
    0x03c0,     0x03c0,     0x03c0,     0x03c0,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_colon[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x03c0,     0x03c0,
    0x03c0,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
    0x0000,     0x03c0,     0x03c0,     0x03c0,     0x0000,     0x0000,     0x0000,     0x0000,
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
};

static const td_u16 g_sample_region_osd_glyph_dash[SAMPLE_REGION_OSD_FONT_HEIGHT] = {
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
    0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0ff0,     0x0ff0,
    0x0ff0,     0x0ff0,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,     0x0000,
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
    { '-', (const td_u8 *)g_sample_region_osd_glyph_dash },
    { ' ', (const td_u8 *)g_sample_region_osd_glyph_space },
};

typedef enum {
    SAMPLE_REGION_OSD_ROLE_COUNTER = 0,
    SAMPLE_REGION_OSD_ROLE_CLOCK,
} sample_region_osd_role;

typedef struct {
    ot_rgn_handle handle;
    ot_mpp_chn chn;
    ot_size canvas;
    ot_point point;
    ot_size video_size;
    td_u32 layer;
    td_u32 padding_x;
    td_u32 padding_y;
    td_bool created;
    td_bool attached;
    sample_region_osd_role role;
    td_u32 last_in;
    td_u32 last_out;
    td_char last_text[64];
} sample_region_osd_context;

static sample_region_osd_context g_sample_region_osd_ctx_venc0 = {
    .handle = 0,
    .chn = { OT_ID_VPSS, 0, 0 },
    .layer = 0,
    .role = SAMPLE_REGION_OSD_ROLE_COUNTER,
};

static sample_region_osd_context g_sample_region_osd_ctx_venc1 = {
    .handle = 1,
    .chn = { OT_ID_VPSS, 1, 0 },
    .layer = 0,
    .role = SAMPLE_REGION_OSD_ROLE_COUNTER,
};

static sample_region_osd_context g_sample_region_osd_time_ctx_venc0 = {
    .handle = 2,
    .chn = { OT_ID_VPSS, 0, 0 },
    .layer = 1,
    .role = SAMPLE_REGION_OSD_ROLE_CLOCK,
};

static sample_region_osd_context g_sample_region_osd_time_ctx_venc1 = {
    .handle = 3,
    .chn = { OT_ID_VPSS, 1, 0 },
    .layer = 1,
    .role = SAMPLE_REGION_OSD_ROLE_CLOCK,
};

static td_void sample_region_osd_prepare_layout(sample_region_osd_context *ctx);
static td_s32 sample_region_osd_set_video_size(sample_region_osd_context *ctx, td_u32 width, td_u32 height);
static td_s32 sample_region_osd_update_display_position(sample_region_osd_context *ctx);
static td_s32 sample_region_osd_draw_text(sample_region_osd_context *ctx, const char *text);
static td_s32 sample_region_osd_init_ctx(sample_region_osd_context *ctx);
static td_s32 sample_region_osd_update_counter_ctx(sample_region_osd_context *ctx, td_u32 in_cnt, td_u32 out_cnt);
static td_s32 sample_region_osd_update_time_ctx(sample_region_osd_context *ctx);
static td_s32 sample_region_osd_destroy_ctx(sample_region_osd_context *ctx);

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

static td_u32 sample_region_osd_measure_text_width(const char *text)
{
    td_u32 line_width = 0;
    td_u32 max_width = 0;
    td_bool has_chars_in_line = TD_FALSE;

    if (text == TD_NULL) {
        return 0;
    }

    while (*text != '\0') {
        const char ch = *text++;

        if (ch == '\n') {
            if (line_width > max_width) {
                max_width = line_width;
            }
            line_width = 0;
            has_chars_in_line = TD_FALSE;
            continue;
        }

        const td_u16 *glyph = sample_region_osd_find_glyph(ch);
        if (glyph == TD_NULL) {
            glyph = sample_region_osd_find_glyph(' ');
        }

        if (glyph == TD_NULL) {
            continue;
        }

        if (has_chars_in_line == TD_TRUE) {
            line_width += SAMPLE_REGION_OSD_COLUMN_SPACING;
        }

        line_width += SAMPLE_REGION_OSD_FONT_WIDTH;
        has_chars_in_line = TD_TRUE;
    }

    if (line_width > max_width) {
        max_width = line_width;
    }

    return max_width;
}

static td_s32 sample_region_osd_set_video_size(sample_region_osd_context *ctx, td_u32 width, td_u32 height)
{
    ot_point old_point;

    if (ctx == TD_NULL) {
        return TD_FAILURE;
    }

    ctx->video_size.width = width;
    ctx->video_size.height = height;

    if (ctx->role != SAMPLE_REGION_OSD_ROLE_CLOCK) {
        return TD_SUCCESS;
    }

    old_point = ctx->point;
    sample_region_osd_prepare_layout(ctx);

    if ((ctx->attached == TD_TRUE) && ((old_point.x != ctx->point.x) || (old_point.y != ctx->point.y))) {
        td_s32 ret = sample_region_osd_update_display_position(ctx);
        if (ret != TD_SUCCESS) {
            sample_print("sample_region_osd_update_display_position failed %#x\n", ret);
            return ret;
        }
    }

    return TD_SUCCESS;
}

static td_s32 sample_region_osd_update_display_position(sample_region_osd_context *ctx)
{
    ot_rgn_chn_attr chn_attr;

    if ((ctx == TD_NULL) || (ctx->attached != TD_TRUE)) {
        return TD_SUCCESS;
    }

    (td_void)memset(&chn_attr, 0, sizeof(chn_attr));
    chn_attr.is_show = TD_TRUE;
    chn_attr.type = OT_RGN_OVERLAYEX;
    chn_attr.attr.overlayex_chn.point = ctx->point;
    chn_attr.attr.overlayex_chn.layer = ctx->layer;
    chn_attr.attr.overlayex_chn.fg_alpha = 255;
    chn_attr.attr.overlayex_chn.bg_alpha = 0;

    return ss_mpi_rgn_set_display_attr(ctx->handle, &ctx->chn, &chn_attr);
}

static td_s32 sample_region_osd_draw_text(sample_region_osd_context *ctx, const char *text)
{
    ot_rgn_canvas_info canvas_info;
    td_u32 stride_pixels;
    td_u32 text_width;
    td_u32 start_x;
    td_s32 ret;

    if ((ctx == TD_NULL) || (text == TD_NULL)) {
        return TD_FAILURE;
    }

    (td_void)memset(&canvas_info, 0, sizeof(canvas_info));
    ret = ss_mpi_rgn_get_canvas_info(ctx->handle, &canvas_info);
    if (ret != TD_SUCCESS) {
        sample_print("ss_mpi_rgn_get_canvas_info failed %#x\n", ret);
        return ret;
    }

    if ((canvas_info.virt_addr == TD_NULL) || (canvas_info.stride == 0)) {
        sample_print("invalid canvas info\n");
        return TD_FAILURE;
    }

    stride_pixels = canvas_info.stride / sizeof(td_u16);
    sample_region_osd_clear_canvas((td_u16 *)canvas_info.virt_addr, stride_pixels, ctx->canvas.width, ctx->canvas.height);

    text_width = sample_region_osd_measure_text_width(text);
    start_x = ctx->padding_x;
    if ((start_x >= ctx->canvas.width) || (text_width + start_x > ctx->canvas.width)) {
        start_x = 0;
    }

    sample_region_osd_draw_line((td_u16 *)canvas_info.virt_addr, stride_pixels, ctx->canvas.width, ctx->canvas.height,
        start_x, ctx->padding_y, text, SAMPLE_REGION_OSD_COLOR_FOREGROUND);

    ret = ss_mpi_rgn_update_canvas(ctx->handle);
    if (ret != TD_SUCCESS) {
        sample_print("ss_mpi_rgn_update_canvas failed %#x\n", ret);
        return ret;
    }

    if (snprintf_s(ctx->last_text, sizeof(ctx->last_text), sizeof(ctx->last_text) - 1, "%s", text) < 0) {
        ctx->last_text[sizeof(ctx->last_text) - 1] = '\0';
    }

    return TD_SUCCESS;
}

static td_s32 sample_region_osd_format_time_string(char *buffer, td_u32 buffer_len)
{
    time_t now = time(TD_NULL);
    struct tm local_tm;

    if ((buffer == TD_NULL) || (buffer_len == 0)) {
        return TD_FAILURE;
    }

    if (now == (time_t)(-1)) {
        sample_print("time failed\n");
        return TD_FAILURE;
    }

    if (localtime_r(&now, &local_tm) == TD_NULL) {
        sample_print("localtime_r failed\n");
        return TD_FAILURE;
    }

    if (strftime(buffer, buffer_len, "%Y-%m-%d %H-%M-%S", &local_tm) == 0) {
        sample_print("strftime failed\n");
        return TD_FAILURE;
    }

    return TD_SUCCESS;
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

static td_u32 sample_region_osd_align2(td_u32 value)
{
    return (value + 1U) & (~1U);
}

static td_void sample_region_osd_prepare_layout(sample_region_osd_context *ctx)
{
    if (ctx == TD_NULL) {
        return;
    }

    if (ctx->role == SAMPLE_REGION_OSD_ROLE_CLOCK) {
        const char *template_text = SAMPLE_REGION_OSD_CLOCK_TEMPLATE;
        td_u32 text_width = sample_region_osd_measure_text_width(template_text);
        td_u32 padding_x = SAMPLE_REGION_OSD_CLOCK_PADDING_X;
        td_u32 padding_y = SAMPLE_REGION_OSD_CLOCK_PADDING_Y;
        ot_point new_point = { 0 };
        td_u32 margin_x = SAMPLE_REGION_OSD_CLOCK_MARGIN_X;
        td_u32 margin_y = SAMPLE_REGION_OSD_CLOCK_MARGIN_Y;
        td_u32 canvas_width = sample_region_osd_align2(text_width + padding_x * 2);
        td_u32 canvas_height = sample_region_osd_align2(SAMPLE_REGION_OSD_FONT_HEIGHT + padding_y * 2);

        if (ctx->video_size.width > canvas_width) {
            td_u32 available_x = ctx->video_size.width - canvas_width;
            if (available_x > margin_x) {
                new_point.x = available_x - margin_x;
            } else {
                new_point.x = available_x;
            }
        }

        if (ctx->video_size.height > canvas_height) {
            td_u32 available_y = ctx->video_size.height - canvas_height;
            if (available_y > margin_y) {
                new_point.y = available_y - margin_y;
            } else {
                new_point.y = available_y;
            }
        }

        new_point.x &= (~1U);
        new_point.y &= (~1U);

        ctx->canvas.width = canvas_width;
        ctx->canvas.height = canvas_height;
        ctx->padding_x = padding_x;
        ctx->padding_y = padding_y;
        ctx->point = new_point;
        return;
    }

    ctx->canvas.width = SAMPLE_REGION_OSD_CANVAS_WIDTH;
    ctx->canvas.height = SAMPLE_REGION_OSD_CANVAS_HEIGHT;
    ctx->padding_x = SAMPLE_REGION_OSD_PADDING_X;
    ctx->padding_y = SAMPLE_REGION_OSD_PADDING_Y;

    ctx->point.x = 0;
    ctx->point.y = 0;
}

static td_s32 sample_region_osd_destroy_ctx(sample_region_osd_context *ctx)
{
    td_s32 ret = TD_SUCCESS;

    if (ctx == TD_NULL) {
        return TD_FAILURE;
    }

    if (ctx->attached == TD_TRUE) {
        td_s32 tmp = ss_mpi_rgn_detach_from_chn(ctx->handle, &ctx->chn);
        if (tmp != TD_SUCCESS) {
            sample_print("ss_mpi_rgn_detach_from_chn failed %#x\n", tmp);
            ret = tmp;
        } else {
            ctx->attached = TD_FALSE;
        }
    }

    if (ctx->created == TD_TRUE) {
        td_s32 tmp = ss_mpi_rgn_destroy(ctx->handle);
        if (tmp != TD_SUCCESS) {
            sample_print("ss_mpi_rgn_destroy failed %#x\n", tmp);
            if (ret == TD_SUCCESS) {
                ret = tmp;
            }
        } else {
            ctx->created = TD_FALSE;
        }
    }

    ctx->last_in = 0;
    ctx->last_out = 0;
    ctx->last_text[0] = '\0';
    sample_region_osd_prepare_layout(ctx);

    return ret;
}

static td_s32 sample_region_osd_init_ctx(sample_region_osd_context *ctx)
{
    td_s32 ret;
    ot_rgn_attr rgn_attr;
    ot_rgn_chn_attr chn_attr;

    if (ctx == TD_NULL) {
        return TD_FAILURE;
    }

    if (ctx->attached == TD_TRUE) {
        return TD_SUCCESS;
    }

    sample_region_osd_prepare_layout(ctx);

    if (ctx->created != TD_TRUE) {
        (td_void)memset(&rgn_attr, 0, sizeof(rgn_attr));
        rgn_attr.type = OT_RGN_OVERLAYEX;
        rgn_attr.attr.overlayex.pixel_format = OT_PIXEL_FORMAT_ARGB_1555;
        rgn_attr.attr.overlayex.bg_color = SAMPLE_REGION_OSD_COLOR_TRANSPARENT;
        rgn_attr.attr.overlayex.size.width = ctx->canvas.width;
        rgn_attr.attr.overlayex.size.height = ctx->canvas.height;
        rgn_attr.attr.overlayex.canvas_num = 1;

        ret = ss_mpi_rgn_create(ctx->handle, &rgn_attr);
        if (ret != TD_SUCCESS) {
            sample_print("ss_mpi_rgn_create failed %#x\n", ret);
            return ret;
        }
        ctx->created = TD_TRUE;
    }

    (td_void)memset(&chn_attr, 0, sizeof(chn_attr));
    chn_attr.is_show = TD_TRUE;
    chn_attr.type = OT_RGN_OVERLAYEX;
    chn_attr.attr.overlayex_chn.layer = ctx->layer;
    chn_attr.attr.overlayex_chn.point.x = ctx->point.x;
    chn_attr.attr.overlayex_chn.point.y = ctx->point.y;
    chn_attr.attr.overlayex_chn.fg_alpha = 255;
    chn_attr.attr.overlayex_chn.bg_alpha = 0;

    ret = ss_mpi_rgn_attach_to_chn(ctx->handle, &ctx->chn, &chn_attr);
    if (ret != TD_SUCCESS) {
        sample_print("ss_mpi_rgn_attach_to_chn failed %#x\n", ret);
        if (ctx->created == TD_TRUE) {
            (td_void)ss_mpi_rgn_destroy(ctx->handle);
            ctx->created = TD_FALSE;
        }
        return ret;
    }
    ctx->attached = TD_TRUE;

    ctx->last_in = 0;
    ctx->last_out = 0;
    ctx->last_text[0] = '\0';

    if (ctx->role == SAMPLE_REGION_OSD_ROLE_COUNTER) {
        ctx->last_in = (td_u32)(~0U);
        ctx->last_out = (td_u32)(~0U);
        ret = sample_region_osd_update_counter_ctx(ctx, 0, 0);
        if (ret != TD_SUCCESS) {
            (td_void)sample_region_osd_destroy_ctx(ctx);
            return ret;
        }
    } else if (ctx->role == SAMPLE_REGION_OSD_ROLE_CLOCK) {
        ret = sample_region_osd_update_time_ctx(ctx);
        if (ret != TD_SUCCESS) {
            (td_void)sample_region_osd_destroy_ctx(ctx);
            return ret;
        }
    }

    return TD_SUCCESS;
}

static td_s32 sample_region_osd_update_counter_ctx(sample_region_osd_context *ctx, td_u32 in_cnt, td_u32 out_cnt)
{
    char text[64];
    td_s32 ret;

    if (ctx == TD_NULL) {
        return TD_FAILURE;
    }

    if (ctx->attached != TD_TRUE) {
        ret = sample_region_osd_init_ctx(ctx);
        if (ret != TD_SUCCESS) {
            return ret;
        }
    }

    if ((ctx->last_in == in_cnt) && (ctx->last_out == out_cnt)) {
        return TD_SUCCESS;
    }

    if (snprintf_s(text, sizeof(text), sizeof(text) - 1, "IN: %u\nOUT: %u", in_cnt, out_cnt) < 0) {
        sample_print("snprintf_s failed\n");
        return TD_FAILURE;
    }

    ret = sample_region_osd_draw_text(ctx, text);
    if (ret != TD_SUCCESS) {
        return ret;
    }

    ctx->last_in = in_cnt;
    ctx->last_out = out_cnt;

    return TD_SUCCESS;
}

static td_s32 sample_region_osd_update_time_ctx(sample_region_osd_context *ctx)
{
    char text[64];
    td_s32 ret;

    if (ctx == TD_NULL) {
        return TD_FAILURE;
    }

    if (ctx->attached != TD_TRUE) {
        ret = sample_region_osd_init_ctx(ctx);
        if (ret != TD_SUCCESS) {
            return ret;
        }
    }

    ret = sample_region_osd_format_time_string(text, sizeof(text));
    if (ret != TD_SUCCESS) {
        return ret;
    }

    if ((ctx->last_text[0] != '\0') && (strcmp(ctx->last_text, text) == 0)) {
        return TD_SUCCESS;
    }

    return sample_region_osd_draw_text(ctx, text);
}

/* 可放在 sample_region_utils.c / sample_vio.c */
td_s32 sample_region_attach_red_cover_to_venc0(td_void)
{
    return sample_region_osd_init_ctx(&g_sample_region_osd_ctx_venc0);
}



/* 可放在 sample_region_utils.c / sample_vio.c */
td_s32 sample_region_attach_red_cover_to_venc1(td_void)
{
    return sample_region_osd_init_ctx(&g_sample_region_osd_ctx_venc1);
}

td_s32 sample_region_osd_update_venc0(td_u32 in_cnt, td_u32 out_cnt)
{
    return sample_region_osd_update_counter_ctx(&g_sample_region_osd_ctx_venc0, in_cnt, out_cnt);
}

td_s32 sample_region_osd_update_venc1(td_u32 in_cnt, td_u32 out_cnt)
{
    return sample_region_osd_update_counter_ctx(&g_sample_region_osd_ctx_venc1, in_cnt, out_cnt);
}

td_s32 sample_region_osd_stop_venc0(td_void)
{
    return sample_region_osd_destroy_ctx(&g_sample_region_osd_ctx_venc0);
}

td_s32 sample_region_osd_stop_venc1(td_void)
{
    return sample_region_osd_destroy_ctx(&g_sample_region_osd_ctx_venc1);
}

td_s32 sample_region_attach_time_to_venc0(td_u32 video_width, td_u32 video_height)
{
    td_s32 ret = sample_region_osd_set_video_size(&g_sample_region_osd_time_ctx_venc0, video_width, video_height);
    if (ret != TD_SUCCESS) {
        return ret;
    }

    return sample_region_osd_init_ctx(&g_sample_region_osd_time_ctx_venc0);
}

td_s32 sample_region_attach_time_to_venc1(td_u32 video_width, td_u32 video_height)
{
    td_s32 ret = sample_region_osd_set_video_size(&g_sample_region_osd_time_ctx_venc1, video_width, video_height);
    if (ret != TD_SUCCESS) {
        return ret;
    }

    return sample_region_osd_init_ctx(&g_sample_region_osd_time_ctx_venc1);
}

td_s32 sample_region_osd_update_time_venc0(td_void)
{
    return sample_region_osd_update_time_ctx(&g_sample_region_osd_time_ctx_venc0);
}

td_s32 sample_region_osd_update_time_venc1(td_void)
{
    return sample_region_osd_update_time_ctx(&g_sample_region_osd_time_ctx_venc1);
}

td_s32 sample_region_osd_set_time_video_size_venc0(td_u32 video_width, td_u32 video_height)
{
    return sample_region_osd_set_video_size(&g_sample_region_osd_time_ctx_venc0, video_width, video_height);
}

td_s32 sample_region_osd_set_time_video_size_venc1(td_u32 video_width, td_u32 video_height)
{
    return sample_region_osd_set_video_size(&g_sample_region_osd_time_ctx_venc1, video_width, video_height);
}

td_s32 sample_region_osd_stop_time_venc0(td_void)
{
    return sample_region_osd_destroy_ctx(&g_sample_region_osd_time_ctx_venc0);
}

td_s32 sample_region_osd_stop_time_venc1(td_void)
{
    return sample_region_osd_destroy_ctx(&g_sample_region_osd_time_ctx_venc1);
}

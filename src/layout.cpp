// layout.cpp — implementation of commander‑damage button layouts
#include "layout.h"
#include "ui/ui.h"

/* ---------------------------------------------------------
 * Rect helper
 * --------------------------------------------------------*/
typedef struct
{
    uint16_t x; /* left   */
    uint16_t y; /* top    */
    uint16_t w; /* width  */
    uint16_t h; /* height */
} rect_t;

static const rect_t sl_layout_2[6] = {
    {10, 7, 100, 150}, // btn 0
    {130, 7, 100, 150} // btn 1
};

static const rect_t sl_layout_3[6] = {
    {10, 7, 89, 150},  // btn 0
    {107, 7, 123, 70}, // btn 1
    {107, 87, 123, 70} // btn 2
};

static const rect_t sl_layout_4[6] = {
    {10, 7, 100, 70},  // btn 0
    {130, 7, 100, 70}, // btn 1
    {10, 82, 100, 70}, // btn 2
    {130, 82, 100, 70} // btn 3
};

static const rect_t sl_layout_5[6] = {
    {10, 7, 70, 70},  // btn 0
    {86, 7, 70, 70},  // btn 1
    {10, 82, 70, 70}, // btn 2
    {86, 82, 70, 70}, // btn 3
    {163, 7, 70, 145} // btn 4
};

static const rect_t sl_layout_6[6] = {
    {10, 7, 70, 70},  // btn 0
    {86, 7, 70, 70},  // btn 1
    {163, 7, 70, 70}, // btn 2
    {10, 82, 70, 70}, // btn 3
    {86, 82, 70, 70}, // btn 4
    {163, 82, 70, 70} // btn 5
};

// MULTI LIFECOUNT

static const rect_t ml_1_layout_2[6] = {
    {10, 10, 100, 250}, // btn 0
    {130, 10, 100, 250} // btn 1
};

static const rect_t ml_1_layout_3[6] = {
    {10, 10, 100, 140},  // btn 0
    {130, 10, 100, 140}, // btn 1
    {10, 160, 220, 100}  // btn 2
};

static const rect_t ml_1_layout_4[6] = {
    {10, 10, 100, 120},  // btn 0
    {130, 10, 100, 120}, // btn 1
    {10, 140, 100, 120}, // btn 2
    {130, 140, 100, 120} // btn 3
};

static const rect_t ml_1_layout_5[6] = {
    {10, 10, 100, 80},  // btn 0
    {130, 10, 100, 80}, // btn 1
    {10, 96, 100, 80},  // btn 2
    {130, 96, 100, 80}, // btn 3
    {10, 180, 220, 80}  // btn 4
};

static const rect_t ml_1_layout_6[6] = {
    {10, 10, 100, 80},  // btn 0
    {130, 10, 100, 80}, // btn 1
    {10, 96, 100, 80},  // btn 2
    {130, 96, 100, 80}, // btn 3
    {10, 180, 100, 80}, // btn 4
    {130, 180, 100, 80} // btn 5
};

// MULTI LIFECOUNT 2
static const rect_t ml_2_layout_2[6] = {
    {10, 7, 100, 150}, // btn 0
    {130, 7, 100, 150} // btn 1
};

static const rect_t ml_2_layout_3[6] = {
    {10, 7, 89, 150},  // btn 0
    {107, 7, 123, 70}, // btn 1
    {107, 87, 123, 70} // btn 2
};

static const rect_t ml_2_layout_4[6] = {
    {10, 7, 100, 70},  // btn 0
    {130, 7, 100, 70}, // btn 1
    {10, 82, 100, 70}, // btn 2
    {130, 82, 100, 70} // btn 3
};

static const rect_t ml_2_layout_5[6] = {
    {10, 7, 70, 70},  // btn 0
    {86, 7, 70, 70},  // btn 1
    {10, 82, 70, 70}, // btn 2
    {86, 82, 70, 70}, // btn 3
    {163, 7, 70, 145} // btn 4
};

static const rect_t ml_2_layout_6[6] = {
    {10, 7, 70, 70},  // btn 0
    {86, 7, 70, 70},  // btn 1
    {163, 7, 70, 70}, // btn 2
    {10, 82, 70, 70}, // btn 3
    {86, 82, 70, 70}, // btn 4
    {163, 82, 70, 70} // btn 5
};

lv_obj_t *sl_cmd_btns[6];
lv_obj_t *sl_cmd_labels[6];

lv_obj_t *ml_1_cmd_btns[6];
lv_obj_t *ml_1_cmd_labels[6];

lv_obj_t *ml_2_cmd_btns[6];
lv_obj_t *ml_2_cmd_labels[6];

lv_obj_t *ml_1_cmd_name_labels[6];

lv_obj_t *ml_2_cmd_name_labels[6];

/* ---------------------------------------------------------
 * Apply layout to up to six buttons.
 * --------------------------------------------------------*/
void sl_layout(uint8_t count)
{
    const rect_t *table = NULL;
    switch (count)
    {
    case 2:
        table = sl_layout_2;
        break;
    case 3:
        table = sl_layout_3;
        break;
    case 4:
        table = sl_layout_4;
        break;
    case 5:
        table = sl_layout_5;
        break;
    case 6:
        table = sl_layout_6;
        break;
    default:
        return; /* unsupported */
    }

    for (uint8_t i = 0; i < 6; ++i)
    {
        if (i < count)
        {
            const rect_t *r = &table[i];
            lv_obj_clear_flag(sl_cmd_btns[i], LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_pos(sl_cmd_btns[i], r->x, r->y);
            lv_obj_set_size(sl_cmd_btns[i], r->w, r->h);
        }
        else if (sl_cmd_btns[i])
        {
            lv_obj_add_flag(sl_cmd_btns[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void ml_1_layout(uint8_t count)
{
    const rect_t *table = NULL;
    switch (count)
    {
    case 2:
        table = ml_1_layout_2;
        break;
    case 3:
        table = ml_1_layout_3;
        break;
    case 4:
        table = ml_1_layout_4;
        break;
    case 5:
        table = ml_1_layout_5;
        break;
    case 6:
        table = ml_1_layout_6;
        break;
    default:
        return; /* unsupported */
    }

    for (uint8_t i = 0; i < 6; ++i)
    {
        if (i < count)
        {
            const rect_t *r = &table[i];
            lv_obj_clear_flag(ml_1_cmd_btns[i], LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_pos(ml_1_cmd_btns[i], r->x, r->y);
            lv_obj_set_size(ml_1_cmd_btns[i], r->w, r->h);
        }
        else if (ml_1_cmd_btns[i])
        {
            lv_obj_add_flag(ml_1_cmd_btns[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void ml_2_layout(uint8_t count)
{
    const rect_t *table = NULL;
    switch (count)
    {
    case 2:
        table = ml_2_layout_2;
        break;
    case 3:
        table = ml_2_layout_3;
        break;
    case 4:
        table = ml_2_layout_4;
        break;
    case 5:
        table = ml_2_layout_5;
        break;
    case 6:
        table = ml_2_layout_6;
        break;
    default:
        return; /* unsupported */
    }

    for (uint8_t i = 0; i < 6; ++i)
    {
        if (i < count)
        {
            const rect_t *r = &table[i];
            lv_obj_clear_flag(ml_2_cmd_btns[i], LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_pos(ml_2_cmd_btns[i], r->x, r->y);
            lv_obj_set_size(ml_2_cmd_btns[i], r->w, r->h);
        }
        else if (ml_2_cmd_btns[i])
        {
            lv_obj_add_flag(ml_2_cmd_btns[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}

/* ---------------------------------------------------------
 * UI screen initialiser — map buttons and set default layout
 * --------------------------------------------------------*/
void layout_init(void)
{
    /* buttons generated by EEZ Studio (ui.h → objects.*) */
    sl_cmd_btns[0] = objects.single_lifecount_edh_btn1;
    sl_cmd_btns[1] = objects.single_lifecount_edh_btn2;
    sl_cmd_btns[2] = objects.single_lifecount_edh_btn3;
    sl_cmd_btns[3] = objects.single_lifecount_edh_btn4;
    sl_cmd_btns[4] = objects.single_lifecount_edh_btn5;
    sl_cmd_btns[5] = objects.single_lifecount_edh_btn6;

    sl_cmd_labels[0] = objects.single_lifecount_edh_btn1_label;
    sl_cmd_labels[1] = objects.single_lifecount_edh_btn2_label;
    sl_cmd_labels[2] = objects.single_lifecount_edh_btn3_label;
    sl_cmd_labels[3] = objects.single_lifecount_edh_btn4_label;
    sl_cmd_labels[4] = objects.single_lifecount_edh_btn5_label;
    sl_cmd_labels[5] = objects.single_lifecount_edh_btn6_label;

    ml_1_cmd_btns[0] = objects.ml_1_btn1;
    ml_1_cmd_btns[1] = objects.ml_1_btn2;
    ml_1_cmd_btns[2] = objects.ml_1_btn3;
    ml_1_cmd_btns[3] = objects.ml_1_btn4;
    ml_1_cmd_btns[4] = objects.ml_1_btn5;
    ml_1_cmd_btns[5] = objects.ml_1_btn6;

    ml_1_cmd_labels[0] = objects.ml_1_btn1_label;
    ml_1_cmd_labels[1] = objects.ml_1_btn2_label;
    ml_1_cmd_labels[2] = objects.ml_1_btn3_label;
    ml_1_cmd_labels[3] = objects.ml_1_btn4_label;
    ml_1_cmd_labels[4] = objects.ml_1_btn5_label;
    ml_1_cmd_labels[5] = objects.ml_1_btn6_label;

    ml_2_cmd_btns[0] = objects.ml_2_btn1;
    ml_2_cmd_btns[1] = objects.ml_2_btn2;
    ml_2_cmd_btns[2] = objects.ml_2_btn3;
    ml_2_cmd_btns[3] = objects.ml_2_btn4;
    ml_2_cmd_btns[4] = objects.ml_2_btn5;
    ml_2_cmd_btns[5] = objects.ml_2_btn6;

    ml_2_cmd_labels[0] = objects.ml_2_btn1_label;
    ml_2_cmd_labels[1] = objects.ml_2_btn2_label;
    ml_2_cmd_labels[2] = objects.ml_2_btn3_label;
    ml_2_cmd_labels[3] = objects.ml_2_btn4_label;
    ml_2_cmd_labels[4] = objects.ml_2_btn5_label;
    ml_2_cmd_labels[5] = objects.ml_2_btn6_label;

    ml_1_cmd_name_labels[0] = objects.ml_1_btn1_name;
    ml_1_cmd_name_labels[1] = objects.ml_1_btn2_name;
    ml_1_cmd_name_labels[2] = objects.ml_1_btn3_name;
    ml_1_cmd_name_labels[3] = objects.ml_1_btn4_name;
    ml_1_cmd_name_labels[4] = objects.ml_1_btn5_name;
    ml_1_cmd_name_labels[5] = objects.ml_1_btn6_name;

    ml_2_cmd_name_labels[0] = objects.ml_2_btn1_name;
    ml_2_cmd_name_labels[1] = objects.ml_2_btn2_name;
    ml_2_cmd_name_labels[2] = objects.ml_2_btn3_name;
    ml_2_cmd_name_labels[3] = objects.ml_2_btn4_name;
    ml_2_cmd_name_labels[4] = objects.ml_2_btn5_name;
    ml_2_cmd_name_labels[5] = objects.ml_2_btn6_name;

    /* Default to a 4‑player pod on load */
    sl_layout(4);
    ml_1_layout(4);
    ml_2_layout(4);
}

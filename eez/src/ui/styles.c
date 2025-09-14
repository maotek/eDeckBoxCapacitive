#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: MenuButtonStyle
//

void init_style_menu_button_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff000000));
    lv_style_set_bg_grad_dir(style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_grad_color(style, lv_color_hex(0xff922b2b));
    lv_style_set_shadow_width(style, 8);
    lv_style_set_shadow_color(style, lv_color_hex(0xff000000));
    lv_style_set_shadow_spread(style, 2);
    lv_style_set_min_height(style, 0);
    lv_style_set_max_height(style, 8191);
    lv_style_set_max_width(style, 8191);
    lv_style_set_bg_opa(style, 0);
    lv_style_set_shadow_ofs_x(style, 1);
    lv_style_set_shadow_ofs_y(style, 1);
    lv_style_set_shadow_opa(style, 125);
};

lv_style_t *get_style_menu_button_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_menu_button_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_menu_button_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_menu_button_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_menu_button_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_menu_button_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: MainBackground
//

void init_style_main_background_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_font(style, &ui_font_roboto_medium_26);
    lv_style_set_bg_img_src(style, &img_background_2);
    lv_style_set_border_color(style, lv_color_hex(0xff000000));
    lv_style_set_border_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_bg_img_opa(style, 255);
};

lv_style_t *get_style_main_background_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_main_background_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_main_background(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_main_background_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_main_background(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_main_background_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: MenuButtonTextStyle
//

void init_style_menu_button_text_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xffffffff));
    lv_style_set_text_font(style, &ui_font_roboto_20);
};

lv_style_t *get_style_menu_button_text_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_menu_button_text_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_menu_button_text_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_menu_button_text_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_menu_button_text_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_menu_button_text_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_menu_button_style,
        add_style_main_background,
        add_style_menu_button_text_style,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_menu_button_style,
        remove_style_main_background,
        remove_style_menu_button_text_style,
    };
    remove_style_funcs[styleIndex](obj);
}


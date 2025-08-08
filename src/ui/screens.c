#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    add_style_main_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 0, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Menu");
        }
        {
            lv_obj_t *obj = lv_list_create(parent_obj);
            lv_obj_set_pos(obj, 0, 53);
            lv_obj_set_size(obj, 240, 267);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 6, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 6, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 14, -17);
                    lv_obj_set_size(obj, 195, 75);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)105);
                    add_style_menu_button_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 1);
                            lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
                            add_style_menu_button_text_style(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Life Counter");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 90, 75);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)102);
                    add_style_menu_button_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_menu_button_text_style(obj);
                            lv_label_set_text(obj, "Wallpaper");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 90, 75);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)107);
                    add_style_menu_button_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_menu_button_text_style(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Dice");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 90, 75);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)103);
                    add_style_menu_button_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_menu_button_text_style(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Settings");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 90, 75);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)100);
                    add_style_menu_button_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_menu_button_text_style(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "About");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_dice() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.dice = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    add_style_main_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // dice_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.dice_slider = obj;
            lv_obj_set_pos(obj, 30, 52);
            lv_obj_set_size(obj, 180, 18);
            lv_slider_set_range(obj, 2, 20);
            lv_slider_set_value(obj, 6, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_generic_slider_cb, LV_EVENT_VALUE_CHANGED, (void *)801);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffcdcdcd), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // dice_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dice_label = obj;
            lv_obj_set_pos(obj, 140, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_medium_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "6");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 75, 268);
            lv_obj_set_size(obj, 90, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)101);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj3 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 75, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_medium_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Dice:");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 75, 215);
            lv_obj_set_size(obj, 90, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)300);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj5 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Roll");
                }
            }
        }
        {
            // dice_result
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dice_result = obj;
            lv_obj_set_pos(obj, 1, -16);
            lv_obj_set_size(obj, 100, 75);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_80, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_dice();
}

void tick_screen_dice() {
}

void create_screen_about() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.about = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    add_style_main_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 75, 269);
            lv_obj_set_size(obj, 90, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)101);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj7 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 259);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_AUTO);
            lv_obj_set_scroll_dir(obj, LV_DIR_VER);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj8 = obj;
                    lv_obj_set_pos(obj, 95, 8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_spec_heading, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Model");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj9 = obj;
                    lv_obj_set_pos(obj, 90, 187);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_spec_heading, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "System");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj10 = obj;
                    lv_obj_set_pos(obj, 63, 29);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "eDeckbox");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj11 = obj;
                    lv_obj_set_pos(obj, 23, 208);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "2x Tensilica LX6\n520KB SRAM\n4MB Flash\n240x320");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj12 = obj;
                    lv_obj_set_pos(obj, 66, 68);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_spec_heading, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Manufacturer");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj13 = obj;
                    lv_obj_set_pos(obj, 1, 89);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "MaoTek");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj14 = obj;
                    lv_obj_set_pos(obj, 47, 130);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_spec_heading, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Firmware Version");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj15 = obj;
                    lv_obj_set_pos(obj, 82, 151);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "V1.0.0");
                }
                {
                    lv_obj_t *obj = lv_qrcode_create(parent_obj, 162, lv_color_hex(0xff000000), lv_color_hex(0xffffffff));
                    lv_obj_set_pos(obj, 41, 354);
                    lv_obj_set_size(obj, 163, 162);
                    lv_qrcode_update(obj, "https://maotek.nl", 17);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj16 = obj;
                    lv_obj_set_pos(obj, 92, 329);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_spec_heading, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Contact");
                }
            }
        }
    }
    
    tick_screen_about();
}

void tick_screen_about() {
}

void create_screen_image() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.image = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)101);
    add_style_main_background(obj);
    
    tick_screen_image();
}

void tick_screen_image() {
}

void create_screen_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    add_style_main_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj17 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 75, 269);
            lv_obj_set_size(obj, 90, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)101);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj18 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj19 = obj;
            lv_obj_set_pos(obj, 0, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Settings");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 240, 214);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 185, 41);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)200);
                    add_style_menu_button_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj20 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_menu_button_text_style(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Debug Monitor");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 150);
                    lv_obj_set_size(obj, 185, 60);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_menu_button_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj21 = obj;
                            lv_obj_set_pos(obj, 0, -11);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_menu_button_text_style(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Brightness");
                        }
                        {
                            // brightness_slider
                            lv_obj_t *obj = lv_slider_create(parent_obj);
                            objects.brightness_slider = obj;
                            lv_obj_set_pos(obj, 7, 30);
                            lv_obj_set_size(obj, 145, 10);
                            lv_slider_set_range(obj, 80, 255);
                            lv_slider_set_value(obj, 125, LV_ANIM_OFF);
                            lv_obj_add_event_cb(obj, action_generic_slider_cb, LV_EVENT_VALUE_CHANGED, (void *)800);
                            lv_obj_add_event_cb(obj, action_generic_slider_cb, LV_EVENT_RELEASED, (void *)800);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffcdcdcd), LV_PART_KNOB | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 100);
                    lv_obj_set_size(obj, 185, 41);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)201);
                    add_style_menu_button_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj22 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_menu_button_text_style(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Background");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 50);
                    lv_obj_set_size(obj, 185, 41);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)202);
                    add_style_menu_button_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj23 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_menu_button_text_style(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Restart");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_settings();
}

void tick_screen_settings() {
}

void create_screen_life_count_select() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.life_count_select = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    add_style_main_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj24 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj25 = obj;
            lv_obj_set_pos(obj, 0, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Life Counter");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 23, 149);
            lv_obj_set_size(obj, 195, 75);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 1, 1);
                    lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Multi Count\nComing Soon...");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 23, 59);
            lv_obj_set_size(obj, 195, 75);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)104);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 1, 1);
                    lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Single Count");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 75, 269);
            lv_obj_set_size(obj, 90, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)101);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj26 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
    }
    
    tick_screen_life_count_select();
}

void tick_screen_life_count_select() {
}

void create_screen_single_lifecount() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.single_lifecount = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    add_style_main_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // single_lifecount_bg_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.single_lifecount_bg_label = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_bg_opa(obj, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // single_lifecount_edh_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.single_lifecount_edh_container = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 261);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 180, 17);
                    lv_obj_set_size(obj, 50, 50);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_SHORT_CLICKED, (void *)501);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_LONG_PRESSED_REPEAT, (void *)501);
                    add_style_menu_button_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "+");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 10, 17);
                    lv_obj_set_size(obj, 50, 50);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_SHORT_CLICKED, (void *)500);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_LONG_PRESSED_REPEAT, (void *)500);
                    add_style_menu_button_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "-");
                        }
                    }
                }
                {
                    // single_lifecount_edh_life_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.single_lifecount_edh_life_label = obj;
                    lv_obj_set_pos(obj, 0, -84);
                    lv_obj_set_size(obj, 100, 70);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_OVERFLOW_VISIBLE|LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
                    lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_x(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_y(obj, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "40");
                }
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 88);
                    lv_obj_set_size(obj, 240, 164);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // single_lifecount_edh_btn1
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.single_lifecount_edh_btn1 = obj;
                            lv_obj_set_pos(obj, 10, 7);
                            lv_obj_set_size(obj, 70, 70);
                            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)600);
                            add_style_menu_button_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // single_lifecount_edh_btn1_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.single_lifecount_edh_btn1_label = obj;
                                    lv_obj_set_pos(obj, 0, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "You\nDealt: 0\nTaken: 0");
                                }
                            }
                        }
                        {
                            // single_lifecount_edh_btn2
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.single_lifecount_edh_btn2 = obj;
                            lv_obj_set_pos(obj, 86, 7);
                            lv_obj_set_size(obj, 70, 70);
                            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)601);
                            add_style_menu_button_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // single_lifecount_edh_btn2_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.single_lifecount_edh_btn2_label = obj;
                                    lv_obj_set_pos(obj, -1, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Player 2\nDealt: 0\nTaken: 0");
                                }
                            }
                        }
                        {
                            // single_lifecount_edh_btn3
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.single_lifecount_edh_btn3 = obj;
                            lv_obj_set_pos(obj, 163, 8);
                            lv_obj_set_size(obj, 70, 70);
                            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)602);
                            add_style_menu_button_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // single_lifecount_edh_btn3_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.single_lifecount_edh_btn3_label = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Player 3\nDealt: 0\nTaken: 0");
                                }
                            }
                        }
                        {
                            // single_lifecount_edh_btn4
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.single_lifecount_edh_btn4 = obj;
                            lv_obj_set_pos(obj, 10, 82);
                            lv_obj_set_size(obj, 70, 70);
                            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)603);
                            add_style_menu_button_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // single_lifecount_edh_btn4_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.single_lifecount_edh_btn4_label = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Player 4\nDealt: 0\nTaken: 0");
                                }
                            }
                        }
                        {
                            // single_lifecount_edh_btn5
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.single_lifecount_edh_btn5 = obj;
                            lv_obj_set_pos(obj, 86, 82);
                            lv_obj_set_size(obj, 70, 70);
                            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)604);
                            add_style_menu_button_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // single_lifecount_edh_btn5_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.single_lifecount_edh_btn5_label = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Player 5\nDealt: 0\nTaken: 0");
                                }
                            }
                        }
                        {
                            // single_lifecount_edh_btn6
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.single_lifecount_edh_btn6 = obj;
                            lv_obj_set_pos(obj, 163, 82);
                            lv_obj_set_size(obj, 70, 70);
                            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)605);
                            add_style_menu_button_style(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // single_lifecount_edh_btn6_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.single_lifecount_edh_btn6_label = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Player 6\nDealt: 0\nTaken: 0");
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // single_lifecount_1v1_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.single_lifecount_1v1_container = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 261);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 180, 105);
                    lv_obj_set_size(obj, 50, 50);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_SHORT_CLICKED, (void *)503);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_LONG_PRESSED_REPEAT, (void *)503);
                    add_style_menu_button_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "+");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 10, 105);
                    lv_obj_set_size(obj, 50, 50);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_SHORT_CLICKED, (void *)502);
                    lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_LONG_PRESSED_REPEAT, (void *)502);
                    add_style_menu_button_style(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "-");
                        }
                    }
                }
                {
                    // single_lifecount_1v1_life_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.single_lifecount_1v1_life_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 100, 75);
                    lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_80, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "20");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 10, 269);
            lv_obj_set_size(obj, 100, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)105);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj27 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 130, 269);
            lv_obj_set_size(obj, 100, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)106);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj28 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Settings");
                }
            }
        }
    }
    
    tick_screen_single_lifecount();
}

void tick_screen_single_lifecount() {
}

void create_screen_single_lifecount_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.single_lifecount_settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    add_style_main_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj29 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 16, 269);
            lv_obj_set_size(obj, 65, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)104);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj30 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 88, 269);
            lv_obj_set_size(obj, 65, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)511);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj31 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Reset");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 160, 269);
            lv_obj_set_size(obj, 65, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)512);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj32 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Apply");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 29, 5);
            lv_obj_set_size(obj, 186, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)510);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // SingleLifecount_setting_Mode
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.single_lifecount_setting_mode = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Mode: Commander");
                }
            }
        }
        {
            // single_lifecount_edh_setting_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.single_lifecount_edh_setting_container = obj;
            lv_obj_set_pos(obj, 0, 58);
            lv_obj_set_size(obj, 240, 202);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // single_lifecount_edh_settings_playercount_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.single_lifecount_edh_settings_playercount_label = obj;
                    lv_obj_set_pos(obj, 79, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_roboto_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Players: 4");
                }
                {
                    // single_lifecount_edh_settings_player_slider
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.single_lifecount_edh_settings_player_slider = obj;
                    lv_obj_set_pos(obj, 55, 33);
                    lv_obj_set_size(obj, 130, 15);
                    lv_slider_set_range(obj, 2, 6);
                    lv_slider_set_value(obj, 4, LV_ANIM_OFF);
                    lv_obj_add_event_cb(obj, action_generic_slider_cb, LV_EVENT_VALUE_CHANGED, (void *)803);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffcdcdcd), LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // single_lifecount_edh_settings_initiallife_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.single_lifecount_edh_settings_initiallife_label = obj;
                    lv_obj_set_pos(obj, 54, 69);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_roboto_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Initial Health: 40");
                }
                {
                    // single_lifecount_edh_settings_initiallife_slider
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.single_lifecount_edh_settings_initiallife_slider = obj;
                    lv_obj_set_pos(obj, 30, 99);
                    lv_obj_set_size(obj, 186, 15);
                    lv_slider_set_range(obj, 1, 60);
                    lv_slider_set_value(obj, 40, LV_ANIM_OFF);
                    lv_obj_add_event_cb(obj, action_generic_slider_cb, LV_EVENT_VALUE_CHANGED, (void *)802);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffcdcdcd), LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // SingleLifecount_1v1SettingContainer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.single_lifecount_1v1_setting_container = obj;
            lv_obj_set_pos(obj, 0, 58);
            lv_obj_set_size(obj, 240, 202);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // single_lifecount_1v1_settings_initiallife_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.single_lifecount_1v1_settings_initiallife_label = obj;
                    lv_obj_set_pos(obj, 58, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &ui_font_roboto_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Initial Health: 20");
                }
                {
                    // single_lifecount_1v1_settings_initiallife_slider
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.single_lifecount_1v1_settings_initiallife_slider = obj;
                    lv_obj_set_pos(obj, 29, 30);
                    lv_obj_set_size(obj, 186, 10);
                    lv_slider_set_range(obj, 1, 60);
                    lv_slider_set_value(obj, 20, LV_ANIM_OFF);
                    lv_obj_add_event_cb(obj, action_generic_slider_cb, LV_EVENT_VALUE_CHANGED, (void *)804);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffcdcdcd), LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_single_lifecount_settings();
}

void tick_screen_single_lifecount_settings() {
}

void create_screen_single_lifecount_opponent_adjust_count() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.single_lifecount_opponent_adjust_count = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    add_style_main_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj33 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // single_lifecount_opponent_namelabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.single_lifecount_opponent_namelabel = obj;
            lv_obj_set_pos(obj, 55, 12);
            lv_obj_set_size(obj, 131, 28);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "12345678");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 182, 86);
            lv_obj_set_size(obj, 50, 50);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_SHORT_CLICKED, (void *)610);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_LONG_PRESSED_REPEAT, (void *)610);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "+");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 9, 87);
            lv_obj_set_size(obj, 50, 50);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_SHORT_CLICKED, (void *)611);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_LONG_PRESSED_REPEAT, (void *)611);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-");
                }
            }
        }
        {
            // single_lifecount_edh_commander_dealt_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.single_lifecount_edh_commander_dealt_label = obj;
            lv_obj_set_pos(obj, 0, -48);
            lv_obj_set_size(obj, 61, 41);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_OVERFLOW_VISIBLE|LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_pivot_x(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_pivot_y(obj, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj34 = obj;
            lv_obj_set_pos(obj, 9, 55);
            lv_obj_set_size(obj, 220, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Commander Damage Dealt");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 10, 269);
            lv_obj_set_size(obj, 100, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)104);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj35 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 130, 269);
            lv_obj_set_size(obj, 100, 41);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_CLICKED, (void *)630);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj36 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_menu_button_text_style(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Set Name");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 182, 191);
            lv_obj_set_size(obj, 50, 50);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_SHORT_CLICKED, (void *)612);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_LONG_PRESSED_REPEAT, (void *)612);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "+");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 9, 192);
            lv_obj_set_size(obj, 50, 50);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_SHORT_CLICKED, (void *)613);
            lv_obj_add_event_cb(obj, action_generic_button_cb, LV_EVENT_LONG_PRESSED_REPEAT, (void *)613);
            add_style_menu_button_style(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj37 = obj;
            lv_obj_set_pos(obj, 9, 160);
            lv_obj_set_size(obj, 222, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Commander Damage Taken");
        }
        {
            // single_lifecount_edh_commander_taken_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.single_lifecount_edh_commander_taken_label = obj;
            lv_obj_set_pos(obj, 0, 57);
            lv_obj_set_size(obj, 61, 41);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_OVERFLOW_VISIBLE|LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_pivot_x(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_pivot_y(obj, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0");
        }
    }
    
    tick_screen_single_lifecount_opponent_adjust_count();
}

void tick_screen_single_lifecount_opponent_adjust_count() {
}

void create_screen_text_screen() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.text_screen = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    add_style_main_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj38 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // my_keyboard
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.my_keyboard = obj;
            lv_obj_set_pos(obj, 0, 129);
            lv_obj_set_size(obj, 240, 191);
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_USER_1);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff7a6868), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc3c2c2), LV_PART_ITEMS | LV_STATE_PRESSED);
        }
        {
            // my_textarea
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.my_textarea = obj;
            lv_obj_set_pos(obj, 25, 39);
            lv_obj_set_size(obj, 191, 48);
            lv_textarea_set_max_length(obj, 8);
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj39 = obj;
            lv_obj_set_pos(obj, 51, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Enter Name");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj40 = obj;
            lv_obj_set_pos(obj, 19, 94);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Max 8 characters");
        }
    }
    lv_keyboard_set_textarea(objects.my_keyboard, objects.my_textarea);
    
    tick_screen_text_screen();
}

void tick_screen_text_screen() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_dice,
    tick_screen_about,
    tick_screen_image,
    tick_screen_settings,
    tick_screen_life_count_select,
    tick_screen_single_lifecount,
    tick_screen_single_lifecount_settings,
    tick_screen_single_lifecount_opponent_adjust_count,
    tick_screen_text_screen,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_dice();
    create_screen_about();
    create_screen_image();
    create_screen_settings();
    create_screen_life_count_select();
    create_screen_single_lifecount();
    create_screen_single_lifecount_settings();
    create_screen_single_lifecount_opponent_adjust_count();
    create_screen_text_screen();
}

#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *dice;
    lv_obj_t *about;
    lv_obj_t *image;
    lv_obj_t *settings;
    lv_obj_t *life_count_select;
    lv_obj_t *single_lifecount;
    lv_obj_t *single_lifecount_settings;
    lv_obj_t *single_lifecount_opponent_adjust_count;
    lv_obj_t *text_screen;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *dice_slider;
    lv_obj_t *dice_label;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *dice_result;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *brightness_slider;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
    lv_obj_t *obj26;
    lv_obj_t *single_lifecount_bg_label;
    lv_obj_t *single_lifecount_edh_container;
    lv_obj_t *single_lifecount_edh_life_label;
    lv_obj_t *single_lifecount_edh_btn1;
    lv_obj_t *single_lifecount_edh_btn1_label;
    lv_obj_t *single_lifecount_edh_btn2;
    lv_obj_t *single_lifecount_edh_btn2_label;
    lv_obj_t *single_lifecount_edh_btn3;
    lv_obj_t *single_lifecount_edh_btn3_label;
    lv_obj_t *single_lifecount_edh_btn4;
    lv_obj_t *single_lifecount_edh_btn4_label;
    lv_obj_t *single_lifecount_edh_btn5;
    lv_obj_t *single_lifecount_edh_btn5_label;
    lv_obj_t *single_lifecount_edh_btn6;
    lv_obj_t *single_lifecount_edh_btn6_label;
    lv_obj_t *single_lifecount_1v1_container;
    lv_obj_t *single_lifecount_1v1_life_label;
    lv_obj_t *obj27;
    lv_obj_t *obj28;
    lv_obj_t *obj29;
    lv_obj_t *obj30;
    lv_obj_t *obj31;
    lv_obj_t *obj32;
    lv_obj_t *single_lifecount_setting_mode;
    lv_obj_t *single_lifecount_edh_setting_container;
    lv_obj_t *single_lifecount_edh_settings_playercount_label;
    lv_obj_t *single_lifecount_edh_settings_player_slider;
    lv_obj_t *single_lifecount_edh_settings_initiallife_label;
    lv_obj_t *single_lifecount_edh_settings_initiallife_slider;
    lv_obj_t *single_lifecount_1v1_setting_container;
    lv_obj_t *single_lifecount_1v1_settings_initiallife_label;
    lv_obj_t *single_lifecount_1v1_settings_initiallife_slider;
    lv_obj_t *obj33;
    lv_obj_t *single_lifecount_opponent_namelabel;
    lv_obj_t *single_lifecount_edh_commander_dealt_label;
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *obj36;
    lv_obj_t *obj37;
    lv_obj_t *single_lifecount_edh_commander_taken_label;
    lv_obj_t *obj38;
    lv_obj_t *my_keyboard;
    lv_obj_t *my_textarea;
    lv_obj_t *obj39;
    lv_obj_t *obj40;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_DICE = 2,
    SCREEN_ID_ABOUT = 3,
    SCREEN_ID_IMAGE = 4,
    SCREEN_ID_SETTINGS = 5,
    SCREEN_ID_LIFE_COUNT_SELECT = 6,
    SCREEN_ID_SINGLE_LIFECOUNT = 7,
    SCREEN_ID_SINGLE_LIFECOUNT_SETTINGS = 8,
    SCREEN_ID_SINGLE_LIFECOUNT_OPPONENT_ADJUST_COUNT = 9,
    SCREEN_ID_TEXT_SCREEN = 10,
};

void create_screen_main();
void tick_screen_main();

void create_screen_dice();
void tick_screen_dice();

void create_screen_about();
void tick_screen_about();

void create_screen_image();
void tick_screen_image();

void create_screen_settings();
void tick_screen_settings();

void create_screen_life_count_select();
void tick_screen_life_count_select();

void create_screen_single_lifecount();
void tick_screen_single_lifecount();

void create_screen_single_lifecount_settings();
void tick_screen_single_lifecount_settings();

void create_screen_single_lifecount_opponent_adjust_count();
void tick_screen_single_lifecount_opponent_adjust_count();

void create_screen_text_screen();
void tick_screen_text_screen();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
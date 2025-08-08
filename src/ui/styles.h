#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: MenuButtonStyle
lv_style_t *get_style_menu_button_style_MAIN_DEFAULT();
void add_style_menu_button_style(lv_obj_t *obj);
void remove_style_menu_button_style(lv_obj_t *obj);

// Style: MainBackground
lv_style_t *get_style_main_background_MAIN_DEFAULT();
void add_style_main_background(lv_obj_t *obj);
void remove_style_main_background(lv_obj_t *obj);

// Style: MenuButtonTextStyle
lv_style_t *get_style_menu_button_text_style_MAIN_DEFAULT();
void add_style_menu_button_text_style(lv_obj_t *obj);
void remove_style_menu_button_text_style(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/
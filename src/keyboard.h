// keyboard.h
#pragma once
#include <lvgl.h>

// Initialize the custom keyboard: sets map, connects to textarea, and wires events.
void keyboard_init(lv_obj_t *keyboard, lv_obj_t *target_textarea);

// (Optional) If you want to change the textarea target at runtime:
void keyboard_set_textarea(lv_obj_t *keyboard, lv_obj_t *target_textarea);

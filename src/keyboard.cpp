// keyboard.cpp
#include "keyboard.h"
#include <cstring>
#include "ui/ui.h"  // for `objects` if you use them inside the callback
#include "player.h" // singlecount_player_set_nickname, globals
#include "layout.h" // loadScreen, SCREEN_ID_...
#include "ui/styles.h"
#include "ui/images.h"
#include "preference_manager.h"

// --- Custom key map & ctrl map (User1) ---
static const char *kb_map_user1[] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "\n",
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "\n",
    "a", "s", "d", "f", "g", "h", "j", "k", "l", "\n",
    "z", "x", "c", "v", "b", "n", "m", LV_SYMBOL_BACKSPACE, "\n",
    " ", LV_SYMBOL_OK, "" // must end with empty string
};

#define BTN_WIDTH(n) ((lv_btnmatrix_ctrl_t)((n) & 0x0F))
static const lv_btnmatrix_ctrl_t kb_ctrl_user1[] = {
    // row1: 10 keys
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    // row2: 10 keys
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    // row3: 9 keys
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    // row4: 7 + backspace wide
    0, 0, 0, 0, 0, 0, 0, BTN_WIDTH(2),
    // row5: space + OK
    0, 0};

// Keep a weak reference to the active textarea (for LV_SYMBOL_OK handler)
static lv_obj_t *s_active_ta = nullptr;

static void my_keyboard_event_cb(lv_event_t *e)
{
    if (!e)
        return;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if (!kb)
        return;

    if (code != LV_EVENT_VALUE_CHANGED)
        return;

    uint16_t btn_id = lv_btnmatrix_get_selected_btn(kb);
    const char *txt = lv_btnmatrix_get_btn_text(kb, btn_id);
    if (!txt)
        return;

    // Handle OK “submit”
    if (strcmp(txt, LV_SYMBOL_OK) == 0)
    {
        // Resolve the textarea: prefer s_active_ta; fall back to a known one from `objects`
        lv_obj_t *ta = s_active_ta ? s_active_ta : objects.my_textarea;
        if (!ta)
            return;

        const char *entered = lv_textarea_get_text(ta);
        if (!entered)
            entered = "";

        if (current_game_mode == GAME_MODE_SL)
        {
            // Persist/update UI (uses your existing globals & functions)
            sl_player_set_nickname(
                sl_current_player_idx,
                entered);

            lv_label_set_text(
                objects.sl_opponent_namelabel,
                sl_players[sl_current_player_idx].nickname);

            lv_textarea_set_text(ta, "");

            lv_label_set_text_fmt(
                sl_cmd_labels[sl_current_player_idx],
                "%s\nTo: %d\nFrom: %d",
                sl_players[sl_current_player_idx].nickname,
                sl_players[sl_current_player_idx].dmg_dealt,
                sl_players[sl_current_player_idx].dmg_taken);

            char key[16];
            snprintf(key, sizeof(key), "p%u_name", sl_current_player_idx + 1);
            set_string_with_key("sl", key, sl_players[sl_current_player_idx].nickname);

            loadScreen(SCREEN_ID_SINGLE_LIFECOUNT_OPPONENT_ADJUST_COUNT);
            return;
        }
        else
        {
            // Persist/update UI (uses your existing globals & functions)
            ml_player_set_nickname(
                ml_current_player_idx,
                entered);

            lv_label_set_text(
                ml_1_cmd_name_labels[ml_current_player_idx],
                ml_players[ml_current_player_idx].nickname);

            lv_label_set_text(
                ml_2_cmd_name_labels[ml_current_player_idx],
                ml_players[ml_current_player_idx].nickname);

            lv_label_set_text(
                objects.ml_player_label,
                ml_players[ml_current_player_idx].nickname);

            lv_textarea_set_text(ta, "");

            char key[16];
            snprintf(key, sizeof(key), "p%u_name", ml_current_player_idx + 1);
            set_string_with_key("ml", key, ml_players[ml_current_player_idx].nickname);

            loadScreen(SCREEN_ID_MULTI_LIFECOUNT_OPPONENT_ADJUST_COUNT);
            return;
        }
    }

    // Default LVGL keyboard behavior is already handled by lv_keyboard,
    // so we don’t need to manually inject chars here.
}

void keyboard_set_textarea(lv_obj_t *keyboard, lv_obj_t *target_textarea)
{
    s_active_ta = target_textarea;
    if (keyboard && target_textarea)
    {
        lv_keyboard_set_textarea(keyboard, target_textarea);
    }
}

void keyboard_init(lv_obj_t *keyboard, lv_obj_t *target_textarea)
{
    if (!keyboard)
        return;

    // Install map into User1 and activate it
    lv_keyboard_set_map(keyboard, LV_KEYBOARD_MODE_USER_1, kb_map_user1, kb_ctrl_user1);
    lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_USER_1);

    // Connect to textarea (and remember it)
    keyboard_set_textarea(keyboard, target_textarea);

    // Optionally restrict accepted chars at the textarea level
    if (target_textarea)
    {
        lv_textarea_set_accepted_chars(
            target_textarea,
            "0123456789 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }

    // Attach the event listener once
    lv_obj_add_event_cb(keyboard, my_keyboard_event_cb, LV_EVENT_ALL, nullptr);
}

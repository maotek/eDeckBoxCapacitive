/*  Copyright (C) 2025 MaoTek Enterprise
 *  DeckBoxCapacitive – All (Reasonable) Rights Reserved
 *
 *  You may use, tweak, and brandish this code under the highly permissive
 *  eDeckBox License v0.1, which states (roughly):
 *    - If this code helps you win a game, you must smile politely.
 *    - If it crashes, you must blame RNG and roll again.
 *    - Derivatives should keep this blurb so future archeologists know who to thank.
 *
 *  This software is provided “as is”, without warranties express or implied,
 *  including but not limited to LVGL sprite integrity, TFT backlight serenity,
 *  or perfect mana curve alignment. Use at your own risk.
 *
 *  If you did not receive a copy of the DeckBox Cafe License, it’s probably
 *  because it hasn’t been formally written yet. Please write to:
 *  support@maotek.example (carrier pigeon also acceptable),
 *  or visit your nearest friendly LGS and ask for the “MaoTek house rules”.
 */

#include "ui/actions.h"
#include "ui/ui.h"
#include "ui/screens.h"
#include "ui/styles.h"
#include "ui/images.h"
#include "Arduino.h"
#include "lvgl.h"
#include "preference_manager.h"
#include "layout.h"
#include "player.h"
#include "ui_action.h"

/* -------------------- CUSTOM BUSINESS LOGIC ----------------------------*/

static inline void refresh_btn_label(uint8_t id)
{
    lv_label_set_text_fmt(sl_cmd_labels[id],
                          "%s\nTo: %d\nFrom: %d",
                          sl_players[id].nickname,
                          sl_players[id].dmg_dealt,
                          sl_players[id].dmg_taken);
}

// Dice Logic
static lv_timer_t *dice_timer = NULL;
static uint32_t dice_max = 0;
static uint32_t dice_anim_steps = 0;

static void roll_dice_step_cb(lv_timer_t *timer)
{
    if (dice_anim_steps-- == 0)
    {
        lv_timer_del(timer);
        dice_timer = NULL;

        int result = (rand() % dice_max) + 1;
        lv_label_set_text_fmt(objects.dice_result, "%d", result);
        return;
    }

    // Simulate random number animation
    int temp_roll = (rand() % dice_max) + 1;
    lv_label_set_text_fmt(objects.dice_result, "%d", temp_roll);
}

/* bump a numeric LIFE label by delta and clamp to [0,99] */
static inline void bump_life_label(lv_obj_t *lbl, int delta)
{
    const char *t = lv_label_get_text(lbl);
    char *end;
    long v = strtol(t ? t : "0", &end, 10);

    v += delta;
    if (v < 0)
        v = 0;
    if (v > 99)
        v = 99;

    lv_label_set_text_fmt(lbl, "%ld", v);
}

/* bump a numeric MANA label by delta and clamp to [0,99] */
static inline void bump_mana_label(lv_obj_t *lbl, int delta)
{
    const char *t = lv_label_get_text(lbl);
    char *end;
    long v = strtol(t ? t : "0", &end, 10);

    v += delta;
    if (v < 0)
        v = 0;
    if (v > 99)
        v = 99;

    lv_label_set_text_fmt(lbl, "%ld", v);
}

/* helper to switch opponent and show adjust screen */
static inline void sl_select_opponent(uint8_t idx)
{
    sl_current_player_idx = idx;

    lv_label_set_text_fmt(objects.sl_edh_commander_dealt_label,
                          "%d", sl_players[idx].dmg_dealt);
    lv_label_set_text_fmt(objects.sl_edh_commander_taken_label,
                          "%d", sl_players[idx].dmg_taken);
    lv_label_set_text(objects.sl_opponent_namelabel,
                      sl_players[idx].nickname);

    current_game_mode = GAME_MODE_SL;
    loadScreen(SCREEN_ID_SINGLE_LIFECOUNT_OPPONENT_ADJUST_COUNT);
}

static inline void ml_select_opponent(uint8_t idx)
{
    ml_current_player_idx = idx;

    lv_label_set_text_fmt(objects.ml_life_label,
                          "%d", ml_players[idx].hp);

    for (int i = 0; i < 6; i++)
    {
        int opp_value = 0;
        switch (i)
        {
        case 0:
            opp_value = ml_players[ml_current_player_idx].opp1;
            break;
        case 1:
            opp_value = ml_players[ml_current_player_idx].opp2;
            break;
        case 2:
            opp_value = ml_players[ml_current_player_idx].opp3;
            break;
        case 3:
            opp_value = ml_players[ml_current_player_idx].opp4;
            break;
        case 4:
            opp_value = ml_players[ml_current_player_idx].opp5;
            break;
        case 5:
            opp_value = ml_players[ml_current_player_idx].opp6;
            break;
        }
        lv_label_set_text_fmt(ml_2_cmd_labels[i],
                              "%d",
                              opp_value);
    }

    current_game_mode = GAME_MODE_ML;

    lv_label_set_text_fmt(objects.ml_player_label,
                          "%s",
                          ml_players[idx].nickname);

    loadScreen(SCREEN_ID_MULTI_LIFECOUNT_OPPONENT_ADJUST_COUNT);
}

/* -------------------- END CUSTOM BUSINESS LOGIC ----------------------------*/

#define IMAGES_COUNT (sizeof(images) / sizeof(images[0]))

void action_generic_button_cb(lv_event_t *e)
{
    uint32_t id = (uint32_t)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);

    switch (id)
    {

    /* ---------------------------------- NAVIGATION -------------------------- */
    case ACT_OPEN_ABOUT:
        loadScreen(SCREEN_ID_ABOUT);
        break;

    case ACT_OPEN_MENU:
        loadScreen(SCREEN_ID_MAIN);
        break;

    case ACT_OPEN_WALLPAPER:
        loadScreen(SCREEN_ID_IMAGE);
        break;

    case ACT_OPEN_SETTINGS:
        loadScreen(SCREEN_ID_SETTINGS);
        break;

    case ACT_OPEN_SINGLE_LIFECOUNT:
        loadScreen(SCREEN_ID_SINGLE_LIFECOUNT);
        break;

    case ACT_OPEN_COUNTER_SELECTOR:
        loadScreen(SCREEN_ID_COUNTER_SELECT);
        break;

    case ACT_OPEN_SINGLE_LIFECOUNT_SETTINGS:
        // Set labels
        lv_label_set_text_fmt(objects.single_lifecount_edh_settings_playercount_label, "Players: %d", sl_layout_count);
        lv_label_set_text(objects.single_lifecount_edh_settings_initiallife_label, "Initial Health: 40");

        // Set slider values
        lv_slider_set_value(objects.single_lifecount_edh_settings_player_slider, sl_layout_count, LV_ANIM_OFF);
        lv_slider_set_value(objects.single_lifecount_edh_settings_initiallife_slider, 40, LV_ANIM_OFF);
        loadScreen(SCREEN_ID_SINGLE_LIFECOUNT_SETTINGS);
        break;

    case ACT_OPEN_DICE:
        loadScreen(SCREEN_ID_DICE);
        break;

    case ACT_OPEN_MANACOUNTER:
        loadScreen(SCREEN_ID_MANA_COUNTER);
        break;

    case ACT_OPEN_MULTI_LIFECOUNT:
        loadScreen(SCREEN_ID_MULTI_LIFECOUNT);
        break;

    case ACT_OPEN_MULTI_LIFECOUNT_SETTINGS:
        // Set labels
        lv_label_set_text_fmt(objects.multi_lifecount_settings_playercount_label, "Players: %d", ml_layout_count);
        lv_label_set_text(objects.multi_lifecount_settings_initiallife_label, "Initial Health: 40");

        // Set slider values
        lv_slider_set_value(objects.multi_lifecount_settings_player_slider, ml_layout_count, LV_ANIM_OFF);
        lv_slider_set_value(objects.multi_lifecount_settings_initiallife_slider, 40, LV_ANIM_OFF);
        loadScreen(SCREEN_ID_MULTI_LIFECOUNT_SETTINGS);
        break;

        /* ---------------------------------- END NAVIGATION -------------------------- */

        /* ---------------------------------- MANA COUNTER -------------------------- */

    case ACT_MANA_BLACK_INCR:
        bump_mana_label(objects.mana_black_label, 1);
        set_value_with_key("mana", "black", atoi(lv_label_get_text(objects.mana_black_label)));
        break;
    case ACT_MANA_BLACK_DECR:
        bump_mana_label(objects.mana_black_label, -1);
        set_value_with_key("mana", "black", atoi(lv_label_get_text(objects.mana_black_label)));
        break;

    case ACT_MANA_BLUE_INCR:
        bump_mana_label(objects.mana_blue_label, 1);
        set_value_with_key("mana", "blue", atoi(lv_label_get_text(objects.mana_blue_label)));
        break;
    case ACT_MANA_BLUE_DECR:
        bump_mana_label(objects.mana_blue_label, -1);
        set_value_with_key("mana", "blue", atoi(lv_label_get_text(objects.mana_blue_label)));
        break;

    case ACT_MANA_GREEN_INCR:
        bump_mana_label(objects.mana_green_label, 1);
        set_value_with_key("mana", "green", atoi(lv_label_get_text(objects.mana_green_label)));
        break;
    case ACT_MANA_GREEN_DECR:
        bump_mana_label(objects.mana_green_label, -1);
        set_value_with_key("mana", "green", atoi(lv_label_get_text(objects.mana_green_label)));
        break;

    case ACT_MANA_YELLOW_INCR:
        bump_mana_label(objects.mana_yellow_label, 1);
        set_value_with_key("mana", "yellow", atoi(lv_label_get_text(objects.mana_yellow_label)));
        break;
    case ACT_MANA_YELLOW_DECR:
        bump_mana_label(objects.mana_yellow_label, -1);
        set_value_with_key("mana", "yellow", atoi(lv_label_get_text(objects.mana_yellow_label)));
        break;

    case ACT_MANA_RED_INCR:
        bump_mana_label(objects.mana_red_label, 1);
        set_value_with_key("mana", "red", atoi(lv_label_get_text(objects.mana_red_label)));
        break;
    case ACT_MANA_RED_DECR:
        bump_mana_label(objects.mana_red_label, -1);
        set_value_with_key("mana", "red", atoi(lv_label_get_text(objects.mana_red_label)));
        break;

    case ACT_MANA_COLORLESS_INCR:
        bump_mana_label(objects.mana_colorless_label, 1);
        set_value_with_key("mana", "colorless", atoi(lv_label_get_text(objects.mana_colorless_label)));
        break;
    case ACT_MANA_COLORLESS_DECR:
        bump_mana_label(objects.mana_colorless_label, -1);
        set_value_with_key("mana", "colorless", atoi(lv_label_get_text(objects.mana_colorless_label)));
        break;

    case ACT_MANA_RESET:
        lv_label_set_text(objects.mana_black_label, "0");
        lv_label_set_text(objects.mana_blue_label, "0");
        lv_label_set_text(objects.mana_green_label, "0");
        lv_label_set_text(objects.mana_yellow_label, "0");
        lv_label_set_text(objects.mana_red_label, "0");
        lv_label_set_text(objects.mana_colorless_label, "0");
        set_value_with_key("mana", "black", 0);
        set_value_with_key("mana", "blue", 0);
        set_value_with_key("mana", "green", 0);
        set_value_with_key("mana", "yellow", 0);
        set_value_with_key("mana", "red", 0);
        set_value_with_key("mana", "colorless", 0);
        break;

        /* ---------------------------------- END MANA COUNTER -------------------------- */

        /* ---------------------------------- SETTINGS -------------------------- */

    case ACT_TOGGLE_PERF_MON:
    {
        // Requires manual change in core files, lv_refr.c to expose the perf_label to user code.
        lv_obj_t *perf_label = lv_perf_monitor_get_label();
        if (lv_obj_has_flag(perf_label, LV_OBJ_FLAG_HIDDEN))
        {
            lv_obj_clear_flag(perf_label, LV_OBJ_FLAG_HIDDEN);
            lv_perf_monitor_enable(true);
        }
        else
        {
            lv_obj_add_flag(perf_label, LV_OBJ_FLAG_HIDDEN);
            lv_perf_monitor_enable(false);
        }
        break;
    }

    case ACT_TOGGLE_BACKGROUND:
    {
        uint16_t bg_idx = get_value_with_key("pref", "bg_idx", 0);
        lv_style_t *style = get_style_main_background_MAIN_DEFAULT();

        /* increment index */
        bg_idx = (bg_idx + 1) % IMAGES_COUNT;

        /* skip if the name is "mana" */
        if (strcmp(images[bg_idx].name, "mana") == 0)
        {
            bg_idx = (bg_idx + 1) % IMAGES_COUNT; // skip mana image
        }

        /* apply background */
        lv_style_set_bg_img_src(style, images[bg_idx].img_dsc);
        lv_obj_report_style_change(style);

        /* save index */
        set_value_with_key("pref", "bg_idx", bg_idx);
        break;
    }

    case ACT_RESTART_DEVICE:
        esp_restart();
        break;

    /* ---------------------------------- END SETTINGS -------------------------- */

    /* ---------------------------------- DICE -------------------------- */
    case ACT_ROLL_DICE:
    {
        if (dice_timer)
        {
            // Already rolling
            return;
        }

        // Read value from slider to get max dice value
        int32_t value = lv_slider_get_value(objects.dice_slider);
        if (value < 1)
            value = 1; // Prevent invalid dice max

        dice_max = value;
        dice_anim_steps = 10; // Total animation steps

        // Start animation timer
        dice_timer = lv_timer_create(roll_dice_step_cb, 50, NULL);
        break;
    }

    /* ---------------------------------- END DICE -------------------------- */

    /* ---------------------------------- SINGLE LIFECOUNT LIFE LABEL -------------------------- */
    case ACT_SL_EDH_LIFE_DECR:
        if (code == LV_EVENT_SHORT_CLICKED ||
            code == LV_EVENT_LONG_PRESSED_REPEAT)
        {
            bump_life_label(objects.sl_edh_life_label, -1);
            set_value_with_key("sl", "edh_life", atoi(lv_label_get_text(objects.sl_edh_life_label)));
        }
        break;

    case ACT_SL_EDH_LIFE_INCR:
        if (code == LV_EVENT_SHORT_CLICKED ||
            code == LV_EVENT_LONG_PRESSED_REPEAT)
        {
            bump_life_label(objects.sl_edh_life_label, +1);
            set_value_with_key("sl", "edh_life", atoi(lv_label_get_text(objects.sl_edh_life_label)));
        }
        break;

    case ACT_SL_1v1_LIFE_DECR:
        if (code == LV_EVENT_SHORT_CLICKED ||
            code == LV_EVENT_LONG_PRESSED_REPEAT)
        {
            bump_life_label(objects.sl_1v1_life_label, -1);
            set_value_with_key("sl", "1v1_life", atoi(lv_label_get_text(objects.sl_1v1_life_label)));
        }
        break;

    case ACT_SL_1v1_LIFE_INCR:
        if (code == LV_EVENT_SHORT_CLICKED ||
            code == LV_EVENT_LONG_PRESSED_REPEAT)
        {
            bump_life_label(objects.sl_1v1_life_label, +1);
            set_value_with_key("sl", "1v1_life", atoi(lv_label_get_text(objects.sl_1v1_life_label)));
        }
        break;

    /* ---------------------------------- END SINGLE LIFECOUNT LIFE LABEL -------------------------- */

    /* ---------------------------------- SINGLE LIFECOUNT SETTINGS -------------------------- */
    case ACT_SL_SETTING_MODE_TOGGLE:
        if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_CLICKED)
        {
            lv_obj_t *lbl = objects.single_lifecount_setting_mode;
            const char *txt = lv_label_get_text(lbl);
            if (txt && strcmp(txt, "Mode: Commander") == 0)
            {
                lv_obj_add_flag(objects.single_lifecount_edh_setting_container, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(objects.single_lifecount_edh_container, LV_OBJ_FLAG_HIDDEN);

                lv_obj_clear_flag(objects.single_lifecount_1v1_setting_container, LV_OBJ_FLAG_HIDDEN);
                lv_obj_clear_flag(objects.single_lifecount_1v1_container, LV_OBJ_FLAG_HIDDEN);
                lv_label_set_text(lbl, "Mode: 1v1");
            }
            else
            {
                lv_obj_clear_flag(objects.single_lifecount_edh_setting_container, LV_OBJ_FLAG_HIDDEN);
                lv_obj_clear_flag(objects.single_lifecount_edh_container, LV_OBJ_FLAG_HIDDEN);

                lv_obj_add_flag(objects.single_lifecount_1v1_setting_container, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(objects.single_lifecount_1v1_container, LV_OBJ_FLAG_HIDDEN);

                lv_label_set_text(lbl, "Mode: Commander");
            }
        }

        break;

    case ACT_SL_SETTINGS_RESET:
        if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_CLICKED)
        {

            lv_obj_t *lbl = objects.single_lifecount_setting_mode;
            const char *txt = lv_label_get_text(lbl);
            if (txt && strcmp(txt, "Mode: Commander") == 0)
            {
                // Reset labels
                lv_label_set_text(objects.single_lifecount_edh_settings_playercount_label, "Players: 4");
                lv_label_set_text(objects.single_lifecount_edh_settings_initiallife_label, "Initial Health: 40");

                // Reset slider values
                lv_slider_set_value(objects.single_lifecount_edh_settings_player_slider, 4, LV_ANIM_OFF);
                lv_slider_set_value(objects.single_lifecount_edh_settings_initiallife_slider, 40, LV_ANIM_OFF);
            }
            else
            {
                // Reset labels
                lv_label_set_text(objects.single_lifecount_1v1_settings_initiallife_label, "Initial Health: 20");

                // Reset slider values
                lv_slider_set_value(objects.single_lifecount_1v1_settings_initiallife_slider, 20, LV_ANIM_OFF);
            }
        }
        break;

    case ACT_SL_APPLY_SETTINGS:
        if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_CLICKED)
        {
            lv_obj_t *lbl = objects.single_lifecount_setting_mode;
            const char *txt = lv_label_get_text(lbl);
            if (txt && strcmp(txt, "Mode: Commander") == 0)
            {
                int32_t life_edh = lv_slider_get_value(objects.single_lifecount_edh_settings_initiallife_slider);
                int32_t players = lv_slider_get_value(objects.single_lifecount_edh_settings_player_slider);
                lv_label_set_text_fmt(objects.sl_edh_life_label, "%d", (int)life_edh);
                sl_layout_count = players;
                sl_layout(players);

                set_value_with_key("sl", "layout_count", sl_layout_count);
                set_value_with_key("sl", "edh_life", life_edh);

                // Reset all opponent dealt/taken to 0
                for (int i = 0; i < 6; i++)
                {
                    sl_players[i].dmg_dealt = 0;
                    sl_players[i].dmg_taken = 0;

                    snprintf(sl_players[i].nickname, sizeof(sl_players[i].nickname), "Player %d", i + 1);

                    // char key_dealt[16];
                    // char key_taken[16];
                    /* Dont save to preferences to decrease wear on flash */
                    // snprintf(key_dealt, sizeof(key_dealt), "p%u_dmg_dealt", i + 1);
                    // snprintf(key_taken, sizeof(key_taken), "p%u_dmg_taken", i + 1);
                    // set_value_with_key("sl", key_dealt, 0);
                    // set_value_with_key("sl", key_taken, 0);
                }
            }
            else
            {

                int32_t life_1v1 = lv_slider_get_value(objects.single_lifecount_1v1_settings_initiallife_slider);
                lv_label_set_text_fmt(objects.sl_1v1_life_label, "%d", (int)life_1v1);

                set_value_with_key("sl", "1v1_life", life_1v1);
            }

            loadScreen(SCREEN_ID_SINGLE_LIFECOUNT);
        }
        break;

        /* ---------------------------------- END SINGLE LIFECOUNT SETTINGS -------------------------- */

        /* ---------------------------------- SINGLE LIFECOUNT OPPONENT SELECTION -------------------------- */

    case ACT_SL_SELECT_OPP0:
        sl_select_opponent(0);
        break;
    case ACT_SL_SELECT_OPP1:
        sl_select_opponent(1);
        break;
    case ACT_SL_SELECT_OPP2:
        sl_select_opponent(2);
        break;
    case ACT_SL_SELECT_OPP3:
        sl_select_opponent(3);
        break;
    case ACT_SL_SELECT_OPP4:
        sl_select_opponent(4);
        break;
    case ACT_SL_SELECT_OPP5:
        sl_select_opponent(5);
        break;

    /* ---------------------------------- END SINGLE LIFECOUNT OPPONENT SELECTION -------------------------- */

    /* ---------------------------------- SINGLE LIFECOUNT OPPONENT DEALT/TAKEN -------------------------- */
    case ACT_SL_EDH_OPP_DEALT_INCR:
        if (sl_players[sl_current_player_idx].dmg_dealt < 99)
        {
            sl_player_add_dealt(sl_current_player_idx, +1);
            bump_life_label(objects.sl_edh_commander_dealt_label, +1);
            refresh_btn_label(sl_current_player_idx);

            char key[16];
            snprintf(key, sizeof(key), "p%u_dmg_dealt", sl_current_player_idx + 1);
            set_value_with_key("sl", key, sl_players[sl_current_player_idx].dmg_dealt);
        }
        break;

    case ACT_SL_EDH_OPP_DEALT_DECR:
        if (sl_players[sl_current_player_idx].dmg_dealt > 0)
        {
            sl_player_add_dealt(sl_current_player_idx, -1);
            bump_life_label(objects.sl_edh_commander_dealt_label, -1);
            refresh_btn_label(sl_current_player_idx);

            char key[16];
            snprintf(key, sizeof(key), "p%u_dmg_dealt", sl_current_player_idx + 1);
            set_value_with_key("sl", key, sl_players[sl_current_player_idx].dmg_dealt);
        }
        break;

    case ACT_SL_EDH_OPP_TAKEN_INCR:
        if (sl_players[sl_current_player_idx].dmg_taken < 99)
        {
            sl_player_add_taken(sl_current_player_idx, +1);
            bump_life_label(objects.sl_edh_commander_taken_label, +1);
            refresh_btn_label(sl_current_player_idx);

            char key[16];
            snprintf(key, sizeof(key), "p%u_dmg_taken", sl_current_player_idx + 1);
            set_value_with_key("sl", key, sl_players[sl_current_player_idx].dmg_taken);
        }
        break;

    case ACT_SL_EDH_OPP_TAKEN_DECR:
        if (sl_players[sl_current_player_idx].dmg_taken > 0)
        {
            sl_player_add_taken(sl_current_player_idx, -1);
            bump_life_label(objects.sl_edh_commander_taken_label, -1);
            refresh_btn_label(sl_current_player_idx);

            char key[16];
            snprintf(key, sizeof(key), "p%u_dmg_taken", sl_current_player_idx + 1);
            set_value_with_key("sl", key, sl_players[sl_current_player_idx].dmg_taken);
        }
        break;

        /* ---------------------------------- END SINGLE LIFECOUNT OPPONENT DEALT/TAKEN -------------------------- */

        /* ---------------------------------- SINGLE LIFECOUNT OPPONENT NAME CHANGE -------------------------- */
    case ACT_SL_OPP_CHANGE_NAME:
        lv_obj_add_state(objects.my_textarea, LV_STATE_FOCUSED);
        loadScreen(SCREEN_ID_TEXT_SCREEN);
        break;

        /* ---------------------------------- END SINGLE LIFECOUNT OPPONENT NAME CHANGE -------------------------- */

        /* ---------------------------------- MULTI LIFECOUNT SETTINGS -------------------------- */
    case ACT_ML_SETTINGS_RESET:
        if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_CLICKED)
        {
            // Reset labels
            lv_label_set_text(objects.multi_lifecount_settings_playercount_label, "Players: 4");
            lv_label_set_text(objects.multi_lifecount_settings_initiallife_label, "Initial Health: 40");

            // Reset slider values
            lv_slider_set_value(objects.multi_lifecount_settings_initiallife_slider, 40, LV_ANIM_OFF);
            lv_slider_set_value(objects.multi_lifecount_settings_player_slider, 4, LV_ANIM_OFF);
        }
        break;

    case ACT_ML_APPLY_SETTINGS:
        if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_CLICKED)
        {
            // Read current settings from sliders
            int32_t players = lv_slider_get_value(objects.multi_lifecount_settings_player_slider);
            int32_t initial_health = lv_slider_get_value(objects.multi_lifecount_settings_initiallife_slider);

            for (int i = 0; i < 6; i++)
            {
                snprintf(ml_players[i].nickname, sizeof(ml_players[i].nickname), "Player %d", i + 1);
                ml_players[i].hp = initial_health;
                ml_players[i].opp1 = 0;
                ml_players[i].opp2 = 0;
                ml_players[i].opp3 = 0;
                ml_players[i].opp4 = 0;
                ml_players[i].opp5 = 0;
                ml_players[i].opp6 = 0;

                lv_label_set_text_fmt(ml_1_cmd_labels[i], "%d", ml_players[i].hp);
                lv_label_set_text_fmt(ml_2_cmd_labels[i], "%d", 0);

                lv_label_set_text(ml_1_cmd_name_labels[i], ml_players[i].nickname);

                /* When reset, dont save to preferences to decrease wear on flash */
                // char key[16];
                // snprintf(key, sizeof(key), "p%u_hp", i + 1);
                // set_value_with_key("ml", key, ml_players[i].hp);
                // snprintf(key, sizeof(key), "p%u_opp1", i + 1);
                // set_value_with_key("ml", key, 0);
                // snprintf(key, sizeof(key), "p%u_opp2", i + 1);
                // set_value_with_key("ml", key, 0);
                // snprintf(key, sizeof(key), "p%u_opp3", i + 1);
                // set_value_with_key("ml", key, 0);
                // snprintf(key, sizeof(key), "p%u_opp4", i + 1);
                // set_value_with_key("ml", key, 0);
                // snprintf(key, sizeof(key), "p%u_opp5", i + 1);
                // set_value_with_key("ml", key, 0);
                // snprintf(key, sizeof(key), "p%u_opp6", i + 1);
                // set_value_with_key("ml", key, 0);
            }

            ml_layout_count = players;
            ml_1_layout(players);
            ml_2_layout(players);

            set_value_with_key("ml", "layout_count", ml_layout_count);

            loadScreen(SCREEN_ID_MULTI_LIFECOUNT);
        }
        break;

        /* ---------------------------------- END MULTI LIFECOUNT SETTINGS -------------------------- */

        /* ---------------------------------- MULTI LIFECOUNT OPPONENT SELECTION -------------------------- */

    case ACT_ML_SELECT_OPP0:
        ml_select_opponent(0);
        break;
    case ACT_ML_SELECT_OPP1:
        ml_select_opponent(1);
        break;
    case ACT_ML_SELECT_OPP2:
        ml_select_opponent(2);
        break;
    case ACT_ML_SELECT_OPP3:
        ml_select_opponent(3);
        break;
    case ACT_ML_SELECT_OPP4:
        ml_select_opponent(4);
        break;
    case ACT_ML_SELECT_OPP5:
        ml_select_opponent(5);
        break;

        /* ---------------------------------- END MULTI LIFECOUNT OPPONENT SELECTION -------------------------- */

        /* ---------------------------------- MULTI LIFECOUNT LIFE LABEL MANAGEMENT -------------------------- */
    case ACT_ML_LIFE_DECR:
        if (code == LV_EVENT_SHORT_CLICKED ||
            code == LV_EVENT_LONG_PRESSED_REPEAT)
        {
            bump_life_label(objects.ml_life_label, -1);
            ml_player_add_hp(ml_current_player_idx, -1);

            lv_label_set_text_fmt(ml_1_cmd_labels[ml_current_player_idx], "%d", ml_players[ml_current_player_idx].hp);

            char key[16];
            snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
        }

        break;

    case ACT_ML_LIFE_INCR:
        if (code == LV_EVENT_SHORT_CLICKED ||
            code == LV_EVENT_LONG_PRESSED_REPEAT)
        {
            bump_life_label(objects.ml_life_label, 1);
            ml_player_add_hp(ml_current_player_idx, 1);

            lv_label_set_text_fmt(ml_1_cmd_labels[ml_current_player_idx], "%d", ml_players[ml_current_player_idx].hp);

            char key[16];
            snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
        }
        break;

        /* ---------------------------------- END MULTI LIFECOUNT LIFE LABEL MANAGEMENT -------------------------- */

        /* ---------------------------------- MULTI LIFECOUNT COMMANDER DAMAGE MANAGEMENT -------------------------- */

    case ACT_ML_2_OPP0:
        if (code == LV_EVENT_SHORT_CLICKED)
        {
            // Increase commander damage
            bump_life_label(objects.ml_2_btn1_label, 1);
            // Decrease player life label
            bump_life_label(objects.ml_life_label, -1);
            // Decrease player life in main label
            bump_life_label(ml_1_cmd_labels[ml_current_player_idx], -1);
            // Update player state
            ml_players[ml_current_player_idx].hp--;
            ml_players[ml_current_player_idx].opp1++;

            char key[16];
            snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp1", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp1);
        }

        if (code == LV_EVENT_LONG_PRESSED)
        {
            bump_life_label(objects.ml_2_btn1_label, -1);
            // bump_life_label(objects.ml_life_label, 1);
            // bump_life_label(ml_1_cmd_labels[ml_current_player_idx], 1);
            // ml_players[ml_current_player_idx].hp++;
            ml_players[ml_current_player_idx].opp1--;

            char key[16];
            // snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            // set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp1", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp1);
        }
        break;
    case ACT_ML_2_OPP1:
        if (code == LV_EVENT_SHORT_CLICKED)
        {
            bump_life_label(objects.ml_2_btn2_label, 1);
            bump_life_label(objects.ml_life_label, -1);
            bump_life_label(ml_1_cmd_labels[ml_current_player_idx], -1);
            ml_players[ml_current_player_idx].hp--;
            ml_players[ml_current_player_idx].opp2++;

            char key[16];
            snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp2", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp2);
        }

        if (code == LV_EVENT_LONG_PRESSED)
        {
            bump_life_label(objects.ml_2_btn2_label, -1);
            // bump_life_label(objects.ml_life_label, 1);
            // bump_life_label(ml_1_cmd_labels[ml_current_player_idx], 1);
            // ml_players[ml_current_player_idx].hp++;
            ml_players[ml_current_player_idx].opp2--;

            char key[16];
            // snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            // set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp2", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp2);
        }
        break;
    case ACT_ML_2_OPP2:
        if (code == LV_EVENT_SHORT_CLICKED)
        {
            bump_life_label(objects.ml_2_btn3_label, 1);
            bump_life_label(objects.ml_life_label, -1);
            bump_life_label(ml_1_cmd_labels[ml_current_player_idx], -1);
            ml_players[ml_current_player_idx].hp--;
            ml_players[ml_current_player_idx].opp3++;

            char key[16];
            snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp3", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp3);
        }

        if (code == LV_EVENT_LONG_PRESSED)
        {
            bump_life_label(objects.ml_2_btn3_label, -1);
            // bump_life_label(objects.ml_life_label, 1);
            // bump_life_label(ml_1_cmd_labels[ml_current_player_idx], 1);
            // ml_players[ml_current_player_idx].hp++;
            ml_players[ml_current_player_idx].opp3--;

            char key[16];
            // snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            // set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp3", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp3);
        }
        break;
    case ACT_ML_2_OPP3:
        if (code == LV_EVENT_SHORT_CLICKED)
        {
            bump_life_label(objects.ml_2_btn4_label, 1);
            bump_life_label(objects.ml_life_label, -1);
            bump_life_label(ml_1_cmd_labels[ml_current_player_idx], -1);
            ml_players[ml_current_player_idx].hp--;
            ml_players[ml_current_player_idx].opp4++;

            char key[16];
            snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp4", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp4);
        }

        if (code == LV_EVENT_LONG_PRESSED)
        {
            bump_life_label(objects.ml_2_btn4_label, -1);
            // bump_life_label(objects.ml_life_label, 1);
            // bump_life_label(ml_1_cmd_labels[ml_current_player_idx], 1);
            // ml_players[ml_current_player_idx].hp++;
            ml_players[ml_current_player_idx].opp4--;

            char key[16];
            // snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            // set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp4", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp4);
        }
        break;
    case ACT_ML_2_OPP4:
        if (code == LV_EVENT_SHORT_CLICKED)
        {
            bump_life_label(objects.ml_2_btn5_label, 1);
            bump_life_label(objects.ml_life_label, -1);
            bump_life_label(ml_1_cmd_labels[ml_current_player_idx], -1);
            ml_players[ml_current_player_idx].hp--;
            ml_players[ml_current_player_idx].opp5++;

            char key[16];
            snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp5", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp5);
        }

        if (code == LV_EVENT_LONG_PRESSED)
        {
            bump_life_label(objects.ml_2_btn5_label, -1);
            // bump_life_label(objects.ml_life_label, 1);
            // bump_life_label(ml_1_cmd_labels[ml_current_player_idx], 1);
            // ml_players[ml_current_player_idx].hp++;
            ml_players[ml_current_player_idx].opp5--;

            char key[16];
            // snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            // set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp5", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp5);
        }
        break;
    case ACT_ML_2_OPP5:
        if (code == LV_EVENT_SHORT_CLICKED)
        {
            bump_life_label(objects.ml_2_btn6_label, 1);
            bump_life_label(objects.ml_life_label, -1);
            bump_life_label(ml_1_cmd_labels[ml_current_player_idx], -1);
            ml_players[ml_current_player_idx].hp--;
            ml_players[ml_current_player_idx].opp6++;

            char key[16];
            snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp6", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp6);
        }

        if (code == LV_EVENT_LONG_PRESSED)
        {
            bump_life_label(objects.ml_2_btn6_label, -1);
            // bump_life_label(objects.ml_life_label, 1);
            // bump_life_label(ml_1_cmd_labels[ml_current_player_idx], 1);
            // ml_players[ml_current_player_idx].hp++;
            ml_players[ml_current_player_idx].opp6--;

            char key[16];
            // snprintf(key, sizeof(key), "p%u_hp", ml_current_player_idx + 1);
            // set_value_with_key("ml", key, ml_players[ml_current_player_idx].hp);
            snprintf(key, sizeof(key), "p%u_opp6", ml_current_player_idx + 1);
            set_value_with_key("ml", key, ml_players[ml_current_player_idx].opp6);
        }
        break;

        /* ---------------------------------- END MULTI LIFECOUNT COMMANDER DAMAGE MANAGEMENT -------------------------- */

    default:
        break;
    }
}

void action_generic_slider_cb(lv_event_t *e)
{
    uint32_t id = (uint32_t)lv_event_get_user_data(e);
    lv_obj_t *slider = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    int32_t v = lv_slider_get_value(slider);

    switch (id)
    {
    case ACT_SLI_BRIGHTNESS:
        if (v < 0)
            v = 0;
        if (v > 255)
            v = 255;

        if (code == LV_EVENT_VALUE_CHANGED)
        {
            analogWrite(27, v); // live effect while dragging
        }
        else if (code == LV_EVENT_RELEASED)
        {
            set_value_with_key("pref", "brightness", (uint8_t)v);
        }
        break;

    case ACT_SLI_DICE_VALUE:
        if (v < 1)
            v = 1;
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            lv_label_set_text_fmt(objects.dice_label, "%d", v);
        }
        break;

    case ACT_SLI_SL_EDH_INIT_LIFE:
    {
        lv_obj_t *slider = lv_event_get_target(e);
        int32_t value = lv_slider_get_value(slider);

        lv_label_set_text_fmt(objects.single_lifecount_edh_settings_initiallife_label, "Initial Health: %d", value);
        break;
    }

    case ACT_SLI_SL_EDH_PLAYERCOUNT:
    {
        lv_obj_t *slider = lv_event_get_target(e);
        int32_t value = lv_slider_get_value(slider);

        lv_label_set_text_fmt(objects.single_lifecount_edh_settings_playercount_label, "Players: %d", value);
        break;
    }

    case ACT_SLI_SL_1V1_INIT_LIFE:
    {
        lv_obj_t *slider = lv_event_get_target(e);
        int32_t value = lv_slider_get_value(slider);

        lv_label_set_text_fmt(objects.single_lifecount_1v1_settings_initiallife_label, "Initial Health: %d", value);
        break;
    }

    // Below is for multi life count
    case ACT_SLI_ML_INIT_LIFE:
    {
        lv_obj_t *slider = lv_event_get_target(e);
        int32_t value = lv_slider_get_value(slider);

        lv_label_set_text_fmt(objects.multi_lifecount_settings_initiallife_label, "Initial Health: %d", value);
        break;
    }

    case ACT_SLI_ML_PLAYERCOUNT:
    {
        lv_obj_t *slider = lv_event_get_target(e);
        int32_t value = lv_slider_get_value(slider);

        lv_label_set_text_fmt(objects.multi_lifecount_settings_playercount_label, "Players: %d", value);
        break;
    }

    default:
        break;
    }
}

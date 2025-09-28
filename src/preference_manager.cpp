#include "preference_manager.h"
#include <Preferences.h>
#include <lvgl.h>
#include "ui/styles.h"
#include "ui/images.h"
#include "ui/ui.h"
#include "state.h"
#include "layout.h"
#include "player.h"

#ifdef __cplusplus
extern "C"
{
#endif
    uint8_t get_value_with_key(const char *ns, const char *key, uint8_t def_val)
    {
        Preferences p;
        if (!p.begin(ns, /*readOnly=*/true))
            return def_val;
        uint8_t val = p.getUChar(key, def_val);
        p.end();
        return val;
    }

    bool set_value_with_key(const char *ns, const char *key, uint8_t val)
    {
        Preferences p;
        if (!p.begin(ns, /*readOnly=*/false))
            return false;
        p.putUChar(key, val);
        p.end();
        return true;
    }

    void get_string_with_key(const char *ns, const char *key, char *buf, uint8_t bufsize, const char *def_val)
    {
        Preferences p;
        if (!p.begin(ns, /*readOnly=*/true))
        {
            strncpy(buf, def_val, bufsize);
            buf[bufsize - 1] = '\0';
            return;
        }
        p.getString(key, buf, bufsize);
        if (buf[0] == '\0' && def_val)
        {
            strncpy(buf, def_val, bufsize);
            buf[bufsize - 1] = '\0';
        }
        p.end();
        return;
    }

    bool set_string_with_key(const char *ns, const char *key, const char *val)
    {
        Preferences p;
        if (!p.begin(ns, /*readOnly=*/false))
            return false;
        p.putString(key, val);
        p.end();
        return true;
    }

#ifdef __cplusplus
}
#endif

void init_preferences(void)
{
    // Set initial value for brightness slider
    lv_slider_set_value(objects.brightness_slider, get_value_with_key("pref", "brightness", 125), LV_ANIM_OFF);

    // Set EEPROM background
    lv_style_t *style = get_style_main_background_MAIN_DEFAULT();
    uint16_t bg_idx = get_value_with_key("pref", "bg_idx", 0);
    lv_style_set_bg_img_src(style, images[bg_idx].img_dsc);

    // Restore mana state
    mana_state.black = get_value_with_key("mana", "black", 0);
    mana_state.blue = get_value_with_key("mana", "blue", 0);
    mana_state.green = get_value_with_key("mana", "green", 0);
    mana_state.yellow = get_value_with_key("mana", "yellow", 0);
    mana_state.red = get_value_with_key("mana", "red", 0);
    mana_state.colorless = get_value_with_key("mana", "colorless", 0);
    lv_label_set_text_fmt(objects.mana_black_label, "%d", mana_state.black);
    lv_label_set_text_fmt(objects.mana_blue_label, "%d", mana_state.blue);
    lv_label_set_text_fmt(objects.mana_green_label, "%d", mana_state.green);
    lv_label_set_text_fmt(objects.mana_yellow_label, "%d", mana_state.yellow);
    lv_label_set_text_fmt(objects.mana_red_label, "%d", mana_state.red);
    lv_label_set_text_fmt(objects.mana_colorless_label, "%d", mana_state.colorless);

    // Restore single lifecount state
    lv_label_set_text_fmt(objects.sl_edh_life_label, "%d", get_value_with_key("sl", "edh_life", 40));
    lv_label_set_text_fmt(objects.sl_1v1_life_label, "%d", get_value_with_key("sl", "1v1_life", 20));
    // Restore layout count
    sl_layout_count = get_value_with_key("sl", "layout_count", 4);
    sl_layout(sl_layout_count);
    // Restore player information
    for (uint8_t i = 1; i < 7; i++)
    {
        sl_players[i - 1].dmg_dealt = get_value_with_key("sl", ("p" + std::to_string(i) + "_dmg_dealt").c_str(), 0);
        sl_players[i - 1].dmg_taken = get_value_with_key("sl", ("p" + std::to_string(i) + "_dmg_taken").c_str(), 0);
        get_string_with_key("sl", ("p" + std::to_string(i) + "_name").c_str(), sl_players[i - 1].nickname, 9, ("Player " + std::to_string(i)).c_str());

        lv_label_set_text_fmt(
            sl_cmd_labels[i - 1],
            "%s\nTo: %d\nFrom: %d",
            sl_players[i - 1].nickname,
            sl_players[i - 1].dmg_dealt,
            sl_players[i - 1].dmg_taken);
    }

    // Restore multi lifecount state
    ml_layout_count = get_value_with_key("ml", "layout_count", 4);
    ml_1_layout(ml_layout_count);
    ml_2_layout(ml_layout_count);

    for (uint8_t i = 1; i < 7; i++)
    {
        ml_players[i - 1].hp = get_value_with_key("ml", ("p" + std::to_string(i) + "_hp").c_str(), 40);
        ml_players[i - 1].opp1 = get_value_with_key("ml", ("p" + std::to_string(i) + "_opp1").c_str(), 0);
        ml_players[i - 1].opp2 = get_value_with_key("ml", ("p" + std::to_string(i) + "_opp2").c_str(), 0);
        ml_players[i - 1].opp3 = get_value_with_key("ml", ("p" + std::to_string(i) + "_opp3").c_str(), 0);
        ml_players[i - 1].opp4 = get_value_with_key("ml", ("p" + std::to_string(i) + "_opp4").c_str(), 0);
        ml_players[i - 1].opp5 = get_value_with_key("ml", ("p" + std::to_string(i) + "_opp5").c_str(), 0);
        ml_players[i - 1].opp6 = get_value_with_key("ml", ("p" + std::to_string(i) + "_opp6").c_str(), 0);

        lv_label_set_text_fmt(ml_1_cmd_labels[i - 1], "%d", ml_players[i - 1].hp);
        lv_label_set_text_fmt(ml_2_cmd_labels[i - 1], "%d", ml_players[i - 1].hp);

        get_string_with_key("ml", ("p" + std::to_string(i) + "_name").c_str(), ml_players[i - 1].nickname, 9, ("Player " + std::to_string(i)).c_str());
        lv_label_set_text_fmt(ml_1_cmd_name_labels[i - 1], "%s", ml_players[i - 1].nickname);
    }

    return;
}
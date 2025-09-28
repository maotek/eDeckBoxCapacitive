/* ui_action.h – stable numeric IDs for EEZ “User data” literals */
#ifndef UI_ACTION_H
#define UI_ACTION_H

/* ------------------------------------------------------------------
 * Ranges
 * ------------------------------------------------------------------*/
typedef enum
{
    /* --- mana counter ------------------------------------------------ */
    ACT_MANA_BLUE_INCR = 0,
    ACT_MANA_BLUE_DECR = 1,
    ACT_MANA_BLACK_INCR = 2,
    ACT_MANA_BLACK_DECR = 3,
    ACT_MANA_GREEN_INCR = 4,
    ACT_MANA_GREEN_DECR = 5,
    ACT_MANA_YELLOW_INCR = 6,
    ACT_MANA_YELLOW_DECR = 7,
    ACT_MANA_RED_INCR = 8,
    ACT_MANA_RED_DECR = 9,
    ACT_MANA_COLORLESS_INCR = 10,
    ACT_MANA_COLORLESS_DECR = 11,

    ACT_MANA_RESET = 12,

    /* --- navigation ------------------------------------------------ */
    ACT_OPEN_ABOUT = 100,
    ACT_OPEN_MENU = 101,
    ACT_OPEN_WALLPAPER = 102,
    ACT_OPEN_SETTINGS = 103,
    ACT_OPEN_SINGLE_LIFECOUNT = 104,
    ACT_OPEN_COUNTER_SELECTOR = 105,
    ACT_OPEN_SINGLE_LIFECOUNT_SETTINGS = 106,
    ACT_OPEN_DICE = 107,
    ACT_OPEN_MANACOUNTER = 108,
    ACT_OPEN_MULTI_LIFECOUNT = 109,
    ACT_OPEN_MULTI_LIFECOUNT_SETTINGS = 110,

    /* --- settings ------------------------------------------------ */
    ACT_TOGGLE_PERF_MON = 200,
    ACT_TOGGLE_BACKGROUND = 201,
    ACT_RESTART_DEVICE = 202,

    /* --- dice --- */
    ACT_ROLL_DICE = 300,

    /* single lifecount main page */
    // EDH
    ACT_SL_EDH_LIFE_DECR = 500,
    ACT_SL_EDH_LIFE_INCR = 501,
    // 1v1
    ACT_SL_1v1_LIFE_DECR = 502,
    ACT_SL_1v1_LIFE_INCR = 503,

    /* single lifecount settings/actions */
    ACT_SL_SETTING_MODE_TOGGLE = 510,
    ACT_SL_SETTINGS_RESET = 511,
    ACT_SL_APPLY_SETTINGS = 512,

    /* single lifecount main page */
    ACT_SL_SELECT_OPP0 = 600,
    ACT_SL_SELECT_OPP1 = 601,
    ACT_SL_SELECT_OPP2 = 602,
    ACT_SL_SELECT_OPP3 = 603,
    ACT_SL_SELECT_OPP4 = 604,
    ACT_SL_SELECT_OPP5 = 605,

    ACT_SL_EDH_OPP_DEALT_INCR = 610,
    ACT_SL_EDH_OPP_DEALT_DECR = 611,
    ACT_SL_EDH_OPP_TAKEN_INCR = 612,
    ACT_SL_EDH_OPP_TAKEN_DECR = 613,

    /* single lifecount opponnent set name */
    ACT_SL_OPP_CHANGE_NAME = 630,

    /* multi lifecount settings */
    ACT_ML_SETTINGS_RESET = 700,
    ACT_ML_APPLY_SETTINGS = 701,

    ACT_ML_SELECT_OPP0 = 715,
    ACT_ML_SELECT_OPP1 = 716,
    ACT_ML_SELECT_OPP2 = 717,
    ACT_ML_SELECT_OPP3 = 718,
    ACT_ML_SELECT_OPP4 = 719,
    ACT_ML_SELECT_OPP5 = 720,

    ACT_ML_LIFE_DECR = 730,
    ACT_ML_LIFE_INCR = 731,

    ACT_ML_2_OPP0 = 740,
    ACT_ML_2_OPP1 = 741,
    ACT_ML_2_OPP2 = 742,
    ACT_ML_2_OPP3 = 743,
    ACT_ML_2_OPP4 = 744,
    ACT_ML_2_OPP5 = 745,

} ui_btn_action_t;

typedef enum
{
    /* settings brightness */
    ACT_SLI_BRIGHTNESS = 800,

    /* dice screen max value */
    ACT_SLI_DICE_VALUE = 801,

    /* single lifecount settings*/
    ACT_SLI_SL_EDH_INIT_LIFE = 802,
    ACT_SLI_SL_EDH_PLAYERCOUNT = 803,
    ACT_SLI_SL_1V1_INIT_LIFE = 804,

    /* multi lifecount settings*/
    ACT_SLI_ML_INIT_LIFE = 810,
    ACT_SLI_ML_PLAYERCOUNT = 811,

} ui_slider_action_t;

#endif /* UI_ACTION_H */

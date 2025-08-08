/* ui_action.h – stable numeric IDs for EEZ “User data” literals */
#ifndef UI_ACTION_H
#define UI_ACTION_H

/* ------------------------------------------------------------------
 * Ranges
 * ------------------------------------------------------------------*/
typedef enum
{
    /* --- navigation ------------------------------------------------ */
    ACT_OPEN_ABOUT = 100,
    ACT_OPEN_MENU = 101,
    ACT_OPEN_WALLPAPER = 102,
    ACT_OPEN_SETTINGS = 103,
    ACT_OPEN_SINGLE_LIFECOUNT = 104,
    ACT_OPEN_LIFECOUNT_SELECTOR = 105,
    ACT_OPEN_SINGLE_LIFECOUNT_SETTINGS = 106,
    ACT_OPEN_DICE = 107,

    /* --- settings ------------------------------------------------ */
    ACT_TOGGLE_PERF_MON = 200,
    ACT_TOGGLE_BACKGROUND = 201,
    ACT_RESTART_DEVICE = 202,

    /* --- dice --- */
    ACT_ROLL_DICE = 300,

    /* single lifecount main page */
    // EDH
    ACT_SINGLE_LIFECOUNT_EDH_LIFE_DECR = 500,
    ACT_SINGLE_LIFECOUNT_EDH_LIFE_INCR = 501,
    // 1v1
    ACT_SINGLE_LIFECOUNT_1v1_LIFE_DECR = 502,
    ACT_SINGLE_LIFECOUNT_1v1_LIFE_INCR = 503,

    /* single lifecount settings/actions */
    ACT_SINGLE_LIFECOUNT_SETTING_MODE_TOGGLE = 510,
    ACT_SINGLE_LIFECOUNT_SETTINGS_RESET = 511,
    ACT_SINGLE_LIFECOUNT_APPLY_SETTINGS = 512,

    /* single lifecount main page */
    ACT_SINGLE_SELECT_OPP0 = 600,
    ACT_SINGLE_SELECT_OPP1 = 601,
    ACT_SINGLE_SELECT_OPP2 = 602,
    ACT_SINGLE_SELECT_OPP3 = 603,
    ACT_SINGLE_SELECT_OPP4 = 604,
    ACT_SINGLE_SELECT_OPP5 = 605,

    ACT_SINGLE_EDH_OPP_DEALT_INCR = 610,
    ACT_SINGLE_EDH_OPP_DEALT_DECR = 611,
    ACT_SINGLE_EDH_OPP_TAKEN_INCR = 612,
    ACT_SINGLE_EDH_OPP_TAKEN_DECR = 613,

    /* single lifecount opponnent set name */
    ACT_SINGLE_LIFECOUNT_OPP_CHANGE_NAME = 630

} ui_btn_action_t;

typedef enum
{
    /* settings brightness */
    ACT_SLI_BRIGHTNESS = 800,

    /* dice screen max value */
    ACT_SLI_DICE_VALUE = 801,

    /* single lifecount settings*/
    ACT_SLI_EDH_INIT_LIFE = 802,
    ACT_SLI_EDH_PLAYERCOUNT = 803,
    ACT_SLI_1V1_INIT_LIFE = 804,

} ui_slider_action_t;

#endif /* UI_ACTION_H */

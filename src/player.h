#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "lvgl.h"

/**
 * Player data record
 *  - nickname    : short name for the player (null-terminated string)
 *  - dmg_taken   : life you have lost (signed 8-bit)
 *  - dmg_dealt   : commander damage you have dealt (signed 8-bit)
 */
typedef struct
{
    char nickname[9]; // max 8 chars + null terminator
    int8_t dmg_taken;
    int8_t dmg_dealt;
} player_t;

#ifdef __cplusplus
extern "C"
{
#endif

    /** Fixed table holding exactly six players */
    extern player_t g_players[6];
    extern uint8_t current_player_idx;

    /* --- helpers --------------------------------------------------------- */
    void player_add_taken(uint8_t id, int8_t delta);
    void player_add_dealt(uint8_t id, int8_t delta);
    void player_set_nickname(uint8_t id, const char *name);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLAYER_H */

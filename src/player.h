#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "lvgl.h"

typedef struct
{
    char nickname[9]; // max 8 chars + null terminator
    int8_t dmg_taken;
    int8_t dmg_dealt;
} sl_player_t;

typedef struct
{
    char nickname[9]; // max 8 chars + null terminator
    int8_t hp;
    int8_t opp1;
    int8_t opp2;
    int8_t opp3;
    int8_t opp4;
    int8_t opp5;
    int8_t opp6;
} ml_player_t;

typedef enum
{
    GAME_MODE_SL = 0,
    GAME_MODE_ML = 1,
} GameMode;

#ifdef __cplusplus
extern "C"
{
#endif

    /** Fixed table holding exactly six players */
    extern sl_player_t sl_players[6];
    extern ml_player_t ml_players[6];
    extern uint8_t sl_current_player_idx;
    extern uint8_t ml_current_player_idx;

    extern GameMode current_game_mode;

    /* --- helpers --------------------------------------------------------- */
    void sl_player_add_taken(uint8_t id, int8_t delta);
    void sl_player_add_dealt(uint8_t id, int8_t delta);
    void sl_player_set_nickname(uint8_t id, const char *name);

    void ml_player_add_hp(uint8_t id, int8_t delta);
    void ml_player_set_nickname(uint8_t id, const char *name);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PLAYER_H */

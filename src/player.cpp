#include "player.h"
#include <string.h> // for strncpy

/* -------------------------------------------------------------------- */
/*  Hard-coded initial nicknames.                                       */
/* -------------------------------------------------------------------- */
sl_player_t sl_players[6] = {
    {"You", 0, 0},
    {"Player 2", 0, 0},
    {"Player 3", 0, 0},
    {"Player 4", 0, 0},
    {"Player 5", 0, 0},
    {"Player 6", 0, 0}};

ml_player_t ml_players[6] = {
    {"Player 1", 40, 0, 0, 0, 0, 0, 0},
    {"Player 2", 40, 0, 0, 0, 0, 0, 0},
    {"Player 3", 40, 0, 0, 0, 0, 0, 0},
    {"Player 4", 40, 0, 0, 0, 0, 0, 0},
    {"Player 5", 40, 0, 0, 0, 0, 0, 0},
    {"Player 6", 40, 0, 0, 0, 0, 0, 0}};

uint8_t sl_current_player_idx = 0;
uint8_t ml_current_player_idx = 0;

GameMode current_game_mode;

/* -------------------------------------------------------------------- */
void sl_player_add_taken(uint8_t id, int8_t delta)
{
    if (id < 6)
        sl_players[id].dmg_taken += delta;
}

void sl_player_add_dealt(uint8_t id, int8_t delta)
{
    if (id < 6)
        sl_players[id].dmg_dealt += delta;
}

void sl_player_set_nickname(uint8_t id, const char *name)
{
    if (id < 6 && name != NULL)
    {
        strncpy(sl_players[id].nickname, name, sizeof(sl_players[id].nickname) - 1);
        sl_players[id].nickname[sizeof(sl_players[id].nickname) - 1] = '\0'; // ensure null-termination
    }
}

void ml_player_add_hp(uint8_t id, int8_t delta)
{
    if (id < 6)
        ml_players[id].hp += delta;
}

void ml_player_set_nickname(uint8_t id, const char *name)
{
    if (id < 6 && name != NULL)
    {
        strncpy(ml_players[id].nickname, name, sizeof(ml_players[id].nickname) - 1);
        ml_players[id].nickname[sizeof(ml_players[id].nickname) - 1] = '\0'; // ensure null-termination
    }
}

#include "player.h"
#include <string.h> // for strncpy

/* -------------------------------------------------------------------- */
/*  Hard-coded initial nicknames.                                       */
/* -------------------------------------------------------------------- */
player_t g_players[6] = {
    {"You", 0, 0},
    {"Player 2", 0, 0},
    {"Player 3", 0, 0},
    {"Player 4", 0, 0},
    {"Player 5", 0, 0},
    {"Player 6", 0, 0}};

uint8_t current_player_idx = 0;

/* -------------------------------------------------------------------- */
void player_add_taken(uint8_t id, int8_t delta)
{
    if (id < 6)
        g_players[id].dmg_taken += delta;
}

void player_add_dealt(uint8_t id, int8_t delta)
{
    if (id < 6)
        g_players[id].dmg_dealt += delta;
}

void player_set_nickname(uint8_t id, const char *name)
{
    if (id < 6 && name != NULL)
    {
        strncpy(g_players[id].nickname, name, sizeof(g_players[id].nickname) - 1);
        g_players[id].nickname[sizeof(g_players[id].nickname) - 1] = '\0'; // ensure null-termination
    }
}

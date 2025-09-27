#include "player.h"
#include <string.h> // for strncpy

/* -------------------------------------------------------------------- */
/*  Hard-coded initial nicknames.                                       */
/* -------------------------------------------------------------------- */
singlecount_player_t singlecount_players[6] = {
    {"You", 0, 0},
    {"Player 2", 0, 0},
    {"Player 3", 0, 0},
    {"Player 4", 0, 0},
    {"Player 5", 0, 0},
    {"Player 6", 0, 0}};

uint8_t singlecount_current_player_idx = 0;

/* -------------------------------------------------------------------- */
void singlecount_player_add_taken(uint8_t id, int8_t delta)
{
    if (id < 6)
        singlecount_players[id].dmg_taken += delta;
}

void singlecount_player_add_dealt(uint8_t id, int8_t delta)
{
    if (id < 6)
        singlecount_players[id].dmg_dealt += delta;
}

void singlecount_player_set_nickname(uint8_t id, const char *name)
{
    if (id < 6 && name != NULL)
    {
        strncpy(singlecount_players[id].nickname, name, sizeof(singlecount_players[id].nickname) - 1);
        singlecount_players[id].nickname[sizeof(singlecount_players[id].nickname) - 1] = '\0'; // ensure null-termination
    }
}

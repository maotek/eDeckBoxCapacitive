#include <stdint.h>

typedef struct
{
    uint8_t black;
    uint8_t blue;
    uint8_t green;
    uint8_t yellow;
    uint8_t red;
    uint8_t colorless;
} mana_state_t;

extern mana_state_t mana_state;
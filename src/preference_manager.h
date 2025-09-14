#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // Save current background index to NVS ("ui"/"bg_idx").
    // Returns true if a new value was written (changed), false otherwise.
    bool bg_save_index(uint16_t idx);

    // Read saved background index; returns def_val if not present.
    uint16_t bg_get_index(uint16_t def_val);

    // Save current brightness level to NVS ("ui"/"brightness").
    // Returns true if a new value was written (changed), false otherwise.
    bool brightness_save(uint16_t level);

    // Read saved brightness level; returns def_val if not present.
    uint16_t brightness_get(uint16_t def_val);

#ifdef __cplusplus
}
#endif
#include "state_manager.h"
#include <Preferences.h>

static const char *NVS_NAMESPACE = "ui";
static const char *KEY_BG_IDX = "bg_idx";
static const char *KEY_BRIGHT = "brightness";

bool bg_save_index(uint16_t idx)
{
    Preferences p;
    if (!p.begin(NVS_NAMESPACE, /*readOnly=*/false))
        return false;
    uint16_t cur = p.getUShort(KEY_BG_IDX, 0xFFFF);
    bool changed = (cur != idx);
    if (changed)
        p.putUShort(KEY_BG_IDX, idx);
    p.end();
    return changed;
}

uint16_t bg_get_index(uint16_t def_val)
{
    Preferences p;
    if (!p.begin(NVS_NAMESPACE, /*readOnly=*/true))
        return def_val;
    uint16_t val = p.getUShort(KEY_BG_IDX, def_val);
    p.end();
    return val;
}

// ---- Brightness persistence ----

bool brightness_save(uint16_t level)
{
    Preferences p;
    if (!p.begin(NVS_NAMESPACE, /*readOnly=*/false))
        return false;
    uint16_t cur = p.getUShort(KEY_BRIGHT, 0xFFFF);
    bool changed = (cur != level);
    if (changed)
        p.putUShort(KEY_BRIGHT, level);
    p.end();
    return changed;
}

uint16_t brightness_get(uint16_t def_val)
{
    Preferences p;
    if (!p.begin(NVS_NAMESPACE, /*readOnly=*/true))
        return def_val;
    uint16_t val = p.getUShort(KEY_BRIGHT, def_val);
    p.end();
    return val;
}
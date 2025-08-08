// layout.h — commander‑damage button placement helpers
#ifndef LAYOUT_H
#define LAYOUT_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Six commander‑damage buttons created elsewhere */
    extern lv_obj_t *cmd_btn[6];
    extern lv_obj_t *cmd_btn_label[6];

    /* Apply rectangular layouts according to player count (2‑4) */
    void layout_commander_buttons(uint8_t count);

    /* Screen initialiser — binds the six buttons and applies default layout */
    void single_lifecount_edh_layout_init(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LAYOUT_H */

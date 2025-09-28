// layout.h — commander‑damage button placement helpers
#ifndef LAYOUT_H
#define LAYOUT_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Six commander‑damage buttons created elsewhere */
    extern lv_obj_t *sl_cmd_btns[6];
    extern lv_obj_t *sl_cmd_labels[6];

    extern lv_obj_t *ml_1_cmd_btns[6];
    extern lv_obj_t *ml_1_cmd_labels[6];

    extern lv_obj_t *ml_2_cmd_btns[6];
    extern lv_obj_t *ml_2_cmd_labels[6];

    extern lv_obj_t *ml_1_cmd_name_labels[6];
    extern lv_obj_t *ml_2_cmd_name_labels[6];

    extern uint8_t sl_layout_count;
    extern uint8_t ml_layout_count;

    /* Apply rectangular layouts according to player count (2‑4) */
    void sl_layout(uint8_t count);

    void ml_1_layout(uint8_t count);

    void ml_2_layout(uint8_t count);

    /* Screen initialiser — binds the six buttons and applies default layout */
    void layout_init(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LAYOUT_H */

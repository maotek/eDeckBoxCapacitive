# MaoTek eDeckBox, electronic DeckBox for MTG with built-in lifecounter

## Specs

- CYD 2.4 inch (capacitive touch version)
- 1800mAh LiPo (Maybe more?) total 3.7 Wh power.
- 0.78 Watt @ 5V at max brightness
- 0.56 Watt @ 5V at lowest brightness
- (Maybe lower PMW duty cycle for less brightness?)

---

## Stack

- LVGL v8.3.11
- PlatformIO

---

## What's Done

- A lot

---

## TODO

- BUGS

---

## End of Life

- MaoTek Enterprise does not support further development of this product.

---

## For performance monitor, please paste the following code into LVGL lvgl/src/core/lv_refr.c

Put this variable on top of the file:

```cpp
#if LV_USE_PERF_MONITOR
static bool perf_monitor_enabled = false;
#endif
```

Then define this somewhere:

```cpp
#if LV_USE_PERF_MONITOR && LV_USE_LABEL
lv_obj_t *lv_perf_monitor_get_label(void)
{
    return perf_monitor.perf_label;
}
#endif

#if LV_USE_PERF_MONITOR
void lv_perf_monitor_enable(bool en)
{
    perf_monitor_enabled = en;
}
#endif
```

And wrap the following code with the boolean:

```cpp
    if (perf_monitor_enabled)
    {

        if (lv_tick_elaps(perf_monitor.perf_last_time) < 300)
        {
            if (px_num > 5000)
            {
                perf_monitor.elaps_sum += elaps;
                perf_monitor.frame_cnt++;
            }
        }
        else
        {
            perf_monitor.perf_last_time = lv_tick_get();
            uint32_t fps_limit;
            uint32_t fps;

            if (disp_refr->refr_timer)
            {
                fps_limit = 1000 / disp_refr->refr_timer->period;
            }
            else
            {
                fps_limit = 1000 / LV_DISP_DEF_REFR_PERIOD;
            }

            if (perf_monitor.elaps_sum == 0)
            {
                perf_monitor.elaps_sum = 1;
            }
            if (perf_monitor.frame_cnt == 0)
            {
                fps = fps_limit;
            }
            else
            {
                fps = (1000 * perf_monitor.frame_cnt) / perf_monitor.elaps_sum;
            }
            perf_monitor.elaps_sum = 0;
            perf_monitor.frame_cnt = 0;
            if (fps > fps_limit)
            {
                fps = fps_limit;
            }

            perf_monitor.fps_sum_all += fps;
            perf_monitor.fps_sum_cnt++;
            uint32_t cpu = 100 - lv_timer_get_idle();
            lv_label_set_text_fmt(perf_label, "%" LV_PRIu32 " FPS\n%" LV_PRIu32 "%% CPU", fps, cpu);
        }
    }
```

Finally, add the hidden flag:

```cpp
#if LV_USE_PERF_MONITOR && LV_USE_LABEL
    lv_obj_t *perf_label = perf_monitor.perf_label;
    if (perf_label == NULL)
    {
        perf_label = lv_label_create(lv_layer_sys());
        lv_obj_set_style_bg_opa(perf_label, LV_OPA_50, 0);
        lv_obj_set_style_bg_color(perf_label, lv_color_black(), 0);
        lv_obj_set_style_text_color(perf_label, lv_color_white(), 0);
        lv_obj_set_style_pad_top(perf_label, 3, 0);
        lv_obj_set_style_pad_bottom(perf_label, 3, 0);
        lv_obj_set_style_pad_left(perf_label, 3, 0);
        lv_obj_set_style_pad_right(perf_label, 3, 0);
        lv_obj_set_style_text_align(perf_label, LV_TEXT_ALIGN_RIGHT, 0);
        lv_label_set_text(perf_label, "?");
        lv_obj_align(perf_label, LV_USE_PERF_MONITOR_POS, 0, 0);
        lv_obj_add_flag(perf_label, LV_OBJ_FLAG_HIDDEN);
        perf_monitor.perf_label = perf_label;
    }
```

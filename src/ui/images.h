#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_background_1;
extern const lv_img_dsc_t img_background_2;
extern const lv_img_dsc_t img_terra;
extern const lv_img_dsc_t img_terra2;
extern const lv_img_dsc_t img_11;
extern const lv_img_dsc_t img_12;
extern const lv_img_dsc_t img_13;
extern const lv_img_dsc_t img_14;
extern const lv_img_dsc_t img_15;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[9];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/
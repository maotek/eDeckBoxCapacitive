
#ifndef SD_FS_H
#define SD_FS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Initializes the SD card filesystem for LVGL as drive letter 'S'
     *
     * This registers the SD card with LVGL's filesystem driver so you can access files via "S:/filename.ext".
     * Requires that SD.begin(...) was called before this function.
     */
    void my_sd_fs_init(void);

    extern uint32_t sd_open_ct;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // SD_FS_H

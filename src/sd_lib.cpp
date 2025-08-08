#include <lvgl.h>
#include <SD.h>
#include "sd_lib.h"

static File file;

uint32_t sd_open_ct = 0;

static void *sd_open_cb(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode)
{
    char full_path[64];
    snprintf(full_path, sizeof(full_path), "/%s", path);

    if (mode == LV_FS_MODE_WR)
    {
        file = SD.open(full_path, FILE_WRITE);
    }
    else
    {
        file = SD.open(full_path, FILE_READ);
    }

    ++sd_open_ct;

    if (!file)
        return nullptr;
    return &file;
}

static lv_fs_res_t sd_close_cb(lv_fs_drv_t *drv, void *file_p)
{
    ((File *)file_p)->close();
    return LV_FS_RES_OK;
}

static lv_fs_res_t sd_read_cb(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br)
{
    *br = ((File *)file_p)->read((uint8_t *)buf, btr);
    return LV_FS_RES_OK;
}

static lv_fs_res_t sd_seek_cb(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence)
{
    File *f = (File *)file_p;
    if (whence == LV_FS_SEEK_SET)
        f->seek(pos, SeekSet);
    else if (whence == LV_FS_SEEK_CUR)
        f->seek(f->position() + pos, SeekSet);
    else if (whence == LV_FS_SEEK_END)
        f->seek(f->size() - pos, SeekSet);
    return LV_FS_RES_OK;
}

static lv_fs_res_t sd_tell_cb(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p)
{
    *pos_p = ((File *)file_p)->position();
    return LV_FS_RES_OK;
}

void my_sd_fs_init()
{
    static lv_fs_drv_t drv;
    lv_fs_drv_init(&drv);
    drv.letter = 'S';
    drv.open_cb = sd_open_cb;
    drv.close_cb = sd_close_cb;
    drv.read_cb = sd_read_cb;
    drv.seek_cb = sd_seek_cb;
    drv.tell_cb = sd_tell_cb;
    lv_fs_drv_register(&drv);
}
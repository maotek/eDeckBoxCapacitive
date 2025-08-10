#include "Arduino.h"
#include <lvgl.h>
#include <TFT_eSPI.h>

#include "ui/ui.h"
#include "CST820.h"

#include "esp_heap_caps.h"

#include "state_manager.h"
#include "ui/styles.h"
#include "ui/images.h"

#include "player.h"

#define BTN_WIDTH(n) ((lv_btnmatrix_ctrl_t)((n) & 0x0F))

#include "layout.h"

#include <SD.h>
#include "sd_lib.h"

SPIClass hspi(HSPI);

#define BUFFER_LINES 160
#define TFT_HOR_RES 240
#define TFT_VER_RES 320

/* --- custom map: digits + letters + backspace + OK --- */
static const char *kb_map_user1[] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "\n",
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "\n",
    "a", "s", "d", "f", "g", "h", "j", "k", "l", "\n",
    "z", "x", "c", "v", "b", "n", "m", LV_SYMBOL_BACKSPACE, "\n",
    " ", LV_SYMBOL_OK, "" /* must end with empty string */
};

/* Optional: widen Backspace, make OK full width. Omit if you don’t care. */
static const lv_btnmatrix_ctrl_t kb_ctrl_user1[] = {
    /* row1: 10 keys */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* row2: 10 keys */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* row3:  9 keys */ 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* row4:  7 letters + backspace wider */ 0, 0, 0, 0, 0, 0, 0, BTN_WIDTH(2),
    /* row5:  OK full row (15 units typical) */ 0, 0};

/* Custom keyboard listener callback */
static void my_keyboard_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *kb = lv_event_get_target(e);

  if (code == LV_EVENT_VALUE_CHANGED)
  {
    uint16_t btn_id = lv_btnmatrix_get_selected_btn(kb);
    const char *txt = lv_btnmatrix_get_btn_text(kb, btn_id);

    if (txt && strcmp(txt, LV_SYMBOL_OK) == 0)
    {
      // Store name in global state
      player_set_nickname(current_player_idx, lv_textarea_get_text(objects.my_textarea));
      // Adjust name
      lv_label_set_text(objects.single_lifecount_opponent_namelabel, g_players[current_player_idx].nickname);
      lv_textarea_set_text(objects.my_textarea, "");
      lv_label_set_text_fmt(cmd_btn_label[current_player_idx],
                            "%s\nDealt: %d\nTaken: %d",
                            g_players[current_player_idx].nickname,
                            g_players[current_player_idx].dmg_dealt,
                            g_players[current_player_idx].dmg_taken);
      loadScreen(SCREEN_ID_SINGLE_LIFECOUNT_OPPONENT_ADJUST_COUNT);
    }
  }
}

/* END Custom keyboard listener callback */

void init_my_keyboard_listener(void)
{
  lv_obj_add_event_cb(objects.my_keyboard, my_keyboard_event_cb, LV_EVENT_ALL, NULL);
}

#define I2C_SDA 33
#define I2C_SCL 32
#define TP_RST 25
#define TP_INT 21
CST820 touch(I2C_SDA, I2C_SCL, TP_RST, TP_INT);

TFT_eSPI tft = TFT_eSPI();

static lv_color_t draw_buf[TFT_HOR_RES * BUFFER_LINES];

// #define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 8 * (LV_COLOR_DEPTH / 8))

// uint32_t *draw_buf = nullptr;
// uint32_t *draw_buf2 = nullptr;

lv_disp_draw_buf_t draw_buf_struct;
lv_disp_drv_t disp_drv;
lv_indev_drv_t indev_drv;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  int32_t w = lv_area_get_width(area);
  int32_t h = lv_area_get_height(area);

  tft.startWrite();
  // tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushImageDMA(area->x1, area->y1, w, h, (uint16_t *)color_p);
  // tft.pushPixels((uint16_t *)color_p, w * h); // ← blocking
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
  bool touched;
  uint8_t gesture;
  uint16_t touchX, touchY;

  touched = touch.getTouch(&touchX, &touchY, &gesture);

  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;

    /*Set the coordinates*/
    data->point.x = 240 - 1 - touchX;
    ;
    data->point.y = 320 - 10 - touchY;
  }
}

void print_heap()
{
  size_t free8 = heap_caps_get_free_size(MALLOC_CAP_8BIT);
  size_t larg8 = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
  size_t free32 = heap_caps_get_free_size(MALLOC_CAP_32BIT);
  Serial.printf("Free8=%u, Largest8=%u, Free32=%u\n", (unsigned)free8, (unsigned)larg8, (unsigned)free32);
}

const int VOLTAGE_PIN = 35;

// Resistor values in ohms
const float R1 = 5100.0;
const float R2 = 10000.0;

char voltageBuf[16];

void setup()
{
  pinMode(27, OUTPUT);
  digitalWrite(27, brightness_get(125));
  tft.fillScreen(TFT_BLACK);

  // Show "Loading..."
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM); // Middle Center
  tft.drawString("Loading...", tft.width() / 2, tft.height() / 2);

  Serial.begin(115200);

  // START MAIN
  lv_init();

  lv_log_register_print_cb([](const char *buf)
                           { Serial.println(buf); print_heap(); Serial.println(sd_open_ct); });

  hspi.begin(18, 19, 23); // CLK, MISO, MOSI for HSPI

  if (!SD.begin(5, hspi))
  {
    Serial.println("SD init failed");
  }
  else
  {
    Serial.println("SD initialized");
    my_sd_fs_init();
  }

  touch.begin();

  tft.begin();
  tft.initDMA();
  tft.setRotation(2);
  

  pinMode(17, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  digitalWrite(17, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(4, HIGH);

  // draw_buf = (uint32_t *)heap_caps_malloc(sizeof(lv_color_t) * TFT_HOR_RES * BUFFER_LINES, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
  // draw_buf2 = (uint32_t *)heap_caps_malloc(sizeof(lv_color_t) * TFT_HOR_RES * BUFFER_LINES, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);

  // if (!draw_buf || !draw_buf2)
  // {
  //   Serial.println("Failed to allocate LVGL draw buffers!");
  //   while (true)
  //     ;
  // }

  // LVGL draw buffer setup
  lv_disp_draw_buf_init(&draw_buf_struct, draw_buf, nullptr, TFT_HOR_RES * BUFFER_LINES);

  // LVGL display driver setup
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = TFT_HOR_RES;
  disp_drv.ver_res = TFT_VER_RES;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf_struct;
  lv_disp_drv_register(&disp_drv);

  // LVGL touch input setup
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // UI init
  ui_init();

  // Set initial value for brightness slider
  lv_slider_set_value(objects.brightness_slider, brightness_get(125), LV_ANIM_OFF);

  // Set EEPROM background
  lv_style_t *style = get_style_main_background_MAIN_DEFAULT();
  uint16_t bg_idx = bg_get_index(0);
  lv_style_set_bg_img_src(style, images[bg_idx].img_dsc);

  // Initialize default layout
  single_lifecount_edh_layout_init();

  // Turn on screen
  analogWrite(27, brightness_get(125));

  Serial.println("Setup complete.");

  /* LINK KEYBOARD */
  lv_obj_t *kb = objects.my_keyboard; /* replace with your keyboard obj */
  lv_obj_t *ta = objects.my_textarea; /* the target textarea */

  lv_keyboard_set_textarea(kb, ta);

  /* Optional: enforce allowed chars at the textarea level */
  lv_textarea_set_accepted_chars(ta, "0123456789 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

  /* Install map into User1 and activate it */
  lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_USER_1, kb_map_user1, kb_ctrl_user1);
  lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_USER_1);

  init_my_keyboard_listener();

  print_heap();
}

static uint32_t prevTime = 0;
void loop()
{
  lv_timer_handler();
  delay(1);

  if (millis() - prevTime > 1000)
  {
    int adcValue = analogRead(VOLTAGE_PIN); // 0–4095 range on ESP32
    float vOut = adcValue * (3.3 / 4095.0); // ESP32 ADC reference is ~3.3V
    // Scale back to the original voltage before the divider
    float vIn = vOut * ((R1 + R2) / R2);
    char voltageBuf[16];
    snprintf(voltageBuf, sizeof(voltageBuf), "%.2f V", vIn);
    lv_label_set_text(objects.voltage, voltageBuf);

    prevTime = millis();
  }
}

#include "Arduino.h"
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "ui/ui.h"
#include "CST820.h"
#include "esp_heap_caps.h"
#include "preference_manager.h"
#include "ui/styles.h"
#include "ui/images.h"
#include "player.h"
#include "layout.h"
#include "keyboard.h"

// SPIClass hspi(HSPI);

#define BUFFER_LINES 160
#define TFT_HOR_RES 240
#define TFT_VER_RES 320

// ADC READING -----------------------------
#include "driver/adc.h"
#include "esp_adc_cal.h"

#define VOLTAGE_PIN 35
#define ADC_CHANNEL ADC1_CHANNEL_7 // GPIO35
#define ADC_WIDTH_CFG ADC_WIDTH_BIT_12
#define ADC_ATTEN_CFG ADC_ATTEN_DB_11 // ~0–3.3V range on ESP32

#define V_MIN 3.0f       // empty voltage
#define V_FULL 4.13f     // treat as full starting at 4.13 V
#define V_CHARGING 4.16f // treat as charging starting at 4.16 V

static esp_adc_cal_characteristics_t adc_chars;

// Call this once, e.g., in setup()
void init_adc_cal()
{
  adc1_config_width(ADC_WIDTH_CFG);
  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_CFG);
  // Use eFuse values if present; fall back to 1100 mV
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_CFG, ADC_WIDTH_CFG,
                           1100 /*mV nominal*/, &adc_chars);
}
// ADC READING -----------------------------

#define I2C_SDA 33
#define I2C_SCL 32
#define TP_RST 25
#define TP_INT 21
CST820 touch(I2C_SDA, I2C_SCL, TP_RST, TP_INT);

TFT_eSPI tft = TFT_eSPI();

static lv_color_t draw_buf[TFT_HOR_RES * BUFFER_LINES];

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

// Resistor values in ohms
const float R1 = 33000.0;
const float R2 = 100000.0;

char voltageBuf[16];

void setup()
{
  pinMode(27, OUTPUT);
  digitalWrite(27, LOW);
  tft.begin();
  tft.initDMA();
  tft.setRotation(2);

  // Show "Loading..."
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM); // Middle Center
  tft.drawString("Loading...", tft.width() / 2, tft.height() / 2);
  analogWrite(27, brightness_get(100));

  init_adc_cal();

  Serial.begin(115200);

  // START MAIN
  lv_init();

  touch.begin();

  pinMode(17, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  digitalWrite(17, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(4, HIGH);

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

  // Move voltage readout to top
  lv_obj_set_parent(objects.voltage, lv_layer_top());

  // Set initial value for brightness slider
  lv_slider_set_value(objects.brightness_slider, brightness_get(125), LV_ANIM_OFF);

  // Set EEPROM background
  lv_style_t *style = get_style_main_background_MAIN_DEFAULT();
  uint16_t bg_idx = bg_get_index(0);
  lv_style_set_bg_img_src(style, images[bg_idx].img_dsc);

  // Initialize default layout
  layout_init();

  Serial.println("Setup complete.");

  keyboard_init(objects.my_keyboard, objects.my_textarea);
}

void loop()
{
  lv_timer_handler();
  delay(1);

  static uint32_t acc = 0;
  static uint16_t sampleCount = 0;
  static uint32_t lastSample = 0;
  static uint32_t lastUpdate = 0;

  static float lowestPercent = 100.0f; // start at 100%

  // take one sample about every 33 ms
  if (millis() - lastSample >= 33)
  {
    int raw = adc1_get_raw(ADC_CHANNEL); // 0..4095
    acc += (uint32_t)raw;
    sampleCount++;
    lastSample = millis();
  }

  // update display about once per second
  if ((millis() - lastUpdate) >= 1000 && sampleCount > 0)
  {
    // Average as before
    uint16_t adcRaw = acc / sampleCount;
    acc = 0;
    sampleCount = 0;

    // Convert averaged raw code to millivolts
    uint32_t mv = esp_adc_cal_raw_to_voltage(adcRaw, &adc_chars);
    float vOutInstant = mv / 1000.0f; // voltage at GPIO35

    // Apply divider
    vOutInstant = vOutInstant * ((R1 + R2) / R2); // R1 top, R2 bottom

    // --- Determine state ---
    float percent = 0;
    bool charging = false;

    if (vOutInstant >= V_CHARGING)
    {
      // 4.16 V or above → charging
      percent = 100.0f;
      charging = true;
    }
    else if (vOutInstant >= V_FULL)
    {
      // Between 4.13 and 4.16 → full
      percent = 100.0f;
    }
    else
    {
      // Below 4.13 → scale between V_MIN and V_FULL
      percent = (vOutInstant - V_MIN) / (V_FULL - V_MIN) * 100.0f;
      if (percent < 0)
        percent = 0;
      if (percent > 100)
        percent = 100;
    }

    // if (percent < lowestPercent)
    {
      lowestPercent = percent; // update when new lower value found
    }

    // --- Format label ---
    char buf[32];
    if (charging)
    {
      snprintf(buf, sizeof(buf), "CHG", lowestPercent);
    }
    else if (percent == 100.0f)
    {
      snprintf(buf, sizeof(buf), "%.0f%%", lowestPercent);
    }
    else
    {
      snprintf(buf, sizeof(buf), "%.0f%%", lowestPercent);
    }
    lv_label_set_text(objects.voltage, buf);

    // --- Color ---
    if (charging)
    {
      lv_obj_set_style_text_color(objects.voltage,
                                  lv_color_hex(0x00FF00), 0);
    }
    else if (percent < 20.0f)
    {
      lv_obj_set_style_text_color(objects.voltage,
                                  lv_color_hex(0xFF0000), 0);
    }
    else
    {
      lv_obj_set_style_text_color(objects.voltage,
                                  lv_color_hex(0xFFFFFF), 0);
    }

    lastUpdate = millis();
  }
}

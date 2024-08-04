#pragma once

#include "esp32-hal.h"

/**
 * WS2812 RGB LED control using ESP32 Remote Control Transceiver (RMT)
 * https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/rmt.html
 */
class RgbLed
{
public:
    RgbLed(size_t ledCount);
    bool init(int pin);

    void setColor(uint32_t rgb, bool includeReset = true);
    void setColors(uint32_t *ledColors, size_t maxlen);

private:
    bool _initialized;
    rmt_obj_t *_rmtObj;
    size_t _ledCount;
};
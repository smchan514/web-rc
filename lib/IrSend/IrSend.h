#pragma once

#include "esp32-hal.h"

/**
 * IR LED control using ESP32 Remote Control Transceiver (RMT)
 * https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/rmt.html
 */
class IrSend
{
public:
    IrSend(bool debugEnabled = false);
    bool init(int pin);

    /**
     * Send 22-bit IR code using "Panasonic Old" mark/space settings at 57kHz carrier
     */
    void sendPanasonicOld(uint32_t irCode);

    /**
     * Send 12-bit IR code using Sony mark/space settings at 40kHz carrier
     * Header: 2660us / 300us
     * One   : 1500us / 300us
     * Zero  :  870us / 300us
     * No stop bit
     * Frame extent: 45000us
     * Repeat three times
     */
    void sendSony(uint32_t irCode);

private:
    bool _initialized;
    bool _debugEnabled;
    rmt_obj_t *_rmtObj;
    int _currentCarrier;

    void setCarrier(int kHz);
};
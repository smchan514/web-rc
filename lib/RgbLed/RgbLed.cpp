#include "RgbLed.h"

#include <algorithm>
#include <Arduino.h>

// https://cdn-shop.adafruit.com/datasheets/WS2812.pdf
#define WS2812_T0H_NS (350)
#define WS2812_T0L_NS (800)
#define WS2812_T1H_NS (700)
#define WS2812_T1L_NS (600)
#define WS2812_RST_NS (55)

#define TICK_NS (12.5)

#define T0H_TICKS ((uint32_t)(WS2812_T0H_NS / TICK_NS))
#define T0L_TICKS ((uint32_t)(WS2812_T0L_NS / TICK_NS))
#define T1H_TICKS ((uint32_t)(WS2812_T1H_NS / TICK_NS))
#define T1L_TICKS ((uint32_t)(WS2812_T1L_NS / TICK_NS))
#define RST_TICKS ((uint32_t)(WS2812_RST_NS / TICK_NS))

RgbLed::RgbLed(size_t ledCount) : _ledCount(ledCount)
{
    // ...
}

bool RgbLed::init(int pin)
{
    Serial.printf("[RgbLed::init] pin=%d\n", pin);

    if ((_rmtObj = rmtInit(pin, RMT_TX_MODE, RMT_MEM_64)) == NULL)
    {
        Serial.println("[RgbLed::init] rmtInit failed");
        return false;
    }

    float realTick = rmtSetTick(_rmtObj, TICK_NS);
    Serial.printf("[RgbLed::init] real tick set to: %fns\n", realTick);

    _initialized = true;
    return true;
}

static inline int insertRmtData(rmt_data_t *data, int dataIndex, uint32_t dur0, uint32_t level0, uint32_t dur1, uint32_t level1)
{
    data[dataIndex].duration0 = dur0;
    data[dataIndex].level0 = level0;
    data[dataIndex].duration1 = dur1;
    data[dataIndex].level1 = level1;
    return dataIndex + 1;
}

static inline uint32_t insert8bits(rmt_data_t *data, int dataIndex, uint32_t rgb, uint32_t mask)
{
    for (int i = 0; i < 8; i++)
    {
        if ((rgb & mask) != 0)
        {
            dataIndex = insertRmtData(data, dataIndex, T1H_TICKS, 1, T1L_TICKS, 0);
        }
        else
        {
            dataIndex = insertRmtData(data, dataIndex, T0H_TICKS, 1, T0L_TICKS, 0);
        }

        mask >>= 1;
    }
    return dataIndex;
}

void RgbLed::setColor(uint32_t rgb, bool includeReset)
{
    // 24 bits (GRB) + optional RET code
    rmt_data_t data[25];
    int dataIndex = 0;

    // G
    dataIndex = insert8bits(data, dataIndex, rgb, 0x8000);

    // R
    dataIndex = insert8bits(data, dataIndex, rgb, 0x800000);

    // B
    dataIndex = insert8bits(data, dataIndex, rgb, 0x80);

    if (includeReset)
    {
        dataIndex = insertRmtData(data, dataIndex, RST_TICKS, 0, 0, 0);
    }

    // Write out bit sequence for this LED
    rmtWriteBlocking(_rmtObj, data, dataIndex);
}

void RgbLed::setColors(uint32_t *ledColors, size_t maxlen)
{
    size_t len = std::min(maxlen, _ledCount);
    for (size_t i = 0; i < len; i++)
    {
        // Include RESET in the last color sequence
        setColor(ledColors[i], i == (len - 1));
    }
}
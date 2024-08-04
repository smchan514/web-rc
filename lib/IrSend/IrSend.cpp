#include "IrSend.h"

#include <Arduino.h>

IrSend::IrSend(bool debugEnabled) : _debugEnabled(debugEnabled), _initialized(false), _rmtObj(NULL), _currentCarrier(0)
{
    // ...
}

bool IrSend::init(int pin)
{
    Serial.printf("[IrSend::init] pin=%d\n", pin);

    if ((_rmtObj = rmtInit(pin, RMT_TX_MODE, RMT_MEM_64)) == NULL)
    {
        Serial.println("[IrSend::init] rmtInit failed");
        return false;
    }

    float realTick = rmtSetTick(_rmtObj, 1000);
    Serial.printf("[IrSend::init] real tick set to: %fns\n", realTick);

    _initialized = true;
    return true;
}

// https://docs.espressif.com/projects/esp-idf/en/v4.2-beta1/esp32/api-reference/peripherals/rmt.html
void IrSend::setCarrier(int kHz)
{
    // Skip if carrier already set to the specified frequency
    if(kHz == _currentCarrier)
    {
        return;
    }

    uint32_t period = 80000 / kHz;
    uint32_t h0 = period >> 1;
    uint32_t h1 = period - h0;

    Serial.printf("[IrSend::setCarrier] kHz=%d, h0=%d, h1=%d\n", kHz, h0, h1);
    if (!rmtSetCarrier(_rmtObj, true, true, h0, h1))
    {
        Serial.println("[IrSend::setCarrier] rmtSetCarrier failed");
        return;
    }

    // Remember current carrier frequency when successful
    _currentCarrier = kHz;
}

static inline int insertRmtData(rmt_data_t *data, int dataIndex, uint32_t dur0, uint32_t level0, uint32_t dur1, uint32_t level1)
{
    data[dataIndex].duration0 = dur0;
    data[dataIndex].level0 = level0;
    data[dataIndex].duration1 = dur1;
    data[dataIndex].level1 = level1;
    return dataIndex + 1;
}

void IrSend::sendPanasonicOld(uint32_t irCode)
{
    if (!_initialized)
    {
        Serial.println("[IrSend::sendPanasonicOld] Uninitialized");
        return;
    }

    setCarrier(57);

    Serial.printf("[IrSend::sendPanasonicOld] irCode=0x%x\n", irCode);

    rmt_data_t data[22 + 2];
    int dataIndex = 0;

    // HEAD
    dataIndex = insertRmtData(data, dataIndex, 833 * 4, 1, 833 * 4, 0);

    int bit = 1 << 21;
    for (int i = 0; i < 22; i++)
    {
        if ((irCode & bit) != 0)
        {
            // ONE
            dataIndex = insertRmtData(data, dataIndex, 833, 1, 833 * 3, 0);
        }
        else
        {
            // ZERO
            dataIndex = insertRmtData(data, dataIndex, 833, 1, 833, 0);
        }

        bit >>= 1;
    }

    // ONE (stop bit?)
    dataIndex = insertRmtData(data, dataIndex, 833, 1, 833 * 3, 0);

    // GAP
    dataIndex = insertRmtData(data, dataIndex, 120000, 0, 0, 0);

    if (_debugEnabled)
    {
        for (int z = 0; z < dataIndex; z++)
        {
            Serial.printf("%5d:%d %5d:%d\n", data[z].duration0, data[z].level0, data[z].duration1, data[z].level1);
        }
    }

    rmtWriteBlocking(_rmtObj, data, dataIndex);
}

void IrSend::sendSony(uint32_t irCode)
{
    if (!_initialized)
    {
        Serial.println("[IrSend::sendPanasonicOld] Uninitialized");
        return;
    }

    setCarrier(40);

    Serial.printf("[IrSend::sendPanasonicOld] irCode=0x%x\n", irCode);

    rmt_data_t data[22 + 2];
    int dataIndex = 0;
    uint32_t extent = 45000;

    // HEAD
    dataIndex = insertRmtData(data, dataIndex, 2660, 1, 300, 0);
    extent -= 2660;
    extent -= 300;

    int bit = 1 << 11;
    for (int i = 0; i < 12; i++)
    {
        if ((irCode & bit) != 0)
        {
            // ONE
            dataIndex = insertRmtData(data, dataIndex, 1500, 1, 300, 0);
            extent -= 1500;
            extent -= 300;
        }
        else
        {
            // ZERO
            dataIndex = insertRmtData(data, dataIndex, 870, 1, 300, 0);
            extent -= 870;
            extent -= 300;
        }

        bit >>= 1;
    }

    // GAP
    dataIndex = insertRmtData(data, dataIndex, extent, 0, 0, 0);

    if (_debugEnabled)
    {
        for (int z = 0; z < dataIndex; z++)
        {
            Serial.printf("%5d:%d %5d:%d\n", data[z].duration0, data[z].level0, data[z].duration1, data[z].level1);
        }
    }

    // Write three times
    rmtWriteBlocking(_rmtObj, data, dataIndex);
    rmtWriteBlocking(_rmtObj, data, dataIndex);
    rmtWriteBlocking(_rmtObj, data, dataIndex);
}
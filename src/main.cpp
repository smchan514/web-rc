#include <Arduino.h>

#include <WiFi.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <WebServer.h>

#include <IrSend.h>
#include <RgbLed.h>
#include <WebContent.h>

#define IR_LED_PIN 4
#define RGB_LED_PIN 18

// Device-specific config loaded from SPIFFS (flash)
static String _wifiSsid;
static String _wifiPass;

// Runtime variables
static IrSend _irSend;
static RgbLed _rgbLed(1);
// static RgbLed _rgbLed2(15);
static WebServer _webServer(80);
unsigned long _lastActivity;

//////////////////////////////////////////////////////////////////////////////

static void loadConfig(const char *filePath)
{
    Serial.printf("[loadConfig] Loading WiFi config from %s ...\n", filePath);
    File file = SPIFFS.open(filePath, "r");
    if (!file)
    {
        Serial.println("[loadConfig] Failed to open file for reading");
        return;
    }

    char buf[256];
    file.readBytes(buf, sizeof(buf));
    file.close();

    StaticJsonDocument<256> jsonDoc;
    deserializeJson(jsonDoc, buf);
    _wifiSsid = jsonDoc["wifiSsid"].as<String>();
    _wifiPass = jsonDoc["wifiPass"].as<String>();

    Serial.printf("[loadConfig] _wifiSsid=%s\n", _wifiSsid.c_str());
}

static void loadFiles()
{
    if (!SPIFFS.begin())
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    loadConfig("/config.json");
}

static void startWifi()
{
    WiFi.begin(_wifiSsid.c_str(), _wifiPass.c_str());

    const uint32_t rgbPattern[] = {0x070000, 0x100000, 0x170000, 0x200000, 0x270000, 0x300000, 0x270000, 0x200000, 0x170000, 0x100000, 0x070000, 0x000000, };
    int rgbIndex = 0;
    Serial.print("[startWifi] Checking WiFi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        _rgbLed.setColor(rgbPattern[rgbIndex]);
        rgbIndex = (rgbIndex + 1) % (sizeof(rgbPattern) / sizeof(uint32_t));
        delay(30);
    }

    Serial.println(" WiFi connected!");
}

uint32_t parseIrCode(String &strIrCode)
{
    uint32_t irCode;
    if (strIrCode[0] == '#')
    {
        // Hex
        irCode = strtoll(strIrCode.c_str() + 1, NULL, 16);
    }
    else
    {
        // Decimal
        irCode = strIrCode.toInt();
    }

    return irCode;
}

static void signalActivity()
{
    _rgbLed.setColor(0x10);
    _lastActivity = millis();
}

static void handleSendPanasonicOld()
{
    signalActivity();
    String strIrCode = _webServer.arg("ir_code");
    Serial.printf("[handleSendPanasonicOld] ir_code='%s'\n", strIrCode.c_str());

    int index0 = 0;
    int index1 = strIrCode.indexOf(' ');

    do
    {
        String part = strIrCode.substring(index0, index1);
        uint32_t irCode = parseIrCode(part);

        // Validate input
        if (irCode == 0)
        {
            Serial.printf("[handleSendPanasonicOld] invalid irCode=%x\n", irCode);
            _webServer.send(400);
            return;
        }

        _irSend.sendPanasonicOld(irCode);

        if (index1 < 0)
        {
            // This was the last code
            break;
        }

        index0 = index1 + 1;
        index1 = strIrCode.indexOf(' ', index0);

        Serial.printf("[handleSendPanasonicOld] index0=%d, index1=%d\n", index0, index1);
    } while (index0 > 0);

    _webServer.send(200);
}

static void handleSendSony()
{
    signalActivity();
    String strIrCode = _webServer.arg("ir_code");
    Serial.printf("[handleSendSony] ir_code='%s'\n", strIrCode.c_str());

    uint32_t irCode = parseIrCode(strIrCode);

    // Validate input
    if (irCode == 0)
    {
        Serial.printf("[handleSendPanasonicOld] invalid irCode=%x\n", irCode);
        _webServer.send(400);
        return;
    }

    _irSend.sendSony(irCode);
    _webServer.send(200);
}

static void sendIndexHtml()
{
    signalActivity();
    _webServer.send(200, "text/html", WEB_CONTENT_INDEX_HTML);
}

static void sendMyStyleCss()
{
    signalActivity();
    _webServer.send(200, "text/css", WEB_CONTENT_MYSTYLE_CSS);
}

void setupWebServer()
{
    Serial.println("[setupWebServer]");
    _webServer.on("/", sendIndexHtml);
    _webServer.on("/mystyle.css", sendMyStyleCss);
    _webServer.on("/send_panasonic_old", HTTP_POST, handleSendPanasonicOld);
    _webServer.on("/send_sony", HTTP_POST, handleSendSony);
    _webServer.begin();
}

// uint32_t colors[] = { 0x100000, 0x100000, 0x100000, 0x100000, 0x1000, 0x1000, 0x1000, 0x1000, 0x10, 0x10, 0x10, 0x10, 0x101010, 0x101010, 0x101010, 0x101010, 0x800000, 0x100000, 0x100000, 0x100000, 0x1000, 0x1000, 0x1000, 0x1000, 0x10, 0x10, 0x10, 0x10, 0x101010, 0x101010, 0x101010, 0x101010};
// int offset = 0;

void setup()
{
    Serial.begin(115200);
    _rgbLed.init(RGB_LED_PIN);
    _rgbLed.setColor(0x100000);

    // _rgbLed2.init(17);
    // _rgbLed2.setColors(colors, sizeof(colors) / sizeof(uint32_t));

    loadFiles();
    startWifi();

    setupWebServer();
    _irSend.init(IR_LED_PIN);

    // Show green light for 2 seconds to signal end of setup
    _rgbLed.setColor(0x001000);
    delay(2000);
    _rgbLed.setColor(0);
}

void loop()
{
    _webServer.handleClient();

    if(millis() - _lastActivity > 1000)
    {
        _rgbLed.setColor(0);
    }

    delay(100);

    // _rgbLed2.setColors(colors + offset, sizeof(colors) / sizeof(uint32_t));
    // offset = (offset + 1)%15;
}
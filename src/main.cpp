#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include "ota.h"
#include "webcontrol.h"
#include "ledcontrol.h"

const char *ssid = "XXXX";
const char *password = "XXXX";

OTA *ota = NULL;
WebControl *webControl = NULL;
LEDControl *ledControl = NULL;

void setup()
{
  Serial.begin(115200);
  delay(3000); // sanity delay

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  ota = new OTA("fire_lamp");
  ledControl = new LEDControl();
  webControl = new WebControl(ledControl);
}

void loop()
{
  ledControl->loop();
  ota->loop();
}

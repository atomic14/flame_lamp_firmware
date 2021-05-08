#include <FS.h>
#include "SPIFFS.h"
#include "ledcontrol.h"
#include "webcontrol.h"
#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include <ArduinoJson.h>

AsyncWebServer server(80);

WebControl::WebControl(LEDControl *_ledControl) : ledControl(_ledControl)
{
    SPIFFS.begin();

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, PUT");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

    server.addHandler(new AsyncCallbackJsonWebHandler("/hue", [this](AsyncWebServerRequest *request, JsonVariant &json) {
        const JsonObject &jsonObj = json.as<JsonObject>();
        this->ledControl->setHueRange(jsonObj["start"], jsonObj["end"]);
        request->send(200, "OK");
    }));

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.onNotFound([](AsyncWebServerRequest *request) {
        if (request->method() == HTTP_OPTIONS)
        {
            request->send(200);
        }
        else
        {
            request->send(404);
        }
    });
    server.begin();
}

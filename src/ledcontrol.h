#include <FastLED.h>

#define PALETTE_SIZE 256
#define NUM_LEDS 299

class LEDControl
{
    float **cells1;
    float **cells2;

    CRGB leds[NUM_LEDS];
    CHSV palette[PALETTE_SIZE];

public:
    LEDControl();
    void loop();
    void setHueRange(int start, int end);
};
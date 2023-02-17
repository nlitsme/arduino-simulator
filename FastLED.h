#pragma once

#include <stdio.h>
#include <array>

#define RGB 0
#define WS2812 0

struct CRGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    CRGB(uint32_t num)
        : r(num), g(num>>8), b(num>>16)
    {
    }
    CRGB(uint8_t r, uint8_t g, uint8_t b)
        : r(r), g(g), b(b)
    {
    }
	inline CRGB(const CRGB& rhs) = default;
	inline CRGB() = default;

    int ansi() const { return ((r&1)<<3) | ((g&3)<<1) | ((b&1)); }

    void setHSV(int h, int s, int v) { r = h; g = s; b = v; }
    enum {
        BlueViolet=0x8A2BE2,
        WhiteSmoke=0xF5F5F5,
    };
};
CRGB CHSV(int a, int b, int c)
{
    // faking it
    return CRGB(a, b, c);
}


int fgcode[16] = { 30,31,32,33,34,35,36,37,90,91,92,93,94,95,96,97 };
int bgcode[16] = { 40,41,42,43,44,45,46,47,100,101,102,103,104,105,106,107 };

class FastLED_class {
    CRGB *leds;
    int num;
public:
    template<int type, int pin, int mode> 
    void addLeds(CRGB *leds, int num)
    {
        printf("got leds %p, %d\n", leds, num);
        this->leds = leds;
        this->num = num;
    }
    void setBrightness(int x) { }
    void show()
    {
        for (int i=0 ; i<num ; i++)
            printled(leds[i]);
        printf("\r");
    }
    void printled(const CRGB led)
    {
        int c = led.ansi();
        printf("\x1b[%d;%dm%x", fgcode[c], bgcode[c], c);
    }
};

FastLED_class FastLED;
#define LEDS FastLED

template<size_t N>
using CRGBArray = std::array<CRGB, N>;

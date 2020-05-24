#include <stdio.h>

#define RGB 0
#define WS2812 0

typedef uint32_t CRGB;

CRGB CHSV(int a, int b, int c)
{
    return (a<<16) | (b<<8) | c;
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
        int c = (led>>20)&15;
        printf("\x1b[%d;%dm%x", fgcode[c], bgcode[c], c);
    }
};

FastLED_class FastLED;
#define LEDS FastLED


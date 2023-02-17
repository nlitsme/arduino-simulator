#pragma once
/*
 *
 *
 */
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#include <stdlib.h>
#include <string.h>

#include "arduino-io.h"

#define F_CPU 16000000

struct __FlashStringHelper {
};

#define BIN  2
#define OCT  8
#define HEX  16
#define DEC  10
class Print {
public:
    void printbin(unsigned int num)
    {
        char buf[36];
        char *p = buf+36;
        *--p = 0;
        if (num==0)
            *--p = '0';
        while (num) {
            *--p = '0' + (num&1);
            num >>= 1;
        }
        printf("%s", p);
    }
    void print(char c) { printf("%c", c); }
    void println(char c) { printf("%c\n", c); }
    void println() { printf("\n"); }
    void println(const __FlashStringHelper *) { printf("...\n"); }

    void print(unsigned int num, int base=DEC) {
        switch(base) {
            case 10: printf("%u", num); break;
            case 16: printf("%x", num); break;
            case 8: printf("%o", num); break;
            case 2: printbin(num); break;
        }
    }
    void println(unsigned int num, int base=DEC) {
        switch(base) {
            case 10: printf("%u\n", num); break;
            case 16: printf("%x\n", num); break;
            case 8: printf("%o\n", num); break;
            case 2: printbin(num); printf("\n"); break;
        }
    }

    void print(int num, int base=DEC) {
        switch(base) {
            case 10: printf("%d", num); break;
            case 16: printf("%x", num); break;
            case 8: printf("%o", num); break;
            case 2: printbin(num); break;
        }
    }
    void println(int num, int base=DEC) {
        switch(base) {
            case 10: printf("%d\n", num); break;
            case 16: printf("%x\n", num); break;
            case 8: printf("%o\n", num); break;
            case 2: printbin(num); printf("\n"); break;
        }
    }
    void print(const char *str) { printf("%s", str); }
    void println(const char *str) { printf("%s\n", str); }

    void begin(int baud) { printf("serial.begin(%d)\n", baud); }
    bool available() { return true; }
    int read() { return getchar(); }

    int write(char c) { printf("serial.write(%02x)\n", c); return 1; }
    int write(const char *str) { printf("write('%s')\n", str); return strlen(str); }
    int write(const uint8_t*str, int size) { printf("write(p, %d)\n", size); return size; }
};
struct Stream : Print {
};
struct SerialClass : Stream {
};
struct String {
    String operator=(const String& s) { return *this; }
    String operator=(const char* s) { return *this; }
    const char *c_str() const { return "x"; }
};

namespace {
void delay(int n)
{
#ifdef VERBOSE
    printf("delay(%d)\n", n);
#endif
    usleep(n*1000);
}

void yield()
{
    printf("yield\n");
}

void delayMicroseconds(int n)
{
#ifdef VERBOSE
    printf("udelay(%d)\n", n);
#endif
    usleep(1000);
}
int random(int min, int max)
{
    return min + (rand() % (max-min));
}

int random(int max)
{
    return rand() % (max);
}

unsigned long micros()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec + tv.tv_sec*uint64_t(1000000);
}


int millis()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec/1000 + tv.tv_sec*1000;
}

void noInterrupts() { printf("noirq\n"); }

#define LED_BUILTIN 13
#define SS 10

void digitalWrite(int pin, int value)
{
    printf("pin %d := %d\n", pin, value);
}
uint16_t analogRead(int pin)
{
    return 234;
}

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
void pinMode(int pin, int value)
{
    printf("mode %d := %d\n", pin, value);
}

SerialClass Serial;


//uint8_t PCICR;
//uint8_t PCIE1;
//uint8_t PCMSK1;
//uint8_t PCINT12;
//uint8_t PCINT13;
}

#define ISR(fn) void fn()
#define _BV(bit) (1 << (bit))


uint8_t sin8(uint8_t x)
{
    // todo
    return x;
}
uint8_t scale8(uint8_t x, uint8_t y)
{
    // todo
    return x;
}

#include <SPI.h>
uint8_t SPIClass::interruptMask;
uint8_t SPIClass::interruptMode;
uint8_t SPIClass::interruptSave;
void SPIClass::end() { printf("SPIClass::end\n"); }
void SPIClass::begin() { printf("SPIClass::begin\n"); }

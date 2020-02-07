#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <stdint.h>
#include <stdbool.h>

uint8_t readByte(uint16_t address);
void writeByte(uint16_t address, uint8_t data);
uint16_t readWord(uint16_t address);
bool loadROM(const char* filename);

extern uint8_t CharacterRAM[0x1800];
extern uint8_t BGMapData1[0x400];
extern uint8_t BGMapData2[0x400];
extern uint8_t OAM[0xA0];

uint8_t ROM;
uint8_t ROM0;

#endif // MEMORY_HPP
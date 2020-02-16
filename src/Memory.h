#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <stdint.h>
#include <stdbool.h>

uint8_t readByte(uint16_t address);
void writeByte(uint16_t address, uint8_t data);
uint16_t readWord(uint16_t address);
void writeWord(uint16_t address, uint16_t data);
uint8_t nextByte();
uint16_t nextWord();
bool loadROM(const char* filename);

extern uint8_t CharacterRAM[0x1800];
extern uint8_t BGMapData1[0x400];
extern uint8_t BGMapData2[0x400];
extern uint8_t OAM[0xA0];
extern bool CPUEnable;

#endif // MEMORY_HPP
#include "Bootstrap.h"
#include "Memory.h"
#include "Log.h"

uint8_t CharacterRAM[0x1800];
uint8_t BGMapData1[0x400];
uint8_t BGMapData2[0x400];
uint8_t OAM[0xA0];

uint8_t ZP[127];

uint8_t readByte(uint16_t address) {
    if (address <= 0x00FF) {
        // Restart and Interrupt Vectors
        if (BootstrapEnable)
            return BOOTSTRAP[address];
        else
            return NULL;//ROM0[address];
    }
    else if (address <= 0x014F) {
        // Cartridge Header Area
    }
    else if (address <= 0x3FFF) {
        // Cartridge ROM - Bank 0 (fixed)
        //return ROM0[address];
    }
    else if (address <= 0x7FFF) {
        // Cartridge ROM - Switchable Banks 1-xx
    }
    else if (address <= 0x97FF) {
        // Character RAM
        return CharacterRAM[address - 0x8000];
    }
    else if (address <= 0x9BFF) {
        // BG Map Data 1
    }
    else if (address <= 0x9FFF) {
        // BG Map Data 2
    }
    else if (address <= 0xBFFF) {
        // Cartridge RAM (If Available)
    }
    else if (address <= 0xCFFF) {
        // Internal RAM - Bank 0 (fixed)
    }
    else if (address <= 0xDFFF) {
        // Internal RAM - Bank 1-7 (switchable - CGB only)
    }
    else if (address <= 0xFDFF) {
        // Echo RAM - Reserved, Do Not Use
    }
    else if (address <= 0xFE9F) {
        // OAM - Object Attribute Memory
    }
    else if (address <= 0xFEFF) {
        // Unusable Memory
    }
    else if (address <= 0xFF7F) {
        // Hardware I/O Registers
    }
    else if (address <= 0xFFFE) {
        // Zero Page - 127 bytes
        return ZP[address - 0xFF80];
    }
    else if (address == 0xFFFF) {
        // Interrupt Enable Flag
    }
}

void writeByte(uint16_t address, uint8_t data) {
    if (address <= 0x00FF) {
        // Restart and Interrupt Vectors
    }
    else if (address <= 0x014F) {
        // Cartridge Header Area
    }
    else if (address <= 0x3FFF) {
        // Cartridge ROM - Bank 0 (fixed)
        //return ROM0[address];
    }
    else if (address <= 0x7FFF) {
        // Cartridge ROM - Switchable Banks 1-xx
    }
    else if (address <= 0x97FF) {
        // Character RAM
        //CharacterRAM[address - 0x8000];
    }
    else if (address <= 0x9BFF) {
        // BG Map Data 1
    }
    else if (address <= 0x9FFF) {
        // BG Map Data 2
    }
    else if (address <= 0xBFFF) {
        // Cartridge RAM (If Available)
    }
    else if (address <= 0xCFFF) {
        // Internal RAM - Bank 0 (fixed)
    }
    else if (address <= 0xDFFF) {
        // Internal RAM - Bank 1-7 (switchable - CGB only)
    }
    else if (address <= 0xFDFF) {
        // Echo RAM - Reserved, Do Not Use
    }
    else if (address <= 0xFE9F) {
        // OAM - Object Attribute Memory
    }
    else if (address <= 0xFEFF) {
        // Unusable Memory
    }
    else if (address <= 0xFF7F) {
        // Hardware I/O Registers
    }
    else if (address <= 0xFFFE) {
        // Zero Page - 127 bytes
        ZP[address - 0xFF80] = data;
    }
    else if (address == 0xFFFF) {
        // Interrupt Enable Flag
    }
}

uint16_t readWord(uint16_t address)
{
    uint16_t word = readByte(address + 1);
    word <<= 8;
    word |= readByte(address);
    return word;
}

bool loadROM(const char* filename)
{
    //// Load our file into ifstream
    //std::ifstream file(filename, std::ios::binary);

    //// Create our buffer, and stuff the file into it.
    //std::vector<uint8_t> buffer(
    //    (std::istreambuf_iterator<char>(file)),
    //    std::istreambuf_iterator<char>()
    //);

    //ROM = ROM0 = buffer.data();

    //// Close the file
    //file.close();

    //LogVerbose("read %zu bytes", buffer.size());

    //if (bytesRead < size) {
    //    LogError("failed to load %s", filename);
    //    return false;
    //}

    return true;
}
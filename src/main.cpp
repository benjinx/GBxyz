#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include "Log.hpp"
#include "Registers.hpp"

uint8_t BOOTSTRAP[0x100] = {
    0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32,
    0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
    0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3,
    0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
    0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A,
    0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
    0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06,
    0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
    0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99,
    0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
    0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64,
    0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
    0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90,
    0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
    0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62,
    0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
    0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42,
    0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
    0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04,
    0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
    0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9,
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
    0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
    0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
    0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
    0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
    0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13,
    0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
    0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20,
    0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50,
};

uint8_t readByte(uint16_t address) {
    if (address <= 0x00FF) {
        // Restart and Interrupt Vectors
        return BOOTSTRAP[address];
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

void fetch() {
    auto byteToPrint = readByte(R.PC);
    R.PC++;
    LogInfo("0x%02X\n", byteToPrint);
}

const uint8_t NINTENDO_MAGIC[] = {
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
};

enum {
    OFF_BEGIN_CODE = 0x0100,
    OFF_MAGIC_START = 0x0104,
    OFF_MAGIC_END = 0x0133,
    OFF_TITLE_START = 0x0134,
    OFF_TITLE_END = 0x0142,
    OFF_COLOR_ENABLE = 0x0143,
    OFF_LICENSE = 0x0144,
    OFF_SUPER_ENABLE = 0x0146,
    OFF_CARTRIDGE_TYPE = 0x0147,
    OFF_ROM_SIZE = 0x0148,
    OFF_RAM_SIZE = 0x0149,
    OFF_REGION = 0x014A,
    OFF_LICENSE_OLD = 0x014B,
    OFF_ROM_MASK = 0x014C,
    OFF_COMPLEMENT_CHECK = 0x014D,
    OFF_CHECKSUM = 0x014E,
    OFF_HEADER_END = 0x0150,
};

void PrintFileHex(const std::vector<uint8_t>& buffer)
{
    // Print the file as hexadecimal numbers
    LogInfo("File as Hexadecimal:");
    for (unsigned i = 0; i < buffer.size(); ++i)
    {
        if (i % 32 == 0)
        {
            LogInfo("\n");
        }
        LogInfo("%02X ", buffer[i]);
    }

    LogInfo("\n\n\n");
}

// argc = number of arguments, argv = the arguments
int main(int argc, char* argv[])
{

    // Error check for too many arguments or too few
    if (argc < 2)
    {
        LogError("No filename specified.\n");
        return EXIT_FAILURE;
    }
    else if (argc > 2)
    {
        LogError("Too many arguments.\n");
        return EXIT_FAILURE;
    }

    // Load our file into ifstream
    std::ifstream file(argv[1], std::ios::binary);

    // Create our buffer, and stuff the file into it.
    std::vector<uint8_t> buffer(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    // Close the file
    file.close();

#pragma region ROMPrinting

    //// Print the file as hex
    ////PrintFileHex(buffer);

    //// Start Reading the buffer
    //printf("Start Code:\t%02X %02X %02X %02X\n", buffer[OFF_BEGIN_CODE], buffer[OFF_BEGIN_CODE + 1], buffer[OFF_BEGIN_CODE + 2], buffer[OFF_BEGIN_CODE + 3]);

    //// Verify the nintendo magic
    //if (memcmp(buffer.data() + OFF_MAGIC_START, NINTENDO_MAGIC, sizeof(NINTENDO_MAGIC)) != 0)
    //{
    //    LogError("NINTENDO MAGIC DOES NOT MATCH.\n");
    //    EXIT_FAILURE;
    //}
    //
    //// Print Title
    //int length = OFF_TITLE_END - OFF_TITLE_START;
    //
    //LogInfo("Title:\t%.*s\n", length, buffer.data() + OFF_TITLE_START);

    //// Color
    //if (buffer[OFF_COLOR_ENABLE] == 0x80)
    //{
    //    LogInfo("Color Enable:\tTrue\n");
    //}
    //else
    //{
    //    LogInfo("Color Enable:\tFalse\n");
    //}

    //// Super
    //if (buffer[OFF_SUPER_ENABLE] == 0x00)
    //{
    //    LogInfo("Super Gameboy:\tFalse\n");
    //}
    //else
    //{
    //    LogInfo("Super Gameboy:\tTrue\n");
    //}

    //// Cartridge Type
    //LogInfo("Cartridge Type:\t%02X\n", buffer[OFF_CARTRIDGE_TYPE]);

    //// Rom Size
    //LogInfo("Rom Size:\t%02X\n", buffer[OFF_ROM_SIZE]);

    //// Ram Size
    //LogInfo("Ram Size:\t%02X\n", buffer[OFF_RAM_SIZE]);

    //// Region
    //if (buffer[OFF_REGION] == 0)
    //{
    //    LogInfo("Region:\tJapan\n");
    //}
    //else
    //{
    //    LogInfo("Region:\tNon-Japan\n");
    //}

    //// Check Sum
    //LogInfo("Checksum:\t%02X %02X\n", buffer[OFF_CHECKSUM], buffer[OFF_CHECKSUM + 1]);
#pragma endregion

    R.PC = 0;

    //printf("0x%02X\n", readByte(0x0000));
    // Step 1
    fetch();

    // Step 2
    R.SP = readWord(R.PC);
    R.PC += 2;
    LogInfo("0x%04X\n", R.SP);

    // Step 3
    fetch();

    // Step 4
    R.A = 0;
    
    // Step 5
    fetch();

    // Step 6
    R.HL = readWord(R.PC);
    R.PC += 2;
    LogInfo("0x%04X\n", R.HL);

    // Step 7
    fetch();

    // Step 8
    //R.A = readByte(R.HL);
    //LogInfo("0x%02X\n", R.A);

    // Step 9
    fetch();

    // Step 10
    fetch();

    // Step 11
    fetch();

    // Step 12

    // Step 13
    fetch();

    return EXIT_SUCCESS;
}
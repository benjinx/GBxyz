#include <string.h>

#include "Log.h"
#include "Registers.h"
#include "Memory.h"

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

//void PrintFileHex(const std::vector<uint8_t>& buffer)
//{
//    // Print the file as hexadecimal numbers
//    LogInfo("File as Hexadecimal:");
//    for (unsigned i = 0; i < buffer.size(); ++i)
//    {
//        if (i % 32 == 0)
//        {
//            LogInfo("\n");
//        }
//        LogInfo("%02X ", buffer[i]);
//    }
//
//    LogInfo("\n\n\n");
//}

// argc = number of arguments, argv = the arguments
int main(int argc, char* argv[])
{

    // Error check for too many arguments or too few
    if (argc < 2)
    {
        LogError("No filename specified.\n");
        return 1;
    }
    else if (argc > 2)
    {
        LogError("Too many arguments.\n");
        return 1;
    }

    loadROM(argv[1]);

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

    return 0;
}
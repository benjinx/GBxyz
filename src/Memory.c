#include "Memory.h"
#include "Bootstrap.h"
#include "Registers.h"
#include "Log.h"

uint8_t CharacterRAM[0x1800];
uint8_t BGMapData1[0x400];
uint8_t BGMapData2[0x400];
uint8_t OAM[0xA0];

uint8_t ZP[127];

uint8_t* ROM = NULL;
uint8_t* ROM0 = NULL;
bool CPUEnable = true;

uint8_t readByte(uint16_t address) {
    if (address <= 0x00FF) {
        // Restart and Interrupt Vectors
        if (BootstrapEnable)
            return BOOTSTRAP[address];
        else
            return ROM0[address];
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

uint8_t nextByte()
{
    uint8_t byte = readByte(R.PC);
    ++R.PC;
    return byte;
}

uint16_t readWord(uint16_t address)
{
    uint16_t word = readByte(address + 1);
    word <<= 8;
    word |= readByte(address);
    return word;
}

void writeWord(uint16_t address, uint16_t data)
{
    writeByte(address, (uint8_t)(data & 0x00FF));
    writeByte(address + 1, (uint8_t)(data >> 8));
}

uint16_t nextWord()
{
    uint16_t word = readWord(R.PC);
    R.PC += 2;
    return word;
}

bool loadROM(const char* filename)
{
    FILE* file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    ROM = ROM0 = (uint8_t*)malloc(size);

    size_t bytesRead = fread(ROM, 1, size, file);
    fclose(file);

    LogVerbose("Read %zu bytes\n", bytesRead);

    if (bytesRead < size) {
        LogError("Failed to load: %s\n", filename);
        return false;
    }

    return true;
}

void pushAF()
{
    R.SP -= 2;
    writeWord(R.SP, R.AF);
}

void pushBC()
{
    R.SP -= 2;
    writeWord(R.SP, R.BC);
}

void pushDE()
{
    R.SP -= 2;
    writeWord(R.SP, R.DE);
}

void pushHL()
{
    R.SP -= 2;
    writeWord(R.SP, R.HL);
}

void readAF()
{
    R.AF = readWord(R.SP);
    R.SP += 2;
}

void readBC()
{
    R.BC = readWord(R.SP);
    R.SP += 2;
}

void readDE()
{
    R.DE = readWord(R.SP);
    R.SP += 2;
}

void readHL()
{
    R.HL = readWord(R.SP);
    R.SP += 2;
}

void NOP()
{

}

void halt()
{
    CPUEnable = false;
}

void stop()
{

}

void _JP_NZ_nn()
{
    uint16_t nn = nextWord();
    
    if (!R.FZ)
    {
        R.PC = nn;
    }
}

void _JP_NC_nn()
{
    uint16_t nn = nextWord();

    if (!R.FC)
    {
        R.PC = nn;
    }
}

void _JP_nn()
{
    R.PC = nextWord();
}

void _JP_pHL()
{
    R.PC = readWord(R.HL);
}

void _JP_Z_nn()
{
    uint16_t nn = nextWord();

    if (R.FZ)
    {
        R.PC = nn;
    }
}

void _JP_C_nn()
{
    uint16_t nn = nextWord();

    if (R.FC)
    {
        R.PC = nn;
    }
}

void _JR_NZ_n()
{
    int8_t n = nextByte();

    if (!R.FZ)
    {
        R.PC += n;
    }
}

void _JR_NC_n()
{
    int8_t n = nextByte();

    if (!R.FC)
    {
        R.PC += n;
    }
}

void _JR_n()
{
    R.PC += nextByte();
}

void _JR_Z_n()
{
    int8_t n = nextByte();

    if (R.FZ)
    {
        R.PC += n;
    }
}

void _JR_C_n()
{
    int8_t n = nextByte();

    if (R.FC)
    {
        R.PC += n;
    }
}

void _RST_00H()
{
    R.PC = 0x0000;
}

void _RST_08H()
{
    R.PC = 0x0008;
}

void _RST_10H()
{
    R.PC = 0x0010;
}

void _RST_18H()
{
    R.PC = 0x0018;
}

void _RST_20H()
{
    R.PC = 0x0020;
}

void _RST_28H()
{
    R.PC = 0x0028;
}

void _RST_30H()
{
    R.PC = 0x0030;
}

void _RST_38H()
{
    R.PC = 0x0038;
}

void _INC_BC()
{
    ++R.BC;
}

void _INC_DE()
{
    ++R.DE;
}

void _INC_HL()
{
    ++R.HL;
}

void _INC_SP()
{
    ++R.SP;
}

void _INC_B()
{
    R.FZ = (R.B + 1U == 256U);
    R.FN = false;
    R.FH = ((R.B & 0xF) == 0xF);
    ++R.B;
}

void _LD_B_B()
{

}

void _LD_D_B()
{
    R.D = R.B;
}

void _LD_H_B()
{
    R.H = R.B;
}

void _LD_pHL_B()
{
    writeByte(R.HL, R.B);
}

void _LD_B_C()
{
    R.B = R.C;
}

void _LD_D_C()
{
    R.D = R.C;
}

void _LD_H_C()
{
    R.H = R.C;
}

void _LD_pHL_C()
{
    writeByte(R.HL, R.C);
}

void _LD_pBC_A()
{
    writeByte(R.BC, R.A);
}

void _LD_pDE_A()
{
    writeByte(R.DE, R.A);
}

void _LDI_pHL_A()
{
    writeByte(R.HL, R.A);
    ++R.HL;
}

void _LDD_pHL_A()
{
    writeByte(R.HL, R.A);
    --R.HL;
}

void _LD_B_D()
{
    R.B = R.D;
}

void _LD_D_D()
{
    
}

void _LD_H_D()
{
    R.H = R.D;
}

void _LD_pHL_D()
{
    writeByte(R.HL, R.D);
}

void _LD_B_E()
{
    R.B = R.E;
}

void _LD_D_E()
{
    R.D = R.E;
}

void _LD_H_E()
{
    R.H = R.E;
}

void _LD_pHL_E()
{
    writeByte(R.HL, R.E);
}

void _LD_B_H()
{
    R.B = R.H;
}

void _LD_D_H()
{
    R.D = R.H;
}

void _LD_H_H()
{

}

void _LD_pHL_H()
{
    writeByte(R.HL, R.H);
}
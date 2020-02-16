#include "../Registers.h"

static void _RST_00H()
{
    R.PC = 0x0000;
}

static void _RST_08H()
{
    R.PC = 0x0008;
}

static void _RST_10H()
{
    R.PC = 0x0010;
}

static void _RST_18H()
{
    R.PC = 0x0018;
}

static void _RST_20H()
{
    R.PC = 0x0020;
}

static void _RST_28H()
{
    R.PC = 0x0028;
}

static void _RST_30H()
{
    R.PC = 0x0030;
}

static void _RST_38H()
{
    R.PC = 0x0038;
}
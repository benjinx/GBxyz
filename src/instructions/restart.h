#include "../registers.h"

static void _RST_00()
{
    R.PC = 0x0000;
}

static void _RST_08()
{
    R.PC = 0x0008;
}

static void _RST_10()
{
    R.PC = 0x0010;
}

static void _RST_18()
{
    R.PC = 0x0018;
}

static void _RST_20()
{
    R.PC = 0x0020;
}

static void _RST_28()
{
    R.PC = 0x0028;
}

static void _RST_30()
{
    R.PC = 0x0030;
}

static void _RST_38()
{
    R.PC = 0x0038;
}
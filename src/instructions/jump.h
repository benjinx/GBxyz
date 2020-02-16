#include "../memory.h"
#include "../registers.h"

static void _JP_NZ_nn()
{
    uint16_t nn = nextWord();

    if (!R.FZ)
    {
        R.PC = nn;
    }
}

static void _JP_NC_nn()
{
    uint16_t nn = nextWord();

    if (!R.FC)
    {
        R.PC = nn;
    }
}

static void _JP_nn()
{
    R.PC = nextWord();
}

static void _JP_pHL()
{
    R.PC = readWord(R.HL);
}

static void _JP_Z_nn()
{
    uint16_t nn = nextWord();

    if (R.FZ)
    {
        R.PC = nn;
    }
}

static void _JP_C_nn()
{
    uint16_t nn = nextWord();

    if (R.FC)
    {
        R.PC = nn;
    }
}

static void _JR_NZ_n()
{
    int8_t n = nextByte();

    if (!R.FZ)
    {
        R.PC += n;
    }
}

static void _JR_NC_n()
{
    int8_t n = nextByte();

    if (!R.FC)
    {
        R.PC += n;
    }
}

static void _JR_n()
{
    R.PC += nextByte();
}

static void _JR_Z_n()
{
    int8_t n = nextByte();

    if (R.FZ)
    {
        R.PC += n;
    }
}

static void _JR_C_n()
{
    int8_t n = nextByte();

    if (R.FC)
    {
        R.PC += n;
    }
}
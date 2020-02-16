#include "../memory.h"
#include "../registers.h"

static void _POP_AF()
{
    R.AF = readWord(R.SP);
    R.SP += 2;
}

static void _POP_BC()
{
    R.BC = readWord(R.SP);
    R.SP += 2;
}

static void _POP_DE()
{
    R.DE = readWord(R.SP);
    R.SP += 2;
}

static void _POP_HL()
{
    R.HL = readWord(R.SP);
    R.SP += 2;
}
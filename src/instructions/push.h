#include "../Memory.h"
#include "../Registers.h"

static void _PUSH_AF()
{
    R.SP -= 2;
    writeWord(R.SP, R.AF);
}

static void _PUSH_BC()
{
    R.SP -= 2;
    writeWord(R.SP, R.BC);
}

static void _PUSH_DE()
{
    R.SP -= 2;
    writeWord(R.SP, R.DE);
}

static void _PUSH_HL()
{
    R.SP -= 2;
    writeWord(R.SP, R.HL);
}
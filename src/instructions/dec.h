#include "../memory.h"
#include "../registers.h"

static void _DEC_BC()
{
    --R.BC;
}

static void _DEC_DE()
{
    --R.DE;
}

static void _DEC_HL()
{
    --R.HL;
}

static void _DEC_SP()
{
    --R.SP;
}

#define _DEC(x)                     \
    R.FH = (((x) & 0xF) == 0);      \
    --(x);                          \
    R.FZ = ((x) == 0);              \
    R.FN = true

static void _DEC_A()
{
    _DEC(R.A);
}

static void _DEC_B()
{
    _DEC(R.B);
}

static void _DEC_C()
{
    _DEC(R.C);
}

static void _DEC_D()
{
    _DEC(R.D);
}

static void _DEC_E()
{
    _DEC(R.E);
}

static void _DEC_H()
{
    _DEC(R.H);
}

static void _DEC_L()
{
    _DEC(R.L);
}

static void _DEC_pHL()
{
    uint8_t n = readByte(R.HL);
    _DEC(n);
    writeByte(R.HL, n);
}
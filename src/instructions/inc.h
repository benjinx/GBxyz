#include "../memory.h"
#include "../registers.h"

static void _INC_BC()
{
    ++R.BC;
}

static void _INC_DE()
{
    ++R.DE;
}

static void _INC_HL()
{
    ++R.HL;
}

static void _INC_SP()
{
    ++R.SP;
}

#define _INC(x)                     \
    R.FH = (((x) & 0xF) == 0xF);    \
    ++(x);                          \
    R.FZ = ((x) == 0);              \
    R.FN = false

static void _INC_A()
{
    _INC(R.A);
}

static void _INC_B()
{
    _INC(R.B);
}

static void _INC_C()
{
    _INC(R.C);
}

static void _INC_D()
{
    _INC(R.D);
}

static void _INC_E()
{
    _INC(R.E);
}

static void _INC_H()
{
    _INC(R.H);
}

static void _INC_L()
{
    _INC(R.L);
}

static void _INC_pHL()
{
    uint8_t n = readByte(R.HL);
    _INC(n);
    writeByte(R.HL, n);
}
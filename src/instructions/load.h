#include "../memory.h"
#include "../registers.h"

static void _LD_B_B()
{

}

static void _LD_D_B()
{
    R.D = R.B;
}

static void _LD_H_B()
{
    R.H = R.B;
}

static void _LD_pHL_B()
{
    writeByte(R.HL, R.B);
}

static void _LD_B_C()
{
    R.B = R.C;
}

static void _LD_D_C()
{
    R.D = R.C;
}

static void _LD_H_C()
{
    R.H = R.C;
}

static void _LD_pHL_C()
{
    writeByte(R.HL, R.C);
}

static void _LD_pBC_A()
{
    writeByte(R.BC, R.A);
}

static void _LD_pDE_A()
{
    writeByte(R.DE, R.A);
}

static void _LDI_pHL_A()
{
    writeByte(R.HL, R.A);
    ++R.HL;
}

static void _LDD_pHL_A()
{
    writeByte(R.HL, R.A);
    --R.HL;
}

static void _LD_B_D()
{
    R.B = R.D;
}

static void _LD_D_D()
{

}

static void _LD_H_D()
{
    R.H = R.D;
}

static void _LD_pHL_D()
{
    writeByte(R.HL, R.D);
}

static void _LD_B_E()
{
    R.B = R.E;
}

static void _LD_D_E()
{
    R.D = R.E;
}

static void _LD_H_E()
{
    R.H = R.E;
}

static void _LD_pHL_E()
{
    writeByte(R.HL, R.E);
}

static void _LD_B_H()
{
    R.B = R.H;
}

static void _LD_D_H()
{
    R.D = R.H;
}

static void _LD_H_H()
{

}

static void _LD_pHL_H()
{
    writeByte(R.HL, R.H);
}

static void _LD_B_L()
{
    R.B = R.L;
}

static void _LD_D_L()
{
    R.D = R.L;
}

static void _LD_H_L()
{
    R.H = R.L;
}

static void _LD_pHL_L()
{
    writeByte(R.HL, R.L);
}

static void _LD_B_n()
{
    uint8_t n = nextByte();
    R.B = n;
}

static void _LD_D_n()
{
    uint8_t n = nextByte();
    R.D = n;
}

static void _LD_H_n()
{
    uint8_t n = nextByte();
    R.H = n;
}

static void _LD_pHL_n()
{
    uint8_t n = nextByte();
    writeByte(R.HL, n);
}

static void _LD_B_pHL()
{
    R.B = readByte(R.HL);
}

static void _LD_D_pHL()
{
    R.D = readByte(R.HL);
}

static void _LD_H_pHL()
{
    R.H = readByte(R.HL);
}

static void _LD_B_A()
{
    R.B = R.A;
}

static void _LD_D_A()
{
    R.D = R.A;
}

static void _LD_H_A()
{
    R.H = R.A;
}

static void _LD_pHL_A()
{
    writeByte(R.HL, R.A);
}

static void _LD_C_B()
{
    R.C = R.B;
}

static void _LD_E_B()
{
    R.E = R.B;
}

static void _LD_L_B()
{
    R.L = R.B;
}

static void _LD_A_B()
{
    R.A = R.B;
}

static void _LD_C_C()
{

}

static void _LD_E_C()
{
    R.E = R.C;
}

static void _LD_L_C()
{
    R.L = R.C;
}

static void _LD_A_C()
{
    R.A = R.C;
}

static void _LD_A_pBC()
{
    R.A = readByte(R.BC);
}

static void _LD_A_pDE()
{
    R.A = readByte(R.DE);
}

static void _LDI_A_pHL()
{
    R.A = readByte(R.HL);
    ++R.HL;
}

static void _LDD_A_pHL()
{
    R.A = readByte(R.HL);
    --R.HL;
}

static void _LD_C_D()
{
    R.C = R.D;
}

static void _LD_E_D()
{
    R.E = R.D;
}

static void _LD_L_D()
{
    R.L = R.D;
}

static void _LD_A_D()
{
    R.A = R.D;
}

static void _LD_C_E()
{
    R.C = R.E;
}

static void _LD_E_E()
{

}

static void _LD_L_E()
{
    R.L = R.E;
}

static void _LD_A_E()
{
    R.A = R.E;
}

static void _LD_C_H()
{
    R.C = R.H;
}

static void _LD_E_H()
{
    R.E = R.H;
}

static void _LD_L_H()
{
    R.L = R.H;
}

static void _LD_A_H()
{
    R.A = R.H;
}

static void _LD_C_L()
{
    R.C = R.L;
}

static void _LD_E_L()
{
    R.E = R.L;
}

static void _LD_L_L()
{

}

static void _LD_A_L()
{
    R.A = R.L;
}

static void _LD_C_n()
{
    uint8_t n = nextByte();
    R.C = n;
}

static void _LD_E_n()
{
    uint8_t n = nextByte();
    R.E = n;
}

static void _LD_L_n()
{
    uint8_t n = nextByte();
    R.L = n;
}

static void _LD_A_n()
{
    uint8_t n = nextByte();
    R.A = n;
}

static void _LD_C_pHL()
{
    R.C = readByte(R.HL);
}

static void _LD_E_pHL()
{
    R.E = readByte(R.HL);
}

static void _LD_L_pHL()
{
    R.L = readByte(R.HL);
}

static void _LD_A_pHL()
{
    R.A = readByte(R.HL);
}

static void _LD_C_A()
{
    R.C = R.A;
}

static void _LD_E_A()
{
    R.E = R.A;
}

static void _LD_L_A()
{
    R.L = R.A;
}

static void _LD_A_A()
{

}

static void _LDH_pn_A()
{
    uint8_t n = nextByte();
    writeByte(0xFF00 + n, R.A);
}

static void _LDH_A_pn()
{
    uint8_t n = nextByte();
    R.A = readByte(0xFF00 + n);
}

static void _LDH_pC_A()
{
    writeByte(0xFF00 + R.C, R.A);
}

static void _LDH_A_pC()
{
    R.A = readByte(0xFF00 + R.C);
}

static void _LD_pnn_A()
{
    uint16_t nn = nextWord();
    writeByte(nn, R.A);
}

static void _LD_A_pnn()
{
    uint16_t nn = nextWord();
    R.A = readByte(nn);
}

static void _LD_BC_nn()
{
    uint16_t nn = nextWord();
    R.BC = nn;
}

static void _LD_DE_nn()
{
    uint16_t nn = nextWord();
    R.DE = nn;
}

static void _LD_HL_nn()
{
    uint16_t nn = nextWord();
    R.HL = nn;
}

static void _LD_SP_nn()
{
    uint16_t nn = nextWord();
    R.SP = nn;
}

static void _LD_SP_HL()
{
    R.SP = R.HL;
}

static void _LD_pnn_SP()
{
    uint16_t nn = nextWord();
    nn = readWord(nn);
    writeWord(nn, R.SP);
}

static void _LD_HL_SP_n()
{
    
}
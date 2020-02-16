#include "../memory.h"

static void _NOP()
{

}

static void _HALT()
{
    CPUEnable = false;
}

static void _STOP()
{

}
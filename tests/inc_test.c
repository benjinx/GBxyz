#include "tinyUT.h"

void setup()
{

}

int main(int argc, char** argv)
{
    UNIT_RUN_SUITE(INC8);
    UNIT_RUN_SUITE(INC16);
    UNIT_REPORT();
    return UNIT_EXIT_CODE;
}
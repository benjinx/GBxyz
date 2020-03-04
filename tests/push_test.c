#include "tinyUT.h"
#include "../src/memory.h"
#include "../src/instructions/push.h"

void setup()
{
    R.SP = 0xFFFE;
}

void teardown()
{
    R.SP = 0x0000;
}

UNIT_TEST(PUSH_AF)
{
    R.AF = 0x1234;
    _PUSH_AF();
    unit_assert_hex_eq(0xFFFC, R.SP); // We're checking to see if it subtracts 2.
    unit_assert_hex_eq(0x1234, readWord(R.SP)); // Checking if it did a writeWord correctly.
}

UNIT_TEST(PUSH_BC)
{
    R.BC = 0x1234;
    _PUSH_BC();
    unit_assert_hex_eq(0xFFFC, R.SP); // We're checking to see if it subtracts 2.
    unit_assert_hex_eq(0x1234, readWord(R.SP)); // Checking if it did a writeWord correctly.
}

UNIT_TEST(PUSH_DE)
{
    R.DE = 0x1234;
    _PUSH_DE();
    unit_assert_hex_eq(0xFFFC, R.SP); // We're checking to see if it subtracts 2.
    unit_assert_hex_eq(0x1234, readWord(R.SP)); // Checking if it did a writeWord correctly.
}

UNIT_TEST(PUSH_HL)
{
    R.HL = 0x1234;
    _PUSH_HL();
    unit_assert_hex_eq(0xFFFC, R.SP); // We're checking to see if it subtracts 2.
    unit_assert_hex_eq(0x1234, readWord(R.SP)); // Checking if it did a writeWord correctly.
}

UNIT_TEST_SUITE(PUSH)
{
    UNIT_SUITE_SETUP(&setup);
    UNIT_SUITE_TEARDOWN(&teardown);

    UNIT_RUN_TEST(PUSH_AF);
    UNIT_RUN_TEST(PUSH_BC);
    UNIT_RUN_TEST(PUSH_DE);
    UNIT_RUN_TEST(PUSH_HL);
}

int main(int argc, char** argv)
{
    UNIT_RUN_SUITE(PUSH);
    UNIT_REPORT();
    return UNIT_EXIT_CODE;
}
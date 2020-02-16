#ifndef TINY_UT_H
#define TINY_UT_H

static int tutRun = 0;
static int tutAssert = 0;
static int tutFail = 0;
static int tutStatus = 0;

#define TUT_TEST(test_name) static void TEST_##test_name()
#define TUT_TEST_SUITE(suite_name) static void SUITE_##suite_name()
#define TUT_EXIT_CODE tutStatus

#define TUT_REPORT()                                                \
    do {                                                            \
        printf("\n%d tests, %d assertions, %d failures\n",          \
            tutRun, tutAssert, tutFail);                            \
    } while (0)

#define tut_assert_string_eq(expected, result)                      \
    do {                                                            \
        ++tutAssert;                                                \
        const char* tmpExpected = (expected);                       \
        const char* tmpResult = (result);                           \
        fflush(stdout);                                             \
        if (strcmp(tmpExpected, tmpResult)) {                       \
            unit_status = 1;                                        \
            if (!tmpExpected) { tmpExpected = "<null>"; }           \
            if (!tmpResult) { tmpResult = "<null>"; }               \
            printf(unit_message, UNIT_MESSAGE_LEN,                  \
                "%s:%d %s expected but was %s\n",                   \
                __FILE__, __LINE__, tmpExpected, tmpResult);        \
        }                                                           \
    } while (0)

#define tut_assert_int_eq(expected, result)                         \
    do {                                                            \
        ++tutAssert;                                                \
        int tmpExpected = (expected);                               \
        int tmpResult = (result);                                   \
        if (tmpExcepted != tmpResult) {                             \
            tutStatus = 1;                                          \
            printf("%s:%d Expected %d, result was %d",              \
                __FILE__, __LINE__, tmpExpected, tmpResult);        \
        }                                                           \
    } while (0)                                                     \

#endif // TINY_UT_H
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(DateFormat) {
    RUN_TEST_CASE(DateFormat, TestisDateValid_NULLDate);
    RUN_TEST_CASE(DateFormat, TestisDateValid_EmptyDate);
    RUN_TEST_CASE(DateFormat, TestisDateValid_AlphaCharInput);
    RUN_TEST_CASE(DateFormat, TestisDateValid_BadSeparatorInput);
    RUN_TEST_CASE(DateFormat, TestisDateValid_InvalidMonth);
    RUN_TEST_CASE(DateFormat, TestisDateValid_InvalidDay);
    RUN_TEST_CASE(DateFormat, TestisDateValid_InvalidLeapYearDay);
    RUN_TEST_CASE(DateFormat, TestisDateValid_InvalidNonLeapYearDay);
    RUN_TEST_CASE(DateFormat, TestisDateValid_ValidDate);
}

TEST_GROUP_RUNNER(StringFormat) {
    RUN_TEST_CASE(StringFormat, TestisNameValid_NULLName);
    RUN_TEST_CASE(StringFormat, TestisNameValid_EmptyName);
    RUN_TEST_CASE(StringFormat, TestisNameValid_DigitCharInput);
    RUN_TEST_CASE(StringFormat, TestisNameValid_SpecialCharInput);
    RUN_TEST_CASE(StringFormat, TestisNameValid_ValidName);
}
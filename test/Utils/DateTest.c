#include "unity.h"
#include "unity_fixture.h"
#include "utils.h"

TEST_GROUP(DateFormat);

TEST_SETUP(DateFormat) {}

TEST_TEAR_DOWN(DateFormat) {}

TEST(DateFormat, TestisDateValid_NULLDate) {
    int error = isDateValid(NULL);
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(DateFormat, TestisDateValid_EmptyDate) {
    int error = isDateValid("\0");
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(DateFormat, TestisDateValid_AlphaCharInput) {
    int error = isDateValid("2r_dfc_fgrg");
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(DateFormat, TestisDateValid_BadSeparatorInput) {
    int error = isDateValid("05)05/2026");
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(DateFormat, TestisDateValid_InvalidMonth) {
    int error = isDateValid("13_05_2026");
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(DateFormat, TestisDateValid_InvalidDay) {
    int error = isDateValid("05_32_2026");
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(DateFormat, TestisDateValid_InvalidLeapYearDay) {
    int error = isDateValid("02_30_2024");
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(DateFormat, TestisDateValid_InvalidNonLeapYearDay) {
    int error = isDateValid("02_29_2026");
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(DateFormat, TestisDateValid_ValidDate) {}
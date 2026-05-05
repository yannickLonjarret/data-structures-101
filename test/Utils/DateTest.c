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

TEST(DateFormat, TestisDateValid_InvalidMonth) {}

TEST(DateFormat, TestisDateValid_InvalidDay) {}

TEST(DateFormat, TestisDateValid_InvalidLeapYearDay) {}

TEST(DateFormat, TestisDateValid_InvalidNonLeapYearDay) {}

TEST(DateFormat, TestisDateValid_ValidDate) {}
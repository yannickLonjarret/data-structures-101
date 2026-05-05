#include "unity.h"
#include "unity_fixture.h"
#include "utils.h"

TEST_GROUP(StringFormat);

TEST_SETUP(StringFormat) {}

TEST_TEAR_DOWN(StringFormat) {}

TEST(StringFormat, TestisNameValid_NULLName) {
    int error = isNameValid(NULL);
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(StringFormat, TestisNameValid_EmptyName) {
    int error = isNameValid("\0");
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(StringFormat, TestisNameValid_DigitCharInput) {
    int error = isNameValid("H7ll0");
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(StringFormat, TestisNameValid_SpecialCharInput) {
    int error = isNameValid("Lorem-ipsum");
    TEST_ASSERT_NOT_EQUAL(0, error);
}

TEST(StringFormat, TestisNameValid_ValidName) {
    int error = isNameValid("NormalName");
    TEST_ASSERT_NOT_EQUAL(1, error);
}
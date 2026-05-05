#include "unity.h"
#include "unity_fixture.h"
#include "utils.h"

TEST_GROUP(DateFormat);

TEST_SETUP(DateFormat) {}

TEST_TEAR_DOWN(DateFormat) {}

TEST(DateFormat, TestisDateValid_NULLDate) {}

TEST(DateFormat, TestisDateValid_EmptyDate) {}

TEST(DateFormat, TestisDateValid_GarbageInput) {}

TEST(DateFormat, TestisDateValid_InvalidMonth) {}

TEST(DateFormat, TestisDateValid_InvalidDay) {}

TEST(DateFormat, TestisDateValid_InvalidLeapYearDay) {}

TEST(DateFormat, TestisDateValid_InvalidNonLeapYearDay) {}

TEST(DateFormat, TestisDateValid_ValidDate) {}
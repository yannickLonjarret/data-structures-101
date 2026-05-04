#include "PatientIndexer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(DeepCopy);

TEST_SETUP(DeepCopy) {}

TEST_TEAR_DOWN(DeepCopy) {}

TEST(DeepCopy, DeepCopyPatient_NULLOriginal) {
    PatientFile* copy = DeepCopyPatient(NULL);
    TEST_ASSERT_NULL(copy);
}
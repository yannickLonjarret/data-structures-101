#include "unity_fixture.h"

static void RunAllTests(void) {
    RUN_TEST_GROUP(DateFormat);
    RUN_TEST_GROUP(StringFormat);
}

int main(int argc, const char* argv[]) { return UnityMain(argc, argv, RunAllTests); }
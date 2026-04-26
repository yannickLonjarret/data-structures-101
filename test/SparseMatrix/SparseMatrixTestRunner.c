#include "unity_fixture.h"

static void RunAllTests(void) {
    RUN_TEST_GROUP(LinkedListManip);
    RUN_TEST_GROUP(LinkedListSearch);
    RUN_TEST_GROUP(MatrixAdd);
    RUN_TEST_GROUP(MemoryManagement);
    RUN_TEST_GROUP(Misc);
    RUN_TEST_GROUP(PutValueTest);
}

int main(int argc, const char* argv[]) { return UnityMain(argc, argv, RunAllTests); }
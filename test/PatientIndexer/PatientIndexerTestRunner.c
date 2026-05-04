#include "unity_fixture.h"

static void RunAllTests(void) {
    RUN_TEST_GROUP(MemoryManagement);
    RUN_TEST_GROUP(NodeRemoval);
    RUN_TEST_GROUP(TreeInsertion);
    RUN_TEST_GROUP(TreeMinimum);
    RUN_TEST_GROUP(TreeSearch);
    RUN_TEST_GROUP(DeepCopy);
}

int main(int argc, const char* argv[]) { return UnityMain(argc, argv, RunAllTests); }
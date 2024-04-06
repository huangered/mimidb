#include "g.hpp"
#include "util/memutils.h"
#include "storage/bufmgr.h"
#include "access/relcache.h"

class Environment1 : public ::testing::Environment {
public:
    ~Environment1() override {
    }

    // Override this to define how to set up the environment.
    void
    SetUp() override {
        MemoryContextInit();
        InitBufferPool();
        RelationCacheInitialize();
    }

    // Override this to define how to tear down the environment.
    void
    TearDown() override {
    }
};

::testing::Environment* const foo_env = ::testing::AddGlobalTestEnvironment(new Environment1);

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB sub_sources */*.cpp)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(unittest global_app.cpp ${sub_sources})
target_link_libraries(unittest 
 GTest::gtest_main
 access catalog common commands executor port storage top util c_util)
 
include(GoogleTest)

gtest_discover_tests(unittest)

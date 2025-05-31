# --- Doctest Configuration ---
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG 2.4.11
)
FetchContent_MakeAvailable(doctest)

# --- Test Executable ---
add_executable(run_tests TestFinanceManager.cpp)

target_link_libraries(run_tests PRIVATE doctest finance_lib)
target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# --- CTest Integration ---
add_test(NAME FinanceManagerTests COMMAND run_tests)
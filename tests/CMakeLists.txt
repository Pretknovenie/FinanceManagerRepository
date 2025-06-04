FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)
FetchContent_MakeAvailable(doctest)

add_executable(run_tests TestFinanceManager.cpp)

target_include_directories(run_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${doctest_SOURCE_DIR}/doctest
)

target_link_libraries(run_tests PRIVATE doctest finance_lib)

add_test(NAME FinanceManagerTests COMMAND run_tests)

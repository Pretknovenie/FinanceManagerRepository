add_executable(finance_app
    main.cpp
    Date.h Date.cpp
    Transaction.h Transaction.cpp
    FinanceManager.h FinanceManager.cpp
)

target_include_directories(finance_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(finance_lib STATIC
    Date.cpp
    Transaction.cpp
    FinanceManager.cpp
)

target_include_directories(finance_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

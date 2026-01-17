cmake_minimum_required(VERSION 3.20)
project(Todo-List)

set(CMAKE_CXX_STANDARD 17)

# Configurazione Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(esegui_test
        Test/testTask.cpp
        Test/testManager.cpp
        Test/testTime.cpp
        Task.cpp
        Time.cpp
        TodoManager.cpp
)
target_link_libraries(esegui_test gtest_main)
add_executable(Todo-List
        main.cpp
        Task.cpp
        TodoManager.cpp
        Time.cpp
)
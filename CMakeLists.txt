cmake_minimum_required(VERSION 3.20)
project(Todo-List)

set(CMAKE_CXX_STANDARD 17)

# Aggiunge l'eseguibile principale
add_executable(Todo-List main.cpp
        main.cpp
        Task.h
        Task.cpp
        TodoManager.h
        TodoManager.cpp
        Time.cpp
        Time.h
)
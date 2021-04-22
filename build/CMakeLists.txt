cmake_minimum_required(VERSION 3.0.0)
project(learnSFML VERSION 0.1.0)

include(CTest)
enable_testing()

set (SOURCES ${SOURCES}
    src/main.cpp
)

set (HEADERS ${HEADERS}
    
)

add_executable(learnSFML ${SOURCES})


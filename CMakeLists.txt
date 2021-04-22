cmake_minimum_required(VERSION 3.8.0)
project(learnSFML VERSION 0.1.0)


# Build libraries
add_subdirectory(SFML)

set (SOURCES ${SOURCES}
    src/main.cpp
)

set (HEADERS ${HEADERS}
    
)

add_executable(learnSFML ${SOURCES})

target_include_directories(learnSFML PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include)

target_link_libraries(learnSFML
    sfml-graphics
    sfml-window
    sfml-graphics
)

set_property(TARGET learnSFML PROPERTY CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.8.0)
project(learnSFML VERSION 0.1.0)


# Build libraries
add_subdirectory(SFML)


set (SOURCES ${SOURCES}
src/new/graphing.cpp
)

add_executable(learnSFML ${SOURCES})

target_include_directories(learnSFML PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include)
target_include_directories(learnSFML PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glm/)
target_include_directories(learnSFML PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)


target_link_libraries(learnSFML
    sfml-graphics
)

set_property(TARGET learnSFML PROPERTY CXX_STANDARD 17)

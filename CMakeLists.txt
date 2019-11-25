cmake_minimum_required(VERSION 3.1)
project(Invaders)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/spdlog")
find_library(spdlog REQUIRED)

# the directory where sfml is located
set(SFML_DIR "C:/Program Files/SFML-2.5.1")
find_package(SFML 2.5 COMPONENTS graphics window audio REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(invaders ${SOURCES})

target_link_libraries(invaders spdlog sfml-system sfml-window sfml-graphics)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
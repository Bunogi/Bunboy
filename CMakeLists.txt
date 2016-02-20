cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)
project(bunboy)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

find_package(SFML REQUIRED system window graphics)
include_directories(${SFML_INCLUDE_DIR})

add_executable(
	bunboy
	src/main.cpp
	src/gb.cpp
	src/cpu.cpp
	src/memory.cpp
	src/opcodes.cpp
)

target_link_libraries(bunboy ${SFML_LIBRARIES})

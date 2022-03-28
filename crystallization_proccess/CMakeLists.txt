cmake_minimum_required(VERSION 3.21)
project(crystallization_proccess)

set(CMAKE_CXX_STANDARD 20)

add_executable(first_attempt main.cpp Map_Draw.cpp Map_Draw.h Map.cpp Map.h Cells.cpp Cells.h Cells_Draw.cpp Cells_Draw.h)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML-2.5.1/include)
target_link_libraries(first_attempt sfml-system sfml-window sfml-graphics sfml-audio)
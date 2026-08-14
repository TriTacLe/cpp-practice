cmake_minimum_required(VERSION 3.16)
project(inft2503 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Emnet krever at koden er ren under -Wall -Wextra.
add_compile_options(-Wall -Wextra)

add_subdirectory(ovinger/oving-01)
add_subdirectory(ovinger/oving-02)
add_subdirectory(ovinger/oving-03)
add_subdirectory(ovinger/oving-04)

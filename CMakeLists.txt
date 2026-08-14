cmake_minimum_required(VERSION 3.16)
project(inft2503 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# The course wants the code clean under -Wall -Wextra.
add_compile_options(-Wall -Wextra)

add_subdirectory(exercises/exercise-01)
add_subdirectory(exercises/exercise-02)
add_subdirectory(exercises/exercise-03)
add_subdirectory(exercises/exercise-04)
add_subdirectory(exercises/exercise-05)
add_subdirectory(exercises/exercise-06)
add_subdirectory(exercises/exercise-07)
add_subdirectory(exercises/exercise-08)
add_subdirectory(exercises/exercise-09)

# exercise-10 is not built here. It replaces main.cpp in
# gitlab.com/ntnu-iini4003/game and needs that repo's sfml, glm, bullet and
# imgui setup.

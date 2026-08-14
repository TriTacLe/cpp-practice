add_executable(exercise06_task1 task1.cpp)

# Task 2 uses POSIX sockets, so it is not built on Windows.
if(UNIX)
  add_executable(exercise06_task2 task2.cpp)
else()
  message(STATUS "not UNIX, skipping exercise06_task2")
endif()

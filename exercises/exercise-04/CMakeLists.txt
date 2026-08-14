add_executable(exercise04_task1 task1.cpp)

# Task 2 needs gtkmm-3.0. Built only if it is installed, so the rest of the
# repo still builds without it.
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
  pkg_check_modules(GTKMM QUIET gtkmm-3.0)
endif()

if(GTKMM_FOUND)
  add_executable(exercise04_task2 task2.cpp)
  target_include_directories(exercise04_task2 SYSTEM PRIVATE ${GTKMM_INCLUDE_DIRS})
  target_link_directories(exercise04_task2 PRIVATE ${GTKMM_LIBRARY_DIRS})
  target_link_libraries(exercise04_task2 PRIVATE ${GTKMM_LIBRARIES})
else()
  message(STATUS "gtkmm-3.0 not found, skipping exercise04_task2")
endif()

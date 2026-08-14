add_executable(oving04_oppgave1 oppgave1.cpp)

# Oppgave 2 krever gtkmm-3.0. Bygges bare hvis biblioteket finnes, slik at
# resten av repoet fortsatt bygger på en maskin uten gtkmm.
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
  pkg_check_modules(GTKMM QUIET gtkmm-3.0)
endif()

if(GTKMM_FOUND)
  add_executable(oving04_oppgave2 oppgave2.cpp)
  target_include_directories(oving04_oppgave2 SYSTEM PRIVATE ${GTKMM_INCLUDE_DIRS})
  target_link_directories(oving04_oppgave2 PRIVATE ${GTKMM_LIBRARY_DIRS})
  target_link_libraries(oving04_oppgave2 PRIVATE ${GTKMM_LIBRARIES})
else()
  message(STATUS "gtkmm-3.0 ikke funnet, hopper over oving04_oppgave2")
endif()

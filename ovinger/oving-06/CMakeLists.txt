add_executable(oving06_oppgave1 oppgave1.cpp)

# Oppgave 2 bruker POSIX-sockets. Bygges ikke på Windows.
if(UNIX)
  add_executable(oving06_oppgave2 oppgave2.cpp)
else()
  message(STATUS "Ikke UNIX, hopper over oving06_oppgave2")
endif()

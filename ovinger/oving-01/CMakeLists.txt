add_executable(oving01a a_uten_tabell.cpp)
add_executable(oving01b b_med_tabell.cpp)

# b) leser fra fil i katalogen programmet kjorer fra.
configure_file(temperaturer.txt temperaturer.txt COPYONLY)

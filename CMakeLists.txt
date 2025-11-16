cmake_minimum_required(VERSION 3.10)
project(OceanDepths C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(oceandephs
        main.c
        joueur.c
        creatures.c
        combat.c
        inventaire.c
)

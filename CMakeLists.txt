cmake_minimum_required(VERSION 4.4)
project(trabalhoIP3t C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(trabalhoIP3t
        carta.h
        dados.c
        dados.h
        jogo.c
        jogo.h
        main.c
        monte.c
        monte.h
        ranking.c
        ranking.h
        utils.c
        utils.h)

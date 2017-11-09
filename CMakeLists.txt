cmake_minimum_required(VERSION 3.8)
project(sys_project)

set(CMAKE_C_STANDARD 11)
add_definitions(-Wall -Wextra -Wconversion -Werror -pedantic)
add_definitions(-fstack-protector-all -D_X_OPEN_SOURCE=700)
add_definitions(-pthread -lrt)

set(SOURCE_FILES
        src/main.c src/headers.h
        src/pipes.c src/pipes.h
        src/waitloop.c src/waitloop.h
        src/clients.c src/clients.h
        src/misc.c src/misc.h src/commands.h)

add_executable(sys_project ${SOURCE_FILES})
add_executable(client client/main.c)

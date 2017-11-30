cmake_minimum_required(VERSION 3.4)
project(sys_project)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion -Werror -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all -D_X_OPEN_SOURCE=700")

set(SERVER_SOURCE_FILES
        src/main.c       src/headers.h
        src/pipes.c      src/pipes.h
        src/waitloop.c   src/waitloop.h
        src/clients.c    src/clients.h
        src/misc.c       src/misc.h
        src/commands.c   src/commands.h
        src/cmd_terminate.c)

set(CLIENT_SOURCE_FILES
        client/main.c
        client/shm.c     client/shm.h
        client/sem.c     client/sem.h
        client/fifo.c    client/fifo.h
        src/commands.h)


add_executable(sys_project ${SERVER_SOURCE_FILES})
target_link_libraries(sys_project rt pthread)

add_executable(client ${CLIENT_SOURCE_FILES})
target_link_libraries(client rt pthread)

cmake_minimum_required(VERSION 3.4)
project(sys_project)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion -Werror -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all -D_X_OPEN_SOURCE=700")

# if debug
#add_definitions("-DDEBUG")

set(SERVER_SOURCE_FILES
        src/main.c src/perrorcl.c common.h
        src/pipes.c      src/pipes.h
        src/waitloop.c   src/waitloop.h
        src/clients.c    src/clients.h
        src/misc.c       src/misc.h
        src/commands.c   src/commands.h
        src/cmd_terminate.c
        src/cmd_info_user.c
        src/cmd_info_proc.c)

set(CLIENT_SOURCE_FILES
        client/main.c client/headers.h common.h
        src/commands.h src/clients.h
        client/shm.c     client/shm.h
        client/sem.c     client/sem.h
        client/fifo.c    client/fifo.h
        client/client.c client/client.h)


add_executable(sys-project ${SERVER_SOURCE_FILES})
target_link_libraries(sys-project rt pthread)

add_executable(client ${CLIENT_SOURCE_FILES})
target_link_libraries(client rt pthread)


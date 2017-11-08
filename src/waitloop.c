//
// Created by nuclearcoder on 06/11/17.
//

#include "headers.h"

#include "waitloop.h"
#include "pipes.h"
#include "clients.h"

static const char *pathname;

static void closehook();

void waitloop(const char *p_pathname) {
    pathname = p_pathname;

    create_pipe(pathname);

    // wait for finish to unlink the pipe
    pid_t pid = fork();
    ERRH(pid == -1, "fork", unlink_pipe(pathname))
    if (pid > 0) {
        // parent process
        int stat;
        ERR(wait(&stat), "wait")
        exit(WEXITSTATUS(stat));
    }

    // create hook to unlink the pipe at exit
    ERRH(atexit(closehook) == -1, "atexit_closehook", unlink_pipe(pathname))

    int ret;
    do {
        int pipe = open_pipe(pathname);
        // the call will block until the pipe is opened for write

        puts("Client connected.");

        ret = handle_client(pipe);
        if (ret != CLERR_NONE) {
            perrorcl();
        }

        close_pipe(pipe);

        puts("Client closed.");
    } while (ret != CLERR_TERMINATE); //TODO: maybe add a way to close the daemon

}

static void closehook() {
    unlink_pipe(pathname);
}
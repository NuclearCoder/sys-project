//
// Created by nuclearcoder on 06/11/17.
//

#include "headers.h"

#include "waitloop.h"
#include "pipes.h"
#include "clients.h"

static const char *pathname;

void wait_loop(const char *p_pathname) {
    pathname = p_pathname;

    create_pipe(pathname);

    // wait for finish to unlink the pipe
    pid_t pid = fork();
    ERRH(pid == -1, "fork", unlink_pipe(pathname))
    if (pid > 0) {
        // parent process
        int stat;
        ERR(wait(&stat) == -1, "wait")
        unlink_pipe(pathname);
        exit(WEXITSTATUS(stat));
    }

    /*
     * The client sends an initiate signal with its PID
     * (which is a unique ID during a process lifetime).
     *
     * Then further communications are done through a SHM
     * named after the client PID (for uniqueness)
     */

    int pipe = open_pipe(pathname);

    int ret;
    do {
        ret = handle_client(pipe);
        if (ret == CLERR_NONE) {
            // success
            printf("Success.\n");
        } else {
            perrorcl();
        }

        printf("- Client closed.\n");

        //usleep(100);
    } while (ret != CLERR_TERMINATE);

    close_pipe(pipe);

}

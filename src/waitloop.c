//
// Created by nuclearcoder on 06/11/17.
//

#include "headers.h"

#include "waitloop.h"
#include "pipes.h"
#include "clients.h"

static const char *pathname;

void term(int signum);

void wait_loop(const char *p_pathname) {
    pathname = p_pathname;

    create_pipe(pathname);

    // register signal
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);

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
    } while (ret != CLERR_TERMINATE);

    close_pipe(pipe);

}

void term(int signum) {
    (void) signum;

    unlink_pipe(pathname);
    exit(EXIT_SUCCESS);
}
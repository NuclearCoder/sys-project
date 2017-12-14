//
// Created by nuclearcoder on 06/11/17.
//

#include "../common.h"

#include "waitloop.h"

int main(int argc, char **argv) {
    const char *pathname = "cmdqueue";
    bool silent_flag = false;
    bool daemon_flag = false;

    int c;
    while ((c = getopt(argc, argv, "sdf:")) != -1) {
        switch (c) {
        case 's':
            silent_flag = true;
            break;
        case 'd':
            daemon_flag = true;
            break;
        case 'f':
            pathname = optarg;
            break;
        case '?':
            if (optopt == 'f') {
                fprintf(stderr, "Option -%c requires a file path argument.\n", optopt);
            } else if (isprint(optopt)) {
                fprintf(stderr, "Unknown option '-%c'.\n", optopt);
            } else {
                fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
            }
            return EXIT_FAILURE;
        default:
            abort();
        }
    }

    // if daemon_flag is set to true, fork and end parent process
    if (daemon_flag) {
        switch (fork()) {
        case -1:
            perror("fork");
            return EXIT_FAILURE;
        case 0: // child process
            break;
        default: // parent process
            printf("Running in daemon mode - process will run in background.");
            return EXIT_SUCCESS;
        }
    } else {
        printf("Running in normal mode - process will run in foreground.");
    }
    
    // if silent_flag is set to true, redirect stdout to /dev/null
    if (silent_flag) {
        freopen("/dev/null", "w", stdout);
    }


    wait_loop(pathname);

    return EXIT_SUCCESS;
}

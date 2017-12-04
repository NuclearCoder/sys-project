//
// Created by nuclearcoder on 2017-11-30.
//

#include "../src/commands.h"

#include "client.h"

int main(int argc, char **argv) {
    // read pathname and command from argument
    const char *pathname;
    const char *command;

    pathname = (argc > 1) ? argv[1] : "cmdqueue";

    if (argc > 2) {
        command = argv[2];
    } else {
        command = NAME(TERMINATE);
    }

    run_client(pathname, command);

    return 0;
}

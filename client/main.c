//
// Created by nuclearcoder on 2017-11-30.
//

#include "headers.h"

#include "../src/clients.h"
#include "../src/commands.h"

#include "client.h"

#define CMD_LINE_MAX 128

int main(int argc, char **argv) {
    // read pathname and command from argument
    const char *pathname;
    char *command;

    pathname = (argc > 1) ? argv[1] : "cmdqueue";

    // if there is no argument for a command to run, start in loop mode
    command = (argc > 2) ? argv[2] : NULL;

    if (command != NULL) {
        run_client(pathname, command);
    } else {
        char *command = calloc(CMD_LINE_MAX, sizeof(char));
        size_t size = CMD_LINE_MAX;
        ssize_t n;
        do {
            putchar('>');
            putchar(' ');

            n = getline(&command, &size, stdin);
            if (n == -1) {
                command = "";
            }
            
            if (n >= 1 && command[n - 1] == '\n')
                command[n - 1] = '\0';

            run_client(pathname, command);
        } while (*command != ' ' && *command != '\n' && *command != '\0');
    }

    return 0;
}

//
// Created by nuclearcoder on 06/11/17.
//

#include "headers.h"

#include "waitloop.h"

int main(int argc, char **argv) {
    //read pathname from arguments if there is one
    const char *pathname;
    
    pathname = (argc > 1) ? argv[1] : "cmdqueue";

    wait_loop(pathname);

    return EXIT_SUCCESS;
}

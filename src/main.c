#include "headers.h"

#include "waitloop.h"

int main(int argc, char **argv) {
    //read pathname from arguments if there is one
    const char *name;
    if (argc > 1) name = argv[1]; 
    else          name = "cmdqueue";

    waitloop(name);
    
    return EXIT_SUCCESS;
}

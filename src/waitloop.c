#include "headers.h"

#include "waitloop.h"
#include "pipes.h"

void waitloop(const char *pathname) {
    create_pipe(pathname);

    do {
        int pipe = open_pipe(pathname);
        // the call will block until the pipe is opened for write

        
        
    } while (true); //TODO: maybe add a way to close the daemon
    
}

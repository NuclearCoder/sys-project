#include "headers.h"

int main(void) {
    create_pipe();

    while (wait_for_client()) {
        
    }
}

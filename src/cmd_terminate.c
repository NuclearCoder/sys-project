//
// Created by nuclearcoder on 28/11/17.
//

#include "../common.h"

#include "clients.h"
#include "commands.h"

DEFCMD(TERMINATE) {
    pset(p, 0, "Terminating...");
    
    return CLERR_TERMINATE;
}

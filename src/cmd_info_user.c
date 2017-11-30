//
// Created by nuclearcoder on 30/11/17.
//

#include "headers.h"

#include "clients.h"
#include "commands.h"

DEFCMD(INFO_USER) {
    pset(p, 0, "Info user...");

    return CLERR_NONE;
}

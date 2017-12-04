//
// Created by nuclearcoder on 30/11/17.
//

#include "../common.h"

#include "clients.h"
#include "commands.h"

#define PROC_LINE_MAX 128

DEFCMD(INFO_PROC) {
    /*
     * The request data is a string that parses to an integer,
     * the process ID of which to return information.
     */

    long val = 0;
    char *endptr;

    // strtol requires a null-terminated string,
    // so add it for safety measures
    // (the PID will likely never be long enough to overwrite anything)
    p->data[PACKET_SIZE - 1] = '\0';

    // skip the command name (space)
    char *sstr = p->data + strlen(NAME(TERMINATE)) + 1;

    errno = 0;
    val = strtol(sstr, &endptr, 0);

    // check if parse went well
    if ((errno = ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
        pset(p, 1, "Error: parsing integer failed");
        return CLERR_PARSE_RANGE;
    } else if (endptr == p->data) {
        pset(p, 1, "Error: no integer was found to parse");
        return CLERR_PARSE_NOTHING;
    }

    // here, it means it is an integer
    pid_t pid = (pid_t) val;

    // fetch answer and write it to packet
    size_t len = PROC_LINE_MAX;

    char *buf = calloc(len, sizeof(char));
    ssize_t read;
    FILE *f; // use FILE for getline

    // write the /proc/status filename
    snprintf(buf, len, "/proc/%d/status", pid);
    f = fopen(buf, "r");
    if (f == NULL) {
        pset(p, 1, "Error: could not read process information");
        free(buf);
        return CLERR_NO_INFO;
    }
  
    // reset packet data
    p->data[0] = '\0';

    // read the first 6 lines in the file
    for (int i = 0; i < 6; i++) {
        read = getline(&buf, &len, f);
        if (read == -1) {
            // break without return, don't discard what we already wrote
            break;
        }
        // concat to the packet data
        strncat(p->data, buf, PACKET_SIZE - strlen(p->data) - 1);
    }
    
    fclose(f);
    free(buf);

    p->id = 0;

    return CLERR_NONE;
}


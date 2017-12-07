//
// Created by nuclearcoder on 30/11/17.
//

#include "../common.h"

#include "clients.h"
#include "commands.h"
#include "misc.h"

#define PROC_LINE_MAX 128

DEFCMD(INFO_PROC) {
    /*
     * The request data is a string that parses to an integer,
     * the process ID of which to return information.
     */

    char *sstr;
    pid_t pid;
    int s;

    // strtol requires a null-terminated string,
    // so add it for safety measures
    // (the PID will likely never be long enough to overwrite anything)
    p->data[PACKET_SIZE - 1] = '\0';

    // skip the command name (space)
    sstr = p->data + strlen(NAME(TERMINATE)) + 1;
    
    s = parseint(sstr, &pid);
    if (s == -1) {
        pset(p, -1, "Error: parsing integer failed");
        return CLERR_PARSE_RANGE;
    } else if (s == 1) {
        pset(p, -1, "Error: no integer was found to parse");
        return CLERR_PARSE_NOTHING;
    }

    // fetch answer and write it to packet
    char *buf;
    size_t len;
    ssize_t read;
    FILE *f; // use FILE for getline
    
    len = PROC_LINE_MAX;
    buf = malloc(len);

    // write the /proc/status filename
    snprintf(buf, len, "/proc/%d/status", pid);
    f = fopen(buf, "r");
    if (f == NULL) {
        pset(p, -1, "Error: could not read process information");
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


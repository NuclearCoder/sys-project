//
// Created by nuclearcoder on 30/11/17.
//

#include "../common.h"

#include "clients.h"
#include "commands.h"
#include "misc.h"

// thread-safe getpwuid,
// returns 0 on success,
//        -1 on syscall error,
//         1 if no corresponding uid
int getpwuid_s(uid_t uid, struct passwd *pwd, char *buf, size_t bufsize);

// thread-safe getpwnam,
// returns 0 on success,
//        -1 on syscall error,
//         1 if no corresponding name
int getpwnam_s(const char *name, struct passwd *pwd, char *buf, size_t bufsize);


DEFCMD(INFO_USER) {
    /*
     * The request data is either an integer string,
     * or a user name, set id to 1 if doesn't exist.
     */

    struct passwd pwd;
    char *sstr;
    int val;

    char *buf;
    long bufsize;

    int s;

    // to prevent overflows
    p->data[PACKET_SIZE - 1] = '\0';

    sstr = p->data + strlen(NAME(TERMINATE)) + 1;
    
    s = parseint(sstr, &val);
    if (s == -1) {
        pset(p, -1, "Error: parsing integer failed");
        return CLERR_PARSE_RANGE;
    } else {
        // query the recommended buffer size
        bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
        if (bufsize == -1)
            bufsize = 16384;

        buf = malloc((size_t) bufsize);
        if (buf == NULL) {
            pset(p, -1, "Error: program out of memory");
            return CLERR_USER_FAILED;
        }

        if (s == 0) {
            // if it was an integer, query with UID
            s = getpwuid_s((uid_t) val, &pwd, buf, (size_t) bufsize);
        } else if (s == 1) {
            // if it wasn't an integer, query with name
            s = getpwnam_s(sstr, &pwd, buf, (size_t) bufsize);
        }
        
        if (s == -1) {
            pset(p, -1, "Error: user query failed");
            free(buf);
            return CLERR_USER_FAILED;
        } else if (s == 1) {
            pset(p, -1, "Error: no such user found");
            free(buf);
            return CLERR_NO_INFO;
        }
    }

    // from this point, pwd contains a valid passwd struct

    // set maximum lengths of each line, for overflow checking
    size_t lengths[6] = {
        10 + strlen(pwd.pw_name),
        20,
        20,
        10 + strlen(pwd.pw_gecos),
        10 + strlen(pwd.pw_dir),
        10 + strlen(pwd.pw_shell)
    };

    // reset data
    p->data[0] = '\0';

#define writeline(i, str, arg) \
    do { \
        snprintf(p->data, PACKET_SIZE, str, arg); \
        increpif(p, sem, strlen(p->data) + lengths[i] <= PACKET_SIZE); \
    } while (true);

    writeline(0, "User:   %s\n", pwd.pw_name);
    writeline(1, "UID:    %d\n", pwd.pw_uid);
    writeline(2, "GID:    %d\n", pwd.pw_gid);
    writeline(3, "Name:   %s\n", pwd.pw_gecos);
    writeline(4, "Home:   %s\n", pwd.pw_dir);
    writeline(5, "Shell:  %s\n", pwd.pw_shell);
    
    free(buf);

    p->id = 0;

    return CLERR_NONE;
}


int getpwuid_s(uid_t uid, struct passwd *pwd, char *buf, size_t bufsize) {
    struct passwd *result;

    int s = getpwuid_r(uid, pwd, buf, bufsize, &result);

    if (result == NULL) {
        if (s == 0) {
            return 1;
        } else {
            errno = s;
            return -1;
        }
    }

    return 0;
}

int getpwnam_s(const char *name, struct passwd *pwd, char *buf, size_t bufsize) {
    struct passwd *result;

    int s = getpwnam_r(name, pwd, buf, bufsize, &result);

    if (result == NULL) {
        if (s == 0) {
            return 1;
        } else {
            errno = s;
            return -1;
        }
    }

    return 0;
}

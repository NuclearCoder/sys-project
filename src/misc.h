//
// Created by nuclearcoder on 08/11/17.
//

#ifndef SYS_PROJECT_MISC_H
#define SYS_PROJECT_MISC_H

/* Reads exactly LEN bytes, not less as read(2). Returns -1 on error, 0 on success, 1 on EOF. */
int exactread(int fd, void *buf, size_t len);

#endif //SYS_PROJECT_MISC_H

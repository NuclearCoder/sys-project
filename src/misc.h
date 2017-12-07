//
// Created by nuclearcoder on 08/11/17.
//

#ifndef SYS_PROJECT_MISC_H
#define SYS_PROJECT_MISC_H

/* Reads exactly LEN bytes, not less as read(2). Returns -1 on error, 0 on success, 1 on EOF. */
int exact_read(int fd, void *buf, size_t len);

/* Compares two strings until a space character is found (null-terminated)  */
bool strsnequ(const char *s1, const char *s2, size_t n);

/* Parses an integer from a string. Returns -1 on error, 0 on success, 1 if not an integer. */
int parseint(const char *str, int *nptr);

#endif //SYS_PROJECT_MISC_H

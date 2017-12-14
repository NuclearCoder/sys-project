//
// Created by nuclearcoder on 08/11/17.
//

#ifndef SYS_PROJECT_COMMANDS_H
#define SYS_PROJECT_COMMANDS_H

/* need deeper level macro to expand twice */

#define __PC_DEF(c)      int fndef_##c (struct packet *p, sem_t *sem)
#define __PC_IS(c, map)    (strsnequ((map)->p.data, NAME(c), PACKET_SIZE) == true)
#define __PC_CALL(c, map)  fndef_##c (&(map)->p, &(map)->sem)
#define __PC_NAME(c)     #c

/* the string name of a command */
#define NAME(c)          __PC_NAME(c)

/* function definition for a command */
#define DEFCMD(c)        __PC_DEF(c)

/* boolean expression to test if a packet corresponds to a command */
#define iscmd(c, map)      __PC_IS(c, map)
/* shorthand for if (iscmd), can be chained like regular if */
#define ifcmd(c, map)      if (iscmd(c, map))

/* call site for a command function */
#define callcmd(c, map)    __PC_CALL(c, map)
/* shorthand for ifcmd callcmd, can be chained like regular if */
#define callcmdif(c, map)  ifcmd(c, map) callcmd(c, map)


// commands:

/* Terminates the daemon. */
#define TERMINATE        terminate

/* Returns information on a user. */
#define INFO_USER        info_user

/* Returns information on a process. */
#define INFO_PROC        info_proc

DEFCMD(TERMINATE);
DEFCMD(INFO_USER);
DEFCMD(INFO_PROC);


#endif //SYS_PROJECT_COMMANDS_H

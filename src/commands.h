//
// Created by nuclearcoder on 08/11/17.
//

#ifndef SYS_PROJECT_COMMANDS_H
#define SYS_PROJECT_COMMANDS_H

/* need deeper level macro to expand twice */

#define __PC_DEF(c)      int fndef_##c (struct packet *p)
#define __PC_IS(c, p)    (strncmp((p)->data, NAME(c), PACKET_SIZE) == 0)
#define __PC_CALL(c, p)  fndef_##c (p)
#define __PC_NAME(c)     #c

/* the string name of a command */
#define NAME(c)          __PC_NAME(c)

/* function definition for a command */
#define DEFCMD(c)        __PC_DEF(c)

/* boolean expression to test if a packet corresponds to a command */
#define iscmd(c, p)      __PC_IS(c, p)
/* shorthand for if (iscmd), can be chained like regular if */
#define ifcmd(c, p)      if (iscmd(c, p))

/* call site for a command function */
#define callcmd(c, p)    __PC_CALL(c, p)
/* shorthand for ifcmd callcmd, can be chained like regular if */
#define callcmdif(c, p)  ifcmd(c, p) callcmd(c, p)


// commands:

/* Terminates the daemon. */
#define TERMINATE        term

DEFCMD(TERMINATE);


#endif //SYS_PROJECT_COMMANDS_H

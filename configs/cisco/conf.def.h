/* 
replace your conf.def.h with this file 
(ofc you need to call this file also conf.def.h) 
*/
#include <stdlib.h>

#include "common.h"
#include "actions.h"

/* 
define what function to call in case of error (advance)
*/
#define ON_ERROR_FUNC on_error


/* unsafe, macros that are used outside this file */
#define ANY_LEVEL -1


/* safe,, macros that can be deleted or overwritten, only used in this file */
#define CONSOLE_LEVEL 0
#define EXEC_LEVEL 1
#define CONFIG_LEVEL 2

#define HOSTNAME "cisco-dumbdevice"
#define SESSION_INIT_PPROMP HOSTNAME ">"


/* alias */
/* simple alias to create a new session */
#define NEW_SESSION_PROMPT_LVL(lvl, str_, prompt) { \
        .level=lvl, \
        .str=str_, \
        .actions={ &save_session, &set_prompt, &set_session_level, NULL }, \
        .args={   {0},            {.v=prompt}, {.i=lvl+1} } \
    } 
/* simple alias to read from a file as a command executed */
#define RD_ON_EXEC(lvl, str_, file) { \
        .level=lvl, \
        .str=str_, \
        .actions={ &rd_file, NULL }, \
        .args={ {.v=file} } \
    }


/* configure device commands */
static Command commands[] = {
    NEW_SESSION_PROMPT_LVL(CONSOLE_LEVEL, "enable",  HOSTNAME "#"),
    NEW_SESSION_PROMPT_LVL(EXEC_LEVEL, "config",  HOSTNAME "(config)#"),
    RD_ON_EXEC(EXEC_LEVEL, "show ip interface brief", "./interfaces.txt"),
    RD_ON_EXEC(EXEC_LEVEL, "show ip route", "./routes.txt"),
    { 
        .level=ANY_LEVEL,  
        .str="exit",
        .actions={ &exit_session, NULL },
        .args={ {.i=0} }                  
    },
};


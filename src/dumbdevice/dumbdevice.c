#include <string.h>

#include "io.h"
#include "common.h"
#include "actions.h"
#include "conf.h"


#define COMMANDS_LEN(cmds) (sizeof(cmds) / sizeof(Command))


static int device_error = 0;

Session session_history[MAX_SESSION_HISTORY];
Session *session = session_history; // by default points to the first element 


/* 
find a command based on the searched string, 
if not found, return NULL and set device_error to the correct error
*/
Command * find_cmd_match(const char *str, size_t str_size)
{
    Command *cmd = NULL, *current_cmd = NULL;
    int i = 0;

    for(; i < COMMANDS_LEN(commands); i++){
        current_cmd = &commands[i];
        
        if( // if found a matching command with the same level as the session level
            (strncmp(str, current_cmd->str, str_size) == 0) &&
            (current_cmd->level == ANY_LEVEL || current_cmd->level == session->level)
        )
            cmd = current_cmd;
    }

    if(cmd == NULL)
        device_error = ERROR_CMD_NOT_FOUND;
    return cmd;
}

/* execute all the given command actions */
void execute_command(Command *cmd)
{
    CommandAction *action = cmd->actions;
    Arg *arg = NULL;
    int i = 0;

    for(;*action != NULL; action++, i++){
        arg = &cmd->args[i];
        (*action)(arg, cmd);
    }
}

/* opens the main command prompt */
void shell()
{
    char inpbuff[DEVICE_MAX_OUTPUT];
    Command *cmd = NULL;
    size_t inplen = 0;

    while(!session->eof){
        inplen = input(session->prompt, inpbuff, sizeof(inpbuff));
        inplen = strip(inpbuff, inplen, inpbuff);

        if(inplen <= 0)
            continue;

        cmd = find_cmd_match(inpbuff, inplen);
        
        if(cmd == NULL)
            ON_ERROR_FUNC(NULL, inpbuff, device_error);
        else
            execute_command(cmd);
    }
}

/* initiat the first session */
void init_session()
{
    session->prompt = SESSION_INIT_PPROMP;
    session->level = 0;
    session->eof = 0;
}

int main(int argc, char *argv[])
{
    init_session();
    shell();
}

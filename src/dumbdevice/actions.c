/*
Copyright 2023 dsal3389@gmail.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
all actions that can be used by the Commands should be defined here
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "common.h"
#include "io.h"


/* save the current session in the session history and create a new replica */
int save_session(const Arg *arg, ...)
{
    size_t session_history_len = session - session_history;

    if(session_history_len >= MAX_SESSION_HISTORY){
        write_screen(
            LOG_ERROR("save_session", "max session save acceded, configured %d\n"), MAX_SESSION_HISTORY
        );
        return 1;
    }

    memcpy(session+1, session, sizeof(Session));
    session++; 
    return 0;
}

/* change the current session prompt */
int set_prompt(const Arg *arg, ...)
{
    session->prompt = arg->v;
    return 0;
}

/* echos the given string to the screen */
int echo(const Arg *arg, ...)
{
    write_screen("%s", (char*) (arg->v));
    return 0;
}

/* read from a given file */
int rd_file(const Arg *arg, ...)
{
    int lr=0, fd = open(arg->v, O_RDONLY);
    char buffer[1024];

    if(fd == -1){
        write_screen(LOG_ERROR("open", "could not open file %s"), arg->v);
        goto END;
    }

    while((lr=read(fd, buffer, sizeof(buffer))) > 0){
        buffer[lr] = 0;
        write_screen(buffer);
    }

    if(lr == -1)
        write_screen(LOG_ERROR("read", "failed reading file %s"), arg->v);

END:
    close(fd);
    return 0;
}

/* goes back 1 session in the session history, if there are no session, it will exit the process */
int exit_session(const Arg *arg, ...)
{
    // if the current session is the last on the session stack
    if(session == session_history)
        exit(arg->i);
    session--;
    return 0;
}

int password_prompt(const Arg *arg, ...)
{
    const char *password = (char *) arg->v;
    char buffer[1024];

    write(STDOUT_FILENO, "password: ", 10);
    read(STDIN_FILENO, buffer, sizeof(buffer));
    return !strncmp(password, buffer, sizeof(buffer));
}

/* change the current session execution commands level */
int set_session_level(const Arg *arg, ...)
{
    session->level = arg->i;
    return 0;
}

int alias(const Arg *arg, ...)
{
    // need to implement
}

/* default error handler, defined in cond.def.h as ON_ERROR_FUNC macro */
void on_error(const Arg *arg, ...)
{
    int error_code;
    const char *cmd_str;
    va_list args;

    va_start(args, 2);
    
    cmd_str = va_arg(args, const char *);
    error_code = va_arg(args, int);

    switch(error_code){
        case ERROR_CMD_NOT_FOUND:
            write_screen("command not found::%s\n", cmd_str);
            break;

        default:
            write_screen("unknown error code %x\n", error_code);
            break;
    }

    va_end(args);
}

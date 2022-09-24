#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

#include "common.h"
#include "io.h"


void save_session(const Arg *arg, ...)
{
    size_t session_history_len = session - session_history;

    if(session_history_len >= MAX_SESSION_HISTORY){
        write_screen(
            LOG_ERROR("save_session", "max session save acceded, configured %d\n"), MAX_SESSION_HISTORY
        );
        return;
    }

    memcpy(session+1, session, sizeof(Session));
    session++; 
}

void set_prompt(const Arg *arg, ...)
{
    session->prompt = arg->v;
}

void echo(const Arg *arg, ...)
{
    write_screen("%s", (char*) (arg->v));
}

void rd_file(const Arg *arg, ...)
{
    int lr=0, fd = open(arg->v, O_RDONLY);
    char buffer[1024];

    if(fd == -1){
        write_screen(LOG_ERROR("open", "could not open file %s"), arg->v);
        goto END;
    }

    while((lr=read(fd, buffer, sizeof(buffer))) > 0)
        write_screen(buffer);

    if(lr == -1)
        write_screen(LOG_ERROR("read", "failed reading file %s"), arg->v);

END:
    close(fd);
}

void exit_session(const Arg *arg, ...)
{
    // if the current session is the last on the session stack
    if(session == session_history)
        exit(arg->i);
    session--;
}

void set_session_level(const Arg *arg, ...)
{
    session->level = arg->i;
}

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

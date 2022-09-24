/*
not a real header file, only used in dumbdevice.c, 
this file has a .h ending so the preprocessor will include 
the file content in dumbdevice.c

this file contains all the allowed actions that should be used
in Command
*/
#ifndef _ACTIONS_H_
#define _ACTIONS_H_ 1
#include "common.h"


extern void echo(const Arg *, ...);
extern void rd_file(const Arg *, ...);
extern void exit_session(const Arg *, ...);
extern void save_session(const Arg *, ...);
extern void set_prompt(const Arg *, ...);
extern void set_session_level(const Arg *, ...);
extern void on_error(const Arg *, ...);


#endif

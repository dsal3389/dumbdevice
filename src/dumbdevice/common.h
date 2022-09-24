#ifndef _COMMON_H_
#define _COMMON_H_ 1


#ifndef _MAX_CMD_ACTIONS
    #define _MAX_CMD_ACTIONS 10
#endif

#ifndef MAX_SESSION_HISTORY
    #define MAX_SESSION_HISTORY 12
#endif

#define ERROR_CMD_NOT_FOUND 0x1


typedef union{
    void * v;
    int i;
} Arg;

typedef void (*CommandAction)(const Arg*, ...);

typedef struct{
    char *str;
    Arg args[_MAX_CMD_ACTIONS]; // amoount of args should be the same as the amount of actionss
    CommandAction actions[_MAX_CMD_ACTIONS];
    int level;
} Command;

typedef struct{
    int eof;
    int level;
    char *prompt;
} Session;


extern Session session_history[];
extern Session *session;


#endif 

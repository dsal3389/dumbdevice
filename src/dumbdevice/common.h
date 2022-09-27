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
#ifndef _COMMON_H_
#define _COMMON_H_ 1


#ifndef _MAX_CMD_ACTIONS
    #define _MAX_CMD_ACTIONS 10
#endif

#ifndef MAX_SESSION_HISTORY
    #define MAX_SESSION_HISTORY 12
#endif

#define ERROR_CMD_NOT_FOUND 0x1


enum throttle { slow, normal, disabled };

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
    enum throttle t;
    char *prompt;
} Session;


extern Session session_history[];
extern Session *session;


#endif 

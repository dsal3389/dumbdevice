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
#ifndef _ACTIONS_H_
#define _ACTIONS_H_ 1
#include "common.h"


extern int echo(const Arg *, ...);
extern int rd_file(const Arg *, ...);
extern int exit_session(const Arg *, ...);
extern int save_session(const Arg *, ...);
extern int set_prompt(const Arg *, ...);
extern int password_prompt(const Arg *, ...);
extern int set_session_level(const Arg *, ...);
extern int alias(const Arg *, ...);
extern int on_error(const Arg *, ...);


#endif

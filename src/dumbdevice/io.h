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
#ifndef _IO_H_
#define _IO_H_ 1

#include <stdlib.h>
#include <string.h>
#include <errno.h>

// macros used for fatal and write_screen functinos
#define LOG_ERRNO(op) "error::" op "::%s", strerror(errno)
#define LOG_ERROR(op, msg) "error::" op "::" msg "\n"

#ifndef DEVICE_MAX_OUTPUT
    #define DEVICE_MAX_OUTPUT 1024
#endif

#ifndef DEVICE_MAX_INPUT
    #define DEVICE_MAX_INPUT MAX_INPUT
#elif DEVICE_MAX_INPUT > MAX_INPUT
    # error MAX_INPUT cannot be greater then linux limit MAX_INPUT
#endif


extern void fatal(const char *, ...);
extern void write_screen(const char *, ...);
extern size_t input(const char *, void *, size_t);
extern size_t strip(char *, size_t, char *);


#endif

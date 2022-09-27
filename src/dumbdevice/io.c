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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <time.h>

#include "common.h"
#include "io.h"

/* max and min time alllowed to wait between every cooldown (in seconds) */
#define MIN_THROTTLE_TIME 1
#define MAX_THROTTLE_TIME 3

/* minimum number of chars that are allowed to be written to screen */
#define MIN_THROTTLE_RD_COUNT 6


static void write_throttled(const char *str, size_t str_len, unsigned int chance)
{
    int rand_num = 0,
        rd_chunk = 0,
        rd_count = 0;
    
    if(str_len <= MIN_THROTTLE_RD_COUNT){
        write(STDOUT_FILENO, str, str_len);
        return;
    }

    srand(time(NULL));
    rd_chunk = (rand() % str_len) + MIN_THROTTLE_RD_COUNT;

    while(rd_count < str_len){
        rand_num = rand() % 100;

        if(rand_num > chance)
            sleep((rand() % MAX_THROTTLE_TIME) + MIN_THROTTLE_TIME);

        // mean we are about to read the last chunk from the string,
        // so we need to get all the left chars 
        if(rd_count + rd_chunk > str_len)
            rd_chunk = str_len - rd_count;

        write(STDOUT_FILENO, str+rd_count, rd_chunk);
        rd_count += rd_chunk;
    }
}

/*
will output the string based on the configured throttle time
*/
void write_screen(const char *fmt, ...)
{
    char buff[DEVICE_MAX_OUTPUT];
    size_t outputted = 0;
    va_list args;

    va_start(args, fmt);
    outputted = vsnprintf(buff, sizeof(buff)-1, fmt, args);
    buff[outputted] = 0;
    va_end(args);

    switch(session->t){
        case disabled:
            write(STDOUT_FILENO, buff, outputted);
            break;

        case slow:
            write_throttled(buff, outputted, 30);
            break;

        case normal:
            write_throttled(buff, outputted, 90);
            break;
    }
}

/* read input from stdin and prompt the user with the given prompt */
size_t input(const char *prompt, void *buff, size_t buff_size)
{
    size_t read_len;

    write_screen(prompt);
    read_len = read(STDIN_FILENO, buff, buff_size);

    if(read_len < 0)
        fatal(LOG_ERRNO("read STDIN"));

    // set null terminator instead of \n
    ((char*) buff)[read_len - 1] = 0;
    return --read_len;
}

/*
strip the given string from spaces, strip it on the left and on the right,
the str_len is not including the NULL terminator
*/
size_t strip(char *str, size_t str_len, char *buff)
{
    char *start=str, *end=&str[str_len];
    size_t new_len = 0;

    while(*start == ' ')
        start++;

    while((*end == ' ' || *end == 0) && end >= start)
        end--;

    *++end = 0;
    new_len = end - start;

    if(end > start)
        // take take the start (points to the first char that is not ' '), move all "new_len"
        // bytes to the str
        memmove(str, start, new_len + 1);
    return new_len;
}

/* display an error message and exit the process */
void fatal(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}
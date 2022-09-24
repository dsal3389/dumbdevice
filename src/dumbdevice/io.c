#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include "io.h"


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
    va_end(args);

    // TODO: implement throttle
    write(STDOUT_FILENO, buff, outputted);
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
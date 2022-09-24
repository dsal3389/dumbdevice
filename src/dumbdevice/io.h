#ifndef _IO_H_
#define _IO_H_ 1

#include <stdlib.h>
#include <string.h>
#include <errno.h>


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

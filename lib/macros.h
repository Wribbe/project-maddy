#ifndef MAD_MACROS_H
#define MAD_MACROS_H

#include <stdlib.h>
#include <stdio.h>

#define MAD_LEN(x) sizeof(x)/sizeof(x[0])

#define FATAL(fmt, ...) do { printf("FATAL: "fmt"\n", __VA_ARGS__); exit(EXIT_FAILURE); } while(0)

#endif

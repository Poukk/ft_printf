#ifndef TEST_FT_PRINTF
#define TEST_FT_PRINTF
#define BUFFER_SIZE 1024

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "unity/unity.h"
#include "../include/ft_printf.h"
#include "unity/unity_internals.h"

int capture_output(char *buffer, size_t size, int (*print_func)(const char *, ...), const char *format, ...);

#endif

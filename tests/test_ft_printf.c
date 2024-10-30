#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "unity/unity.h"
#include "../include/ft_printf.h"

#define BUFFER_SIZE 1024

void setUp(void) {}

void tearDown(void) {}

static int capture_output(char *buffer, size_t size, int (*print_func)(const char *, ...), const char *format, ...) {
    int backup_stdout = dup(STDOUT_FILENO);
    int pipefd[2];
    pipe(pipefd);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    va_list args;
    va_start(args, format);
    int result;
    if (print_func == printf) {
        result = vprintf(format, args);
    } else {
        result = ft_printf(format, "World");
    }
    va_end(args);

    fflush(stdout);
    dup2(backup_stdout, STDOUT_FILENO);
    close(backup_stdout);

    ssize_t bytes_read = read(pipefd[0], buffer, size - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
    } else {
        buffer[0] = '\0';
    }
    close(pipefd[0]);

    return result;
}

void test_ft_printf_basic(void) {
    char expected[BUFFER_SIZE] = {0};
    char actual[BUFFER_SIZE] = {0};
    int expected_len, actual_len;

    expected_len = capture_output(expected, BUFFER_SIZE, printf, "Hello, %s!", "World");
    actual_len = capture_output(actual, BUFFER_SIZE, ft_printf, "Hello, %s!", "World");

    printf("Expected: '%s' (len: %d)\n", expected, expected_len);
    printf("Actual  : '%s' (len: %d)\n", actual, actual_len);

    TEST_ASSERT_EQUAL_STRING(expected, actual);
    TEST_ASSERT_EQUAL_INT(expected_len, actual_len);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ft_printf_basic);
    return UNITY_END();
}

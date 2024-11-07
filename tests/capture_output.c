#include "test_ft_printf.h"

int capture_output(char *buffer, size_t size, int (*print_func)(const char *, ...), const char *format, ...) {
    int backup_stdout;
    int pipefd[2];
    int result;
    va_list args;

    if ((backup_stdout = dup(STDOUT_FILENO)) == -1)
        return -1;
    if (pipe(pipefd) == -1) {
        close(backup_stdout);
        return -1;
    }
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        close(backup_stdout);
        close(pipefd[0]);
        close(pipefd[1]);
        return -1;
    }

    va_start(args, format);
    if (print_func == printf)
        result = vprintf(format, args);
    else
    {
        result = vft_printf(format, args);
	va_end(args);
    }

    fflush(stdout);
    if (dup2(backup_stdout, STDOUT_FILENO) == -1) {
        result = -1;
    }
    close(backup_stdout);
    close(pipefd[1]);

    ssize_t bytes_read = read(pipefd[0], buffer, size - 1);
    if (bytes_read > 0)
        buffer[bytes_read] = '\0';
    else
        buffer[0] = '\0';

    close(pipefd[0]);
    return (bytes_read >= 0) ? result : -1;
}

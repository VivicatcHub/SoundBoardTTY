/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** file_gestion_fc.c
*/

#include "help_fc.h"

static char *open_file_result(int fd, char *result, struct stat *buffer)
{
    ssize_t bytes_read;

    bytes_read = read(fd, result, buffer->st_size);
    if (bytes_read != buffer->st_size) {
        close(fd);
        free(result);
        return ERROR_STR;
    }
    result[buffer->st_size] = '\0';
    close(fd);
    return result;
}

char *open_file(char *file)
{
    int fd = open(file, O_RDONLY);
    struct stat buffer;
    char *result;

    if (fd == -1)
        return ERROR_STR;
    if (stat(file, &buffer) == -1) {
        close(fd);
        return ERROR_STR;
    }
    if (buffer.st_size == 0) {
        close(fd);
        return ERROR_STR;
    }
    result = emalloc(buffer.st_size + 1);
    if (!result) {
        close(fd);
        return ERROR_STR;
    }
    return open_file_result(fd, result, &buffer);
}

int size_of_file(char *file)
{
    int fd = open(file, O_RDONLY);
    char buf[4096];
    int result = 0;
    ssize_t bytes_read;

    if (fd == -1)
        return -1;
    bytes_read = read(fd, buf, 1);
    while (bytes_read > 0) {
        result++;
        bytes_read = read(fd, buf, 1);
    }
    if (bytes_read == -1) {
        close(fd);
        return -1;
    }
    close(fd);
    return result;
}

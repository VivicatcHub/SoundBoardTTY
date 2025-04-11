#include "header.h"

char *get_absolute_path(const char *path)
{
    char *absolute_path =
        realpath(path, NULL);

    return absolute_path;
}

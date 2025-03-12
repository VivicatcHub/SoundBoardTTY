#include "header.h"

char *get_absolute_path(const char *path)
{
    char *absolute_path =
        realpath(path, NULL);
    if (absolute_path == NULL)
        return NULL;
    return absolute_path;
}

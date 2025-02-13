/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** error_handling_fc.c
*/

#include "help_fc.h"

void *emalloc(size_t w)
{
    void *ret;

    ret = malloc(w);
    if (!ret)
        my_puterror("Error with malloc\n");
    return ret;
}

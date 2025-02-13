/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** test_str_fc.c
*/

#include "help_fc.h"

int my_str_isalpha(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!IS_ALPHABETICAL(str[i]))
            return FALSE;
    return TRUE;
}

int my_str_islower(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (IS_UPPER(str[i]))
            return FALSE;
    return TRUE;
}

int my_str_isupper(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (IS_LOWER(str[i]))
            return FALSE;
    return TRUE;
}

int my_str_isnum(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!IS_NUMERICAL(str[i]))
            return FALSE;
    return TRUE;
}

int my_str_isprintable(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!IS_PRINTABLE(str[i]))
            return FALSE;
    return TRUE;
}

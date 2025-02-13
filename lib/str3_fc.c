/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** str3_fc.c
*/

#include "help_fc.h"

char *my_strcapitalize(char *str)
{
    int espace = 0;

    if (!str)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (IS_LOWER(str[i]) && espace == 0)
            str[i] = UPPER(str[i]);
        if (IS_UPPER(str[i]) && espace != 0)
            str[i] = LOWER(str[i]);
        if (!IS_ALPHABETICAL(str[i]) && !IS_NUMERICAL(str[i]))
            espace = 0;
        else
            espace++;
    }
    return str;
}

char *my_strlowcase(char *str)
{
    if (!str)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++)
        if (IS_UPPER(str[i]))
            str[i] = LOWER(str[i]);
    return str;
}

char *my_strupcase(char *str)
{
    if (!str)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++)
        if (IS_LOWER(str[i]))
            str[i] = UPPER(str[i]);
    return str;
}

char *my_strstr(char *str, char const *to_find)
{
    int j = 0;
    int trouve = 0;

    if (!str || !to_find || to_find[0] == '\0')
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (to_find[j] == '\0')
            return &str[trouve];
        if (str[i] == to_find[j]) {
            trouve = (j == 0 ? i : trouve);
            j++;
        } else
            j = 0;
    }
    return NULL;
}

/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** str_fc.c
*/

#include "help_fc.h"

int my_strlen(char *str)
{
    int result = 0;

    if (!str)
        return 0;
    while (str[result] != '\0')
        result++;
    return result;
}

char *my_revstr(char *str)
{
    char temp;
    int i;

    if (!str)
        return NULL;
    i = my_strlen(str) - 1;
    for (int m = 0; m < i; m++) {
        temp = str[m];
        str[m] = str[i];
        str[i] = temp;
        i--;
    }
    return str;
}

char *my_strdup(char *str)
{
    int len;
    char *result;

    if (!str)
        return NULL;
    len = my_strlen(str);
    result = emalloc(sizeof(char) * (len + 1));
    if (!result)
        return NULL;
    for (int i = 0; i <= len; i++)
        result[i] = str[i];
    return result;
}

int my_strcmp(char *str1, char *str2)
{
    if (!str1 || !str2) {
        if (str1 == str2)
            return 0;
        else
            return str1 ? 1 : -1;
    }
    for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
        if (str1[i] != str2[i])
            return str1[i] - str2[i];
    return 0;
}

int my_strcontain(char *str, char c)
{
    if (!str)
        return FALSE;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            return TRUE;
    return FALSE;
}

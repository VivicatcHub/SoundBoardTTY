/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** strn_fc.c
*/

#include "help_fc.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int dest_len = my_strlen(dest);
    int i;

    for (i = 0; i < nb && src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';
    return dest;
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while (i < n && s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    if (i == n || (s1[i] == '\0' && s2[i] == '\0'))
        return 0;
    return (s1[i] - s2[i]);
}

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    for (; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}

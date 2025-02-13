/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** str2_fc.c
*/

#include "help_fc.h"

char *str_to_str(char *str1, char *str2)
{
    int len1;
    int len2;
    int i = 0;
    char *result;

    if (!str1 || !str2)
        return NULL;
    len1 = my_strlen(str1);
    len2 = my_strlen(str2);
    result = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!result)
        return NULL;
    for (; i < len1; i++)
        result[i] = str1[i];
    for (int j = 0; j < len2; j++) {
        result[i] = str2[j];
        i++;
    }
    result[i] = '\0';
    return result;
}

void replace(char *str, char c, char new_c)
{
    if (!str)
        return;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            str[i] = new_c;
}

char *my_strcat(char *dest, char const *src)
{
    if (!dest || !src)
        return NULL;
    my_strcpy(dest + my_strlen(dest), src);
    return dest;
}

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if (!dest || !src)
        return NULL;
    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

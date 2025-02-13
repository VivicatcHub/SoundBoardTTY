/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** display2_fc.c
*/

#include "help_fc.h"

static void display_spe(char *str)
{
    my_putchar('\\');
    for (int j = 0; str[j] != '\0'; j++) {
        if (IS_UPPER(str[j]))
            my_putchar(LOWER(str[j]));
        else
            my_putchar(str[j]);
    }
}

void my_showstr(char const *str)
{
    char *tohex;

    for (int i = 0; str[i] != '\0'; i++)
        if (IS_PRINTABLE(str[i]))
            my_putchar(str[i]);
        else {
            tohex = dec_to_hex(str[i]);
            if (tohex) {
                display_spe(tohex);
                free(tohex);
            }
        }
}

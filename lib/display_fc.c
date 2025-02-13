/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** display_fc.c
*/

#include "help_fc.h"

int my_putstr(char *str)
{
    if (!str)
        return ERROR;
    return write(1, str, my_strlen(str));
}

int my_putchar(char c)
{
    return write(1, &c, 1);
}

int my_putnbr(int nb)
{
    char *to_print = int_to_str(nb);
    int result;

    if (to_print == ERROR_STR)
        return ERROR;
    result = my_putstr(to_print);
    free(to_print);
    return result;
}

int my_puterror(char *error)
{
    if (!error)
        return ERROR;
    return write(2, error, my_strlen(error));
}

int my_put_nbr_float(double nb, int prec)
{
    char *to_print = float_to_str(nb, prec);
    int result;

    if (to_print == ERROR_STR)
        return ERROR;
    result = my_putstr(to_print);
    free(to_print);
    return result;
}

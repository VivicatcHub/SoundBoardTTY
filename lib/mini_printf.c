/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** mini_printf.c
*/

#include "help_fc.h"

static int display_mini_printf(char *str, va_list args, int *i)
{
    (*i)++;
    switch (str[*i]) {
        case 'c':
            return my_putchar(va_arg(args, int));
        case 's':
            return my_putstr(va_arg(args, char *));
        case 'd':
        case 'i':
            return my_putnbr(va_arg(args, int));
        case '%':
            return my_putchar('%');
        default:
            (*i)--;
            return my_putchar('%');
    }
}

int mini_printf(char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%')
            count += display_mini_printf(format, args, &i);
        else {
            my_putchar(format[i]);
            count++;
        }
    }
    va_end(args);
    return count;
}

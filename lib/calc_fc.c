/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** calc_fc.c
*/

#include "help_fc.h"

int my_compute_factorial(int nb)
{
    if (nb < 0 || nb > 12)
        return 0;
    if (nb == 0)
        return 1;
    return nb * my_compute_factorial(nb - 1);
}

int my_compute_power(int nb, int p)
{
    if (p < 0)
        return 0;
    if (p == 0)
        return 1;
    if (p == 1)
        return nb;
    if (nb == 0)
        return 0;
    return nb * my_compute_power(nb, p - 1);
}

int my_compute_square_root(int nb)
{
    if (nb < 0)
        return 0;
    for (int i = 0; i * i <= nb; i++)
        if (i * i == nb)
            return i;
    return 0;
}

int my_is_prime(int nb)
{
    if (nb < 2)
        return FALSE;
    for (int i = 2; i * i <= nb; i++)
        if (nb % i == 0)
            return FALSE;
    return TRUE;
}

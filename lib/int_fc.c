/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** int_fc.c
*/

#include "help_fc.h"

int size_of_int(long long int nb)
{
    int count = 0;

    if (nb == 0)
        return 1;
    if (nb < 0) {
        nb *= -1;
        count++;
    }
    for (int i = 0; nb != 0; i++) {
        count++;
        nb /= 10;
    }
    return count;
}

void my_swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}

/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** int_array_fc.c
*/

#include "help_fc.h"

void my_sort_int_array(int *array, int size)
{
    int temp;
    int j;

    if (!array || size <= 1)
        return;
    for (int i = 0; i < size; i++) {
        temp = array[i];
        j = i;
        while (j > 0 && array[j - 1] > temp) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = temp;
    }
}

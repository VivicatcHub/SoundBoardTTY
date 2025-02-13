/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** base_fc.c
*/

#include "help_fc.h"

char *dec_to_hex(int nb)
{
    int i = 0;
    int temp;
    char *hexa;

    if (nb < 0)
        return ERROR_STR;
    hexa = emalloc(sizeof(char) * 9 + 1);
    if (!hexa)
        return ERROR_STR;
    if (nb == 0) {
        hexa[i] = '0';
        i++;
    }
    for (; nb != 0; i++) {
        temp = nb % 16;
        hexa[i] = (temp < 10) ? STR(temp) : (temp + 'A' - 10);
        nb /= 16;
    }
    hexa[i] = '\0';
    return my_revstr(hexa);
}

static int is_valid_base_result(char const *base, int len, int i)
{
    for (int j = i + 1; j < len; j++)
        if (base[i] == base[j])
            return FALSE;
    return TRUE;
}

static int is_valid_base(char const *base)
{
    int len = my_strlen((char *) base);

    if (len < 2)
        return FALSE;
    for (int i = 0; i < len; i++) {
        if (base[i] == '+' || base[i] == '-')
            return FALSE;
        if (!is_valid_base_result(base, len, i))
            return FALSE;
    }
    return TRUE;
}

static void putnbr_base_recursive(int nbr, char const *base, int base_len)
{
    if (nbr <= -(base_len) || nbr >= base_len)
        putnbr_base_recursive(nbr / base_len, base, base_len);
    my_putchar(base[(nbr < 0 ? -(nbr % base_len) : (nbr % base_len))]);
}

int my_putnbr_base(int nbr, char const *base)
{
    int base_len = my_strlen((char *) base);

    if (!is_valid_base(base))
        return FALSE;
    if (nbr < 0)
        my_putchar('-');
    putnbr_base_recursive(nbr, base, base_len);
    return TRUE;
}

static int get_index_in_base(char c, char const *base)
{
    for (int i = 0; base[i] != '\0'; i++)
        if (base[i] == c)
            return i;
    return -1;
}

static int handle_sign(char const *str, int *index)
{
    int sign = 1;

    while (str[*index] == '+' || str[*index] == '-') {
        if (str[*index] == '-')
            sign *= -1;
        (*index)++;
    }
    return sign;
}

int my_getnbr_base(char const *str, char const *base)
{
    int base_len = my_strlen((char *) base);
    int index = 0;
    int sign;
    int result = 0;
    int digit;

    if (!is_valid_base(base) || str == NULL)
        return 0;
    sign = handle_sign(str, &index);
    while (str[index] != '\0') {
        digit = get_index_in_base(str[index], base);
        if (digit == -1)
            return 0;
        if (result > (2147483647 - digit) / base_len)
            return 0;
        result = result * base_len + digit;
        index++;
    }
    return result * sign;
}

char *my_putnbr_base_result(int nbr, char const *base)
{
    int base_len = 0;
    int temp = nbr;
    int length = 1;
    char *result;

    while (base[base_len] != '\0')
        base_len++;
    while (temp / base_len != 0) {
        temp /= base_len;
        length++;
    }
    result = emalloc(sizeof(char) * (length + 1));
    if (!result)
        return NULL;
    result[length] = '\0';
    for (int i = length - 1; i >= 0; i--) {
        result[i] = base[nbr % base_len];
        nbr /= base_len;
    }
    return result;
}

char *convert_base(char const *nbr, char const *base_from, char const *base_to)
{
    int num;

    if (!nbr || !base_from || !base_to)
        return NULL;
    num = my_getnbr_base(nbr, base_from);
    return my_putnbr_base_result(num, base_to);
}

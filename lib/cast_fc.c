/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** cast_fc.c
*/

#include "help_fc.h"

char *int_to_str(long long int nb)
{
    int len = size_of_int(nb);
    char *result = emalloc(sizeof(char) * (len + 1) + 1);
    long long int n = nb;

    if (!result)
        return ERROR_STR;
    n = (nb < 0 ? -nb : nb);
    for (int i = len - 1; i >= 0; i--) {
        result[i] = STR(n % 10);
        n /= 10;
        if (i == 0 && nb < 0)
            result[i] = '-';
    }
    result[len] = '\0';
    return result;
}

char *char_to_str(char c)
{
    char *result = emalloc(sizeof(char) * 2);

    if (!result)
        return ERROR_STR;
    result[0] = c;
    result[1] = '\0';
    return result;
}

int str_to_int(char *str)
{
    int result = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '-')
            result *= -1;
        else
            result = result * 10 + INT(str[i]);
    return result;
}

int my_getnbr(char const *str)
{
    long int result = 0;
    int signe = 1;

    if (!str)
        return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-')
            signe *= -1;
        if (IS_NUMERICAL(str[i]))
            result = (result * 10) + INT(str[i]);
        if (!IS_NUMERICAL(str[i]) && !my_strcontain("+- \t", str[i]))
            return signe * (int) result;
        if ((signe * result) < INT_MIN || INT_MAX < (signe * result))
            return 0;
    }
    return signe * (int) result;
}

static char *float_to_str_result(int nbr, double dec, int temp_dec, int is_neg)
{
    char *result;

    if ((dec * 10) - ((int) dec * 10) >= 5) {
        if (size_of_int(temp_dec) == size_of_int(temp_dec + 1))
            temp_dec++;
        else {
            temp_dec = (temp_dec + 1) % 10;
            nbr++;
        }
    }
    result =
        emalloc(sizeof(char) * (size_of_int(nbr) * size_of_int(dec) + 1) + 1);
    if (!result)
        return ERROR_STR;
    result =
        str_to_str(int_to_str(nbr), str_to_str(".", int_to_str(temp_dec)));
    return str_to_str((is_neg ? "-" : ""), result);
}

char *float_to_str(double nb, int prec)
{
    int nbr;
    double dec;
    int temp_dec;
    int is_neg = FALSE;

    if (nb < 0) {
        nb *= -1;
        is_neg = TRUE;
    }
    nbr = (int) nb;
    dec = nb - nbr;
    for (int i = 0; i < prec; i++)
        dec *= 10;
    temp_dec = (int) dec;
    return float_to_str_result(nbr, dec, temp_dec, is_neg);
}

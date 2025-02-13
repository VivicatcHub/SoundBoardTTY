/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** tests_help_fc.c
*/

#include "help_fc.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

////////////////////////////////////////////////////////////
/// base_fc.c
////////////////////////////////////////////////////////////

Test(tests_dec_to_hex, tests_dec_to_hex, .init = redirect_all_std)
{
    cr_assert_str_eq(dec_to_hex(0), "0");
    cr_assert_str_eq(dec_to_hex(1), "1");
    cr_assert_str_eq(dec_to_hex(10), "A");
    cr_assert_str_eq(dec_to_hex(15), "F");
    cr_assert_str_eq(dec_to_hex(255), "FF");
    cr_assert_null(dec_to_hex(-42));
}

Test(tests_my_putnbr_base, my_putnbr_base, .init = redirect_all_std)
{
    cr_assert_eq(my_putnbr_base(255, "0"), 0);
    cr_assert_eq(my_putnbr_base(255, ""), 0);
    cr_assert_eq(my_putnbr_base(255, "01234+"), 0);
    cr_assert_eq(my_putnbr_base(255, "01234-"), 0);
    cr_assert_eq(my_putnbr_base(255, "0012345"), 0);
}
Test(tests_my_putnbr_base, my_putnbr_base_display, .init = redirect_all_std)
{
    cr_assert_eq(my_putnbr_base(255, "0123456789ABCDEF"), 1);
    cr_assert_stdout_eq_str("FF");
}
Test(tests_my_putnbr_base, my_putnbr_base_display1, .init = redirect_all_std)
{
    cr_assert_eq(my_putnbr_base(42, "01"), 1);
    cr_assert_stdout_eq_str("101010");
}
Test(tests_my_putnbr_base, my_putnbr_base_display2, .init = redirect_all_std)
{
    cr_assert_eq(my_putnbr_base(-42, "0123456789"), 1);
    cr_assert_stdout_eq_str("-42");
}
Test(tests_my_putnbr_base, my_putnbr_base_display3, .init = redirect_all_std)
{
    cr_assert_eq(my_putnbr_base(12345, "01234567"), 1);
    cr_assert_stdout_eq_str("30071");
}

Test(tests_my_getnbr_base, my_getnbr_base, .init = redirect_all_std)
{
    cr_assert_eq(my_getnbr_base("FF", "01234+"), 0);
    cr_assert_eq(my_getnbr_base("FF", "01234-"), 0);
    cr_assert_eq(my_getnbr_base("FF", "0012345"), 0);
    cr_assert_eq(my_getnbr_base(NULL, "0123456789"), 0);
    cr_assert_eq(my_getnbr_base("G", "0123456789ABCDEF"), 0);
    cr_assert_eq(my_getnbr_base("FF", "0123456789ABCDEF"), 255);
    cr_assert_eq(my_getnbr_base("101010", "01"), 42);
    cr_assert_eq(my_getnbr_base("-42", "0123456789"), -42);
    cr_assert_eq(my_getnbr_base("30071", "01234567"), 12345);
    cr_assert_eq(my_getnbr_base("+FF", "0123456789ABCDEF"), 255);
    cr_assert_eq(my_getnbr_base("999999999999", "0123456789"), 0);
    cr_assert_eq(my_getnbr_base("-999999999999", "0123456789"), 0);
}

Test(tests_my_putnbr_base_result, my_putnbr_base_result,
    .init = redirect_all_std)
{
    char *result = my_putnbr_base_result(255, "01");
    char *result_bin = my_putnbr_base_result(0, "01");
    char *result_hex = my_putnbr_base_result(0, "0123456789ABCDEF");

    cr_assert_str_eq(result, "11111111");
    free(result);
    result = my_putnbr_base_result(255, "0123456789ABCDEF");
    cr_assert_str_eq(result, "FF");
    free(result);
    result = my_putnbr_base_result(255, "01234567");
    cr_assert_str_eq(result, "377");
    free(result);
    cr_assert_str_eq(result_bin, "0");
    cr_assert_str_eq(result_hex, "0");
    free(result_bin);
    free(result_hex);
}

Test(tests_convert_base, convert_base, .init = redirect_all_std)
{
    char *result = convert_base("1010", "01", "0123456789");

    cr_assert_str_eq(result, "10");
    free(result);
    result = convert_base(NULL, "0123456789", "01");
    cr_assert_null(result);
    result = convert_base("42", NULL, "01");
    cr_assert_null(result);
    result = convert_base("42", "0123456789", NULL);
    cr_assert_null(result);
    result = convert_base(NULL, NULL, NULL);
    cr_assert_null(result);
}

////////////////////////////////////////////////////////////
/// calc_fc.c
////////////////////////////////////////////////////////////

Test(tests_my_compute_factorial, tests_my_compute_factorial,
    .init = redirect_all_std)
{
    cr_assert_eq(my_compute_factorial(0), 1);
    cr_assert_eq(my_compute_factorial(-12), 0);
    cr_assert_eq(my_compute_factorial(1), 1);
    cr_assert_eq(my_compute_factorial(5), 120);
    cr_assert_eq(my_compute_factorial(12), 479001600);
    cr_assert_eq(my_compute_factorial(-1), 0);
    cr_assert_eq(my_compute_factorial(13), 0);
}

Test(tests_my_compute_power, tests_my_compute_power, .init = redirect_all_std)
{
    cr_assert_eq(my_compute_power(2, 0), 1);
    cr_assert_eq(my_compute_power(2, -1), 0);
    cr_assert_eq(my_compute_power(17, 1), 17);
    cr_assert_eq(my_compute_power(5, 2), 25);
    cr_assert_eq(my_compute_power(5, 0), 1);
    cr_assert_eq(my_compute_power(2, 3), 8);
    cr_assert_eq(my_compute_power(0, 3), 0);
    cr_assert_eq(my_compute_power(1, 5), 1);
    cr_assert_eq(my_compute_power(2, 10), 1024);
}

Test(tests_my_compute_square_root, tests_my_compute_square_root,
    .init = redirect_all_std)
{
    cr_assert_eq(my_compute_square_root(16), 4);
    cr_assert_eq(my_compute_square_root(15), 0);
    cr_assert_eq(my_compute_square_root(0), 0);
    cr_assert_eq(my_compute_square_root(-4), 0);
    cr_assert_eq(my_compute_square_root(10000), 100);
}

Test(tests_my_is_prime, tests_my_is_prime, .init = redirect_all_std)
{
    cr_assert_eq(my_is_prime(0), FALSE);
    cr_assert_eq(my_is_prime(1), FALSE);
    cr_assert_eq(my_is_prime(2), TRUE);
    cr_assert_eq(my_is_prime(4), FALSE);
    cr_assert_eq(my_is_prime(17), TRUE);
    cr_assert_eq(my_is_prime(7), TRUE);
    cr_assert_eq(my_is_prime(8), FALSE);
    cr_assert_eq(my_is_prime(-5), FALSE);
    cr_assert_eq(my_is_prime(7919), TRUE);
    cr_assert_eq(my_is_prime(8000), FALSE);
}

////////////////////////////////////////////////////////////
/// cast_fc.c
////////////////////////////////////////////////////////////

Test(tests_int_to_str, tests_int_to_str, .init = redirect_all_std)
{
    char *result;

    result = int_to_str(0);
    cr_assert_str_eq(result, "0");
    free(result);
    result = int_to_str(12345);
    cr_assert_str_eq(result, "12345");
    free(result);
    result = int_to_str(-12345);
    cr_assert_str_eq(result, "-12345");
    free(result);
    result = int_to_str(9223372036854775807LL);
    cr_assert_str_eq(result, "9223372036854775807");
    free(result);
}

Test(tests_char_to_str, tests_char_to_str, .init = redirect_all_std)
{
    char *result;

    result = char_to_str('a');
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "a");
    free(result);
    result = char_to_str('Z');
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "Z");
    free(result);
    result = char_to_str('\n');
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "\n");
    free(result);
    result = char_to_str('\0');
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "");
    free(result);
}

Test(tests_str_to_int, tests_str_to_int, .init = redirect_all_std)
{
    cr_assert_eq(str_to_int("0"), 0);
    cr_assert_eq(str_to_int("2147483647"), 2147483647);
    cr_assert_eq(str_to_int("-2147483648"), -2147483648);
}

Test(tests_my_getnbr, tests_my_getnbr, .init = redirect_all_std)
{
    cr_assert_eq(my_getnbr("0"), 0);
    cr_assert_eq(my_getnbr("2147483647"), 2147483647);
    cr_assert_eq(my_getnbr("-2147483648"), -2147483648);
    cr_assert_eq(my_getnbr("+---+--++---+---+---+-42"), -42);
    cr_assert_eq(my_getnbr("42a43"), 42);
    cr_assert_eq(my_getnbr("11000000000000000000000042"), 0);
    cr_assert_eq(my_getnbr("-1000000000000000000000042"), 0);
    cr_assert_eq(my_getnbr("123"), 123);
    cr_assert_eq(my_getnbr("-123"), -123);
    cr_assert_eq(my_getnbr("+123"), 123);
    cr_assert_eq(my_getnbr("   42"), 42);
    cr_assert_eq(my_getnbr("42abc"), 42);
    cr_assert_eq(my_getnbr("abc42"), 0);
    cr_assert_eq(my_getnbr("-0"), 0);
    cr_assert_eq(my_getnbr(""), 0);
    cr_assert_eq(my_getnbr(NULL), 0);
    cr_assert_eq(my_getnbr("  -2147483648"), -2147483648);
    cr_assert_eq(my_getnbr("2147483647"), 2147483647);
    cr_assert_eq(my_getnbr("2147483648"), 0);
    cr_assert_eq(my_getnbr("-2147483649"), 0);
}

Test(tests_float_to_str, tests_float_to_str, .init = redirect_all_std)
{
    char *result;

    result = float_to_str(123.456, 2);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "123.46");
    free(result);
    result = float_to_str(-123.456, 2);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "-123.46");
    free(result);
    result = float_to_str(123.4, 3);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "123.400");
    free(result);
    result = float_to_str(0.9999, 3);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "1.0");
    free(result);
    result = float_to_str(-0.9999, 3);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "-1.0");
    free(result);
    result = float_to_str(123.0, 3);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "123.0");
    free(result);
    result = float_to_str(-0.5, 1);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "-0.5");
    free(result);
    result = float_to_str(0.5, 1);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "0.5");
    free(result);
}

////////////////////////////////////////////////////////////
/// display_fc.c
////////////////////////////////////////////////////////////

Test(tests_my_putstr, tests_my_putstr, .init = redirect_all_std)
{
    cr_assert_eq(my_putstr(""), 0);
    cr_assert_eq(my_putstr("kitagawa marin supremacy"), 24);
    cr_assert_eq(my_putstr("Hello, World!"), 13);
    cr_assert_eq(my_putstr(""), 0);
    cr_assert_eq(my_putstr(NULL), ERROR);
}
Test(tests_my_putstr, tests_my_putstr_display, .init = redirect_all_std)
{
    my_putstr("kitagawa marin supremacy");
    cr_assert_stdout_eq_str("kitagawa marin supremacy");
}
Test(tests_my_putstr, tests_my_putstr_display2, .init = redirect_all_std)
{
    my_putstr("");
    cr_assert_stdout_eq_str("");
}

Test(tests_my_putchar, tests_my_putchar, .init = redirect_all_std)
{
    cr_assert_eq(my_putchar('v'), 1);
    cr_assert_eq(my_putchar('a'), 1);
    cr_assert_eq(my_putchar('Z'), 1);
    cr_assert_eq(my_putchar('\n'), 1);
    cr_assert_eq(my_putchar(' '), 1);
    cr_assert_eq(my_putchar('1'), 1);
}
Test(tests_my_putchar, tests_my_putchar_display, .init = redirect_all_std)
{
    my_putchar('v');
    cr_assert_stdout_eq_str("v");
}

Test(tests_my_putnbr, tests_my_putnbr, .init = redirect_all_std)
{
    cr_assert_eq(my_putnbr(0), 1);
    cr_assert_eq(my_putnbr(INT_MAX), 10);
    cr_assert_eq(my_putnbr(INT_MIN), 11);
    cr_assert_eq(my_putnbr(123), 3);
    cr_assert_eq(my_putnbr(-123), 4);
    cr_assert_eq(my_putnbr(0), 1);
    cr_assert_eq(my_putnbr(2147483647), 10);
    cr_assert_eq(my_putnbr(-2147483648), 11);
}
Test(tests_my_putnbr, tests_my_putnbr_display, .init = redirect_all_std)
{
    my_putnbr(0);
    cr_assert_stdout_eq_str("0");
}
Test(tests_my_putnbr, tests_my_putnbr_display2, .init = redirect_all_std)
{
    my_putnbr(2147483647);
    cr_assert_stdout_eq_str("2147483647");
}
Test(tests_my_putnbr, tests_my_putnbr_display3, .init = redirect_all_std)
{
    my_putnbr(-2147483648);
    cr_assert_stdout_eq_str("-2147483648");
}

Test(tests_my_puterror, tests_my_puterror, .init = redirect_all_std)
{
    cr_assert_eq(my_puterror(""), 0);
    cr_assert_eq(my_puterror("error"), 5);
    cr_assert_eq(my_puterror("An error occurred"), 17);
    cr_assert_eq(my_puterror(NULL), ERROR);
    cr_assert_eq(my_puterror("Critical failure"), 16);
}
Test(tests_my_puterror, tests_my_puterror_display, .init = redirect_all_std)
{
    my_puterror("error");
    cr_assert_stderr_eq_str("error");
}

Test(tests_my_put_nbr_float, tests_my_put_nbr_float, .init = redirect_all_std)
{
    cr_assert_eq(my_put_nbr_float(2.25, 1), 3);
    cr_assert_eq(my_put_nbr_float(2.25, 2), 4);
    cr_assert_eq(my_put_nbr_float(-2.25, 2), 5);
    cr_assert_eq(my_put_nbr_float(123.456, 2), 6);
    cr_assert_eq(my_put_nbr_float(-123.456, 2), 7);
    cr_assert_eq(my_put_nbr_float(0.0, 3), 3);
    cr_assert_eq(my_put_nbr_float(-0.9999, 4), 7);
    cr_assert_eq(my_put_nbr_float(3.14159, 3), 5);
}
Test(tests_my_put_nbr_float, tests_my_put_nbr_float_display,
    .init = redirect_all_std)
{
    my_put_nbr_float(-2.258, 2);
    cr_assert_stdout_eq_str("-2.26");
}

Test(tests_my_showstr, tests_my_showstr_display, .init = redirect_all_std)
{
    my_showstr("AHAH \n");
    cr_assert_stdout_eq_str("AHAH \\a");
}
Test(tests_my_showstr, tests_my_showstr_display2, .init = redirect_all_std)
{
    my_showstr("AHAH \t");
    cr_assert_stdout_eq_str("AHAH \\9");
}
Test(tests_my_showstr, tests_my_showstr_display3, .init = redirect_all_std)
{
    my_showstr("Hello\nWorld!");
    cr_assert_stdout_eq_str("Hello\\aWorld!");
}
Test(tests_my_showstr, tests_my_showstr_display4, .init = redirect_all_std)
{
    my_showstr("123");
    cr_assert_stdout_eq_str("123");
}
Test(tests_my_showstr, tests_my_showstr_display5, .init = redirect_all_std)
{
    my_showstr("");
    cr_assert_stdout_eq_str("");
}
Test(tests_my_showstr, tests_my_showstr_display6, .init = redirect_all_std)
{
    my_showstr(char_to_str(127));
    cr_assert_stdout_eq_str("\\7f");
}

////////////////////////////////////////////////////////////
/// error_handling_fc.c
////////////////////////////////////////////////////////////

Test(tests_emalloc, tests_emalloc_display, .init = redirect_all_std)
{
    void *data = emalloc(-5);

    cr_assert_stderr_eq_str("Error with malloc\n");
}

////////////////////////////////////////////////////////////
/// file_gestion_fc.c
////////////////////////////////////////////////////////////

Test(tests_open_file, tests_open_file, .init = redirect_all_std)
{
    char *filename = "testfile.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char *result;

    cr_assert_eq(open_file("nofile/empty"), NULL);
    cr_assert_str_not_empty(open_file("Makefile"));
    cr_assert_neq(fd, -1);
    write(fd, "Hello, world!", 13);
    close(fd);
    result = open_file(filename);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "Hello, world!");
    free(result);
    result = open_file("non_existent_file.txt");
    cr_assert_null(result);
    fd = open("emptyfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    cr_assert_neq(fd, -1);
    close(fd);
    result = open_file("emptyfile.txt");
    cr_assert_null(result);
}

Test(tests_size_of_file, tests_size_of_file, .init = redirect_all_std)
{
    char *filename = "testfile.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    cr_assert_eq(size_of_file("nofile/empty"), -1);
    cr_assert(size_of_file("Makefile") > 0);
    cr_assert_neq(fd, -1);
    write(fd, "Hello, world!", 13);
    close(fd);
    cr_assert_eq(size_of_file(filename), 13);
    cr_assert_eq(size_of_file("non_existent_file.txt"), -1);
    fd = open("emptyfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    cr_assert_neq(fd, -1);
    close(fd);
    cr_assert_eq(size_of_file("emptyfile.txt"), 0);
}

////////////////////////////////////////////////////////////
/// int_array_fc.c
////////////////////////////////////////////////////////////

Test(tests_my_sort_int_array, tests_my_sort_int_array,
    .init = redirect_all_std)
{
    int array1[] = {5, 3, 8, 1, 2};
    int array2[] = {-1, -3, 4, 0, -2};
    int array3[] = {1};
    int *array4 = NULL;

    my_sort_int_array(array1, 5);
    int expected1[] = {1, 2, 3, 5, 8};
    cr_assert_arr_eq(array1, expected1, 5);
    my_sort_int_array(array2, 5);
    int expected2[] = {-3, -2, -1, 0, 4};
    cr_assert_arr_eq(array2, expected2, 5);
    my_sort_int_array(array3, 1);
    int expected3[] = {1};
    cr_assert_arr_eq(array3, expected3, 1);
    my_sort_int_array(array4, 0);
    int array5[1] = {};
    my_sort_int_array(array5, 0);
    cr_assert_arr_eq(array5, array5, 0);
}

////////////////////////////////////////////////////////////
/// int_fc.c
////////////////////////////////////////////////////////////

Test(tests_size_of_int, tests_size_of_int, .init = redirect_all_std)
{
    cr_assert_eq(size_of_int(0), 1);
    cr_assert_eq(size_of_int(2147483647), 10);
    cr_assert_eq(size_of_int(-2147483648), 11);
    cr_assert_eq(size_of_int(0), 1);
    cr_assert_eq(size_of_int(12345), 5);
    cr_assert_eq(size_of_int(-12345), 6);
    cr_assert_eq(size_of_int(9223372036854775807LL), 19);
    cr_assert_eq(size_of_int(-9223372036854775807LL), 20);
}

Test(tests_my_swap, tests_my_swap, .init = redirect_all_std)
{
    int a = 7;
    int b = 2;
    int c = 0;
    int d = 0;
    int p = -5;
    int q = 7;
    int x = 5;
    int y = 10;

    my_swap(&a, &b);
    cr_assert_eq(a, 2);
    cr_assert_eq(b, 7);
    my_swap(&c, &d);
    cr_assert_eq(c, 0);
    cr_assert_eq(d, 0);
    my_swap(&p, &q);
    cr_assert_eq(p, 7);
    cr_assert_eq(q, -5);
    my_swap(&x, &y);
    cr_assert_eq(x, 10);
    cr_assert_eq(y, 5);
}

////////////////////////////////////////////////////////////
/// mini_printf.c
////////////////////////////////////////////////////////////

Test(tests_mini_printf, tests_mini_printf, .init = redirect_all_std)
{
    cr_assert_eq(mini_printf(""), 0);
    cr_assert_eq(mini_printf("text"), 4);
    cr_assert_eq(mini_printf("%c\n", 'v'), 2);
    cr_assert_eq(mini_printf("%s\n", "text"), 5);
    cr_assert_eq(mini_printf("%d\n", 12), 3);
    cr_assert_eq(mini_printf("%i\n", -12), 4);
    cr_assert_eq(mini_printf("%%\n"), 2);
}
Test(tests_mini_printf, tests_mini_printf_display, .init = redirect_all_std)
{
    mini_printf("Hello, %s! Your score is %d.\n", "Alice", 42);
    cr_assert_stdout_eq_str("Hello, Alice! Your score is 42.\n");
}
Test(tests_mini_printf, tests_mini_printf_display2, .init = redirect_all_std)
{
    mini_printf("Character: %c and %% symbol.\n", 'A');
    cr_assert_stdout_eq_str("Character: A and % symbol.\n");
}
Test(tests_mini_printf, tests_mini_printf_display3, .init = redirect_all_std)
{
    mini_printf("Integer: %i, String: %s\n", -12345, "Test");
    cr_assert_stdout_eq_str("Integer: -12345, String: Test\n");
}
Test(tests_mini_printf, tests_mini_printf_display4, .init = redirect_all_std)
{
    mini_printf("Literal percent: %%\n");
    cr_assert_stdout_eq_str("Literal percent: %\n");
}
Test(tests_mini_printf, tests_mini_printf_display5, .init = redirect_all_std)
{
    mini_printf("No format specifiers %\n");
    cr_assert_stdout_eq_str("No format specifiers %\n");
}

////////////////////////////////////////////////////////////
/// str_array_fc.c
////////////////////////////////////////////////////////////

Test(tests_my_strsplit, tests_my_strsplit, .init = redirect_all_std)
{
    char **result;

    result = my_strsplit("hello,world,test", ',');
    cr_assert_str_eq(result[0], "hello");
    cr_assert_str_eq(result[1], "world");
    cr_assert_str_eq(result[2], "test");
    cr_assert_null(result[3]);
    for (int i = 0; result[i]; i++)
        free(result[i]);
    free(result);
    result = my_strsplit("a,b,c", ',');
    cr_assert_str_eq(result[0], "a");
    cr_assert_str_eq(result[1], "b");
    cr_assert_str_eq(result[2], "c");
    cr_assert_null(result[3]);
    for (int i = 0; result[i]; i++)
        free(result[i]);
    free(result);
    result = my_strsplit(".start", '.');
    cr_assert_str_eq(result[0], "");
    cr_assert_str_eq(result[1], "start");
    cr_assert_null(result[2]);
    for (int i = 0; result[i]; i++)
        free(result[i]);
    free(result);
    result = my_strsplit("end:", ':');
    cr_assert_str_eq(result[0], "end");
    cr_assert_str_eq(result[1], "");
    cr_assert_null(result[2]);
    for (int i = 0; result[i]; i++)
        free(result[i]);
    free(result);
    result = my_strsplit("", ',');
    cr_assert_str_eq(result[0], "");
    cr_assert_null(result[1]);
    result = my_strsplit(NULL, ',');
    cr_assert_null(result);
}

Test(tests_my_show_word_array, my_show_word_array)
{
    int result = my_show_word_array(NULL);

    cr_assert_eq(result, FALSE);
}
Test(tests_my_show_word_array, my_show_word_array_display,
    .init = redirect_all_std)
{
    char *tab[] = {"Hello", "world", "!", NULL};
    int result = my_show_word_array(tab);

    cr_assert_eq(result, TRUE);
    cr_assert_stdout_eq_str("Hello\nworld\n!\n");
}
Test(tests_my_show_word_array, my_show_word_array_display2,
    .init = redirect_all_std)
{
    char *tab[] = {NULL};
    int result = my_show_word_array(tab);

    cr_assert_eq(result, TRUE);
    cr_assert_stdout_eq_str("");
}
Test(tests_my_show_word_array, my_show_word_array_display3,
    .init = redirect_all_std)
{
    char *test_word_array[] = {"The", "Answer", "to", "the", "Great",
        "Question...", "Of", "Life,", "the", "Universe", "and",
        "Everything...", "Is...", "Forty-two,", 0};
    int result = my_show_word_array(test_word_array);

    cr_assert_eq(result, TRUE);
    cr_assert_stdout_eq_str(
        "The\nAnswer\nto\nthe\nGreat\nQuestion...\nOf\nLife,\nthe\nUniverse\nand\nEverything...\nIs...\nForty-two,\n");
}

Test(tests_my_str_to_word_array, my_str_to_word_array,
    .init = redirect_all_std)
{
    char const *str = "Hello world?this is a test";
    char **result = my_str_to_word_array(str);

    cr_assert_not_null(result);
    cr_assert_str_eq(result[0], "Hello");
    cr_assert_str_eq(result[1], "world");
    cr_assert_str_eq(result[2], "this");
    cr_assert_str_eq(result[3], "is");
    cr_assert_str_eq(result[4], "a");
    cr_assert_str_eq(result[5], "test");
    cr_assert_null(result[6]);
    for (int i = 0; result[i] != NULL; i++)
        free(result[i]);
    free(result);
    str = "42Hello!! world123\nthis\tis_a~test.";
    result = my_str_to_word_array(str);
    cr_assert_not_null(result);
    cr_assert_str_eq(result[0], "42Hello");
    cr_assert_str_eq(result[1], "world123");
    cr_assert_str_eq(result[2], "this");
    cr_assert_str_eq(result[3], "is");
    cr_assert_str_eq(result[4], "a");
    cr_assert_str_eq(result[5], "test");
    cr_assert_null(result[6]);
    for (int i = 0; result[i] != NULL; i++)
        free(result[i]);
    free(result);
    str = "";
    result = my_str_to_word_array(str);
    cr_assert_not_null(result);
    cr_assert_null(result[0]);
    free(result);
    result = my_str_to_word_array(NULL);
    cr_assert_null(result);
}

////////////////////////////////////////////////////////////
/// str_fc.c
////////////////////////////////////////////////////////////

Test(tests_my_strlen, tests_my_strlen, .init = redirect_all_std)
{
    cr_assert_eq(my_strlen(""), 0);
    cr_assert_eq(my_strlen("ah ah"), 5);
    cr_assert_eq(my_strlen("hello"), 5);
    cr_assert_eq(my_strlen(""), 0);
    cr_assert_eq(my_strlen(NULL), 0);
    cr_assert_eq(my_strlen("a"), 1);
    cr_assert_eq(my_strlen("This is a longer string"), 23);
}

Test(tests_my_revstr, tests_my_revstr, .init = redirect_all_std)
{
    cr_assert_str_eq(my_revstr(""), "");
    cr_assert_str_eq(my_revstr("a"), "a");
    cr_assert_str_eq(my_revstr(my_strdup("ah ah!")), "!ha ha");
    cr_assert_str_eq(my_revstr(my_strdup("ah ah")), "ha ha");
    cr_assert_str_eq(my_revstr(my_strdup("hello")), "olleh");
    cr_assert_str_eq(my_revstr(my_strdup("world")), "dlrow");
    cr_assert_null(NULL);
}

Test(tests_my_strdup, tests_my_strdup, .init = redirect_all_std)
{
    char str1[] = "hello";
    char str2[] = "";
    char *null_str = NULL;
    char *dup1 = my_strdup(str1);
    char *dup2 = my_strdup(str2);
    char *dup3 = my_strdup(null_str);

    cr_assert_str_eq(dup1, "hello");
    cr_assert_str_eq(dup2, "");
    cr_assert_null(dup3);
    free(dup1);
    free(dup2);
}

Test(tests_my_strcmp, tests_my_strcmp, .init = redirect_all_std)
{
    char str1[] = "hello";
    char str2[] = "hello";
    char str3[] = "hell";
    char str4[] = "helloo";
    char str5[] = "world";
    char *null_str = NULL;

    cr_assert_eq(my_strcmp(str1, str2), 0);
    cr_assert_eq(my_strcmp(str1, str3), 'o');
    cr_assert_eq(my_strcmp(str3, str1), -'o');
    cr_assert_eq(my_strcmp(str1, str4), -'o');
    cr_assert_eq(my_strcmp(str4, str1), 'o');
    cr_assert_eq(my_strcmp(str1, str5), 'h' - 'w');
    cr_assert_eq(my_strcmp(null_str, null_str), 0);
    cr_assert_eq(my_strcmp(str1, null_str), 1);
    cr_assert_eq(my_strcmp(null_str, str1), -1);
}

Test(tests_my_strcontain, tests_my_strcontain, .init = redirect_all_std)
{
    char str1[] = "hello";
    char str2[] = "world";
    char str3[] = "abcdef";
    char *null_str = NULL;

    cr_assert_eq(my_strcontain(str1, 'h'), TRUE);
    cr_assert_eq(my_strcontain(str1, 'e'), TRUE);
    cr_assert_eq(my_strcontain(str1, 'l'), TRUE);
    cr_assert_eq(my_strcontain(str1, 'o'), TRUE);
    cr_assert_eq(my_strcontain(str1, 'z'), FALSE);
    cr_assert_eq(my_strcontain(str2, 'w'), TRUE);
    cr_assert_eq(my_strcontain(str2, 'o'), TRUE);
    cr_assert_eq(my_strcontain(str2, 'd'), TRUE);
    cr_assert_eq(my_strcontain(str2, 'z'), FALSE);
    cr_assert_eq(my_strcontain(str3, 'a'), TRUE);
    cr_assert_eq(my_strcontain(str3, 'f'), TRUE);
    cr_assert_eq(my_strcontain(str3, 'z'), FALSE);
    cr_assert_eq(my_strcontain(null_str, 'a'), FALSE);
}

Test(tests_str_to_str, tests_str_to_str, .init = redirect_all_std)
{
    char str1[] = "hello";
    char str2[] = "world";
    char str3[] = "";
    char *null_str = NULL;
    char *result1 = str_to_str(str1, str2);
    char *result2 = str_to_str(str1, str3);
    char *result3 = str_to_str(str3, str2);
    char *result4 = str_to_str(str3, str3);
    char *result5 = str_to_str(null_str, str2);
    char *result6 = str_to_str(str1, null_str);

    cr_assert_str_eq(result1, "helloworld");
    cr_assert_str_eq(result2, "hello");
    cr_assert_str_eq(result3, "world");
    cr_assert_str_eq(result4, "");
    cr_assert_null(result5);
    cr_assert_null(result6);
    free(result1);
    free(result2);
    free(result3);
    free(result4);
}

Test(tests_replace, tests_replace, .init = redirect_all_std)
{
    char str1[] = "hello";
    char str2[] = "world";
    char str3[] = "";
    char *null_str = NULL;

    replace(str1, 'l', 'x');
    replace(str2, 'o', 'a');
    replace(str3, 'a', 'b');
    replace(null_str, 'a', 'b');
    cr_assert_str_eq(str1, "hexxo");
    cr_assert_str_eq(str2, "warld");
    cr_assert_str_eq(str3, "");
}

Test(tests_my_strcat, tests_my_strcat, .init = redirect_all_std)
{
    char dest1[50] = "Hello";
    char dest2[50] = "World";
    char dest3[50] = "";
    char *null_dest = NULL;
    char *null_src = NULL;

    cr_assert_str_eq(my_strcat(dest1, " World"), "Hello World");
    cr_assert_str_eq(my_strcat(dest2, "!"), "World!");
    cr_assert_str_eq(my_strcat(dest3, "Hello"), "Hello");
    cr_assert_null(my_strcat(null_dest, "test"));
    cr_assert_null(my_strcat("test", null_src));
}

Test(tests_my_strcpy, tests_my_strcpy, .init = redirect_all_std)
{
    char dest1[50];
    char dest2[50];
    char dest3[50];
    char *null_dest = NULL;
    char *null_src = NULL;

    cr_assert_str_eq(my_strcpy(dest1, "Hello"), "Hello");
    cr_assert_str_eq(my_strcpy(dest2, "World"), "World");
    cr_assert_str_eq(my_strcpy(dest3, ""), "");
    cr_assert_null(my_strcpy(null_dest, "test"));
    cr_assert_null(my_strcpy("test", null_src));
}

Test(tests_my_strcapitalize, tests_my_strcapitalize, .init = redirect_all_std)
{
    char str1[] = "hello world~";
    char str2[] = "HELLO WORLD";
    char str3[] = "123 hello world!\n";
    char str4[] = "@   test with spaces!";
    char *null_str = NULL;

    cr_assert_str_eq(my_strcapitalize(str1), "Hello World~");
    cr_assert_str_eq(my_strcapitalize(str2), "Hello World");
    cr_assert_str_eq(my_strcapitalize(str3), "123 Hello World!\n");
    cr_assert_str_eq(my_strcapitalize(str4), "@   Test With Spaces!");
    cr_assert_null(my_strcapitalize(null_str));
}

Test(tests_my_strlowcase, tests_my_strlowcase, .init = redirect_all_std)
{
    char str1[] = "Hello World~";
    char str2[] = "HELLO WORLD";
    char str3[] = "123 HELLO WORLD!";
    char str4[] = "   test with spaces!";
    char *null_str = NULL;

    cr_assert_str_eq(my_strlowcase(str1), "hello world~");
    cr_assert_str_eq(my_strlowcase(str2), "hello world");
    cr_assert_str_eq(my_strlowcase(str3), "123 hello world!");
    cr_assert_str_eq(my_strlowcase(str4), "   test with spaces!");
    cr_assert_null(my_strlowcase(null_str));
}

Test(tests_my_strupcase, tests_my_strupcase, .init = redirect_all_std)
{
    char str1[] = "Hello World~";
    char str2[] = "hello world";
    char str3[] = "123 hello world!";
    char str4[] = "   TEST WITH SPACES!";
    char *null_str = NULL;

    cr_assert_str_eq(my_strupcase(str1), "HELLO WORLD~");
    cr_assert_str_eq(my_strupcase(str2), "HELLO WORLD");
    cr_assert_str_eq(my_strupcase(str3), "123 HELLO WORLD!");
    cr_assert_str_eq(my_strupcase(str4), "   TEST WITH SPACES!");
    cr_assert_null(my_strupcase(null_str));
}

Test(tests_my_strstr, tests_my_strstr, .init = redirect_all_std)
{
    char str1[] = "Hello, world!";
    char str2[] = "Test with some text!";
    char str3[] = "Find the substring here.";
    char *null_str = NULL;

    cr_assert_str_eq(my_strstr(str1, "world"), "world!");
    cr_assert_str_eq(my_strstr(str2, "with"), "with some text!");
    cr_assert_str_eq(my_strstr(str3, "substring"), "substring here.");
    cr_assert_null(my_strstr(str1, "notfound"));
    cr_assert_null(my_strstr(null_str, "world"));
    cr_assert_null(my_strstr(str1, ""));
    cr_assert_null(my_strstr(null_str, ""));
    cr_assert_null(my_strstr(str1, NULL));
    cr_assert_null(my_strstr(null_str, NULL));
}

Test(tests_my_strncat, tests_my_strncat, .init = redirect_all_std)
{
    char dest[100] = "Hello";
    char dest2[100] = "Hello";
    char dest3[100] = "Hello";
    char dest4[100] = "Hello";
    char dest5[100] = "Hello";
    char src[] = " world!";

    cr_assert_str_eq(my_strncat(dest, src, 3), "Hello wo");
    cr_assert_str_eq(my_strncat(dest2, src, 0), "Hello");
    cr_assert_str_eq(my_strncat(dest3, src, 7), "Hello world!");
    cr_assert_str_eq(my_strncat(dest4, src, 20), "Hello world!");
    cr_assert_str_eq(my_strncat(dest5, "", 5), "Hello");
}

Test(tests_my_strncmp, tests_my_strncmp, .init = redirect_all_std)
{
    char s1[] = "Hello";
    char s2[] = "Hello";
    char s3[] = "Helloo";
    char s4[] = "Hell";
    char s5[] = "Non";
    char s6[] = "Hella";

    cr_assert_eq(my_strncmp(s1, s2, 5), 0);
    cr_assert_eq(my_strncmp(s1, s2, 3), 0);
    cr_assert_eq(my_strncmp(s1, s2, 9), 0);
    cr_assert_eq(my_strncmp(s1, s3, 5), 0);
    cr_assert_eq(my_strncmp(s3, s1, 5), 0);
    cr_assert_eq(my_strncmp(s1, s4, 5), 'o');
    cr_assert_eq(my_strncmp(s4, s1, 5), -'o');
    cr_assert_eq(my_strncmp(s1, s4, 4), 0);
    cr_assert_eq(my_strncmp(s4, s1, 4), 0);
    cr_assert_eq(my_strncmp(s1, s3, 4), 0);
    cr_assert_eq(my_strncmp(s1, s2, 3), 0);
    cr_assert_eq(my_strncmp(s1, s4, 6), 'o');
    cr_assert_eq(my_strncmp(s1, s5, 6), 'H' - 'N');
    cr_assert_eq(my_strncmp(s1, s6, 5), 'o' - 'a');
    cr_assert_eq(my_strncmp(s1, s6, 7), 'o' - 'a');
}

Test(tests_my_strncpy, tests_my_strncpy, .init = redirect_all_std)
{
    char dest[50];

    cr_assert_str_eq(my_strncpy(dest, "Hello", 5), "Hello");
    cr_assert_str_eq(my_strncpy(dest, "Hi", 5), "Hi\0\0\0\0\0");
    cr_assert_str_eq(my_strncpy(dest, "Hello", 3), "Hel\0\0\0");
    cr_assert_str_eq(my_strncpy(dest, "Short", 10), "Short\0\0\0\0\0\0");
}

////////////////////////////////////////////////////////////
/// test_str_fc.c
////////////////////////////////////////////////////////////

Test(tests_my_str_isalpha, tests_my_str_isalpha, .init = redirect_all_std)
{
    cr_assert_eq(my_str_isalpha("Hello"), TRUE);
    cr_assert_eq(my_str_isalpha("hello"), TRUE);
    cr_assert_eq(my_str_isalpha("Hello123"), FALSE);
    cr_assert_eq(my_str_isalpha("123"), FALSE);
    cr_assert_eq(my_str_isalpha(""), TRUE);
    cr_assert_eq(my_str_isalpha(char_to_str(127)), FALSE);
}

Test(tests_my_str_islower, tests_my_str_islower, .init = redirect_all_std)
{
    cr_assert_eq(my_str_islower("hello"), TRUE);
    cr_assert_eq(my_str_islower("HELLO"), FALSE);
    cr_assert_eq(my_str_islower("Hello"), FALSE);
    cr_assert_eq(my_str_islower("123"), TRUE);
    cr_assert_eq(my_str_islower(""), TRUE);
}

Test(tests_my_str_isupper, tests_my_str_isupper, .init = redirect_all_std)
{
    cr_assert_eq(my_str_isupper("HELLO"), TRUE);
    cr_assert_eq(my_str_isupper("hello"), FALSE);
    cr_assert_eq(my_str_isupper("Hello"), FALSE);
    cr_assert_eq(my_str_isupper("123"), TRUE);
    cr_assert_eq(my_str_isupper(""), TRUE);
    cr_assert_eq(my_str_isupper("~"), TRUE);
}

Test(tests_my_str_isnum, tests_my_str_isnum, .init = redirect_all_std)
{
    cr_assert_eq(my_str_isnum("12345"), TRUE);
    cr_assert_eq(my_str_isnum("123a45"), FALSE);
    cr_assert_eq(my_str_isnum(""), TRUE);
    cr_assert_eq(my_str_isnum("000000"), TRUE);
    cr_assert_eq(my_str_isnum("12.34"), FALSE);
    cr_assert_eq(my_str_isnum("1234567890"), TRUE);
}

Test(tests_str_isprintable, tests_str_isprintable, .init = redirect_all_std)
{
    cr_assert_eq(my_str_isprintable("Hello, World!"), TRUE);
    cr_assert_eq(my_str_isprintable("Hello\tWorld!"), FALSE);
    cr_assert_eq(my_str_isprintable("1234567890"), TRUE);
    cr_assert_eq(my_str_isprintable("Text\nText"), FALSE);
    cr_assert_eq(my_str_isprintable("!@#$%^&*()"), TRUE);
    cr_assert_eq(my_str_isprintable(" "), TRUE);
    cr_assert_eq(my_str_isprintable("Hello\x01World"), FALSE);
    cr_assert_eq(my_str_isprintable(char_to_str(127)), FALSE);
}

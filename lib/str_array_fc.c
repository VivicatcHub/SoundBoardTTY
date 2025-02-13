/*
** EPITECH PROJECT, 2024
** EmptyRepo
** File description:
** str_array_fc.c
*/

#include "help_fc.h"

static char **my_strsplit_result(int a, char c, char *str, char **result)
{
    int b = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != c) {
            result[a][b] = str[i];
            b++;
            continue;
        }
        result[a][b] = '\0';
        a++;
        b = 0;
        result[a] = emalloc(sizeof(char) * (my_strlen(str) + 1));
        if (!result[a])
            return NULL;
    }
    result[a][b] = '\0';
    result[a + 1] = NULL;
    return result;
}

char **my_strsplit(char *str, char c)
{
    int count = 1;
    char **result;
    int a = 0;

    if (!str)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            count++;
    result = emalloc(sizeof(char *) * (count + 1));
    if (!result)
        return NULL;
    result[a] = emalloc(sizeof(char) * (my_strlen(str) + 1));
    if (!result[a])
        return NULL;
    return my_strsplit_result(a, c, str, result);
}

int my_show_word_array(char *const *tab)
{
    if (tab == NULL)
        return FALSE;
    for (int i = 0; tab[i] != NULL; i++) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
    return TRUE;
}

static int count_words(char const *str)
{
    int count = 0;
    int in_word = FALSE;

    for (int i = 0; str[i] != '\0'; i++)
        if (IS_ALPHANUMERICAL(str[i]) && !in_word) {
            in_word = TRUE;
            count++;
        } else
            in_word = FALSE;
    return count;
}

static char *extract_word(char const *str, int *index)
{
    int start = *index;
    int length = 0;
    char *word;

    while (str[*index] != '\0' && IS_ALPHANUMERICAL(str[*index])) {
        (*index)++;
        length++;
    }
    word = emalloc(sizeof(char) * (length + 1));
    if (!word)
        return NULL;
    for (int i = 0; i < length; i++)
        word[i] = str[start + i];
    word[length] = '\0';
    return word;
}

static void process_word(char **word_array, char const *str, int *index,
    int *word_index)
{
    char *word = extract_word(str, index);

    if (word) {
        word_array[*word_index] = word;
        (*word_index)++;
    }
}

char **my_str_to_word_array(char const *str)
{
    int word_count;
    char **word_array;
    int index = 0;
    int word_index = 0;

    if (!str)
        return NULL;
    word_count = count_words(str);
    word_array = emalloc(sizeof(char *) * (word_count + 1));
    if (!word_array)
        return NULL;
    while (str[index] != '\0')
        if (IS_ALPHANUMERICAL(str[index]))
            process_word(word_array, str, &index, &word_index);
        else
            index++;
    word_array[word_index] = NULL;
    return word_array;
}

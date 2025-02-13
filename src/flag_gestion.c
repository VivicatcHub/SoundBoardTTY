#include "header.h"

static void print_help(void)
{
    printf("Usage: sbtty [options]\n");
    printf("Options:\n");
    printf("\t-h, --help          Show this help message\n");
    printf("\t-a, --add           Add a sound/music\n");
    printf("\t-u, --update        Update a sound/music\n");
    printf("\t-d, --delete        Delete a sound/music\n");
    printf("\t-p, --play [name]   Play a sound by name\n");
}

void flag_gestion(char **av)
{
    if (my_strcmp(av[1], "-h") == 0)
        print_help();
    if (my_strcmp(av[1], "-a") == 0)
        print_help();
    if (my_strcmp(av[1], "-u") == 0)
        print_help();
    if (my_strcmp(av[1], "-d") == 0)
        print_help();
    if (my_strcmp(av[1], "-p") == 0)
        print_help();
}

#include "header.h"

static void print_help(void)
{
    printf("Usage: sbtty [options]\n");
    printf("Options:\n");
    printf(
        "\t-h, --help                                   Show this help message\n");
    printf(
        "\t-a, --add [name] [path]                      Add a sound/music\n");
    printf(
        "\t-u, --update [name] [new_name] [new_path]    Update a sound/music\n");
    printf(
        "\t-d, --delete [name]                          Delete a sound/music\n");
    printf(
        "\t-p, --play [name]                            Play a sound by name\n");
    exit(ERROR);
}

static void flag_a(int ac, char **av)
{
    if (ac != 4)
        print_help();
    command_add(av[2], av[3]);
    printf("Sound '%s' added with path '%s'\n", av[2], av[3]);
}

static void flag_u(int ac, char **av)
{
    int id = -1;

    if (ac != 5)
        print_help();
    for (int i = 0; i < sound_count; i++)
        if (my_strcmp(sounds[i].name, av[2]) == 0)
            id = i;
    command_upd(id, av[3], av[4]);
    printf("Sound '%s' updated with path '%s'\n", av[3], av[4]);
}

static void flag_d(int ac, char **av)
{
    int id = -1;
    if (ac != 3)
        print_help();

    for (int i = 0; i < sound_count; i++)
        if (my_strcmp(sounds[i].name, av[2]) == 0)
            id = i;
    command_del(id);
    printf("Sound deleted\n");
}

static void flag_p(int ac, char **av)
{
    int id = -1;
    if (ac != 3)
        print_help();

    for (int i = 0; i < sound_count; i++)
        if (my_strcmp(sounds[i].name, av[2]) == 0)
            id = i;
    play_sound(sounds[id].path);
    while (!is_finished)
        sleep(0.1);
}

void flag_gestion(int ac, char **av)
{
    if (my_strcmp(av[1], "-h") == 0)
        print_help();
    if (my_strcmp(av[1], "-a") == 0)
        flag_a(ac, av);
    if (my_strcmp(av[1], "-u") == 0)
        flag_u(ac, av);
    if (my_strcmp(av[1], "-d") == 0)
        flag_d(ac, av);
    if (my_strcmp(av[1], "-p") == 0)
        flag_p(ac, av);
}

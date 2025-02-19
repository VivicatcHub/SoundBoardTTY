#include "header.h"

static void print_help(void)
{
    printf("Usage: sbtty [options]\n");
    printf("Options:\n");
    printf("\t-h, --help\t\t\t\t\tShow this help message\n");
    printf("\t-a, --add [name] [path]\t\t\t\tAdd a sound/music\n");
    printf(
        "\t-u, --update [name] [new_name] [new_path]\tUpdate a sound/music\n");
    printf("\t-d, --delete [name]\t\t\t\tDelete a sound/music\n");
    printf("\t-p, --play [name]\t\t\t\tPlay a sound by name\n");
    exit(ERROR);
}

static void flag_a(int ac, char **av, Global_t *global)
{
    if (ac != 4)
        print_help();
    command_add(av[2], av[3], global);
    printf("Sound '%s' added with path '%s'\n", av[2], av[3]);
}

static void flag_u(int ac, char **av, Global_t *global)
{
    int id = -1;

    if (ac != 5)
        print_help();
    for (int i = 0; i < global->sound_count; i++)
        if (my_strcmp(global->sounds[i].name, av[2]) == 0)
            id = i;
    command_upd(id, av[3], av[4], global);
    printf("Sound '%s' updated with path '%s'\n", av[3], av[4]);
}

static void flag_d(int ac, char **av, Global_t *global)
{
    int id = -1;

    if (ac != 3)
        print_help();
    for (int i = 0; i < global->sound_count; i++)
        if (my_strcmp(global->sounds[i].name, av[2]) == 0)
            id = i;
    command_del(id, global);
    printf("Sound deleted\n");
}

static void flag_p(int ac, char **av, Global_t *global)
{
    int id = -1;

    if (ac != 3)
        print_help();
    for (int i = 0; i < global->sound_count; i++)
        if (my_strcmp(global->sounds[i].name, av[2]) == 0)
            id = i;
    play_sound(global->sounds[id].path, global);
    while (!global->is_finished)
        sleep(0.1);
}

void flag_gestion(int ac, char **av, Global_t *global)
{
    if (my_strcmp(av[1], "-h") == 0)
        print_help();
    if (my_strcmp(av[1], "-a") == 0)
        flag_a(ac, av, global);
    if (my_strcmp(av[1], "-u") == 0)
        flag_u(ac, av, global);
    if (my_strcmp(av[1], "-d") == 0)
        flag_d(ac, av, global);
    if (my_strcmp(av[1], "-p") == 0)
        flag_p(ac, av, global);
}

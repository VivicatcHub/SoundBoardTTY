#include "header.h"

static void print_help(void)
{
    printf("Usage: sbtty [options]\n\nOptions:\n"
        "\t-h, --help\t\t\t\t\tShow this help message\n"
        "\t-a, --add [name] [path] *type*\t\t\tAdd a sound/music\n"
        "\t-u, --update [old_name] [name] [path] [type]\tUpdatsound/music\n"
        "\t-d, --delete [name]\t\t\t\tDelete a sound/music\n"
        "\t-p, --play [name]\t\t\t\tPlay a sound by name\n"
        "\n\n[arg]: mandatory flag\n*arg*: optionnal flag\n");
    exit(ERROR);
}

static void flag_a(int ac, char **av, Global_t *global)
{
    char *absolute_path = get_absolute_path(av[3]);
    char *type;

    if (ac != 5 && ac != 4)
        print_help();
    type = (av[4] ? av[4] : "");
    command_add(av[2], absolute_path, type, global);
    free(absolute_path);
    printf("Sound '%s' added with path '%s' in '%s' category\n", av[2], av[3],
        type);
}

static void flag_u(int ac, char **av, Global_t *global)
{
    int id = -1;
    char *absolute_path = get_absolute_path(av[4]);
    NewSound_t new_values = {NULL, NULL, NULL};

    if (ac != 6)
        print_help();
    for (int i = 0; i < global->nb_sound; i++)
        if (strcmp(global->sounds[i].name, av[2]) == 0)
            id = i;
    new_values.name = av[3];
    new_values.path = absolute_path;
    new_values.type = av[5];
    command_upd(id, &new_values, global);
    free(absolute_path);
    printf("Sound '%s' updated with path '%s' in category %s\n", av[3], av[4],
        av[5]);
}

static void flag_d(int ac, char **av, Global_t *global)
{
    int id = -1;

    if (ac != 3)
        print_help();
    for (int i = 0; i < global->nb_sound; i++)
        if (strcmp(global->sounds[i].name, av[2]) == 0)
            id = i;
    command_del(id, global);
    printf("Sound deleted\n");
}

static void flag_p(int ac, char **av, Global_t *global)
{
    int id = -1;

    if (ac != 3)
        print_help();
    for (int i = 0; i < global->nb_sound; i++)
        if (strcmp(global->sounds[i].name, av[2]) == 0)
            id = i;
    play_sound(global->sounds[id].path, FALSE);
}

void flag_gestion(int ac, char **av, Global_t *global)
{
    if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0)
        print_help();
    if (strcmp(av[1], "-a") == 0 || strcmp(av[1], "--add") == 0)
        flag_a(ac, av, global);
    if (strcmp(av[1], "-u") == 0 || strcmp(av[1], "--update") == 0)
        flag_u(ac, av, global);
    if (strcmp(av[1], "-d") == 0 || strcmp(av[1], "--delete") == 0)
        flag_d(ac, av, global);
    if (strcmp(av[1], "-p") == 0 || strcmp(av[1], "--play") == 0)
        flag_p(ac, av, global);
}

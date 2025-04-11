#include "header.h"

void command_add(char *name, char *path, char *type, Global_t *global)
{
    strcpy(global->sounds[global->nb_sound].name, name);
    strcpy(global->sounds[global->nb_sound].path, path);
    strcpy(global->sounds[global->nb_sound].type, type);
    global->nb_sound++;
    write_sounds(global);
}

void command_upd(int id, NewSound_t *new_values, Global_t *global)
{
    if (strlen(new_values->name) > 0)
        strcpy(global->sounds[id].name, new_values->name);
    if (strlen(new_values->path) > 0)
        strcpy(global->sounds[id].path, new_values->path);
    if (strlen(new_values->type) > 0)
        strcpy(global->sounds[id].type, new_values->type);
    write_sounds(global);
}

void command_del(int id, Global_t *global)
{
    global->nb_sound--;
    for (int i = id; i < global->nb_sound; i++)
        global->sounds[i] = global->sounds[i + 1];
    write_sounds(global);
}

#include "header.h"

void command_add(char *name, char *path, Global_t *global)
{
    my_strcpy(global->sounds[global->sound_count].name, name);
    my_strcpy(global->sounds[global->sound_count].path, path);
    global->sound_count++;
    write_sounds(global);
}

void command_upd(int id, char *new_name, char *new_path, Global_t *global)
{
    if (my_strlen(new_name) > 0)
        my_strcpy(global->sounds[id].name, new_name);
    if (my_strlen(new_path) > 0)
        my_strcpy(global->sounds[id].path, new_path);
    write_sounds(global);
}

void command_del(int id, Global_t *global)
{
    global->sound_count--;
    for (int i = id; i < global->sound_count; i++)
        global->sounds[i] = global->sounds[i + 1];
    write_sounds(global);
}

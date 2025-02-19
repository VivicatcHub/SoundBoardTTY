#include "header.h"

void command_add(char *name, char *path)
{
    my_strcpy(sounds[sound_count].name, name);
    my_strcpy(sounds[sound_count].path, path);
    sound_count++;
    write_sounds();
}

void command_upd(int id, char *new_name, char *new_path)
{
    if (my_strlen(new_name) > 0)
        my_strcpy(sounds[id].name, new_name);
    if (my_strlen(new_path) > 0)
        my_strcpy(sounds[id].path, new_path);
    write_sounds();
}

void command_del(int id)
{
    sound_count--;
    for (int i = id; i < sound_count; i++)
        sounds[i] = sounds[i + 1];
    write_sounds();
}

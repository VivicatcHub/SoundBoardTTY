#include "header.h"

static void create_sounds(FILE *file, Global_t *global)
{
    char line[512];
    char *name;
    char *path;

    while (fgets(line, sizeof(line), file)) {
        name = strtok(line, ",");
        path = strtok(NULL, "\n");
        if (name && path) {
            strncpy(global->sounds[global->sound_count].name, name,
                sizeof(global->sounds[global->sound_count].name));
            strncpy(global->sounds[global->sound_count].path, path,
                sizeof(global->sounds[global->sound_count].path));
            global->sound_count++;
        }
    }
}

void read_sounds(Global_t *global)
{
    FILE *file = fopen(global->sounds_file_path, "r");

    if (!file) {
        printf("%s\n", global->sounds_file_path);
        file = fopen(global->sounds_file_path, "w");
        if (!file) {
            perror("Failed to create .txt");
            exit(EXIT_FAILURE);
        }
        fclose(file);
        printw("Le fichier .txt a été créé.\n");
        return;
    }
    create_sounds(file, global);
    fclose(file);
    if (global->sound_count == 0)
        printw("Il n'y a pas de sons dans la liste.\n");
}

void write_sounds(Global_t *global)
{
    FILE *file = fopen(global->sounds_file_path, "w");

    if (!file) {
        perror("Failed to open .txt for writing");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < global->sound_count; i++)
        fprintf(file, "%s,%s\n", global->sounds[i].name, global->sounds[i].path);
    fclose(file);
}

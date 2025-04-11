#include "header.h"

static void update_variables(Global_t *global)
{
    global->sounds[global->nb_sound]
        .name[sizeof(global->sounds[global->nb_sound].name) - 1] = '\0';
    global->sounds[global->nb_sound]
        .path[sizeof(global->sounds[global->nb_sound].path) - 1] = '\0';
    global->sounds[global->nb_sound]
        .type[sizeof(global->sounds[global->nb_sound].type) - 1] = '\0';
    global->nb_sound++;
}

static void create_sounds(FILE *file, Global_t *global)
{
    char line[MAX_NAME + MAX_PATH + MAX_TYPE];
    char name[MAX_NAME] = {0};
    char path[MAX_PATH] = {0};
    char type[MAX_TYPE] = {0};

    while (fgets(line, sizeof(line), file)) {
        memset(name, 0, sizeof(name));
        memset(path, 0, sizeof(path));
        memset(type, 0, sizeof(type));
        sscanf(line, "%[^,],%[^,],%s", name, path, type);
        snprintf(global->sounds[global->nb_sound].name, MAX_NAME, "%s", name);
        snprintf(global->sounds[global->nb_sound].path, MAX_PATH, "%s", path);
        snprintf(global->sounds[global->nb_sound].type, MAX_TYPE, "%s", type);
        update_variables(global);
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
    if (global->nb_sound == 0)
        printw("Il n'y a pas de sons dans la liste.\n");
}

void write_sounds(Global_t *global)
{
    FILE *file = fopen(global->sounds_file_path, "w");

    if (!file) {
        perror("Failed to open .txt for writing");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < global->nb_sound; i++)
        fprintf(file, "%s,%s,%s\n", global->sounds[i].name,
            global->sounds[i].path, global->sounds[i].type);
    fclose(file);
}

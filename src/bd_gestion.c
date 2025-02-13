#include "header.h"

void read_sounds(void)
{
    FILE *file = fopen(sounds_file_path, "r");
    if (!file) {
        printf("%s\n", sounds_file_path);
        file = fopen(sounds_file_path, "w");
        if (!file) {
            perror("Failed to create .txt");
            exit(EXIT_FAILURE);
        }
        fclose(file);
        printw("Le fichier .txt a été créé.\n");
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, ",");
        char *path = strtok(NULL, "\n");
        if (name && path) {
            strncpy(sounds[sound_count].name, name,
                sizeof(sounds[sound_count].name));
            strncpy(sounds[sound_count].path, path,
                sizeof(sounds[sound_count].path));
            sound_count++;
        }
    }
    fclose(file);

    if (sound_count == 0)
        printw("Il n'y a pas de sons dans la liste.\n");
}

void write_sounds(void)
{
    FILE *file = fopen(sounds_file_path, "w");
    if (!file) {
        perror("Failed to open .txt for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < sound_count; i++)
        fprintf(file, "%s,%s\n", sounds[i].name, sounds[i].path);
    fclose(file);
}

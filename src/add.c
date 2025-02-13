#include "header.h"

void handle_add_sound(void)
{
    char name[100] = "";
    char path[256] = "";
    int ch;
    long unsigned int name_pos = 0;
    long unsigned int path_pos = 0;

    clear();
    mvprintw(0, 0, "Enter sound name: ");
    move(1, 0);
    refresh();

    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (name_pos > 0) {
                name_pos--;
                name[name_pos] = '\0';
                mvprintw(1, name_pos, " ");
                move(1, name_pos);
            }
        } else if (name_pos < sizeof(name) - 1) {
            name[name_pos++] = ch;
            name[name_pos] = '\0';
            mvprintw(1, name_pos - 1, "%c", ch);
        }
        refresh();
    }

    mvprintw(2, 0, "Enter sound path: ");
    move(3, 0);
    refresh();

    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (path_pos > 0) {
                path_pos--;
                path[path_pos] = '\0';
                mvprintw(3, path_pos, " ");
                move(3, path_pos);
            }
        } else if (path_pos < sizeof(path) - 1) {
            path[path_pos++] = ch;
            path[path_pos] = '\0';
            mvprintw(3, path_pos - 1, "%c", ch);
        }
        refresh();
    }

    strncpy(sounds[sound_count].name, name, sizeof(name));
    strncpy(sounds[sound_count].path, path, sizeof(path));
    sound_count++;
    write_sounds();

    mvprintw(5, 0, "Sound '%s' added with path '%s'\n", name, path);
    refresh();
    getch();
}

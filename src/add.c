#include "header.h"

void handle_add_sound(void)
{
    char name[100] = "";
    char path[256] = "";
    int ch;
    long unsigned int name_pos = 0;
    long unsigned int path_pos = 0;

    clear();
    mvprintw(MARGIN_TOP, MARGIN_LEFT, "Enter sound name: ");
    move(MARGIN_TOP + 1, 0);
    refresh();

    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (name_pos > 0) {
                name_pos--;
                name[name_pos] = '\0';
                mvprintw(MARGIN_TOP + 1, MARGIN_LEFT + name_pos, " ");
                move(1, MARGIN_LEFT + name_pos);
            }
        } else if (name_pos < sizeof(name) - 1) {
            name[name_pos++] = ch;
            name[name_pos] = '\0';
            mvprintw(MARGIN_TOP + 1, MARGIN_LEFT + name_pos - 1, "%c", ch);
        }
        refresh();
    }

    mvprintw(MARGIN_TOP + 3, MARGIN_LEFT, "Enter sound path: ");
    move(MARGIN_TOP + 4, 0);
    refresh();

    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (path_pos > 0) {
                path_pos--;
                path[path_pos] = '\0';
                mvprintw(MARGIN_TOP + 4, MARGIN_LEFT + path_pos, " ");
                move(3, path_pos);
            }
        } else if (path_pos < sizeof(path) - 1) {
            path[path_pos++] = ch;
            path[path_pos] = '\0';
            mvprintw(MARGIN_TOP + 4, MARGIN_LEFT + path_pos - 1, "%c", ch);
        }
        refresh();
    }

    command_add(name, path);

    mvprintw(MARGIN_TOP + 6, MARGIN_LEFT, "Sound '%s' added with path '%s'\n", name, path);
    refresh();
    getch();
}

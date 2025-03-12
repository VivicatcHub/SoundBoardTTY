#include "header.h"

void input_ncurses(char *buffer, size_t size, int begin)
{
    int ch = getch();
    size_t pos = 0;

    while (ch != '\n') {
        if ((ch == KEY_BACKSPACE || ch == 127) && pos > 0) {
            pos--;
            buffer[pos] = '\0';
            mvprintw(MARGIN_TOP + begin, MARGIN_LEFT + pos, " ");
            move(begin, MARGIN_LEFT + pos);
        }
        if (!(ch == KEY_BACKSPACE || ch == 127) && pos < size - 1) {
            buffer[pos] = ch;
            pos++;
            buffer[pos] = '\0';
            mvprintw(MARGIN_TOP + begin, MARGIN_LEFT + pos - 1, "%c", ch);
        }
        refresh();
        ch = getch();
    }
}

void handle_add_sound(Global_t *global)
{
    char name[MAX_NAME] = "";
    char path[MAX_PATH] = "";
    char *absolute_path;

    clear();
    mvprintw(MARGIN_TOP, MARGIN_LEFT, "Enter sound name: ");
    move(MARGIN_TOP + 1, 0);
    input_ncurses(name, sizeof(name), 1);
    mvprintw(MARGIN_TOP + 3, MARGIN_LEFT, "Enter sound path: ");
    move(MARGIN_TOP + 4, 0);
    input_ncurses(path, sizeof(path), 4);
    absolute_path = get_absolute_path(path);
    command_add(name, absolute_path, global);
    free(absolute_path);
    mvprintw(MARGIN_TOP + 6, MARGIN_LEFT, "Sound '%s' added with path '%s'\n",
        name, path);
    refresh();
    getch();
}

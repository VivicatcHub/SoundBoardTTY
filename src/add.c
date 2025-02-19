#include "header.h"

void input_ncurses(char *buffer, int begin)
{
    int ch = getch();
    long unsigned int pos = 0;

    while (ch != '\n') {
        if ((ch == KEY_BACKSPACE || ch == 127) && pos > 0) {
            pos--;
            buffer[pos] = '\0';
            mvprintw(MARGIN_TOP + begin, MARGIN_LEFT + pos, " ");
            move(begin, MARGIN_LEFT + pos);
        }
        if (!(ch == KEY_BACKSPACE || ch == 127) && pos < sizeof(buffer) - 1) {
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
    char name[256] = "";
    char path[256] = "";

    clear();
    mvprintw(MARGIN_TOP, MARGIN_LEFT, "Enter sound name: ");
    move(MARGIN_TOP + 1, 0);
    refresh();
    input_ncurses(name, 1);
    mvprintw(MARGIN_TOP + 3, MARGIN_LEFT, "Enter sound path: ");
    move(MARGIN_TOP + 4, 0);
    refresh();
    input_ncurses(path, 4);
    command_add(name, path, global);
    mvprintw(MARGIN_TOP + 6, MARGIN_LEFT, "Sound '%s' added with path '%s'\n",
        name, path);
    refresh();
    getch();
}

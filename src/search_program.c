#include "header.h"

static void delete_char(int *index, Global_t *global)
{
    *index--;
    global->search[*index] = '\0';
    move(0, 12 + *index);
}

static void add_char(int *index, Global_t *global, int ch)
{
    global->search[*index] = ch;
    *index++;
    global->search[*index] = '\0';
}

static void display_searching(Global_t *global, int highlight)
{
    draw_submenu("Select a sound to play", global, highlight);
    mvprintw(MARGIN_TOP_SEARCH, MARGIN_LEFT, "Rechercher: ");
    mvprintw(MARGIN_TOP_SEARCH, MARGIN_LEFT + 12, "%s", global->search);
    refresh();
}

int search_programm(Global_t *global, int *highlight)
{
    int index = 0;
    int ch = getch();

    cbreak();
    draw_submenu("Select a sound to play", global, *highlight);
    mvprintw(MARGIN_TOP_SEARCH, MARGIN_LEFT, "Rechercher: ");
    while (ch != '\n') {
        if ((ch == KEY_BACKSPACE || ch == 127) && index > 0)
            delete_char(&index, global);
        if (index < MAX_NAME - 1 && ch >= 32 && ch <= 126)
            add_char(&index, global, ch);
        if (ch == KEY_UP)
            return global->sound_displayed;
        if (ch == KEY_DOWN)
            return 0;
        display_searching(global, *highlight);
        ch = getch();
    }
    return *highlight;
}

#include <ncurses.h>

#define MAX_LINES 5

void draw_menu(int highlight)
{
    const char *choices[MAX_LINES] = {"Ligne 1", "Ligne 2", "Ligne 3",
        "Ligne 4", "Ligne 5"};
    for (int i = 0; i < MAX_LINES; i++) {
        if (i == highlight)
            attron(A_REVERSE);
        mvprintw(2 + i, 5, choices[i]);
        if (i == highlight)
            attroff(A_REVERSE);
    }
    refresh();
}

int main()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int highlight = 0;
    int ch;
    draw_menu(highlight);

    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                if (highlight > 0)
                    highlight--;
                break;
            case KEY_DOWN:
                if (highlight < MAX_LINES - 1)
                    highlight++;
                break;
        }
        draw_menu(highlight);
    }

    endwin();
    return 0;
}

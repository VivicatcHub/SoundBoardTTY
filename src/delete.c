#include "header.h"

static void enter_delete_sound(int highlight, Global_t *global)
{
    if (highlight == global->sound_count)
        return;
    command_del(highlight, global);
    mvprintw(MARGIN_TOP + global->sound_count + 1, MARGIN_LEFT,
        "Sound deleted\n");
    refresh();
    getch();
}

void handle_delete_sound(Global_t *global)
{
    int highlight = 0;
    int ch = 0;

    while (ch != 'q') {
        switch (ch) {
            case KEY_UP:
                highlight =
                    (highlight > 0 ? highlight - 1 : global->sound_count);
                break;
            case KEY_DOWN:
                highlight =
                    (highlight < global->sound_count ? highlight + 1 : 0);
                break;
            case 10:
                enter_delete_sound(highlight, global);
                return;
        }
        draw_submenu("Select a sound to delete", global, highlight);
        ch = getch();
    }
}

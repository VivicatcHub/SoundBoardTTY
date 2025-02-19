#include "header.h"

static void enter_delete_sound(int highlight)
{
    if (highlight == sound_count)
        return;
    command_del(highlight);
    mvprintw(MARGIN_TOP + sound_count + 1, MARGIN_LEFT, "Sound deleted\n");
    refresh();
    getch();
}

void handle_delete_sound(void)
{
    int highlight = 0;
    int ch = 0;

    while (ch != 'q') {
        switch (ch) {
            case KEY_UP:
                highlight = (highlight > 0 ? highlight - 1 : sound_count);
                break;
            case KEY_DOWN:
                highlight = (highlight < sound_count ? highlight + 1 : 0);
                break;
            case 10:
                enter_delete_sound(highlight);
                return;
        }
        draw_submenu("Select a sound to delete", sounds, sound_count,
            highlight);
        ch = getch();
    }
}

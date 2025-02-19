#include "header.h"

void handle_delete_sound(void)
{
    int highlight = 0;
    int ch;
    while (1) {
        draw_submenu("Select a sound to delete", sounds, sound_count,
            highlight);
        ch = getch();
        if (ch == KEY_UP) {
            if (highlight > 0)
                highlight--;
        } else if (ch == KEY_DOWN) {
            if (highlight < sound_count)
                highlight++;
        } else if (ch == 10) {
            if (highlight == sound_count)
                return;
            command_del(highlight);
            mvprintw(MARGIN_TOP + sound_count + 1, MARGIN_LEFT, "Sound deleted\n");
            refresh();
            getch();
            return;
        }
    }
}

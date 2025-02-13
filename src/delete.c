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
            for (int i = highlight; i < sound_count - 1; i++)
                sounds[i] = sounds[i + 1];
            sound_count--;
            write_sounds();
            mvprintw(2 + sound_count + 1, 0, "Sound deleted\n");
            refresh();
            getch();
            return;
        }
    }
}

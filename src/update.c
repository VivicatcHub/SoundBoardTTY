#include "header.h"

void handle_update_sound(void)
{
    int highlight = 0;
    int ch;
    while (1) {
        draw_submenu("Select a sound to update", sounds, sound_count,
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
            char name[100];
            char path[256];
            mvprintw(2 + sound_count + 1, 0,
                "Enter new sound name (press Enter to keep current): ");
            getstr(name);
            mvprintw(3 + sound_count + 1, 0,
                "Enter new sound path (press Enter to keep current): ");
            getstr(path);
            if (strlen(name) > 0)
                strncpy(sounds[highlight].name, name, sizeof(name));
            if (strlen(path) > 0)
                strncpy(sounds[highlight].path, path, sizeof(path));
            write_sounds();
            mvprintw(4 + sound_count + 1, 0,
                "Sound '%s' updated with path '%s'\n", sounds[highlight].name,
                sounds[highlight].path);
            refresh();
            getch();
            return;
        }
    }
}

#include "header.h"

void handle_update_sound(void)
{
    int highlight = 0;
    int ch;
    while (1) {
        draw_submenu("Select a sound to update", sounds, sound_count,
            highlight);
        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (highlight > 0)
                    highlight--;
                else if (highlight == 0)
                    highlight = sound_count;
                break;
            case KEY_DOWN:
                if (highlight < sound_count)
                    highlight++;
                else if (highlight == sound_count)
                    highlight = 0;
                break;
            case 10:
                if (highlight == sound_count)
                    return;
                char name[100] = "";
                char path[256] = "";
                long unsigned int name_pos = 0;
                long unsigned int path_pos = 0;

                clear();
                mvprintw(MARGIN_TOP, MARGIN_LEFT, "Current: '%s'",
                    sounds[highlight].name);
                mvprintw(MARGIN_TOP + 1, MARGIN_LEFT,
                    "Enter new sound name (press Enter to keep current): ");
                move(MARGIN_TOP + 2, 0);
                refresh();

                while ((ch = getch()) != '\n') {
                    if (ch == KEY_BACKSPACE || ch == 127) {
                        if (name_pos > 0) {
                            name_pos--;
                            name[name_pos] = '\0';
                            mvprintw(MARGIN_TOP + 2, MARGIN_LEFT + name_pos,
                                " ");
                            move(1, MARGIN_LEFT + name_pos);
                        }
                    } else if (name_pos < sizeof(name) - 1) {
                        name[name_pos++] = ch;
                        name[name_pos] = '\0';
                        mvprintw(MARGIN_TOP + 2, MARGIN_LEFT + name_pos - 1,
                            "%c", ch);
                    }
                    refresh();
                }

                mvprintw(MARGIN_TOP + 4, MARGIN_LEFT, "Current: '%s'",
                    sounds[highlight].path);
                mvprintw(MARGIN_TOP + 5, MARGIN_LEFT,
                    "Enter new sound path (press Enter to keep current): ");
                move(MARGIN_TOP + 6, 0);
                refresh();

                while ((ch = getch()) != '\n') {
                    if (ch == KEY_BACKSPACE || ch == 127) {
                        if (path_pos > 0) {
                            path_pos--;
                            path[path_pos] = '\0';
                            mvprintw(MARGIN_TOP + 6, MARGIN_LEFT + path_pos,
                                " ");
                            move(3, path_pos);
                        }
                    } else if (path_pos < sizeof(path) - 1) {
                        path[path_pos++] = ch;
                        path[path_pos] = '\0';
                        mvprintw(MARGIN_TOP + 6, MARGIN_LEFT + path_pos - 1,
                            "%c", ch);
                    }
                    refresh();
                }

                command_upd(highlight, name, path);

                mvprintw(MARGIN_TOP + 8, MARGIN_LEFT,
                    "Sound '%s' updated with path '%s'\n",
                    (my_strlen(name) > 0 ? name : sounds[highlight].name),
                    (my_strlen(path) > 0 ? path : sounds[highlight].path));
                refresh();
                getch();
                return;
        }
    }
}

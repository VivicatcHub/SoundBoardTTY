#include "header.h"

static void enter_function(int highlight, Global_t *global)
{
    char name[256] = "";
    char path[256] = "";

    clear();
    mvprintw(MARGIN_TOP, MARGIN_LEFT,
        "Enter new sound name (press Enter to keep '%s'): ",
        global->sounds[highlight].name);
    move(MARGIN_TOP + 1, 0);
    input_ncurses(name, 1);
    mvprintw(MARGIN_TOP + 3, MARGIN_LEFT,
        "Enter new sound path (press Enter to keep '%s): ",
        global->sounds[highlight].path);
    move(MARGIN_TOP + 4, 0);
    input_ncurses(path, 4);
    command_upd(highlight, name, path, global);
    mvprintw(MARGIN_TOP + 6, MARGIN_LEFT,
        "Sound '%s' updated with path '%s'\n",
        (my_strlen(name) > 0 ? name : global->sounds[highlight].name),
        (my_strlen(path) > 0 ? path : global->sounds[highlight].path));
    getch();
}

void handle_update_sound(Global_t *global)
{
    int id = 0;
    int ch = 0;

    while (ch != 'q') {
        if (id == global->sound_count && ch == 10)
            return;
        switch (ch) {
            case KEY_UP:
                id = (id > 0 ? id - 1 : global->sound_count);
                break;
            case KEY_DOWN:
                id = (id < global->sound_count ? id + 1 : 0);
                break;
            case 10:
                enter_function(id, global);
                refresh();
        }
        draw_submenu("Select a sound to update", global, id);
        ch = getch();
    }
}

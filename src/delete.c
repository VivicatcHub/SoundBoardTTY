#include "header.h"

static void enter_delete_sound(int highlight, Global_t *global)
{
    int id = -1;

    if (highlight == global->sound_displayed)
        return;
    for (int i = 0; i < global->nb_sound; i++)
        if (strcmp(global->selected.name, global->sounds[i].name) == 0)
            id = i;
    command_del(id, global);
    mvprintw(MARGIN_TOP + global->sound_displayed + 1, MARGIN_LEFT,
        "Sound deleted\n");
    refresh();
    getch();
}

static void s_key(int *highlight, Global_t *global)
{
    *highlight = -1;
    *highlight =
        search_programm(global, highlight, "Select a sound to delete");
}

void handle_delete_sound(Global_t *global)
{
    int id = 0;
    int ch = 0;

    while (ch != 'q') {
        switch (ch) {
            case KEY_UP:
                id = (id > 0 ? id - 1 : global->sound_displayed);
                break;
            case KEY_DOWN:
                id = (id < global->sound_displayed ? id + 1 : 0);
                break;
            case '\n':
                enter_delete_sound(id, global);
                return;
            case 's':
                s_key(&id, global);
        }
        draw_submenu("Select a sound to delete", global, id);
        ch = getch();
    }
}

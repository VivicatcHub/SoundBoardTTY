#include "header.h"

// static void enter_function(int highlight, Global_t *global)
// {
//     char name[MAX_NAME] = "";
//     char path[MAX_PATH] = "";
//     char *absolute_path;

//     clear();
//     mvprintw(MARGIN_TOP, MARGIN_LEFT,
//         "Enter new sound name (press Enter to keep '%s'): ",
//         global->selected.name);
//     move(MARGIN_TOP + 1, 0);
//     input_ncurses(name, sizeof(name), 1);
//     mvprintw(MARGIN_TOP + 3, MARGIN_LEFT,
//         "Enter new sound path (press Enter to keep '%s): ",
//         global->selected.path);
//     move(MARGIN_TOP + 4, 0);
//     input_ncurses(path, sizeof(path), 4);
//     absolute_path = get_absolute_path(path);
//     command_upd(highlight, name, absolute_path, global);
//     free(absolute_path);
//     mvprintw(MARGIN_TOP + 6, MARGIN_LEFT,
//         "Sound '%s' updated with path '%s'\n",
//         (strlen(name) > 0 ? name : global->selected.name),
//         (strlen(path) > 0 ? path : global->selected.path));
//     getch();
// }

static void display_question(int nb, const char *str)
{
    switch (nb) {
        case 1:
            mvprintw(MARGIN_TOP, MARGIN_LEFT,
                "Enter new sound name (press Enter to keep '%s'): ", str);
            move(MARGIN_TOP + 1, 0);
            break;
        case 2:
            mvprintw(MARGIN_TOP + 3, MARGIN_LEFT,
                "Enter new sound path (press Enter to keep '%s'): ", str);
            move(MARGIN_TOP + 4, 0);
            break;
        case 3:
            mvprintw(MARGIN_TOP + 6, MARGIN_LEFT,
                "Enter new sound catgeory (press Enter to keep '%s'): ", str);
            move(MARGIN_TOP + 7, 0);
            break;
    }
}

static void display_result(Global_t *global, const char *name,
    const char *path, const char *type)
{
    mvprintw(MARGIN_TOP + 10, MARGIN_LEFT,
        "Sound '%s' updated with path '%s' in category %s\n",
        (strlen(name) > 0 ? name : global->selected.name),
        (strlen(path) > 0 ? path : global->selected.path),
        (strlen(type) > 0 ? type : global->selected.type));
}

static void enter_function(int highlight, Global_t *global)
{
    char name[MAX_NAME] = "";
    char path[MAX_PATH] = "";
    char type[MAX_TYPE] = "";
    char *absolute_path;
    NewSound_t new_values = {NULL, NULL, NULL};

    clear();
    display_question(1, global->selected.name);
    input_ncurses(name, MAX_NAME, 1);
    display_question(2, global->selected.path);
    input_ncurses(path, MAX_PATH, 4);
    absolute_path = get_absolute_path(path);
    display_question(3, global->selected.type);
    input_ncurses(type, MAX_TYPE, 8);
    new_values = (NewSound_t) {name, absolute_path, type};
    command_upd(highlight, &new_values, global);
    display_result(global, name, absolute_path, type);
    free(absolute_path);
    refresh();
    getch();
}

static void s_key(Global_t *global, int *id)
{
    *id = -1;
    *id = search_programm(global, id, "Select a sound to update");
}

void handle_update_sound(Global_t *global)
{
    int id = 0;
    int ch = 0;

    while (ch != 'q') {
        if (id == global->sound_displayed && ch == '\n')
            return;
        if (ch == KEY_UP)
            id = (id > 0 ? id - 1 : global->sound_displayed);
        if (ch == KEY_DOWN)
            id = (id < global->sound_displayed ? id + 1 : 0);
        if (ch == '\n') {
            enter_function(id, global);
            refresh();
        }
        if (ch == 's')
            s_key(global, &id);
        draw_submenu("Select a sound to update", global, id);
        ch = getch();
    }
}

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
//         (my_strlen(name) > 0 ? name : global->selected.name),
//         (my_strlen(path) > 0 ? path : global->selected.path));
//     getch();
// }

static void get_user_input(char *name, size_t name_size, char *path,
    size_t path_size, Global_t *global)
{
    clear();
    mvprintw(MARGIN_TOP, MARGIN_LEFT,
        "Enter new sound name (press Enter to keep '%s'): ",
        global->selected.name);
    move(MARGIN_TOP + 1, 0);
    input_ncurses(name, name_size, 1);
    mvprintw(MARGIN_TOP + 3, MARGIN_LEFT,
        "Enter new sound path (press Enter to keep '%s'): ",
        global->selected.path);
    move(MARGIN_TOP + 4, 0);
    input_ncurses(path, path_size, 4);
}

static void update_sound(int highlight, char *name, char *path,
    Global_t *global)
{
    char *absolute_path = get_absolute_path(path);

    command_upd(highlight, name, absolute_path, global);
    free(absolute_path);
    mvprintw(MARGIN_TOP + 6, MARGIN_LEFT,
        "Sound '%s' updated with path '%s'\n",
        (my_strlen(name) > 0 ? name : global->selected.name),
        (my_strlen(path) > 0 ? path : global->selected.path));
    getch();
}

static void enter_function(int highlight, Global_t *global)
{
    char name[MAX_NAME] = "";
    char path[MAX_PATH] = "";

    get_user_input(name, sizeof(name), path, sizeof(path), global);
    update_sound(highlight, name, path, global);
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

#include "header.h"

// int sound_count = 0;
// char sounds_file_path[1024];

// pthread_t play_thread;
// int stop_playback = 0;  // Indique si on doit arrêter la lecture en cours
// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
// int is_finished = FALSE;

static void set_color(int i, int highlight)
{
    if (i == highlight)
        attron(A_REVERSE);
    switch (i) {
        case ADD_SOUND:
            attron(COLOR_PAIR(2));
            break;
        case DEL_SOUND:
            attron(COLOR_PAIR(3));
            break;
        default:
            attron(COLOR_PAIR(4));
            break;
    }
}

static void set_off_color(int i, int highlight)
{
    if (i == highlight)
        attroff(A_REVERSE);
    switch (i) {
        case ADD_SOUND:
            attroff(COLOR_PAIR(2));
            break;
        case DEL_SOUND:
            attroff(COLOR_PAIR(3));
            break;
        default:
            attroff(COLOR_PAIR(4));
            break;
    }
}

void draw_menu(int highlight)
{
    const char *choices[MAX_LINES] = {"Jouer un son", "", "Ajouter un son",
        "Mettre à jour un son", "Supprimer un son", "", "Volume", "Aide",
        "Quitter"};

    for (int i = 0; i < MAX_LINES; i++) {
        set_color(i, highlight);
        mvprintw(MARGIN_TOP + i, MARGIN_LEFT, "%s", choices[i]);
        set_off_color(i, highlight);
    }
    refresh();
}

static void print_help(void)
{
    clear();
    mvprintw(MARGIN_TOP + 0, MARGIN_LEFT, "Usage: soundboard [options]\n");
    mvprintw(MARGIN_TOP + 1, MARGIN_LEFT, "Options:\n");
    mvprintw(MARGIN_TOP + 2, MARGIN_LEFT,
        "  -h, --help          Show this help message\n");
    mvprintw(MARGIN_TOP + 3, MARGIN_LEFT,
        "  -a, --add           Add a sound/music\n");
    mvprintw(MARGIN_TOP + 4, MARGIN_LEFT,
        "  -u, --update        Update a sound/music\n");
    mvprintw(MARGIN_TOP + 5, MARGIN_LEFT,
        "  -d, --delete        Delete a sound/music\n");
    mvprintw(MARGIN_TOP + 6, MARGIN_LEFT,
        "  -p, --play [name]   Play a sound by name\n");
    refresh();
    getch();
}

static void call_functions2(int highlight)
{
    switch (highlight) {
        case VOLUME:
            handle_volume();
            break;
        case HELP:
            print_help();
            break;
        case QUIT:
            endwin();
            exit(0);
    }
}

static void call_functions(Global_t *global, int highlight)
{
    switch (highlight) {
        case PLAY_SOUND:
            handle_play_sound(global);
            break;
        case ADD_SOUND:
            handle_add_sound(global);
            break;
        case UPD_SOUND:
            handle_update_sound(global);
            break;
        case DEL_SOUND:
            handle_delete_sound(global);
            break;
        default:
            call_functions2(highlight);
    }
}

static void key_gestion(int ch, Global_t *global, int *hl)
{
    switch (ch) {
        case KEY_UP:
            *hl = (*hl > 0 ? *hl - 1 : MAX_LINES - 1);
            *hl = ((*hl == 1 || *hl == 5) ? *hl - 1 : *hl);
            break;
        case KEY_DOWN:
            *hl = (*hl < MAX_LINES - 1 ? *hl + 1 : 0);
            *hl = ((*hl == 1 || *hl == 5) ? *hl + 1 : *hl);
            break;
        case 10:
            call_functions(global, *hl);
            break;
    }
}

static void launch_ncurses(Global_t *global)
{
    int ch = 0;
    int highlight = 0;

    initscr();
    start_color();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    draw_menu(highlight);
    while (ch != 'q') {
        key_gestion(ch, global, &highlight);
        clear();
        draw_menu(highlight);
        ch = getch();
    }
    endwin();
}

int main(int ac, char **av)
{
    Global_t global;

    global.sound_count = 0;
    global.sound_displayed = 0;
    global.stop_playback = 0;
    global.lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    global.is_finished = FALSE;
    global.search[0] = '\0';
    snprintf(global.sounds_file_path, sizeof(global.sounds_file_path), "%s/%s",
        getenv("HOME"), "SoundBoardTTY_sounds.txt");
    read_sounds(&global);
    if (ac == 1)
        launch_ncurses(&global);
    else
        flag_gestion(ac, av, &global);
    return NOERROR;
}

// void draw_submenu(const char *title, Global_t *global, int highlight)
// {
//     clear();
//     mvprintw(0, MARGIN_LEFT, "%s", title);
//     for (int i = 0; i < global->sound_count; i++) {
//         if (i == highlight)
//             attron(A_REVERSE);
//         attron(COLOR_PAIR(4));
//         mvprintw(MARGIN_TOP + i, MARGIN_LEFT, "- %s",
//              (global->sounds[i]).name);
//         if (i == highlight)
//             attroff(A_REVERSE);
//         attroff(COLOR_PAIR(4));
//     }
//     mvprintw(MARGIN_TOP + global->sound_count, MARGIN_LEFT, "Retour");
//     if (highlight == global->sound_count)
//         attron(A_REVERSE);
//     mvprintw(MARGIN_TOP + global->sound_count, MARGIN_LEFT, "Retour");
//     if (highlight == global->sound_count)
//         attroff(A_REVERSE);
//     refresh();
// }

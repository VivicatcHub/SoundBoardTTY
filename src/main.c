#include "header.h"

Sound sounds[MAX_SOUNDS];
int sound_count = 0;
char sounds_file_path[1024];

pthread_t play_thread;
int stop_playback = 0;  // Indique si on doit arrêter la lecture en cours
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int is_finished = FALSE;

void draw_menu(int highlight)
{
    const char *choices[MAX_LINES] = {"Jouer un son", "", "Ajouter un son",
        "Mettre à jour un son", "Supprimer un son", "", "Volume", "Aide",
        "Quitter"};
    for (int i = 0; i < MAX_LINES; i++) {
        if (i == highlight)
            attron(A_REVERSE);
        if (i == ADD_SOUND)
            attron(COLOR_PAIR(2));
        else if (i == DEL_SOUND)
            attron(COLOR_PAIR(3));
        else
            attron(COLOR_PAIR(4));
        mvprintw(MARGIN_TOP + i, MARGIN_LEFT, choices[i]);
        if (i == highlight)
            attroff(A_REVERSE);
        if (i == ADD_SOUND)
            attroff(COLOR_PAIR(2));
        else if (i == DEL_SOUND)
            attroff(COLOR_PAIR(3));
        else
            attroff(COLOR_PAIR(4));
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

void draw_submenu(const char *title, Sound *sounds, int num_sounds,
    int highlight)
{
    clear();
    mvprintw(0, MARGIN_LEFT, title);
    for (int i = 0; i < num_sounds; i++) {
        if (i == highlight)
            attron(A_REVERSE);
        attron(COLOR_PAIR(4));
        mvprintw(MARGIN_TOP + i, MARGIN_LEFT, sounds[i].name);
        if (i == highlight)
            attroff(A_REVERSE);
        attroff(COLOR_PAIR(4));
    }
    mvprintw(MARGIN_TOP + num_sounds, MARGIN_LEFT, "Retour");
    if (highlight == num_sounds)
        attron(A_REVERSE);
    mvprintw(MARGIN_TOP + num_sounds, MARGIN_LEFT, "Retour");
    if (highlight == num_sounds)
        attroff(A_REVERSE);
    refresh();
}

static int launch_ncurses(void)
{
    initscr();
    start_color();// Initialiser les couleurs
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    // Définir les paires de couleurs
    init_pair(1, COLOR_WHITE, COLOR_BLUE); // Fond d'écran bleu
    init_pair(2, COLOR_GREEN, COLOR_BLACK);// Ajouter un son en vert
    init_pair(3, COLOR_RED, COLOR_BLACK);  // Supprimer un son en rouge
    init_pair(4, COLOR_WHITE, COLOR_BLACK);// Autres éléments en blanc

    // bkgd(COLOR_PAIR(1));// Appliquer la couleur de fond

    int highlight = 0;
    int ch;
    draw_menu(highlight);

    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                if (highlight > 0) {
                    highlight--;
                    if (highlight == 1 || highlight == 5)
                        highlight--;
                } else if (highlight == 0)
                    highlight = MAX_LINES - 1;
                break;
            case KEY_DOWN:
                if (highlight < MAX_LINES - 1) {
                    highlight++;
                    if (highlight == 1 || highlight == 5)
                        highlight++;
                } else if (highlight == MAX_LINES - 1)
                    highlight = 0;
                break;
            case 10:// Enter key
                switch (highlight) {
                    case PLAY_SOUND:
                        handle_play_sound();
                        break;
                    case ADD_SOUND:
                        handle_add_sound();
                        break;
                    case UPD_SOUND:
                        handle_update_sound();
                        break;
                    case DEL_SOUND:
                        handle_delete_sound();
                        break;
                    case VOLUME:
                        handle_volume();
                        break;
                    case HELP:
                        print_help();
                        break;
                    case QUIT:
                        endwin();
                        return 0;
                }
                break;
        }
        clear();
        draw_menu(highlight);
    }

    endwin();
    return 0;
}

int main(int ac, char **av)
{
    snprintf(sounds_file_path, sizeof(sounds_file_path), "%s/%s",
        getenv("HOME"), "SoundBoardTTY_sounds.txt");
    read_sounds();
    if (ac == 1)
        return launch_ncurses();
    else
        flag_gestion(ac, av);
}

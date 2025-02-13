#include "header.h"

Sound sounds[MAX_SOUNDS];
int sound_count = 0;
char sounds_file_path[1024];

pthread_t play_thread;
int stop_playback = 0;

void draw_menu(int highlight)
{
    const char *choices[MAX_LINES] = {"Jouer un son", "Ajouter un son",
        "Mettre à jour un son", "Supprimer un son", "Volume", "Aide",
        "Quitter"};
    for (int i = 0; i < MAX_LINES; i++) {
        if (i == highlight)
            attron(A_REVERSE);
        if (i == 1)// Ajouter un son
            attron(COLOR_PAIR(2));
        else if (i == 3)// Supprimer un son
            attron(COLOR_PAIR(3));
        else
            attron(COLOR_PAIR(4));
        mvprintw(2 + i, 5, choices[i]);
        if (i == highlight)
            attroff(A_REVERSE);
        if (i == 1)
            attroff(COLOR_PAIR(2));
        else if (i == 3)
            attroff(COLOR_PAIR(3));
        else
            attroff(COLOR_PAIR(4));
    }
    refresh();
}

static void print_help(void)
{
    clear();
    mvprintw(0, 0, "Usage: soundboard [options]\n");
    mvprintw(1, 0, "Options:\n");
    mvprintw(2, 0, "  -h, --help          Show this help message\n");
    mvprintw(3, 0, "  -a, --add           Add a sound/music\n");
    mvprintw(4, 0, "  -u, --update        Update a sound/music\n");
    mvprintw(5, 0, "  -d, --delete        Delete a sound/music\n");
    mvprintw(6, 0, "  -p, --play [name]   Play a sound by name\n");
    refresh();
    getch();
}

void draw_submenu(const char *title, Sound *sounds, int num_sounds,
    int highlight)
{
    clear();
    mvprintw(0, 0, title);
    for (int i = 0; i < num_sounds; i++) {
        if (i == highlight)
            attron(A_REVERSE);
        attron(COLOR_PAIR(4));
        mvprintw(2 + i, 5, sounds[i].name);
        if (i == highlight)
            attroff(A_REVERSE);
        attroff(COLOR_PAIR(4));
    }
    mvprintw(2 + num_sounds, 5, "Retour");
    if (highlight == num_sounds)
        attron(A_REVERSE);
    mvprintw(2 + num_sounds, 5, "Retour");
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
                if (highlight > 0)
                    highlight--;
                break;
            case KEY_DOWN:
                if (highlight < MAX_LINES - 1)
                    highlight++;
                break;
            case 10:// Enter key
                switch (highlight) {
                    case 0:
                        handle_play_sound();
                        break;
                    case 1:
                        handle_add_sound();
                        break;
                    case 2:
                        handle_update_sound();
                        break;
                    case 3:
                        handle_delete_sound();
                        break;
                    case 4:
                        handle_volume();
                        break;
                    case 5:
                        print_help();
                        break;
                    case 6:
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
        flag_gestion(av);
}

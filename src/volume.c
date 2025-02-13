#include "header.h"

int get_volume()
{
    FILE *fp;
    char path[1035];
    int volume = 0;

    // Exécuter la commande pour obtenir le volume actuel
    fp = popen("amixer get Master | grep -o '[0-9]*%' | head -n1 | tr -d '%'", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    // Lire la sortie de la commande
    if (fgets(path, sizeof(path) - 1, fp) != NULL)
        volume = atoi(path);
    // Fermer le flux
    pclose(fp);
    return volume;
}

void draw_volume_menu(int highlight)
{
    int volume = get_volume();
    char volume_text[20];
    snprintf(volume_text, sizeof(volume_text), "Volume: %d%%", volume);

    const char *choices[3] = {"[-]", volume_text, "[+]"};
    clear();
    mvprintw(0, 0, "Réglage du volume");
    for (int i = 0; i < 3; i++) {
        if (i == highlight)
            attron(A_REVERSE);
        mvprintw(2 + i, 5, choices[i]);
        if (i == highlight)
            attroff(A_REVERSE);
    }
    refresh();
}

void handle_volume()
{
    int highlight = 1;
    int ch;
    draw_volume_menu(highlight);

    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                if (highlight > 0)
                    highlight--;
                break;
            case KEY_DOWN:
                if (highlight < 2)
                    highlight++;
                break;
            case 10: // Enter key
                if (highlight == 0) {
                    // Diminuer le volume
                    system("amixer set Master 2%-");
                } else if (highlight == 2) {
                    // Augmenter le volume
                    system("amixer set Master 2%+");
                } else if (highlight == 1) {
                    // Retour au menu principal
                    return;
                }
                break;
            case KEY_LEFT:
                // Diminuer le volume
                system("amixer set Master 2%-");
                break;
            case KEY_RIGHT:
                // Augmenter le volume
                system("amixer set Master 2%+");
                break;
        }
        clear();
        draw_volume_menu(highlight);
    }
}
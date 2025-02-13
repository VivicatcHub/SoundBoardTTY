#include "header.h"

int get_volume()
{
    FILE *fp;
    char path[1035];
    int volume = 0;

    fp = popen("amixer get Master | grep -o '[0-9]*%' | head -n1 | tr -d '%'",
        "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }
    if (fgets(path, sizeof(path) - 1, fp) != NULL)
        volume = atoi(path);
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

void handle_volume(void)
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
            case 10:
                if (highlight == 0)
                    system("amixer set Master 2%-");
                else if (highlight == 2)
                    system("amixer set Master 2%+");
                else if (highlight == 1)
                    return;
                break;
            case KEY_LEFT:
                system("amixer set Master 2%-");
                break;
            case KEY_RIGHT:
                system("amixer set Master 2%+");
                break;
        }
        clear();
        draw_volume_menu(highlight);
    }
}

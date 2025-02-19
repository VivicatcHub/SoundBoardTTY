#include "header.h"

int get_volume(void)
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
    char *choices[3];

    snprintf(volume_text, sizeof(volume_text), "Volume: %d%%", volume);
    choices[0] = "[-]";
    choices[1] = volume_text;
    choices[2] = "[+]";
    clear();
    mvprintw(0, 5, "Réglage du volume");
    for (int i = 0; i < 3; i++) {
        if (i == highlight)
            attron(A_REVERSE);
        mvprintw(2 + i, 5, "%s", choices[i]);
        if (i == highlight)
            attroff(A_REVERSE);
    }
    refresh();
}

void set_volume(char *cmd)
{
    FILE *fp = popen(cmd, "r");

    if (fp != NULL)
        pclose(fp);
}

static void key_gestion(int ch, int *highlight)
{
    switch (ch) {
        case KEY_UP:
            *highlight = (*highlight > 0 ? *highlight - 1 : *highlight);
            break;
        case KEY_DOWN:
            *highlight = (*highlight < 2 ? *highlight + 1 : *highlight);
            break;
        case KEY_LEFT:
            set_volume("amixer set Master 2%-");
            break;
        case KEY_RIGHT:
            set_volume("amixer set Master 2%+");
            break;
    }
}

void handle_volume(void)
{
    int highlight = 1;
    int ch = 0;

    draw_volume_menu(highlight);
    while (ch != 'q') {
        key_gestion(ch, &highlight);
        if (highlight == 0 && ch == 10)
            set_volume("amixer set Master 2%-");
        if (highlight == 1 && ch == 10)
            return;
        if (highlight == 2 && ch == 10)
            set_volume("amixer set Master 2%+");
        clear();
        draw_volume_menu(highlight);
        ch = getch();
    }
}

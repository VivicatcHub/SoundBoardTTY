#include "header.h"
#include <mpv/client.h>
#include <stdio.h>
#include <stdlib.h>

static void launch_sound(mpv_handle *mpv, const char *file_path,
    int is_ncurses)
{
    const char *cmd[] = {"loadfile", file_path, "replace", NULL};
    mpv_event *event;

    mpv_command_string(mpv, "stop");
    mpv_set_property_string(mpv, "video", "no");
    if (mpv_command(mpv, cmd) < 0) {
        fprintf(stderr, "Erreur: Impossible de lire le fichier %s\n",
            file_path);
    }
    while (!is_ncurses) {
        event = mpv_wait_event(mpv, 1000);
        if (event->event_id == MPV_EVENT_END_FILE)
            break;
    }
}

void play_sound(const char *file_path, int is_ncurses)
{
    static mpv_handle *mpv = NULL;

    if (!mpv) {
        mpv = mpv_create();
        if (!mpv) {
            fprintf(stderr, "Erreur: Impossible d'initialiser MPV\n");
            return;
        }
        if (mpv_initialize(mpv) < 0) {
            fprintf(stderr, "Erreur: Échec de l'initialisation de MPV\n");
            mpv_destroy(mpv);
            mpv = NULL;
            return;
        }
    }
    launch_sound(mpv, file_path, is_ncurses);
}

static void key_gestion(int ch, int *highlight, Global_t *global)
{
    switch (ch) {
        case KEY_UP:
            *highlight =
                (*highlight > 0 ? *highlight - 1 : global->sound_count);
            break;
        case KEY_DOWN:
            *highlight =
                (*highlight < global->sound_count ? *highlight + 1 : 0);
            break;
        case 10:
            play_sound(global->sounds[*highlight].path, TRUE);
    }
}

void handle_play_sound(Global_t *global)
{
    int highlight = 0;
    int ch = 0;

    if (global->sound_count == 0) {
        mvprintw(0, 5, "Aucun son dans la liste\n");
        refresh();
        getch();
        return;
    }
    while (ch != 'q') {
        if (ch == 10 && highlight == global->sound_count)
            return;
        key_gestion(ch, &highlight, global);
        refresh();
        draw_submenu("Select a sound to play", global, highlight);
        ch = getch();
    }
}

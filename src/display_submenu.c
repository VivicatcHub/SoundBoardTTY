#include "header.h"

static void display_retour(Global_t *global, int highlight)
{
    mvprintw(MARGIN_TOP + global->sound_displayed, MARGIN_LEFT, "Retour");
    if (highlight == global->sound_displayed)
        attron(A_REVERSE);
    mvprintw(MARGIN_TOP + global->sound_displayed, MARGIN_LEFT, "Retour");
    if (highlight == global->sound_displayed)
        attroff(A_REVERSE);
    refresh();
}

void draw_submenu(const char *title, Global_t *global, int highlight)
{
    int len = my_strlen(global->search);

    global->sound_displayed = 0;
    clear();
    mvprintw(0, MARGIN_LEFT, "%s", title);
    for (int i = 0; i < global->sound_count; i++) {
        if (!(my_strncmp(global->sounds[i].name, global->search, len) == 0
                || len == 0))
            continue;
        if (global->sound_displayed == highlight) {
            attron(A_REVERSE);
            global->selected = global->sounds[i];
        }
        mvprintw(MARGIN_TOP + global->sound_displayed, MARGIN_LEFT, "- %s",
            (global->sounds[i]).name);
        if (global->sound_displayed == highlight)
            attroff(A_REVERSE);
        global->sound_displayed++;
    }
    display_retour(global, highlight);
}

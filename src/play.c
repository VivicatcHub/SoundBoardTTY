#include "header.h"

void *play_sound_thread(void *global)
{
    const char *path = ((Global_t *) global)->path;
    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;

    ao_sample_format format;
    int channels, encoding;
    long rate;

    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char *) malloc(buffer_size * sizeof(unsigned char));

    mpg123_open(mh, path);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    format.bits = mpg123_encsize(encoding) * BITS;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
        pthread_mutex_lock(&(((Global_t *) global)->lock));
        if (((Global_t *) global)->stop_playback) {
            ((Global_t *) global)->is_finished = TRUE;
            pthread_mutex_unlock(&(((Global_t *) global)->lock));
            break;
        }
        pthread_mutex_unlock(&(((Global_t *) global)->lock));

        ao_play(dev, (char *) buffer, done);
    }

    // Assure que le thread est bien marqué comme terminé
    pthread_mutex_lock(&(((Global_t *) global)->lock));
    ((Global_t *) global)->is_finished = TRUE;
    pthread_mutex_unlock(&(((Global_t *) global)->lock));

    ((Global_t *) global)->is_finished = TRUE;
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();

    return NULL;
}

void play_sound(const char *path, Global_t *global)
{
    pthread_mutex_lock(&(global->lock));
    global->stop_playback = 1;// Demande l'arrêt du son en cours
    pthread_mutex_unlock(&(global->lock));

    // Vérifie que le thread précédent existe avant de le joindre
    if (global->play_thread && !global->is_finished) {
        pthread_join(global->play_thread, NULL);
        global->play_thread = 0;// Réinitialisation après la fin du thread
    }

    pthread_mutex_lock(&(global->lock));
    global->stop_playback = 0;  // Réinitialise pour la nouvelle lecture
    global->is_finished = FALSE;// Reset pour le prochain thread
    global->path = path;
    pthread_mutex_unlock(&(global->lock));

    // Démarre un nouveau thread pour lire le son
    if (pthread_create(&(global->play_thread), NULL, play_sound_thread,
            (void *) global)
        != 0) {
        perror("pthread_create failed");
    }
}

void handle_play_sound(Global_t *global)
{
    int highlight = 0;
    int ch;
    while (1) {
        if (global->sound_count == 0) {
            mvprintw(0, 5, "Aucun son dans la liste\n");
            refresh();
            getch();
            return;
        }

        draw_submenu("Select a sound to play", global, highlight);
        ch = getch();
        switch (ch) {
            case 'q':
                return;
            case KEY_UP:
                if (highlight > 0)
                    highlight--;
                else if (highlight == 0)
                    highlight = global->sound_count;
                break;
            case KEY_DOWN:
                if (highlight < global->sound_count)
                    highlight++;
                else if (highlight == global->sound_count)
                    highlight = 0;
                break;
            case 10:
                if (highlight == global->sound_count)
                    return;
                // mvprintw(2 + sound_count + 1, 0, "Playing sound '%s'\n",
                //     sounds[highlight].name);
                refresh();
                play_sound(global->sounds[highlight].path, global);
        }
    }
}

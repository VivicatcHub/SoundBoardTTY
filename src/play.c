#include "header.h"

void *play_sound_thread(void *arg)
{
    const char *path = (const char *) arg;
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
        if (stop_playback)
            break;
        ao_play(dev, (char *) buffer, done);
    }

    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();

    return NULL;
}

void play_sound(const char *path)
{
    stop_playback = 1;
    pthread_join(play_thread, NULL);
    stop_playback = 0;
    pthread_create(&play_thread, NULL, play_sound_thread, (void *) path);
}

void handle_play_sound(void)
{
    int highlight = 0;
    int ch;
    while (1) {
        if (sound_count == 0) {
            mvprintw(0, 0, "Aucun son dans la liste\n");
            mvprintw(1, 0, "Retour");
            refresh();
            getch();
            return;
        }

        draw_submenu("Select a sound to play", sounds, sound_count, highlight);
        ch = getch();
        if (ch == KEY_UP) {
            if (highlight > 0)
                highlight--;
        } else if (ch == KEY_DOWN) {
            if (highlight < sound_count)
                highlight++;
        } else if (ch == 10) {
            if (highlight == sound_count)
                return;
            mvprintw(2 + sound_count + 1, 0, "Playing sound '%s'\n",
                sounds[highlight].name);
            refresh();
            play_sound(sounds[highlight].path);
        }
    }
}

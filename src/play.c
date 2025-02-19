#include "header.h"

static int init_audio_system(mpg123_handle **mh, ao_device **dev,
    ao_sample_format *format, const char *path)
{
    int err;
    int driver;
    long rate;
    int channels;
    int encoding;

    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    *mh = mpg123_new(NULL, &err);
    mpg123_open(*mh, path);
    mpg123_getformat(*mh, &rate, &channels, &encoding);
    format->bits = mpg123_encsize(encoding) * BITS;
    format->rate = rate;
    format->channels = channels;
    format->byte_format = AO_FMT_NATIVE;
    format->matrix = 0;
    *dev = ao_open_live(driver, format, NULL);
    return (*dev && *mh) ? 0 : -1;
}

static void play_audio_loop(Global_t *global, mpg123_handle *mh,
    unsigned char *buffer, size_t buffer_size)
{
    size_t done;

    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
        pthread_mutex_lock(&(global->lock));
        if (global->stop_playback) {
            global->is_finished = TRUE;
            pthread_mutex_unlock(&(global->lock));
            break;
        }
        pthread_mutex_unlock(&(global->lock));
        ao_play(global->dev, (char *) buffer, done);
    }
}

static void cleanup_audio(mpg123_handle *mh, ao_device *dev,
    unsigned char *buffer)
{
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
}

void *play_sound_thread(void *arg)
{
    Global_t *global = (Global_t *) arg;
    mpg123_handle *mh;
    ao_device *dev;
    ao_sample_format format;
    unsigned char *buffer;
    size_t buffer_size;

    if (init_audio_system(&mh, &dev, &format, global->path) == -1)
        return NULL;
    buffer_size = mpg123_outblock(mh);
    buffer = malloc(buffer_size);
    global->dev = dev;
    play_audio_loop(global, mh, buffer, buffer_size);
    pthread_mutex_lock(&(global->lock));
    global->is_finished = TRUE;
    pthread_mutex_unlock(&(global->lock));
    cleanup_audio(mh, dev, buffer);
    return NULL;
}

void play_sound(const char *path, Global_t *global)
{
    pthread_mutex_lock(&(global->lock));
    global->stop_playback = 1;
    pthread_mutex_unlock(&(global->lock));
    if (global->play_thread && !global->is_finished) {
        pthread_join(global->play_thread, NULL);
        global->play_thread = 0;
    }
    pthread_mutex_lock(&(global->lock));
    global->stop_playback = 0;
    global->is_finished = FALSE;
    global->path = path;
    pthread_mutex_unlock(&(global->lock));
    if (pthread_create(&(global->play_thread), NULL, play_sound_thread,
            (void *) global)
        != 0) {
        perror("pthread_create failed");
    }
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
            play_sound(global->sounds[*highlight].path, global);
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

// void *play_sound_thread(void *global)
// {
//     const char *path = ((Global_t *) global)->path;
//     mpg123_handle *mh;
//     unsigned char *buffer;
//     size_t buffer_size;
//     size_t done;
//     int err;
//     int driver;
//     ao_device *dev;
//     ao_sample_format format;
//     int channels;
//     int encoding;
//     long rate;

//     ao_initialize();
//     driver = ao_default_driver_id();
//     mpg123_init();
//     mh = mpg123_new(NULL, &err);
//     buffer_size = mpg123_outblock(mh);
//     buffer = (unsigned char *) malloc(buffer_size * sizeof(unsigned char));
//     mpg123_open(mh, path);
//     mpg123_getformat(mh, &rate, &channels, &encoding);
//     format.bits = mpg123_encsize(encoding) * BITS;
//     format.rate = rate;
//     format.channels = channels;
//     format.byte_format = AO_FMT_NATIVE;
//     format.matrix = 0;
//     dev = ao_open_live(driver, &format, NULL);
//     while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
//         pthread_mutex_lock(&(((Global_t *) global)->lock));
//         if (((Global_t *) global)->stop_playback) {
//             ((Global_t *) global)->is_finished = TRUE;
//             pthread_mutex_unlock(&(((Global_t *) global)->lock));
//             break;
//         }
//         pthread_mutex_unlock(&(((Global_t *) global)->lock));
//         ao_play(dev, (char *) buffer, done);
//     }
//     pthread_mutex_lock(&(((Global_t *) global)->lock));
//     ((Global_t *) global)->is_finished = TRUE;
//     pthread_mutex_unlock(&(((Global_t *) global)->lock));
//     ((Global_t *) global)->is_finished = TRUE;
//     free(buffer);
//     ao_close(dev);
//     mpg123_close(mh);
//     mpg123_delete(mh);
//     mpg123_exit();
//     ao_shutdown();
//     return NULL;
// }

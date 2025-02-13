#include "header.h"

Sound sounds[MAX_SOUNDS];
int sound_count = 0;
const char *sounds_file_path = "data_sound/sounds.txt";

pthread_t play_thread;
int stop_playback = 0;

void read_sounds() {
  FILE *file = fopen(sounds_file_path, "r");
  if (!file) {
    file = fopen(sounds_file_path, "w");
    if (!file) {
      perror("Failed to create sounds.txt");
      exit(EXIT_FAILURE);
    }
    fclose(file);
    printw("Le fichier sounds.txt a été créé.\n");
    return;
  }

  char line[512];
  while (fgets(line, sizeof(line), file)) {
    char *name = strtok(line, ",");
    char *path = strtok(NULL, "\n");
    if (name && path) {
      strncpy(sounds[sound_count].name, name, sizeof(sounds[sound_count].name));
      strncpy(sounds[sound_count].path, path, sizeof(sounds[sound_count].path));
      sound_count++;
    }
  }
  fclose(file);

  if (sound_count == 0) {
    printw("Il n'y a pas de sons dans la liste.\n");
  }
}

void write_sounds() {
  FILE *file = fopen(sounds_file_path, "w");
  if (!file) {
    perror("Failed to open sounds.txt for writing");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < sound_count; i++) {
    fprintf(file, "%s,%s\n", sounds[i].name, sounds[i].path);
  }
  fclose(file);
}

void *play_sound_thread(void *arg) {
  const char *path = (const char *)arg;
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
  buffer = (unsigned char *)malloc(buffer_size * sizeof(unsigned char));

  mpg123_open(mh, path);
  mpg123_getformat(mh, &rate, &channels, &encoding);

  format.bits = mpg123_encsize(encoding) * BITS;
  format.rate = rate;
  format.channels = channels;
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = 0;
  dev = ao_open_live(driver, &format, NULL);

  while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
    if (stop_playback) {
      break;
    }
    ao_play(dev, (char *)buffer, done);
  }

  free(buffer);
  ao_close(dev);
  mpg123_close(mh);
  mpg123_delete(mh);
  mpg123_exit();
  ao_shutdown();

  return NULL;
}

void play_sound(const char *path) {
  stop_playback = 1;
  pthread_join(play_thread, NULL);
  stop_playback = 0;
  pthread_create(&play_thread, NULL, play_sound_thread, (void *)path);
}

void draw_menu(int highlight) {
  const char *choices[MAX_LINES] = {"Jouer un son", "Ajouter un son",
                                    "Mettre à jour un son", "Supprimer un son",
                                    "Aide"};
  for (int i = 0; i < MAX_LINES; i++) {
    if (i == highlight)
      attron(A_REVERSE);
    mvprintw(2 + i, 5, choices[i]);
    if (i == highlight)
      attroff(A_REVERSE);
  }
  refresh();
}

void print_help() {
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
                  int highlight) {
  clear();
  mvprintw(0, 0, title);
  for (int i = 0; i < num_sounds; i++) {
    if (i == highlight)
      attron(A_REVERSE);
    mvprintw(2 + i, 5, sounds[i].name);
    if (i == highlight)
      attroff(A_REVERSE);
  }
  mvprintw(2 + num_sounds, 5, "Retour");
  if (highlight == num_sounds)
    attron(A_REVERSE);
  mvprintw(2 + num_sounds, 5, "Retour");
  if (highlight == num_sounds)
    attroff(A_REVERSE);
  refresh();
}

void handle_add_sound() {
  char name[100] = "";
  char path[256] = "";
  int ch;
  long unsigned int name_pos = 0;
  long unsigned int path_pos = 0;

  clear();
  mvprintw(0, 0, "Enter sound name: ");
  move(1, 0);
  refresh();

  while ((ch = getch()) != '\n') {
    if (ch == KEY_BACKSPACE || ch == 127) {
      if (name_pos > 0) {
        name_pos--;
        name[name_pos] = '\0';
        mvprintw(1, name_pos, " ");
        move(1, name_pos);
      }
    } else if (name_pos < sizeof(name) - 1) {
      name[name_pos++] = ch;
      name[name_pos] = '\0';
      mvprintw(1, name_pos - 1, "%c", ch);
    }
    refresh();
  }

  mvprintw(2, 0, "Enter sound path: ");
  move(3, 0);
  refresh();

  while ((ch = getch()) != '\n') {
    if (ch == KEY_BACKSPACE || ch == 127) {
      if (path_pos > 0) {
        path_pos--;
        path[path_pos] = '\0';
        mvprintw(3, path_pos, " ");
        move(3, path_pos);
      }
    } else if (path_pos < sizeof(path) - 1) {
      path[path_pos++] = ch;
      path[path_pos] = '\0';
      mvprintw(3, path_pos - 1, "%c", ch);
    }
    refresh();
  }

  strncpy(sounds[sound_count].name, name, sizeof(name));
  strncpy(sounds[sound_count].path, path, sizeof(path));
  sound_count++;
  write_sounds();

  mvprintw(5, 0, "Sound '%s' added with path '%s'\n", name, path);
  refresh();
  getch();
}

void handle_update_sound() {
  int highlight = 0;
  int ch;
  while (1) {
    draw_submenu("Select a sound to update", sounds, sound_count, highlight);
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
      char name[100];
      char path[256];
      mvprintw(2 + sound_count + 1, 0,
               "Enter new sound name (press Enter to keep current): ");
      getstr(name);
      mvprintw(3 + sound_count + 1, 0,
               "Enter new sound path (press Enter to keep current): ");
      getstr(path);
      if (strlen(name) > 0)
        strncpy(sounds[highlight].name, name, sizeof(name));
      if (strlen(path) > 0)
        strncpy(sounds[highlight].path, path, sizeof(path));
      write_sounds();
      mvprintw(4 + sound_count + 1, 0, "Sound '%s' updated with path '%s'\n",
               sounds[highlight].name, sounds[highlight].path);
      refresh();
      getch();
      return;
    }
  }
}

void handle_delete_sound() {
  int highlight = 0;
  int ch;
  while (1) {
    draw_submenu("Select a sound to delete", sounds, sound_count, highlight);
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
      for (int i = highlight; i < sound_count - 1; i++)
        sounds[i] = sounds[i + 1];
      sound_count--;
      write_sounds();
      mvprintw(2 + sound_count + 1, 0, "Sound deleted\n");
      refresh();
      getch();
      return;
    }
  }
}

void handle_play_sound() {
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

int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  read_sounds();

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
    case 10: // Enter key
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
        print_help();
        break;
      }
      break;
    }
    clear();
    draw_menu(highlight);
  }

  endwin();
  return 0;
}
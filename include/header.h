#ifndef HEADER
#define HEADER

////////////////////////////////////////////////////////////
/// INCLUDE
////////////////////////////////////////////////////////////

#include "help_fc.h"
#include <ao/ao.h>
#include <mpg123.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

////////////////////////////////////////////////////////////
/// VALUES
////////////////////////////////////////////////////////////

#define MAX_LINES 5
#define MAX_SOUNDS 100
#define BITS 8

////////////////////////////////////////////////////////////
/// STRUCTS
////////////////////////////////////////////////////////////

typedef struct {
  char name[100];
  char path[256];
} Sound;

////////////////////////////////////////////////////////////
/// main
////////////////////////////////////////////////////////////

void draw_menu(int highlight);
void draw_submenu(const char *title, Sound *sounds, int num_sounds,
                  int highlight);
void handle_add_sound();
void handle_update_sound();
void handle_delete_sound();
void handle_play_sound();

#endif /* !HEADER */

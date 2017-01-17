#ifndef LUL_SCREEN
#define LUL_SCREEN
#include <ncurses.h>

typedef enum {
  INSERT,
  NORMAL
} screen_mode_t;

#define screen_t struct screen
#define this screen_t *self
struct screen {
  WINDOW *win;
  int width;
  int height;
  screen_mode_t mode;
  int (*draw_border)(this);
  int (*read_ch)(this);
  int (*write_ch)(this, chtype c);
  int (*mv_write_ch)(this, int y, int x, chtype c);
  int (*write)(this, char *fmt, ...);
  int (*mv_write)(this, int y, int x, char *fmt, ...);
  int (*set_background_ch)(this, chtype c);
};

screen_t *new_screen(int height, int width, int y, int x);
#endif

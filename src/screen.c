/*#include <ncurses.h>*/
/*#include <stdarg.h>*/
/*#include <stdio.h>*/
/*#include <strings.h>*/
/*#include <gc.h>*/
/*#include "screen.h"*/
/*#include "tools.h"*/

/*int set_background_ch(screen_t *self, chtype c){*/
  /*return wbkgd(self->win, c);*/
/*}*/

/*int mv_write(screen_t *self, int y, int x, char *fmt, ...){*/
  /*char *text  = (char *) GC_MALLOC(sizeof(char) * strlen(fmt) + 100);*/
  /*va_list fmt_args;*/
  /*va_start(fmt_args, fmt);*/
  /*vsprintf(text, fmt, fmt_args);*/
  /*va_end(fmt_args);*/
  /*mvwprintw(self->win, y, x, text);*/
  /*return 1;*/
/*}*/

/*int write(screen_t *self, char *fmt, ...){*/
  /*va_list fmt_args;*/
  /*va_start(fmt_args, fmt);*/
  /*vwprintw(self->win, fmt, fmt_args);*/
  /*va_end(fmt_args);*/
  /*return 1;*/
/*}*/

/*int mv_write_ch(screen_t *self, int y, int x, chtype c){*/
  /*return mvwaddch(self->win, y, x, c);*/
/*}*/

/*int write_ch(screen_t *self, chtype c){*/
  /*return waddch(self->win, c);*/
/*}*/

/*int read_ch(screen_t *self){*/
  /*return wgetch(self->win);*/
/*}*/

/*int draw_border(screen_t *self){*/
  /*return box(self->win, 0 , 0);*/
/*}*/

/*screen_t *new_screen(int height, int width,  int y, int x){*/
  /*screen_t *result = (screen_t *) GC_MALLOC(sizeof(screen_t));*/
  /*result->win = newwin(height, width, y, x);*/
  /*getmaxyx(result->win, result->height, result->width); */
  /*result->mode = INSERT;*/
  /*add_method(result, draw_border);*/
  /*add_method(result, write_ch);*/
  /*add_method(result, read_ch);*/
  /*add_method(result, mv_write_ch);*/
  /*add_method(result, write);*/
  /*add_method(result, mv_write);*/
  /*add_method(result, set_background_ch);*/

  /*return result;*/
/*}*/

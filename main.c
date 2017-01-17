#include <gc.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>

#include "tools.h"
#include "screen.h"

screen_t *main_window;

int main(){
  GC_INIT();
  initscr();
  cbreak();
  noecho();

  main_window = new_screen(0,0,0,0);
  call(main_window, draw_border);
  apply(main_window, write, "hello world");
  apply(main_window, mv_write, 2, 5, "it works!");
  /*apply(main_window, set_background_ch, ACS_BULLET);*/
  chtype c;

  wattrset(main_window->win, A_NORMAL );
  while((c = call(main_window, read_ch))){
    if(isprint(c) || isspace(c)) {
      wattron(main_window->win, A_REVERSE);
      apply(main_window, write_ch, c);
      wattroff(main_window->win, A_REVERSE);
    }
  };
}

void init_ncurses(){
}


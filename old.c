#include <ncurses.h>
#include <stdio.h>

#define key_up    259
#define key_down  258
#define key_left  260
#define key_right 261
int width, height;

enum {
  NORMAL,
  INSERT
} lul_mode = INSERT;

void where_am_i(int y, int x, int c){
  int before_x = x;
  int before_y = y;
  mvprintw(height - 1, 5, "%s", lul_mode == INSERT ? " insert " : " normal ");
  mvprintw(height - 1, width - 25, " c: %3d y: %2d x: %2d ", c, y, x);
  move(before_y, before_x);
}

void toggle_lul_mode(){
  if (lul_mode == NORMAL)
    lul_mode = INSERT;
  else 
    lul_mode = NORMAL;
}

int main(){
   /*init screen*/
  initscr();
  noecho();
  keypad(stdscr, TRUE);

  // init looks
  /*box(stdscr, 0, 0 );*/
  /*getmaxyx(stdscr, height, width);*/
  /*mvprintw(0, width - 10, "lulwut");*/
  /*move(1,1);*/

  /*SCREEN *wat =newterm("xterm", stdout, stdin);*/
  /*set_term(wat);*/

  WINDOW *lil_box = newwin(5,3,4,5);
  mvwaddch(lil_box, 1, 1, 'l');
  mvwaddch(lil_box, 2, 1, 'u');
  mvwaddch(lil_box, 3, 1, 'l');
  /*mvprintw(10, 4, "are you afraid of what you will find?");*/
  box(lil_box, 0, 0);
  wbkgd(lil_box, 'a');
  wrefresh(lil_box);
  wgetch(lil_box);
  /*refresh();*/

  /*wsyncup(lil_box);*/
  /*delwin(lil_box);*/
  /*mvprintw(10, 4, "                                     ");*/
  mvwaddch(lil_box, 2, 1, 'x');

   /*setup render vars*/
  int y, x;
  int c;
  while((c = getch()) != KEY_F(1)){
    getyx(stdscr, y, x);
    if (c == '1') {
      toggle_lul_mode();
      where_am_i(y, x, c);
      continue;
    }
    where_am_i(y, x, c);
    if(x == width - 1){
      move(y + 1, 1);
    }
    if( c == '\n'){
      move(y + 1, 1);
      continue;
    }
    if(c == '\t'){
      printw("  ");
      continue;
    }
    if( c == 127){
      if(x == 1){
        mvaddch(y - 1, width -  2, ' ');
        move(y -1, width - 2);
        continue;
      }
      mvaddch(y, x - 1, ' ');
      move(y, x-1);
      continue;
    }
    if(c == key_up){
      if(y > 1){
        move(y-1, x);
      }
      continue;
    }
    if(c == key_down){
      if(y < height){
        move(y+1, x);
      }
      continue;
    }
    if(c == key_left){
      if(x > 1){
        move(y, x - 1);
      }
      continue;
    }
    if(c == key_right){
      if(x < width - 1 ){
        move(y, x +1);
      }
      continue;
    }
    addch(c);
  }
  endwin();

  return 0;
}


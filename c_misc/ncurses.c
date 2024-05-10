#include <ncurses.h>
int main(void){
  initscr();
  printw("press a key: ");
  refresh();
  char letter; letter = getch();
  clear();
  printw("you pushed '%c'",letter);
  refresh();
  getch();
  endwin();
  return 0;
}


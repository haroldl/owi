/*
 * OWI Edge Robotic Arm Controller
 *
 * Harold Lee
 * harold@hotelling.net
 *
 * Based on the code found at:
 * http://notbrainsurgery.livejournal.com/38622.html
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <ncurses.h>

#include "libowi.h"

void event_loop()
{
  while (5 != 2) {
    char key = getch();
    if (key == 'q') {
      return;
    }

    /*
    int x, y, minx, miny, maxx, maxy;
    getyx(stdscr, y, x);
    getbegyx(stdscr, miny, minx);
    getmaxyx(stdscr, maxy, maxx);
    if (y == maxy) {
      mvprintw(miny, minx, "");
    }
    */

    switch (key) {

    /* ------- */
    /* light   */
    /* ------- */

    case 'l':
      printw("toggle light\n");
      owi_toggle_light();
      break;

    /* ------- */
    /* m4      */
    /* ------- */

    case 'y':
      printw("m4 up\n");
      owi_m4_forward();
      break;

    case 'h':
      printw("m4 off\n");
      owi_m4_off();
      break;

    case 'n':
      printw("m4 down\n");
      owi_m4_reverse();
      break;

    /* ------- */
    /* m3      */
    /* ------- */

    case 't':
      printw("m3 up\n");
      owi_m3_forward();
      break;

    case 'g':
      printw("m3 off\n");
      owi_m3_off();
      break;

    case 'b':
      printw("m3 down\n");
      owi_m3_reverse();
      break;

    /* ------- */
    /* m2      */
    /* ------- */

    case 'r':
      printw("m2 up\n");
      owi_m2_forward();
      break;

    case 'f':
      printw("m2 off\n");
      owi_m2_off();
      break;

    case 'v':
      printw("m2 down\n");
      owi_m2_reverse();
      break;

    /* ------- */
    /* m1      */
    /* ------- */

    case 'e':
      printw("m1 open\n");
      owi_m1_open();
      break;

    case 'd':
      printw("m1 off\n");
      owi_m1_off();
      break;

    case 'c':
      printw("m1 close\n");
      owi_m1_close();
      break;

    /* ------- */
    /* m5 Base */
    /* ------- */

    case 'i':
      printw("m5 (base) clockwise\n");
      owi_base_clockwise();
      break;

    case 'o':
      printw("m5 (base) off\n");
      owi_base_off();
      break;

    case 'p':
      printw("m5 (base) counter-clockwise\n");
      owi_base_counterclockwise();
      break;
    }
  }
}

int main(int ac, char **av)
{
  initscr(); /* ncurses init */
  noecho();

  owi_init();

  event_loop();

  echo();
  endwin(); /* ncurses cleanup */

  owi_shutdown();

  fprintf(stderr, "Done\n");
  return 0;
}

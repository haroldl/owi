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
#include <unistd.h>

#include "libowi.h"

int main(int argc, char **argv)
{
  printf("Running test...\n");
  owi_init();

  printf("owi_base_clockwise\n");
  owi_base_clockwise();
  sleep(1);
  owi_base_off();

  printf("owi_base_counterclockwise\n");
  owi_base_counterclockwise();
  sleep(1);
  owi_base_off();

  printf("owi_m4_forward\n");
  owi_m4_forward();
  sleep(1);
  owi_m4_off();

  printf("owi_m4_reverse\n");
  owi_m4_reverse();
  sleep(1);
  owi_m4_off();

  printf("owi_m3_forward\n");
  owi_m3_forward();
  sleep(1);
  owi_m3_off();

  printf("owi_m3_reverse\n");
  owi_m3_reverse();
  sleep(1);
  owi_m3_off();

  printf("owi_m2_forward\n");
  owi_m2_forward();
  sleep(1);
  owi_m2_off();

  printf("owi_m2_reverse\n");
  owi_m2_reverse();
  sleep(1);
  owi_m2_off();

  printf("owi_m1_close\n");
  owi_m1_close();
  sleep(1);
  owi_m1_off();

  printf("owi_m1_open\n");
  owi_m1_open();
  sleep(1);
  owi_m1_off();

  owi_shutdown();
  return 0;
}

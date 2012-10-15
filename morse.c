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

void dit()
{
  owi_toggle_light();
  usleep(100000);
  owi_toggle_light();
  usleep(100000);
}

void dah()
{
  owi_toggle_light();
  usleep(300000);
  owi_toggle_light();
  usleep(100000);
}

int main(int argc, char **argv)
{
  printf("Running test...\n");
  owi_init();

  printf("Morse code test\n");
  dit();
  dit();
  dit();
  dah();
  dah();
  dah();
  dit();
  dit();
  dit();

  owi_shutdown();
  return 0;
}

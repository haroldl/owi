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
#include <libusb-1.0/libusb.h>

#define EP_INTR (1 | LIBUSB_ENDPOINT_IN)

#define ARM_VENDOR       0x1267
#define ARM_PRODUCT      0x0000
#define CMD_DATALEN      3

struct libusb_device_handle *devh = NULL;

libusb_device * find_arm(libusb_device **devs)
{
  libusb_device *dev;
  int i = 0;

  while ((dev = devs[i++]) != NULL) {
    struct libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
      printw("Failed to get device descriptor\n");
      return NULL;
    }
    if(desc.idVendor == ARM_VENDOR &&
       desc.idProduct == ARM_PRODUCT)
      {
	return dev;
      }
  }
  return NULL;
}

int send_command(unsigned char b1, unsigned char b2, unsigned char b3)
{
  unsigned char cmd[3];
  cmd[0] = b1;
  cmd[1] = b2;
  cmd[2] = b3;

  printw("Sending %02X %02X %02X\n",
	 (int)cmd[0],
	 (int)cmd[1],
	 (int)cmd[2]
	 );

  if (devh == NULL) {
    return 0;
  }

  int actual_length = -1;
  int r;

  r = libusb_control_transfer(devh,
			      0x40, //uint8_t     bmRequestType,
			      6, //uint8_t    bRequest,
			      0x100, //uint16_t   wValue,
			      0,//uint16_t    wIndex,
			      cmd,
			      CMD_DATALEN,
			      0    
			      );
    
  if(!(r == 0 && actual_length >= CMD_DATALEN))
    {
      printw("Write err %d. len=%d\n",r,actual_length);
    }

  return r;
}

int stop()
{
  return send_command(0, 0, 0);
}

libusb_device ** detect_robot_arm()
{
  libusb_device **devs;
  libusb_device *dev;
  int r;
  ssize_t cnt;

  r = libusb_init(NULL);
  if (r < 0) {
    printw("Failed to initialize libusb\n");
    return NULL;
  }

  libusb_set_debug(NULL,2);
    
  cnt = libusb_get_device_list(NULL, &devs);
  if (cnt < 0)
    return NULL;
  dev=find_arm(devs);
  if(!dev) {
    printw("Robot Arm not found\n");
    return NULL;
  }

  r = libusb_open(dev,&devh);
  if(r!=0) {
    printw("Error opening device\n");
    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);
    return NULL;
  }

  return devs;
}

void event_loop()
{
  unsigned char cmd[3];
  cmd[0] = 0;
  cmd[1] = 0;
  cmd[2] = 0;

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
      printw("toggle light: ");
      cmd[2] = 1 - cmd[2];
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    /* ------- */
    /* m4      */
    /* ------- */

    case 'y':
      printw("m4 up: ");
      cmd[0] &= 0x3f;
      cmd[0] |= 0x80;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    case 'h':
      printw("m4 off: ");
      cmd[0] &= 0x3f;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    case 'n':
      printw("m4 down: ");
      cmd[0] &= 0x3f;
      cmd[0] |= 0x40;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    /* ------- */
    /* m3      */
    /* ------- */

    case 't':
      printw("m3 up: ");
      cmd[0] &= 0xcf;
      cmd[0] |= 0x20;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    case 'g':
      printw("m3 off: ");
      cmd[0] &= 0xcf;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    case 'b':
      printw("m3 down: ");
      cmd[0] &= 0xcf;
      cmd[0] |= 0x10;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    /* ------- */
    /* m2      */
    /* ------- */

    case 'r':
      printw("m2 up: ");
      cmd[1] &= 0xcf;
      cmd[1] |= 0x20;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    case 'f':
      printw("m2 off: ");
      cmd[1] &= 0xcf;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    case 'v':
      printw("m2 down: ");
      cmd[1] &= 0xcf;
      cmd[1] |= 0x10;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    /* ------- */
    /* m5 Base */
    /* ------- */

    case 'i':
      printw("m5 (base) clockwise: ");
      cmd[1] = 2;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    case 'o':
      printw("m5 (base) off: ");
      cmd[1] = 0;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;

    case 'p':
      printw("m5 (base) counter-clockwise: ");
      cmd[1] = 1;
      send_command(cmd[0], cmd[1], cmd[2]);
      break;
    }
  }
}

int main(int ac, char **av)
{
  initscr(); /* ncurses init */
  noecho();

  libusb_device **devs = detect_robot_arm();
  if (devs == NULL) {
    /* Take commands but there is no robot arm to send them to. */
    devh = NULL;
  }
  
  if (devh == NULL) {
    printw("*** NO ROBOT ARM FOUND ***\n");
  }
  printw("Press 'l' to turn the LED on/off...\n");
  printw("Press 'q' to quit.\n");
  refresh();

  event_loop();

  /* all stop! */
  send_command(0, 0, 0);

  libusb_close(devh);
  libusb_free_device_list(devs, 1);
  libusb_exit(NULL);

  echo();
  endwin(); /* ncurses cleanup */

  fprintf(stderr, "Done\n");
  return 0;
}

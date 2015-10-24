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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

#include "libowi.h"

#define EP_INTR (1 | LIBUSB_ENDPOINT_IN)

#define ARM_VENDOR       0x1267
#define ARM_PRODUCT      0x0000
#define CMD_DATALEN      3

/* Current action being executed by the arm. */
static unsigned char cmd[3];

static struct libusb_device_handle *devh = NULL;
static libusb_device **devs = NULL;

static libusb_device * _owi_find_arm(libusb_device **devs)
{
  libusb_device *dev;
  int i = 0;

  while ((dev = devs[i++]) != NULL) {
    struct libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
      fprintf(stderr, "Failed to get device descriptor\n");
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

static libusb_device ** _owi_detect_robot_arm()
{
  libusb_device **devs;
  libusb_device *dev;
  int r;
  ssize_t cnt;

  r = libusb_init(NULL);
  if (r < 0) {
    fprintf(stderr, "Failed to initialize libusb.\n");
    return NULL;
  }

  libusb_set_debug(NULL,2);
    
  cnt = libusb_get_device_list(NULL, &devs);
  if (cnt < 0)
    return NULL;
  dev = _owi_find_arm(devs);
  if(!dev) {
    fprintf(stderr, "Robot Arm not found.\n");
    return NULL;
  }

  r = libusb_open(dev,&devh);
  if(r!=0) {
    fprintf(stderr, "Error opening USB device for Robot Arm.\n");
    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);
    return NULL;
  }

  return devs;
}

void owi_init()
{
  devs = _owi_detect_robot_arm();
  if (devs == NULL) {
    devh = NULL;
    return;
  }

  cmd[0] = 0;
  cmd[1] = 0;
  cmd[2] = 0;
  owi_send_command(0, 0, 0);
}

int owi_send_command(unsigned char b1, unsigned char b2, unsigned char b3)
{
  cmd[0] = b1;
  cmd[1] = b2;
  cmd[2] = b3;

  fprintf(stderr, "Sending %02X %02X %02X\n",
	  (int)cmd[0], (int)cmd[1], (int)cmd[2]);

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
			      0);

  if(!(r == 0 && actual_length >= CMD_DATALEN)) {
    fprintf(stderr, "Write err %d. len=%d\n",r,actual_length);
  }

  return r;
}

int owi_stop()
{
  return owi_send_command(0, 0, 0);
}

int owi_toggle_light()
{
  cmd[2] = 1 - cmd[2];
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_light_off()
{
  cmd[2] = 0;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_light_on()
{
  cmd[2] = 1;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m4_forward()
{
  cmd[0] &= 0x3f;
  cmd[0] |= 0x80;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m4_off()
{
  cmd[0] &= 0x3f;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m4_reverse()
{
  cmd[0] &= 0x3f;
  cmd[0] |= 0x40;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m3_forward()
{
  cmd[0] &= 0xcf;
  cmd[0] |= 0x20;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m3_off()
{
  cmd[0] &= 0xcf;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m3_reverse()
{
  cmd[0] &= 0xcf;
  cmd[0] |= 0x10;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m2_forward()
{
  cmd[0] &= 0xf3;
  cmd[0] |= 0x08;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m2_off()
{
  cmd[0] &= 0xf3;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m2_reverse()
{
  cmd[0] &= 0xf3;
  cmd[0] |= 0x04;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m1_close()
{
  cmd[0] &= 0xfc;
  cmd[0] |= 0x01;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m1_off()
{
  cmd[0] &= 0xfc;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_m1_open()
{
  cmd[0] &= 0xfc;
  cmd[0] |= 0x02;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_base_clockwise()
{
  cmd[1] = 2;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_base_off()
{
  cmd[1] = 0;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

int owi_base_counterclockwise()
{
  cmd[1] = 1;
  return owi_send_command(cmd[0], cmd[1], cmd[2]);
}

void owi_shutdown()
{
  /* all stop! */
  owi_send_command(0, 0, 0);

  if (devh != NULL) {
    libusb_close(devh);
  }

  if (devs != NULL) {
    libusb_free_device_list(devs, 1);
  }

  libusb_exit(NULL);
}

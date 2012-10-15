#ifndef __LIBOWI_H__
#define __LIBOWI_H__

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

void owi_init();
void owi_shutdown();

/* Lower-level call to set the motion of all motors and the light at once. */
int owi_send_command(unsigned char b1, unsigned char b2, unsigned char b3);

/* Stop all motion and turn off the light. */
int owi_stop();

int owi_toggle_light();
int owi_light_off();
int owi_light_on();

/* The base is M5 */
int owi_base_clockwise();
int owi_base_off();
int owi_base_counterclockwise();

int owi_m4_forward();
int owi_m4_off();
int owi_m4_reverse();

int owi_m3_forward();
int owi_m3_off();
int owi_m3_reverse();

int owi_m2_forward();
int owi_m2_off();
int owi_m2_reverse();

/* M1 controls the grip */
int owi_m1_close();
int owi_m1_off();
int owi_m1_open();

#endif

/*
 * Adapter code to allow access to the owi.c functions from Python.
 */
#include <Python.h>
#include <time.h>
#include <stdbool.h>
#include "libowi.h"

static bool parse_usleep_arg(PyObject *args, long *out_usleep_time) {
  double sleep_time_seconds = 0.0;
  if (!PyArg_ParseTuple(args, "d", &sleep_time_seconds)) {
    return false;
  }
  long usleep_time = (long) (sleep_time_seconds * 1000000);
  *out_usleep_time = usleep_time;
  return true;
}

static PyObject * py_owi_init(PyObject *self, PyObject *args) {
  owi_init();
  return Py_None;
}

static PyObject * py_owi_shutdown(PyObject *self, PyObject *args) {
  owi_shutdown();
  return Py_None;
}

static PyObject * py_owi_toggle_light(PyObject *self, PyObject *args) {
  owi_toggle_light();
  return Py_None;
}

static PyObject * py_owi_light_on(PyObject *self, PyObject *args) {
  owi_light_on();
  return Py_None;
}

static PyObject * py_owi_light_off(PyObject *self, PyObject *args) {
  owi_light_off();
  return Py_None;
}

static PyObject * py_owi_base_left(PyObject *self, PyObject *args) {
  long usleep_time;
  if (!parse_usleep_arg(args, &usleep_time)) {
    return NULL;
  }

  owi_base_clockwise();
  usleep(usleep_time);
  owi_base_off();
  return Py_None;
}

static PyObject * py_owi_base_right(PyObject *self, PyObject *args) {
  long usleep_time;
  if (!parse_usleep_arg(args, &usleep_time)) {
    return NULL;
  }

  owi_base_counterclockwise();
  usleep(usleep_time);
  owi_base_off();
  return Py_None;
}

static PyObject * py_owi_shoulder_up(PyObject *self, PyObject *args) {
  long usleep_time;
  if (!parse_usleep_arg(args, &usleep_time)) {
    return NULL;
  }

  owi_m4_forward();
  usleep(usleep_time);
  owi_m4_off();
  return Py_None;
}

static PyObject * py_owi_shoulder_down(PyObject *self, PyObject *args) {
  long usleep_time;
  if (!parse_usleep_arg(args, &usleep_time)) {
    return NULL;
  }

  owi_m4_reverse();
  usleep(usleep_time);
  owi_m4_off();
  return Py_None;
}

static PyObject * py_owi_elbow_up(PyObject *self, PyObject *args) {
  long usleep_time;
  if (!parse_usleep_arg(args, &usleep_time)) {
    return NULL;
  }

  owi_m3_forward();
  usleep(usleep_time);
  owi_m3_off();
  return Py_None;
}

static PyObject * py_owi_elbow_down(PyObject *self, PyObject *args) {
  long usleep_time;
  if (!parse_usleep_arg(args, &usleep_time)) {
    return NULL;
  }

  owi_m3_reverse();
  usleep(usleep_time);
  owi_m3_off();
  return Py_None;
}

static PyObject * py_owi_wrist_up(PyObject *self, PyObject *args) {
  long usleep_time;
  if (!parse_usleep_arg(args, &usleep_time)) {
    return NULL;
  }

  owi_m2_forward();
  usleep(usleep_time);
  owi_m2_off();
  return Py_None;
}

static PyObject * py_owi_wrist_down(PyObject *self, PyObject *args) {
  long usleep_time;
  if (!parse_usleep_arg(args, &usleep_time)) {
    return NULL;
  }

  owi_m2_reverse();
  usleep(usleep_time);
  owi_m2_off();
  return Py_None;
}

static PyObject * py_owi_grip_open(PyObject *self, PyObject *args) {
  long usleep_time;
  if (!parse_usleep_arg(args, &usleep_time)) {
    return NULL;
  }

  owi_m1_open();
  usleep(usleep_time);
  owi_m1_off();
  return Py_None;
}

static PyObject * py_owi_grip_close(PyObject *self, PyObject *args) {
  long usleep_time;
  if (!parse_usleep_arg(args, &usleep_time)) {
    return NULL;
  }

  owi_m1_close();
  usleep(usleep_time);
  owi_m1_off();
  return Py_None;
}

static PyObject * py_owi_stop(PyObject *self, PyObject *args) {
  owi_stop();
  return Py_None;
}

static PyMethodDef OwiMethods[] = {
  { "init",          py_owi_init,          METH_VARARGS, "Initialize the OWI robot arm via USB." },
  { "shutdown",      py_owi_shutdown,      METH_VARARGS, "Shut down the OWI robot arm via USB." },
  { "light_toggle",  py_owi_toggle_light,  METH_VARARGS, "Toggle the light on or off." },
  { "light_on",      py_owi_light_on,      METH_VARARGS, "Turn the light on." },
  { "light_off",     py_owi_light_off,     METH_VARARGS, "Turn the light off." },
  { "base_left",     py_owi_base_left,     METH_VARARGS, "Turn the base left for the given number of seconds." },
  { "base_right",    py_owi_base_right,    METH_VARARGS, "Turn the base right for the given number of seconds." },
  { "shoulder_up",   py_owi_shoulder_up,   METH_VARARGS, "Move the shoulder up for the given number of seconds." },
  { "shoulder_down", py_owi_shoulder_down, METH_VARARGS, "Move the shoulder down for the given number of seconds." },
  { "elbow_up",      py_owi_elbow_up,      METH_VARARGS, "Move the elbow up for the given number of seconds." },
  { "elbow_down",    py_owi_elbow_down,    METH_VARARGS, "Move the elbow down for the given number of seconds." },
  { "wrist_up",      py_owi_wrist_up,      METH_VARARGS, "Move the wrist up for the given number of seconds." },
  { "wrist_down",    py_owi_wrist_down,    METH_VARARGS, "Move the wrist down for the given number of seconds." },
  { "grip_open",     py_owi_grip_open,     METH_VARARGS, "Open the grip for the given number of seconds." },
  { "grip_close",    py_owi_grip_close,    METH_VARARGS, "Close the grip for the given number of seconds." },
  { "stop",         py_owi_stop,           METH_VARARGS, "Stop all motion of the robot arm and turn off the light." },
  { NULL, NULL, 0, NULL } /* sentinal */
};

static struct PyModuleDef owimodule = {
  PyModuleDef_HEAD_INIT,
  "owi",
  NULL,
  -1,
  OwiMethods
};

PyMODINIT_FUNC PyInit_owi(void) {
  return PyModule_Create(&owimodule);
}

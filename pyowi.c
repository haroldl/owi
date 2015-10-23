/*
 * Adapter code to allow access to the owi.c functions from Python.
 */
#include <Python.h>
#include "libowi.h"

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

static PyMethodDef OwiMethods[] = {
  { "init",         py_owi_init,         METH_VARARGS, "Initialize the OWI robot arm via USB." },
  { "shutdown",     py_owi_shutdown,     METH_VARARGS, "Shut down the OWI robot arm via USB." },
  { "toggle_light", py_owi_toggle_light, METH_VARARGS, "Toggle the light on or off." },
  { "light_on",     py_owi_light_on,     METH_VARARGS, "Turn the light on." },
  { "light_off",    py_owi_light_off,    METH_VARARGS, "Turn the light off." },
  { NULL, NULL, 0, NULL } /* sentinal */
};

static struct PyModuleDef owimodule = {
  PyModuleDef_HEAD_INIT,
  "owi",
  NULL,
  -1,
  OwiMethods
};

PyMODINIT_FUNC PyInit_owiedge(void) {
  return PyModule_Create(&owimodule);
}

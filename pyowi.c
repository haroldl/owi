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

static PyMethodDef OwiMethods[] = {
  { "init", py_owi_init, METH_VARARGS, "Initialize the OWI robot arm via USB." },
  { "shutdown", py_owi_shutdown, METH_VARARGS, "Shut down the OWI robot arm via USB." },
  { NULL, NULL, 0, NULL }
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

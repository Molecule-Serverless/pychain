#include <Python.h>
#include <stdio.h>
#include "moleculeIPC.h"

#define IPC_USE_LOCAL 0

/* int divide(int, int, int *) */
static PyObject *py_divide(PyObject *self, PyObject *args) {
  int a, b, quotient, remainder;
  if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
    return NULL;
  }
  quotient = a / b;
  remainder = a - b * quotient;
  return Py_BuildValue("(ii)", quotient, remainder);
}

static PyObject *py_init_server(PyObject *self, PyObject *args) {
  int fifo_self, global_fifo, uuid;
  if (!PyArg_ParseTuple(args, "i", &uuid)) {
    return NULL;
  }
  init_server(&fifo_self, &global_fifo, uuid);
  return Py_BuildValue("(ii)", fifo_self, global_fifo);
} 

static PyObject *py_global_fifo_connect(PyObject *self, PyObject *args) {
  int global_uuid, global_fifo_connection;
  if (!PyArg_ParseTuple(args, "i", &global_uuid))
    return Py_BuildValue("i", -1);
#if IPC_USE_LOCAL
  global_fifo_connection = fifo_connect(global_uuid);
#else //moleculeOS IPC
  global_fifo_connection = global_fifo_connect(global_uuid);
#endif
  return Py_BuildValue("i", global_fifo_connection);

} 

static PyObject *py_send_to_server(PyObject *self, PyObject *args){
  int connection; 
  char* message;
  if (!PyArg_ParseTuple(args, "is", &connection, &message)){
    return Py_BuildValue("i", -1); 
  }
#if IPC_USE_LOCAL
  fifo_write(connection, message, strlen(message));
#else //moleculeOS IPC
  global_fifo_write(connection, message, strlen(message));
#endif

  return Py_BuildValue("i", 0); 
}

static PyObject *py_receive_from_client(PyObject *self, PyObject *args) {
  int fifo_self, global_fifo;
  char* response;
  if (!PyArg_ParseTuple(args, "ii", &fifo_self, &global_fifo)) {
    return NULL;
  }
  response = receive_from_client(fifo_self, global_fifo);
  fprintf(stderr, "receive from client: %s\n", response);
  // return Py_BuildValue("s#", response, strlen(response) + 1);
  return PyUnicode_Decode(response, strlen(response), "ascii", "ignore");
}


static PyMethodDef MoleculeOSMethods[] = {
    {"divide", py_divide, METH_VARARGS, "Integer division"},
    {"init_server", py_init_server, METH_VARARGS, "Init molecule server"},
    {"receive_from_client", py_receive_from_client, METH_VARARGS, "Receive messages from client"},
    {"global_fifo_connect", py_global_fifo_connect, METH_VARARGS, "Connect existing global ipc server"},
    {"send_to_server", py_send_to_server, METH_VARARGS, "send response to server"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef MoleculeOSMod = {
    PyModuleDef_HEAD_INIT,
    "moleculeIPC",
    NULL,
    -1,
    MoleculeOSMethods
};

PyMODINIT_FUNC
PyInit_moleculeIPC(void)
{
    return PyModule_Create(&MoleculeOSMod);
}

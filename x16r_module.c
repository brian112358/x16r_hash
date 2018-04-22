#include <Python.h>

#include "x16r.h"

static PyObject *x16r_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    x16r_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    x16r_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef X16RMethods[] = {
    { "getPoWHash", x16r_getpowhash, METH_VARARGS, "Returns the proof of work hash using X16R hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef X16RModule = {
    PyModuleDef_HEAD_INIT,
    "x16r_hash",
    "...",
    -1,
    X16RMethods
};

PyMODINIT_FUNC PyInit_x16r_hash(void) {
    return PyModule_Create(&X16RModule);
}

#else

PyMODINIT_FUNC initx16r_hash(void) {
    (void) Py_InitModule("x16r_hash", X16RMethods);
}
#endif

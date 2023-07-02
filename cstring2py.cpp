#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "numpy/arrayobject.h"


int main(){

// qm-mm system to test
    const int qm_num = 3, mm_num = 2;
    std::string qm_kinds[qm_num] = {"N", "O", "H"};

    for (int n = 0; n < qm_num; n ++)
    {   std::cout << qm_kinds[n] << ":";
    }

    Py_Initialize();
    import_array();

    PyObject* pQMKinds = PyList_New(qm_num);
    for (int i = 0; i < qm_num; i++)
    {
        PyObject* pStr = PyUnicode_FromString(qm_kinds[i].c_str());
        PyList_SetItem(pQMKinds, i, pStr);
    }

    // import mymodule
    const char *module_name = "para_printer";
    PyObject *pName = PyUnicode_FromString(module_name);
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    // import and call function
    const char *func_name = "printQMKinds";
    PyObject *pFunc = PyObject_GetAttrString(pModule, func_name);
    PyObject *pReturn = PyObject_CallFunctionObjArgs(pFunc, pQMCoords, pQMKinds, NULL);

    PyObject *pReturnCoords = PyTuple_GetItem(pReturn, 1);
    PyObject *pReturnKinds = PyTuple_GetItem(pReturn, 2);


    return 0;
}

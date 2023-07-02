#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "numpy/arrayobject.h"


int main()
{

// qm-mm system to test
    const int qm_num = 3, mm_num = 2;
    std::string qm_kinds[qm_num] = {"H", "O", "H"};
    const char* qm_basis = "ccpvdz";
    int qm_charge = 0, qm_mult = 1;
    double qm_coords[qm_num][3] = {{0.0,0.0,1.0},{0.0,0.0,0.0},{0.0,1.0,0.0}};
    double mm_coords[mm_num][3] = {{0.5,2.0,1.0},{-0.5,2.0,1.0}};
    double mm_charges[mm_num] = {0.3, -0.3};

    Py_Initialize();
    import_array();

    PyObject* pQMCoords = PyList_New(qm_num);
    for (int i = 0; i < qm_num; i++)
    {
        PyObject* pQMCoords_row = PyList_New(3);

        PyObject* pQMCoords_x = PyFloat_FromDouble(qm_coords[i][0]);
        PyList_SetItem(pQMCoords_row, 0, pQMCoords_x);

        PyObject* pQMCoords_y = PyFloat_FromDouble(qm_coords[i][1]);
        PyList_SetItem(pQMCoords_row, 1, pQMCoords_y);

        PyObject* pQMCoords_z = PyFloat_FromDouble(qm_coords[i][2]);
        PyList_SetItem(pQMCoords_row, 2, pQMCoords_z);

        PyList_SetItem(pQMCoords, i, pQMCoords_row);
    }

    PyObject* pMMCoords = PyList_New(mm_num);
    for (int i = 0; i < mm_num; i++)
    {
        PyObject* pMMCoords_row = PyList_New(3);

        PyObject* pMMCoords_x = PyFloat_FromDouble(mm_coords[i][0]);
        PyList_SetItem(pMMCoords_row, 0, pMMCoords_x);

        PyObject* pMMCoords_y = PyFloat_FromDouble(mm_coords[i][1]);
        PyList_SetItem(pMMCoords_row, 1, pMMCoords_y);

        PyObject* pMMCoords_z = PyFloat_FromDouble(mm_coords[i][2]);
        PyList_SetItem(pMMCoords_row, 2, pMMCoords_z);

        PyList_SetItem(pMMCoords, i, pMMCoords_row);
    }

    PyObject* pMMCharges = PyList_New(mm_num);
    for (int i = 0; i < mm_num; i++)
    {
        PyObject* pStr = PyFloat_FromDouble(mm_charges[i]);
        PyList_SetItem(pMMCharges, i, pStr);
    }

    PyObject* pQMKinds = PyList_New(qm_num);
    for (int i = 0; i < qm_num; i++)
    {
        PyObject* pStr = PyUnicode_FromString(qm_kinds[i].c_str());
        PyList_SetItem(pQMKinds, i, pStr);
    }

    PyObject* pQMBasis = PyUnicode_FromString(qm_basis);
    PyObject* pQMMult = PyLong_FromLong(qm_mult);
    PyObject* pQMCharge = PyLong_FromLong(qm_charge);


    // import mymodule
    const char* module_name = "pyscfdriver";
    PyObject* pName = PyUnicode_FromString(module_name);
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    //import and call function
    const char* func_name = "QMcalculation";
    PyObject* pFunc = PyObject_GetAttrString(pModule, func_name);
    PyObject* pReturn = PyObject_CallFunctionObjArgs(pFunc,
            pQMCoords, pQMKinds, pQMBasis, pQMMult, pQMCharge,
            pMMCoords, pMMCharges, NULL);
    PyObject* pQMMMEnergy = PyTuple_GetItem(pReturn, 0);
    PyObject* pQMForce = PyTuple_GetItem(pReturn, 1);

    double qmmmEnergy(0);
    double qmmmForce(0);
    double qm_force[qm_num][3] = {{0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0}};
    double qm_force_temp(0);

    qmmmEnergy = PyFloat_AsDouble(pQMMMEnergy);
    std::cout << "C++ received energy = " << std::setprecision(15) << qmmmEnergy << std::endl;

    // PyObject* pQMForceRow = PyTuple_GetItem(pQMForce, 0);
    // PyObject* pQMForce_temp = PyTuple_GetItem(pQMForceRow, 0);
    // qm_force_temp = PyFloat_AsDouble(pQMForce_temp);
    // std::cout << "C++ received force = " << std::setprecision(15) << qm_force_temp << std::endl;

    PyArrayObject *np_ret = reinterpret_cast<PyArrayObject*>(pQMForce);


    // Py_ssize_t qm_force_rows = PyList_Size(pQMForce);;
    // Py_ssize_t qm_force_columns;

    // std::cout << "rows" << qm_force_rows << std::endl;
    // std::cout << "columns" << qm_force_columns << std::endl;

    // for (int i = 0; i < qm_num; i++)
    // {
    //     PyObject* pQMForceRow = PyList_GetItem(pQMForce, i);
    //     for (int j = 0; j < 2; j++)
    //     {
    //         PyObject* pQMForceCompTemp = PyList_GetItem(pQMForceRow, j);
    //         qm_force_temp = PyFloat_AsDouble(pQMForceCompTemp);
    //         qm_force[i][j] = qm_force_temp;
    //     }
    // }

    // std::cout << "   qm_kind   " <<  "      Fx      " << "      Fy      " << "      Fz      " << std::endl;
    // for (int i = 0; i < qm_num; i ++)
    // {
    //     std::cout << " " << qm_kinds[i];
    //     std::cout << "  " << std::setprecision(10) << qm_force[i][0] << "  ";
    //     std::cout << "  " << std::setprecision(10) << qm_force[i][1] << "  ";
    //     std::cout << "  " << std::setprecision(10) << qm_force[i][2] << "  " << std::endl;
    // }

    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);

    Py_Finalize();

    return 0;
}

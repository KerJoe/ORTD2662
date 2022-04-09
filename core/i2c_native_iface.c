#define RTDMULTIPROG_PATH "/media/all/Data/Users/Misha/Documents/Projects/RTD2662/RTDMultiProg"
#define INTERFACE   "mcp2221"
#define DEVICE      0
#define SETTINGS    ""



#include "Python.h"
#include "stdint.h"


#define CHECK(_par) if (!_par) { printf("Error in function \"%s\" at line %i\n", __FUNCTION__, __LINE__); PyErr_Print(); return 1; }
#define CHECKNR(_par) if (!_par) { printf("Error in function \"%s\" at line %i\n", __FUNCTION__, __LINE__); PyErr_Print(); }

// Controller's address on I2C bus
#define RTD_ISP_ADR         0x4A
#define RTD_ISP_AUTOINC_ADR (RTD_ISP_ADR | 1)

PyObject *pI2C;


void ScalerWriteByte(uint8_t address, uint8_t data)
{
    PyObject* result = PyObject_CallMethod(pI2C, "write_i2c", "(i[ii])", RTD_ISP_ADR, (int)address, (int)data); CHECKNR(result)
    Py_XDECREF(result);
}

uint8_t ScalerReadByte(uint8_t address)
{
    PyObject* retList = PyObject_CallMethod(pI2C, "read_i2c", "(ii)", RTD_ISP_ADR, 1); CHECKNR(retList)
    CHECKNR(PyList_Check(retList))
    PyObject* retLong = PyList_GetItem(retList, 0); CHECKNR(retLong)
    CHECKNR(PyLong_Check(retLong))
    uint8_t ret = PyLong_AsLong(retLong);

    Py_XDECREF(retList);
    Py_XDECREF(retLong);

    return ret;
}


int __attribute__ ((constructor)) begin_i2c_native_iface()
{
    Py_Initialize();

    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *sys_path = PyObject_GetAttrString(sys, "path");
    PyObject *folder_path = PyUnicode_FromString(RTDMULTIPROG_PATH);
    PyList_Append(sys_path, folder_path);

    Py_XDECREF(sys);
    Py_XDECREF(sys_path);
    Py_XDECREF(folder_path);

    PyObject* pName = PyUnicode_FromString("interfaces." INTERFACE ".main"); CHECK(pName)
    PyObject* pModule = PyImport_Import(pName); CHECK(pModule)
    PyObject* pDict = PyModule_GetDict(pModule); CHECK(pDict)
    PyObject* pClass = PyDict_GetItemString(pDict, "I2C"); CHECK(pClass)
    CHECK(PyCallable_Check(pClass))
    pI2C = PyObject_CallObject(pClass, NULL);

    Py_XDECREF(pName);
    Py_XDECREF(pModule);
    Py_XDECREF(pDict);
    Py_XDECREF(pClass);

    PyObject* result = PyObject_CallMethod(pI2C, "init_i2c", "(iz)", DEVICE, SETTINGS); CHECK(result)
    Py_XDECREF(result);

    ScalerWriteByte(0x6F, 0x80);

    return 0;
}

int __attribute__ ((destructor)) end_i2c_native_iface()
{
    ScalerWriteByte(0xEE, 0x02);
    ScalerWriteByte(0x6F, 0x01);

    PyObject* result = PyObject_CallMethod(pI2C, "deinit_i2c", ""); CHECK(result)
    Py_XDECREF(result);

    Py_XDECREF(pI2C);
    Py_Finalize();

    return 0;
}
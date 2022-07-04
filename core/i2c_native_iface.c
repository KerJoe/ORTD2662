// Compile only for native
// NOTE: XSFRWriteByte and XSFRReadByte declarations are in xsfr.h
#ifndef __SDCC

#if 0
#define RTDMULTIPROG_PATH "../RTDMultiProg"
#define INTERFACE   "i2cdev"
#define DEVICE      0
#define SETTINGS    ""


#include "Python.h"
#include "stdint.h"


#define CHECK(__par) if (!__par) { printf("Error in function \"%s\" at line %i\n", __FUNCTION__, __LINE__); PyErr_Print(); return 1; }
#define CHECKNR(__par) if (!__par) { printf("Error in function \"%s\" at line %i\n", __FUNCTION__, __LINE__); PyErr_Print(); }

// Controller's address on I2C bus
#define RTD_ISP_ADR         0x4A
#define RTD_ISP_AUTOINC_ADR (RTD_ISP_ADR | 1)

PyObject* pI2C;


void XSFRWriteByte(uint8_t address, uint8_t data)
{
    PyObject* result = PyObject_CallMethod(pI2C, "write_i2c", "(i[ii])", RTD_ISP_ADR, (int)address, (int)data); CHECKNR(result)
    Py_XDECREF(result);
}

uint8_t XSFRReadByte(uint8_t address)
{
    PyObject* result  = PyObject_CallMethod(pI2C, "write_i2c", "(i[i])", RTD_ISP_ADR, (int)address); CHECKNR(result)
    PyObject* retList = PyObject_CallMethod(pI2C, "read_i2c", "(ii)", RTD_ISP_ADR, 1); CHECKNR(retList)
    CHECKNR(PyList_Check(retList))
    PyObject* retLong = PyList_GetItem(retList, 0); CHECKNR(retLong)
    CHECKNR(PyLong_Check(retLong))
    uint8_t ret = PyLong_AsLong(retLong);

    Py_XDECREF(result);
    Py_XDECREF(retList);
    Py_XDECREF(retLong);

    return ret;
}


int __attribute__ ((constructor)) begin_i2c_native_iface()
{
    Py_Initialize();

    PyObject* sys = PyImport_ImportModule("sys");
    PyObject* sys_path = PyObject_GetAttrString(sys, "path");
    PyObject* folder_path = PyUnicode_FromString(RTDMULTIPROG_PATH);
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

    XSFRWriteByte(0xEE, 0x02);
    XSFRWriteByte(0x6F, 0x80);

    return 0;
}

int __attribute__ ((destructor)) end_i2c_native_iface()
{
    XSFRWriteByte(0xEE, 0x02);
    XSFRWriteByte(0x6F, 0x01);

    PyObject* result = PyObject_CallMethod(pI2C, "deinit_i2c", ""); CHECK(result)
    Py_XDECREF(result);

    Py_XDECREF(pI2C);
    Py_Finalize();

    return 0;
}
#else

#include <sys/ioctl.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#define DEVICE "0"

// Controller's address on I2C bus
#define RTD_ISP_ADR         0x4A
#define RTD_ISP_AUTOINC_ADR (RTD_ISP_ADR | 1)

int fi2c;
#define I2C_SLAVE 0x0703


void XSFRWriteByte(uint8_t address, uint8_t data)
{
    ioctl(fi2c, I2C_SLAVE, RTD_ISP_ADR);
    uint8_t buf[] = { address, data };
    write(fi2c, &buf, 2);
}

uint8_t XSFRReadByte(uint8_t address)
{
    ioctl(fi2c, I2C_SLAVE, RTD_ISP_ADR);
    write(fi2c, &address, 1);
    uint8_t data;
    read(fi2c, &data, 1);
    return data;
}


int __attribute__ ((constructor)) begin_i2c_native_iface()
{
    fi2c = open("/dev/i2c-"DEVICE, O_RDWR);

    XSFRWriteByte(0x6F, 0x80);
    XSFRWriteByte(0xEE, 0x02);
    XSFRWriteByte(0x6F, 0x80);

    return 0;
}

int __attribute__ ((destructor)) end_i2c_native_iface()
{
    XSFRWriteByte(0xEE, 0x02);
    XSFRWriteByte(0x6F, 0x01);

    close(fi2c);

    return 0;
}

#endif

#endif // #ifndef __SDCC
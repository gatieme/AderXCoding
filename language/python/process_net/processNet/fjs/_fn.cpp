/*#include "/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7/Python.h"
#include<stdio.h>

static PyObject* add(PyObject *self, PyObject *args)
{
    //把输入的Python对象转换为C/C++能识别的数据

    int arg1, arg2;
    if(!PyArg_ParseTuple(args, "ii", &arg1, &arg2))
    return NULL;
    //调用C/C++函数，得到结果

    int result = arg1 + arg2;
    //把得到的结果包装成Python对象，并返回

    return (PyObject*)Py_BuildValue("i", result);
}

static PyMethodDef wrap_methods[] ={
     {"add", add, METH_VARARGS,
        "Return currently connected users as a list of tuples"},

     {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC init_fn (void)
{
    printf("hello\n");
    PyObject *module = Py_InitModule("_fn ", wrap_methods);
    if (module == NULL) {
        printf("null\n");
    }
    printf("over\n");
}*/

    /*
 * Copyright (c) 2009, Giampaolo Rodola'. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * Functions specific to all POSIX compliant platforms.
 */
 #include "app.h"

#include <Python.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/resource.h>
#include "_fn.h"


App *app = NULL;

static PyObject* testProcess(PyObject *self, PyObject *args)
{
    //把输入的Python对象转换为C/C++能识别的数据
    int pid;
    if(!PyArg_ParseTuple(args, "i", &pid))
        return NULL;
    //调用C/C++函数，得到结果
    double out = -1;
    pthread_mutex_lock(&pmutex);
    size_t size = app->processs.size();
    for (int i = 0; i< size; i++) {
        Process *now = app->processs[i];
        if (now->pid == pid) {
            out = now->sudu;
            break;
        }
    }
    pthread_mutex_unlock(&pmutex);
    //把得到的结果包装成Python对象，并返回
    PyObject *parm = (PyObject*)Py_BuildValue("d", out);
    return parm;

}

static PyObject* removeProcess(PyObject *self, PyObject *args)
{
    //把输入的Python对象转换为C/C++能识别的数据
    int pid;
    if(!PyArg_ParseTuple(args, "i", &pid))
        return NULL;
    //调用C/C++函数，得到结果
    pthread_mutex_lock(&pmutex);
    app->removeProcess(pid);
    pthread_mutex_unlock(&pmutex);


    //把得到的结果包装成Python对象，并返回
    PyObject *parm = (PyObject*)Py_BuildValue("d", 0);

    return parm;

}


static PyObject* addProcess(PyObject *self, PyObject *args)
{
    //把输入的Python对象转换为C/C++能识别的数据
    int pid;
    if(!PyArg_ParseTuple(args, "i", &pid))
        return NULL;
    //调用C/C++函数，得到结果
    Process *pro = new Process(pid);
    PyObject *parm = NULL;
    if (pro->inodes == NULL) {
        delete pro;
        parm = (PyObject*)Py_BuildValue("d", -1);
    } else {
        pthread_mutex_lock(&pmutex);
        app->addProcess(pro);
        pthread_mutex_unlock(&pmutex);
        parm = (PyObject*)Py_BuildValue("d", 0);
    }
    


    //把得到的结果包装成Python对象，并返回

    return parm;

}






/*
 * define the psutil C module methods and initialize the module.
 */


static PyMethodDef
PsutilMethods[] =
{
     {"removeProcess", removeProcess, METH_VARARGS,
     "Return process priority"},
     {"testProcess", testProcess, METH_VARARGS,
     "Return process priority"},
     {"addProcess", addProcess, METH_VARARGS,
     "Return process priority"},
    {NULL, NULL, 0, NULL}
};




struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
#endif

#if PY_MAJOR_VERSION >= 3

static int
psutil_posix_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int
psutil_posix_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "psutil_posix",
    NULL,
    sizeof(struct module_state),
    PsutilMethods,
    NULL,
    psutil_posix_traverse,
    psutil_posix_clear,
    NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC PyInit__fn(void)

#else
#define INITERROR return


void init_fn(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("_fn", PsutilMethods);
#endif
    if (module == NULL) {
        INITERROR;
    }
    // 
    app = new App(10);
    app->dispatch();
#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}

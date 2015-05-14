#include <Python.h>
#include "nrflib.h"

static PyObject* NrfPy_Init(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }
    
    int  Ret;
    char Status;
    Ret  = NRF_Init();    
    Ret += NRF_ClearRX_DR(&Status);
    Ret += NRF_ClearMAX_RT(&Status);
    Ret += NRF_ClearTX_DS(&Status);
    Ret += NRF_FlushRX(&Status);
    Ret += NRF_FlushTX(&Status);
    
	return Py_BuildValue("i", Ret);
}

static PyObject* NrfPy_SetPower(PyObject *self, PyObject *args)
{
	int  Power;
	int  Ret;
	char Status;
	
    if (!PyArg_ParseTuple(args, "i", &Power))
        return NULL;
        
	Ret = NRF_SetPowerMode(Power, &Status);

	return Py_BuildValue("i", Ret);
}

static PyObject* NrfPy_SetPTX(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }    
    
    int  Ret;
    char Status;
    Ret = NRF_SetModePTX(&Status);

	return Py_BuildValue("i", Ret);
}

static PyObject* NrfPy_SetPRX(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }    
    
    int  Ret;
    char Status;
    
    Ret = NRF_SetModePRX(&Status);    

	return Py_BuildValue("i", Ret);
}

static PyObject* NrfPy_ReadDHT22(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }
    
    int   Ret;
    int   TemperatureTemp;
	int   HumidityTemp;
    char  Status;
    char  RecvBuffer[8];
    float Humidity;
    float Temperature;
    float Battery;
    int   LinkQuality;
        
    memset(RecvBuffer, 0x00, sizeof(RecvBuffer));
	NRF_SetDataPipeLength(P0, 8, &Status);
	
	Humidity    = 0.0;
    Temperature = 0.0;
    Battery     = 0.0;
    LinkQuality = 0;
	Ret 		= 0;
	
	NRF_GetStatus(&Status);	
	if ((Status & RX_DR) == RX_DR)
	{
		Ret = NRF_ReadRXPayload(RecvBuffer, 8, &Status);		
		TemperatureTemp = (RecvBuffer[4] << 8) | RecvBuffer[5];
		HumidityTemp    = (RecvBuffer[2] << 8) | RecvBuffer[3];
		
		Ret += NRF_ClearRX_DR(&Status);
		Ret += NRF_ClearMAX_RT(&Status);
		Ret += NRF_ClearTX_DS(&Status);
		Ret += NRF_FlushRX(&Status);
		Humidity    = (float)(HumidityTemp/10.0);
		Temperature = (float)(TemperatureTemp/10.0);
		Battery     = (float)((3.3/256.0)*RecvBuffer[6]);
		LinkQuality = (int)(RecvBuffer[7] & 0x0F);
		
	}
	else
	{
		Ret = -1;
	}
	return Py_BuildValue("ifffi", Ret, Humidity, Temperature, Battery, LinkQuality);     
}

static PyObject* NrfPy_StartRX(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }    
    
	NRF_StartRX();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* NrfPy_StopRX(PyObject *self, PyObject *args)
{
	if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }    
	NRF_StopRX();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef NrfPyMethods[] = {
    {"init",       NrfPy_Init, METH_VARARGS,      "Initialize NRF24L01 Python interface"},
    {"set_power",  NrfPy_SetPower, METH_VARARGS,  "Set Power ON or OFF"},
    {"set_ptx",    NrfPy_SetPTX, METH_VARARGS,    "Set PTX mode"},
    {"set_prx",    NrfPy_SetPRX, METH_VARARGS,    "Set PRX mode"},
    {"start_rx",   NrfPy_StartRX, METH_VARARGS,   "Start RX"},
    {"stop_rx",    NrfPy_StopRX, METH_VARARGS,    "Stop RX"},
    {"read_dht22", NrfPy_ReadDHT22, METH_VARARGS, "Read the remote DHT22 sensor"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initnrfpy(void)
{
    PyObject * module;

    module = Py_InitModule("nrfpy", NrfPyMethods);
    if (module == NULL)
        return;
        
	PyObject * NrfPyPowerOn;
	NrfPyPowerOn = Py_BuildValue("i", POWER_ON);
	PyModule_AddObject(module, "POWER_ON", NrfPyPowerOn);
	
	PyObject * NrfPyPowerOff;
	NrfPyPowerOff = Py_BuildValue("i", POWER_OFF);
	PyModule_AddObject(module, "POWER_OFF", NrfPyPowerOff);
}

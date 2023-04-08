
#ifndef _H_LIB_
#define _H_LIB_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "modbus.h"
#include "modbus-private.h"
#include "gpio-rockpi4.h"

#include "device.h"

//Devices
#include "em210.h"
#include "em330.h"
#include "em340.h"
#include "sunspec.h"

#define _NUM_OF_DEVICES 4

void 		writeConfigGeneric(modbus_t* ctx, device_t* dev, uint8_t config, uint32_t value);
void 		displayAllRegistersGeneric(modbus_t* ctx, device_t* dev);
uint8_t		searchDevicesGeneric(modbus_t* ctx, char* port, uint32_t baud, uint8_t maxAddress, device_t* list);
void 		getSerial(modbus_t* ctx, EM_Device_t* device, device_t* dev);
config_t*	getConfig(device_t* dev, uint8_t config);
uint8_t 	getDeviceCount();
EM_Device_t* 	getDevice(uint8_t p);
void 		resetDeviceCount();
void 		getAllConfigsGeneric(modbus_t* ctx, device_t* dev);

char* 		lookupConversion(conversion_t* conv, uint32_t value);
uint32_t 	reverseLookupConversion(conversion_t* conv, char* name);

uint8_t 	getTimeOnBus(uint32_t baud);
uint16_t 	getWaitTimeOnBus(uint32_t baud);

#endif

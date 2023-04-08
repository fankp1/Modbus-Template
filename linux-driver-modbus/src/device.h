
#ifndef _H_DEVICE
#define _H_DEVICE

#include "conversions.h"

/*****************************************************************************
 * REGISTER VALUE PAIR                                                       *
 *****************************************************************************/
typedef struct pair 
{
	uint16_t 	offset;
	uint8_t		factor;
	uint8_t		size;
	char* 		format;
}
pair_t;

/*****************************************************************************
 * PAGE TABLE                                                                * 
 *****************************************************************************/
typedef struct pagetable 
{
	uint8_t 	size;
	uint16_t	base;
}
pagetable_t;


/*****************************************************************************
 * CONFIG ENTRY                                                              * 
 *****************************************************************************/
typedef struct config 
{
	uint8_t 	type;
	uint8_t 	size;
	uint16_t	offset;
	uint32_t	min;
	uint32_t	max;
	char* 		format;
	conversion_t*	conv;
}
config_t;


/*****************************************************************************
 * DEVICE                                                                    *
 *****************************************************************************/
typedef struct device
{
	char* 		name;
	uint16_t	signature;
	uint16_t	sig_reg;
	uint16_t 	mask;
	uint16_t 	length;
	uint16_t 	lines;
	uint16_t	size;
	pagetable_t**	pages;
	pair_t* 	registers;
	uint8_t 	config_regs;
	config_t*	config;
}
device_t;

typedef struct EM_Device
{
	uint16_t 	Signature;
	const char* 	Name;
	const char*	Version;
	const char* 	Port;
	uint32_t	Baud;
	uint8_t 	Address;
	char*		Serial;
	device_t* 	model;
	uint16_t 	modelID;
}EM_Device_t;


/*****************************************************************************
 * DEFINES                                                                   *
 *****************************************************************************/
#define __NULL 		0x0000
#define __TIME 		0x0002
#define __BASE 		0x0004

#define __2BYTE		0x0001
#define __2BYTEU	0x0003
#define __4BYTE		0x0002
#define __4BYTEU	0x0004
#define __14BYTE	0x0007

#define __F10_0		0x00
#define __F10_1		0x01
#define __F10_2		0x02
#define __F10_3		0x03
#define __F10_4		0x04

#define __PASSWORD	0x01
#define __MEAS_SYS	0x02
#define __BAUDRATE	0x03
#define __ADDRESS	0x04
#define __SERIAL	0x05
#define __CT_RATIO	0x06
#define __VT_RATIO	0x07
#define __MEAS_MODE	0x08
#define __RESET		0x09
#define __SENSOR	0x0A
#define __ROGOWSKI	0x0B
#define __APPTYPE	0x0C

#endif


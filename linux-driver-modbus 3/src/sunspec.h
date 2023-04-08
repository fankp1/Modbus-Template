/******************************************************************************/
/* Sunspec Library                                                              */
/******************************************************************************/
/* Author: 	Alexander Portenier                                           */
/******************************************************************************/
/* Date: 	25. August 2020                                              */
/******************************************************************************/
/* Copyright AppModule AG                                                     */
/******************************************************************************/

#ifndef SUNSPEC_LIBRARY
#define SUNSPEC_LIBRARY

#include "device.h"

/******************************************************************************/
/* Register Page 1                                                            */
/******************************************************************************/
#define SUNSPEC_P1_SIZE		0x2A
#define SUNSPEC_P1_BASE		0x9C85

#define SUNSPEC_L1_V		0x0A
#define SUNSPEC_L2_V		0x0B
#define SUNSPEC_L3_V		0x0C
#define SUNSPEC_L1_A		0x03
#define SUNSPEC_L2_A		0x04
#define SUNSPEC_L3_A		0x05
//#define SUNSPEC_L1_kW		0x12
//#define SUNSPEC_L2_kW		0x14
//#define SUNSPEC_L3_kW		0x16
//#define SUNSPEC_L1_kVA	0x18
//#define SUNSPEC_L2_kVA	0x1A
//#define SUNSPEC_L3_kVA	0x1C
//#define SUNSPEC_L1_kvar	0x1E
//#define SUNSPEC_L2_kvar	0x20
//#define SUNSPEC_L3_kvar	0x22
#define SUNSPEC_SYS_HZ		0x10
#define SUNSPEC_SYS_kW		0x0E
#define SUNSPEC_SYS_kVA		0x12
#define SUNSPEC_SYS_kvar	0x14
#define SUNSPEC_SYS_I_SF	0x06
#define SUNSPEC_SYS_U_SF	0x0D
#define SUNSPEC_SYS_P_SF	0x0F
#define SUNSPEC_SYS_HZ_SF	0x11
#define SUNSPEC_SYS_VA_SF	0x13
#define SUNSPEC_SYS_VAR_SF	0x15
#define SUNSPEC_SYS_kWh		0x18
#define SUNSPEC_SYS_kWh_SF	0x20

static pagetable_t __sunspec_p1 = {
	.size 	= SUNSPEC_P1_SIZE,
	.base 	= SUNSPEC_P1_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Register Page 2                                                            */
/******************************************************************************/
/*#define SUNSPEC_P2_SIZE	0x20
#define SUNSPEC_P2_BASE	0x32

#define SUNSPEC_HZ	0x33
#define SUNSPEC_kWh_P	0x34
#define SUNSPEC_L1_kWh_P	0x40	//doesn't exist FIXME
#define SUNSPEC_L2_kWh_P	0x42	//doesn't exist FIXME
#define SUNSPEC_L3_kWh_P	0x44	//doesn't exist FIXME
#define SUNSPEC_kWh_N	0x4E
#define SUNSPEC_kvarh_P	0x36
#define SUNSPEC_kvarh_N	0x50	//doesn't exist FIXME

static pagetable_t __em210_p2 = {
	.size	= SUNSPEC_P2_SIZE,
	.base	= SUNSPEC_P2_BASE,
};*/
/******************************************************************************/


/******************************************************************************/
/* Register Page 3                                                            */
/******************************************************************************/
/*#define SUNSPEC_P3_SIZE	0x06
#define SUNSPEC_P3_BASE	0x60

#define SUNSPEC_L1_kWh_N	0x60	//doesn't exist FIXME
#define SUNSPEC_L2_kWh_N	0x62	//doesn't exist FIXME
#define SUNSPEC_L3_kWh_N	0x64	//doesn't exist FIXME

static pagetable_t __em210_p3 = {
	.size	= SUNSPEC_P3_SIZE,
	.base	= SUNSPEC_P3_BASE,
};*/
/******************************************************************************/

/******************************************************************************/
/* Internal Buffer Pointers                                                   */
/******************************************************************************/

#define __SUNSPEC_L1_V		( SUNSPEC_L1_V 	+ __BASE )
#define __SUNSPEC_L2_V		( SUNSPEC_L2_V 	+ __BASE )
#define __SUNSPEC_L3_V		( SUNSPEC_L3_V 	+ __BASE )
#define __SUNSPEC_L1_A		( SUNSPEC_L1_A 	+ __BASE )
#define __SUNSPEC_L2_A		( SUNSPEC_L2_A 	+ __BASE )
#define __SUNSPEC_L3_A		( SUNSPEC_L3_A 	+ __BASE )
#define __SUNSPEC_SYS_kW		( SUNSPEC_SYS_kW 	+ __BASE )
#define __SUNSPEC_SYS_kVA		( SUNSPEC_SYS_kVA	+ __BASE )
#define __SUNSPEC_SYS_kvar		( SUNSPEC_SYS_kvar	+ __BASE )
#define __SUNSPEC_SYS_I_SF		( SUNSPEC_SYS_I_SF	+ __BASE )
#define __SUNSPEC_SYS_U_SF		( SUNSPEC_SYS_U_SF	+ __BASE )
#define __SUNSPEC_SYS_P_SF		( SUNSPEC_SYS_P_SF	+ __BASE )
#define __SUNSPEC_SYS_HZ		( SUNSPEC_SYS_HZ 	+ __BASE )
#define __SUNSPEC_SYS_kWh		( SUNSPEC_SYS_kWh 	+ __BASE )
#define __SUNSPEC_SYS_HZ_SF		( SUNSPEC_SYS_HZ_SF	+ __BASE )
#define __SUNSPEC_SYS_kWh_SF		( SUNSPEC_SYS_kWh_SF	+ __BASE )
#define __SUNSPEC_SYS_VA_SF		( SUNSPEC_SYS_VA_SF	+ __BASE )
#define __SUNSPEC_SYS_VAR_SF		( SUNSPEC_SYS_VAR_SF	+ __BASE )

/******************************************************************************/


/******************************************************************************/
/* Device Description Structure                                               */
/******************************************************************************/
static device_t  __SUNSPEC = {
	.name 		= "SUNSPEC",
	.signature 	= 0x5375,
	.sig_reg	= 0x9C40,
	.mask 		= 0xFFFF,
	.lines		= 44,
	.length 	= 1,
	.size 		= ( SUNSPEC_P1_SIZE),// + SUNSPEC_P2_SIZE + SUNSPEC_P3_SIZE ),
	.pages 		= (pagetable_t*[]){&__sunspec_p1},//, &__em210_p2, &__em210_p3},
	.registers 	= (pair_t[]){
/*|---------------------|--------|------|-----------------------------------|*/
/*| Register            | Factor | Size | Format String                     |*/
/*|---------------------|--------|------|-----------------------------------|*/
{__NULL			,__F10_0,__4BYTE,"{\n\t\"meterId\": \"GUID\",\n"},
{__TIME			,__F10_0,__4BYTE,"\t\"time\": %ld,\n"},
{__NULL			,__F10_0,__4BYTE,"\t\"sys\": {\n"},
{__SUNSPEC_SYS_HZ	,__F10_0,__2BYTEU,"\t\t\"Hz\": %7.3f,\n"},
{__NULL			,__F10_1,__4BYTE,"\t\t\"kWh+\": null,\n"},
{__NULL			,__F10_1,__4BYTE,"\t\t\"kWh-\": null,\n"},
{__NULL			,__F10_1,__4BYTE,"\t\t\"kvarh+\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kvarh-\": null,\n"},
{__SUNSPEC_SYS_kW	,__F10_0,__2BYTE,"\t\t\"kW\": %7.3f,\n"},
{__SUNSPEC_SYS_kVA	,__F10_0,__2BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__SUNSPEC_SYS_kvar	,__F10_0,__2BYTE,"\t\t\"kvar\": %7.3f,\n"},
{__SUNSPEC_SYS_kWh	,__F10_3,__4BYTEU,"\t\t\"kWh-\": %7.3f,\n"},
{__SUNSPEC_SYS_P_SF	,__F10_0,__2BYTE,"\t\t\"SF_kW\": %7.3f,\n"},
{__SUNSPEC_SYS_VA_SF	,__F10_0,__2BYTE,"\t\t\"SF_kVA\": %7.3f,\n"},
{__SUNSPEC_SYS_VAR_SF	,__F10_0,__2BYTE,"\t\t\"SF_kVAR\": %7.3f,\n"},
{__SUNSPEC_SYS_I_SF	,__F10_0,__2BYTE,"\t\t\"SF_I\": %7.3f,\n"},
{__SUNSPEC_SYS_U_SF	,__F10_0,__2BYTE,"\t\t\"SF_U\": %7.3f,\n"},
{__SUNSPEC_SYS_HZ_SF	,__F10_0,__2BYTE,"\t\t\"SF_Hz\": %7.3f,\n"},
{__SUNSPEC_SYS_kWh_SF	,__F10_0,__2BYTEU,"\t\t\"SF_kWH\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l1\": {\n\t\t\"phase\": \"R\",\n"},
{__SUNSPEC_L1_V		,__F10_0,__2BYTEU,"\t\t\"V\": %7.3f,\n"},
{__SUNSPEC_L1_A		,__F10_0,__2BYTEU,"\t\t\"A\": %7.3f,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kWh+\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kWh-\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kW\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kVA\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kvar\": null\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l2\": {\n\t\t\"phase\": \"S\",\n"},
{__SUNSPEC_L2_V		,__F10_0,__2BYTEU,"\t\t\"V\": %7.3f,\n"},
{__SUNSPEC_L2_A		,__F10_0,__2BYTEU,"\t\t\"A\": %7.3f,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kWh+\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kWh-\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kW\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kVA\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kvar\": null\n"},
//{__SUNSPEC_L2_kWh_P	,__F10_4,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
//{__SUNSPEC_L2_kWh_N	,__F10_4,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
//{__SUNSPEC_L2_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
//{__SUNSPEC_L2_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
//{__SUNSPEC_L2_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l3\": {\n\t\t\"phase\": \"T\",\n"},
{__SUNSPEC_L3_V		,__F10_0,__2BYTEU,"\t\t\"V\": %7.3f,\n"},
{__SUNSPEC_L3_A		,__F10_0,__2BYTEU,"\t\t\"A\": %7.3f,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kWh+\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kWh-\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kW\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kVA\": null,\n"},
{__NULL			,__F10_4,__4BYTE,"\t\t\"kvar\": null\n"},
//{__SUNSPEC_L3_kWh_P	,__F10_4,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
//{__SUNSPEC_L3_kWh_N	,__F10_4,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
//{__SUNSPEC_L3_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
//{__SUNSPEC_L3_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
//{__SUNSPEC_L3_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_4,__4BYTE,"\t}\n}\n"}
},
	.config_regs	= 11,
	.config 	= (config_t[]){
/*|---------------------|-------|--------|------|-------|--------------------|*/
/*| Register            | Size  | Offset | Min  | Max   | Format String      |*/
/*|---------------------|-------|--------|------|-------|--------------------|*/
{__PASSWORD		,__2BYTE,0x1000 , 0    , 999   ,"\"Password\": %d",NULL},
{__MEAS_SYS		,__2BYTE,0x1002 , 0    , 4     ,"\"Measurement System\": %s",&MeasSys},
{__BAUDRATE		,__2BYTE,0x2001 , 0    , 4     ,"\"Baudrate\": %s",&Baudrate1},
{__ADDRESS		,__2BYTE,0x2000 , 1    , 247   ,"\"Address\": %d",NULL},
{__CT_RATIO		,__4BYTE,0x1003 , 10   , 9990  ,"\"CT Ratio\": %d",NULL},
{__VT_RATIO		,__4BYTE,0x1005 , 10   , 9990  ,"\"VT Ratio\": %d",NULL},
{__SENSOR		,__2BYTE,0x1007 , 0    , 1     ,"\"Sensor Selection\": %s",&SensorSel},
{__ROGOWSKI		,__2BYTE,0x1008 , 0    , 2     ,"\"Range Rogowski Sensor\": %s",&RogowskiSel},
{__RESET		,__2BYTE,0x4000 , 0    , 1     ,"\"Reset\": %s",&ResetCmd},
{__APPTYPE		,__2BYTE,0x1300 , 0    , 5     ,"\"Application Type\": %s",&ApplicationType},
{__SERIAL		,__14BYTE,0x9C44, 0    , 0     ,"\"Serial\": %s",NULL}
}
};
/******************************************************************************/

#endif

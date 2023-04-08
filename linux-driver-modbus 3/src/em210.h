/******************************************************************************/
/* EM210 Library                                                              */
/******************************************************************************/
/* Author: 	Alexander Portenier                                           */
/******************************************************************************/
/* Date: 	27. January 2020                                              */
/******************************************************************************/
/* Copyright AppModule AG                                                     */
/******************************************************************************/

#ifndef EM210_LIBRARY
#define EM210_LIBRARY

#include "device.h"

/******************************************************************************/
/* Register Page 1                                                            */
/******************************************************************************/
#define EM210_P1_SIZE	0x32
#define EM210_P1_BASE	0x00

#define EM210_L1_V	0x00
#define EM210_L2_V	0x02
#define EM210_L3_V	0x04
#define EM210_L1_A	0x0C
#define EM210_L2_A	0x0E
#define EM210_L3_A	0x10
#define EM210_L1_kW	0x12
#define EM210_L2_kW	0x14
#define EM210_L3_kW	0x16
#define EM210_L1_kVA	0x18
#define EM210_L2_kVA	0x1A
#define EM210_L3_kVA	0x1C
#define EM210_L1_kvar	0x1E
#define EM210_L2_kvar	0x20
#define EM210_L3_kvar	0x22
#define EM210_SYS_kW	0x28
#define EM210_SYS_kVA	0x2A
#define EM210_SYS_kvar	0x2C

static pagetable_t __em210_p1 = {
	.size 	= EM210_P1_SIZE,
	.base 	= EM210_P1_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Register Page 2                                                            */
/******************************************************************************/
#define EM210_P2_SIZE	0x20
#define EM210_P2_BASE	0x32

#define EM210_HZ	0x33
#define EM210_kWh_P	0x34
#define EM210_L1_kWh_P	0x40	//doesn't exist FIXME
#define EM210_L2_kWh_P	0x42	//doesn't exist FIXME
#define EM210_L3_kWh_P	0x44	//doesn't exist FIXME
#define EM210_kWh_N	0x4E
#define EM210_kvarh_P	0x36
#define EM210_kvarh_N	0x50	//doesn't exist FIXME

static pagetable_t __em210_p2 = {
	.size	= EM210_P2_SIZE,
	.base	= EM210_P2_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Register Page 3                                                            */
/******************************************************************************/
#define EM210_P3_SIZE	0x06
#define EM210_P3_BASE	0x60

#define EM210_L1_kWh_N	0x60	//doesn't exist FIXME
#define EM210_L2_kWh_N	0x62	//doesn't exist FIXME
#define EM210_L3_kWh_N	0x64	//doesn't exist FIXME

static pagetable_t __em210_p3 = {
	.size	= EM210_P3_SIZE,
	.base	= EM210_P3_BASE,
};
/******************************************************************************/

/******************************************************************************/
/* Internal Buffer Pointers                                                   */
/******************************************************************************/
#define __EM210_P1_BASE 	( __BASE )
#define __EM210_P2_BASE		( __EM210_P1_BASE + EM210_P1_SIZE )
#define __EM210_P3_BASE		( __EM210_P2_BASE + EM210_P2_SIZE )

#define __EM210_L1_V		( EM210_L1_V 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L2_V		( EM210_L2_V 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L3_V		( EM210_L3_V 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L1_A		( EM210_L1_A 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L2_A		( EM210_L2_A 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L3_A		( EM210_L3_A 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L1_kW		( EM210_L1_kW 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L2_kW		( EM210_L2_kW 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L3_kW		( EM210_L3_kW 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L1_kVA		( EM210_L1_kVA 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L2_kVA		( EM210_L2_kVA 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L3_kVA		( EM210_L3_kVA 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L1_kvar		( EM210_L1_kvar	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L2_kvar		( EM210_L2_kvar	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_L3_kvar		( EM210_L3_kvar	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_SYS_kW		( EM210_SYS_kW 	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_SYS_kVA		( EM210_SYS_kVA	+ __EM210_P1_BASE - EM210_P1_BASE )
#define __EM210_SYS_kvar	( EM210_SYS_kvar+ __EM210_P1_BASE - EM210_P1_BASE )

#define __EM210_HZ		( EM210_HZ 	+ __EM210_P2_BASE - EM210_P2_BASE )
#define __EM210_kWh_P		( EM210_kWh_P 	+ __EM210_P2_BASE - EM210_P2_BASE )
#define __EM210_L1_kWh_P	( EM210_L1_kWh_P+ __EM210_P2_BASE - EM210_P2_BASE )
#define __EM210_L2_kWh_P	( EM210_L2_kWh_P+ __EM210_P2_BASE - EM210_P2_BASE )
#define __EM210_L3_kWh_P	( EM210_L3_kWh_P+ __EM210_P2_BASE - EM210_P2_BASE )
#define __EM210_kWh_N		( EM210_kWh_N	+ __EM210_P2_BASE - EM210_P2_BASE )
#define __EM210_kvarh_P		( EM210_kvarh_P + __EM210_P2_BASE - EM210_P2_BASE )
#define __EM210_kvarh_N		( EM210_kvarh_N + __EM210_P2_BASE - EM210_P2_BASE )

#define __EM210_L1_kWh_N	( EM210_L1_kWh_N+ __EM210_P3_BASE - EM210_P3_BASE )
#define __EM210_L2_kWh_N	( EM210_L2_kWh_N+ __EM210_P3_BASE - EM210_P3_BASE )
#define __EM210_L3_kWh_N	( EM210_L3_kWh_N+ __EM210_P3_BASE - EM210_P3_BASE )
/******************************************************************************/


/******************************************************************************/
/* Device Description Structure                                               */
/******************************************************************************/
static device_t  __EM210 = {
	.name 		= "EM210",
	.signature 	= 208,
	.sig_reg	= 11,
	.mask 		= 0xFFFC,
	.lines		= 36,
	.length 	= 3,
	.size 		= ( EM210_P1_SIZE + EM210_P2_SIZE + EM210_P3_SIZE ),
	.pages 		= (pagetable_t*[]){&__em210_p1, &__em210_p2, &__em210_p3},
	.registers 	= (pair_t[]){
/*|---------------------|--------|------|-----------------------------------|*/
/*| Register            | Factor | Size | Format String                     |*/
/*|---------------------|--------|------|-----------------------------------|*/
{__NULL			,__F10_0,__4BYTE,"{\n\t\"meterId\": \"GUID\",\n"},
{__TIME			,__F10_0,__4BYTE,"\t\"time\": %ld,\n"},
{__NULL			,__F10_0,__4BYTE,"\t\"sys\": {\n"},
{__EM210_HZ		,__F10_0,__2BYTE,"\t\t\"Hz\": %7.3f,\n"},
{__EM210_kWh_P		,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM210_kWh_N		,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM210_kvarh_P	,__F10_1,__4BYTE,"\t\t\"kvarh+\": %7.3f,\n"},
{__EM210_kvarh_N	,__F10_4,__4BYTE,"\t\t\"kvarh-\": %7.3f,\n"},
{__EM210_SYS_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM210_SYS_kVA	,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM210_SYS_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l1\": {\n\t\t\"phase\": \"R\",\n"},
{__EM210_L1_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__EM210_L1_A		,__F10_3,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__EM210_L1_kWh_P	,__F10_4,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM210_L1_kWh_N	,__F10_4,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM210_L1_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM210_L1_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM210_L1_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l2\": {\n\t\t\"phase\": \"S\",\n"},
{__EM210_L2_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__EM210_L2_A		,__F10_3,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__EM210_L2_kWh_P	,__F10_4,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM210_L2_kWh_N	,__F10_4,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM210_L2_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM210_L2_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM210_L2_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l3\": {\n\t\t\"phase\": \"T\",\n"},
{__EM210_L3_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__EM210_L3_A		,__F10_3,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__EM210_L3_kWh_P	,__F10_4,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM210_L3_kWh_N	,__F10_4,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM210_L3_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM210_L3_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM210_L3_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
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
{__SERIAL		,__14BYTE,0x5000, 0    , 0     ,"\"Serial\": %s",NULL}
}
};
/******************************************************************************/

#endif

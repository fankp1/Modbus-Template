/******************************************************************************/
/* EM340 Library                                                              */
/******************************************************************************/
/* Author: 	Alexander Portenier                                           */
/******************************************************************************/
/* Date: 	3. January 2020                                               */
/******************************************************************************/
/* Copyright AppModule AG                                                     */
/******************************************************************************/

#ifndef EM340_LIBRARY
#define EM340_LIBRARY

#include "device.h"

/******************************************************************************/
/* Register Page 1                                                            */
/******************************************************************************/
#define EM340_P1_SIZE	0x32
#define EM340_P1_BASE	0x00

#define EM340_L1_V	0x00
#define EM340_L2_V	0x02
#define EM340_L3_V	0x04
#define EM340_L1_A	0x0C
#define EM340_L2_A	0x0E
#define EM340_L3_A	0x10
#define EM340_L1_kW	0x12
#define EM340_L2_kW	0x14
#define EM340_L3_kW	0x16
#define EM340_L1_kVA	0x18
#define EM340_L2_kVA	0x1A
#define EM340_L3_kVA	0x1C
#define EM340_L1_kvar	0x1E
#define EM340_L2_kvar	0x20
#define EM340_L3_kvar	0x22
#define EM340_SYS_kW	0x28
#define EM340_SYS_kVA	0x2A
#define EM340_SYS_kvar	0x2C

static pagetable_t __em340_p1 = {
	.size 	= EM340_P1_SIZE,
	.base 	= EM340_P1_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Register Page 2                                                            */
/******************************************************************************/
#define EM340_P2_SIZE	0x20
#define EM340_P2_BASE	0x32

#define EM340_HZ	0x33
#define EM340_kWh_P	0x34
#define EM340_L1_kWh_P	0x40
#define EM340_L2_kWh_P	0x42
#define EM340_L3_kWh_P	0x44
#define EM340_kWh_N	0x4E
#define EM340_kvarh_P	0x36
#define EM340_kvarh_N	0x50

static pagetable_t __em340_p2 = {
	.size	= EM340_P2_SIZE,
	.base	= EM340_P2_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Register Page 3                                                            */
/******************************************************************************/
#define EM340_P3_SIZE	0x06
#define EM340_P3_BASE	0x60

#define EM340_L1_kWh_N	0x60	
#define EM340_L2_kWh_N	0x62	
#define EM340_L3_kWh_N	0x64	

static pagetable_t __em340_p3 = {
	.size	= EM340_P3_SIZE,
	.base	= EM340_P3_BASE,
};
/******************************************************************************/

/******************************************************************************/
/* Internal Buffer Pointers                                                   */
/******************************************************************************/
#define __EM340_P1_BASE 	( __BASE)
#define __EM340_P2_BASE		( __EM340_P1_BASE + EM340_P1_SIZE )
#define __EM340_P3_BASE		( __EM340_P2_BASE + EM340_P2_SIZE )

#define __EM340_L1_V		( EM340_L1_V 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L2_V		( EM340_L2_V 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L3_V		( EM340_L3_V 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L1_A		( EM340_L1_A 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L2_A		( EM340_L2_A 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L3_A		( EM340_L3_A 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L1_kW		( EM340_L1_kW 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L2_kW		( EM340_L2_kW 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L3_kW		( EM340_L3_kW 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L1_kVA		( EM340_L1_kVA 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L2_kVA		( EM340_L2_kVA 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L3_kVA		( EM340_L3_kVA 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L1_kvar		( EM340_L1_kvar	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L2_kvar		( EM340_L2_kvar	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_L3_kvar		( EM340_L3_kvar	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_SYS_kW		( EM340_SYS_kW 	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_SYS_kVA		( EM340_SYS_kVA	+ __EM340_P1_BASE - EM340_P1_BASE )
#define __EM340_SYS_kvar	( EM340_SYS_kvar+ __EM340_P1_BASE - EM340_P1_BASE )

#define __EM340_HZ		( EM340_HZ 	+ __EM340_P2_BASE - EM340_P2_BASE )
#define __EM340_kWh_P		( EM340_kWh_P 	+ __EM340_P2_BASE - EM340_P2_BASE )
#define __EM340_L1_kWh_P	( EM340_L1_kWh_P+ __EM340_P2_BASE - EM340_P2_BASE )
#define __EM340_L2_kWh_P	( EM340_L2_kWh_P+ __EM340_P2_BASE - EM340_P2_BASE )
#define __EM340_L3_kWh_P	( EM340_L3_kWh_P+ __EM340_P2_BASE - EM340_P2_BASE )
#define __EM340_kWh_N		( EM340_kWh_N	+ __EM340_P2_BASE - EM340_P2_BASE )
#define __EM340_kvarh_P		( EM340_kvarh_P + __EM340_P2_BASE - EM340_P2_BASE )
#define __EM340_kvarh_N		( EM340_kvarh_N + __EM340_P2_BASE - EM340_P2_BASE )

#define __EM340_L1_kWh_N	( EM340_L1_kWh_N+ __EM340_P3_BASE - EM340_P3_BASE )
#define __EM340_L2_kWh_N	( EM340_L2_kWh_N+ __EM340_P3_BASE - EM340_P3_BASE )
#define __EM340_L3_kWh_N	( EM340_L3_kWh_N+ __EM340_P3_BASE - EM340_P3_BASE )
/******************************************************************************/


/******************************************************************************/
/* Device Description Structure                                               */
/******************************************************************************/
static device_t  __EM340 = {
	.name 		= "EM340",
	.signature 	= 340,
	.sig_reg	= 11,
	.mask 		= 0xFFFC,
	.lines		= 36,
	.length 	= 3,
	.size 		= ( EM340_P1_SIZE + EM340_P2_SIZE + EM340_P3_SIZE ),
	.pages 		= (pagetable_t*[]){&__em340_p1, &__em340_p2, &__em340_p3},
	.registers 	= (pair_t[]){
/*|---------------------|--------|------|-----------------------------------|*/
/*| Register            | Factor | Size | Format String                     |*/
/*|---------------------|--------|------|-----------------------------------|*/
{__NULL			,__F10_0,__4BYTE,"{\n\t\"meterId\": \"GUID\",\n"},
{__TIME			,__F10_0,__4BYTE,"\t\"time\": %ld,\n"},
{__NULL			,__F10_0,__4BYTE,"\t\"sys\": {\n"},
{__EM340_HZ		,__F10_1,__2BYTE,"\t\t\"Hz\": %7.3f,\n"},
{__EM340_kWh_P		,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM340_kWh_N		,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM340_kvarh_P	,__F10_4,__4BYTE,"\t\t\"kvarh+\": %7.3f,\n"},
{__EM340_kvarh_N	,__F10_4,__4BYTE,"\t\t\"kvarh-\": %7.3f,\n"},
{__EM340_SYS_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM340_SYS_kVA	,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM340_SYS_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l1\": {\n\t\t\"phase\": \"R\",\n"},
{__EM340_L1_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__EM340_L1_A		,__F10_3,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__EM340_L1_kWh_P	,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM340_L1_kWh_N	,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM340_L1_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM340_L1_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM340_L1_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l2\": {\n\t\t\"phase\": \"S\",\n"},
{__EM340_L2_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__EM340_L2_A		,__F10_3,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__EM340_L2_kWh_P	,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM340_L2_kWh_N	,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM340_L2_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM340_L2_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM340_L2_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l3\": {\n\t\t\"phase\": \"T\",\n"},
{__EM340_L3_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__EM340_L3_A		,__F10_3,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__EM340_L3_kWh_P	,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM340_L3_kWh_N	,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM340_L3_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM340_L3_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM340_L3_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_1,__4BYTE,"\t}\n}\n"}
},
	.config_regs	= 7,
	.config 	= (config_t[]){
/*|---------------------|-------|--------|------|-------|--------------------|*/
/*| Register            | Size  | Offset | Min  | Max   | Format String      |*/
/*|---------------------|-------|--------|------|-------|--------------------|*/
{__PASSWORD		,__2BYTE, 0x1000 , 0	, 9999 ,"\"Password\": %d",NULL},
{__BAUDRATE		,__2BYTE, 0x2001 , 1	, 5    ,"\"Baudrate\": %s",&Baudrate2},
{__MEAS_SYS		,__2BYTE, 0x1002 , 0    , 3    ,"\"Measurement System\": %s",&MeasSys},
{__MEAS_MODE		,__2BYTE, 0x1103 , 0    , 1    ,"\"Measurement Mode\": %s",&MeasMode},
{__ADDRESS		,__2BYTE, 0x2000 , 1    , 247  ,"\"Address\": %d",NULL},
{__RESET		,__2BYTE, 0x4001 , 0    , 1    ,"\"Reset\": %s",&ResetCmd},
{__SERIAL		,__14BYTE, 0x5000, 0	, 0    ,"\"Serial\": %s",NULL}
//{__CT_RATIO		,__4BYTE, 0x1003 , 10   , 9990 ,"\"CT Ratio\": %3.1f"},
//{__VT_RATIO		,__4BYTE, 0x1005 , 10   , 9990 ,"\"VT Ratio\": %3.1f"},
}
};
/******************************************************************************/

#endif

/******************************************************************************/
/* EM330 Library                                                              */
/******************************************************************************/
/* Author:  	Alexander Portenier                                           */
/******************************************************************************/
/* Date:	24. January 2020                                               */
/******************************************************************************/
/* Copyright AppModule AG                                                     */
/******************************************************************************/

#ifndef EM330_LIBRARY
#define EM330_LIBRARY

#include "device.h"

/******************************************************************************/
/* Register Page 1                                                            */
/******************************************************************************/
#define EM330_P1_SIZE	0x32
#define EM330_P1_BASE	0x00

#define EM330_L1_V	0x00
#define EM330_L2_V	0x02
#define EM330_L3_V	0x04
#define EM330_L1_A	0x0C
#define EM330_L2_A	0x0E
#define EM330_L3_A	0x10
#define EM330_L1_kW	0x12
#define EM330_L2_kW	0x14
#define EM330_L3_kW	0x16
#define EM330_L1_kVA	0x18
#define EM330_L2_kVA	0x1A
#define EM330_L3_kVA	0x1C
#define EM330_L1_kvar	0x1E
#define EM330_L2_kvar	0x20
#define EM330_L3_kvar	0x22
#define EM330_SYS_kW	0x28
#define EM330_SYS_kVA	0x2A
#define EM330_SYS_kvar	0x2C

static pagetable_t __em330_p1 = {
	.size 	= EM330_P1_SIZE,
	.base 	= EM330_P1_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Register Page 2                                                            */
/******************************************************************************/
#define EM330_P2_SIZE	0x20
#define EM330_P2_BASE	0x32

#define EM330_HZ	0x33
#define EM330_kWh_P	0x34
#define EM330_L1_kWh_P	0x40
#define EM330_L2_kWh_P	0x42
#define EM330_L3_kWh_P	0x44
#define EM330_kWh_N	0x4E
#define EM330_kvarh_P	0x36
#define EM330_kvarh_N	0x50

static pagetable_t __em330_p2 = {
	.size	= EM330_P2_SIZE,
	.base	= EM330_P2_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Register Page 3                                                            */
/******************************************************************************/
#define EM330_P3_SIZE	0x06
#define EM330_P3_BASE	0x60

#define EM330_L1_kWh_N	0x60	
#define EM330_L2_kWh_N	0x62	
#define EM330_L3_kWh_N	0x64	

static pagetable_t __em330_p3 = {
	.size	= EM330_P3_SIZE,
	.base	= EM330_P3_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Internal Buffer Pointers                                                   */
/******************************************************************************/
#define __EM330_P1_BASE 	( __BASE)
#define __EM330_P2_BASE		( __EM330_P1_BASE + EM330_P1_SIZE )
#define __EM330_P3_BASE		( __EM330_P2_BASE + EM330_P2_SIZE )

#define __EM330_L1_V		( EM330_L1_V 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L2_V		( EM330_L2_V 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L3_V		( EM330_L3_V 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L1_A		( EM330_L1_A 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L2_A		( EM330_L2_A 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L3_A		( EM330_L3_A 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L1_kW		( EM330_L1_kW 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L2_kW		( EM330_L2_kW 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L3_kW		( EM330_L3_kW 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L1_kVA		( EM330_L1_kVA 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L2_kVA		( EM330_L2_kVA 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L3_kVA		( EM330_L3_kVA 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L1_kvar		( EM330_L1_kvar	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L2_kvar		( EM330_L2_kvar	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_L3_kvar		( EM330_L3_kvar	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_SYS_kW		( EM330_SYS_kW 	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_SYS_kVA		( EM330_SYS_kVA	+ __EM330_P1_BASE - EM330_P1_BASE )
#define __EM330_SYS_kvar	( EM330_SYS_kvar+ __EM330_P1_BASE - EM330_P1_BASE )

#define __EM330_HZ		( EM330_HZ 	+ __EM330_P2_BASE - EM330_P2_BASE )
#define __EM330_kWh_P		( EM330_kWh_P 	+ __EM330_P2_BASE - EM330_P2_BASE )
#define __EM330_L1_kWh_P	( EM330_L1_kWh_P+ __EM330_P2_BASE - EM330_P2_BASE )
#define __EM330_L2_kWh_P	( EM330_L2_kWh_P+ __EM330_P2_BASE - EM330_P2_BASE )
#define __EM330_L3_kWh_P	( EM330_L3_kWh_P+ __EM330_P2_BASE - EM330_P2_BASE )
#define __EM330_kWh_N		( EM330_kWh_N	+ __EM330_P2_BASE - EM330_P2_BASE )
#define __EM330_kvarh_P		( EM330_kvarh_P + __EM330_P2_BASE - EM330_P2_BASE )
#define __EM330_kvarh_N		( EM330_kvarh_N + __EM330_P2_BASE - EM330_P2_BASE )

#define __EM330_L1_kWh_N	( EM330_L1_kWh_N+ __EM330_P3_BASE - EM330_P3_BASE )
#define __EM330_L2_kWh_N	( EM330_L2_kWh_N+ __EM330_P3_BASE - EM330_P3_BASE )
#define __EM330_L3_kWh_N	( EM330_L3_kWh_N+ __EM330_P3_BASE - EM330_P3_BASE )
/******************************************************************************/


/******************************************************************************/
/* Device Description Structure                                               */
/******************************************************************************/
static device_t  __EM330 = {
	.name 		= "EM330",
	.signature 	= 332,
	.sig_reg	= 11,
	.mask 		= 0xFFFC,
	.lines		= 36,
	.length 	= 3,
	.size 		= ( EM330_P1_SIZE + EM330_P2_SIZE + EM330_P3_SIZE ),
	.pages 		= (pagetable_t*[]){&__em330_p1, &__em330_p2, &__em330_p3},
	.registers 	= (pair_t[]){
/*|---------------------|--------|------|-----------------------------------|*/
/*| Register            | Factor | Size | Format String                     |*/
/*|---------------------|--------|------|-----------------------------------|*/
{__NULL			,__F10_0,__4BYTE,"{\n\t\"meterId\": \"GUID\",\n"},
{__TIME			,__F10_0,__4BYTE,"\t\"time\": %ld,\n"},
{__NULL			,__F10_0,__4BYTE,"\t\"sys\": {\n"},
{__EM330_HZ		,__F10_1,__2BYTE,"\t\t\"Hz\": %7.3f,\n"},
{__EM330_kWh_P		,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM330_kWh_N		,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM330_kvarh_P	,__F10_4,__4BYTE,"\t\t\"kvarh+\": %7.3f,\n"},
{__EM330_kvarh_N	,__F10_4,__4BYTE,"\t\t\"kvarh-\": %7.3f,\n"},
{__EM330_SYS_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM330_SYS_kVA	,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM330_SYS_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l1\": {\n\t\t\"phase\": \"R\",\n"},
{__EM330_L1_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__EM330_L1_A		,__F10_3,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__EM330_L1_kWh_P	,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM330_L1_kWh_N	,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM330_L1_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM330_L1_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM330_L1_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l2\": {\n\t\t\"phase\": \"S\",\n"},
{__EM330_L2_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__EM330_L2_A		,__F10_3,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__EM330_L2_kWh_P	,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM330_L2_kWh_N	,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM330_L2_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM330_L2_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM330_L2_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l3\": {\n\t\t\"phase\": \"T\",\n"},
{__EM330_L3_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__EM330_L3_A		,__F10_3,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__EM330_L3_kWh_P	,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__EM330_L3_kWh_N	,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__EM330_L3_kW		,__F10_4,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__EM330_L3_kVA		,__F10_4,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__EM330_L3_kvar	,__F10_4,__4BYTE,"\t\t\"kvar\": %7.3f\n"},
{__NULL			,__F10_1,__4BYTE,"\t}\n}\n"}
},
	.config_regs	= 9,
	.config 	= (config_t[]){
/*|---------------------|-------|--------|------|-------|--------------------|*/
/*| Register            | Size  | Offset | Min  | Max   | Format String      |*/
/*|---------------------|-------|--------|------|-------|--------------------|*/
{__PASSWORD		,__2BYTE, 0x1000 , 0	, 9999 ,"\"Password\": %d",NULL},
{__BAUDRATE		,__2BYTE, 0x2001 , 1	, 5    ,"\"Baudrate\": %s",&Baudrate2},
{__MEAS_SYS		,__2BYTE, 0x1002 , 0	, 3    ,"\"Measurement System\": %s",&MeasSys},
{__ADDRESS		,__2BYTE, 0x2000 , 1    , 247  ,"\"Address\": %d",NULL},
{__MEAS_MODE		,__2BYTE, 0x1103 , 0    , 1    ,"\"Measurement Mode\": %s",&MeasMode},
{__CT_RATIO		,__4BYTE, 0x1003 , 10   , 9990 ,"\"CT Ratio\": %d",NULL},
{__VT_RATIO		,__4BYTE, 0x1005 , 10   , 9990 ,"\"VT Ratio\": %d",NULL},
{__RESET		,__2BYTE, 0x4001 , 0    , 1    ,"\"Reset\": %s",&ResetCmd},
{__SERIAL		,__14BYTE, 0x5000, 0	, 0    ,"\"Serial\": %s",NULL}
}
};
/******************************************************************************/

#endif

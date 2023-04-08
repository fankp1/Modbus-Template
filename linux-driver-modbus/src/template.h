/******************************************************************************/
/* TEMPLATE Library                                                              */
/******************************************************************************/
/* Author:  	Alexander Portenier                                           */
/******************************************************************************/
/* Date:	3. January 2020                                               */
/******************************************************************************/
/* Copyright AppModule AG                                                     */
/******************************************************************************/

#ifndef TEMPLATE_LIBRARY
#define TEMPLATE_LIBRARY

#include "device.h"

/******************************************************************************/
/* Register Page 1                                                            */
/******************************************************************************/
#define TEMPLATE_P1_SIZE	0x32
#define TEMPLATE_P1_BASE	0x00

#define TEMPLATE_L1_V		0x00
#define TEMPLATE_L2_V		0x02
#define TEMPLATE_L3_V		0x04
#define TEMPLATE_L1_A		0x06
#define TEMPLATE_L2_A		0x08
#define TEMPLATE_L3_A		0x0A
#define TEMPLATE_L1_kW		0x12
#define TEMPLATE_L2_kW		0x14
#define TEMPLATE_L3_kW		0x16
#define TEMPLATE_L1_kVA		0x18
#define TEMPLATE_L2_kVA		0x1A
#define TEMPLATE_L3_kVA		0x1C
#define TEMPLATE_L1_kvar	0x1E
#define TEMPLATE_L2_kvar	0x20
#define TEMPLATE_L3_kvar	0x22
#define TEMPLATE_SYS_kW		0x28
#define TEMPLATE_SYS_kVA	0x2A
#define TEMPLATE_SYS_kvar	0x2C

static pagetable_t __template_p1 = {
	.size 	= TEMPLATE_P1_SIZE,
	.base 	= TEMPLATE_P1_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Register Page 2                                                            */
/******************************************************************************/
#define TEMPLATE_P2_SIZE	0x20
#define TEMPLATE_P2_BASE	0x32

#define TEMPLATE_HZ		0x33
#define TEMPLATE_kWh_P		0x34
#define TEMPLATE_L1_kWh_P	0x40
#define TEMPLATE_L2_kWh_P	0x42
#define TEMPLATE_L3_kWh_P	0x44
#define TEMPLATE_kWh_N		0x4E
#define TEMPLATE_kvarh_P	0x36
#define TEMPLATE_kvarh_N	0x50

static pagetable_t __template_p2 = {
	.size	= TEMPLATE_P2_SIZE,
	.base	= TEMPLATE_P2_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Register Page 3                                                            */
/******************************************************************************/
#define TEMPLATE_P3_SIZE	0x06
#define TEMPLATE_P3_BASE	0x60

#define TEMPLATE_L1_kWh_N	0x60	
#define TEMPLATE_L2_kWh_N	0x62	
#define TEMPLATE_L3_kWh_N	0x64	

static pagetable_t __template_p3 = {
	.size	= TEMPLATE_P3_SIZE,
	.base	= TEMPLATE_P3_BASE,
};
/******************************************************************************/


/******************************************************************************/
/* Internal Buffer Pointers                                                   */
/******************************************************************************/
#define __TEMPLATE_P1_BASE 	( __BASE)
#define __TEMPLATE_P2_BASE	( __TEMPLATE_P1_BASE + TEMPLATE_P1_SIZE )
#define __TEMPLATE_P3_BASE	( __TEMPLATE_P2_BASE + TEMPLATE_P2_SIZE )

#define __TEMPLATE_L1_V		( TEMPLATE_L1_V 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L2_V		( TEMPLATE_L2_V 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L3_V		( TEMPLATE_L3_V 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L1_A		( TEMPLATE_L1_A 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L2_A		( TEMPLATE_L2_A 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L3_A		( TEMPLATE_L3_A 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L1_kW	( TEMPLATE_L1_kW 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L2_kW	( TEMPLATE_L2_kW 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L3_kW	( TEMPLATE_L3_kW 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L1_kVA	( TEMPLATE_L1_kVA 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L2_kVA	( TEMPLATE_L2_kVA 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L3_kVA	( TEMPLATE_L3_kVA 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L1_kvar	( TEMPLATE_L1_kvar	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L2_kvar	( TEMPLATE_L2_kvar	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_L3_kvar	( TEMPLATE_L3_kvar	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_SYS_kW	( TEMPLATE_SYS_kW 	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_SYS_kVA	( TEMPLATE_SYS_kVA	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )
#define __TEMPLATE_SYS_kvar	( TEMPLATE_SYS_kvar	+ __TEMPLATE_P1_BASE - TEMPLATE_P1_BASE )

#define __TEMPLATE_HZ		( TEMPLATE_HZ 		+ __TEMPLATE_P2_BASE - TEMPLATE_P2_BASE )
#define __TEMPLATE_kWh_P	( TEMPLATE_kWh_P 	+ __TEMPLATE_P2_BASE - TEMPLATE_P2_BASE )
#define __TEMPLATE_L1_kWh_P	( TEMPLATE_L1_kWh_P	+ __TEMPLATE_P2_BASE - TEMPLATE_P2_BASE )
#define __TEMPLATE_L2_kWh_P	( TEMPLATE_L2_kWh_P	+ __TEMPLATE_P2_BASE - TEMPLATE_P2_BASE )
#define __TEMPLATE_L3_kWh_P	( TEMPLATE_L3_kWh_P	+ __TEMPLATE_P2_BASE - TEMPLATE_P2_BASE )
#define __TEMPLATE_kWh_N	( TEMPLATE_kWh_N	+ __TEMPLATE_P2_BASE - TEMPLATE_P2_BASE )
#define __TEMPLATE_kvarh_P	( TEMPLATE_kvarh_P 	+ __TEMPLATE_P2_BASE - TEMPLATE_P2_BASE )
#define __TEMPLATE_kvarh_N	( TEMPLATE_kvarh_N 	+ __TEMPLATE_P2_BASE - TEMPLATE_P2_BASE )

#define __TEMPLATE_L1_kWh_N	( TEMPLATE_L1_kWh_N	+ __TEMPLATE_P3_BASE - TEMPLATE_P3_BASE )
#define __TEMPLATE_L2_kWh_N	( TEMPLATE_L2_kWh_N	+ __TEMPLATE_P3_BASE - TEMPLATE_P3_BASE )
#define __TEMPLATE_L3_kWh_N	( TEMPLATE_L3_kWh_N	+ __TEMPLATE_P3_BASE - TEMPLATE_P3_BASE )
/******************************************************************************/


/******************************************************************************/
/* Device Description Structure                                               */
/******************************************************************************/
static device_t  __TEMPLATE = {
	.name 		= "TEMPLATE",
	.signature 	= 332,
	.sig_reg	= 11,
	.mask 		= 0xFFFC,
	.lines		= 36,
	.length 	= 3,
	.pages 		= (pagetable_t*[]){&__template_p1, &__template_p2, &__template_p3},
	.registers 	= (pair_t[]){
/*|---------------------|--------|------|-----------------------------------|*/
/*| Register            | Factor | Size | Format String                     |*/
/*|---------------------|--------|------|-----------------------------------|*/
{__NULL			,__F10_0,__4BYTE,"{\n\t\"meterId\": \"GUID\",\n"},
{__TIME			,__F10_0,__4BYTE,"\t\"time\": %ld,\n"},
{__NULL			,__F10_0,__4BYTE,"\t\"sys\": {\n"},
{__TEMPLATE_HZ		,__F10_1,__2BYTE,"\t\t\"Hz\": %7.3f,\n"},
{__TEMPLATE_kWh_P		,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__TEMPLATE_kWh_N		,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__TEMPLATE_kvarh_P	,__F10_1,__4BYTE,"\t\t\"kvarh+\": %7.3f,\n"},
{__TEMPLATE_kvarh_N	,__F10_1,__4BYTE,"\t\t\"kvarh-\": %7.3f,\n"},
{__TEMPLATE_SYS_kW		,__F10_1,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__TEMPLATE_SYS_kVA	,__F10_1,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__TEMPLATE_SYS_kvar	,__F10_1,__4BYTE,"\t\t\"kvar\": %7.3f,\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l1\": {\n\t\t\"phase\": \"R\",\n"},
{__TEMPLATE_L1_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__TEMPLATE_L1_A		,__F10_4,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__TEMPLATE_L1_kWh_P	,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__TEMPLATE_L1_kWh_N	,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__TEMPLATE_L1_kW		,__F10_1,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__TEMPLATE_L1_kVA		,__F10_1,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__TEMPLATE_L1_kvar	,__F10_1,__4BYTE,"\t\t\"kvar\": %7.3f,\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l2\": {\n\t\t\"phase\": \"S\",\n"},
{__TEMPLATE_L2_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__TEMPLATE_L2_A		,__F10_4,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__TEMPLATE_L2_kWh_P	,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__TEMPLATE_L2_kWh_N	,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__TEMPLATE_L2_kW		,__F10_1,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__TEMPLATE_L2_kVA		,__F10_1,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__TEMPLATE_L2_kvar	,__F10_1,__4BYTE,"\t\t\"kvar\": %7.3f,\n"},
{__NULL			,__F10_0,__4BYTE,"\t},\n\t\"l3\": {\n\t\t\"phase\": \"T\",\n"},
{__TEMPLATE_L3_V		,__F10_1,__4BYTE,"\t\t\"V\": %7.3f,\n"},
{__TEMPLATE_L3_A		,__F10_4,__4BYTE,"\t\t\"A\": %7.3f,\n"},
{__TEMPLATE_L3_kWh_P	,__F10_1,__4BYTE,"\t\t\"kWh+\": %7.3f,\n"},
{__TEMPLATE_L3_kWh_N	,__F10_1,__4BYTE,"\t\t\"kWh-\": %7.3f,\n"},
{__TEMPLATE_L3_kW		,__F10_1,__4BYTE,"\t\t\"kW\": %7.3f,\n"},
{__TEMPLATE_L3_kVA		,__F10_1,__4BYTE,"\t\t\"kVA\": %7.3f,\n"},
{__TEMPLATE_L3_kvar	,__F10_1,__4BYTE,"\t\t\"kvar\": %7.3f,\n"},
{__NULL			,__F10_1,__4BYTE,"\t}\n}\n"}
}
};
/******************************************************************************/

#endif

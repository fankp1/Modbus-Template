
#include <stdio.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define UP 1
#define DOWN 0

static char* _selector = " > ";
static char* _noselector = "   ";

#define	 _RESET	0
#define _B_BLUE	1
#define _BLUE	2

char getch() 
{
	char buf = 0;
	struct termios old = { 0 };
	fflush(stdout);
	if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
	old.c_lflag    &= ~ICANON;   // local modes = Non Canonical mode
	old.c_lflag    &= ~ECHO;     // local modes = Disable echo. 
	old.c_cc[VMIN]  = 1;         // control chars (MIN value) = 1
	old.c_cc[VTIME] = 0;         // control chars (TIME value) = 0 (No time)
	if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0) perror("read()");
	old.c_lflag    |= ICANON;    // local modes = Canonical mode
	old.c_lflag    |= ECHO;      // local modes = Enable echo. 
	if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
	return buf;
}
void setTextColor(uint8_t color)
{
	switch(color)
	{
		case _RESET:
			printf("\033[0m");
			break;
		case _B_BLUE:
			printf("\033[1;34m");
			break;
		case _BLUE:
			printf("\033[0;34m");
			break;
	}
}
void hideCursor(void)
{
	printf("\e[?25l");
}

void showCursor(void)
{
	printf("\e[?25h");
}

void deleteLine(void)
{
	printf("\033[A\33[2K\r");
}

void deleteLines(uint8_t num)
{
	for(int i=0; i<num; i++)
		deleteLine();	
}

void drawMenu(char** opts, uint8_t num, uint8_t sel, uint8_t fgc, uint8_t bgc, uint8_t hc)
{
	for(int i=0; i<num; i++)
	{
		if(i==sel)
		{
			printf(" \033[%d;%dm%s%s \033[%dm",hc,fgc,_selector,opts[i],bgc);
		}
		else
		{
			printf(" \033[%dm%s%s ",fgc,_noselector,opts[i]);	
		}
		//if(i!=num-1)
			printf("\n");
	}
}

uint8_t getNext(uint8_t val, uint8_t max, uint8_t dir)
{
	if((val==max)&&(dir==DOWN))
	{
		return 0;
	}
	else if((val==0)&&(dir==UP))
	{
		return max;
	}
	else
	{
		if(dir==UP)
		{
			return --val;
		}
		else
		{
			return ++val;
		}
	}
}

#define lScreen_states 	3
void loadingScreen(uint8_t state)
{
	static uint8_t cnt = 0;
	static char* strs[lScreen_states] = {".  ",".. ","..."};
	if(state==0x00)
	{
		cnt = 0;
		deleteLine();
		return;
	}
	else
	{
		if(cnt!=0)
		{
			deleteLine();
		}
		printf(" \033[34mLoading %s",strs[cnt]);
	}
}

int64_t nmenu(uint32_t min, uint32_t max, char* format, char* title, uint8_t fgc, uint8_t bgc, uint8_t hc)
{
	uint8_t sel = 0;
	uint8_t finished = 0;
	uint32_t ret;
	uint32_t value = min;

	printf("  \033[%dm%s\033[%dm\n",fgc,title,bgc);

	while(!finished)
	{
		printf("\033[%d;%dm %s",hc,fgc,_selector);
		printf(format,value);
		printf(" \n\033[%dm",bgc);
		ret = getch();
		if(ret  == '\033')
		{
			getch();
			switch(getch())
			{
			      	case 'A':
					if(value<max)
					{
						value++;
					}
					else
					{
						value = min;
					}
				    break;
				case 'B':
				    	if(value>min)
					{
						value--;
					}
					else
					{
						value = max;
					}
				    break;
				case 'C':
					deleteLines(2);
					return value;	
				    break;
				case 'D':
					deleteLines(2);
					return -1;	
				    break;
			}
			deleteLines(1);
		}
		else if(ret == 0x0A)
		{
			deleteLines(2);
			return value;	
		}
		else if(ret>=0x30 && ret<=0x39)
		{
			if((value*10+ret-0x30)<max)
				value = value*10+ret-0x30;
			deleteLines(1);	
		}
		else if(ret == 0x7F || ret == 0x08)
		{
			if(value/10>min)
			{
				value = value/10;
			}
			else
			{
				value = min;
			}
			deleteLines(1);
		}
		else
		{
			deleteLines(1);
		}
	}
}

int8_t menu(char** opts, char* title, uint8_t num, uint8_t fgc, uint8_t bgc, uint8_t hc)
{
	uint8_t sel = 0;
	uint8_t finished = 0;
	uint32_t ret;

	printf("  \033[%dm%s\033[%dm\n",fgc,title,bgc);

	while(!finished)
	{
		drawMenu(opts,num,sel,fgc,bgc,hc);
		ret = getch();
		if(ret  == '\033')
		{
			getch();
			switch(getch())
			{
			      	case 'A':
					sel = getNext(sel,num-1,UP);
				    break;
				case 'B':
					sel = getNext(sel,num-1,DOWN);
				    break;
				case 'C':
					deleteLines(num+1);
					return sel;	
				    break;
				case 'D':
					deleteLines(num+1);
					return -1;	
				    break;
			}
			deleteLines(num);
		}
		else if(ret == 0x0A)
		{
			deleteLines(num+1);
			return sel;	
		}
		else
		{
			deleteLines(num);
		}
	}
}


static char* menu1[] = {};
static char* menu2[] = {};
static char* menu3[] = {};
static char* menu2a[] = {"Option 2a1","Option 2a2","Option 2a3","Option 2a4","Option 2a5"};
static char* menu2b[] = {"Option 2b1","Option 2b2","Option 2b3","Option 2b4","Option 2b5"};

#define S_SEARCH_DEVICES 	0
#define S_MENU1 	1
#define S_SETTINGS 	2
#define S_SET_SETTING 	3
#define S_END	10

#define FGC 	34
#define BGC 	0
#define HC 	47

#include "lib.h"

int main(int argc, char *argv[]) 
{

	int64_t ret;
	uint8_t state = S_SEARCH_DEVICES;
	modbus_t* ctx = NULL;
	uint32_t baud = 115200;
	char* port = "/dev/ttyS2";
	uint32_t address = 15;
	uint16_t cnt = 0;
	uint16_t cnt2 = 0;
	volatile EM_Device_t* dev;
	EM_Device_t* devices[256];
	device_t* models[16];
	device_t* cmodel;

	config_t* conf;
	uint8_t retries = 0;
	uint16_t* buff;
	uint32_t value;
	uint8_t len;
	
	device_t devs[] = 
	{
		__EM330,
		__EM340,
		__EM210
	};

	if(strcmp(port,"/dev/ttyS2")==0)
	{
		GPIOExport(131);
		GPIODirection(131,OUT);
	}
	else if(strcmp(port,"/dev/ttyS1")==0)
	{
		GPIOExport(158);
		GPIODirection(158,OUT);
	}

	buff = malloc(16*sizeof(uint16_t));
	
	hideCursor();

	printf(" \033[%d;44m%s\033[%dm\n",37," ModBus Configuration Tool ",0);

	while(state!=S_END)
	{

	switch(state)
	{
		case S_SEARCH_DEVICES:
			if(cnt!=0)
				resetDeviceCount();
			/*for(int j=0; j<cnt; j++)
			{
				free(menu1[j]);
			}*/
			searchDevicesGeneric(ctx,port,baud,address,devs);

			cnt = getDeviceCount();
			
			for(int i=0;i<cnt;i++)
			{
				dev = getDevice(i);
				models[i] = dev->model;
				menu1[i] = malloc(sizeof(char)*64);

				snprintf(menu1[i],64,"%s @ %s id %d #%s",dev->Name,dev->Port,dev->Address,dev->Serial);
			}
			
			state = S_MENU1;

			break;
		case S_MENU1:
			ret = menu(menu1,"ModBus Devices",cnt,FGC,BGC,HC);
			if(ret==-1)
			{
				state = S_END;
			}
			else
			{
				dev = getDevice(ret);
				cmodel = models[ret];
				state = S_SETTINGS;
			}

			break;
		case S_SETTINGS:
			if(ctx!=NULL)
			{
				modbus_close(ctx);
				ctx = NULL;
			}
			ctx = modbus_new_rtu(port,baud,'N',8,1);
			if(strcmp(port,"/dev/ttyS2")==0)
			{
				ctx->rw_pin = 131;
				ctx->t_char = getTimeOnBus(baud);
				GPIOExport(131);
				GPIODirection(131,OUT);
			}
			else if(strcmp(port,"/dev/ttyS1")==0)
			{
				ctx->rw_pin = 158;
				ctx->t_char = getTimeOnBus(baud);
				GPIOExport(158);
				GPIODirection(158,OUT);
			}
			modbus_set_slave(ctx,dev->Address);
			modbus_connect(ctx);

			cnt2 = 0;
			for(int i=0; i<cmodel->config_regs; i++)
			{
				conf = &cmodel->config[i];

				while((modbus_read_registers(ctx,conf->offset,conf->size,buff)!=conf->size)&&(retries<5))
					retries++;
				retries = 0;

				if(conf->size==__2BYTE)
				{
					menu2[cnt2] = malloc(sizeof(char)*64);
					value = buff[0];
					if(conf->conv!=NULL)
					{
						snprintf(menu2[cnt2],64,conf->format,lookupConversion(conf->conv,value));
					}
					else
					{
						snprintf(menu2[cnt2],64,conf->format,value);
					}
					cnt2++;
				}
				else if(conf->size==__4BYTE)
				{
					menu2[cnt2] = malloc(sizeof(char)*64);
					value = buff[0]+(buff[1]<<16);
					if(conf->conv!=NULL)
					{
						snprintf(menu2[cnt2],64,conf->format,lookupConversion(conf->conv,value));
					}
					else
					{
						snprintf(menu2[cnt2],64,conf->format,value);
					}
					cnt2++;
				}
			}

			ret = menu(menu2,"Settings",cnt2,FGC,BGC,HC);
			if(ret==-1)
			{
				state = S_SEARCH_DEVICES;
			}
			else
			{
				state = S_SET_SETTING;
			}
			break;
		case S_SET_SETTING:
			conf = &cmodel->config[ret];

			int n = 0;
			if(conf->conv==NULL)
			{
				
				ret = nmenu(conf->min,conf->max,conf->format,"Set a Setting",FGC,BGC,HC);
			}
			else
			{
				for(int i=conf->min; i<=conf->max; i++)
				{
					menu3[n] = malloc(sizeof(char)*64);
					snprintf(menu3[n],64,"%s",lookupConversion(conf->conv,i));
					n++;
				}

				ret = menu(menu3,"Set a Setting",n,FGC,BGC,HC);
			}

			if(ret==-1)
			{
				state = S_SETTINGS;
			}
			else
			{
				if(conf->conv!=NULL)
				{
					value = reverseLookupConversion(conf->conv,menu3[ret]);
				}
				else
				{
					value = ret;
				}
				writeConfigGeneric(ctx,cmodel,conf->type,value);
				sleep(1);
				state = S_SETTINGS;
			}
			break;
	}

	}

	setTextColor(_RESET);
	showCursor();

  	return 0;
}



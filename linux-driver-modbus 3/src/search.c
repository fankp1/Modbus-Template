#include "lib.h"

#define BAUDRATES_SIZE	4

int main(int argc, char *argv[]) 
{

	modbus_t *ctx;
	uint32_t baud;
	uint32_t address;
	EM_Device_t* dev; 
	char* port;
	uint32_t baudrates[4] = {9600,38400,57600,115200};
	char* ports[5] = {"/dev/ttyUSB0","/dev/ttyUSB1","/dev/ttyS0","/dev/ttyS2","/dev/ttyS4"};
	uint8_t JSON;
	uint16_t tmp;
	uint32_t value;
	config_t* conf;

	resetDeviceCount();

	device_t known_devices[] = 
	{
		__EM330,
		__EM340,
		__EM210,
		__SUNSPEC
	};

	if(argc==4)
	{
		port = argv[1];
		baud = strtol(argv[2],(char**)NULL,10);
		address = strtol(argv[3],(char**)NULL,10);
	}
	else
	{
		printf("Usage: Port Baud max.Address\n");
		return -1;
	}
/*
	if(argc==5&&(strcmp(argv[4],"-json")==0))
	{
		JSON = 1;
	}
	else
	{
		JSON = 0;
	}
*/
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

	if(searchDevicesGeneric(ctx,port,baud,address,known_devices)==0)
	{
/*		if(JSON==0)
		{
			printf("No Devices found on %s with Baudrate %d\n",port,baud);
		}
*/	}

	//Load Configuration
	for(int o=0;o<getDeviceCount();o++)
	{
		dev = getDevice(o);
		if(dev->Baud!=115200)
		{
			ctx = modbus_new_rtu(dev->Port,dev->Baud,'N',8,1);
			if(strcmp(port,"/dev/ttyS2")==0)
			{
				ctx->rw_pin = 131;
				ctx->t_char = getTimeOnBus(baud);
			}
			else if(strcmp(port,"/dev/ttyS1")==0)
			{
				ctx->rw_pin = 158;
				ctx->t_char = getTimeOnBus(baud);
			}
			else
			{
				ctx->rw_pin = 0;
			}
			modbus_set_slave(ctx,dev->Address);
			if(modbus_connect(ctx)==0)
			{
				conf = getConfig(dev->model,__BAUDRATE);
				value = reverseLookupConversion(conf->conv,"115200");
				writeConfigGeneric(ctx,dev->model,__BAUDRATE,value);
			}
			else
			{
				printf("Error while writing Configuration !!\n");
			}
		}
	}	  


		printf("{\n\"count\": %d,\n\"devices\": [\n",getDeviceCount());
		for(int m=0;m<getDeviceCount();m++)
		{
			dev = getDevice(m);
			printf("\t{\n");
			printf("\t\"name\":\"%s\",\n",dev->Name);
			printf("\t\"description\":\"%s%s\",\n",dev->Name,dev->Version);
			printf("\t\"port\":\"%s\",\n",dev->Port);
			printf("\t\"baudrate\":\"%d\",\n",dev->Baud);
			printf("\t\"address\":%d,\n",dev->Address);
			printf("\t\"serial\":\"%s\",\n",dev->Serial);
			printf("\t\"modelID\":\"%d\"\n",dev->modelID);
			if((m+1)<getDeviceCount())
			{
				printf("\t},\n");
			}
			else
			{
				printf("\t}\n");
			}
		}
		printf("]\n}\n");
	
	return 0;
}



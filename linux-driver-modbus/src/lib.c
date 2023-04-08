#include "lib.h"

static EM_Device_t 	devices[256];
static uint8_t 		device_cnt;

EM_Device_t* getDevice(uint8_t p)
{
	return &devices[p];
}

uint8_t getDeviceCount()
{
	return device_cnt;
}

void resetDeviceCount()
{
	device_cnt = 0;
}

void writeConfigGeneric(modbus_t* ctx, device_t* dev, uint8_t config, uint32_t value)
{
	config_t* conf = dev->config;
	uint32_t ret;
	uint32_t ret2;
	uint16_t tmp;
	uint32_t tmp2;
	
	conf = getConfig(dev,config); 
	
	if(value>conf->max)
	{
		printf("Error: value too large!\n");
		return;
	}

	if(value<conf->min)
	{
		printf("Error: value too small!\n");
		return;
	}

	for(int j=0; j<5; j++)
	{
		if(conf->size==__2BYTE)
		{
			ret = modbus_write_register(ctx,conf->offset,value&0x0000FFFF);
		}
		else if(conf->size==__4BYTE)
		{
			ret = modbus_write_register(ctx,conf->offset,value&0x0000FFFF);
			ret = modbus_write_register(ctx,conf->offset,(value&0xFFFF0000)>>16);	
		}

		if(ret==1)
		{
			return;
		}
/*	
		if(conf->size==__2BYTE)
		{
			ret2 = modbus_read_registers(ctx,conf->offset,1,&tmp);
			if(tmp==value)
				return;
			printf("didn't work, retrying.. should be:%d is:%d, ret:%d, ret2:%d\n",value,tmp,ret,ret2);
		}
		else if(conf->size==__4BYTE)
		{
			modbus_read_registers(ctx,conf->offset,2,(uint16_t*)&tmp2);
			if(tmp2==value)
				return;	
			printf("didn't work, retrying.. should be:%d is:%d, ret:%d\n",value,tmp,ret);
		}
*/
	}

	return;
}

void displayAllRegistersGeneric(modbus_t* ctx, device_t* dev)
{
	time_t 		current_time = time(NULL);
	pagetable_t* 	current_page;
	pair_t*		registers = dev->registers;
	uint16_t 	pages = dev->length;
	uint16_t 	buffer_size = 0;
	uint16_t 	buffer_ptr = 0;
	uint16_t* 	buffer;
	void* 		data_ptr;
	float 		value;
	uint16_t	intvalue;
	uint16_t 	ret;
	uint16_t 	twait = getWaitTimeOnBus(115200);
	uint16_t 	tmp;

	buffer_size = __BASE + dev->size;
	buffer_ptr = __BASE;
	buffer = calloc(buffer_size,sizeof(uint16_t));

	for(int j=0; j<pages; j++)
	{

		current_page = dev->pages[j];
		//buffer[current_page->base+(current_page->size/2)] = 0x5555;
		
		printf("loading data at %d to %d size %d\n",current_page->base,buffer_ptr,current_page->size);
		//usleep(twait);
		modbus_read_registers(ctx,0x30,1,&tmp);
		usleep(twait);
		
		ret = modbus_read_registers(ctx,current_page->base,current_page->size,&buffer[buffer_ptr]);	
		usleep(twait);
		printf("ret1: %d \n",ret);
		
		if(ret == current_page->size)
		{
			buffer_ptr += current_page->size;
		}
		else
		{
			modbus_read_registers(ctx,0x30,1,&tmp);
			usleep(twait);
			printf("loading data at %d to %d size %d\n",current_page->base,buffer_ptr,current_page->size);
			ret = modbus_read_registers(ctx,current_page->base,current_page->size,&buffer[buffer_ptr]);		
			usleep(twait);
			printf("ret2: %d \n",ret);
			
			if(ret == current_page->size)
			{
				buffer_ptr += current_page->size;
			}
			else
			{
				return;
			}
		}

		/*
		if(buffer[current_page->base+(current_page->size/2)]==0x5555)
		{
			return;
		}
		*/
	}

	printf("----------\n");

	for(int i=0; i<dev->lines; i++)
	{
		data_ptr = &buffer[registers[i].offset];
	
		if(registers[i].offset==__TIME)
		{
			printf(registers[i].format,(time_t)current_time);
		}
		else
		{
			if(registers[i].size == __2BYTE)
			{	
				value = *(int16_t*)data_ptr;
			}
			else if(registers[i].size == __4BYTE)	
			{
				value = *(int32_t*)data_ptr;
			}
			else if(registers[i].size == __2BYTEU)	
			{
				value = *(uint16_t*)data_ptr;
			}
			else if(registers[i].size == __4BYTEU)	
			{
				value = ((*(uint16_t*)(data_ptr))<<16) + (*(uint16_t*)(data_ptr+1));
			}

			if(registers[i].factor > 0)
			{
				value = value*pow(10,-registers[i].factor);
			}
			//else
			//{
			//	printf(registers[i].format,intvalue);
			//}
				printf(registers[i].format,value);
		}
	}
}

uint8_t getTimeOnBus(uint32_t baud)
{
	switch(baud)
	{
		case 9600:
			return 99;
		case 19200:
			return 52;
		case 38400:
			return 26;
		case 57600:
			return 17;
		case 115200:
			return 11;
		default:
			return 0;
	}
}

uint16_t getWaitTimeOnBus(uint32_t baud)
{
	switch(baud)
	{
		case 9600:
		return 3646;
		break;
		case 19200:
		return 1823;
		break;
		default:
		return 1750;
		break;
	}
}

uint8_t searchDevicesGeneric(modbus_t* ctx, char* port, uint32_t baud, uint8_t maxAddress, device_t* list)
{
	uint16_t 	signature;
	uint16_t 	tmp;
	uint16_t 	twait;
	uint8_t 	cnt;

	ctx = modbus_new_rtu(port,baud,'N',8,1);

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

	twait = getWaitTimeOnBus(baud);

	for(int i=1; i<=maxAddress; i++)
	{
		modbus_set_slave(ctx,i);

		if(modbus_connect(ctx)==0)
		{	
			for(int j=0; j<_NUM_OF_DEVICES;j++)
			{
				signature = 0xFFFF;
				usleep(twait);
				modbus_read_registers(ctx,0x30,1,&tmp);
				usleep(twait);
				modbus_read_registers(ctx,list[j].sig_reg,1,&signature);
				tmp = signature&list[j].mask;
				//printf("ID %d| signature: %x trying mask: %x result:%x should be: %x\n",i,signature,list[j].mask,tmp,list[j].signature);

				if(tmp==list[j].signature)
				{
					cnt++;
					EM_Device_t dev;
					dev.Name = list[j].name;
					dev.Version = "";
					dev.Signature = signature;
					dev.Port = port;
					dev.Baud = baud;
					dev.Address = i;
					dev.model = &list[j];
					dev.modelID = j;
					getSerial(ctx,&dev,&list[j]);
					devices[device_cnt] = dev;
					device_cnt++;
					break;
				}
			}
		}
	}

	return cnt;
}

void getSerial(modbus_t* ctx, EM_Device_t* device, device_t* dev)
{
	config_t* conf = getConfig(dev,__SERIAL);
  	uint16_t buff[conf->size];
	uint8_t retries = 0;
	uint8_t j = 0;

  	while((modbus_read_registers(ctx,conf->offset,conf->size,buff)!=conf->size)&&(retries<5))
		retries++;

	device->Serial = malloc(sizeof(conf->size*2*sizeof(char)));

	for(int i=0; i<conf->size; i++)
	{
		if((buff[i]&0xFF00)==0)
		{
			device->Serial[j] = (char)buff[i]&0x00FF;
			j++;
		}
		else
		{
			device->Serial[j] = (char)((buff[i]&0xFF00)>>8);
			j++;
			device->Serial[j] = (char)buff[i]&0x00FF;
			j++;
		}
	}
}

config_t* getConfig(device_t* dev, uint8_t config)
{
	for(int i=0; i<dev->config_regs; i++)
	{
		if(dev->config[i].type==config)
		{
			return &dev->config[i];
		}
	}
}

void getAllConfigsGeneric(modbus_t* ctx, device_t* dev)
{
	config_t* conf;
	uint8_t retries = 0;
	uint16_t* buff;
	uint32_t value;

	buff = malloc(16*sizeof(uint16_t));

	printf("{\n");

	for(int i=0; i<dev->config_regs; i++)
	{

		conf = &dev->config[i];
		
		while((modbus_read_registers(ctx,conf->offset,conf->size,buff)!=conf->size)&&(retries<5))
			retries++;

		retries = 0;

		if(conf->size==__2BYTE)
		{
			value = buff[0];
			if(conf->conv!=NULL)
			{
				printf(conf->format,lookupConversion(conf->conv,value));
			}
			else
			{
				printf(conf->format,value);
			}
			printf("\n");
		}
		else if(conf->size==__4BYTE)
		{
			value = buff[0]+(buff[1]<<16);
			if(conf->conv!=NULL)
			{
				printf(conf->format,lookupConversion(conf->conv,value));
			}
			else
			{
				printf(conf->format,value);
			}
			printf("\n");
		}
	}
	printf("}\n");
}

char* lookupConversion(conversion_t* conv, uint32_t value)
{
	for(int i=0; i<conv->size; i++)
	{
		if(conv->numbers[i]==value)
			return (char*)conv->names[i];
	}
	return "";
}

uint32_t reverseLookupConversion(conversion_t* conv, char* name)
{
	for(int i=0; i<conv->size; i++)
	{
		if(strcmp(conv->names[i],name)==0)
			return conv->numbers[i];
	}
	return 0;	
}


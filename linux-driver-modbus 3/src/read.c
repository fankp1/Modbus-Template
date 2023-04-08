
#include "lib.h"

int main(int argc, char *argv[]) 
{
  modbus_t *ctx;
  uint32_t baud;
  uint32_t address;
  uint8_t devices;
  char* port;
  uint8_t JSON;
  uint16_t tmp;
  uint16_t signature;
  uint16_t model = 0xFFFF;

  device_t known_devices[] = 
  {
	__EM330,
	__EM340,
	__EM210,
	__SUNSPEC
  };
  uint8_t _num_of_devices = 4;

  if(argc==4||argc==5)
  {
	  port = argv[1];
	  baud = strtol(argv[2],(char**)NULL,10);
	  address = strtol(argv[3],(char**)NULL,10);
  }
  else
  {
	  printf("Usage: Port Baudrate Address [Model]\n");
	  return -1;
  }

 
  ctx = modbus_new_rtu(port,baud,'N',8,1);
  
  if(strcmp(port,"/dev/ttyS2")==0)
  {
  	  ctx->rw_pin = 131;
	  ctx->t_char = getTimeOnBus(baud); 
  	  //GPIOExport(131);
  	  //GPIODirection(131,OUT);
  }
  else if(strcmp(port,"/dev/ttyS1")==0)
  {
  	  ctx->rw_pin = 158;
	  ctx->t_char = getTimeOnBus(baud); 
  	  //GPIOExport(158);
  	  //GPIODirection(158,OUT);
  }
  else
  {
	  ctx->rw_pin = 0;
  }
  
  if(argc==5)
  {
	model = strtol(argv[4],(char**)NULL,10);
  	modbus_set_slave(ctx,address); 
  	if(modbus_connect(ctx)==0)
	{
		displayAllRegistersGeneric(ctx,&known_devices[model]);
  
	}
  }
  else
  {
  	modbus_set_slave(ctx,address); 
  	if(modbus_connect(ctx)==0)
  	{
		for(int i=0;i<_num_of_devices;i++)
		{
			modbus_read_registers(ctx,known_devices[i].sig_reg,1,&signature);

			tmp = signature&known_devices[i].mask;
			//printf("Device Signature: %x Mask: %x Result: %x\n",signature,known_devices[i].mask,tmp);

			if(tmp==known_devices[i].signature)
			{
				//printf("found a known device! %s \n",known_devices[i].name);
				displayAllRegistersGeneric(ctx,&known_devices[i]);
				return 0;
			}
			else
			{
				//printf("found a not known device! %x \n",signature);
			}
		}
  	}
  }
  
  return 0;
}




#include "lib.h"

int main(int argc, char *argv[]) 
{
  modbus_t *ctx;
  uint32_t baud;
  uint32_t address;
  uint8_t devices;
  //EM_Device_t* dev; 
  char* port;
  uint8_t JSON;
  uint16_t tmp;
  uint16_t signature;
  uint16_t* buffer = calloc(32,sizeof(uint16_t));

  device_t known_devices[] = 
  {
	__EM330,
	__EM340,
	__EM210
  };
  uint8_t _num_of_devices = 3;

  if(argc==4)
  {
	  port = argv[1];
	  baud = strtol(argv[2],(char**)NULL,10);
	  address = strtol(argv[3],(char**)NULL,10);
  }
  else
  {
	  printf("Usage: Port Baudrate Address\n");
	  return -1;
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
  else
  {
	  ctx->rw_pin = 0;
  }
 
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
			getAllConfigsGeneric(ctx,&known_devices[i]);
			break;
		}
		else
		{
			//printf("found a not known device! %x \n",signature);
		}
	}
  }
  
  return 0;
}



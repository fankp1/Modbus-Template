#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <string.h>

static int fd = -1;

int openi2cbus(char* file)
{
	fd = -1;
        if((fd = open(file, O_RDWR)) < 0)
        {
		printf("Error: Failed to open the i2c bus");
                return -1;
        }
	return 0;
}

int readi2cbus(int addr, char* buffer, int length)
{
        if(ioctl(fd, I2C_SLAVE, addr) < 0)
        {
                printf("Error: Failed to acquire bus access and/or talk to slave.\n");
                return -1;
        }

	if(read(fd, buffer, length) != length)
        {
                //printf("Error: Failed to read from the i2c bus.\n");
		return -1;
        }
        else
        {
		for(int i=0;i<length;i++)
		{
			if(buffer[i]==0xff)
				buffer[i] = 0x0A;
		}

        }
	return 0;
}

int writei2cbus(char* buffer, int length)
{
	if(write(fd, buffer, length) != length) 
	{
		printf("Error Failed to write to the i2c bus.\n");
		return -1;
	}
	return 0;
}

#define I2C_SUPPORT_HAT		0x50
#define I2C_IFM			0x51

int main()
{
	char buffer[128];

	openi2cbus((char*)"/dev/i2c-1");

	if(readi2cbus(I2C_SUPPORT_HAT,buffer,128)!=-1)
	{
		printf("Support HAT @ 0x50:\n");
		printf("%s",buffer);	

		memset(buffer,0x00,128);
		
		if(readi2cbus(I2C_IFM,buffer,128)!=-1)
		{
			printf("IFM @ 0x51:\n");
			printf("%s",buffer);	
		}
	}
	else
	{
                printf("Error: Failed to read from the i2c bus.\n");	
	}

	return 0;
}

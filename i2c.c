// I2C test program for a MCP23017

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

// I2C Linux device handle
int i2cFile;

// Address of MCP23017
int  mcp_address=0x20;      // I2C Address of MCP23017 Chip
int  GPIOA=0x12;            // Register Address of Port A
int  GPIOB=0x13;            // Register Address of Port B
int  IODIRA=0x00;            // IODIRA register
int  IODIRB=0x01;            // IODIRB register

//Buffer
char buffer[4];

// open the Linux device
void i2cOpen()
{
	i2cFile = open("/dev/i2c-2", O_RDWR);
	if (i2cFile < 0) {
		perror("i2cOpen");
		exit(1);
	}
}

// close the Linux device
void i2cClose()
{
	close(i2cFile);
}

// set the I2C slave address for all subsequent I2C device transfers
void i2cSetAddress(int address)
{
	if (ioctl(i2cFile, I2C_SLAVE, address) < 0) {
		perror("i2cSetAddress");
		exit(1);
	}
}

// write a 8 bit value to a register 
void mcp23017WriteRegister(uint8_t reg, uint8_t value)
{
	buffer[0] = reg;
	buffer[1] = value;
	if (write(i2cFile, buffer, 2) != 2) {
		perror("MCP23017: set register address\n");
	}
}

// read a 8 bit value from a register
uint8_t mcp23017ReadRegister(uint8_t reg)
{
	uint8_t data[1];
	data[0] = reg;
	if (write(i2cFile, data, 1) != 1) {
		perror("mcp23017: set register address");
	}
	if (read(i2cFile, data, 1) != 1) {
		perror("mcp23017: read value");
	}
	return data[0];
}

// set IO ports to input, if the corresponding direction bit is 1,
// otherwise set it to output
void mcp23017SetDirection(uint8_t reg, uint8_t direction)
{
	mcp23017WriteRegister(reg, direction);
}

int main(int argc, char** argv)
{
	uint8_t data;
	// open Linux I2C device
	printf("Open I2C device...\t");
	i2cOpen();
	printf("OK!\n\n");

	// set address of the MCP23017
	printf("Set MCP23017 Address...\t");
	i2cSetAddress(mcp_address);
	printf("OK!\n\n");

	// set GPIOA-0 to GPIOA-7 as outputs
	printf("Set GPIOA AS outputs...\t");
	mcp23017SetDirection(IODIRA, 0x00);
	printf("OK!\n\n");

	while(1){
		mcp23017WriteRegister(GPIOA, 0xff);
		printf("Set the GPIOA HIGH!\n");
		sleep(1);
		mcp23017WriteRegister(GPIOA, 0x00);
		printf("Set the GPIOA LOW!\n");
		sleep(1);
    }
	

	// close Linux I2C device
	i2cClose();

	return 0;
}

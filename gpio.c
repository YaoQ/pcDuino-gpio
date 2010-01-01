/************************************************************
* gpio.c : Accessing the GPIO of pcDuino directly using C
*
* Author : Qi Yao <qi.yao@linksprite.com>
*
* Turns the desired GPIO pin on and off ten times
*
*************************************************************/
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
 
#define pinModePath "/sys/devices/virtual/misc/gpio/mode/gpio%d"
#define pinDataPath "/sys/devices/virtual/misc/gpio/pin/gpio%d"

int main(int c, char *v[]) {
 
  int pinMode;
  int pinData;
  char buffer[128];
  int pin;
  
  if(c != 2) {
    fprintf(stderr,"usage: %s [pin]\n",v[0]);
    exit(1);
  }
  pin = atoi(v[1]);
  
  sprintf(buffer,pinModePath,pin); 
  pinMode = open(buffer, O_RDWR);
  
  sprintf(buffer,pinDataPath,pin);
  pinData = open(buffer, O_RDWR);

  // "0" - pin INPUT
  // "1" - pin OUTPUT
  // "8" - pin INPUT with pull-up resistor
  write(pinMode, "1", 1);
   
  // "0" - LOW
  // "1" - HIGH
  write(pinData, "1", 1);
   
  int i;
  for (i=0; i < 100; i++) {
    write(pinData, "1", 1);
    sleep(1);
    write(pinData, "0", 1);
    sleep(1);
  }
}

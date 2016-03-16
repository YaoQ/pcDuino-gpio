all: gpio i2c

gpio: gpio.c
	cc gpio.c -o gpio  

i2c: i2c.c
	cc i2c.c -o i2c 

clean :
	rm gpio 
	rm i2c 

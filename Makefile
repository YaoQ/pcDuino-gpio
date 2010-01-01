gpio: gpio.o 
	cc -o gpio gpio.o 

gpio.o : gpio.c
	cc -c gpio.c
clean :
	rm gpio gpio.o 

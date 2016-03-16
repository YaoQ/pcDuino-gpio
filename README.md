# pcDuino-gpio
This is the example for programming GPIO on pcDuino using C language.


## How to use this I2C demo
When you use this I2C demo, you need mount [I/O expander shield for Arduino/pcDuino](http://store.linksprite.com/i-o-expander-shield-for-arduino-pcduino/) to pcDuino, And you have to install i2c-dev:

```
sudo apt-get install libi2c-dev i2c-tools
```
And use `i2cdetect` tool to check the I2C device: 
```
linaro@linaro-alip:~/pcDuino-gpio$ i2cdetect -y 2
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: 20 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --                                                                                    
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --                                                                                    
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --                                                                                    
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --                                                                                    
70: -- -- -- -- -- -- -- --       
```

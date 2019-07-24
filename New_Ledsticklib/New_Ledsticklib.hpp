/*!
@file Ledsticklib.hpp
*This is the header file of the New_Ledsticklib Library. The functions declared
in the class are elaborated in the cpp file.
@mainpage Library for driving Adafruit Neopixel and other WS2812 led.
 */

#include "hwlib.hpp"

#ifndef NEW_LEDSTICKLIB_HPP
#define NEW_LEDSTICKLIB_HPP


/*!
@brief
*This is the class for WS2812 leds. The class is a subclass and is based on
*window from the hwlib library. In the protected specifier are variables stored
*like the portarray and pinarray which stores the port and bit of each pin
*given in the contructor. The other variables like  
*/
class New_ledsticklib: public hwlib::window{

const int x_size = 8;
const int y_size = 7;

protected:

//variables
int* portarray;
int* pinarray;
int stick;
hwlib::color* buffer;

//functions

auto confport(int port);

uint32_t confmask(int pin ){
return (0x1u << pin);
}

static void  wait_busy( int32_t n ) __attribute__((noinline));

int checkbit(uint8_t value, int number);

void sendBit(bool bit);

void sendByte(uint8_t value);

public:

/*!
@brief
*This is the constructor of the library. To call the object you need three
*values. At first an hwlib::xy value so that all leds will be configured. 
*Secondly an array of the portletter from each pin, and at last an pinarray 
*which consist of the portnumber from each pin.
*/
New_ledsticklib(hwlib::xy total_pixels, int* portarray, int* pinarray):
window(total_pixels),
portarray(portarray),
pinarray(pinarray)
{}

void write_implementation( hwlib::xy pos, hwlib::color c ) override;

void write( hwlib::xy pos, hwlib::color c);

void flush() override;

void reset();

void clear() override;

};

#endif
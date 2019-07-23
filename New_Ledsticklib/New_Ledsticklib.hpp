#include "hwlib.hpp"

#ifndef NEW_LEDSTICKLIB_HPP
#define NEW_LEDSTICKLIB_HPP

class New_ledsticklib: public hwlib::window{

protected:
hwlib::color GRB;
hwlib::xy position;
int* portarray;
int* pinarray;
int stick;
int colorindex = 0;
hwlib::xy start[99];
hwlib::xy end[99];
int arraylength = 0;
hwlib::color RGB_array[99];

public:
New_ledsticklib(hwlib::xy total_pixels, int* portarray, int* pinarray):
window(total_pixels),
portarray(portarray),
pinarray(pinarray)
{}

auto confport(int port);

uint32_t confmask(int pin ){
return (0x1u << pin);
}

static void  wait_busy( int32_t n ) __attribute__((noinline));

int checkbit(uint8_t value, int number);

void sendBit(bool bit);

void sendByte(uint8_t value);

void showcolor();

void write_implementation( hwlib::xy pos, hwlib::color c ) override;

void write_change(int index, hwlib::xy pos1, hwlib::xy pos2, hwlib::color c);

void write_line( hwlib::xy pos1, hwlib::xy pos2, hwlib::color c);


bool check_xy(int x, int y);

void flush() override;

void clear();

};

#endif
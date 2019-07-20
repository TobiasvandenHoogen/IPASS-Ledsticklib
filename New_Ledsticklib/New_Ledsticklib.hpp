#include "hwlib.hpp"

#ifndef NEW_LEDSTICKLIB_HPP
#define NEW_LEDSTICKLIB_HPP

class New_ledsticklib: public hwlib::window{

protected:
hwlib::xy total_pixels;
uint32_t pin;
Pio & port;
uint32_t mask;


public:
New_ledsticklib(hwlib::xy total_pixels , uint32_t pin, uint32_t port_number):
window(total_pixels ),
pin ( pin ),
port{ hwlib::target::port_registers( port_number ) },
mask{ 0x1u << pin}
{
port.PIO_OER = mask;
}

static void  wait_busy( int32_t n ) __attribute__((noinline)){
   __asm volatile(                  
      "   .align 4           \t\n"  
      "1: subs.w  r0, #3     \t\n"  
      "   bgt 1b             \t\n"  
      : : "r" ( n )          // uses (reads) n         
   ); 
}

int checkbit(uint8_t value, int number){
    value = value & (1 << number);
    value = value >> number;
    return value;
}


void sendBit(bool bit){


if(bit){
    port.PIO_SODR = mask;
    wait_busy(58);
    port.PIO_CODR = mask;
     wait_busy(20);
}

else{
    port.PIO_SODR = mask;
    wait_busy(5);
    port.PIO_CODR = mask;
     wait_busy(58);
}
}

void sendByte(uint8_t value){
for(int i = 7; i >= 0; i--){
    int bit = checkbit(value, i);
    this->sendBit(bit);
}
}


void showcolor(){
    sendByte(0);
    sendByte(50);
    sendByte(50);
}

void write_implementation( hwlib::xy pos, hwlib::color c ) override{
    int i = 0;
    i++;
}

void flush() override{
for(int i = 0; i < 8; i++){
    showcolor();
}

hwlib::wait_us(50);
}

};

#endif
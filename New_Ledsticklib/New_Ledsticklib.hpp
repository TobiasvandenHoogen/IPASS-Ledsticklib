#include "hwlib.hpp"

#ifndef NEW_LEDSTICKLIB_HPP
#define NEW_LEDSTICKLIB_HPP

class New_Ledsticklib : public hwlib::window {
protected:
hwlib::xy total_pixels;
uint8_t redvalue;
uint8_t greenvalue;
uint8_t bluevalue;
uint32_t pin;
Pio & port;
uint32_t mask;
void sendBit(bool bit);
void sendByte(uint8_t value);
auto nanosec_to_cycle();

public:
New_Ledsticklib(hwlib::xy total_pixels, uint32_t pin, uint32_t port_number):
window(total_pixels),
pin ( pin ),
port{ hwlib::target::port_registers( port_number ) },
mask{ 0x1u << pin}
{
port.PIO_OER = mask;
}

void config_pin();

void test();

void write_implementation( hwlib::xy pos, hwlib::color c ) override;

void flush();

void clear();

static void  wait_busy( int32_t n ) __attribute__((noinline)){
   __asm volatile(                  
      "   .align 4           \t\n"  
      "1: subs.w  r0, #3     \t\n"  
      "   bgt 1b             \t\n"  
      : : "r" ( n )          // uses (reads) n         
   ); 
}

};

#endif 

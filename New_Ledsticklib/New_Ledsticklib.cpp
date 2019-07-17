#include "New_Ledsticklib.hpp"


void New_Ledsticklib::write_implementation(hwlib::xy pos, hwlib::color c ){
redvalue = c.red;
greenvalue = c.green;
bluevalue = c.blue;
}

inline void New_Ledsticklib::sendBit(bool bit){
auto TL0 = 800; 
auto TH0 = 350;
auto TL1 = 600;
auto TH1 = 700;
//auto latch = 7000;
auto nanosec_per_sec = 1000000000L;
auto cycles_per_second = 84000000;
auto nanosec_per_cycle = (nanosec_per_sec/ cycles_per_second);
#define nanosec_to_cycle(n)  ( (n) / nanosec_per_cycle)

if(bit){
    port.PIO_SODR = mask;
    wait_busy(nanosec_to_cycle(TH1));
    port.PIO_CODR = mask;
    wait_busy(nanosec_to_cycle(TL1));
}

else{
    port.PIO_SODR = mask;
    wait_busy(nanosec_to_cycle(TH0));
    port.PIO_CODR = mask;
    wait_busy(nanosec_to_cycle(TL0));
}

}

void New_Ledsticklib::sendByte(uint8_t value){
for(int i = 7; i >= 0; i++){
this->sendBit(((value >> i) & 0x01));
}

}

inline void New_Ledsticklib::flush(){
this->sendByte(greenvalue);
this->sendByte(redvalue);
this->sendByte(bluevalue);
hwlib::wait_us((7000 / 1000UL) + 1);
}

void New_Ledsticklib::clear(){
 redvalue = 50;
 greenvalue = 0;
 bluevalue = 0;
 this->flush();   
}

void New_Ledsticklib::test(){
    for(;;){
       port.PIO_SODR = mask;
    }
}
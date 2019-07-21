#include "New_Ledsticklib.hpp"

auto New_ledsticklib::confport(int port){
    switch(port){
        case 0: return PIOA;
        case 1: return PIOB;
        case 2: return PIOC;
        case 3: return PIOD;
        default: return PIOA;
    }
}

void New_ledsticklib::wait_busy( int32_t n ){
   __asm volatile(                  
      "   .align 4           \t\n"  
      "1: subs.w  r0, #3     \t\n"  
      "   bgt 1b             \t\n"  
      : : "r" ( n )          // uses (reads) n         
   ); 
}


int New_ledsticklib::checkbit(uint8_t value, int number){
    value = value & (1 << number);
    value = value >> number;
    return value;
}


void New_ledsticklib::sendBit(bool bit){
auto porta = confport(portarray[stick]);
auto maska = confmask(pinarray[stick]);
porta->PIO_OER = maska;
if(bit){
    porta->PIO_SODR = maska;
    wait_busy(58);
    porta->PIO_CODR = maska;
    wait_busy(20);
}

else{
    porta->PIO_SODR = maska;
    wait_busy(5);
    porta->PIO_CODR = maska;
    wait_busy(58);
}
}

void New_ledsticklib::sendByte(uint8_t value){
for(int i = 7; i >= 0; i--){
    int bit = checkbit(value, i);
    this->sendBit(bit);
}
}


void New_ledsticklib::showcolor(){
    sendByte(GRB.green);
    sendByte(GRB.red);
    sendByte(GRB.blue);
}

void New_ledsticklib::write_implementation( hwlib::xy pos, hwlib::color c ){
    position.x = pos.x;
    position.y = pos.y;
    GRB = c;
}

void New_ledsticklib::flush(){
       hwlib::wait_ms(50);
    for(int y = 0; y < size.y; y++){
        stick = y;
        if((y == position.y) || (position.y == size.y)){
            for(int x = 0; x < size.x; x++){
                if((x == position.x) || (position.x == size.x)){
                    showcolor();
                }
                else{
                    clear();
                }
            }
            hwlib::wait_ms(50);
        }
        else{
            for(int x = 0; x < size.x; x++){
                clear();
            }
            hwlib::wait_ms(50);
        }
    }
}

void New_ledsticklib::clear(){
    sendByte(0);
    sendByte(0);
    sendByte(0);
}


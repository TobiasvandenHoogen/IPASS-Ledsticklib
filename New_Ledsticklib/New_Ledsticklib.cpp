#include "New_Ledsticklib.hpp"

//function which returns a port depending on the giving parameter
auto New_ledsticklib::confport(int port){
    switch(port){
        case 0: return PIOA;
        case 1: return PIOB;
        case 2: return PIOC;
        case 3: return PIOD;
        default: return PIOA; //if the parameter doesn't match with the cases
    }
}


//assembly functions which waits at least 3 cycles (33 nanoseconds) times
//the given value. this function is used to create a delay in the sendBit
//function
void New_ledsticklib::wait_busy( int32_t n ){
   __asm volatile(                  
      "   .align 4           \t\n"  
      "1: subs.w  r0, #3     \t\n"  
      "   bgt 1b             \t\n"  
      : : "r" ( n )          // uses (reads) n         
   ); 
}


//function which checks if a bit from a byte is 0 or 1
int New_ledsticklib::checkbit(uint8_t value, int number){
    value = value & (1 << number); //to make sure only the chosen index remains
    value = value >> number;       //shift chosen index all the way to the right
    return value;                  //return value is either 0 or 1
}

bool New_ledsticklib::check_xy(int x, int y){
for(int i = 0; i < arraylength; i++){
 if(((y >= start[i].y) && (y <= end[i].y)) || (start[i].y == 8)){
    if(((x >= start[i].x) && (x <= end[i].x)) || (start[i].x == 8)){
        colorindex = i;
        return true;
    }
    }
}
    return false;
}

//function which sets a bit of a stick(depending on fush function) as
//output and sends a 0 or 1 bit depending on the bit parameter
void New_ledsticklib::sendBit(bool bit){
auto port = confport(portarray[stick]);
auto mask = confmask(pinarray[stick]);
port->PIO_OER = mask;
if(bit){
    port->PIO_SODR = mask; //pin high 
    wait_busy(58);           //wait 58 * 11 = 638 nanoseconds
    port->PIO_CODR = mask; //pin low
    wait_busy(20);           //wait 20 * 11 = 220 nanoseconds
}

else{
    port->PIO_SODR = mask; //pin high
    wait_busy(10);           //wait 10 * 11 = 110 nanoseconds
    port->PIO_CODR = mask; //pin low   
    wait_busy(58);           //wait 58 * 11 = 638 nanoseconds
}
}

//function wich takes the parameter value and sends each bit with sendBit
void New_ledsticklib::sendByte(uint8_t value){
for(int i = 7; i >= 0; i--){
    int bit = checkbit(value, i);
    this->sendBit(bit);
}
}

//function which sends each colovalue(byte) in this order: green, red and blue
void New_ledsticklib::showcolor(){
    sendByte(RGB_array[colorindex].green);
    sendByte(RGB_array[colorindex].red);
    sendByte(RGB_array[colorindex].blue);
}


//function which declares and sets a single neopixel as output
//DON'T PUT THIS FUNCTION IN A LONG FOR LOOP WITHOUT RESET!!!!
void New_ledsticklib::write_implementation( hwlib::xy pos, hwlib::color c ){
    start[arraylength] = pos;
    end[arraylength] = pos;
    RGB_array[arraylength] = c;
    arraylength++;
    }


void New_ledsticklib::write_line(hwlib::xy pos1, hwlib::xy pos2, hwlib::color c){
   start[arraylength] = pos1;
    end[arraylength] = pos2;
    RGB_array[arraylength] = c;
    arraylength++;
}

//function which sends bytes(depending on the given positiom )
void New_ledsticklib::flush(){
    for(int y = 0; y < size.y; y++){
        stick = y;
            for(int x = 0; x < size.x; x++){
                if(check_xy(x, y)){
                    showcolor();
                }
                else{
                    clear();
                }
            }
            hwlib::wait_us(50);
        }
}

void New_ledsticklib::reset(){
    arraylength = 0;
}


//function wich sends three bytes with the value zero to cause a neopixel to 
//go off
void New_ledsticklib::clear(){
    sendByte(0);
    sendByte(0);
    sendByte(0);
}


/*!
@file Ledsticklib.cpp
*This is the source file of the New_Ledsticklib library. 
 */

#include "New_Ledsticklib.hpp"

/*! 
@brief
*Function which returns a port depending on the giving parameter.
@param
*port    the given integer of the protected portarray
*/
auto New_ledsticklib::confport(int port){
    switch(port){
        case 0: return PIOA;
        case 1: return PIOB;
        case 2: return PIOC;
        case 3: return PIOD;
        default: return PIOA; //if the parameter doesn't match with the cases
    }
}

/*! 
@brief
*Assembly function which waits at least 3 cycles (33 nanoseconds) times
*the given value. this function is used to create a delay in the sendBit
@param
*n  the number of cycles times three
*/
void New_ledsticklib::wait_busy( int32_t n ){
   __asm volatile(                  
      "   .align 4           \t\n"  
      "1: subs.w  r0, #3     \t\n"  
      "   bgt 1b             \t\n"  
      : : "r" ( n )          // uses (reads) n         
   ); 
}

/*! 
@brief
*function which checks if a bit from a byte is 0 or 1
@param
value   the 8 bit value
@param
number  the index of the bit you want to check
*/
int New_ledsticklib::checkbit(uint8_t value, int number){
    value = value & (1 << number); //to make sure only the chosen index remains
    value = value >> number;       //shift chosen index all the way to the right
    return value;                  //return value is either 0 or 1
}

/*!
@brief
*function which sets a bit of a stick(depending on fush function) as
*output and sends a 0 or 1 bit depending on the bit parameter
@param
bit the type of bit you want to send(0 or 1)
*/
void New_ledsticklib::sendBit(bool bit){
auto port = confport(portarray[stick]);
auto mask = confmask(pinarray[stick]);
port->PIO_OER = mask;
if(bit){
    port->PIO_SODR = mask; //pin high 
    wait_busy(58);           //wait 58 * 33 = 638 nanoseconds
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

/*!
@brief
*function wich takes the parameter value and sends each bit with sendBit
@param
value   the byte you want to send
*/
void New_ledsticklib::sendByte(uint8_t value){
    for(int i = 7; i >= 0; i--){
        int bit = checkbit(value, i);
        this->sendBit(bit);
    }
}


/*!
@brief
*this function changes the color of a led
@param
*pos the x and y coordinate of the pixel you want to set a color
@param
c   the RGB colorvalue of the pixel you want to send as output
*/
void New_ledsticklib::write_implementation( hwlib::xy pos, hwlib::color c ){
    buffer[pos.x  + (pos.y * 8)] = c;
}

/*!
@brief
*this function is the same as write_implementation. The difference
*is that this function is public while the write implementation
*function is protected. The only reason this function exist is to match 
*with hwlib::window.
@param
*pos the x and y coordinate of the pixel you want to set a color
@param
c   the RGB colorvalue of the pixel you want to send as output
*/
void New_ledsticklib::write(hwlib::xy pos, hwlib::color c){
    write_implementation(pos, c);
}

/*!
@brief
*function which sends the colorvalues of the buffer array to each led
*/
void New_ledsticklib::flush(){
    for(int y = 0; y < size.y; y++){
        stick = y;
        for(int x = (y * 8); x < ((y + 1) * 8); x++){
            sendByte(buffer[x].green);
            sendByte(buffer[x].red);
            sendByte(buffer[x].blue);
        }
        hwlib::wait_us(50);
    }
}

/*!
@brief
*function wich sends three bytes with the value zero to each 
*led which cause a led to go off
//go off
*/
void New_ledsticklib::clear(){
    for(int i = 0; i < (size.x * size.y); i++){
        buffer[i] = hwlib::color(0,0,0);
    }
}


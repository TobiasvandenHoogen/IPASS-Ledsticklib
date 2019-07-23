#include "New_Ledsticklib.hpp"
#include "game.hpp"

int randomnumber(){
    static int n = 3251;
    n = ((n * n) / 100) % 10000;
    return n;
}

int randrange(){
return randomnumber() % (7 + 1 - 0) + 0;
}

void nicecolors(){
   hwlib::xy pixels(8, 7);
    hwlib::color RGB[3]{hwlib::color(10, 0, 0), 
    hwlib::color(10,10,10), 
    hwlib::color(0,0,10)};
    hwlib::xy p(7, 2);
    int ports[7] = {1, 3, 3, 2, 2, 2, 2};
    int pins[7] = {27, 8, 7, 29, 21, 22, 23};
    New_ledsticklib led(pixels, ports, pins);
    hwlib::wait_ms(1);
    led.write_implementation(hwlib::xy(3, 5), RGB[0]);
    led.write_implementation(hwlib::xy(5, 1), RGB[1]);
    for(;;){
        led.flush();
        hwlib::wait_ms(50);
    }
}

int main(){
    hwlib::xy pixels(8, 7); //total pixels and pins(1 pin with 8 leds)
    hwlib::color RGB(10, 0, 0); //hwlib color red
    hwlib::xy p(0, 0); // led 0 of stick 1 
    int ports[7] = {1, 3, 3, 2, 2, 2, 2};
    int pins[7] = {27, 8, 7, 29, 21, 22, 23};
    New_ledsticklib led(pixels, ports, pins); //declare the library object
    hwlib::wait_ms(1); //wait of 1ms so that the bytes are send correctly
    led.write_line(hwlib::xy(1,0), hwlib::xy(3, 6), RGB); //set coordinates of variable p and the colorvalues of RGB as output
    for(;;){
        led.flush(); //this wil turn the leds on
        hwlib::wait_ms(50); //wait of 50 ms so that they dont show random colors
    }
}


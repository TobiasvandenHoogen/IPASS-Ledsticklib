#include "New_Ledsticklib.hpp"

int main(){
    hwlib::xy pixels(8, 7);
    hwlib::color RGB(0, 10, 0);
    hwlib::xy p(7, 2);
    int ports[7] = {1, 3, 3, 2, 2, 2, 2};
    int pins[7] = {27, 8, 7, 29, 21, 22, 23};
    New_ledsticklib led(pixels, ports, pins);
    led.write_implementation(p, RGB);
    for(;;){
    hwlib::wait_ms(50);
    led.flush();
    }
}

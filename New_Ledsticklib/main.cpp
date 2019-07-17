#include "New_Ledsticklib.hpp"

int main(){
    hwlib::xy total(8, 1);
    hwlib::color(50, 50, 50);
    uint32_t portnum = 4;
    uint32_t pin = 8;
    New_Ledsticklib led(total, pin, portnum);
    led.test();
}
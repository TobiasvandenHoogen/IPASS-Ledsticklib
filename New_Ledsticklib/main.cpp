#include "New_Ledsticklib.hpp"

int main(){
    hwlib::xy pixels(1, 8);
    constexpr uint32_t portnum = 1;
    constexpr uint32_t pin = 27;
    New_ledsticklib led(pixels, pin, portnum);
    hwlib::wait_ms(1);
        led.flush();
    }

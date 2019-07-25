#include "New_Ledsticklib.hpp"
#include "game.hpp"
#include "test.hpp"

int main(){
     hwlib::xy t(8, 7);
    int ports[7] = {1, 3, 3, 2, 2, 2, 2};
    int pins[7] = {27, 8, 7, 29, 21, 22, 23};
    New_ledsticklib l(t, ports, pins);
    test te(l);
    hwlib::wait_ms(1);
    te.colorkitt();
}


#include "New_Ledsticklib.hpp"
#include "game.hpp"

void test(){
     hwlib::xy t(8, 7);
    int ports[7] = {1, 3, 3, 2, 2, 2, 2};
    int pins[7] = {27, 8, 7, 29, 21, 22, 23};
    New_ledsticklib l(t, ports, pins);
    l.clear();
    for(int i = 0; i < 56; i++){
        l.write_implementation(hwlib::xy(6, 7), hwlib::color(10, 0,0 ));
    }
    for(;;){
        l.flush();
        hwlib::wait_ms(1);

    }
}

void wait(){
    hwlib::xy t(8, 7);
    int ports[7] = {1, 3, 3, 2, 2, 2, 2};
    int pins[7] = {27, 8, 7, 29, 21, 22, 23};
    New_ledsticklib l(t, ports, pins);
    auto button1 = hwlib::target::pin_in(hwlib::target::pins::d5);
    hwlib::color C[3]{hwlib::color(10, 0, 0), 
    hwlib::color(0,10,0), 
    hwlib::color(0,0,10)};
    hwlib::wait_ms(1);
    for(;;){
    for(int c = 0; c < 3; c++){
    for(int i = 0; i < l.size.x; i++){
        for(int j = 0; j < l.size.y; j++){
        l.write_implementation(hwlib::xy(i, j), C[c]);
        button1.refresh();
        l.flush();


    }
        hwlib::wait_ms(50);
        l.clear();
    }

    }
    }
    }

int main(){
     hwlib::xy t(8, 7);
    int ports[7] = {1, 3, 3, 2, 2, 2, 2};
    int pins[7] = {27, 8, 7, 29, 21, 22, 23};
    New_ledsticklib l(t, ports, pins);
game g(l);
g.maingame();
}


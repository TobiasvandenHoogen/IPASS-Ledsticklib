#include "New_Ledsticklib.hpp"

class game: public New_ledsticklib {

protected:
int lives = 3;
int ports[7] = {1, 3, 3, 2, 2, 2, 2};
int pins[7] = {27, 8, 7, 29, 21, 22, 23};
int leftcatch = 3;
int rightcatch = 4;

public:
game():
New_ledsticklib(hwlib::xy(8, 7), ports, pins)
{}

void maingame(){
wait();
}

void wait(){
    auto button1 = hwlib::target::pin_in(hwlib::target::pins::d5);
    hwlib::color RGB[3]{hwlib::color(10, 0, 0), 
    hwlib::color(10,10,10), 
    hwlib::color(0,0,10)};
    hwlib::wait_ms(1);
    for(;;){
    for(int c = 0; c < 3; c++){
    for(int i = 0; i < size.x; i++){
        button1.refresh();
        write_implementation(hwlib::xy(i, 7), RGB[c]);
        flush();
        hwlib::wait_ms(50);
        if(button1.read() == 1){
        fallingball();
    }
    }
    }
    }
}

void fallingball(){
 hwlib::wait_ms(1);
    for(;;){
    int t = 0;
    for(int i = 6; i > 0; i--){
        write_implementation(hwlib::xy(t, i), hwlib::color(10, 0,0));
        flush();
        hwlib::wait_ms(250);
    }
    }
}

void catcher(){
    auto button1 = hwlib::target::pin_in(hwlib::target::pins::d5);
    auto button2 = hwlib::target::pin_in(hwlib::target::pins::d4);
    hwlib::wait_ms(1);
    

}


};



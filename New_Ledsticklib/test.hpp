#include "New_Ledsticklib.hpp"
#include "game.hpp"


class test{
protected:
bool succes;
hwlib::window & w;

public:
test(hwlib::window & w):
w (w)

{}

void bittest(){

}

void porttest(){

}

void colortest(){
    
}

//This test should write the first led of the first stick as red
void show_color(){
    w.clear();
    w.write(hwlib::xy(0,0), hwlib::color(10, 0, 0));
    for(;;){
        w.flush();
    }
}

//This test should write all leds red
void show_color_all(){
    w.clear();
    for(int i = 0; i < w.size.y; i++){
        for(int j = 0; j < w.size.x; j++)
            w.write(hwlib::xy(i,j), hwlib::color(10, 0, 0));
    }
    for(;;){
        w.flush();
    }
}

//this test should do kitt with three different colors
void colorkitt(){
 w.clear();
 for(int c = 0; c < 3; c++){
            for(int i = 0; i < w.size.x; i++){
                for(int j = 0; j < w.size.y; j++){
                    w.write(hwlib::xy(i, j), C[c]);
                    w.flush();
                }
                hwlib::wait_ms(50);
            }

        }
    }

//This test should run the game succesfull
void run_application(hwlib::window & w){
    g game(w);
    g.maingame();

}

};
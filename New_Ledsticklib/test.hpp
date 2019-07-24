#include "New_Ledsticklib.hpp"


class test: public New_ledsticklib{
protected:
bool succes;

public:
test(New_ledsticklib led):
New_ledsticklib(led) 

{}
void succes(){
if(succes){
    hwlib::cout << "test passed" << hwlib::endl;
}
else{
    hwlib::cout << "test failed" << hwlib::endl;
}
}

void bittest(){

}

void porttest(){

}

void colortest(){
    
}

//This test should write the first led of the first stick as red
void show_color(){
    clear();
    write(hwlib::xy(0,0), hwlib::color(10, 0, 0));
    for(;;){
        flush();
    }
}

//This test should write all leds red
void show_color_all(){
    clear();
    for(int i = 0; i < size.y; i++){
        for(int j = 0; j < size.x; j++)
            write(hwlib::xy(i,j), hwlib::color(10, 0, 0));
    }
    for(;;){
        flush();
    }
}

//This test should run the game succesfull
void run_application(hwlib::window & w){
    g game(w);
    g.maingame();

}

};
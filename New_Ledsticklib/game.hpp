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

int randomnumber(){
    static int n = 3251;
    n = ((n * n) / 100) % 10000;
    return n;
}

int randrange(){
return randomnumber() % (6 + 1 - 1) + 1;
}

void maingame(){
wait();
}

void wait(){
    auto button1 = hwlib::target::pin_in(hwlib::target::pins::d5);
    hwlib::color C[3]{hwlib::color(10, 0, 0), 
    hwlib::color(0,10,0), 
    hwlib::color(0,0,10)};
    hwlib::wait_ms(1);
    for(;;){
    for(int c = 0; c < 3; c++){
    for(int i = 0; i < size.x; i++){
        write_implementation(hwlib::xy(i, 8), C[c]);
        button1.refresh();
        flush();
        hwlib::wait_ms(50);
        if(button1.read() == 1){
        write_implementation(hwlib::xy(8, 8), hwlib::color(0,0,0));
        flush();
        reset();
        fallingball();
    }
        reset();
    }
    }
    }
}

void fallingball(){
 hwlib::wait_ms(1);
 auto button1 = hwlib::target::pin_in(hwlib::target::pins::d4);
 auto button2 = hwlib::target::pin_in(hwlib::target::pins::d5);
    for(;;){
    int random_num = randrange();
        if(lives == 0){
            lives = 3;
            break;
        }
    for(int i = 6; i > 0; i--){
        button1.refresh();
        button2.refresh();
        if((button1.read() == 1) && (leftcatch > 0)){
            leftcatch--;
            rightcatch--;
            hwlib::wait_ms(50);
        }
          if((button2.read() == 1) && (rightcatch < 7)){
            leftcatch++;
            rightcatch++;
            hwlib::wait_ms(50);
        }
        if(i == 1){
            if((random_num != leftcatch) && (random_num != rightcatch)){
                lives--;
            }
        }
        write_implementation(hwlib::xy(random_num, i), hwlib::color(10, 0,0));
        write_line(hwlib::xy(leftcatch, 0), hwlib::xy(rightcatch, 0), hwlib::color(0, 0, 10));
        flush();
        hwlib::wait_ms(250);
        reset();
    }
    }
}

};



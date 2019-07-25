#include "New_Ledsticklib.hpp"
#ifndef GAME_HPP
#define GAME_HPP

class game {

protected:
int lives = 3;
hwlib::window & w;
int leftcatch = 3;
int rightcatch = 4;

public:
game(hwlib::window & w):
w( w )
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
    w.clear();
    wait();
}

void wait(){
    auto button1 = hwlib::target::pin_in(hwlib::target::pins::d5); //leftbutton
    hwlib::color C[3]{hwlib::color(10, 0, 0), 
    hwlib::color(0,10,0), 
    hwlib::color(0,0,10)};
    hwlib::wait_ms(1);

    for(;;){
        for(int c = 0; c < 3; c++){
            for(int i = 0; i < w.size.x; i++){
                for(int j = 0; j < w.size.y; j++){
                    w.write(hwlib::xy(i, j), C[c]);
                    button1.refresh();
                    w.flush();

                if(button1.read() == 1){
                    w.clear();
                    w.flush();
                    fallingball();
                }


                }
                hwlib::wait_ms(50);
                w.clear();
            }

        }
    }
}

void fallingball(){
    hwlib::wait_ms(1);
    auto button1 = hwlib::target::pin_in(hwlib::target::pins::d4);
    auto button2 = hwlib::target::pin_in(hwlib::target::pins::d5);
    for(;;){
        int num = randrange();
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
            if((num != leftcatch) && (num != rightcatch)){
                lives--;
            }
        }
        w.write(hwlib::xy(num, i), hwlib::color(10, 0,0));
        w.write(hwlib::xy(leftcatch, 0), hwlib::color(0, 0, 10));
        w.write(hwlib::xy(rightcatch, 0), hwlib::color(0, 0, 10));
        w.flush();
        hwlib::wait_ms(250);
        w.clear();
    }
    }
}

};

#endif



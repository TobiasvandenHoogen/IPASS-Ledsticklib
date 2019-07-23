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

void bittest(New_ledsticklib led){

}

void porttest(){

}

void colortest(){
    
}

};
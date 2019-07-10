#include "hwlib.hpp"

class New_Ledsticklib : public hwlib::window {
protected:

public:

void write( hwlib::xy pos, hwlib::color c );

void flush();

void clear();

};
#pragma once
using namespace std;

class Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
public:
    Pixel(unsigned int blue = 0, unsigned int green = 0, unsigned int red = 0);
    unsigned char getBlue() const;
    void setBlue(unsigned char blue);
    unsigned char getGreen() const;
    void setGreen(unsigned char green);
    unsigned char getRed() const;
    void setRed(unsigned char red);

};

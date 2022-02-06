#include "Pixel.h"

Pixel::Pixel(unsigned int blue, unsigned int green, unsigned int red) {
    this->blue = blue;
    this->green = green;
    this->red = red;
}

unsigned char Pixel::getBlue() const {
    return blue;
}

void Pixel::setBlue(unsigned char blue) {
    this->blue = blue;
}

unsigned char Pixel::getGreen() const {
    return green;
}

void Pixel::setGreen(unsigned char green) {
    this->green = green;
}

unsigned char Pixel::getRed() const {
    return red;
}

void Pixel::setRed(unsigned char red) {
    this->red = red;
}
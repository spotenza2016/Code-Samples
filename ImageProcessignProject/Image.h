#pragma once
#include <string>
#include "Pixel.h"
using namespace std;

class Image {
    unsigned char IDLength;
    unsigned char colorMapType;
    unsigned char imageType;
    unsigned short colorMapOrigin;
    unsigned short colorMapLength;
    unsigned char colorMapDepth;
    unsigned short XOrigin;
    unsigned short YOrigin;
    unsigned short imageWidth;
    unsigned short imageHeight;
    unsigned char pixelDepth;
    unsigned char imageDescriptor;
    unsigned int size;
    Pixel* Pixels;
public:
    Image(const string& FileName);
    Image(const Image& rhs);
    Image& operator=(const Image& rhs);
    ~Image();
    void writeImage(const string& FileName);
    unsigned int getSize() const;
    void setSize(unsigned int size);
    Pixel* getPixels() const;
    void PrintAll() const;
    void SetWidthHeight(unsigned short imageWidth, unsigned short imageHeight);
    unsigned short GetWidth() const;
    unsigned short GetHeight() const;
    void setPixels(Pixel* Pixels);
};

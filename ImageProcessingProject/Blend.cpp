#include "Pixel.h"
#include "Blend.h"
#include "Image.h"
#include <iostream>
using namespace std;

Image& Blend::Multiply(const Image& Top, const Image& Bottom) {
    Pixel* TopPixels = Top.getPixels();
    Pixel* BottomPixels = Bottom.getPixels();
    Image* New = new Image(Bottom);
    Pixel* NewPixels = New->getPixels();
    for (unsigned int i = 0; i < Bottom.getSize(); i++) {
        NewPixels[i].setBlue(((float)BottomPixels[i].getBlue() * (float)TopPixels[i].getBlue() / 255.0f) + 0.5f);
        NewPixels[i].setGreen(((float)BottomPixels[i].getGreen() * (float)TopPixels[i].getGreen() / 255.0f) + 0.5f);
        NewPixels[i].setRed(((float)BottomPixels[i].getRed() * (float)TopPixels[i].getRed() / 255.0f) + 0.5f);
    }

    return *New;
}

Image& Blend::Subtract(const Image& Top, const Image& Bottom) {
    Pixel* TopPixels = Top.getPixels();
    Image* New = new Image(Bottom);
    for (unsigned int i = 0; i < Bottom.getSize(); i++) {
        AdjustBlue(*New, TopPixels[i].getBlue(), i, false);
        AdjustGreen(*New, TopPixels[i].getGreen(), i, false);
        AdjustRed(*New, TopPixels[i].getRed(), i, false);
    }
    return *New;
}

Image& Blend::Screen(const Image& Top, const Image& Bottom) {
    Pixel* TopPixels = Top.getPixels();
    Pixel* BottomPixels = Bottom.getPixels();
    Image* New = new Image(Bottom);
    Pixel* NewPixels = New->getPixels();
    for (unsigned int i = 0; i < Bottom.getSize(); i++) {
        NewPixels[i].setBlue((255.0f - (((255.0f - (float)BottomPixels[i].getBlue()) * (255.0f - (float)TopPixels[i].getBlue())) / 255.0f)) + 0.5f);
        NewPixels[i].setGreen((255.0f - (((255.0f - (float)BottomPixels[i].getGreen()) * (255.0f - (float)TopPixels[i].getGreen())) / 255.0f)) + 0.5f);
        NewPixels[i].setRed((255.0f - (((255.0f - (float)BottomPixels[i].getRed()) * (255.0f - (float)TopPixels[i].getRed())) / 255.0f)) + 0.5f);
    }

    return *New;
}

Image& Blend::Overlay(const Image& Top, const Image& Bottom) {
    Pixel* TopPixels = Top.getPixels();
    Pixel* BottomPixels = Bottom.getPixels();
    Image* New = new Image(Bottom);
    Pixel* NewPixels = New->getPixels();
    for (unsigned int i = 0; i < Bottom.getSize(); i++) {
        if ((float)BottomPixels[i].getBlue() / 255.0f <= 0.5) {
            float target = (2.0f * (float)BottomPixels[i].getBlue() * (float)TopPixels[i].getBlue() / 255.0f);
            if (target > 255.0f) {
                target = 255.0f;
            }
            NewPixels[i].setBlue(target + 0.5f);
        }
        else {
            float target = (2.0f * (((255.0f - ((float)BottomPixels[i].getBlue())) * (255.0f - (float)TopPixels[i].getBlue())) / 255.0f));
            if (target > 255.0f) {
                target = 255.0f;
            }
            NewPixels[i].setBlue(255.0f - target + 0.5f);
        }

        if ((float)BottomPixels[i].getGreen() / 255.0f <= 0.5) {
            float target = (2.0f * (float)BottomPixels[i].getGreen() * (float)TopPixels[i].getGreen() / 255.0f);
            if (target > 255.0f) {
                target = 255.0f;
            }
            NewPixels[i].setGreen(target + 0.5f);
        }
        else {
            float target = (2.0f * (((255.0f - ((float)BottomPixels[i].getGreen())) * (255.0f - (float)TopPixels[i].getGreen())) / 255.0f));
            if (target > 255.0f) {
                target = 255.0f;
            }
            NewPixels[i].setGreen(255.0f - target + 0.5f);
        }

        if ((float)BottomPixels[i].getRed() / 255.0f <= 0.5) {
            float target = (2.0f * (float)BottomPixels[i].getRed() * (float)TopPixels[i].getRed() / 255.0f);
            if (target > 255.0f) {
                target = 255.0f;
            }
            NewPixels[i].setRed(target + 0.5f);
        }
        else {
            float target = (2.0f * (((255.0f - ((float)BottomPixels[i].getRed())) * (255.0f - (float)TopPixels[i].getRed())) / 255.0f));
            if (target > 255.0f) {
                target = 255.0f;
            }
            NewPixels[i].setRed(255.0f - target + 0.5f);
        }
    }

    return *New;
}

Image& Blend::Rotate(const Image& Original) {
    Pixel* Pixels = Original.getPixels();
    Image* New = new Image(Original);
    Pixel* NewPixels = New->getPixels();
    for (unsigned int i = 0; i < Original.getSize(); i++) {
        NewPixels[i].setBlue(Pixels[Original.getSize() - i - 1].getBlue());
        NewPixels[i].setGreen(Pixels[Original.getSize() - i - 1].getGreen());
        NewPixels[i].setRed(Pixels[Original.getSize() - i - 1].getRed());
    }
    return *New;
}

Image& Blend::ExtraCredit(const Image& BotLeft, const Image& BotRight, const Image& TopLeft, const Image& TopRight) {
    Image* New = new Image(BotLeft);
    unsigned short imageWidth = BotLeft.GetWidth() + BotRight.GetWidth();
    unsigned short imageHeight = BotLeft.GetHeight() + TopLeft.GetHeight();
    New->SetWidthHeight(imageWidth, imageHeight);
    unsigned int size = imageHeight * imageWidth;
    New->setSize(size);
    New->setPixels(new Pixel[size]);

    Pixel* NewPixels = New->getPixels();
    Pixel* BotLeftPixels = BotLeft.getPixels();
    Pixel* BotRightPixels = BotRight.getPixels();
    Pixel* TopLeftPixels = TopLeft.getPixels();
    Pixel* TopRightPixels = TopRight.getPixels();

    unsigned int BotLeftIndex = 0;
    unsigned int BotRightIndex = 0;
    unsigned int TopLeftIndex = 0;
    unsigned int TopRightIndex = 0;

    for (unsigned int i = 0; i < size; i++) {
        if (i % imageWidth < BotLeft.GetWidth() && i / imageWidth < BotLeft.GetHeight()) {
            NewPixels[i].setBlue(BotLeftPixels[BotLeftIndex].getBlue());
            NewPixels[i].setGreen(BotLeftPixels[BotLeftIndex].getGreen());
            NewPixels[i].setRed(BotLeftPixels[BotLeftIndex].getRed());
            BotLeftIndex++;
        }
        else if (i % imageWidth >= BotRight.GetWidth() && i / imageWidth < BotRight.GetHeight()){
            NewPixels[i].setBlue(BotRightPixels[BotRightIndex].getBlue());
            NewPixels[i].setGreen(BotRightPixels[BotRightIndex].getGreen());
            NewPixels[i].setRed(BotRightPixels[BotRightIndex].getRed());
            BotRightIndex++;
        }
        else if (i % imageWidth < TopLeft.GetWidth() && i / imageWidth >= TopLeft.GetHeight()) {
            NewPixels[i].setBlue(TopLeftPixels[TopLeftIndex].getBlue());
            NewPixels[i].setGreen(TopLeftPixels[TopLeftIndex].getGreen());
            NewPixels[i].setRed(TopLeftPixels[TopLeftIndex].getRed());
            TopLeftIndex++;
        }
        else if (i % imageWidth >= TopLeft.GetWidth() && i / imageWidth >= TopLeft.GetHeight()){
            NewPixels[i].setBlue(TopRightPixels[TopRightIndex].getBlue());
            NewPixels[i].setGreen(TopRightPixels[TopRightIndex].getGreen());
            NewPixels[i].setRed(TopRightPixels[TopRightIndex].getRed());
            TopRightIndex++;
        }
        else {
            cout << "Error: Could not determine location in extra credit." << endl;
        }
    }

    return *New;
}

void Blend::AdjustBlue(const Image& Image, unsigned char value, unsigned int i, bool add) {
    Pixel* Pixels = Image.getPixels();
    int target;
    if (add) {
        target = Pixels[i].getBlue() + value;
    }
    else {
        target = Pixels[i].getBlue() - value;
    }
    if (target > 255) {
        Pixels[i].setBlue(255);
    }
    else if (target < 0){
        Pixels[i].setBlue(0);
    }
    else {
        Pixels[i].setBlue(target);
    }
}

void Blend::AdjustGreen(const Image& Image, unsigned char value, unsigned int i, bool add) {
    Pixel* Pixels = Image.getPixels();
    int target;
    if (add) {
        target = Pixels[i].getGreen() + value;
    }
    else {
        target = Pixels[i].getGreen() - value;
    }
    if (target > 255) {
        Pixels[i].setGreen(255);
    }
    else if (target < 0){
        Pixels[i].setGreen(0);
    }
    else {
        Pixels[i].setGreen(target);
    }
}

void Blend::AdjustRed(const Image& Image, unsigned char value, unsigned int i, bool add) {
    Pixel* Pixels = Image.getPixels();
    int target;
    if (add) {
        target = Pixels[i].getRed() + value;
    }
    else {
        target = Pixels[i].getRed() - value;
    }
    if (target > 255) {
        Pixels[i].setRed(255);
    }
    else if (target < 0){
        Pixels[i].setRed(0);
    }
    else {
        Pixels[i].setRed(target);
    }
}

void Blend::ScaleBlue(const Image& Image, float value) {
    Pixel* Pixels = Image.getPixels();
    for (unsigned int i = 0; i < Image.getSize(); i++) {
        float target = (float) Pixels[i].getBlue() * value + 0.5f;
        if (target > 255) {
            Pixels[i].setBlue(255);
        } else {
            Pixels[i].setBlue(target);
        }
    }
}

void Blend::ScaleGreen(const Image& Image, float value) {
    Pixel* Pixels = Image.getPixels();
    for (unsigned int i = 0; i < Image.getSize(); i++) {
        float target = (float) Pixels[i].getGreen() * value + 0.5f;
        if (target > 255) {
            Pixels[i].setGreen(255);
        } else {
            Pixels[i].setGreen(target);
        }
    }
}

void Blend::ScaleRed(const Image&Image, float value) {
    Pixel* Pixels = Image.getPixels();
    for (unsigned int i = 0; i < Image.getSize(); i++) {
        float target = (float) Pixels[i].getRed() * value + 0.5f;
        if (target > 255) {
            Pixels[i].setRed(255);
        } else {
            Pixels[i].setRed(target);
        }
    }
}

bool Blend::Evaluate(const Image& Example, const Image& Output, int num) {
    bool test = true;
    if (Example.getSize() != Output.getSize()) {
        test = false;
    }
    for (unsigned int i = 0; i < Example.getSize(); i++) {
        if (Example.getPixels()[i].getRed() != Output.getPixels()[i].getRed()) {
            test = false;
        }
        if (Example.getPixels()[i].getGreen() != Output.getPixels()[i].getGreen()) {
            test = false;
        }
        if (Example.getPixels()[i].getBlue() != Output.getPixels()[i].getBlue()) {
            test = false;
        }
    }
    cout << "Test " << num << ": ";
    if (test) {
        cout << "Passed!" << endl;
        return true;
    }
    else {
        cout << "Failed!" << endl;
        return false;
    }
}

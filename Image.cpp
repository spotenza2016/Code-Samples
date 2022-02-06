#include "Image.h"
#include <fstream>
#include <iostream>

Image::Image(const string& FileName) {
    ifstream File(FileName, ios_base::binary);
    if (File.is_open()) {
        IDLength = 0;
        colorMapType = 0;
        imageType = 0;
        colorMapOrigin = 0;
        colorMapLength = 0;
        colorMapDepth = 0;
        XOrigin = 0;
        YOrigin = 0;
        imageWidth = 0;
        imageHeight = 0;
        pixelDepth = 0;
        imageDescriptor = 0;

        File.read((char *) &IDLength, sizeof(IDLength));
        File.read((char *) &colorMapType, sizeof(colorMapType));
        File.read((char *) &imageType, sizeof(imageType));
        File.read((char *) &colorMapOrigin, sizeof(colorMapOrigin));
        File.read((char *) &colorMapLength, sizeof(colorMapLength));
        File.read((char *) &colorMapDepth, sizeof(colorMapDepth));
        File.read((char *) &XOrigin, sizeof(XOrigin));
        File.read((char *) &YOrigin, sizeof(YOrigin));
        File.read((char *) &imageWidth, sizeof(imageWidth));
        File.read((char *) &imageHeight, sizeof(imageHeight));
        File.read((char *) &pixelDepth, sizeof(pixelDepth));
        File.read((char *) &imageDescriptor, sizeof(imageDescriptor));

        size = imageHeight * imageWidth;
        Pixels = new Pixel[size];

        for (unsigned int i = 0; i < size; i++) {
            unsigned char data;
            Pixels[i] = Pixel();

            File.read((char *) &data, sizeof(data));
            Pixels[i].setBlue(data);

            File.read((char *) &data, sizeof(data));
            Pixels[i].setGreen(data);

            File.read((char *) &data, sizeof(data));
            Pixels[i].setRed(data);
        }

        File.close();
    }
    else {
        cout << FileName << "could not be opened." << endl;
    }
}

Image::Image(const Image& rhs) {
    IDLength = rhs.IDLength;
    colorMapType = rhs.colorMapType;
    imageType = rhs.imageType;
    colorMapOrigin = rhs.colorMapOrigin;
    colorMapLength = rhs.colorMapLength;
    colorMapDepth = rhs.colorMapDepth;
    XOrigin = rhs.XOrigin;
    YOrigin = rhs.YOrigin;
    imageWidth = rhs.imageWidth;
    imageHeight = rhs.imageHeight;
    pixelDepth = rhs.pixelDepth;
    imageDescriptor = rhs.imageDescriptor;
    size = rhs.size;
    Pixels = new Pixel[size];
    for (unsigned int i = 0; i < size; i++) {
        Pixels[i] = rhs.Pixels[i];
    }
}

Image& Image::operator=(const Image& rhs) {
    delete[] Pixels;
    IDLength = rhs.IDLength;
    colorMapType = rhs.colorMapType;
    imageType = rhs.imageType;
    colorMapOrigin = rhs.colorMapOrigin;
    colorMapLength = rhs.colorMapLength;
    colorMapDepth = rhs.colorMapDepth;
    XOrigin = rhs.XOrigin;
    YOrigin = rhs.YOrigin;
    imageWidth = rhs.imageWidth;
    imageHeight = rhs.imageHeight;
    pixelDepth = rhs.pixelDepth;
    imageDescriptor = rhs.imageDescriptor;
    size = rhs.size;
    Pixels = new Pixel[size];
    for (unsigned int i = 0; i < size; i++) {
        Pixels[i] = rhs.Pixels[i];
    }
    return *this;
}

Image::~Image() {
    delete[] Pixels;
}

void Image::writeImage(const string& FileName) {
    ofstream File(FileName, ios_base::binary);

    File.write((char *)&IDLength, sizeof(IDLength));
    File.write((char *)&colorMapType, sizeof(colorMapType));
    File.write((char *)&imageType, sizeof(imageType));
    File.write((char *)&colorMapOrigin, sizeof(colorMapOrigin));
    File.write((char *)&colorMapLength, sizeof(colorMapLength));
    File.write((char *)&colorMapDepth, sizeof(colorMapDepth));
    File.write((char *)&XOrigin, sizeof(XOrigin));
    File.write((char *)&YOrigin, sizeof(YOrigin));
    File.write((char *)&imageWidth, sizeof(imageWidth));
    File.write((char *)&imageHeight, sizeof(imageHeight));
    File.write((char *)&pixelDepth, sizeof(pixelDepth));
    File.write((char *)&imageDescriptor, sizeof(imageDescriptor));

    for (unsigned int i = 0; i < size; i++) {
        unsigned char data;

        data = Pixels[i].getBlue();
        File.write((char *)&data, sizeof(data));

        data = Pixels[i].getGreen();
        File.write((char *)&data, sizeof(data));

        data = Pixels[i].getRed();
        File.write((char *)&data, sizeof(data));
    }

    File.close();
}

unsigned int Image::getSize() const {
    return size;
}

void Image::setSize(unsigned int size) {
    this->size = size;
}

Pixel* Image::getPixels() const {
    return Pixels;
}

void Image::PrintAll() const {
    cout << "ID Length: " << IDLength << endl;
    cout << "Color Map Type: " << colorMapType << endl;
    cout << "Image Type: " << imageType << endl;
    cout << "Color Map Origin: " << colorMapOrigin << endl;
    cout << "Color Map Length: " << colorMapLength << endl;
    cout << "Color Map Depth: " << colorMapDepth << endl;
    cout << "X-Origin: " << XOrigin << endl;
    cout << "Y-Origin: " << YOrigin << endl;
    cout << "Image Width: " << imageWidth << endl;
    cout << "Image Height: " << imageHeight << endl;
    cout << "Pixel Depth: " << pixelDepth << endl;
    cout << "Image Descriptor: " << imageDescriptor << endl;
}

void Image::SetWidthHeight(unsigned short imageWidth, unsigned short imageHeight) {
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;
    size = imageWidth * imageHeight;
}

unsigned short Image::GetWidth() const {
    return imageWidth;
}

unsigned short Image::GetHeight() const {
    return imageHeight;
}

void Image::setPixels(Pixel* Pixels) {
    delete[] this->Pixels;
    this->Pixels = Pixels;
}
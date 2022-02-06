#pragma once
#include "Image.h"
using namespace std;

class Blend {
public:
    static Image& Multiply(const Image& Top, const Image& Bottom);
    static Image& Subtract(const Image& Top, const Image& Bottom);
    static Image& Screen(const Image& Top, const Image& Bottom);
    static Image& Overlay(const Image& Top, const Image& Bottom);
    static Image& Rotate(const Image& Image);
    static Image& ExtraCredit(const Image& BotLeft, const Image& BotRight, const Image& TopLeft, const Image& TopRight);
    static void AdjustBlue(const Image& Image, unsigned char value, unsigned int i, bool add);
    static void AdjustGreen(const Image& Image, unsigned char value, unsigned int i, bool add);
    static void AdjustRed(const Image& Image, unsigned char value, unsigned int i, bool add);
    static void ScaleBlue(const Image& Image, float value);
    static void ScaleGreen(const Image& Image, float value);
    static void ScaleRed(const Image& Image, float value);
    static bool Evaluate(const Image& Example, const Image& Output, int num);
};
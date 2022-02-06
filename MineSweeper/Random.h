#pragma once
#include <random>
#include <ctime>
using namespace std;

struct Random {
    static mt19937 random;
    static int RandomNum(int max);
};

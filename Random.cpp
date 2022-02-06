#include "Random.h"
mt19937 Random::random(time(0));

int Random::RandomNum(int max) {
    uniform_int_distribution<int> dist(0, max);
    return dist(random);
}
#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

struct Boat {
    unsigned int cannibals;
    unsigned int missionaries;
    Boat(unsigned int c, unsigned int m) : missionaries(m), cannibals(c) {}
};

struct Combination {
    unsigned int cannibals;
    unsigned int missionaries;
    Combination* parent;
    Combination(unsigned int c, unsigned int m, Combination* p) : cannibals(c), missionaries(m), parent(p) {}
};

struct Level {
    unsigned int level;
    std::list<Combination*> combinations;
    Level(unsigned int l) : level(l) {}
};
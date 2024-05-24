#ifndef BILET_NORMAL_H
#define BILET_NORMAL_H

#include "Bilet_Template.h"

template <typename T = int>
class Bilet_Normal : public Bilet_Template<T> {
public:
    Bilet_Normal(int rand, int coloana) : Bilet_Template<T>(rand, coloana) {};
    Bilet_Normal() : Bilet_Template<T>(0, 0) {};
    ~Bilet_Normal() override = default;
};

#endif
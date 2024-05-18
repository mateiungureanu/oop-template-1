#include "Bilet_Normal.h"

#include <iomanip>

Bilet_Normal::Bilet_Normal(int rand, int coloana) : Bilet_Template<int>(rand, coloana) {}

Bilet_Normal::Bilet_Normal() : Bilet_Template<int>(0, 0) {}

std::string
Bilet_Normal::getType() const
{
    return "Normal";
}
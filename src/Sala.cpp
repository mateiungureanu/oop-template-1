#include "Sala.h"

Sala::Sala() : id(0), nrLocuri(0), nrRanduri(0), nrColoane(0), locuriOcupate() {}

Sala &Sala::operator=(const Sala &other)
{
    if (this != &other)
    {
        id = other.id;
        nrLocuri = other.nrLocuri;
        nrRanduri = other.nrRanduri;
        nrColoane = other.nrColoane;
        locuriOcupate = other.locuriOcupate;
    }
    return *this;
}

// cppcheck-suppress unusedFunction
void Sala::setIdSala(int id1)
{
    this->id = id1;
}

void Sala::setLocuriOcupate(int nrLocuri1, const std::vector<bool> &locuriOcupate1)
{
    this->nrLocuri = nrLocuri1;
    this->locuriOcupate = locuriOcupate1;
}

// cppcheck-suppress unusedFunction
int Sala::getIdSala() const
{
    return id;
}

// cppcheck-suppress unusedFunction
int Sala::getNrLocuri() const
{
    return nrLocuri;
}

// cppcheck-suppress unusedFunction
int Sala::getNrRanduri() const
{
    return nrRanduri;
}

// cppcheck-suppress unusedFunction
int Sala::getNrColoane() const
{
    return nrColoane;
}

std::vector<bool> Sala::getLocuriOcupate() const
{
    return locuriOcupate;
}

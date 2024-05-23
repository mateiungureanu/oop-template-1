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

void Sala::setIdSala(int id1)
{
    this->id = id1;
}

void Sala::setLocuriOcupate(int nrLocuri1, const std::vector<bool> &locuriOcupate1)
{
    this->nrLocuri = nrLocuri1;
    this->locuriOcupate = locuriOcupate1;
}

int Sala::getIdSala() const
{
    return id;
}

int Sala::getNrLocuri() const
{
    return nrLocuri;
}

int Sala::getNrRanduri() const
{
    return nrRanduri;
}

int Sala::getNrColoane() const
{
    return nrColoane;
}

std::vector<bool> Sala::getLocuriOcupate() const
{
    return locuriOcupate;
}

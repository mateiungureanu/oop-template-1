#include "Sala.h"

Sala::Sala(int id)
{
    this->id = id;
    this->nrLocuri = 63;
    this->nrRanduri = 9;
    this->nrColoane = 7;
    locuriOcupate = new bool[nrLocuri];
    for (int i = 0; i < nrLocuri; i++)
    {
        locuriOcupate[i] = false;
    }
}

Sala::Sala()
{
    this->id = 0;
    this->nrLocuri = 0;
    this->nrRanduri = 0;
    this->nrColoane = 0;
    locuriOcupate = nullptr;
}

Sala::~Sala()
{
    delete[] locuriOcupate;
    locuriOcupate = nullptr;
}

Sala::Sala(const Sala &other)
{
    id = other.id;
    nrLocuri = other.nrLocuri;
    nrRanduri = other.nrRanduri;
    nrColoane = other.nrColoane;
    locuriOcupate = new bool[nrLocuri];
    for (int i = 0; i < nrLocuri; i++)
    {
        locuriOcupate[i] = other.locuriOcupate[i];
    }
}

Sala &
Sala::operator=(const Sala &other)
{
    if (this != &other)
    {
        delete[] locuriOcupate;
        id = other.id;
        nrLocuri = other.nrLocuri;
        nrRanduri = other.nrRanduri;
        nrColoane = other.nrColoane;
        locuriOcupate = new bool[other.nrLocuri];
        for (int i = 0; i < other.nrLocuri; i++)
        {
            locuriOcupate[i] = other.locuriOcupate[i];
        }
    }
    return *this;
}

/// function is never used
// cppcheck-suppress unusedFunction
void
Sala::setIdSala(int id1)
{
    this->id = id1;
}

/// function is never used
// cppcheck-suppress unusedFunction
void
Sala::setLocuriOcupate(int nrLocuri1, const bool *locuriOcupate1)
{
    this->nrLocuri = nrLocuri1;
    delete[] this->locuriOcupate;
    this->locuriOcupate = new bool[nrLocuri];
    for (int i = 0; i < nrLocuri; i++)
    {
        this->locuriOcupate[i] = locuriOcupate1[i];
    }
}

/// function is never used
// cppcheck-suppress unusedFunction
[[nodiscard]] int
Sala::getIdSala() const
{
    return id;
}

/// function is never used
// cppcheck-suppress unusedFunction
[[nodiscard]] int
Sala::getNrLocuri() const
{
    return nrLocuri;
}

/// function is never used
// cppcheck-suppress unusedFunction
[[nodiscard]] int
Sala::getNrRanduri() const
{
    return nrRanduri;
}

/// function is never used
// cppcheck-suppress unusedFunction
[[nodiscard]] int
Sala::getNrColoane() const
{
    return nrColoane;
}

[[nodiscard]] bool *
Sala::getLocuriOcupate() const
{
    return locuriOcupate;
}
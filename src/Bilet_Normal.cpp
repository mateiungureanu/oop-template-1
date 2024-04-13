#include "Bilet_Normal.h"

#include <memory>

Bilet_Normal::Bilet_Normal(int rand, int coloana)
{
    this->rand = rand;
    this->coloana = coloana;
    this->pret = 25;
}

Bilet_Normal::Bilet_Normal()
{
    this->rand = 0;
    this->coloana = 0;
    this->pret = 25;
}

void
Bilet_Normal::setRand(int rand1)
{
    this->rand = rand1;
}

void
Bilet_Normal::setColoana(int coloana1)
{
    this->coloana = coloana1;
}

// cppcheck-suppress unusedFunction
void
Bilet_Normal::setPret(int pret1)
{
    this->pret = pret1;
}

[[nodiscard]] int
Bilet_Normal::getRand() const
{
    return rand;
}

[[nodiscard]] int
Bilet_Normal::getColoana() const
{
    return coloana;
}

[[nodiscard]] int
Bilet_Normal::getPret()
{
    return pret;
}

Bilet_Normal::Bilet_Normal(const Bilet_Normal &aux)
{
    this->rand = aux.rand;
    this->coloana = aux.coloana;
    this->pret = aux.pret;
}

Bilet_Normal &
Bilet_Normal::operator=(const Bilet_Normal &aux)
{
    if (this == &aux)
    {
        return *this;
    }
    this->rand = aux.rand;
    this->coloana = aux.coloana;
    this->pret = aux.pret;
    return *this;
}

void
Bilet_Normal::afiseaza()
{
    std::cout << "Bilet Normal | Rand: " << rand << ", Loc: " << coloana << " | Pret: " << pret;
}

std::string
Bilet_Normal::getType()
{
    return "Normal";
}

std::unique_ptr<Bilet_Normal>
Bilet_Normal::downgradeBilet(int rand1, int coloana1)
{
    return std::make_unique<Bilet_Normal>(rand1, coloana1);
}
#include "Bilet_Normal.h"

#include <memory>
#include <iomanip>

Bilet_Normal::Bilet_Normal(int rand, int coloana)
{
    this->rand = rand;
    this->coloana = coloana;
}

Bilet_Normal::Bilet_Normal()
{
    this->rand = 0;
    this->coloana = 0;
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
    return *this;
}

void
Bilet_Normal::afiseaza()
{
    std::cout << "Bilet " << std::setw(6) << std::left << getType() << " | Rand: " << rand << ", Loc: " << coloana << " | Pret: " << getPret();}

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
#include "Bilet_4Dx.h"

#include <memory>

Bilet_4Dx::Bilet_4Dx(int rand, int coloana, bool scaunMiscator, bool scaunSuflator) : Bilet_Normal(rand, coloana),
                                                                                      scaunMiscator(scaunMiscator),
                                                                                      scaunSuflator(scaunSuflator),
                                                                                      pret4Dx(45) {}

Bilet_4Dx::Bilet_4Dx(int rand, int coloana) : Bilet_Normal(rand, coloana),
                                                      scaunMiscator(true),
                                                      scaunSuflator(true),
                                                      pret4Dx(45) {}

Bilet_4Dx::Bilet_4Dx() : Bilet_Normal(), scaunMiscator(true), scaunSuflator(true), pret4Dx(45) {}

void
Bilet_4Dx::setScaunMiscator(int scaunMiscator1)
{
    this->scaunMiscator = scaunMiscator1;
}

void
Bilet_4Dx::setScaunSuflator(int scaunSuflator1)
{
    this->scaunSuflator = scaunSuflator1;
}

void
Bilet_4Dx::setPret4Dx(int pret4Dx1)
{
    this->pret4Dx = pret4Dx1;
}

[[nodiscard]] int
Bilet_4Dx::getScaunMiscator() const
{
    return scaunMiscator;
}

[[nodiscard]] int
Bilet_4Dx::getScaunSuflator() const
{
    return scaunSuflator;
}

[[nodiscard]] int
Bilet_4Dx::getPret()
{
    return pret4Dx;
}

Bilet_4Dx::Bilet_4Dx(const Bilet_4Dx &aux) : Bilet_Normal(aux)
{
    this->pret4Dx = aux.pret4Dx;
    this->scaunMiscator = aux.scaunMiscator;
    this->scaunSuflator = aux.scaunSuflator;
}

Bilet_4Dx &
Bilet_4Dx::operator=(const Bilet_4Dx &aux)
{
    if (this == &aux)
    {
        return *this;
    }
    Bilet_Normal::operator=(aux);
    this->pret4Dx = aux.pret4Dx;
    this->scaunMiscator = aux.scaunMiscator;
    this->scaunSuflator = aux.scaunSuflator;
    return *this;
}

void
Bilet_4Dx::functieUpCast()
{
    Bilet_Normal *basePtr = this;
    std::cout << "Rand: " << basePtr->getRand() << ", Coloana: " << basePtr->getColoana() << std::endl;
}

void
Bilet_4Dx::afiseaza()
{
    std::cout << "Bilet 4Dx    | Rand: " << rand << ", Loc: " << coloana << " | Pret: " << pret4Dx
              << " | Bonus-uri 4Dx:";
    if (scaunMiscator)
    {
        std::cout << " scaun_miscator";
    }
    if (scaunSuflator)
    {
        std::cout << " scaun_suflator";
    }
}

[[nodiscard]] std::string
Bilet_4Dx::getType()
{
    return "4Dx";
}

std::unique_ptr<Bilet_4Dx>
Bilet_4Dx::upgradeBilet4Dx(int rand1, int coloana1)
{
    return std::make_unique<Bilet_4Dx>(rand1, coloana1);
}
#include "Bilet_VIP.h"

#include <memory>

Bilet_VIP::Bilet_VIP(int rand, int coloana, bool popcornGratis, bool bauturiGratis) : Bilet_Normal(rand, coloana),
                                                                                      popcornGratis(popcornGratis),
                                                                                      bauturiGratis(bauturiGratis),
                                                                                      pretVIP(60) {}

Bilet_VIP::Bilet_VIP(int rand, int coloana) : Bilet_Normal(rand, coloana),
                                              popcornGratis(true),
                                              bauturiGratis(true),
                                              pretVIP(60) {}

Bilet_VIP::Bilet_VIP() : Bilet_Normal(), popcornGratis(true), bauturiGratis(true), pretVIP(60) {}

void
Bilet_VIP::setPopcornGratis(bool popcornGratis1)
{
    this->popcornGratis = popcornGratis1;
}

void
Bilet_VIP::setBauturiGratis(bool bauturiGratis1)
{
    this->bauturiGratis = bauturiGratis1;
}

void
Bilet_VIP::setPretVIP(int pretVIP1)
{
    this->pretVIP = pretVIP1;
}

[[nodiscard]] bool
Bilet_VIP::getPopcornGratis() const
{
    return popcornGratis;
}

[[nodiscard]] bool
Bilet_VIP::getBauturiGratis() const
{
    return bauturiGratis;
}

[[nodiscard]] int
Bilet_VIP::getPret() const
{
    return pretVIP;
}

Bilet_VIP::Bilet_VIP(const Bilet_VIP &aux) : Bilet_Normal(aux)
{
    this->pretVIP = aux.pretVIP;
    this->popcornGratis = aux.popcornGratis;
    this->bauturiGratis = aux.bauturiGratis;
}

Bilet_VIP &
Bilet_VIP::operator=(const Bilet_VIP &aux)
{
    if (this == &aux)
    {
        return *this;
    }
    Bilet_Normal::operator=(aux);
    this->pretVIP = aux.pretVIP;
    this->popcornGratis = aux.popcornGratis;
    this->bauturiGratis = aux.bauturiGratis;
    return *this;
}

void
Bilet_VIP::afiseaza() const
{
    Bilet_Normal::afiseaza();
    std::cout << " | Pret: " << pretVIP;
    std::cout << " | Bonus-uri VIP:";
    if (popcornGratis)
    {
        std::cout << " popcorn_gratis";
    }
    if (bauturiGratis)
    {
        std::cout << " bauturi_gratis";
    }
}

[[nodiscard]] std::string
Bilet_VIP::getType() const
{
    return "VIP";
}

Bilet_VIP *
Bilet_VIP::upgradeBiletVIP(int rand1, int coloana1)
{
    return new Bilet_VIP(rand1, coloana1);
}
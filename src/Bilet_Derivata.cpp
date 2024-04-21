#include "Bilet_Derivata.h"

#include <memory>

Bilet_Derivata::Bilet_Derivata (int rand, int coloana, bool a, bool b) : Bilet_Normal(rand, coloana),
                                                                                      a(a),
                                                                                      b(b),
                                                                                      pretDerivata(80) {}

Bilet_Derivata::Bilet_Derivata(int rand, int coloana) : Bilet_Normal(rand, coloana),
                                              a(true),
                                              b(true),
                                              pretDerivata(80) {}

Bilet_Derivata::Bilet_Derivata() : Bilet_Normal(), a(true), b(true), pretDerivata(80) {}

void
Bilet_Derivata::setA(int a1)
{
    this->a = a1;
}

void
Bilet_Derivata::setB(int b1)
{
    this->b = b1;
}

void
Bilet_Derivata::setPretDerivata(int pretDerivata1)
{
    this->pretDerivata = pretDerivata1;
}

[[nodiscard]] int
Bilet_Derivata::getA() const
{
    return a;
}

[[nodiscard]] int
Bilet_Derivata::getB() const
{
    return b;
}

[[nodiscard]] int
Bilet_Derivata::getPret()
{
    return pretDerivata;
}

Bilet_Derivata::Bilet_Derivata(const Bilet_Derivata &aux) : Bilet_Normal(aux)
{
    this->pretDerivata = aux.pretDerivata;
    this->a = aux.a;
    this->b = aux.b;
}

Bilet_Derivata &
Bilet_Derivata::operator=(const Bilet_Derivata &aux)
{
    if (this == &aux)
    {
        return *this;
    }
    Bilet_Normal::operator=(aux);
    this->pretDerivata = aux.pretDerivata;
    this->a = aux.a;
    this->b = aux.b;
    return *this;
}

void
Bilet_Derivata::afiseaza()
{
    Bilet_Normal::afiseaza();
    std::cout << " | Bonus-uri Derivata:";
    if (a)
    {
        std::cout << " a";
    }
    if (b)
    {
        std::cout << " b";
    }
}

[[nodiscard]] std::string
Bilet_Derivata::getType()
{
    return "Derivata";
}

Bilet_Derivata *
Bilet_Derivata::upgradeBiletDerivata(int rand1, int coloana1)
{
    return new Bilet_Derivata(rand1, coloana1);
}

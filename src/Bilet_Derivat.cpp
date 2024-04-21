#include "Bilet_Derivat.h"

#include <memory>

Bilet_Derivat::Bilet_Derivat (int rand, int coloana, bool a, bool b) : Bilet_Normal(rand, coloana),
                                                                                      a(a),
                                                                                      b(b),
                                                                                      pretDerivat(80) {}

Bilet_Derivat::Bilet_Derivat(int rand, int coloana) : Bilet_Normal(rand, coloana),
                                              a(true),
                                              b(true),
                                              pretDerivat(80) {}

Bilet_Derivat::Bilet_Derivat() : Bilet_Normal(), a(true), b(true), pretDerivat(80) {}

void
Bilet_Derivat::setA(int a1)
{
    this->a = a1;
}

void
Bilet_Derivat::setB(int b1)
{
    this->b = b1;
}

void
Bilet_Derivat::setPretDerivat(int pretDerivat1)
{
    this->pretDerivat = pretDerivat1;
}

[[nodiscard]] int
Bilet_Derivat::getA() const
{
    return a;
}

[[nodiscard]] int
Bilet_Derivat::getB() const
{
    return b;
}

[[nodiscard]] int
Bilet_Derivat::getPret()
{
    return pretDerivat;
}

Bilet_Derivat::Bilet_Derivat(const Bilet_Derivat &aux) : Bilet_Normal(aux)
{
    this->pretDerivat = aux.pretDerivat;
    this->a = aux.a;
    this->b = aux.b;
}

Bilet_Derivat &
Bilet_Derivat::operator=(const Bilet_Derivat &aux)
{
    if (this == &aux)
    {
        return *this;
    }
    Bilet_Normal::operator=(aux);
    this->pretDerivat = aux.pretDerivat;
    this->a = aux.a;
    this->b = aux.b;
    return *this;
}

void
Bilet_Derivat::afiseaza()
{
    Bilet_Normal::afiseaza();
    std::cout << " | Bonus-uri Derivat:";
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
Bilet_Derivat::getType()
{
    return "Derivat";
}

Bilet_Derivat *
Bilet_Derivat::upgradeBiletDerivat(int rand1, int coloana1)
{
    return new Bilet_Derivat(rand1, coloana1);
}

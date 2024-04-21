#ifndef BILET_DERIVATA_H
#define BILET_DERIVATA_H

#include <string>
#include <iostream>
#include <memory>
#include "Bilet_Normal.h"

class Bilet_Derivata : public Bilet_Normal
{
private:
    bool a;
    bool b;
    int pretDerivata;
public:
    Bilet_Derivata(int rand, int coloana, bool a, bool b);

    explicit Bilet_Derivata(int rand, int coloana);

    Bilet_Derivata();

    ~Bilet_Derivata() override = default;

    void
    setA(int a1);

    void
    setB(int b1);

    void
    setPretDerivata(int pretDerivata1);

    [[nodiscard]] int
    getA() const;

    [[nodiscard]] int
    getB() const;

    [[nodiscard]] int
    getPret() override;

    Bilet_Derivata(const Bilet_Derivata &aux);

    Bilet_Derivata &
    operator=(const Bilet_Derivata &aux);

    void
    afiseaza() override;

    [[nodiscard]] std::string
    getType() override;

    static Bilet_Derivata *
    upgradeBiletDerivata(int rand1, int coloana1);
};

#endif

#ifndef BILET_DERIVAT_H
#define BILET_DERIVAT_H

#include <string>
#include <iostream>
#include <memory>
#include "Bilet_Normal.h"

class Bilet_Derivat : public Bilet_Normal
{
private:
    bool a;
    bool b;
    int pretDerivat;
public:
    Bilet_Derivat(int rand, int coloana, bool a, bool b);

    explicit Bilet_Derivat(int rand, int coloana);

    Bilet_Derivat();

    ~Bilet_Derivat() override = default;

    void
    setA(int a1);

    void
    setB(int b1);

    void
    setPretDerivat(int pretDerivat1);

    [[nodiscard]] int
    getA() const;

    [[nodiscard]] int
    getB() const;

    [[nodiscard]] int
    getPret() override;

    Bilet_Derivat(const Bilet_Derivat &aux);

    Bilet_Derivat &
    operator=(const Bilet_Derivat &aux);

    void
    afiseaza() override;

    [[nodiscard]] std::string
    getType() override;

    static Bilet_Derivat *
    upgradeBiletDerivat(int rand1, int coloana1);
};

#endif

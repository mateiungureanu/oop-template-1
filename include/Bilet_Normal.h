#ifndef BILET_NORMAL_H
#define BILET_NORMAL_H

#include <string>
#include <iostream>
#include <memory>

class Bilet_Normal
{
protected:
    int rand;
    int coloana;
    const int pret = 25;
public:
    Bilet_Normal(int rand, int coloana);

    Bilet_Normal();

    virtual ~Bilet_Normal() = default;

    void
    setRand(int rand1);

    void
    setColoana(int coloana1);

    [[nodiscard]] int
    getRand() const;

    [[nodiscard]] int
    getColoana() const;

    [[nodiscard]] virtual int
    getPret();

    Bilet_Normal(const Bilet_Normal &aux);

    Bilet_Normal &
    operator=(const Bilet_Normal &aux);

    virtual void
    afiseaza();

    virtual std::string
    getType();

    static std::unique_ptr<Bilet_Normal>
    downgradeBilet(int rand, int coloana);
};

#endif
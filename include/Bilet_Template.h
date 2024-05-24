#ifndef BILET_TEMPLATE_H
#define BILET_TEMPLATE_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Bilet.h"

template<typename T>
class Bilet_Template : public Bilet
{
private:
    int rand;
    int coloana;
    T pret;

public:
    Bilet_Template(int rand, int coloana)
        : rand(rand), coloana(coloana), pret(25) {}

    Bilet_Template()
        : rand(0), coloana(0), pret(25) {}

    ~Bilet_Template() override = default;

    void
    setRand(int rand1) { this->rand = rand1; }
    void
    setColoana(int coloana1) { this->coloana = coloana1; }
    void
    setPret(T pret1) { this->pret = pret1; }

    [[nodiscard]] int
    getRand() const { return rand; }
    [[nodiscard]] int
    getColoana() const { return coloana; }
    virtual T
    getPret() const { return pret; }

    virtual void
    afiseaza() const
    {
        std::cout << "Bilet " << std::setw(6) << std::left << getType() << " | Rand: " << rand << ", Loc: " << coloana;
        if (getType() == "Normal")
        {
            std::cout << " | Pret: " << pret;
        }
    }
    [[nodiscard]] std::string getType() const override
    {
        return "Normal";
    }
    static Bilet_Template<T> *
    downgradeBilet(int rand1, int coloana1)
    {
        return new Bilet_Template<T>(rand1, coloana1);
    }
};

#endif

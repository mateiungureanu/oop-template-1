#ifndef BILET_VIP_H
#define BILET_VIP_H

#include <string>
#include <iostream>
#include <memory>
#include "Bilet_Normal.h"

class Bilet_VIP : public Bilet_Normal<>
{
private:
    bool popcornGratis;
    bool bauturiGratis;
    int pretVIP;
public:
    Bilet_VIP(int rand, int coloana, bool popcornGratis, bool bauturiGratis);

    explicit Bilet_VIP(int rand, int coloana); // = 0, = 0, nu mai stiu pentru ce erau dar merge si fara aparent

    Bilet_VIP();

    ~Bilet_VIP() override = default;

    void
    setPopcornGratis(bool popcornGratis1);

    void
    setBauturiGratis(bool bauturiGratis1);

    void
    setPretVIP(int pretVIP1);

    [[nodiscard]] bool
    getPopcornGratis() const;

    [[nodiscard]] bool
    getBauturiGratis() const;

    [[nodiscard]] int
    getPret() const override;

    Bilet_VIP(const Bilet_VIP &aux);

    Bilet_VIP &
    operator=(const Bilet_VIP &aux);

    void
    afiseaza() const override;

    [[nodiscard]] std::string
    getType() const override;

    static Bilet_VIP *
    upgradeBiletVIP(int rand1, int coloana1);
};

#endif

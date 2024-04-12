#ifndef BILET_VIP_H
#define BILET_VIP_H

#include <string>
#include <iostream>
#include "Bilet_Normal.h"

class Bilet_VIP : public Bilet_Normal
{
private:
    bool popcornGratis;
    bool bauturiGratis;
    int pretVIP;
public:
    Bilet_VIP(int rand, int coloana, bool popcornGratis, bool bauturiGratis);

    explicit Bilet_VIP(int rand = 0, int coloana = 0);

    Bilet_VIP();

    ~Bilet_VIP() override = default;

    void
    setPretVIP(int pretVIP1);

    void
    setPopcornGratis(bool popcornGratis1);

    void
    setBauturiGratis(bool bauturiGratis1);

    [[nodiscard]] bool
    getPopcornGratis() const;

    [[nodiscard]] bool
    getBauturiGratis() const;

    [[nodiscard]] int
    getPret() override;

    Bilet_VIP(const Bilet_VIP &aux);

    Bilet_VIP &
    operator=(const Bilet_VIP &aux);

    void
    functieUpCast() override;

    void
    afiseaza() override;

    [[nodiscard]] std::string
    getType() override;

    static std::unique_ptr<Bilet_VIP>
    upgradeBiletVIP(int rand1, int coloana1);
};

#endif

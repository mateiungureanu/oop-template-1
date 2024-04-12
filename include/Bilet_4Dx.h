#ifndef BILET_4DX_H
#define BILET_4DX_H

#include <string>
#include <iostream>
#include "Bilet_Normal.h"

class Bilet_4Dx : public Bilet_Normal
{
private:
    bool scaunMiscator;
    bool scaunSuflator;
    int pret4Dx;
public:
    Bilet_4Dx(int rand, int coloana, bool scaunMiscator, bool scaunSuflator);

    explicit Bilet_4Dx(int rand = 0, int coloana = 0);

    Bilet_4Dx();

    ~Bilet_4Dx() override = default;

    void
    setScaunMiscator(int scaunMiscator1);

    void
    setScaunSuflator(int scaunSuflator1);

    void
    setPret4Dx(int pret4Dx1);

    [[nodiscard]] int
    getScaunMiscator() const;

    [[nodiscard]] int
    getScaunSuflator() const;

    [[nodiscard]] int
    getPret() override;

    Bilet_4Dx(const Bilet_4Dx &aux);

    Bilet_4Dx &
    operator=(const Bilet_4Dx &aux);

    void
    functieUpCast() override;

    void
    afiseaza() override;

    [[nodiscard]] std::string
    getType() override;

    static std::unique_ptr<Bilet_4Dx>
    upgradeBilet4Dx(int rand1, int coloana1);
};

#endif

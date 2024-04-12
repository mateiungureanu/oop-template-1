#ifndef SALA_H
#define SALA_H

#include <string>
#include <iostream>

class Sala
{
private:
    int id;
    int nrLocuri;
    int nrRanduri;
    int nrColoane;
    bool *locuriOcupate;
public:
    friend class Cinema;

    explicit Sala(int id);

    Sala();

    ~Sala();

    Sala(const Sala &other);

    Sala &
    operator=(const Sala &other);

    void
    setIdSala(int id1);

    void
    setLocuriOcupate(int nrLocuri1, const bool *locuriOcupate1);

    [[nodiscard]] int
    getIdSala() const;

    [[nodiscard]] bool *
    getLocuriOcupate() const;
};

#endif
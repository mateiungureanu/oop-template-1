#ifndef SALA_H
#define SALA_H

#include <string>
#include <iostream>
#include <utility>
#include <vector>

class Sala
{
private:
    int id;
    int nrLocuri;
    int nrRanduri;
    int nrColoane;
    std::vector<bool> locuriOcupate;

    friend class SalaBuilder;

public:
    friend class Cinema;
    Sala();
    ~Sala() = default;
    Sala(const Sala &other) = default;
    Sala &operator=(const Sala &other);

    void setIdSala(int id1);
    void setLocuriOcupate(int nrLocuri1, const std::vector<bool> &locuriOcupate1);

    [[nodiscard]] int getIdSala() const;
    [[nodiscard]] int getNrLocuri() const;
    [[nodiscard]] int getNrRanduri() const;
    [[nodiscard]] int getNrColoane() const;
    [[nodiscard]] std::vector<bool> getLocuriOcupate() const;
};

class SalaBuilder
{
private:
    Sala s;

public:
    SalaBuilder() = default;
    SalaBuilder &setId(int id)
    {
        s.id = id;
        return *this;
    }
    SalaBuilder &setNrLocuri(int nrLocuri)
    {
        s.nrLocuri = nrLocuri;
        return *this;
    }
    SalaBuilder &setNrRanduri(int nrRanduri)
    {
        s.nrRanduri = nrRanduri;
        return *this;
    }
    SalaBuilder &setNrColoane(int nrColoane)
    {
        s.nrColoane = nrColoane;
        return *this;
    }
    SalaBuilder &setLocuriOcupate(const std::vector<bool> &locuriOcupate)
    {
        s.locuriOcupate = locuriOcupate;
        return *this;
    }

    Sala build()
    {
        return s;
    }
};

#endif

#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <iostream>
#include "Film.h"

class Cinema
{
private:
    int id;
    std::string numeMall;
    Film *filmeDifuzate;
    int nrFilme;
public:
    Cinema(int id, std::string numeMall);

    Cinema();

    ~Cinema();

    void
    setId(int id1);

    void
    setNumeMall(std::string numeMall1);

    void
    setNrFilme(int nrFilme1);

    void
    setFilmeDifuzate(int nrFilme1, const Film *filmeDifuzate1);

    [[nodiscard]] int
    getId() const;

    [[nodiscard]] std::string
    getNumeMall() const;

    [[nodiscard]] int
    getNrFilme() const;

    [[nodiscard]] Film *
    getFilmeDifuzate() const;

    void
    adaugaFilm(const std::string &numeFilm, double rating);

    void
    stergeFilm(const std::string &numeFilm);

    void
    schimbaRating(const std::string &numeFilm, double nouRating);

    Cinema(const Cinema &aux);

    Cinema &
    operator=(const Cinema &aux);

    Cinema
    operator+(Cinema &cinema);

    friend std::istream &
    operator>>(std::istream &in, Cinema &cinema);

    friend std::ostream &
    operator<<(std::ostream &out, const Cinema &cinema);
};

#endif

#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <iostream>
#include <set>
#include "Film.h"

class Cinema
{
private:
    int id;
    std::string numeMall;
    std::set<Film> filmeDifuzate;
public:
    Cinema(int id, std::string numeMall);

    Cinema();

    ~Cinema();

    void
    setId(int id1);

    void
    setNumeMall(std::string numeMall1);

    void
    setFilmeDifuzate(const std::set<Film>& filmeDifuzate1);

    [[nodiscard]] int
    getId() const;

    [[nodiscard]] std::string
    getNumeMall() const;

    [[nodiscard]] const std::set<Film> &
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
    operator+(const Cinema &cinema);

    friend std::istream &
    operator>>(std::istream &in, Cinema &cinema);

    friend std::ostream &
    operator<<(std::ostream &out, const Cinema &cinema);
};

#endif

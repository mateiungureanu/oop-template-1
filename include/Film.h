#ifndef FILM_H
#define FILM_H

#include <string>
#include <iostream>
#include <iomanip>

class Film
{
private:
    std::string numeFilm;
    double rating;
public:
    friend class Cinema;
    Film(std::string numeFilm, double rating);
    Film();
    ~Film() = default;

    void
    setRating(double rating);
    void
    setNumeFilm(std::string numeFilm);

    [[nodiscard]] double
    getRating() const;
    [[nodiscard]] std::string
    getNumeFilm() const;

    bool
    operator==(const Film &film) const;
    Film &
    operator=(const Film &aux);
    friend std::ostream &
    operator<<(std::ostream &out, const Film &film);
    static bool
    comparaFilme(const Film &a, const Film &b);
    bool operator<(const Film& other) const;
};

#endif

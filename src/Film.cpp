#include "Film.h"

#include <utility>

Film::Film(std::string numeFilm, double rating) : numeFilm(std::move(numeFilm)), rating(rating) {}
Film::Film() : rating(0) {}

// cppcheck-suppress unusedFunction
void Film::setRating(double rating1)
{
    this->rating = rating1;
}

// cppcheck-suppress unusedFunction
void Film::setNumeFilm(std::string numeFilm1)
{
    this->numeFilm = std::move(numeFilm1);
}

// cppcheck-suppress unusedFunction
double
Film::getRating() const
{
    return rating;
}
std::string
Film::getNumeFilm() const
{
    return numeFilm;
}
Film::Film(const Film &aux)
{
    this->numeFilm = aux.numeFilm;
    this->rating = aux.rating;
}
bool
Film::operator==(const Film &film) const
{
    if (this->numeFilm == film.numeFilm and this->rating == film.rating)
        return true;
    else
        return false;
}
Film &
Film::operator=(const Film &aux)
{
    if (this == &aux)
    {
        return *this;
    }
    this->numeFilm = aux.numeFilm;
    this->rating = aux.rating;
    return *this;
}
std::ostream &
operator<<(std::ostream &out, const Film &film)
{
    out << "\nnume film: " << film.numeFilm << " (" << std::fixed << std::setprecision(1) << film.rating << ")";
    return out;
}

bool
Film::operator<(const Film &other) const
{
    return numeFilm < other.numeFilm;
}

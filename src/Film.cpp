#include "Film.h"

Film::Film(std::string numeFilm, double rating)
{
    this->numeFilm = std::move(numeFilm);
    this->rating = rating;
}
Film::Film()
{
    this->numeFilm = "";
    this->rating = 0;
}
void
Film::setRating(double rating1)
{
    this->rating = rating1;
}
void
Film::setNumeFilm(std::string numeFilm1)
{
    this->numeFilm = std::move(numeFilm1);
}
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
Film::comparaFilme(const Film &a, const Film &b)
{
    return a.numeFilm < b.numeFilm;
}

bool Film::operator<(const Film& other) const {
    return numeFilm < other.numeFilm;
}

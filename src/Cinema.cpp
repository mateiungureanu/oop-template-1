#include "Cinema.h"

#include <algorithm>

Cinema::Cinema(int id, std::string numeMall) : numeMall(std::move(numeMall))
{
    this->id = id;
    this->nrFilme = 0;
    this->filmeDifuzate = nullptr;
}

Cinema::Cinema()
{
    this->id = 0;
    this->nrFilme = 0;
    this->numeMall = "";
    this->filmeDifuzate = nullptr;
}

Cinema::~Cinema()
{
    delete[] this->filmeDifuzate;
}

void
Cinema::setId(int id1)
{
    this->id = id1;
}

void
Cinema::setNumeMall(std::string numeMall1)
{
    this->numeMall = std::move(numeMall1);
}

// cppcheck-suppress unusedFunction
void Cinema::setNrFilme(int nrFilme1)
{
    this->nrFilme = nrFilme1;
}

void
Cinema::setFilmeDifuzate(int nrFilme1, const Film *filmeDifuzate1)
{
    this->nrFilme = nrFilme1;
    delete[] this->filmeDifuzate;
    this->filmeDifuzate = new Film[nrFilme];
    for (int i = 0; i < nrFilme; i++)
    {
        this->filmeDifuzate[i] = filmeDifuzate1[i];
    }
}

[[nodiscard]] int
Cinema::getId() const
{
    return id;
}

[[nodiscard]] std::string
Cinema::getNumeMall() const
{
    return numeMall;
}

[[nodiscard]] int
Cinema::getNrFilme() const
{
    return nrFilme;
}

[[nodiscard]] Film *
Cinema::getFilmeDifuzate() const
{
    return filmeDifuzate;
}

void
Cinema::adaugaFilm(const std::string &numeFilm, const double rating)
{
    int ok = 1;
    for (int i = 0; i < nrFilme; i++)
    {
        if (filmeDifuzate[i].numeFilm == numeFilm)
        {
            ok = 0;
            break;
        }
    }
    if (ok == 0)
    {
        std::cout << "Filmul este deja in lista filmelor difuzate.\n";
    }
    else
    {
        Film *nouFilmeDifuzate = new Film[nrFilme + 1];
        for (int i = 0; i < nrFilme; i++)
        {
            nouFilmeDifuzate[i] = filmeDifuzate[i];
        }
        nouFilmeDifuzate[nrFilme] = Film(numeFilm, rating);
        nrFilme++;
        delete[] filmeDifuzate;
        filmeDifuzate = nouFilmeDifuzate;
        std::sort(filmeDifuzate, filmeDifuzate + nrFilme, Film::comparaFilme);
    }
}

void
Cinema::stergeFilm(const std::string &numeFilm)
{
    int index = -1;
    for (int i = 0; i < nrFilme; i++)
    {
        if (filmeDifuzate[i].numeFilm == numeFilm)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        Film *nouFilmeDifuzate = new Film[nrFilme - 1];
        for (int i = 0; i < index; i++)
        {
            nouFilmeDifuzate[i] = filmeDifuzate[i];
        }
        for (int i = index; i < nrFilme - 1; i++)
        {
            nouFilmeDifuzate[i] = filmeDifuzate[i + 1];
        }
        nrFilme--;
        delete[] filmeDifuzate;
        filmeDifuzate = nouFilmeDifuzate;
    }
    else
    {
        std::cout << "Filmul nu exista in lista filmelor difuzate.\n";
    }
}

void
Cinema::schimbaRating(const std::string &numeFilm, double nouRating)
{
    for (int i = 0; i < nrFilme; ++i)
    {
        if (filmeDifuzate[i].numeFilm == numeFilm)
        {
            filmeDifuzate[i].rating = nouRating;
            return;
        }
    }
    std::cout << "Filmul nu exista in lista filmelor difuzate.\n";
}

Cinema::Cinema(const Cinema &aux) : numeMall(aux.numeMall)
{
    this->id = aux.id;
    this->nrFilme = aux.nrFilme;
    filmeDifuzate = new Film[aux.nrFilme];
    for (int i = 0; i < aux.nrFilme; i++)
    {
        this->filmeDifuzate[i] = aux.filmeDifuzate[i];
    }
}

Cinema &
Cinema::operator=(const Cinema &aux)
{
    if (this == &aux)
    {
        return *this;
    }
    this->id = aux.id;
    this->numeMall = aux.numeMall;
    this->nrFilme = aux.nrFilme;
    delete[] filmeDifuzate;
    this->filmeDifuzate = new Film[nrFilme];
    for (int i = 0; i < aux.nrFilme; i++)
    {
        filmeDifuzate[i] = aux.filmeDifuzate[i];
    }
    return *this;
}

Cinema
Cinema::operator+(Cinema &cinema)
{
    if (this == &cinema)
    {
        return *this;
    }
    Cinema nouCinema;
    nouCinema.id = this->id;
    nouCinema.numeMall = this->numeMall;
    int totalFilme = this->nrFilme + cinema.nrFilme;
    nouCinema.filmeDifuzate = new Film[totalFilme];
    for (int i = 0; i < this->nrFilme; i++)
    {
        nouCinema.filmeDifuzate[i] = this->filmeDifuzate[i];
    }
    int nouFilmeCount = this->nrFilme;
    for (int i = 0; i < cinema.nrFilme; i++)
    {
        bool duplicateFound = false;
        for (int j = 0; j < nouFilmeCount; j++)
        {
            if (nouCinema.filmeDifuzate[j].getNumeFilm() == cinema.filmeDifuzate[i].getNumeFilm()
                && nouCinema.filmeDifuzate[j].getRating() == cinema.filmeDifuzate[i].getRating())
            {
                duplicateFound = true;
                break;
            }
        }
        if (!duplicateFound)
        {
            nouCinema.filmeDifuzate[nouFilmeCount++] = cinema.filmeDifuzate[i];
        }
    }
    nouCinema.nrFilme = nouFilmeCount;
    return nouCinema;
}

std::istream &
operator>>(std::istream &in, Cinema &cinema)
{
    in >> cinema.id;
    in >> cinema.numeMall;
    in >> cinema.nrFilme;
    return in;
}

std::ostream &
operator<<(std::ostream &out, const Cinema &cinema)
{
    out << "\nid: " << cinema.id << " nume mall: " << cinema.numeMall << " numar sali: " << cinema.nrFilme;
    return out;
}

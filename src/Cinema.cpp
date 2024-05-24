#include "Cinema.h"

#include <algorithm>
#include <set>

Cinema::Cinema(int id, std::string numeMall) : id(id), numeMall(std::move(numeMall)) {}

Cinema::Cinema() : id(0) {}

Cinema::~Cinema() = default;

void Cinema::setId(int id1) {
    id = id1;
}

void Cinema::setNumeMall(std::string numeMall1) {
    numeMall = std::move(numeMall1);
}

void Cinema::setFilmeDifuzate(const std::set<Film>& filmeDifuzate1) {
    filmeDifuzate = filmeDifuzate1;
}

int Cinema::getId() const {
    return id;
}

std::string Cinema::getNumeMall() const {
    return numeMall;
}

const std::set<Film>& Cinema::getFilmeDifuzate() const {
    return filmeDifuzate;
}

void Cinema::adaugaFilm(const std::string &numeFilm, double rating) {
    filmeDifuzate.insert(Film(numeFilm, rating));
}


void Cinema::stergeFilm(const std::string &numeFilm) {
    auto it = std::find_if(filmeDifuzate.begin(), filmeDifuzate.end(),
                           [&](const Film& film) { return film.getNumeFilm() == numeFilm; });
    if (it != filmeDifuzate.end()) {
        filmeDifuzate.erase(it);
        std::cout << "Filmul a fost sters cu succes.\n";
    } else {
        std::cout << "Filmul nu exista in lista filmelor difuzate.\n";
    }
}

void Cinema::schimbaRating(const std::string &numeFilm, double nouRating) {
    auto it = std::find_if(filmeDifuzate.begin(), filmeDifuzate.end(),
                           [&](const Film& film) { return film.getNumeFilm() == numeFilm; });
    if (it != filmeDifuzate.end()) {
        filmeDifuzate.erase(it);
        filmeDifuzate.insert(Film(numeFilm, nouRating));
        std::cout << "Rating-ul filmului a fost modificat cu succes.\n";
    } else {
        std::cout << "Filmul nu exista in lista filmelor difuzate.\n";
    }
}

Cinema::Cinema(const Cinema &aux) = default;

Cinema &Cinema::operator=(const Cinema &aux) {
    if (this == &aux) {
        return *this;
    }
    id = aux.id;
    numeMall = aux.numeMall;
    filmeDifuzate = aux.filmeDifuzate;
    return *this;
}

Cinema Cinema::operator+(const Cinema &cinema) {
    Cinema nouCinema;
    nouCinema.id = id;
    nouCinema.numeMall = numeMall;
    nouCinema.filmeDifuzate = filmeDifuzate;
    nouCinema.filmeDifuzate.insert(cinema.filmeDifuzate.begin(), cinema.filmeDifuzate.end());
    return nouCinema;
}

std::istream &operator>>(std::istream &in, Cinema &cinema) {
    in >> cinema.id >> cinema.numeMall;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Cinema &cinema) {
    out << "\nid: " << cinema.id << " nume mall: " << cinema.numeMall;
    return out;
}

bool
operator==(const Cinema &cinema, const Cinema &aux)
{
    if (cinema.getId() == aux.getId() and cinema.getNumeMall() == aux.getNumeMall())
    {
        return true;
    }
    else
    {
        return false;
    }
}
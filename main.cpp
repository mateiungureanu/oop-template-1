#include <iostream>
#include <array>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include <cxxabi.h>
#include "Film.h"

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

    explicit Sala(int id)
    {
        this->id = id;
        this->nrLocuri = 63;
        this->nrRanduri = 9;
        this->nrColoane = 7;
        locuriOcupate = new bool[nrLocuri];
        for (int i = 0; i < nrLocuri; i++)
        {
            locuriOcupate[i] = false;
        }
    }

    Sala()
    {
        this->id = 0;
        this->nrLocuri = 0;
        this->nrRanduri = 0;
        this->nrColoane = 0;
        locuriOcupate = nullptr;
    }

    ~Sala()
    {
        delete[] locuriOcupate;
        locuriOcupate = nullptr;
    }

    Sala(const Sala &other)
    {
        id = other.id;
        nrLocuri = other.nrLocuri;
        nrRanduri = other.nrRanduri;
        nrColoane = other.nrColoane;
        if (locuriOcupate == nullptr)
        {
            locuriOcupate = new bool[other.nrLocuri];
        }
        for (int i = 0; i < other.nrLocuri; i++)
        {
            locuriOcupate[i] = other.locuriOcupate[i];
        }
    }

    Sala &
    operator=(const Sala &other)
    {
        if (this != &other)
        {
            delete[] locuriOcupate;
            id = other.id;
            nrLocuri = other.nrLocuri;
            nrRanduri = other.nrRanduri;
            nrColoane = other.nrColoane;
            locuriOcupate = new bool[other.nrLocuri];
            for (int i = 0; i < other.nrLocuri; i++)
            {
                locuriOcupate[i] = other.locuriOcupate[i];
            }
        }
        return *this;
    }

///    function is never used
//    void setIdSala(int id1) {
//        this->id = id1;
//    }

///    function is never used
//    void setLocuriOcupate(int nrLocuri1, const bool *locuriOcupate1) {
//        this->nrLocuri = nrLocuri1;
//        delete[] this->locuriOcupate;
//        this->locuriOcupate = new bool[nrLocuri];
//        for (int i = 0; i < nrLocuri; i++) {
//            this->locuriOcupate[i] = locuriOcupate1[i];
//        }
//    }

///    function is never used
//    [[nodiscard]] int getIdSala() const {
//        return id;
//    }

    [[nodiscard]] bool *
    getLocuriOcupate() const
    {
        return locuriOcupate;
    }
};

class Cinema
{
private:
    int id;
    std::string numeMall;
    Film *filmeDifuzate;
    int nrFilme;
public:
    Cinema(int id, std::string numeMall) : numeMall(std::move(numeMall))
    {
        this->id = id;
        this->nrFilme = 0;
        this->filmeDifuzate = nullptr;
    }

    Cinema()
    {
        this->id = 0;
        this->nrFilme = 0;
        this->numeMall = '\0';
        this->filmeDifuzate = nullptr;
    }

    ~Cinema()
    {
        delete[] this->filmeDifuzate;
    }

    void
    setId(int id1)
    {
        this->id = id1;
    }

    void
    setNumeMall(std::string numeMall1)
    {
        this->numeMall = std::move(numeMall1);
    }

///    function is never used
//    void setNrFilme(int nrFilme1) {
//        this->nrFilme = nrFilme1;
//    }

    void
    setFilmeDifuzate(int nrFilme1, const Film *filmeDifuzate1)
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
    getId() const
    {
        return id;
    }

    [[nodiscard]] std::string
    getNumeMall() const
    {
        return numeMall;
    }

    [[nodiscard]] int
    getNrFilme() const
    {
        return nrFilme;
    }

    [[nodiscard]] Film *
    getFilmeDifuzate() const
    {
        return filmeDifuzate;
    }

    void
    adaugaFilm(const std::string &numeFilm, const double rating)
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
    stergeFilm(const std::string &numeFilm)
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
    schimbaRating(const std::string &numeFilm, double nouRating)
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

    Cinema(const Cinema &aux) : numeMall(aux.numeMall)
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
    operator=(const Cinema &aux)
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
    operator+(Cinema &cinema)
    {
        if (this == &cinema)
        {
            return *this;
        }
        Cinema nouCinema;
        nouCinema.id = this->id;
        nouCinema.numeMall = this->numeMall;
        nouCinema.filmeDifuzate = new Film[this->nrFilme + cinema.nrFilme];
        for (int i = 0; i < this->nrFilme; i++)
        {
            nouCinema.filmeDifuzate[i] = this->filmeDifuzate[i];
        }
        for (int i = 0; i < cinema.nrFilme; i++)
        {
            nouCinema.filmeDifuzate[i] = cinema.filmeDifuzate[i];
        }
        this->id = 0;
        this->numeMall = '\0';
        cinema.id = 0;
        cinema.numeMall = '\0';
        delete[] cinema.filmeDifuzate;
        delete[] this->filmeDifuzate;
        return nouCinema;
    }

    friend std::istream &
    operator>>(std::istream &in, Cinema &cinema)
    {
        std::cout << "\nid: ";
        in >> cinema.id;
        std::cout << "\nnume mall: ";
        in >> cinema.numeMall;
        std::cout << "\nnumar sali: ";
        in >> cinema.nrFilme;
        return in;
    }

    friend std::ostream &
    operator<<(std::ostream &out, const Cinema &cinema)
    {
        out << "\nid: " << cinema.id;
        out << "\nnume mall: " << cinema.numeMall;
        out << "\nnumar sali: " << cinema.nrFilme;
        return out;
    }
};

class Bilet
{
protected:
    int rand;
    int coloana;
public:
    friend class Cinema;

    Bilet(int rand, int coloana)
    {
        this->rand = rand;
        this->coloana = coloana;
    }

    Bilet()
    {
        this->rand = 0;
        this->coloana = 0;
    }

    virtual ~Bilet() = default;

    void
    setRand(int rand1)
    {
        this->rand = rand1;
    }

    void
    setColoana(int coloana1)
    {
        this->coloana = coloana1;
    }

    [[nodiscard]] int
    getRand() const
    {
        return rand;
    }

    [[nodiscard]] int
    getColoana() const
    {
        return coloana;
    }

    Bilet(const Bilet &aux)
    {
        this->rand = aux.rand;
        this->coloana = aux.coloana;
    }

    Bilet &
    operator=(const Bilet &aux)
    {
        if (this == &aux)
        {
            return *this;
        }
        this->rand = aux.rand;
        this->coloana = aux.coloana;
    }

/// function id never used
//    virtual void
//    functieUpCast()
//    {
//        std::cout << "A";
//    }

    virtual void
    afiseaza()
    {
        std::cout << "Bilet " << getType();
        std::cout << " | Rand: " << rand << ", Loc: " << coloana;
    }

    virtual std::string
    getType() = 0;

    virtual int
    getPret() = 0;
};

class Bilet_Normal : public Bilet
{
private:
    int pretNormal;
public:
    Bilet_Normal(int rand, int coloana) : Bilet(rand, coloana), pretNormal(25) {}

    Bilet_Normal() : Bilet(), pretNormal(25) {}

    ~Bilet_Normal() override = default;

/// function is never used
//    void
//    setPretNormal(int pretNormal1)
//    {
//        this->pretNormal = pretNormal1;
//    }

    [[nodiscard]] int
    getPret() override
    {
        return pretNormal;
    }

    Bilet_Normal(const Bilet_Normal &aux) : Bilet(aux)
    {
        this->pretNormal = aux.pretNormal;
    }

    Bilet_Normal &
    operator=(const Bilet_Normal &aux)
    {
        if (this == &aux)
        {
            return *this;
        }
        Bilet::operator=(aux);
        this->pretNormal = aux.pretNormal;
    }

/// function is never used
//    void
//    functieUpCast() override
//    {
//        Bilet* basePtr = this;
//        std::cout << "Rand: " << basePtr->getRand() << ", Coloana: " << basePtr->getColoana() << std::endl;
//    }

    void
    afiseaza() override
    {
        Bilet::afiseaza();
        std::cout << " | Pret: " << pretNormal;
    }

    [[nodiscard]] std::string
    getType() override
    {
        return "Normal";
    }

    static std::unique_ptr<Bilet_Normal>
    downgradeBilet()
    {
        return std::make_unique<Bilet_Normal>();
    }
};

class Bilet_VIP : public Bilet
{
private:
    int pretVIP;
    bool popcornGratis;
    bool bauturiGratis;
public:
    Bilet_VIP(int rand, int coloana, bool popcornGratis, bool bauturiGratis) : Bilet(rand, coloana),
                                                                               pretVIP(60),
                                                                               popcornGratis(popcornGratis),
                                                                               bauturiGratis(bauturiGratis) {}

    Bilet_VIP(int rand, int coloana) : Bilet(rand, coloana), pretVIP(60), popcornGratis(true), bauturiGratis(true) {}

    Bilet_VIP() : Bilet(), pretVIP(60), popcornGratis(true), bauturiGratis(true) {}

    ~Bilet_VIP() override = default;

/// function is never used
//    void
//    setPretVIP(int pretVIP1)
//    {
//        this->pretVIP = pretVIP1;
//    }

/// function is never used
//    void
//    setPopcornGratis(bool popcornGratis1)
//    {
//        this->popcornGratis = popcornGratis1;
//    }

/// function is never used
//    void
//    setBauturiGratis(bool bauturiGratis1)
//    {
//        this->bauturiGratis = bauturiGratis1;
//    }

    [[nodiscard]] int
    getPret() override
    {
        return pretVIP;
    }

/// function is never used
//    [[nodiscard]] bool
//    getPopcornGratis() const
//    {
//        return popcornGratis;
//    }

/// function is never used
//    [[nodiscard]] bool
//    getBauturiGratis() const
//    {
//        return bauturiGratis;
//    }

    Bilet_VIP(const Bilet_VIP &aux) : Bilet(aux)
    {
        this->pretVIP = aux.pretVIP;
        this->popcornGratis = aux.popcornGratis;
        this->bauturiGratis = aux.bauturiGratis;
    }

    Bilet_VIP &
    operator=(const Bilet_VIP &aux)
    {
        if (this == &aux)
        {
            return *this;
        }
        Bilet::operator=(aux);
        this->pretVIP = aux.pretVIP;
        this->popcornGratis = aux.popcornGratis;
        this->bauturiGratis = aux.bauturiGratis;
    }

/// function is never used
//    void
//    functieUpCast() override
//    {
//        Bilet* basePtr = this;
//        std::cout << "Rand: " << basePtr->getRand() << ", Coloana: " << basePtr->getColoana() << std::endl;
//    }

    void
    afiseaza() override
    {
        Bilet::afiseaza();
        std::cout << " | Pret: " << pretVIP;
        std::cout << " | Bonus-uri VIP: ";
        if (popcornGratis)
        {
            std::cout << "popcorn gratis ";
        }
        if (bauturiGratis)
        {
            std::cout << "bauturi gratis";
        }
    }

    static std::unique_ptr<Bilet_VIP>
    upgradeBilet()
    {
        return std::make_unique<Bilet_VIP>();
    }

    [[nodiscard]] std::string
    getType() override
    {
        return "VIP";
    }
};

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

int
main()
{
    std::istream &f = std::cin;
    int id_sala, k, loc[63], x, y, nr_bilete = 0, suma = 0, ccv;
    std::string tasta, cod_cinema, cod_film, cod_zi, cod_ora, cod_sala, cod_rand, cod_coloana, cod_beneficii, nr_card,
        nume_titular,
        data_exp;
    std::array<Cinema, 3> cinemauri{};
    cinemauri[0].setNumeMall("Afi Cotroceni");
    cinemauri[1].setNumeMall("Park Lake");
    cinemauri[2].setNumeMall("Mega Mall");
    for (int i = 0; i < 3; i++)
    {
        cinemauri[i].setId(i + 1);
    }
    Film *filme = new Film[7];
    filme[0].setNumeFilm("Dune Part 2");
    filme[1].setNumeFilm("Oppenheimer");
    filme[2].setNumeFilm("Star Wars Episode 3 Revenge of the Sith");
    filme[3].setNumeFilm("The Dark Knight");
    filme[4].setNumeFilm("The Lord of the Rings The Two Towers");
    filme[5].setNumeFilm("The Martian");
    filme[6].setNumeFilm("The Matrix");
    filme[0].setRating(8.8);
    filme[1].setRating(8.3);
    filme[2].setRating(7.6);
    filme[3].setRating(9.0);
    filme[4].setRating(8.8);
    filme[5].setRating(8.0);
    filme[6].setRating(8.7);
    for (int i = 0; i < 3; ++i)
    {
        cinemauri[i].setFilmeDifuzate(7, filme);
    }
    std::vector<std::string> zile = {
        "Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica"
    };
    std::vector<std::string> ore = {
        "10:30", "12:00", "13:30", "15:00", "16:30", "18:00", "19:30", "21:00"
    };
    Sala *S1 = new Sala(1);
    Sala *S2 = new Sala(2);
    std::array<std::unique_ptr<Bilet>, 63> bilete{};
    for (int i = 0; i < 63; i++)
    {
        bilete[i] = std::make_unique<Bilet_Normal>(0, 0);
    }
    std::cout << "\nBine ati venit la Cinema Multiplex!\n";
client_sau_admin:
    std::cout
        << "\nPentru a cumpara un bilet de film apasati tasta 1.\n[admin] Pentru a va loga apasati tasta 2.\nPentru a iesi apasati tasta 0.\n";
    f >> tasta;
    if (std::stoi(tasta) == 0)
    {
        goto exit;
    }
    if (std::stoi(tasta) < 0 || std::stoi(tasta) > 2)
    {
        std::cout << "\nVa rugam apasati o tasta valida.\n";
        goto client_sau_admin;
    }
    if (std::stoi(tasta) == 1)
    {
        std::cout << "\nVa rugam completati campurile de mai jos.\n\n";
    citeste_cinema:
        std::cout << "\nApasati tasta corespunzatoare mall-ului dorit:\n1.Afi Cotroceni\n2.Park Lake\n3.Mega Mall\n";
        f >> tasta;
        if (std::stoi(tasta) == 0)
        {
            goto client_sau_admin;
        }
        if (std::stoi(tasta) < 0 || std::stoi(tasta) > 3)
        {
            std::cout << "\nVa rugam apasati o tasta valida.\n";
            goto citeste_cinema;
        }
        std::cout << "Ati selectat " << cinemauri[std::stoi(tasta) - 1].getNumeMall() << "\n";
        cod_cinema = std::to_string(cinemauri[std::stoi(tasta) - 1].getId());
    citeste_film:
        std::cout << "\nApasati tasta corespunzatoare filmului dorit:\n";
        for (int i = 0; i < cinemauri[0].getNrFilme(); ++i)
        {
            std::cout << i + 1 << "." << cinemauri[0].getFilmeDifuzate()[i].getNumeFilm() << " ("
                      << cinemauri[0].getFilmeDifuzate()[i].getRating() << ")\n";
        }
        std::cout << "Apasati tasta 0 pentru a merge inapoi.\n";
        f >> tasta;
        if (std::stoi(tasta) == 0)
        {
            goto citeste_cinema;
        }
        if (std::stoi(tasta) < 0 || std::stoi(tasta) > cinemauri[0].getNrFilme())
        {
            std::cout << "\nVa rugam apasati o tasta valida.\n";
            goto citeste_film;
        }
        std::cout << "Ati selectat " << cinemauri[0].getFilmeDifuzate()[std::stoi(tasta) - 1].getNumeFilm() << "\n";
        cod_film = cinemauri[0].getFilmeDifuzate()[std::stoi(tasta) - 1].getNumeFilm();
        for (int i = 0; (unsigned long long)i < cod_film.length(); ++i)
        {
            if (cod_film[i] == ' ')
            {
                cod_film[i] = '_';
            }
        }
    citeste_zi:
        std::cout
            << "\nApasati tasta corespunzatoare zilei dorite:\n1.Luni\n2.Marti\n3.Miercuri\n4.Joi\n5.Vineri\n6.Sambata\n7.Duminica\nApasati tasta 0 pentru a merge inapoi.\n";
        f >> tasta;
        if (std::stoi(tasta) == 0)
        {
            goto citeste_film;
        }
        if (std::stoi(tasta) < 0 || std::stoi(tasta) > 7)
        {
            std::cout << "\nVa rugam apasati o tasta valida.\n";
            goto citeste_zi;
        }
        std::cout << "Ati selectat " << zile[std::stoi(tasta) - 1] << "\n";
        cod_zi = zile[std::stoi(tasta) - 1];
    citeste_ora:
        std::cout
            << "\nApasati tasta corespunzatoare orei dorite:\n1.10:30\n2.12:00\n3.13:30\n4.15:00\n5.16:30\n6.18:00\n7.19:30\n8.21:00\n9.22:30\nApasati tasta 0 pentru a merge inapoi.\n";
        f >> tasta;
        if (std::stoi(tasta) == 0)
        {
            goto citeste_zi;
        }
        if (std::stoi(tasta) < 0 || std::stoi(tasta) > 9)
        {
            std::cout << "\nVa rugam apasati o tasta valida.\n";
            goto citeste_ora;
        }
        cod_ora = ore[std::stoi(tasta) - 1];
        std::cout << "Ati selectat " << ore[std::stoi(tasta) - 1] << "\n";
        id_sala = std::stoi(tasta) % 2;
        cod_sala = std::to_string(id_sala);
        if (id_sala == 1)
        {
            for (int i = 0; i < 63; i++)
            {
                loc[i] = S1->getLocuriOcupate()[i];
            }
        }
        else
        {
            for (int i = 0; i < 63; i++)
            {
                loc[i] = S2->getLocuriOcupate()[i];
            }
        }
        std::cout << "\nLocurile disponibile sunt marcate cu 0, locurile ocupate sunt marcate cu 1.\n";
        std::cout << "Pentru a alege locul tastati randul urmat de tasta Enter apoi numarul scaunului.\n\n";
        std::cout << " __";
        for (int j = 0; j < 9; j++)
        {
            std::cout << "__";
        }
        std::cout << "__ ";
        std::cout << "\n\n\n   ";
        for (int j = 0; j < 9; j++)
        {
            std::cout << j + 1 << " ";
        }
        std::cout << "\n";
        for (int i = 0; i < 7; i++)
        {
            std::cout << i + 1 << "  ";
            for (int j = 0; j < 9; j++)
            {
                std::cout << loc[i * 9 + j] << " ";
            }
            std::cout << '\n';
        }
        while (nr_bilete < 63)
        {
        citeste_loc:
            std::cout
                << "\nAlegeti locul. Introduceti randul si coloana locului dorit.\nApasati de 2 ori tasta 0 pentru a merge inapoi.\n";
            if (nr_bilete != 0)
            {
                std::cout << "Apasati de 2 ori tasta 10 pentru a continua cu plata.\n";
            }
            f >> x >> y;
            if (x == 10 && y == 10)
            {
                break;
            }
            if (x == 0 && y == 0)
            {
                if (nr_bilete == 0)
                {
                    goto citeste_ora;
                }
                nr_bilete--;
                bilete[nr_bilete]->setRand(0);
                bilete[nr_bilete]->setColoana(0);
                goto citeste_loc;
            }
            if (x < 0 || y < 0 || x == 9 || x > 10 || y > 10 || (x == 10 && y != 10) || (x == 0 && y != 0)
                || (x != 10 && y == 10) || (x != 0 && y == 0))
            {
                std::cout << "\nVa rugam apasati o tasta valida.\n";
                goto citeste_loc;
            }
            if (loc[x * 9 + y] == 1)
            {
                std::cout << "\nLocul este deja ocupat.\n";
                goto citeste_loc;
            }
            if (loc[x * 9 + y] == 2)
            {
                std::cout << "\nLocul este deja ales de dvs.\n";
                goto citeste_loc;
            }
            bilete[nr_bilete]->setRand(x);
            bilete[nr_bilete]->setColoana(y);
            cod_rand = std::to_string(x);
            cod_coloana = std::to_string(y);
            loc[(bilete[nr_bilete]->getRand() - 1) * 9 + (bilete[nr_bilete]->getColoana() - 1)] = 2;
            nr_bilete++;
            k = 0;
            std::cout << "\nLocurile alese de dvs. sunt cele marcate cu 2:\n";
            std::cout << " __";
            for (int j = 0; j < 9; j++)
            {
                std::cout << "__";
            }
            std::cout << "__ ";
            std::cout << "\n\n\n   ";
            for (int j = 0; j < 9; j++)
            {
                std::cout << j + 1 << " ";
            }
            std::cout << "\n";
            for (int i = 0; i < 7; i++)
            {
                std::cout << i + 1 << "  ";
                for (int j = 0; j < 9; j++)
                {
                    if (bilete[k]->getRand() == i + 1 and bilete[k]->getColoana() == j + 1 and k < nr_bilete)
                    {
                        k++;
                        std::cout << "2 ";
                    }
                    else
                    {
                        std::cout << loc[i * 9 + j] << " ";
                    }
                }
                std::cout << '\n';
            }
        }
        for (int i = 0; i < nr_bilete; i++)
        {
            loc[(bilete[i]->getRand() - 1) * 9 + (bilete[i]->getColoana() - 1)] = 1;
            suma += bilete[i]->getPret();
        }
    upgrade_bilet:
        std::cout
            << "\nDoriti sa upgradati sau sa downgradati un bilet? Apasati tasta corespunzatoare:\n1.Nu, multumesc\n2.Vreau sa upgradez la bilet VIP (60 lei)\n3.Vreau sa downgradez la bilet normal (25 lei)\n";
        f >> tasta;
        if (std::stoi(tasta) < 1 || std::stoi(tasta) > 3)
        {
            std::cout << "\nVa rugam apasati o tasta valida.\n";
            goto upgrade_bilet;
        }
        if (std::stoi(tasta) == 1)
        {
            std::cout << "\nAti ales sa nu modificati biletele.\n";
            cod_beneficii = "Normal";
            goto plata;
        }
        if (std::stoi(tasta) == 2)
        {
            std::cout << "\nAlegeti biletul pe care doriti sa il upgradati:\n";
            for (int i = 0; i < nr_bilete; ++i)
            {
                std::cout << i + 1 << ".";
                bilete[i]->afiseaza();
                std::cout << std::endl;
            }
            f >> tasta;
            int index = std::stoi(tasta) - 1;
            std::cout << tasta << std::endl;
            std::cout << index << std::endl;
            std::cout << nr_bilete << std::endl;
            std::cout << bilete[index]->getType() << std::endl;

            int status;
            char * realname = abi::__cxa_demangle(typeid(tasta).name(), 0, 0, &status);
            std::cout<< realname << std::endl;
            free(realname);

            std::cout << typeid(std::string("Normal")).name() << std::endl;
            std::cout << typeid(bilete[index]->getType()).name() << std::endl;
            /// aici se rupe firul, nu intra in iful 3
            if (index >= nr_bilete || index < 0)
            {
                std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                goto upgrade_bilet;
            }
            if (bilete[index]->getType() == "VIP")
            {
                std::cout << "\nBiletul nu poate fi upgradat pentru ca e un bilet VIP.\n";
                goto upgrade_bilet;
            }
            if (bilete[index]->getType() == std::string("Normal"))
            {
                suma -= bilete[index]->getPret();
                std::cout << suma;
                auto *pVIP = dynamic_cast<Bilet_VIP *>(bilete[index].get());
                bilete[index] = Bilet_VIP::upgradeBilet();
                std::cout << "\nBiletul a fost upgradat la VIP.";
                suma += pVIP->getPret();
                cod_beneficii = "VIP";
                goto upgrade_bilet;
            }
        }
        if (std::stoi(tasta) == 3)
        {
            std::cout << "\nAlegeti biletul pe care doriti sa il downgradati:\n";
            for (int i = 0; i < nr_bilete; i++)
            {
                std::cout << i + 1 << ".";
                bilete[i]->afiseaza();
                std::cout << std::endl;
            }
            f >> tasta;
            int index = std::stoi(tasta) - 1;
            if (index >= nr_bilete || index < 0)
            {
                std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                goto upgrade_bilet;
            }
            if (bilete[index]->getType() == "Normal")
            {
                std::cout << "\nBiletul nu poate fi downgradat pentru ca e un bilet normal.\n";
                goto upgrade_bilet;
            }
            if (bilete[index]->getType() == "VIP")
            {
                suma -= bilete[index]->getPret();
                auto *pNormal = dynamic_cast<Bilet_Normal *>(bilete[index].get());
                bilete[index] = Bilet_Normal::downgradeBilet();
                std::cout << "\nBiletul a fost downgradat la Normal.";
                suma += pNormal->getPret();
                cod_beneficii = "normal";
                goto upgrade_bilet;
            }
        }
    plata:
        std::cout << "\nDe platit: " << suma << "\nNumarul cardului [12 cifre]: ";
        f.get();
        std::getline(f, nr_card);
        std::cout << nr_card << "\n";
        std::cout << "Numele titularului: ";
        std::getline(f, nume_titular);
        std::cout << nume_titular << "\n";
        std::cout << "Data expirarii [MM/YY]: ";
        f >> data_exp;
        std::cout << data_exp << "\n";
        std::cout << "CCV [3 cifre]: ";
        f >> ccv;
        std::cout << ccv << "\n";
        if (nr_bilete == 1)
        {
            std::cout << "\n\nCodul biletului dvs. este: " << cod_cinema << cod_film << cod_zi << cod_ora << cod_sala
                      << cod_rand << cod_coloana << cod_beneficii << "\n";
        }
        else
        {
            std::cout << "\n\nCodurile biletelor dvs. sunt:\n";
            for (int i = 0; i < nr_bilete; i++)
            {
                std::cout << cod_cinema << cod_film << cod_zi << cod_ora << cod_sala << bilete[i]->getRand()
                          << bilete[i]->getColoana() << bilete[i]->getType() << "\n";
            }
        }
        std::cout << "\nVa multumim pentru achizitie! Vizionare placuta!\n";
        goto exit;
    }
    if (std::stoi(tasta) == 2)
    {
        f.get();
        std::cout << "\nUsername: ";
        std::string username;
        std::getline(f, username);
        std::cout << username;
        std::cout << "\nParola: ";
        std::string parola;
        std::getline(f, parola);
        std::cout << parola;
        std::cout << "\n\nBuna, " << username;
    actiuni_admin:
        std::cout
            << "\n0.Iesiti\n1.Adaugati un film. [input: nume 'enter' rating]\n2.Stergeti un film. [input: nume]\n3.Schimba rating-ul unui film. [input: nume 'enter' rating]\n4.Afiseaza lista filmelor.\n";
        f >> tasta;
        if (std::stoi(tasta) == 0)
        {
            goto exit;
        }
        if (std::stoi(tasta) < 0)
        {
            std::cout << "\nVa rugam apasati o tasta mai mare sau egala cu 0.\n";
            goto actiuni_admin;
        }
        std::cout << "\nAti selectat tasta " << tasta << ".\n";
        if (std::stoi(tasta) == 1)
        {
            f.get();
            std::string nouFilm;
            std::getline(f, nouFilm);
            double rating;
            f >> rating;
            std::cout << "Ati selectat " << nouFilm << " (" << rating << ").";
            cinemauri[0].adaugaFilm(nouFilm, rating);
            if (cinemauri[0].getNrFilme() > cinemauri[1].getNrFilme())
            {
                std::cout << " Filmul a fost adaugat cu succes.\n";
                for (int i = 1; i < 3; i++)
                {
                    cinemauri[i].adaugaFilm(nouFilm, rating);
                }
            }
            goto actiuni_admin;
        }
        if (std::stoi(tasta) == 2)
        {
            f.get();
            std::string nouFilm;
            std::getline(f, nouFilm);
            std::cout << "Ati selectat " << nouFilm << ". ";
            cinemauri[0].stergeFilm(nouFilm);
            if (cinemauri[0].getNrFilme() < cinemauri[1].getNrFilme())
            {
                std::cout << " Filmul a fost sters cu succes.\n";
                for (int i = 1; i < 3; i++)
                {
                    cinemauri[i].stergeFilm(nouFilm);
                }
            }
            goto actiuni_admin;
        }
        if (std::stoi(tasta) == 3)
        {
            f.get();
            std::string nouFilm;
            std::getline(f, nouFilm);
            float nouRating;
            f >> nouRating;
            int index = -1;
            for (int i = 0; i < cinemauri[0].getNrFilme(); ++i)
            {
                if (cinemauri[0].getFilmeDifuzate()[i].getNumeFilm() == nouFilm)
                {
                    index = i;
                    break;
                }
            }
            std::cout << "Ati selectat " << nouFilm << " (" << cinemauri[0].getFilmeDifuzate()[index].getRating()
                      << " -> " << nouRating << ").";
            cinemauri[0].schimbaRating(nouFilm, nouRating);
            if (index != -1 && cinemauri[0].getFilmeDifuzate()[index].getRating() !=
                cinemauri[1].getFilmeDifuzate()[index].getRating())
            {
                std::cout << " Rating-ul filmului a fost modificat cu succes.\n";
                for (int i = 1; i < 3; i++)
                {
                    cinemauri[i].schimbaRating(nouFilm, nouRating);
                }
            }
            goto actiuni_admin;
        }
        if (std::stoi(tasta) == 4)
        {
            for (int i = 0; i < cinemauri[0].getNrFilme(); ++i)
            {
                std::cout << i + 1 << "." << cinemauri[0].getFilmeDifuzate()[i].getNumeFilm() << " ("
                          << cinemauri[0].getFilmeDifuzate()[i].getRating() << ")\n";
            }
            goto actiuni_admin;
        }
    }
exit:
    std::cout << "\nLa revedere!\n";
    delete S1;
    delete S2;
    delete[] filme;
    return 0;
}

#include <iostream>
//#include <fstream>
#include <array>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include "Film.h"

class Sala {
private:
    int id;
    int nrLocuri;
    int nrRanduri;
    int nrColoane;
    bool *locuriOcupate;
public:
    friend class Cinema;

    explicit Sala(int id) {
        this->id = id;
        this->nrLocuri = 63;
        this->nrRanduri = 9;
        this->nrColoane = 7;
        locuriOcupate = new bool[nrLocuri];
        for (int i = 0; i < nrLocuri; i++) {
			locuriOcupate[i] = false;
		}
    }

    Sala() {
        this->id = 0;
        this->nrLocuri = 0;
        this->nrRanduri = 0;
        this->nrColoane = 0;
        locuriOcupate = nullptr;
    }

    ~Sala() {
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
			locuriOcupate = new bool[other.nrLocuri];
		for (int i = 0; i < other.nrLocuri; i++) {
			locuriOcupate[i] = other.locuriOcupate[i];
		}
    }

    Sala &operator=(const Sala &other) {
        if (this != &other) {
            delete[] locuriOcupate;
            id = other.id;
            nrLocuri = other.nrLocuri;
            nrRanduri = other.nrRanduri;
            nrColoane = other.nrColoane;
            locuriOcupate = new bool[other.nrLocuri];
            for (int i = 0; i < other.nrLocuri; i++) {
                locuriOcupate[i] = other.locuriOcupate[i];
            }
        }
        return *this;
    }

    void setIdSala(int id) {
        this->id = id;
    }

    void setLocuriOcupate(int nrLocuri, const bool *locuriOcupate) {
        this->nrLocuri = nrLocuri;
        delete[] this->locuriOcupate;
        this->locuriOcupate = new bool[nrLocuri];
        for (int i = 0; i < nrLocuri; i++) {
            this->locuriOcupate[i] = locuriOcupate[i];
        }
    }

    [[nodiscard]] int getIdSala() const {
        return id;
    }

    [[nodiscard]] bool *getLocuriOcupate() const {
        return locuriOcupate;
    }
};

class Cinema {
private:
    int id;
    std::string numeMall;
    Film *filmeDifuzate;
    int nrFilme;
public:
    Cinema(int id, std::string numeMall) {
        this->id = id;
        this->numeMall = std::move(numeMall);
        this->nrFilme = 0;
        this->filmeDifuzate = nullptr;
    }

    Cinema() {
        this->id = 0;
        this->nrFilme = 0;
        this->numeMall = '\0';
        this->filmeDifuzate = nullptr;
    }

    ~Cinema() {
        delete[] this->filmeDifuzate;
    }

    void setId(int id) {
        this->id = id;
    }

    void setNumeMall(std::string numeMall) {
        this->numeMall = std::move(numeMall);
    }

    void setNrFilme(int nrFilme) {
        this->nrFilme = nrFilme;
    }

    void setFilmeDifuzate(int nrFilme, const Film *filmeDifuzate)
	{
		this->nrFilme = nrFilme;
		delete[] this->filmeDifuzate;
		this->filmeDifuzate = new Film[nrFilme];
		for (int i = 0; i < nrFilme; i++) {
			this->filmeDifuzate[i] = filmeDifuzate[i];
		}
    }

    [[nodiscard]] int getId() const {
        return id;
    }

    [[nodiscard]] std::string getNumeMall() const {
        return numeMall;
    }

    [[nodiscard]] int getNrFilme() const {
        return nrFilme;
    }

    [[nodiscard]] Film *getFilmeDifuzate() const {
        return filmeDifuzate;
    }

    void adaugaFilm(const std::string &numeFilm, const float rating) {
        int ok = 1;
        for (int i = 0; i < nrFilme; i++) {
			if (filmeDifuzate[i].numeFilm == numeFilm)
			{
				ok = 0;
				break;
			}
		}
        if (ok == 0)
            std::cout << "Filmul este deja in lista filmelor difuzate.\n";
        else {
            Film *nouFilmeDifuzate = new Film[nrFilme + 1];
            for (int i = 0; i < nrFilme; i++) {
				nouFilmeDifuzate[i] = filmeDifuzate[i];
			}
			nouFilmeDifuzate[nrFilme] = Film(numeFilm, rating);
            nrFilme++;
            delete[] filmeDifuzate;
            filmeDifuzate = nouFilmeDifuzate;
            std::sort(filmeDifuzate, filmeDifuzate + nrFilme, Film::comparaFilme);
        }
    }

    void stergeFilm(const std::string &numeFilm) {
        int index = -1;
        for (int i = 0; i < nrFilme; i++) {
			if (filmeDifuzate[i].numeFilm == numeFilm)
			{
				index = i;
				break;
			}
		}
        if (index != -1) {
            Film *nouFilmeDifuzate = new Film[nrFilme - 1];
            for (int i = 0; i < index; i++) {
                nouFilmeDifuzate[i] = filmeDifuzate[i];
            }
            for (int i = index; i < nrFilme - 1; i++) {
                nouFilmeDifuzate[i] = filmeDifuzate[i + 1];
            }
            nrFilme--;
            delete[] filmeDifuzate;
            filmeDifuzate = nouFilmeDifuzate;
        } else
            std::cout << "Filmul nu exista in lista filmelor difuzate.\n";
    }

    void schimbaRating(const std::string &numeFilm, float nouRating) {
        for (int i = 0; i < nrFilme; ++i) {
			if (filmeDifuzate[i].numeFilm == numeFilm)
			{
				filmeDifuzate[i].rating = nouRating;
				return;
			}
		}
        std::cout << "Filmul nu exista in lista filmelor difuzate.\n";
    }

    Cinema(const Cinema &aux) {
        id = aux.id;
        numeMall = aux.numeMall;
        nrFilme = aux.nrFilme;
        filmeDifuzate = new Film[aux.nrFilme];
        for (int i = 0; i < aux.nrFilme; i++) {
			filmeDifuzate[i] = aux.filmeDifuzate[i];
		}
    }

    Cinema &operator=(const Cinema &aux) {
        if (this == &aux) {
            return *this;
        }
        this->id = aux.id;
        this->numeMall = aux.numeMall;
        this->nrFilme = aux.nrFilme;
        delete[] filmeDifuzate;
        this->filmeDifuzate = new Film[nrFilme];
        for (int i = 0; i < aux.nrFilme; i++) {
			filmeDifuzate[i] = aux.filmeDifuzate[i];
		}
        return *this;
    }

    Cinema operator+(Cinema &cinema) {
        if (this == &cinema)
            return *this;
        Cinema nouCinema;
        nouCinema.id = this->id;
        nouCinema.numeMall = this->numeMall;
        nouCinema.filmeDifuzate = new Film[this->nrFilme + cinema.nrFilme];
        for (int i = 0; i < this->nrFilme; i++) {
            nouCinema.filmeDifuzate[i] = this->filmeDifuzate[i];
        }
        for (int i = 0; i < cinema.nrFilme; i++) {
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

    friend std::istream &operator>>(std::istream &in, Cinema &cinema) {
        std::cout << "\nid: ";
        in >> cinema.id;
        std::cout << "\nnume mall: ";
        in >> cinema.numeMall;
        std::cout << "\nnumar sali: ";
        in >> cinema.nrFilme;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const Cinema &cinema) {
        out << "\nid: " << cinema.id;
        out << "\nnume mall: " << cinema.numeMall;
        out << "\nnumar sali: " << cinema.nrFilme;
        return out;
    }
};

class Bilet {
private:
    int rand;
    int coloana;
    int nr_bilete;
public:
    friend class Cinema;

    Bilet(int nr_bilete, int rand, int coloana) {
        this->rand = rand;
        this->coloana = coloana;
        this->nr_bilete = nr_bilete;
    }

    explicit Bilet(int nr_bilete) {
        this->rand = 0;
        this->coloana = 0;
        this->nr_bilete = nr_bilete;
    }

    Bilet() {
        this->rand = 0;
        this->coloana = 0;
        this->nr_bilete = 0;
    }

    ~Bilet() = default;

    void setRand(int rand) {
        this->rand = rand;
    }

    void setColoana(int coloana) {
        this->coloana = coloana;
    }

    void setNrBilet(int nr_bilete) {
        this->nr_bilete = nr_bilete;
    }

    [[nodiscard]] int getRand() const {
        return rand;
    }

    [[nodiscard]] int getColoana() const {
        return coloana;
    }

    [[nodiscard]] int getNrBilete() const {
        return nr_bilete;
    }
};

bool operator==(const Cinema &cinema, const Cinema &aux) {
    if (cinema.getId() == aux.getId() and cinema.getNumeMall() == aux.getNumeMall())
        return true;
    else
        return false;
}

int main() {
    std::istream &f = std::cin;
    int tasta, id_sala, k, loc[63], x, y, nr_bilete = 0, ccv;
    std::string cod_cinema, cod_film, cod_zi, cod_ora, cod_sala, cod_rand, cod_coloana, nr_card, nume_titular, data_exp;
    std::array<Cinema, 3> cinemauri{};
    cinemauri[0].setNumeMall("Afi Cotroceni");
    cinemauri[1].setNumeMall("Park Lake");
    cinemauri[2].setNumeMall("Mega Mall");
    for (int i = 0; i < 3; i++) {
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
    for (int i = 0; i < 3; ++i) {
        cinemauri[i].setFilmeDifuzate(7, filme);
    }
    std::vector<std::string> zile;
    zile.emplace_back("Luni");
    zile.emplace_back("Marti");
    zile.emplace_back("Miercuri");
    zile.emplace_back("Joi");
    zile.emplace_back("Vineri");
    zile.emplace_back("Sambata");
    zile.emplace_back("Duminica");
    std::vector<std::string> ore;
    ore.emplace_back("10:30");
    ore.emplace_back("12:00");
    ore.emplace_back("13:30");
    ore.emplace_back("15:00");
    ore.emplace_back("16:30");
    ore.emplace_back("18:00");
    ore.emplace_back("19:30");
    ore.emplace_back("21:00");
    Sala *S1 = new Sala(1);
    Sala *S2 = new Sala(2);
    std::array<Bilet, 9> bilete{};
    for (int i = 0; i < 9; i++) {
		bilete[i].setNrBilet(i + 1);
	}
    std::cout << "\nBine ati venit la Cinema Multiplex!\n";
    client_sau_admin:
    std::cout
            << "\nPentru a cumpara un bilet de film apasati tasta 1.\n[admin] Pentru a va loga apasati tasta 2.\nPentru a iesi apasati tasta 0.\n";
    f >> tasta;
    if (tasta == 0)
        goto exit;
    if (tasta == 1) {
        std::cout << "\nVa rugam completati campurile de mai jos.\n\n";
        citeste_cinema:
        std::cout << "\nApasati tasta corespunzatoare mall-ului dorit:\n1.Afi Cotroceni\n2.Park Lake\n3.Mega Mall\n";
        f >> tasta;
        if (tasta == 0) {
            goto client_sau_admin;
        }
        std::cout << "Ati selectat " << cinemauri[tasta - 1].getNumeMall() << "\n";
        cod_cinema = std::to_string(cinemauri[tasta - 1].getId());
        citeste_film:
        std::cout << "\nApasati tasta corespunzatoare filmului dorit:\n";
        for (int i = 0; i < cinemauri[0].getNrFilme(); ++i) {
			std::cout << i + 1 << "." << cinemauri[0].getFilmeDifuzate()[i].getNumeFilm() << " ("
					  << cinemauri[0].getFilmeDifuzate()[i].getRating() << ")\n";
		}
        std::cout << "Apasati tasta 0 pentru a merge inapoi.\n";
        f >> tasta;
        if (tasta == 0)
            goto citeste_cinema;
        std::cout << "Ati selectat " << cinemauri[0].getFilmeDifuzate()[tasta - 1].getNumeFilm() << "\n";
        cod_film = cinemauri[0].getFilmeDifuzate()[tasta - 1].getNumeFilm();
        citeste_zi:
        std::cout
                << "\nApasati tasta corespunzatoare zilei dorite:\n1.Luni\n2.Marti\n3.Miercuri\n4.Joi\n5.Vineri\n6.Sambata\n7.Duminica\nApasati tasta 0 pentru a merge inapoi.\n";
        f >> tasta;
        if (tasta == 0)
            goto citeste_film;
        std::cout << "Ati selectat " << zile[tasta - 1] << "\n";
        cod_zi = zile[tasta - 1];
        citeste_ora:
        std::cout
                << "\nApasati tasta corespunzatoare orei dorite:\n1.10:30\n2.12:00\n3.13:30\n4.15:00\n5.16:30\n6.18:00\n7.19:30\n8.21:00\n9.22:30\nApasati tasta 0 pentru a merge inapoi.\n";
        f >> tasta;
        if (tasta == 0)
            goto citeste_zi;
        cod_ora += ore[tasta - 1];
        std::cout << "Ati selectat " << ore[tasta - 1] << "\n";
        id_sala = tasta % 2;
        cod_sala += std::to_string(id_sala);
        if (tasta == 0)
            goto citeste_ora;
        if (id_sala == 1)
            for (int i = 0; i < 63; i++) {
				loc[i] = S1->getLocuriOcupate()[i];
			}
        else
            for (int i = 0; i < 63; i++) {
				loc[i] = S2->getLocuriOcupate()[i];
			}
        std::cout << "\nLocurile disponibile sunt marcate cu 0, locurile ocupate sunt marcate cu 1.\n";
        std::cout << "Pentru a alege locul tastati randul urmat de tasta Enter apoi numarul scaunului.\n\n";
        std::cout << " __";
        for (int j = 0; j < 9; j++) {
			std::cout << "__";
		}
        std::cout << "__ ";
        std::cout << "\n\n\n   ";
        for (int j = 0; j < 9; j++) {
			std::cout << j + 1 << " ";
		}
        std::cout << "\n";
        for (int i = 0; i < 7; i++) {
            std::cout << i + 1 << "  ";
            for (int j = 0; j < 9; j++) {
				std::cout << loc[i * 9 + j] << " ";
			}
            std::cout << '\n';
        }
        while (nr_bilete < 9) {
            citeste_rand:
            std::cout << "\nAlegeti randul.\nApasati tasta 0 pentru a merge inapoi.\n";
            if (nr_bilete != 0)
                std::cout << "Apasati tasta 10 pentru a continua cu plata.\n";
            f >> x;
            if (x == 10) {
                break;
            }
            if (x == 0) {
                if (nr_bilete == 0) {
                    goto citeste_ora;
                }
                nr_bilete--;
                bilete[nr_bilete].setColoana(0);
                goto citeste_coloana;
            }
            bilete[nr_bilete].setRand(x);
            cod_rand = std::to_string(x);
            citeste_coloana:
            std::cout << "\nAlegeti locul.\nApasati tasta 0 pentru a merge inapoi.\n";
            f >> y;
            if (y == 0) {
                bilete[nr_bilete].setRand(0);
                goto citeste_rand;
            }
            bilete[nr_bilete].setColoana(y);
            cod_coloana = std::to_string(y);
            nr_bilete++;
            k = 0;
            std::cout << "\nLocurile alese de dvs. sunt cele marcate cu 2:\n";
            std::cout << " __";
            for (int j = 0; j < 9; j++) {
				std::cout << "__";
			}
            std::cout << "__ ";
            std::cout << "\n\n\n   ";
            for (int j = 0; j < 9; j++) {
				std::cout << j + 1 << " ";
			}
            std::cout << "\n";
            for (int i = 0; i < 7; i++) {
                std::cout << i + 1 << "  ";
                for (int j = 0; j < 9; j++) {
                    if (bilete[k].getRand() == i + 1 and bilete[k].getColoana() == j + 1 and k < nr_bilete) {
                        k++;
                        std::cout << "2 ";
                    } else
                        std::cout << loc[i * 9 + j] << " ";
                }
                std::cout << '\n';
            }
        }
        for (int i = 0; i < nr_bilete; i++) {
			loc[(bilete[i].getRand() - 1) * 9 + (bilete[i].getColoana() - 1)] = 1;
		}
        std::cout << "\nNumarul cardului [12 cifre]: ";
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
        if (nr_bilete == 1) {
            std::cout << "\n\nCodul biletului dvs. este: " << cod_cinema << cod_film << cod_zi << cod_ora << cod_sala
                      << cod_rand << cod_coloana << "\n";
        } else {
            std::cout << "\n\nCodurile biletelor dvs. sunt:\n";
            for (int i = 0; i < nr_bilete; i++) {
                std::cout << cod_cinema << cod_film << cod_zi << cod_ora << cod_sala << bilete[i].getRand()
                          << bilete[i].getColoana() << "\n";
            }
        }
        std::cout << "\nVa multumim pentru achizitie! Vizionare placuta!\n";
        goto exit;
    }
    if (tasta == 2) {
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
        if (tasta == 0)
            goto exit;
        std::cout << "\nAti selectat tasta " << tasta << ".\n";
        if (tasta == 1) {
            f.get();
            std::string nouFilm;
            std::getline(f, nouFilm);
            float rating;
            f >> rating;
            std::cout << "Ati selectat " << nouFilm << " (" << rating << ").";
            cinemauri[0].adaugaFilm(nouFilm, rating);
            if (cinemauri[0].getNrFilme() > cinemauri[1].getNrFilme()) {
                std::cout << " Filmul a fost adaugat cu succes.\n";
                for (int i = 1; i < 3; i++) {
					cinemauri[i].adaugaFilm(nouFilm, rating);
				}
            }
            goto actiuni_admin;
        }
        if (tasta == 2) {
            f.get();
            std::string nouFilm;
            std::getline(f, nouFilm);
            std::cout << "Ati selectat " << nouFilm << ". ";
            cinemauri[0].stergeFilm(nouFilm);
            if (cinemauri[0].getNrFilme() < cinemauri[1].getNrFilme()) {
                std::cout << " Filmul a fost sters cu succes.\n";
                for (int i = 1; i < 3; i++) {
					cinemauri[i].stergeFilm(nouFilm);
				}
            }
            goto actiuni_admin;
        }
        if (tasta == 3) {
            f.get();
            std::string nouFilm;
            std::getline(f, nouFilm);
            float nouRating;
            f >> nouRating;
            int index = -1;
            for (int i = 0; i < cinemauri[0].getNrFilme(); ++i) {
                if (cinemauri[0].getFilmeDifuzate()[i].getNumeFilm() == nouFilm) {
                    index = i;
                    break;
                }
            }
            std::cout << "Ati selectat " << nouFilm << " (" << cinemauri[0].getFilmeDifuzate()[index].getRating()
                      << " -> " << nouRating << ").";
            cinemauri[0].schimbaRating(nouFilm, nouRating);
            if (index != -1 && cinemauri[0].getFilmeDifuzate()[index].getRating() !=
                               cinemauri[1].getFilmeDifuzate()[index].getRating()) {
                std::cout << " Rating-ul filmului a fost modificat cu succes.\n";
                for (int i = 1; i < 3; i++) {
					cinemauri[i].schimbaRating(nouFilm, nouRating);
				}
            }
            goto actiuni_admin;
        }
        if (tasta == 4) {
            for (int i = 0; i < cinemauri[0].getNrFilme(); ++i) {
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
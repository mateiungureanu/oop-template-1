#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <regex>
#include <algorithm>

#include "Sala.h"
#include "Cinema.h"
#include "Film.h"
#include "Bilet.h"
#include "Bilet_Normal.h"
#include "Bilet_4Dx.h"
#include "Bilet_VIP.h"

class application {
private:
    application() = default;

    static std::string
    conversie(std::istream &f)
    {
        std::string tasta;
        f >> tasta;
        (void)std::stoi(tasta);
        return tasta;
    }

    static std::string
    conversieExtinsa(std::istream &f)
    {
        std::string tasta;
        while (true)
        {
            try
            {
                tasta = conversie(f);
                return tasta;
            }
            catch (const std::exception &)
            {
                std::cout << "\nVa rugam apasati o tasta valida0.\n";
            }
        }
    }

    static void
    addUser(std::map<std::string, std::string> &credentials, const std::string &username, const std::string &password)
    {
        credentials[username] = password;
    }

    static bool
    authenticate(const std::map<std::string, std::string> &credentials,
                 const std::string &username,
                 const std::string &password)
    {
        auto it = credentials.find(username);
        if (it != credentials.end() && it->second == password)
        {
            return true;
        }
        return false;
    }

    static bool
    nrCard(const std::string &nr_card)
    {
        std::regex pattern(R"(^\d{4}(?:\s?\d{4}){3}$)");
        return std::regex_match(nr_card, pattern);
    }

    static bool
    ccvCode(const std::string &ccv)
    {
        std::regex pattern(R"(^\d{3}$)");
        return std::regex_match(ccv, pattern);
    }

    static bool
    dataExp(const std::string &data_exp)
    {
        std::regex pattern(R"(^(0[1-9]|1[0-2])/(2[4-9])$)");
        return std::regex_match(data_exp, pattern);
    }

    bool ordoneaza = false;

public:
    application(const application&) = delete;
    application& operator=(const application&) = delete;
    static application& get_app() {
        static application app;
        return app;
    }
    void meniu() {
        std::istream &f = std::cin;
        int id_sala, k, loc[63], x, y, nr_bilete = 0, suma = 0, ccv, index;
        std::string tasta, cod_cinema, cod_film, cod_zi, cod_ora, cod_sala, nr_card, nume_titular, data_exp;
        std::map<std::string, std::string> credentials;
        addUser(credentials, "mateistefan", "qwertyuiop");
        addUser(credentials, "dragosbahrim", "asdfghjkl");
        addUser(credentials, "shatgepeto", "zxcvbnm");
        std::array<Cinema, 3> cinemauri{};
        cinemauri[0].setNumeMall("Afi Cotroceni");
        cinemauri[1].setNumeMall("Park Lake");
        cinemauri[2].setNumeMall("Mega Mall");
        for (int i = 0; i < 3; ++i)
        {
            cinemauri[i].setId(i + 1);
        }
        for (int i = 0; i < 3; ++i)
        {
            cinemauri[i].adaugaFilm("Dune Part 2", 8.8);
            cinemauri[i].adaugaFilm("Oppenheimer", 8.3);
            cinemauri[i].adaugaFilm("Star Wars Episode 3 Revenge of the Sith", 7.6);
            cinemauri[i].adaugaFilm("The Dark Knight", 9.0);
            cinemauri[i].adaugaFilm("The Lord of the Rings The Two Towers", 8.8);
            cinemauri[i].adaugaFilm("The Martian", 8.0);
            cinemauri[i].adaugaFilm("The Matrix", 8.7);
        }
        std::vector<std::string> zile = {
            "Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica"
        };
        std::vector<std::string> ore = {
            "10:30", "12:00", "13:30", "15:00", "16:30", "18:00", "19:30", "21:00"
        };
        std::vector<bool> locuriOcupate(63, false);
        SalaBuilder b;
        Sala S1 = b.setId(1).setNrLocuri(63).setNrRanduri(9).setNrColoane(7).setLocuriOcupate(locuriOcupate).build();
        Sala S2 = b.setId(1).setNrLocuri(63).setNrRanduri(9).setNrColoane(7).setLocuriOcupate(locuriOcupate).build();
        std::vector<Bilet *> bilete;
        for (int i = 0; i < 63; ++i)
        {
            bilete.emplace_back(new Bilet_Normal);
        }
        std::cout << "\nBine ati venit la Cinema Multiplex!\n";
    client_sau_admin:
        std::cout
            << "\nPentru a cumpara un bilet de film apasati tasta 1.\n[admin] Pentru a va loga apasati tasta 2.\nPentru a iesi apasati tasta 0.\n";
        tasta = conversieExtinsa(f);
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
            tasta = conversieExtinsa(f);
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
            std::vector<Film> filme(cinemauri[0].getFilmeDifuzate().begin(), cinemauri[0].getFilmeDifuzate().end());
            std::sort(filme.begin(), filme.end(), [](const Film &a, const Film &b)
            {
                return a.getRating() > b.getRating();
            });
            if (!ordoneaza)
            {
                std::cout << "(ordonat dupa nume)\n";
                int it = 1;
                for (const auto &film : cinemauri[0].getFilmeDifuzate())
                {
                    std::cout << it++ << "." << film.getNumeFilm() << " (" << std::fixed
                              << std::setprecision(1) << film.getRating() << ")\n";
                }
            }
            else
            {
                std::cout << "(ordonat dupa rating)\n";
                int it = 1;
                for (const auto &film : filme)
                {
                    std::cout << it++ << "." << film.getNumeFilm() << " (" << std::fixed
                              << std::setprecision(1) << film.getRating() << ")\n";
                }
            }
            std::cout
                << "Apasati tasta 10 pentru a schimba modul de ordonare al filmelor.\nApasati tasta 0 pentru a merge inapoi.\n";
            tasta = conversieExtinsa(f);
            if (std::stoi(tasta) == 10)
            {
                ordoneaza = !ordoneaza;
                goto citeste_film;
            }
            if (std::stoi(tasta) == 0)
            {
                goto citeste_cinema;
            }
            if (std::stoi(tasta) < 0 || std::stoi(tasta) > (int)cinemauri[0].getFilmeDifuzate().size())
            {
                std::cout << "\nVa rugam apasati o tasta valida.\n";
                goto citeste_film;
            }
            if (!ordoneaza)
            {
                auto filmeDifuzate = cinemauri[0].getFilmeDifuzate();
                index = std::stoi(tasta) - 1;
                auto filmIterator = filmeDifuzate.begin();
                std::advance(filmIterator, index);
                std::cout << "Ati selectat " << filmIterator->getNumeFilm() << "\n";
                cod_film = filmIterator->getNumeFilm();
                for (int i = 0; (unsigned long long)i < cod_film.length(); ++i)
                {
                    if (cod_film[i] == ' ')
                    {
                        cod_film[i] = '_';
                    }
                }
            }
            else
            {
                index = std::stoi(tasta) - 1;
                std::cout << "Ati selectat " << filme[index].getNumeFilm() << "\n";
                cod_film = filme[index].getNumeFilm();
                for (int i = 0; (unsigned long long)i < cod_film.length(); ++i)
                {
                    if (cod_film[i] == ' ')
                    {
                        cod_film[i] = '_';
                    }
                }
            }
        citeste_zi:
            std::cout
                << "\nApasati tasta corespunzatoare zilei dorite:\n1.Luni\n2.Marti\n3.Miercuri\n4.Joi\n5.Vineri\n6.Sambata\n7.Duminica\nApasati tasta 0 pentru a merge inapoi.\n";
            tasta = conversieExtinsa(f);
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
            tasta = conversieExtinsa(f);
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
            id_sala = std::stoi(tasta) % 2 + 1;
            cod_sala = std::to_string(id_sala);
            if (id_sala == 1)
            {
                for (int i = 0; i < 63; ++i)
                {
                    loc[i] = S1.getLocuriOcupate()[i];
                }
            }
            else
            {
                for (int i = 0; i < 63; ++i)
                {
                    loc[i] = S2.getLocuriOcupate()[i];
                }
            }
            std::cout << "\nLocurile disponibile sunt marcate cu 0, locurile ocupate sunt marcate cu 1.\n";
            std::cout << "Pentru a alege locul tastati randul urmat de tasta Enter apoi numarul scaunului.\n\n";
            std::cout << " __";
            for (int j = 0; j < 9; ++j)
            {
                std::cout << "__";
            }
            std::cout << "__ ";
            std::cout << "\n\n\n   ";
            for (int j = 0; j < 9; ++j)
            {
                std::cout << j + 1 << " ";
            }
            std::cout << "\n";
            for (int i = 0; i < 7; ++i)
            {
                std::cout << i + 1 << "  ";
                for (int j = 0; j < 9; ++j)
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
                x = std::stoi(conversieExtinsa(f));
                y = std::stoi(conversieExtinsa(f));
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
                    auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[nr_bilete]);
                    bilet_normal->setRand(0);
                    bilet_normal->setColoana(0);
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
                auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[nr_bilete]);
                bilet_normal->setRand(x);
                bilet_normal->setColoana(y);
                loc[(bilet_normal->getRand() - 1) * 9 + (bilet_normal->getColoana() - 1)] = 2;
                nr_bilete++;
                k = 0;
                std::cout << "\nLocurile alese de dvs. sunt cele marcate cu 2:\n";
                std::cout << " __";
                for (int j = 0; j < 9; ++j)
                {
                    std::cout << "__";
                }
                std::cout << "__ ";
                std::cout << "\n\n\n   ";
                for (int j = 0; j < 9; ++j)
                {
                    std::cout << j + 1 << " ";
                }
                std::cout << "\n";
                for (int i = 0; i < 7; ++i)
                {
                    std::cout << i + 1 << "  ";
                    for (int j = 0; j < 9; ++j)
                    {
                        bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[k]);
                        if (bilet_normal->getRand() == i + 1 and bilet_normal->getColoana() == j + 1 and k < nr_bilete)
                        {
                            ++k;
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
            for (int i = 0; i < nr_bilete; ++i)
            {
                auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[i]);
                loc[(bilet_normal->getRand() - 1) * 9 + (bilet_normal->getColoana() - 1)] = 1;
            }
        upgrade_bilet:
            std::cout << "\nBiletele dvs. sunt urmatoarele:\n";
            for (int i = 0; i < nr_bilete; ++i)
            {
                std::cout << i + 1 << ".";
                auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[i]);
                bilet_normal->afiseaza();
                std::cout << std::endl;
            }
            std::cout
                << "\nDoriti sa upgradati sau sa downgradati un bilet? Apasati tasta corespunzatoare:\n1.Nu, multumesc (mergeti la plata)\n2.Vreau sa upgradez un bilet normal la bilet 4DX (45 lei)\n3.Vreau sa adaug/elimin beneficii pentru un bilet 4Dx\n4.Vreau sa upgradez un bilet normal la bilet VIP (60 lei)\n5.Vreau sa adaug/elimin beneficii pentru un bilet VIP\n6.Vreau sa downgradez un bilet 4Dx sau VIP sau Derivat la bilet normal (25 lei)\n";
            tasta = conversieExtinsa(f);
            if (std::stoi(tasta) < 1 || std::stoi(tasta) > 6)
            {
                std::cout << "\nVa rugam apasati o tasta valida.\n";
                goto upgrade_bilet;
            }
            if (std::stoi(tasta) == 1)
            {
                std::cout << "\nAti ales sa nu modificati biletele.\n";
                goto plata;
            }
            if (std::stoi(tasta) == 2)
            {
                std::cout << "\nAlegeti biletul pe care doriti sa il upgradati la 4Dx:\n";
                for (int i = 0; i < nr_bilete; ++i)
                {
                    std::cout << i + 1 << ".";
                    auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[i]);
                    bilet_normal->afiseaza();
                    std::cout << std::endl;
                }
                tasta = conversieExtinsa(f);
                index = std::stoi(tasta) - 1;
                if (index >= nr_bilete || index < 0)
                {
                    std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                    goto upgrade_bilet;
                }
                std::cout << "\nAti ales biletul " << tasta;
                if (bilete[index]->getType() == "4Dx" || bilete[index]->getType() == "VIP"
                    || bilete[index]->getType() == "Derivat")
                {
                    std::cout << ". Biletul nu poate fi upgradat pentru ca e un bilet " << bilete[index]->getType()
                              << ".\n";
                    goto upgrade_bilet;
                }
                if (bilete[index]->getType() == std::string("Normal"))
                {
                    auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[index]);
                    bilete[index] = Bilet_4Dx::upgradeBilet4Dx(bilet_normal->getRand(), bilet_normal->getColoana());
                    delete bilet_normal;
                    std::cout << ". Biletul a fost upgradat la 4Dx.\n";
                    goto upgrade_bilet;
                }
            }
            if (std::stoi(tasta) == 3)
            {
                std::cout << "\nAlegeti biletul 4Dx pentru care doriti sa adaugati/eliminati beneficii:\n";
                for (int i = 0; i < nr_bilete; ++i)
                {
                    std::cout << i + 1 << ".";
                    auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[i]);
                    bilet_normal->afiseaza();
                    std::cout << std::endl;
                }
                tasta = conversieExtinsa(f);
                index = std::stoi(tasta) - 1;
                if (index >= nr_bilete || index < 0)
                {
                    std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                    goto upgrade_bilet;
                }
                std::cout << "\nAti ales biletul " << tasta << ".\n";
                if (bilete[index]->getType() == "Normal" || bilete[index]->getType() == "VIP"
                    || bilete[index]->getType() == "Derivat")
                {
                    std::cout << "Biletul nu poate fi modificat pentru ca nu e un bilet 4Dx.\n";
                    goto upgrade_bilet;
                }
                if (bilete[index]->getType() == "4Dx")
                {
                    std::cout << "\nApasati tasta corespunzatoare:\n1.";
                    auto *p4Dx = dynamic_cast<Bilet_4Dx *>(bilete[index]);
                    if (p4Dx->getScaunMiscator())
                    {
                        std::cout << "elimina";
                    }
                    else
                    {
                        std::cout << "adauga";
                    }
                    std::cout << " scaun_miscator (10 lei)\n2.";
                    if (p4Dx->getScaunSuflator())
                    {
                        std::cout << "elimina";
                    }
                    else
                    {
                        std::cout << "adauga";
                    }
                    std::cout << " scaun_suflator (10 lei)\n";
                    tasta = conversieExtinsa(f);
                    index = std::stoi(tasta);
                    if (index < 0 || index > 2)
                    {
                        std::cout << "Va rugam apasati o tasta valida.";
                        goto upgrade_bilet;
                    }
                    if (index == 1)
                    {
                        if (p4Dx->getScaunMiscator())
                        {
                            p4Dx->setScaunMiscator(false);
                            p4Dx->setPret4Dx(p4Dx->getPret() - 10);
                        }
                        else
                        {
                            p4Dx->setScaunMiscator(true);
                            p4Dx->setPret4Dx(p4Dx->getPret() + 10);
                        }
                    }
                    if (index == 2)
                    {
                        if (p4Dx->getScaunSuflator())
                        {
                            p4Dx->setScaunSuflator(false);
                            p4Dx->setPret4Dx(p4Dx->getPret() - 10);
                        }
                        else
                        {
                            p4Dx->setScaunSuflator(true);
                            p4Dx->setPret4Dx(p4Dx->getPret() + 10);
                        }
                    }
                    std::cout << "\nBeneficiile biletului 4Dx au fost modificate.\n";
                    goto upgrade_bilet;
                }
            }
            if (std::stoi(tasta) == 4)
            {
                std::cout << "\nAlegeti biletul pe care doriti sa il upgradati la VIP:\n";
                for (int i = 0; i < nr_bilete; ++i)
                {
                    std::cout << i + 1 << ".";
                    auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[i]);
                    bilet_normal->afiseaza();
                    std::cout << std::endl;
                }
                tasta = conversieExtinsa(f);
                index = std::stoi(tasta) - 1;
                if (index >= nr_bilete || index < 0)
                {
                    std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                    goto upgrade_bilet;
                }
                std::cout << "\nAti ales biletul " << tasta;
                if (bilete[index]->getType() == "4Dx" || bilete[index]->getType() == "VIP"
                    || bilete[index]->getType() == "Derivat")
                {
                    std::cout << ". Biletul nu poate fi upgradat pentru ca e un bilet " << bilete[index]->getType()
                              << ".\n";
                    goto upgrade_bilet;
                }
                if (bilete[index]->getType() == std::string("Normal"))
                {
                    auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[index]);
                    bilete[index] = Bilet_VIP::upgradeBiletVIP(bilet_normal->getRand(), bilet_normal->getColoana());
                    delete bilet_normal;
                    std::cout << ". Biletul a fost upgradat la VIP.\n";
                    goto upgrade_bilet;
                }
            }
            if (std::stoi(tasta) == 5)
            {
                std::cout << "\nAlegeti biletul VIP pentru care doriti sa adaugati/eliminati beneficii:\n";
                for (int i = 0; i < nr_bilete; ++i)
                {
                    std::cout << i + 1 << ".";
                    auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[i]);
                    bilet_normal->afiseaza();
                    std::cout << std::endl;
                }
                tasta = conversieExtinsa(f);
                index = std::stoi(tasta) - 1;
                if (index >= nr_bilete || index < 0)
                {
                    std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                    goto upgrade_bilet;
                }
                std::cout << "\nAti ales biletul " << tasta << ".\n";
                if (bilete[index]->getType() == "Normal" || bilete[index]->getType() == "4Dx"
                    || bilete[index]->getType() == "Derivata")
                {
                    std::cout << "Biletul nu poate fi modificat pentru ca nu e un bilet VIP.\n";
                    goto upgrade_bilet;
                }
                if (bilete[index]->getType() == "VIP")
                {
                    std::cout << "\nApasati tasta corespunzatoare:\n1.";
                    auto *pVIP = dynamic_cast<Bilet_VIP *>(bilete[index]);
                    if (pVIP->getPopcornGratis())
                    {
                        std::cout << "elimina";
                    }
                    else
                    {
                        std::cout << "adauga";
                    }
                    std::cout << " popcorn_gratis (25 lei)\n2.";
                    if (pVIP->getBauturiGratis())
                    {
                        std::cout << "elimina";
                    }
                    else
                    {
                        std::cout << "adauga";
                    }
                    std::cout << " bauturi_gratis (10 lei)\n";
                    tasta = conversieExtinsa(f);
                    index = std::stoi(tasta);
                    if (index < 0 || index > 2)
                    {
                        std::cout << "Va rugam apasati o tasta valida.";
                        goto upgrade_bilet;
                    }
                    if (index == 1)
                    {
                        if (pVIP->getPopcornGratis())
                        {
                            pVIP->setPopcornGratis(false);
                            pVIP->setPretVIP(pVIP->getPret() - 25);
                        }
                        else
                        {
                            pVIP->setPopcornGratis(true);
                            pVIP->setPretVIP(pVIP->getPret() + 25);
                        }
                    }
                    if (index == 2)
                    {
                        if (pVIP->getBauturiGratis())
                        {
                            pVIP->setBauturiGratis(false);
                            pVIP->setPretVIP(pVIP->getPret() - 10);
                        }
                        else
                        {
                            pVIP->setBauturiGratis(true);
                            pVIP->setPretVIP(pVIP->getPret() + 10);
                        }
                    }
                    std::cout << "\nBeneficiile biletului 4Dx au fost modificate.\n";
                    goto upgrade_bilet;
                }
            }
            if (std::stoi(tasta) == 6)
            {
                std::cout << "\nAlegeti biletul pe care doriti sa il downgradati:\n";
                for (int i = 0; i < nr_bilete; ++i)
                {
                    std::cout << i + 1 << ".";
                    auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[i]);
                    bilet_normal->afiseaza();
                    std::cout << std::endl;
                }
                tasta = conversieExtinsa(f);
                index = std::stoi(tasta) - 1;
                if (index >= nr_bilete || index < 0)
                {
                    std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                    goto upgrade_bilet;
                }
                std::cout << "\nAti ales biletul " << tasta;
                if (bilete[index]->getType() == "Normal")
                {
                    std::cout << ". Biletul nu poate fi downgradat pentru ca e un bilet normal.\n";
                    goto upgrade_bilet;
                }
                if (bilete[index]->getType() == "4Dx")
                {
                    auto *p4Dx = dynamic_cast<Bilet_4Dx *>(bilete[index]);
                    bilete[index] = Bilet_Normal<int>::downgradeBilet(p4Dx->getRand(), p4Dx->getColoana());
                    delete p4Dx;
                    std::cout << ". Biletul a fost downgradat la Normal.\n";
                    goto upgrade_bilet;
                }
                if (bilete[index]->getType() == "VIP")
                {
                    auto *pVIP = dynamic_cast<Bilet_VIP *>(bilete[index]);
                    bilete[index] = Bilet_Normal<int>::downgradeBilet(pVIP->getRand(), pVIP->getColoana());
                    delete pVIP;
                    std::cout << ". Biletul a fost downgradat la Normal.\n";
                    goto upgrade_bilet;
                }
            }
        plata:
            for (int i = 0; i < nr_bilete; ++i)
            {
                auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[i]);
                suma += bilet_normal->getPret();
            }
            std::cout << "\nDe platit: " << suma << " lei\nNumarul cardului [16 cifre]: ";
            f.get();
            std::getline(f, nr_card);
            std::cout << nr_card << "\n";
            if (!nrCard(nr_card))
            {
                std::cout << "Numarul cardului introdus nu este valid.\n";
                goto plata;
            }
            std::cout << "Numele titularului: ";
            std::getline(f, nume_titular);
            std::cout << nume_titular << "\n";
            std::cout << "Data expirarii [MM/YY]: ";
            f >> data_exp;
            std::cout << data_exp << "\n";
            if (!dataExp(data_exp))
            {
                std::cout << "Data introdusa nu este valida.\n";
                goto plata;
            }
            std::cout << "CCV [3 cifre]: ";
            ccv = std::stoi(conversieExtinsa(f));
            std::cout << ccv << "\n";
            if (!ccvCode(std::to_string(ccv)))
            {
                std::cout << "CCV-ul introdus nu este valid.\n";
                goto plata;
            }
            if (nr_bilete == 1)
            {
                auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[0]);
                std::cout << "\n\nCodul biletului dvs. este: C" << cod_cinema << "|F" << cod_film << "|Z" << cod_zi << "|O"
                          << cod_ora << "|S" << cod_sala << "|R" << bilet_normal->getRand() << "|C"
                          << bilet_normal->getColoana()
                          << "|B" << bilet_normal->getType();
                if (bilete[0]->getType() == "4Dx")
                {
                    auto *p4Dx = dynamic_cast<Bilet_4Dx *>(bilete[0]);
                    std::cout << "|P";
                    if (p4Dx->getScaunMiscator())
                        std::cout << "SM";
                    else
                        std::cout << "__";
                    if (p4Dx->getScaunSuflator())
                        std::cout << "SS";
                    else
                        std::cout << "__";
                }
                if (bilete[0]->getType() == "VIP")
                {
                    auto *pVIP = dynamic_cast<Bilet_VIP *>(bilete[0]);
                    std::cout << "|P";
                    if (pVIP->getPopcornGratis())
                        std::cout << "PG";
                    else
                        std::cout << "__";
                    if (pVIP->getBauturiGratis())
                        std::cout << "BG";
                    else
                        std::cout << "__";
                }
                std::cout << "\n";
            }
            else
            {
                std::cout << "\n\nCodurile biletelor dvs. sunt:\n";
                for (int i = 0; i < nr_bilete; ++i)
                {
                    auto *bilet_normal = dynamic_cast<Bilet_Normal<int> *>(bilete[i]);
                    std::cout << "C" << cod_cinema << "|F" << cod_film << "|Z" << cod_zi << "|O" << cod_ora << "|S"
                              << cod_sala << "|R" << bilet_normal->getRand() << "|C" << bilet_normal->getColoana() << "|B"
                              << bilet_normal->getType();
                    if (bilete[i]->getType() == "4Dx")
                    {
                        auto *p4Dx = dynamic_cast<Bilet_4Dx *>(bilete[i]);
                        std::cout << "|P";
                        if (p4Dx->getScaunMiscator())
                            std::cout << "SM";
                        else
                            std::cout << "__";
                        if (p4Dx->getScaunSuflator())
                            std::cout << "SS";
                        else
                            std::cout << "__";
                    }
                    if (bilete[i]->getType() == "VIP")
                    {

                        auto *pVIP = dynamic_cast<Bilet_VIP *>(bilete[i]);
                        std::cout << "|P";
                        if (pVIP->getPopcornGratis())
                            std::cout << "PG";
                        else
                            std::cout << "__";
                        if (pVIP->getBauturiGratis())
                            std::cout << "BG";
                        else
                            std::cout << "__";
                    }
                    std::cout << "\n";
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
            if (authenticate(credentials, username, parola))
            {
                std::cout << "\n\nBuna, " << username;
            }
            else
            {
                std::cout << "\n\nNume sau parola gresita.";
                goto client_sau_admin;
            }
        actiuni_admin:
            std::cout
                << "\n0.Iesiti\n1.Adaugati un film. [input: nume 'enter' rating]\n2.Stergeti un film. [input: nume]\n3.Schimba rating-ul unui film. [input: nume 'enter' rating]\n4.Afiseaza lista filmelor.\n";
            tasta = conversieExtinsa(f);
            if (std::stoi(tasta) == 0)
            {
                goto client_sau_admin;
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
                std::cout << "Ati selectat " << nouFilm << " (" << std::fixed << std::setprecision(1) << rating
                          << "). Filmul a fost adaugat cu succes.\n";
                for (auto &cinema : cinemauri)
                {
                    cinema.adaugaFilm(nouFilm, rating);
                }
                goto actiuni_admin;
            }
            if (std::stoi(tasta) == 2)
            {
                f.get();
                std::string nouFilm;
                std::getline(f, nouFilm);
                std::cout << "Ati selectat " << nouFilm << ". ";
                for (auto &cinema : cinemauri)
                {
                    cinema.stergeFilm(nouFilm);
                }
                goto actiuni_admin;
            }
            if (std::stoi(tasta) == 3)
            {
                f.get();
                std::string nouFilm;
                std::getline(f, nouFilm);
                double nouRating;
                f >> nouRating;
                std::cout << "Ati selectat " << nouFilm << " (" << nouRating << "). ";
                for (auto &cinema : cinemauri)
                {
                    cinema.schimbaRating(nouFilm, nouRating);
                }
                goto actiuni_admin;
            }
            if (std::stoi(tasta) == 4)
            {
                int it = 1;
                for (const auto &film : cinemauri[0].getFilmeDifuzate())
                {
                    std::cout << it++ << "." << film.getNumeFilm() << " (" << std::fixed
                              << std::setprecision(1) << film.getRating() << ")\n";
                }
                goto actiuni_admin;
            }
        }
    exit:
        std::cout << "\nLa revedere!\n";
        for (Bilet *bilet : bilete)
        {
            delete bilet;
        }
        bilete.clear();
    }
};


int
main()
{
    application::get_app().meniu();
}
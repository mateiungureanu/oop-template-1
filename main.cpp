#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <iomanip>

#include "Sala.h"
#include "Cinema.h"
#include "Film.h"
#include "Bilet.h"
#include "Bilet_Normal.h"
#include "Bilet_4Dx.h"
#include "Bilet_VIP.h"

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
    int id_sala, k, loc[63], x, y, nr_bilete = 0, suma = 0, ccv, index;
    std::string tasta, cod_cinema, cod_film, cod_zi, cod_ora, cod_sala, nr_card, nume_titular, data_exp;
    std::array<Cinema, 3> cinemauri{};
    cinemauri[0].setNumeMall("Afi Cotroceni");
    cinemauri[1].setNumeMall("Park Lake");
    cinemauri[2].setNumeMall("Mega Mall");
    for (int i = 0; i < 3; ++i)
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
    std::vector<Bilet*> bilete;
    for (int i = 0; i<63; ++i)
    {
        bilete.emplace_back(new Bilet_Normal);
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
            std::cout << i + 1 << "." << cinemauri[0].getFilmeDifuzate()[i].getNumeFilm() << " (" << std::fixed
                      << std::setprecision(1) << cinemauri[0].getFilmeDifuzate()[i].getRating() << ")\n";
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
            for (int i = 0; i < 63; ++i)
            {
                loc[i] = S1->getLocuriOcupate()[i];
            }
        }
        else
        {
            for (int i = 0; i < 63; ++i)
            {
                loc[i] = S2->getLocuriOcupate()[i];
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
                auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[nr_bilete]);
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
            auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[nr_bilete]);
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
                    bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[k]);
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
            auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[nr_bilete]);
            loc[(bilet_normal->getRand() - 1) * 9 + (bilet_normal->getColoana() - 1)] = 1;
        }
    upgrade_bilet:
        std::cout << "\nBiletele dvs. sunt urmatoarele:\n";
        for (int i = 0; i < nr_bilete; ++i)
        {
            std::cout << i + 1 << ".";
            auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[i]);
            bilet_normal->afiseaza();
            std::cout << std::endl;
        }
        std::cout
            << "\nDoriti sa upgradati sau sa downgradati un bilet? Apasati tasta corespunzatoare:\n1.Nu, multumesc (mergeti la plata)\n2.Vreau sa upgradez un bilet normal la bilet 4DX (45 lei)\n3.Vreau sa adaug/elimin beneficii pentru un bilet 4Dx\n4.Vreau sa upgradez un bilet normal la bilet VIP (60 lei)\n5.Vreau sa adaug/elimin beneficii pentru un bilet VIP\n6.Vreau sa downgradez un bilet 4Dx sau VIP la bilet normal (25 lei)\n";
        f >> tasta;
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
                auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[i]);
                bilet_normal->afiseaza();
                std::cout << std::endl;
            }
            f >> tasta;
            index = std::stoi(tasta) - 1;
            if (index >= nr_bilete || index < 0)
            {
                std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                goto upgrade_bilet;
            }
            std::cout << "\nAti ales biletul " << tasta;
            if (bilete[index]->getType() == "4Dx" || bilete[index]->getType() == "VIP")
            {
                std::cout << ". Biletul nu poate fi upgradat pentru ca e un bilet " << bilete[index]->getType()
                          << ".\n";
                goto upgrade_bilet;
            }
            if (bilete[index]->getType() == std::string("Normal"))
            {
                auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[index]);
                bilete[index] = Bilet_4Dx::upgradeBilet4Dx(bilet_normal->getRand(), bilet_normal->getColoana());
                delete bilet_normal;
                std::cout << ". Biletul a fost upgradat la 4Dx.\n";
                goto upgrade_bilet;
            }
        }
        if (std::stoi(tasta) == 3)
        {
            std::cout << "\nlegeti biletul 4Dx pentru care doriti sa adaugati/eliminati beneficii:\n";
            for (int i = 0; i < nr_bilete; ++i)
            {
                std::cout << i + 1 << ".";
                auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[i]);
                bilet_normal->afiseaza();
                std::cout << std::endl;
            }
            f >> tasta;
            index = std::stoi(tasta) - 1;
            if (index >= nr_bilete || index < 0)
            {
                std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                goto upgrade_bilet;
            }
            std::cout << "\nAti ales biletul " << tasta << ".\n";
            if (bilete[index]->getType() == "Normal" || bilete[index]->getType() == "VIP")
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
                    std::cout << "adauga";
                }
                else
                {
                    std::cout << "elimina";
                }
                std::cout << " scaun_miscator\n2.";
                if (p4Dx->getScaunSuflator())
                {
                    std::cout << "adauga";
                }
                else
                {
                    std::cout << "elimina";
                }
                std::cout << " scaun_suflator\n";
                f >> tasta;
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
                auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[i]);
                bilet_normal->afiseaza();
                std::cout << std::endl;
            }
            f >> tasta;
            index = std::stoi(tasta) - 1;
            if (index >= nr_bilete || index < 0)
            {
                std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                goto upgrade_bilet;
            }
            std::cout << "\nAti ales biletul " << tasta;
            if (bilete[index]->getType() == "4Dx" || bilete[index]->getType() == "VIP")
            {
                std::cout << ". Biletul nu poate fi upgradat pentru ca e un bilet " << bilete[index]->getType()
                          << ".\n";
                goto upgrade_bilet;
            }
            if (bilete[index]->getType() == std::string("Normal"))
            {
                auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[index]);
                bilete[index] = Bilet_VIP::upgradeBiletVIP(bilet_normal->getRand(), bilet_normal->getColoana());
                delete bilet_normal;
                std::cout << ". Biletul a fost upgradat la VIP.\n";
                goto upgrade_bilet;
            }
        }
        if (std::stoi(tasta) == 5)
        {
            std::cout << "\nlegeti biletul VIP pentru care doriti sa adaugati/eliminati beneficii:\n";
            for (int i = 0; i < nr_bilete; ++i)
            {
                std::cout << i + 1 << ".";
                auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[i]);
                bilet_normal->afiseaza();
                std::cout << std::endl;
            }
            f >> tasta;
            index = std::stoi(tasta) - 1;
            if (index >= nr_bilete || index < 0)
            {
                std::cout << "\nVa rugam apasati o tasta intre 0 si numarul de bilete alese.\n";
                goto upgrade_bilet;
            }
            std::cout << "\nAti ales biletul " << tasta << ".\n";
            if (bilete[index]->getType() == "Normal" || bilete[index]->getType() == "4Dx")
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
                    std::cout << "adauga";
                }
                else
                {
                    std::cout << "elimina";
                }
                std::cout << " popcorn_gratis\n2.";
                if (pVIP->getBauturiGratis())
                {
                    std::cout << "adauga";
                }
                else
                {
                    std::cout << "elimina";
                }
                std::cout << " bauturi_gratis\n";
                f >> tasta;
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
                        pVIP->setBauturiGratis(true);
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
                auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[i]);
                bilet_normal->afiseaza();
                std::cout << std::endl;
            }
            f >> tasta;
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
                bilete[index] = Bilet_Normal::downgradeBilet(p4Dx->getRand(), p4Dx->getColoana());
                delete p4Dx;
                std::cout << ". Biletul a fost downgradat la Normal.\n";
                goto upgrade_bilet;
            }
            if (bilete[index]->getType() == "VIP")
            {
                auto *pVIP = dynamic_cast<Bilet_VIP *>(bilete[index]);
                bilete[index] = Bilet_Normal::downgradeBilet(pVIP->getRand(), pVIP->getColoana());
                delete pVIP;
                std::cout << ". Biletul a fost downgradat la Normal.\n";
                goto upgrade_bilet;
            }
        }
    plata:
        for (int i = 0; i < nr_bilete; ++i)
        {
            auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[i]);
            suma += bilet_normal->getPret();
        }
        std::cout << "\nDe platit: " << suma << " lei\nNumarul cardului [12 cifre]: ";
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
            auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[0]);
            std::cout << "\n\nCodul biletului dvs. este: C" << cod_cinema << "|F" << cod_film << "|Z" << cod_zi << "|O"
                      << cod_ora << "|S" << cod_sala << "|R" << bilet_normal->getRand() << "|C" << bilet_normal->getColoana()
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
                auto* bilet_normal = dynamic_cast<Bilet_Normal*>(bilete[i]);
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
        std::cout << "\n\nBuna, " << username;
    actiuni_admin:
        std::cout << "\n0.Iesiti\n1.Adaugati un film. [input: nume 'enter' rating]\n2.Stergeti un film. [input: nume]\n3.Schimba rating-ul unui film. [input: nume 'enter' rating]\n4.Afiseaza lista filmelor.\n";
        f >> tasta;
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
            std::cout << "Ati selectat " << nouFilm << " (" << std::fixed << std::setprecision(1) << rating << ").";
            cinemauri[0].adaugaFilm(nouFilm, rating);
            if (cinemauri[0].getNrFilme() > cinemauri[1].getNrFilme())
            {
                std::cout << " Filmul a fost adaugat cu succes.\n";
                for (int i = 1; i < 3; ++i)
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
                for (int i = 1; i < 3; ++i)
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
            index = -1;
            for (int i = 0; i < cinemauri[0].getNrFilme(); ++i)
            {
                if (cinemauri[0].getFilmeDifuzate()[i].getNumeFilm() == nouFilm)
                {
                    index = i;
                    break;
                }
            }
            std::cout << "Ati selectat " << nouFilm << " (" << cinemauri[0].getFilmeDifuzate()[index].getRating()
                      << " -> " << std::fixed << std::setprecision(1) << nouRating << ").";
            cinemauri[0].schimbaRating(nouFilm, nouRating);
            if (index != -1 && cinemauri[0].getFilmeDifuzate()[index].getRating() !=
                cinemauri[1].getFilmeDifuzate()[index].getRating())
            {
                std::cout << " Rating-ul filmului a fost modificat cu succes.\n";
                for (int i = 1; i < 3; ++i)
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
                std::cout << i + 1 << "." << cinemauri[0].getFilmeDifuzate()[i].getNumeFilm() << " (" << std::fixed
                          << std::setprecision(1) << cinemauri[0].getFilmeDifuzate()[i].getRating() << ")\n";
            }
            goto actiuni_admin;
        }
    }
exit:
    std::cout << "\nLa revedere!\n";
    delete S1;
    delete S2;
    delete[] filme;
    for (Bilet* bilet : bilete)
    {
        delete bilet;
    }
    bilete.clear();
    return 0;
}

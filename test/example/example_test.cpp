#include <gtest/gtest.h>
#include <Film.h>
#include <Sala.h>
#include <Cinema.h>
#include <Bilet_Normal.h>
#include <Bilet_4Dx.h>
#include <Bilet_VIP.h>
#include "Bilet_Template.h"

TEST(FilmConstructor, ParametrizedConstructor)
{
    Film film("Film_Name", 8.2);
    EXPECT_EQ((double)8.2, film.getRating());
    EXPECT_EQ("Film_Name", film.getNumeFilm());
}

TEST(FilmConstructor, DefaultConstructor)
{
    Film film;
    EXPECT_EQ(0, film.getRating());
    EXPECT_EQ("", film.getNumeFilm());
}

TEST(FilmConstructor, CopyConstructor)
{
    Film film("FilmName", 7.3);
    Film copyFilm(film);
    EXPECT_EQ(film.getNumeFilm(), copyFilm.getNumeFilm());
    EXPECT_EQ(film.getRating(), copyFilm.getRating());
}

TEST(FilmSetterGetter, RatingSetterGetter)
{
    Film film("Film_Name", 8.2);
    film.setRating(9.0);
    EXPECT_DOUBLE_EQ(9.0, film.getRating());
}

TEST(FilmSetterGetter, NumeFilmSetterGetter)
{
    Film film("Film_Name", 8.2);
    film.setNumeFilm("Film_Name_New");
    EXPECT_EQ("Film_Name_New", film.getNumeFilm());
}

TEST(FilmOperatorEqual, EqualOperator)
{
    Film film1("Film_Name", 8.2);
    Film film2("Film_Name", 8.2);
    EXPECT_TRUE(film1 == film2);
}

TEST(FilmOperatorAssignment, AssignmentOperator)
{
    Film film1("Film_Name", 8.2);
    Film film2;
    film2 = film1;
    EXPECT_TRUE(film1 == film2);
}

TEST(FilmStreamOperators, OutputOperator)
{
    Film film("Film_Name", 9.0);
    std::stringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());
    std::cout << film;
    std::cout.rdbuf(oldCout);
    EXPECT_EQ("\nnume film: Film_Name (9.0)", output.str());
}

TEST(FilmComparison, LessThanOperator)
{
    Film film1("Film_Name_1", 8.0);
    Film film2("Film_Name_2", 9.0);
    EXPECT_TRUE(film1 < film2);
    EXPECT_FALSE(film2 < film1);
}

TEST(CinemaConstructor, ParametrizedConstructor)
{

    Cinema cinema(1, "Nume_Mall");
    EXPECT_EQ(1, cinema.getId());
    EXPECT_EQ("Nume_Mall", cinema.getNumeMall());
}

TEST(CinemaConstructor, DefaultConstructor)
{
    Cinema cinema;
    EXPECT_EQ(0, cinema.getId());
    EXPECT_EQ("", cinema.getNumeMall());
}

TEST(CinemaSetterGetter, IdSetterGetter)
{
    Cinema cinema;
    cinema.setId(1);
    EXPECT_EQ(1, cinema.getId());
}

TEST(CinemaSetterGetter, NumeMallSetterGetter)
{
    Cinema cinema;
    cinema.setNumeMall("Mall_Name");
    EXPECT_EQ("Mall_Name", cinema.getNumeMall());
}

TEST(CinemaSetterGetter, FilmeDifuzateSetterGetter)
{
    Cinema cinema;
    Film film("Film_Name", 8.0);
    std::set<Film> filmSet;
    filmSet.insert(film);
    cinema.setFilmeDifuzate(filmSet);
    EXPECT_EQ("Film_Name", cinema.getFilmeDifuzate().begin()->getNumeFilm());
    EXPECT_EQ(8.0, cinema.getFilmeDifuzate().begin()->getRating());
}

TEST(CinemaAddFilm, AdaugaFilm)
{
    Cinema cinema;
    cinema.adaugaFilm("Film_Name", 8.0);
    EXPECT_EQ("Film_Name", cinema.getFilmeDifuzate().begin()->getNumeFilm());
    EXPECT_EQ(8.0, cinema.getFilmeDifuzate().begin()->getRating());
}

TEST(CinemaRemoveFilm, StergeFilm)
{
    Cinema cinema;
    std::ostringstream oss;
    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    cinema.adaugaFilm("Film_Name", 8.0);
    cinema.stergeFilm("Film_Name");
    std::cout.rdbuf(coutBuffer);
    EXPECT_EQ("Filmul a fost sters cu succes.\n", oss.str());
    EXPECT_EQ(0, cinema.getFilmeDifuzate().size());
}

TEST(CinemaChangeRating, SchimbaRating)
{
    Cinema cinema;
    std::ostringstream oss;
    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    cinema.adaugaFilm("Film_Name", 8.0);
    cinema.schimbaRating("Film_Name", 8.5);
    std::cout.rdbuf(coutBuffer);
    EXPECT_EQ("Rating-ul filmului a fost modificat cu succes.\n", oss.str());
    EXPECT_EQ(8.5, cinema.getFilmeDifuzate().begin()->getRating());
}

TEST(CinemaCopyConstructor, CopyConstructor)
{
    Cinema cinema1;
    cinema1.adaugaFilm("Film_Name", 8.0);
    Cinema cinema2(cinema1);
    EXPECT_EQ("Film_Name", cinema2.getFilmeDifuzate().begin()->getNumeFilm());
    EXPECT_EQ(8.0, cinema2.getFilmeDifuzate().begin()->getRating());
}

TEST(CinemaAssignmentOperator, AssignmentOperator)
{
    Cinema cinema1;
    cinema1.adaugaFilm("Film_Name_1", 8.0);
    Cinema cinema2;
    cinema2 = cinema1;
    EXPECT_EQ("Film_Name_1", cinema2.getFilmeDifuzate().begin()->getNumeFilm());
    EXPECT_EQ(8.0, cinema2.getFilmeDifuzate().begin()->getRating());
}

TEST(CinemaAdditionOperator, AdditionOperator)
{
    Cinema cinema1;
    cinema1.adaugaFilm("Film_Name_1", 8.0);
    Cinema cinema2;
    cinema2.adaugaFilm("Film_Name_1", 8.0);
    cinema2.adaugaFilm("Film_Name_2", 9.0);
    Cinema cinema3 = cinema1 + cinema2;
    const std::set<Film>& filmeDifuzate = cinema3.getFilmeDifuzate();
    auto it = filmeDifuzate.begin();
    EXPECT_EQ("Film_Name_1", it->getNumeFilm());
    EXPECT_EQ(8.0, it->getRating());
    it++;
    EXPECT_EQ("Film_Name_2", it->getNumeFilm());
    EXPECT_EQ(9.0, it->getRating());
}

TEST(CinemaStreamOperators, InputOperator)
{
    std::istringstream input("1 Mall_Name");
    Cinema cinema;
    input >> cinema;
    EXPECT_EQ(1, cinema.getId());
    EXPECT_EQ("Mall_Name", cinema.getNumeMall());
}

TEST(CinemaStreamOperators, OutputOperator)
{
    Cinema cinema(1, "Mall_Name");
    std::set<Film> filmSet;
    filmSet.insert(Film("Film_Name", 8.0));
    cinema.setFilmeDifuzate(filmSet);
    std::ostringstream output;
    output << cinema;
    EXPECT_EQ("\nid: 1 nume mall: Mall_Name", output.str());
}

TEST(SalaConstructor, ParameterizedConstructor)
{
    std::vector<bool> locuriOcupate(63, false);
    SalaBuilder b;
    Sala sala = b.setId(1).setNrLocuri(63).setNrRanduri(9).setNrColoane(7).setLocuriOcupate(locuriOcupate).build();
    EXPECT_EQ(1, sala.getIdSala());
    EXPECT_EQ(63, sala.getNrLocuri());
    EXPECT_EQ(9, sala.getNrRanduri());
    EXPECT_EQ(7, sala.getNrColoane());
    EXPECT_EQ(locuriOcupate, sala.getLocuriOcupate());
}

TEST(SalaConstructor, DefaultConstructor)
{
    Sala sala;
    EXPECT_EQ(0, sala.getIdSala());
    EXPECT_EQ(0, sala.getNrLocuri());
    EXPECT_EQ(0, sala.getNrRanduri());
    EXPECT_EQ(0, sala.getNrColoane());
    EXPECT_TRUE(sala.getLocuriOcupate().empty());
}

TEST(SalaConstructor, CopyConstructor)
{
    std::vector<bool> locuriOcupate(63, false);
    SalaBuilder b;
    Sala sala1 = b.setId(1).setNrLocuri(63).setNrRanduri(9).setNrColoane(7).setLocuriOcupate(locuriOcupate).build();
    Sala sala2(sala1);
    EXPECT_EQ(sala1.getIdSala(), sala2.getIdSala());
    EXPECT_EQ(sala1.getNrLocuri(), sala2.getNrLocuri());
    EXPECT_EQ(sala1.getLocuriOcupate(), sala2.getLocuriOcupate());
}

TEST(SalaAssignmentOperator, AssignmentOperator)
{
    std::vector<bool> locuriOcupate(63, false);
    SalaBuilder b;
    Sala sala1 = b.setId(1).setNrLocuri(63).setNrRanduri(9).setNrColoane(7).setLocuriOcupate(locuriOcupate).build();
    Sala sala2;
    sala2 = sala1;
    EXPECT_EQ(sala1.getIdSala(), sala2.getIdSala());
    EXPECT_EQ(sala1.getNrLocuri(), sala2.getNrLocuri());
    EXPECT_EQ(sala1.getLocuriOcupate(), sala2.getLocuriOcupate());
}

TEST(SalaSetterGetter, IdSalaSetterGetter)
{
    Sala sala;
    sala.setIdSala(1);
    EXPECT_EQ(1, sala.getIdSala());
}

TEST(SalaSetterGetter, LocuriOcupateSetterGetter)
{
    Sala sala;
    std::vector<bool> locuriOcupate(63, false);
    sala.setLocuriOcupate(63, locuriOcupate);
    EXPECT_EQ(locuriOcupate, sala.getLocuriOcupate());
}

TEST(BiletNormalConstructor, ParameterizedConstructor)
{
    Bilet_Normal bilet(3, 5);
    EXPECT_EQ(3, bilet.getRand());
    EXPECT_EQ(5, bilet.getColoana());
    EXPECT_EQ(25, bilet.getPret());
}

TEST(BiletNormalConstructor, DefaultConstructor)
{
    Bilet_Normal bilet;
    EXPECT_EQ(0, bilet.getRand());
    EXPECT_EQ(0, bilet.getColoana());
    EXPECT_EQ(25, bilet.getPret());
}

TEST(BiletNormalConstructor, CopyConstructor)
{
    Bilet_Normal bilet(2, 4);
    Bilet_Normal copyBilet(bilet);
    EXPECT_EQ(bilet.getRand(), copyBilet.getRand());
    EXPECT_EQ(bilet.getColoana(), copyBilet.getColoana());
    EXPECT_EQ(bilet.getPret(), copyBilet.getPret());
}

TEST(BiletNormalSetterGetter, RandSetterGetter)
{
    Bilet_Normal bilet;
    bilet.setRand(7);
    EXPECT_EQ(7, bilet.getRand());
}

TEST(BiletNormalSetterGetter, ColoanaSetterGetter)
{
    Bilet_Normal bilet;
    bilet.setColoana(3);
    EXPECT_EQ(3, bilet.getColoana());
}

TEST(BiletNormalSetterGetter, PretSetterGetter)
{
    Bilet_Normal bilet;
    EXPECT_EQ(25, bilet.getPret());
}

TEST(BiletNormalAssignmentOperator, AssignmentOperator)
{
    Bilet_Normal bilet1(3, 6);
    Bilet_Normal bilet2;
    bilet2 = bilet1;
    EXPECT_EQ(bilet1.getRand(), bilet2.getRand());
    EXPECT_EQ(bilet1.getColoana(), bilet2.getColoana());
    EXPECT_EQ(bilet1.getPret(), bilet2.getPret());
}

TEST(BiletNormalGetType, GetTypeFunction)
{
    Bilet_Normal bilet;
    EXPECT_EQ("Normal", bilet.getType());
}

TEST(BiletNormalDowngradeBilet, DowngradeBiletFunction)
{
    Bilet_Template<int>* biletPtr = Bilet_Template<int>::downgradeBilet(4, 8);
    EXPECT_EQ(4, biletPtr->getRand());
    EXPECT_EQ(8, biletPtr->getColoana());
    EXPECT_EQ(25, biletPtr->getPret());
    delete biletPtr;
}

TEST(Bilet4DxConstructor, ParameterizedConstructorWithScaunMiscatorSuflator)
{
    Bilet_4Dx bilet(3, 5, true, false);
    EXPECT_EQ(3, bilet.getRand());
    EXPECT_EQ(5, bilet.getColoana());
    EXPECT_TRUE(bilet.getScaunMiscator());
    EXPECT_FALSE(bilet.getScaunSuflator());
    EXPECT_EQ(45, bilet.getPret());
}

TEST(Bilet4DxConstructor, ParameterizedConstructorWithoutScaunMiscatorSuflator)
{
    Bilet_4Dx bilet(3, 5);
    EXPECT_EQ(3, bilet.getRand());
    EXPECT_EQ(5, bilet.getColoana());
    EXPECT_TRUE(bilet.getScaunMiscator());
    EXPECT_TRUE(bilet.getScaunSuflator());
    EXPECT_EQ(45, bilet.getPret());
}

TEST(Bilet4DxConstructor, DefaultConstructor)
{
    Bilet_4Dx bilet;
    EXPECT_EQ(0, bilet.getRand());
    EXPECT_EQ(0, bilet.getColoana());
    EXPECT_TRUE(bilet.getScaunMiscator());
    EXPECT_TRUE(bilet.getScaunSuflator());
    EXPECT_EQ(45, bilet.getPret());
}

TEST(Bilet4DxConstructor, CopyConstructor)
{
    Bilet_4Dx bilet(2, 4, true, false);
    Bilet_4Dx copyBilet(bilet);
    EXPECT_EQ(bilet.getRand(), copyBilet.getRand());
    EXPECT_EQ(bilet.getColoana(), copyBilet.getColoana());
    EXPECT_EQ(bilet.getPret(), copyBilet.getPret());
    EXPECT_EQ(bilet.getScaunMiscator(), copyBilet.getScaunMiscator());
    EXPECT_EQ(bilet.getScaunSuflator(), copyBilet.getScaunSuflator());
}

TEST(Bilet4DxSetterGetter, ScaunMiscatorSetterGetter)
{
    Bilet_4Dx bilet;
    bilet.setScaunMiscator(false);
    EXPECT_FALSE(bilet.getScaunMiscator());
}

TEST(Bilet4DxSetterGetter, ScaunSuflatorSetterGetter)
{
    Bilet_4Dx bilet;
    bilet.setScaunSuflator(false);
    EXPECT_FALSE(bilet.getScaunSuflator());
}

TEST(Bilet4DxSetterGetter, Pret4DxSetterGetter)
{
    Bilet_4Dx bilet;
    bilet.setPret4Dx(50);
    EXPECT_EQ(50, bilet.getPret());
}


TEST(Bilet4DxAssignmentOperator, AssignmentOperator)
{
    Bilet_4Dx bilet1(3, 6, true, false);
    Bilet_4Dx bilet2;
    bilet2 = bilet1;
    EXPECT_EQ(bilet1.getRand(), bilet2.getRand());
    EXPECT_EQ(bilet1.getColoana(), bilet2.getColoana());
    EXPECT_EQ(bilet1.getPret(), bilet2.getPret());
    EXPECT_EQ(bilet1.getScaunMiscator(), bilet2.getScaunMiscator());
    EXPECT_EQ(bilet1.getScaunSuflator(), bilet2.getScaunSuflator());
}

TEST(Bilet4DxGetType, GetTypeFunction)
{
    Bilet_4Dx bilet;
    EXPECT_EQ("4Dx", bilet.getType());
}

TEST(Bilet4DxUpgradeBilet4Dx, UpgradeBilet4DxFunction)
{
    Bilet_4Dx* biletPtr = Bilet_4Dx::upgradeBilet4Dx(4, 8);
    EXPECT_EQ(4, biletPtr->getRand());
    EXPECT_EQ(8, biletPtr->getColoana());
    EXPECT_TRUE(biletPtr->getScaunMiscator());
    EXPECT_TRUE(biletPtr->getScaunSuflator());
    EXPECT_EQ(45, biletPtr->getPret());
    delete biletPtr;
}

TEST(BiletVIPConstructor, ParameterizedConstructorWithPopcornBauturiGratis)
{
    Bilet_VIP bilet(2, 3, true, false);
    EXPECT_EQ(2, bilet.getRand());
    EXPECT_EQ(3, bilet.getColoana());
    EXPECT_TRUE(bilet.getPopcornGratis());
    EXPECT_FALSE(bilet.getBauturiGratis());
    EXPECT_EQ(60, bilet.getPret());
}

TEST(BiletVIPConstructor, ParameterizedConstructorWithoutPopcornBauturiGratis)
{
    Bilet_VIP bilet(3, 5);
    EXPECT_EQ(3, bilet.getRand());
    EXPECT_EQ(5, bilet.getColoana());
    EXPECT_TRUE(bilet.getPopcornGratis());
    EXPECT_TRUE(bilet.getBauturiGratis());
    EXPECT_EQ(60, bilet.getPret());
}

TEST(BiletVIPConstructor, DefaultConstructor)
{
    Bilet_VIP bilet;
    EXPECT_EQ(0, bilet.getRand());
    EXPECT_EQ(0, bilet.getColoana());
    EXPECT_TRUE(bilet.getPopcornGratis());
    EXPECT_TRUE(bilet.getBauturiGratis());
    EXPECT_EQ(60, bilet.getPret());
}

TEST(BiletVIPConstructor, CopyConstructor)
{
    Bilet_VIP bilet(2, 3, true, false);
    Bilet_VIP copyBilet(bilet);
    EXPECT_EQ(bilet.getRand(), copyBilet.getRand());
    EXPECT_EQ(bilet.getColoana(), copyBilet.getColoana());
    EXPECT_EQ(bilet.getPopcornGratis(), copyBilet.getPopcornGratis());
    EXPECT_EQ(bilet.getBauturiGratis(), copyBilet.getBauturiGratis());
    EXPECT_EQ(bilet.getPret(), copyBilet.getPret());
}

TEST(BiletVIPSetterGetter, PopcornGratisSetterGetter)
{
    Bilet_VIP bilet;
    bilet.setPopcornGratis(false);
    EXPECT_FALSE(bilet.getPopcornGratis());
}

TEST(BiletVIPSetterGetter, BauturiGratisSetterGetter)
{
    Bilet_VIP bilet;
    bilet.setBauturiGratis(false);
    EXPECT_FALSE(bilet.getBauturiGratis());
}

TEST(BiletVIPSetterGetter, PretVIPSetterGetter)
{
    Bilet_VIP bilet;
    bilet.setPretVIP(70);
    EXPECT_EQ(70, bilet.getPret());
}

TEST(BiletVIPAssignmentOperator, AssignmentOperator)
{
    Bilet_VIP bilet(2, 3, true, false);
    Bilet_VIP biletCopy;
    biletCopy = bilet;
    EXPECT_EQ(bilet.getRand(), biletCopy.getRand());
    EXPECT_EQ(bilet.getColoana(), biletCopy.getColoana());
    EXPECT_EQ(bilet.getPopcornGratis(), biletCopy.getPopcornGratis());
    EXPECT_EQ(bilet.getBauturiGratis(), biletCopy.getBauturiGratis());
    EXPECT_EQ(bilet.getPret(), biletCopy.getPret());
}

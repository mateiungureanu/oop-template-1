#include <gtest/gtest.h>
#include <Film.h>
#include <Sala.h>
#include <Cinema.h>
#include <Bilet_Normal.h>
#include <Bilet_4Dx.h>
#include <Bilet_VIP.h>

TEST(FilmConstructor, DefaultConstructor)
{
    Film film;
    EXPECT_EQ(0, film.getRating());
    EXPECT_EQ("", film.getNumeFilm());
}

TEST(FilmConstructor, ParametrizedConstructor)
{
    Film film("Film_Name", 8.2);
    EXPECT_EQ((double)8.2, film.getRating());
    EXPECT_EQ("Film_Name", film.getNumeFilm());
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
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    std::cout << film;
    std::cout.rdbuf(oldCout);
    EXPECT_EQ("\nnume film: Film_Name (9.0)", output.str());
}

TEST(FilmComparison, LessThanOperator) {
    Film film1("Film_Name_1", 8.0);
    Film film2("Film_Name_2", 9.0);
    EXPECT_TRUE(Film::comparaFilme(film1, film2));
    EXPECT_FALSE(Film::comparaFilme(film2, film1));
}

TEST(CinemaConstructor, DefaultConstructor)
{
    Cinema cinema;
    EXPECT_EQ(0, cinema.getId());
    EXPECT_EQ("", cinema.getNumeMall());
    EXPECT_EQ(0, cinema.getNrFilme());
    EXPECT_EQ(nullptr, cinema.getFilmeDifuzate());
}

TEST(CinemaConstructor, ParametrizedConstructor)
{

    Cinema cinema(1,"Nume_Mall");
    EXPECT_EQ(1, cinema.getId());
    EXPECT_EQ("Nume_Mall", cinema.getNumeMall());
    EXPECT_EQ(0, cinema.getNrFilme());
    EXPECT_EQ(nullptr, cinema.getFilmeDifuzate());
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

TEST(CinemaSetterGetter, NrFilmeSetterGetter)
{
    Cinema cinema;
    cinema.setNrFilme(5);
    EXPECT_EQ(5, cinema.getNrFilme());
}

TEST(CinemaSetterGetter, FilmeDifuzateSetterGetter)
{
    Cinema cinema;
    Film film("Film_Name", 8.0);
    Film* filmArray = new Film[1];
    filmArray[0] = film;
    cinema.setFilmeDifuzate(1, filmArray);
    EXPECT_EQ(1, cinema.getNrFilme());
    EXPECT_EQ("Film_Name", cinema.getFilmeDifuzate()[0].getNumeFilm());
    EXPECT_EQ(8.0, cinema.getFilmeDifuzate()[0].getRating());
    delete[] filmArray;
}

TEST(CinemaAddFilm, AdaugaFilm)
{
    Cinema cinema;
    cinema.adaugaFilm("Film_Name", 8.0);
    EXPECT_EQ(1, cinema.getNrFilme());
    EXPECT_EQ("Film_Name", cinema.getFilmeDifuzate()[0].getNumeFilm());
    EXPECT_EQ(8.0, cinema.getFilmeDifuzate()[0].getRating());
}

TEST(CinemaRemoveFilm, StergeFilm)
{
    Cinema cinema;
    cinema.adaugaFilm("Film_Name", 8.0);
    cinema.stergeFilm("Film_Name");
    EXPECT_EQ(0, cinema.getNrFilme());
}

TEST(CinemaChangeRating, SchimbaRating)
{
    Cinema cinema;
    cinema.adaugaFilm("Film_Name", 8.0);
    cinema.schimbaRating("Film_Name", 9.0);
    EXPECT_EQ(9.0, cinema.getFilmeDifuzate()[0].getRating());
}

TEST(CinemaCopyConstructor, CopyConstructor)
{
    Cinema cinema1;
    cinema1.adaugaFilm("Film_Name", 8.0);
    Cinema cinema2(cinema1);
    EXPECT_EQ(1, cinema2.getNrFilme());
    EXPECT_EQ("Film_Name", cinema2.getFilmeDifuzate()[0].getNumeFilm());
    EXPECT_EQ(8.0, cinema2.getFilmeDifuzate()[0].getRating());
}

TEST(CinemaAssignmentOperator, AssignmentOperator)
{
    Cinema cinema1;
    cinema1.adaugaFilm("Film_Name_1", 8.0);
    Cinema cinema2;
    cinema2 = cinema1;
    EXPECT_EQ(1, cinema2.getNrFilme());
    EXPECT_EQ("Film_Name_1", cinema2.getFilmeDifuzate()[0].getNumeFilm());
    EXPECT_EQ(8.0, cinema2.getFilmeDifuzate()[0].getRating());
}

TEST(CinemaAdditionOperator, AdditionOperator)
{
    Cinema cinema1;
    cinema1.adaugaFilm("Film_Name_1", 8.0);
    Cinema cinema2;
    cinema2.adaugaFilm("Film_Name_1", 8.0);
    cinema2.adaugaFilm("Film_Name_2", 9.0);
    Cinema cinema3 = cinema1 + cinema2;
    EXPECT_EQ(2, cinema3.getNrFilme());
    EXPECT_EQ("Film_Name_1", cinema3.getFilmeDifuzate()[0].getNumeFilm());
    EXPECT_EQ(8.0, cinema3.getFilmeDifuzate()[0].getRating());
    EXPECT_EQ("Film_Name_2", cinema3.getFilmeDifuzate()[1].getNumeFilm());
    EXPECT_EQ(9.0, cinema3.getFilmeDifuzate()[1].getRating());
}

TEST(CinemaStreamOperators, InputOperator) {
    std::istringstream input("1 Mall_Name 5");
    Cinema cinema;
    input >> cinema;
    EXPECT_EQ(1, cinema.getId());
    EXPECT_EQ("Mall_Name", cinema.getNumeMall());
    EXPECT_EQ(5, cinema.getNrFilme());
}

TEST(CinemaStreamOperators, OutputOperator) {
    Cinema cinema(1, "Mall_Name");
    cinema.setNrFilme(5);
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    std::cout << cinema;
    std::cout.rdbuf(oldCout);
    EXPECT_EQ("\nid: 1 nume mall: Mall_Name numar sali: 5", output.str());
}


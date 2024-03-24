#include <gtest/gtest.h>
#include <Film.h>

TEST(FilmConstructor, DefaultConstructor)
{
    Film film;
    EXPECT_EQ(0, film.getRating());
    EXPECT_EQ("", film.getNumeFilm());
}

TEST(FilmConstructor, ParameterizedConstructor)
{
    Film film("Inception", 8.2);
    EXPECT_EQ((double)8.2, film.getRating());
    EXPECT_EQ("Inception", film.getNumeFilm());
}
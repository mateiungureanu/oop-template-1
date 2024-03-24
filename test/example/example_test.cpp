#include <gtest/gtest.h>
#include "../../Film.h"

TEST(FilmConstructor, DefaultConstructor) {
    Film film;
    EXPECT_EQ(0, film.getRating());
    EXPECT_EQ("", film.getNumeFilm());
}

TEST(FilmConstructor, ParameterizedConstructor) {
    Film film("Inception", 8.2);
    EXPECT_EQ(8.2, film.getRating());
    EXPECT_EQ("Inception", film.getNumeFilm());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


//#include <gtest/gtest.h>
//#include "Film.h" // Include your Film class header
//
//// Test case for Film constructor
//TEST(FilmConstructor, HandlesInitialization) {
//	std::string expectedName = "Inception";
//	float expectedRating = 8.8f;
//	Film testFilm(expectedName, expectedRating);
//
//	// Assert that the name and rating are correctly set
//	ASSERT_EQ(expectedName, testFilm.getNumeFilm());
//	ASSERT_EQ(expectedRating, testFilm.getRating());
//}


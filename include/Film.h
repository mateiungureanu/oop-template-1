#ifndef FILM_H
#define FILM_H

#include <string>
#include <iostream>

class Film {
private:
	std::string numeFilm;
	float rating;

public:
	friend class Cinema;
	Film(std::string numeFilm, float rating);
	Film();
	~Film() = default;

	void setRating(float rating);
	void setNumeFilm(std::string numeFilm);

	[[nodiscard]] float getRating() const;
	[[nodiscard]] std::string getNumeFilm() const;

	bool operator==(const Film& film);
	Film& operator=(const Film &aux);
	friend std::ostream& operator<<(std::ostream& out, const Film& film);
	static bool comparaFilme(const Film& a, const Film& b);
};

#endif

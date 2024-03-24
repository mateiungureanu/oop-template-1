#include "Film.h"


Film::Film(std::string numeFilm, float rating) {
	this->numeFilm = numeFilm;
	this->rating = rating;
	}
Film::Film() {
	this->numeFilm = "";
	this->rating = 0;
}
void Film::setRating(float rating){
	this->rating = rating;
}
void Film::setNumeFilm(std::string numeFilm) {
	this->numeFilm = numeFilm;
}
float Film::getRating() const{
	return rating;
}
std::string Film::getNumeFilm() const{
	return numeFilm;
}
bool Film::operator==(const Film& film) {
	if(this->numeFilm == film.numeFilm and this->rating == film.rating)
		return true;
	else
		return false;
}
Film& Film::operator=(const Film &aux) {
	if (this == &aux) {
		return *this;
	}
	this->numeFilm = aux.numeFilm;
	this->rating = aux.rating;
	return *this;
}
std::ostream& operator<<(std::ostream& out, const Film& film) {
	out << "\nnume film: " << film.numeFilm;
	out << "\nrating: " << film.rating;
	return out;
}
bool Film::comparaFilme(const Film& a, const Film& b) {
	return a.numeFilm < b.numeFilm;
}

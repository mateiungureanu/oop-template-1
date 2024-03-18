#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
class Sala {
private:
    int id;
    int nrLocuri;
    int nrRanduri;
    int nrColoane;
    bool *locuriOcupate;
public:
    Sala(int id) {
        this->id = id;
        this->nrLocuri = 70;
        this->nrRanduri = 10;
        this->nrColoane = 7;
        locuriOcupate = new bool[nrLocuri];
        for (int i = 0; i < nrLocuri; i++)
            locuriOcupate[i] = false;
    }

    Sala() {
        this->id = 0;
        this->nrLocuri = 0;
        this->nrRanduri = 0;
        this->nrColoane = 0;
        locuriOcupate = nullptr;
    }

    ~Sala() {
        id = 0;
        nrLocuri = 0;
        nrRanduri = 0;
        nrColoane = 0;
        if (locuriOcupate != nullptr)
            delete[] locuriOcupate;
//        locuriOcupate = nullptr;
    }
    Sala(const Sala& other) {
        id = other.id;
        nrLocuri = other.nrLocuri;
        nrRanduri = other.nrRanduri;
        nrColoane = other.nrColoane;
        if(locuriOcupate == nullptr)
            locuriOcupate = new bool[other.nrLocuri];
        for (int i = 0; i < other.nrLocuri; i++)
            locuriOcupate[i] = other.locuriOcupate[i];
    }
    Sala& operator=(const Sala& other) {
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
//    Sala& operator=(const Sala& other) {
//        if (this != &other) {
//            bool* newLocuriOcupate = new bool[other.nrLocuri];
//            for (int i = 0; i < other.nrLocuri; i++) {
//                newLocuriOcupate[i] = other.locuriOcupate[i];
//            }
//            delete[] locuriOcupate;
//            locuriOcupate = newLocuriOcupate;
//            id = other.id;
//            nrLocuri = other.nrLocuri;
//            nrRanduri = other.nrRanduri;
//            nrColoane = other.nrColoane;
//        }
//        return *this;
//    }

    void setIdSala(int id) {
        this->id = id;
    }

    void setLocuriOcupate(int nrLocuri, bool *locuriOcupate) {
        delete[] this->locuriOcupate;
        this->locuriOcupate = new bool[nrLocuri];
        for (int i = 0; i < nrLocuri; i++) {
            this->locuriOcupate[i] = locuriOcupate[i];
        }
    }
    int getIdSala() {
        return id;
    }
    bool* getLocuriOcupate() {
        return locuriOcupate;
    }
};

class Cinema{
private:
    int id;
    std::string nume_mall;
    Sala *saliCinema;
    int nrSali;
public:
    Cinema(int id, std::string nume_mall) {
        this->id = id;
        this->nume_mall = nume_mall;
        this->nrSali = 0;
        this->saliCinema = nullptr;
    }
    Cinema() {
        this->id = 0;
        this->nrSali = 0;
        this->nume_mall = "\0";
        this->saliCinema = nullptr;
    }
    ~Cinema() {
        id = 0;
    }
    void setId(int id){
        this->id = id;
    }
    void setNumeMall(std::string nume_mall){
        this->nume_mall = nume_mall;
    }
    int getId() {
        return id;
    }
    std::string getNumeMall() {
        return nume_mall;
    }
    Cinema& operator=(const Cinema &aux) {
        if (this == &aux) {
            return *this;
        }
        this->id = aux.id;
        this->nume_mall = aux.nume_mall;
        return *this;
    }
    bool operator==(Cinema &aux) {
        if(this->id == aux.id and this->nume_mall == aux.nume_mall)
            return true;
        else
            return false;
    }
    friend std::istream& operator>>(std::istream& in, Cinema& cinema) {
        std::cout << "id: ";
        in >> cinema.id;
        std::cout << "nume mall: ";
        in >> cinema.nume_mall;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Cinema& cinema) {
        out << "id: " << cinema.id;
        out << "nume mall: " << cinema.nume_mall;
        return out;
    }
//    Cinema& operator+(Cinema& cinema) {
//        Cinema *aux = new Cinema(cinema);
//        aux->setId(cinema.getId());
//        return *aux;
//    }
};

class Film {
private:
    int id;
    std::string nume_film;
public:
    Film(int id, std::string nume_film) {
        this->id = id;
        this->nume_film = nume_film;
    }
    Film() {
        this->id = 0;
        this->nume_film = "\0";
    }
    ~Film() = default;
    void setNumeFilm(std::string nume_film){
        this->nume_film = nume_film;
    }
    std::string getNumeFilm() {
        return nume_film;
    }
    int getId() {
        return id;
    }
    Film& operator=(const Film &aux) {
        if (this == &aux) {
            return *this;
        }
        this->id = aux.id;
        this->nume_film = aux.nume_film;
        return *this;
    }
};

class Zi {
private:
    std::string zi;
public:
    Zi() {
        this->zi = "\0";
    }
    ~Zi() = default;
    void setZi(std::string zi){
        this->zi = zi;
    }
    std::string getZi() {
        return zi;
    }
};

//class Angajat{
//private:
//    int cnp;
//    std::string nume;
//    int salariu;
//    int numar_telefon;
//public:
//    Angajat(int cnp, std::string nume, int salariu, int numar_telefon) {
//        this->cnp = cnp;
//        this->nume = nume;
//        this->salariu = salariu;
//        this->numar_telefon = numar_telefon;
//    }
//    Angajat(){
//        this->salariu = 0;
//    }
//    ~Angajat() {
//        cnp = 0;
//        salariu = 0;
//        numar_telefon = 0;
//    }
//    void setNume(std::string nume){
//        this->nume = nume;
//    }
//    void setSalariu(int salariu){
//        this->salariu = salariu;
//    }
//    void setNumarTelefon(int numar_telefon){
//        this->numar_telefon = numar_telefon;
//    }
//    int getCnp() {
//        return cnp;
//    }
//    std::string getNume() {
//        return nume;
//    }
//    int getSalariu() {
//        return salariu;
//    }
//    int getNumarTelefon() {
//        return numar_telefon;
//    }
//};

class Ticket {
private:
    std::string cinema_id;
    std::string day;
    std::string hour;
    std::string movie_name;
    int price;
public:
    Ticket(std::string cinema_name, std::string day, std::string hour, std::string movie_name, int price) {
        this->cinema_id = cinema_id;
        this->day = day;
        this->hour = hour;
        this->price = price;
    }
    ~Ticket() {
        price = 0;
    }
    void setCinemaId(std::string cinema_id) {
        this->cinema_id = cinema_id;
    }
    void setDay(std::string day) {
        this->day = day;
    }
    void setHour(std::string hour) {
        this->hour = hour;
    }
    void setMovieName(std::string movie_name) {
        this->movie_name = movie_name;
    }
    std::string getCinemaId() {
        return cinema_id;
    }
    std::string getDay() {
        return day;
    }
    std::string getHour() {
        return hour;
    }
    std::string getMovieName() {
        return movie_name;
    }
    [[nodiscard]] int getPrice() const {
        return price;
    }
};

int main() {

    std::ifstream f("in.txt");
    int id_sala, nrBilete, k = 0, loc[71];
    std::string cod_bilet;
    int tasta;
    std::cout << "Bine ati venit la Cinema Multiplex!\n\n";
    std::cout<<"Va rugam completati campurile de mai jos.\n\n";
    Cinema Afi_Cotroceni(1,"Afi Cotroceni");
    Cinema Park_Lake(2,"Park Lake");
    Cinema Mega_Mall(3,"Mega Mall");
    std::array<Cinema, 3> cinemauri{};
    cinemauri[0] = Afi_Cotroceni;
    cinemauri[1] = Park_Lake;
    cinemauri[2] = Mega_Mall;
    std::cout<<"Apasati tasta corespunzatoare mall-ului dorit:\n1.Afi Cotroceni\n2.Park Lake\n3.Mega Mall\n";
    f>>tasta;
    std::cout<<"Ati selectat "<<cinemauri[tasta-1].getNumeMall()<<std::endl;
    cod_bilet = std::to_string(cinemauri[tasta-1].getId());
    Film Dune_Part_2(1,"Dune Part 2");
    Film Oppenheimer(2,"Oppenheimer");
    Film Star_Wars_Episode_3_Revenge_of_the_Sith(3,"Star Wars Episode 3: Revenge of the Sith");
    Film The_Dark_Knight(4,"Dune Part 2");
    Film The_Lord_of_the_Rings_The_Two_Towers(5,"The Lord of the Rings: The Two Towers");
    Film The_Martian(6,"The Martian");
    Film The_Matrix(7,"The Matrix");
    std::array<Film, 7> filme{};
    filme[0] = Dune_Part_2;
    filme[1] = Oppenheimer;
    filme[2] = Star_Wars_Episode_3_Revenge_of_the_Sith;
    filme[3] = The_Dark_Knight;
    filme[4] = The_Lord_of_the_Rings_The_Two_Towers;
    filme[5] = The_Martian;
    filme[6] = The_Matrix;
    std::cout<<"Apasati tasta corespunzatoare filmului dorit:\n1.Dune Part 2\n2.Oppenheimer\n3.Star Wars Episode 3: Revenge of the Sith\n4.The Dark Knight\n5.The Lord of the Rings: The Two Towers\n6.The Martian\n7.The Matrix\n";
    f>>tasta;
    cod_bilet += std::to_string(filme[tasta-1].getId());
    std::cout<<"Ati selectat "<<filme[tasta-1].getNumeFilm()<<std::endl;
    std::array<Zi, 7> zile{};
    zile[0].setZi("Luni");
    zile[1].setZi("Marti");
    zile[2].setZi("Miercuri");
    zile[3].setZi("Joi");
    zile[4].setZi("Vineri");
    zile[5].setZi("Sambata");
    zile[6].setZi("Duminica");
    std::cout<<"Apasati tasta corespunzatoare zilei dorite:\n1.Luni\n2.Marti\n3.Miercuri\n4.Joi\n5.Vineri\n6.Sambata\n7.Duminica\n";
    f>>tasta;
    std::cout<<"Ati selectat "<<zile[tasta-1].getZi()<<std::endl;
    cod_bilet += zile[tasta-1].getZi();
    std::cout<<"Apasati tasta corespunzatoare orei dorite:\n1.10:30\n2.12:00\n3.13:30\n4.15:00\n5.16:30\n6.18:00\n7.19:30\n8.21:00\n9.22:30\n";
    f>>tasta;
    std::vector<std::string> ore;
    ore.emplace_back("10:30");
    ore.emplace_back("12:00");
    ore.emplace_back("13:30");
    ore.emplace_back("15:00");
    ore.emplace_back("16:30");
    ore.emplace_back("18:00");
    ore.emplace_back("19:00");
    ore.emplace_back("20:30");
    cod_bilet += ore[tasta-1];
    std::cout<<"Ati selectat "<<ore[tasta-1]<<std::endl;
    id_sala = tasta%2;
    cod_bilet += std::to_string(id_sala);
    std::cout<<"Numarul de bilete de achizitionat (maxim 9): ";
    f>>tasta;
    std::cout<<tasta<<std::endl;
    nrBilete=tasta;
    Sala *S1 = new Sala (1);
    Sala *S2 = new Sala (2);
    if(id_sala == 1)
        for(int i=0;i<70;i++)
            loc[i]=S1->getLocuriOcupate()[i];
    else
        for(int i=0;i<70;i++)
            loc[i]=S2->getLocuriOcupate()[i];
    delete S1;
    delete S2;
    std::cout<<"Locurile disponibile sunt marcate cu 0, locurile ocupate sunt marcate cu 1.\n";
    std::cout<<"Pentru a alege locul tastati randul urmat de tasta Enter apoi numarul scaunului.\n\n";
    std::cout<<" __";
    for(int j = 0; j < 10; j++)
        std::cout<<"__";
    std::cout<<"__ ";
    std::cout<<"\n\n\n   ";
    for(int j = 0; j < 10;j++)
        std::cout<<j+1<<" ";
    std::cout<<"\n";
    for(int i=0;i<7;i++) {
        std::cout << i + 1 << "  ";
        for (int j = 0; j < 10; j++)
            std::cout << loc[i * 10 + j] << " ";
        std::cout << '\n';
    }
    for(int i=0;i<nrBilete;i++) {
        int x, y;
        f >> x >> y;
        cod_bilet += std::to_string(x);
        cod_bilet += std::to_string(y);
        loc[x*10+y] = 1;
    }
//    payment? cu cardul, verific daca e valid; sau la intrare in cinema, cash
    std::cout<<cod_bilet;
    f.close();
    return 0;
}
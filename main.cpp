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
        this->nrLocuri = 63;
        this->nrRanduri = 9;
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
        delete[] locuriOcupate;
        locuriOcupate = nullptr;
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
    [[nodiscard]] bool* getLocuriOcupate() const{
        return locuriOcupate;
    }
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
        this->nume_film = '\0';
    }
    ~Film() = default;
    void setNumeFilm(std::string nume_film){
        this->nume_film = nume_film;
    }
    [[nodiscard]] std::string getNumeFilm() const{
        return nume_film;
    }
    [[nodiscard]] int getId() const {
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

class Cinema{
private:
    int id;
    std::string numeMall;
    Film *filmeDifuzate;
    int nrFilme;
public:
    Cinema(int id, std::string numeMall) {
        this->id = id;
        this->numeMall = numeMall;
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
    void setId(int id){
        this->id = id;
    }
    void setNumeMall(std::string numeMall) {
        this->numeMall = numeMall;
    }
    void setNrFilme(int nrFilme) {
        this->nrFilme = nrFilme;
    }
    void setFilmeDifuzate(int nrFilme, Film *filmeDifuzate) {
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
    [[nodiscard]] Film* getFilmeDifuzate() const{
        return filmeDifuzate;
    }
    Cinema(Cinema& aux) {
        id = aux.id;
        numeMall = aux.numeMall;
        nrFilme = aux.nrFilme;
        filmeDifuzate = new Film[aux.nrFilme];
        for (int i = 0; i < aux.nrFilme; i++)
            filmeDifuzate[i] = aux.filmeDifuzate[i];
    }
    Cinema& operator=(const Cinema &aux) {
        if (this == &aux) {
            return *this;
        }
        this->id = aux.id;
        this->numeMall = aux.numeMall;
        this->nrFilme= aux.nrFilme;
        delete[] filmeDifuzate;
        this->filmeDifuzate = new Film[nrFilme];
        for (int i = 0; i < aux.nrFilme; i++)
            filmeDifuzate[i] = aux.filmeDifuzate[i];
        return *this;
    }
//    bool operator==(Cinema &aux) {
//        if(this->id == aux.id and this->numeMall == aux.numeMall)
//            return true;
//        else
//            return false;
//    }
    friend std::istream& operator>>(std::istream& in, Cinema& cinema) {
        std::cout << "id: ";
        in >> cinema.id;
        std::cout << "nume mall: ";
        in >> cinema.numeMall;
        std::cout<< "numar sali: ";
        in >> cinema.nrFilme;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Cinema& cinema) {
        out << "id: " << cinema.id;
        out << "nume mall: " << cinema.numeMall;
        out << "numar sali: " << cinema.nrFilme;
        return out;
    }
};

class Zi {
private:
    std::string zi;
public:
    Zi() {
        this->zi = '\0';
    }
    ~Zi() = default;
    void setZi(std::string zi){
        this->zi = zi;
    }
    [[nodiscard]] std::string getZi() const{
        return zi;
    }
};

class Bilet {
private:
    int rand;
    int coloana;
    int nr_bilete;
public:
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

//Cinema operator+(Cinema cinema, Film *filmeDifuzate) {
//    cinema.setNrFilme(cinema.getNrFilme()+1);
//    delete[] filmeDifuzate;
//    cinema.setFilmeDifuzate() = new Sala[cinema.getNrFilme()];
//    for (int i = 0; i < cinema.getNrFilme(); ++i) {
//        cinema.filmeDifuzate[i] = cinema.filmeDifuzate[i];
//    }
//    cinema.setFilmeDifuzate[cinema.getNrFilme() - 1] = Sala();
//    return cinema;
//}

bool operator==(const Cinema& cinema, const Cinema& aux) {
    if(cinema.getId() == aux.getId() and cinema.getNumeMall() == aux.getNumeMall())
        return true;
    else
        return false;
}

int main() {
    std::ifstream f("date.txt");
    int tasta, id_sala, k, loc[63], x, y, nr_bilete=0, ccv;
    std::string cod_cinema, cod_film, cod_zi, cod_ora, cod_sala, cod_rand, cod_coloana, nr_card, nume_titular, data_exp;
    Cinema Afi_Cotroceni(1, "Afi Cotroceni");
    Cinema Park_Lake(2, "Park Lake");
    Cinema Mega_Mall(3, "Mega Mall");
    std::array<Cinema, 3> cinemauri{};
    cinemauri[0] = Afi_Cotroceni;
    cinemauri[1] = Park_Lake;
    cinemauri[2] = Mega_Mall;
    Film Dune_Part_2(1, "Dune Part 2");
    Film Oppenheimer(2, "Oppenheimer");
    Film Star_Wars_Episode_3_Revenge_of_the_Sith(3, "Star Wars Episode 3: Revenge of the Sith");
    Film The_Dark_Knight(4, "Dune Part 2");
    Film The_Lord_of_the_Rings_The_Two_Towers(5, "The Lord of the Rings: The Two Towers");
    Film The_Martian(6, "The Martian");
    Film The_Matrix(7, "The Matrix");
    std::array<Film, 7> filme{};
    filme[0] = Dune_Part_2;
    filme[1] = Oppenheimer;
    filme[2] = Star_Wars_Episode_3_Revenge_of_the_Sith;
    filme[3] = The_Dark_Knight;
    filme[4] = The_Lord_of_the_Rings_The_Two_Towers;
    filme[5] = The_Martian;
    filme[6] = The_Matrix;
    std::array<Zi, 7> zile{};
    zile[0].setZi("Luni");
    zile[1].setZi("Marti");
    zile[2].setZi("Miercuri");
    zile[3].setZi("Joi");
    zile[4].setZi("Vineri");
    zile[5].setZi("Sambata");
    zile[6].setZi("Duminica");
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
    Bilet B1(1);
    Bilet B2(2);
    Bilet B3(3);
    Bilet B4(4);
    Bilet B5(5);
    Bilet B6(6);
    Bilet B7(7);
    Bilet B8(8);
    Bilet B9(9);
    std::array<Bilet, 9> bilete{};
    for (int i = 0; i < 9; i++)
        bilete[i].setNrBilet(i+1);
    std::cout << "\nBine ati venit la Cinema Multiplex!\n\n";
    std::cout << "Va rugam completati campurile de mai jos.\n\n";
    citeste_cinema:
    std::cout << "Apasati tasta corespunzatoare mall-ului dorit:\n1.Afi Cotroceni\n2.Park Lake\n3.Mega Mall\nApasati tasta 0 pentru a iesi.\n";
    f >> tasta;
    if (tasta == 0) {
        std::cout << "La revedere!";
        goto exit;
    }
    std::cout << "Ati selectat " << cinemauri[tasta - 1].getNumeMall() << "\n\n";
    cod_cinema = std::to_string(cinemauri[tasta - 1].getId());
    citeste_film:
    std::cout << "Apasati tasta corespunzatoare filmului dorit:\n1.Dune Part 2\n2.Oppenheimer\n3.Star Wars Episode 3: Revenge of the Sith\n4.The Dark Knight\n5.The Lord of the Rings: The Two Towers\n6.The Martian\n7.The Matrix\nApasati tasta 0 pentru a merge inapoi.\n";
    f >> tasta;
    if (tasta == 0)
        goto citeste_cinema;
    std::cout<<"Ati selectat "<<filme[tasta-1].getNumeFilm()<<"\n\n";
    cod_film = std::to_string(filme[tasta - 1].getId());
    citeste_zi:
    std::cout<<"Apasati tasta corespunzatoare zilei dorite:\n1.Luni\n2.Marti\n3.Miercuri\n4.Joi\n5.Vineri\n6.Sambata\n7.Duminica\nApasati tasta 0 pentru a merge inapoi.\n";
    f>>tasta;
    if (tasta == 0)
        goto citeste_film;
    std::cout<<"Ati selectat "<<zile[tasta-1].getZi()<<"\n\n";
    cod_zi = zile[tasta-1].getZi();
    citeste_ora:
    std::cout<<"Apasati tasta corespunzatoare orei dorite:\n1.10:30\n2.12:00\n3.13:30\n4.15:00\n5.16:30\n6.18:00\n7.19:30\n8.21:00\n9.22:30\nApasati tasta 0 pentru a merge inapoi.\n";
    f>>tasta;
    if (tasta == 0)
        goto citeste_zi;
    cod_ora += ore[tasta-1];
    std::cout<<"Ati selectat "<<ore[tasta-1]<<"\n\n";
    id_sala = tasta%2;
    cod_sala += std::to_string(id_sala);
    if (tasta == 0)
        goto citeste_ora;
    if(id_sala == 1)
        for(int i=0;i<63;i++)
            loc[i]=S1->getLocuriOcupate()[i];
    else
        for(int i=0;i<63;i++)
            loc[i]=S2->getLocuriOcupate()[i];
    std::cout<<"\nLocurile disponibile sunt marcate cu 0, locurile ocupate sunt marcate cu 1.\n";
    std::cout<<"Pentru a alege locul tastati randul urmat de tasta Enter apoi numarul scaunului.\n\n";
    std::cout<<" __";
    for(int j = 0; j < 9; j++)
        std::cout<<"__";
    std::cout<<"__ ";
    std::cout<<"\n\n\n   ";
    for(int j = 0; j < 9;j++)
        std::cout<<j+1<<" ";
    std::cout<<"\n";
    for(int i=0;i<7;i++) {
        std::cout << i + 1 << "  ";
        for (int j = 0; j < 9; j++)
            std::cout << loc[i * 9 + j] << " ";
        std::cout << '\n';
    }
    while(nr_bilete<9) {
        citeste_rand:
        std::cout<<"\nAlegeti randul.\nApasati tasta 0 pentru a merge inapoi.\n";
        if(nr_bilete!=0)
            std::cout<<"Apasati tasta 10 pentru a continua cu plata.\n";
        f >> x;
        if(x == 10) {
            break;
        }
        if(x==0) {
            nr_bilete--;
            bilete[nr_bilete].setColoana(0);
            goto citeste_coloana;
        }
        bilete[nr_bilete].setRand(x);
        cod_rand = std::to_string(x);
        citeste_coloana:
        std::cout<<"\nAlegeti locul.\nApasati tasta 0 pentru a merge inapoi.\n";
        f >> y;
        if(y==0) {
            bilete[nr_bilete].setRand(0);
            goto citeste_rand;
        }
        bilete[nr_bilete].setColoana(y);
        cod_coloana = std::to_string(y);
        nr_bilete++;
        k=0;
        std::cout<<"\nLocurile alese de dvs. sunt cele marcate cu 2:\n";
        std::cout<<" __";
        for(int j = 0; j < 9; j++)
            std::cout<<"__";
        std::cout<<"__ ";
        std::cout<<"\n\n\n   ";
        for(int j = 0; j < 9;j++)
            std::cout<<j+1<<" ";
        std::cout<<"\n";
        for(int i=0;i<7;i++) {
            std::cout << i + 1 << "  ";
            for (int j = 0; j < 9; j++) {
                if(bilete[k].getRand()==i+1 and bilete[k].getColoana()==j+1 and k<nr_bilete) {
                    k++;
                    std::cout<<"2 ";
                }
                else
                    std::cout << loc[i*9+j] << " ";
            }
            std::cout << '\n';
        }
    }
    for(int i=0;i<nr_bilete;i++)
        loc[(bilete[i].getRand()-1)*9+(bilete[i].getColoana()-1)] = 1;
    std::cout<<"\nNumarul cardului: ";
    f.get();
    std::getline(f,nr_card);
    std::cout<<nr_card<<"\n";
    std::cout<<"Numele titularului: ";
    std::getline(f,nume_titular);
    std::cout<<nume_titular<<"\n";
    std::cout<<"Data expirarii: ";
    f>>data_exp;
    std::cout<<data_exp<<"\n";
    std::cout<<"CCV: ";
    f>>ccv;
    std::cout<<ccv<<"\n";
    if(nr_bilete==1) {
        std::cout<<"\n\nCodul biletului dvs. este: "<<cod_cinema<<cod_film<<cod_zi<<cod_ora<<cod_sala<<cod_rand<<cod_coloana<<"\n";
    }
    else {
        std::cout<<"\n\nCodurile biletelor dvs. sunt:\n";
        for(int i=0;i<nr_bilete;i++) {
            std::cout<<cod_cinema<<cod_film<<cod_zi<<cod_ora<<cod_sala<<bilete[i].getRand()<<bilete[i].getColoana()<<"\n";
        }
    }
    std::cout<<"\nVa multumim pentru achizitie! Vizionare placuta!\n";
    exit:
    delete S1;
    delete S2;
    f.close();
    return 0;
}
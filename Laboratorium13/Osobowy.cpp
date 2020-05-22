#include "Osobowy.h"

Osobowy::Osobowy() :
	Samochod(),
	nastepny(NULL),
	typ("osobowy"),
	pojemnoscBagaznika(0),
	sylwetka(' ') {
}

Osobowy::Osobowy(Osobowy& o) :
	Samochod(o.rocznik, o.przebieg, o.marka, o.model),
	nastepny(NULL),
	typ("osobowy"),
	pojemnoscBagaznika(o.pojemnoscBagaznika),
	sylwetka(o.sylwetka) {
}

Osobowy::Osobowy(int rocznik, int przebieg, std::string marka, std::string model, float pojemnoscBagaznika, char sylwetka) :
	Samochod(rocznik, przebieg, marka, model),
	nastepny(NULL),
	typ("osobowy"),
	pojemnoscBagaznika(pojemnoscBagaznika),
	sylwetka(sylwetka) {
}

Osobowy::~Osobowy() {
	delete this->nastepny;
}

void Osobowy::Wypisz() {
	if (this->marka == "-") std::cout << "<polaczenie samochodow osobowych>" << std::endl;
	std::cout << "marka:\t\t" << this->marka << std::endl;
	std::cout << "model:\t\t" << this->model << std::endl;
	std::cout << "rok:\t\t" << this->rocznik << std::endl;
	std::cout << "przebieg:\t" << this->przebieg << std::endl;
	std::cout << "bagaznik:\t" << this->pojemnoscBagaznika << " [L]"<< std::endl;
	std::cout << "typ sylwetki:\t" << this->sylwetka << std::endl << std::endl;
}

// operatory
Osobowy Osobowy::operator = (const Osobowy& o) {
	Osobowy wynik;
	wynik.SetMarka(o.marka);
	wynik.SetModel(o.model);
	wynik.SetRocznik(o.rocznik);
	wynik.SetPrzebieg(o.przebieg);
	wynik.SetPojemnoscBagaznika(o.pojemnoscBagaznika);
	wynik.SetSylwetka(o.sylwetka);
	return wynik;
}

Osobowy Osobowy::operator + (const Osobowy& o) {
	Osobowy wynik;
	this->SetMarka("-");
	this->SetModel("-");
	this->SetPrzebieg(this->przebieg + o.przebieg);
	this->SetPojemnoscBagaznika(this->pojemnoscBagaznika + o.pojemnoscBagaznika);
	this->SetSylwetka('-');
	if (this->rocznik != 0) this->SetRocznik(this->rocznik < o.rocznik ? this->rocznik : o.rocznik);
	else this->rocznik = o.rocznik;
	return wynik;
}

void Osobowy::operator += (const Osobowy& o) {
	this->SetMarka("-");
	this->SetModel("-");
	this->SetPrzebieg(this->przebieg + o.przebieg);
	this->SetPojemnoscBagaznika(this->pojemnoscBagaznika + o.pojemnoscBagaznika);
	this->SetSylwetka('-');
	if (this->rocznik != 0) this->SetRocznik(this->rocznik < o.rocznik ? this->rocznik : o.rocznik);
	else this->rocznik = o.rocznik;
}

// settery
void Osobowy::SetNastepny(Osobowy* o) { this->nastepny = o; }
void Osobowy::SetPojemnoscBagaznika(float p) { this->pojemnoscBagaznika = p; }
void Osobowy::SetSylwetka(char s) { this->sylwetka = s; }

// gettery
Osobowy* Osobowy::GetNastepny() { return this->nastepny; }
std::string Osobowy::GetTyp() { return this->typ; }
float Osobowy::GetPojemnoscBagaznika() { return this->pojemnoscBagaznika; }
char Osobowy::GetSylwetka() { return this->sylwetka; }
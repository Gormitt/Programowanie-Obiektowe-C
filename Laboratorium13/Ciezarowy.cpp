#include <iostream>
#include "Ciezarowy.h"

Ciezarowy::Ciezarowy() :
	Samochod(),
	nastepny(NULL),
	typ("ciezarowy"),
	maxLadownosc(0),
	liczbaKol(0) {
}

Ciezarowy::Ciezarowy(Ciezarowy& c) :
	Samochod(c.rocznik, c.przebieg, c.marka, c.model),
	nastepny(NULL),
	typ("ciezarowy"),
	maxLadownosc(c.maxLadownosc),
	liczbaKol(c.liczbaKol) {
}

Ciezarowy::Ciezarowy(int rocznik, int przebieg, std::string marka, std::string model, float maxLadownosc, int liczbaKol) :
	Samochod(rocznik, przebieg, marka, model),
	nastepny(NULL),
	typ("ciezarowy"),
	maxLadownosc(maxLadownosc),
	liczbaKol(liczbaKol) {
}

Ciezarowy::~Ciezarowy() {
	delete this->nastepny;
}

void Ciezarowy::Wypisz() {
	if (this->marka == "-") std::cout << "<polaczenie samochodow ciezarowych>" << std::endl;
	std::cout << "marka:\t\t" << this->marka << std::endl;
	std::cout << "model:\t\t" << this->model << std::endl;
	std::cout << "rok:\t\t" << this->rocznik << std::endl;
	std::cout << "przebieg:\t" << this->przebieg << std::endl;
	std::cout << "ladownosc:\t" << this->maxLadownosc << std::endl;
	std::cout << "liczba kol:\t" << this->liczbaKol << std::endl << std::endl;
}

// operatory
Ciezarowy Ciezarowy::operator = (const Ciezarowy& c) {
	Ciezarowy wynik;
	wynik.SetMarka(c.marka);
	wynik.SetModel(c.model);
	wynik.SetRocznik(c.rocznik);
	wynik.SetPrzebieg(c.przebieg);
	wynik.SetMaxLadownosc(c.maxLadownosc);
	wynik.SetLiczbaKol(c.liczbaKol);
	return wynik;
}

Ciezarowy Ciezarowy::operator + (const Ciezarowy& c) {
	Ciezarowy wynik;
	this->SetMarka("-");
	this->SetModel("-");
	this->SetPrzebieg(this->przebieg + c.przebieg);
	this->SetMaxLadownosc(this->maxLadownosc + c.maxLadownosc);
	this->SetLiczbaKol(this->liczbaKol + c.liczbaKol);
	if (this->rocznik != 0)this->SetRocznik(this->rocznik < c.rocznik ? this->rocznik : c.rocznik);
	else this->rocznik = c.rocznik;
	return wynik;
}

void Ciezarowy::operator += (const Ciezarowy& c) {
	this->SetMarka("-");
	this->SetModel("-");
	this->SetPrzebieg(this->przebieg + c.przebieg);
	this->SetMaxLadownosc(this->maxLadownosc + c.maxLadownosc);
	this->SetLiczbaKol(this->liczbaKol + c.liczbaKol);
	if (this->rocznik != 0)this->SetRocznik(this->rocznik < c.rocznik ? this->rocznik : c.rocznik);
	else this->rocznik = c.rocznik;
}

// settery
void Ciezarowy::SetNastepny(Ciezarowy* c) { this->nastepny = c; }
void Ciezarowy::SetMaxLadownosc(float maxLadownosc) { this->maxLadownosc = maxLadownosc; }
void Ciezarowy::SetLiczbaKol(int liczbaKol) { this->liczbaKol = liczbaKol; }

// gettery
Ciezarowy* Ciezarowy::GetNastepny() { return this->nastepny; }
std::string Ciezarowy::GetTyp() { return this->typ; }
float Ciezarowy::GetMaxLadownosc() { return this->maxLadownosc; }
int Ciezarowy::GetLiczbaKol() { return this->liczbaKol; }
#include <iostream>
#include "Samochod.h"

Samochod::Samochod() :
	nastepny(NULL),
	rocznik(0),
	przebieg(0),
	marka(""),
	model(""){
}

Samochod::Samochod(Samochod& s) :
	nastepny(NULL),
	rocznik(s.rocznik),
	przebieg(s.przebieg),
	marka(s.marka),
	model(s.model) {
}


Samochod::Samochod(int rocznik, int przebieg, std::string marka, std::string model) :
	nastepny(NULL),
	rocznik(rocznik),
	przebieg(przebieg),
	marka(marka),
	model(model) {
}

Samochod::~Samochod() {
	delete this->nastepny;
}

void Samochod::Wypisz() {
	if (this->marka == "-") std::cout << "<polaczenie samochodow>" << std::endl;
	std::cout << "marka:\t\t" << this->marka << std::endl;
	std::cout << "model:\t\t" << this->model << std::endl;
	std::cout << "rok:\t\t" << this->rocznik << std::endl;
	std::cout << "przebieg:\t" << this->przebieg << std::endl << std::endl;
}

// settery
void Samochod::SetNastepny(Samochod* s) { this->nastepny = s; }
void Samochod::SetRocznik(int r) { this->rocznik = r; }
void Samochod::SetPrzebieg(int p) { this->przebieg = p; }
void Samochod::SetMarka(std::string marka) { this->marka = marka; }
void Samochod::SetModel(std::string model) { this->model = model; }

//gettery
Samochod* Samochod::GetNastepny() { return this->nastepny; }
int Samochod::GetRocznik() { return this->rocznik; }
int Samochod::GetPrzebieg() { return this->przebieg; }
std::string Samochod::GetMarka() { return this->marka; }
std::string Samochod::GetModel() { return this->model; }
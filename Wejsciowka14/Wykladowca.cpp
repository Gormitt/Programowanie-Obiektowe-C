#include <iostream>
#include "Wykladowca.h"

Wykladowca::Wykladowca() :
	Osoba(),
	nast(NULL),
	liczbaGrup(0),
	przedmiot(""),
	stopien("") {
}

Wykladowca::Wykladowca(std::string imie, int wiek, int liczbaZainteresowa, int liczbaGrup, std::string przedmiot, std::string stopien) :
	Osoba(imie, wiek, liczbaZainteresowa),
	nast(NULL),
	liczbaGrup(liczbaGrup),
	przedmiot(przedmiot),
	stopien(stopien) {
}

Wykladowca::~Wykladowca() {
	delete this->nast;
}

void Wykladowca::operator+= (Wykladowca& wykladowca) {
	Osoba::operator+=(wykladowca);
	this->liczbaGrup += wykladowca.liczbaGrup;
	this->przedmiot = "";
	this->stopien = "";
}

void Wykladowca::Wypisz() {
	std::cout << "wykladowca";
	if (this->imie.length() > 0) std::cout << "\nimie: " << this->imie;
	std::cout << "\nwiek: " << this->wiek;
	std::cout << "\nliczba zainteresowan: " << this->liczbaZainteresowan;
	std::cout << "\nliczba grup: " << this->liczbaGrup;
	if (this->przedmiot.length() > 0) std::cout << "\nwykladany przedmiot: " << this->przedmiot;
	if (this->stopien.length() > 0) std::cout << "\stopien naukowy: " << this->stopien << "\n\n";
	else std::cout << "\n\n";
}

// set
void Wykladowca::Set_nastepny(Wykladowca* w) { this->nast = w; }
// get
Wykladowca* Wykladowca::Get_nastepny() { return this->nast; }
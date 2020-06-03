#include <iostream>
#include "Osoba.h"

Osoba::Osoba() :
	nast(NULL),
	imie(""),
	wiek(0),
	liczbaZainteresowan(0) {
}

Osoba::Osoba(std::string imie, int wiek, int liczbaZainteresowan) : 
	nast(NULL),
	imie(imie),
	wiek(wiek),
	liczbaZainteresowan(liczbaZainteresowan) {
}

Osoba::~Osoba() {
	delete this->nast;
}

void Osoba::operator += (Osoba& osoba) {
	this->imie = "";
	this->wiek += osoba.wiek;
	this->liczbaZainteresowan += osoba.liczbaZainteresowan;
}

void Osoba::Wypisz() {
	std::cout << "osoba";
	if (this->imie.length() > 0) std::cout << "\nimie: " << this->imie;
	std::cout << "\nwiek: " << this->wiek;
	std::cout << "\nliczba zainteresowan: " << this->liczbaZainteresowan << "\n\n";
}

// set
void Osoba::Set_nastepny(Osoba* osoba) { this->nast = osoba; }
// get
Osoba* Osoba::Get_nastepny() { return this->nast; }
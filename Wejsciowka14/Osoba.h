#pragma once
#include <string>

class Osoba {
protected:
	Osoba* nast;
	std::string imie;
	int wiek;
	int liczbaZainteresowan;
public:
	Osoba();
	Osoba(std::string imie, int wiek, int liczbaZainteresowan);
	~Osoba();
	void operator += (Osoba& osoba);
	void Wypisz();

	// set 
	void Set_nastepny(Osoba* osoba);
	// get
	Osoba* Get_nastepny();
};


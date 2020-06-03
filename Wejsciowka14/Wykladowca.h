#pragma once
#include "Osoba.h"

class Wykladowca : public Osoba {
private:
	Wykladowca* nast;
	int liczbaGrup;
	std::string przedmiot;
	std::string stopien;
public:
	Wykladowca();
	Wykladowca(std::string imie, int wiek, int liczbaZainteresowa, int liczbaGrup, std::string przedmiot, std::string stopien);
	~Wykladowca();
	void operator += (Wykladowca& wykladowca);
	virtual void Wypisz();

	// set
	void Set_nastepny(Wykladowca* wykladowca);
	// get
	Wykladowca* Get_nastepny();
};


#pragma once
#include <iostream>
#include "Samochod.h"

class Osobowy : public Samochod {
protected:
	Osobowy* nastepny;
	std::string typ;
	float pojemnoscBagaznika;
	char sylwetka;
public:
	Osobowy();
	Osobowy(Osobowy& osobowy);
	Osobowy(int rocznik, int przebieg, std::string marka, std::string model, float pojemnoscBagaznika, char sylwetka);
	~Osobowy();

	void Wypisz();
	
	// operatory
	Osobowy operator = (const Osobowy& o);
	Osobowy operator + (const Osobowy& o);
	void operator += (const Osobowy& o);

	// settery
	void SetNastepny(Osobowy* o);
	void SetPojemnoscBagaznika(float pojemnoscBagaznika);
	void SetSylwetka(char sylwetka);
	// gettery
	Osobowy* GetNastepny();
	std::string GetTyp();
	float GetPojemnoscBagaznika();
	char GetSylwetka();
};


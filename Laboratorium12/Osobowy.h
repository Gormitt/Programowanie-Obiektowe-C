#pragma once
#include <iostream>
#include "Samochod.h"

class Osobowy : public Samochod {
protected:
	float pojemnoscBagaznika;
	char sylwetka;
public:
	Osobowy();
	Osobowy(Osobowy& osobowy);
	Osobowy(int rocznik, int przebieg, char* marka, char* model, float pojemnoscBagaznika, char sylwetka);
	void Wypisz(FILE* out);
	// settery
	void SetPojemnoscBagaznika(float pojemnoscBagaznika);
	void SetSylwetka(char sylwetka);
	// gettery
	float GetPojemnoscBagaznika();
	char GetSylwetka();
};


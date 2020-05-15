#pragma once
#include "Samochod.h"

class Ciezarowy : public Samochod {
protected:
	float maxLadownosc;
	int liczbaKol;
public:
	Ciezarowy();
	Ciezarowy(Ciezarowy& c);
	Ciezarowy(int rocznik, int przebieg, char* marka, char* model, float maxLadownosc, int liczbaKol);
	void Wypisz(FILE* out);
	void MniejszyNiz(FILE* out, float wielkosc); 
	// settery
	void SetMaxLadownosc(float maxLadownosc);
	void SetLiczbaKol(int liczbaKol);
	// gettery
	float GetMaxLadownosc();
	int GetLiczbaKol();
};


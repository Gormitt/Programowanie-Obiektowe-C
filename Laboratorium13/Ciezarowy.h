#pragma once

#include "Samochod.h"

class Ciezarowy : public Samochod {
protected:
	Ciezarowy* nastepny;
	std::string typ;
	float maxLadownosc;
	int liczbaKol;
public:
	Ciezarowy();
	Ciezarowy(Ciezarowy& c);
	Ciezarowy(int rocznik, int przebieg, std::string marka, std::string model, float maxLadownosc, int liczbaKol);
	~Ciezarowy();

	void Wypisz();
	
	// operatory
	Ciezarowy operator = (const Ciezarowy& c);
	Ciezarowy operator + (const Ciezarowy& c);
	void operator += (const Ciezarowy& c);

	// settery
	void SetNastepny(Ciezarowy* c);
	void SetMaxLadownosc(float maxLadownosc);
	void SetLiczbaKol(int liczbaKol);
	
	// gettery
	Ciezarowy* GetNastepny();
	std::string GetTyp();
	float GetMaxLadownosc();
	int GetLiczbaKol();
};


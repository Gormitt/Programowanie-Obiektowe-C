#include <iostream>
#include "Ciezarowy.h"

Ciezarowy::Ciezarowy() :
	Samochod(),
	maxLadownosc(0),
	liczbaKol(0) {
}

Ciezarowy::Ciezarowy(Ciezarowy& c) :
	Samochod(c.rocznik, c.przebieg, c.marka, c.model),
	maxLadownosc(c.maxLadownosc),
	liczbaKol(c.liczbaKol) {
}

Ciezarowy::Ciezarowy(int rocznik, int przebieg, char* marka, char* model, float maxLadownosc, int liczbaKol) :
	Samochod(rocznik, przebieg, marka, model),
	maxLadownosc(maxLadownosc),
	liczbaKol(liczbaKol) {
}

void Ciezarowy::Wypisz(FILE* out) {
	/*
	printf("marka:\t\t%s\n", this->marka);
	printf("model:\t\t%s\n", this->model);
	printf("rocznik:\t%d\n", this->rocznik);
	printf("przebieg:\t%d\n", this->przebieg);
	printf("ladownosc:\t%.1lfkg\n", this->maxLadownosc);
	printf("liczba kol:\t%d\n\n", this->liczbaKol);
	*/
	fprintf(out, "samochod ciezarowy:\n");
	fprintf(out, "marka:\t\t%s\n", this->marka);
	fprintf(out, "model:\t\t%s\n", this->model);
	fprintf(out, "rocznik:\t%d\n", this->rocznik);
	fprintf(out, "przebieg:\t%d\n", this->przebieg);
	fprintf(out, "ladwonosc:\t%.1fL\n", this->maxLadownosc);
	fprintf(out, "liczba kol:\t%d\n\n", this->liczbaKol);
}

void Ciezarowy::MniejszyNiz(FILE* out, float wielkosc) {
	if (this->maxLadownosc < wielkosc) {
		fprintf(out, "ciezarowka o ladownosci mniejszej od %.1f [kg]\n", wielkosc);
		this->Wypisz(out);
	}
	if (Samochod::GetNastepny() != NULL) Samochod::GetNastepny()->MniejszyNiz(out, wielkosc);
	else return;
}

// settery
void Ciezarowy::SetMaxLadownosc(float maxLadownosc) { this->maxLadownosc = maxLadownosc; }
void Ciezarowy::SetLiczbaKol(int liczbaKol) { this->liczbaKol = liczbaKol; }

// gettery
float Ciezarowy::GetMaxLadownosc() { return this->maxLadownosc; }
int Ciezarowy::GetLiczbaKol() { return this->liczbaKol; }
#include <iostream>
#include "Osobowy.h"

Osobowy::Osobowy() :
	Samochod(),
	pojemnoscBagaznika(0),
	sylwetka(' ') {
}

Osobowy::Osobowy(Osobowy& o) :
	Samochod(o.rocznik, o.przebieg, o.marka, o.model),
	pojemnoscBagaznika(o.pojemnoscBagaznika),
	sylwetka(o.sylwetka) {
}

Osobowy::Osobowy(int rocznik, int przebieg, char* marka, char* model, float pojemnoscBagaznika, char sylwetka) :
	Samochod(rocznik, przebieg, marka, model),
	pojemnoscBagaznika(pojemnoscBagaznika),
	sylwetka(sylwetka) {
}

void Osobowy::Wypisz(FILE* out) {
	printf("marka:\t\t%s\n", this->marka);
	printf("model:\t\t%s\n", this->model);
	printf("rocznik:\t%d\n", this->rocznik);
	printf("przebieg:\t%d\n", this->przebieg);
	printf("bagaznik:\t%lfL\n", this->pojemnoscBagaznika);
	printf("sylwetka:\t%c\n\n", this->sylwetka);
	/*
	fprintf(out, "marka:\t\t%s\n", this->marka);
	fprintf(out, "model:\t\t%s\n", this->model);
	fprintf(out, "rocznik:\t%d\n", this->rocznik);
	fprintf(out, "przebieg:\t%d\n", this->przebieg);
	fprintf(out, "bagaznik:\t%lfL\n", this->pojemnoscBagaznika);
	fprintf(out, "sylwetka:\t%c\n\n", this->sylwetka);
	*/
}

// settery
void Osobowy::SetPojemnoscBagaznika(float p) { this->pojemnoscBagaznika = p; }
void Osobowy::SetSylwetka(char s) { this->sylwetka = s; }

// gettery
float Osobowy::GetPojemnoscBagaznika() { return this->pojemnoscBagaznika; }
char Osobowy::GetSylwetka() { return this->sylwetka; }
#include <iostream>
#include "Samochod.h"

Samochod::Samochod() :
	nastepny(NULL),
	rocznik(0),
	przebieg(0) {
	strcpy_s(this->marka, DL, "");
	strcpy_s(this->model, DL, "");
}

Samochod::Samochod(Samochod& s) :
	nastepny(NULL),
	rocznik(s.rocznik),
	przebieg(s.przebieg) {
	strcpy_s(this->marka, DL, s.marka);
	strcpy_s(this->model, DL, s.model);
}

Samochod::Samochod(int rocznik, int przebieg, char* marka, char* model) :
	nastepny(NULL),
	rocznik(rocznik),
	przebieg(przebieg) {
	strcpy_s(this->marka, DL, marka);
	strcpy_s(this->model, DL, model);
}

Samochod::~Samochod() {
	delete this->nastepny;
}

void Samochod::Wypisz(FILE* out) {
	fprintf(out, "samochod:\n");
	fprintf(out, "marka:\t\t%s\n", this->marka);
	fprintf(out, "model:\t\t%s\n", this->model);
	fprintf(out, "rocznik:\t%d\n", this->rocznik);
	fprintf(out, "przebieg:\t%d\n\n", this->przebieg);
	/*
	printf("marka:\t\t%s\n", this->marka);
	printf("model:\t\t%s\n", this->model);
	printf("rocznik:\t%d\n", this->rocznik);
	printf("przebieg:\t%d\n\n", this->przebieg);
	*/
}

void Samochod::MniejszyNiz(FILE* out, float wielkosc) {
	if (this->rocznik < wielkosc) {
		fprintf(out, "samochod wyprodukowany wczesniej niz w %d:\n", (int)wielkosc);
		this->Wypisz(out);
	}
	if (this->nastepny != NULL) Samochod::nastepny->MniejszyNiz(out, wielkosc);
	else return;
}

// settery
void Samochod::SetNastepny(Samochod* s) { this->nastepny = s; }
void Samochod::SetRocznik(int r) { this->rocznik = r; }
void Samochod::SetPrzebieg(int p) { this->przebieg = p; }
void Samochod::SetMarka(char* marka) { strcpy_s(this->marka, DL, marka); }
void Samochod::SetModel(char* model) { strcpy_s(this->model, DL, model); }

//gettery
Samochod* Samochod::GetNastepny() { return this->nastepny; }
int Samochod::GetRocznik() { return this->rocznik; }
int Samochod::GetPrzebieg() { return this->przebieg; }
char* Samochod::GetMarka() { return this->marka; }
char* Samochod::GetModel() { return this->model; }
#include <iostream>
#include "Samochod.h"

Samochod::Samochod() :
	nst(NULL),
	zdefiniowany(0),
	rocznik(0),
	przebieg(0) {
	char tmp[DL] = "";
	strcpy_s(this->marka, DL, tmp);
	strcpy_s(this->model, DL, tmp);
}

Samochod::Samochod(int rocznik, int przebieg, const char* marka, const char* model) :
	nst(NULL),
	zdefiniowany(1),
	rocznik(rocznik),
	przebieg(przebieg) {
	strcpy_s(this->marka, DL, marka);
	strcat_s(this->model, DL, model);
}

Samochod::Samochod(Samochod& s) :
	nst(NULL),
	zdefiniowany(1),
	rocznik(s.rocznik),
	przebieg(s.przebieg) {
	strcpy_s(this->marka, DL, s.marka);
	strcat_s(this->model, DL, s.model);
}

Samochod::~Samochod() {
	delete this->nst;
}

void Samochod::Wypisz() {
	if (this->zdefiniowany) {
		printf("marka:\t\t%s\n", this->marka);
		printf("model:\t\t%s\n", this->model);
		printf("rok:\t\t%d\n", this->rocznik);
		printf("przebieg:\t%d\n\n", this->przebieg);
	}
	else {
		printf("samochod nie zostal zdefiniowany\n\n");
	}
}

void Samochod::WypiszDalsze() {
	Samochod* tmp = this;
	while (tmp) {
		tmp->Wypisz();
		tmp = tmp->GetNst();
	}
}

// settery
void Samochod::SetNst(Samochod* s) { this->nst = s; }
void Samochod::SetRocznik(int r) { this->rocznik = r; };
void Samochod::SetPrzebieg(int p) { this->przebieg = p; };
void Samochod::SetMarka(char* m) { strcpy_s(this->marka, DL, m); }
void Samochod::SetModel(char* m) { strcpy_s(this->model, DL, m); }

// gettery
Samochod* Samochod::GetNst() { return this->nst; }
int Samochod::GetRocznik() { return this->rocznik; }
int Samochod::GetPrzebieg() { return this->przebieg; }
char* Samochod::GetMarka() { return this->marka; }
char* Samochod::GetModel() { return this->model; }
#include <iostream>
#include "Silnik.h"

Silnik::Silnik() :
	nst(NULL),
	zdefiniowany(0),
	moc(0),
	pojemnosc(0) {
}

Silnik::Silnik(int moc, double pojemnosc) :
	nst(NULL),
	zdefiniowany(1),
	moc(moc),
	pojemnosc(pojemnosc) {
}

Silnik::Silnik(Silnik& s) :
	nst(NULL),
	zdefiniowany(1),
	moc(s.moc),
	pojemnosc(s.pojemnosc) {
}

Silnik::~Silnik() {
	delete this->nst;
}

void Silnik::Wypisz() {
	if (this->zdefiniowany) {
		printf("moc silnika:\t\t%d KM\n", this->moc);
		printf("pojemnosc silnika:\t%.1lf L\n\n", this->pojemnosc);
	}
	else {
		printf("silnik nie zostal zdefiniowany\n\n");
	}
}

void Silnik::WypiszDalsze() {
	Silnik* tmp = this;
	while (tmp) {
		tmp->Wypisz();
		tmp = tmp->GetNst();
	}
}

// settery 
void Silnik::SetNst(Silnik* s) { this->nst = s; }
void Silnik::SetMoc(int moc) { this->moc = moc; }
void Silnik::SetPojemnosc(double pojemnosc) { this->pojemnosc = pojemnosc; }

// gettery
Silnik* Silnik::GetNst() { return this->nst; }
int Silnik::GetMoc() { return this->moc; }
double Silnik::GetPojemnosc() { return this->pojemnosc; }
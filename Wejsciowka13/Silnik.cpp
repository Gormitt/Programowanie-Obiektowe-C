#include <iostream>
#include "Silnik.h"

Silnik::Silnik() :
	nastepny(NULL),
	liczbaCylindrow(0),
	maxObroty(0),
	pojemnosc(0) {
}

Silnik::Silnik(Silnik& s) :
	nastepny(NULL),
	liczbaCylindrow(s.liczbaCylindrow),
	maxObroty(s.maxObroty),
	pojemnosc(s.pojemnosc) {
}

Silnik::Silnik(int a, int b, float c) :
	nastepny(NULL),
	liczbaCylindrow(a),
	maxObroty(b),
	pojemnosc(c) {
}

Silnik::~Silnik() {
	delete this->nastepny;
}

void Silnik::Wypisz() {
	printf("liczba cylindrow: %d\n", this->liczbaCylindrow);
	printf("max liczba obrotow: %d obr/min\n", this->maxObroty);
	printf("pojemnosc: %.2f\n\n", this->pojemnosc);
}

void Silnik::operator+= (const Silnik& s) {
	if (s.maxObroty < this->maxObroty || this->maxObroty == 0) this->maxObroty = s.maxObroty;
	this->liczbaCylindrow += s.liczbaCylindrow;
	this->pojemnosc += s.pojemnosc;
}

// settery
void Silnik::SetNastepny(Silnik* silnik) { this->nastepny = silnik; }
void Silnik::SetLiczbaCylindrow(int liczbaCylindrow) { this->liczbaCylindrow = liczbaCylindrow; }
void Silnik::SetMaxObroty(int maxObroty) { this->maxObroty = maxObroty; }
void Silnik::SetPojemnosc(float pojemnosc) { this->pojemnosc = pojemnosc; }

// gettery
Silnik* Silnik::GetNastepny() { return this->nastepny; }
int Silnik::GetLiczbaCylindrow() { return this->liczbaCylindrow; }
int Silnik::GetMaxObroty() { return this->maxObroty; }
float Silnik::GetPojemnosc() { return this->pojemnosc; }
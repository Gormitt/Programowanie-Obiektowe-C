#include "Prostokat.h"
#include <iostream>
#include <math.h>

int Prostokat::liczbaWszystkich = 0;
double Prostokat::poleWszystkich = 0;

Prostokat::Prostokat(double ax, double ay, double pozioma, double pionowa, int kPoziomy, int kPionowy) :
	nastepny(NULL),
	kPoziomy((kPoziomy < 0) ? -1 : 1),
	kPionowy((kPionowy < 0) ? -1 : 1) {
	if (pozioma <= 0) {
		pozioma = 1;
		printf("error - dlugosc pozioma nie moze byc ujemna lub zerowa, zmieniam jej dlugosc na 1\n");
	}
	if (pionowa <= 0) {
		pionowa = 1;
		printf("error - dlugosc pionowa nie moze byc ujemna lub zerowa, zmieniam jej dlugosc na 1\n");
	}

	Prostokat::UstawFigure(ax, ay, pozioma, pionowa, kPoziomy, kPionowy);
	Prostokat::liczbaWszystkich++;
	Prostokat::poleWszystkich += Prostokat::GetPole();
}

Prostokat::Prostokat() :
	nastepny(NULL),
	ax(0),
	ay(0),
	pozioma(1),
	pionowa(1),
	kPoziomy(1),
	kPionowy(1) {
	Prostokat::liczbaWszystkich++;
	Prostokat::poleWszystkich += Prostokat::GetPole();
}

Prostokat::Prostokat(Prostokat& p) :
	nastepny(NULL),
	ax(p.ax),
	ay(p.ay),
	pozioma(p.pozioma),
	pionowa(p.pionowa),
	kPoziomy(p.kPoziomy),
	kPionowy(p.kPionowy) {
	Prostokat::liczbaWszystkich++;
	Prostokat::poleWszystkich += Prostokat::GetPole();
}

Prostokat::~Prostokat() {
	Prostokat::liczbaWszystkich--;
	Prostokat::poleWszystkich -= Prostokat::GetPole();
	delete this->nastepny;
}

void Prostokat::UstawFigure(double ax, double ay, double pozioma, double pionowa, int kPoziomy, int kPionowy) {
	this->ax = ax;
	this->ay = ay;
	this->pozioma = pozioma;
	this->pionowa = pionowa;
	this->kPoziomy = kPoziomy;
	this->kPionowy = kPionowy;
}

void Prostokat::Wypisz() {
	double bx = this->ax + this->pozioma * this->kPoziomy;
	double cy = this->ay + this->pionowa * this->kPionowy;
	double dx = this->ax + this->pozioma * this->kPoziomy;
	double dy = this->ay + this->pionowa * this->kPionowy;

	printf("wymiary: %.1lf x %.1lf\n", this->pozioma, this->pionowa);
	printf("wsp. podstawy A: (%.1lf, %.1lf) oraz (%.1lf, %.1lf)  \n", this->ax, this->ay, bx, this->ay);
	printf("wsp. podstawy B: (%.1lf, %.1lf) oraz (%.1lf, %.1lf)\n\n", this->ax, cy, dx, dy);
}

void Prostokat::Symetria(double x) {
	this->ax = (this->ax < x) ? (x + abs(this->ax - x)) : (x - abs(this->ax - x));
	this->kPoziomy = (this->kPoziomy < 0) ? 1 : -1;
}

void Prostokat::Skaluj(double x) {
	this->pozioma *= x;
	this->pionowa *= x;
}

void Prostokat::ZwiekszPole(Prostokat& p) {
	double docelowePole = Prostokat::GetPole() + p.GetPole();
	double skala = sqrt(docelowePole / Prostokat::GetPole());
	Prostokat::Skaluj(skala);
}

Prostokat* Prostokat::SzukajDrugiego(Prostokat* p) {
	if (this != p && abs(this->ax - (*p).ax) < 0.001 && abs(this->ay - (*p).ay) < 0.001 &&
		abs(this->pozioma - (*p).pozioma) < 0.001 && abs(this->pionowa < (*p).pionowa) < 0.001 &&
		this->kPoziomy == (*p).kPoziomy && this->kPionowy == (*p).kPionowy) return this;
	else if (this->nastepny != NULL) return this->nastepny->SzukajDrugiego(p);
	else return NULL;
}

void Prostokat::SetNastepny(Prostokat* p) {
	this->nastepny = p;
}

Prostokat* Prostokat::GetNastepny() {
	return this->nastepny;
}

double Prostokat::GetPole() {
	return this->pozioma * this->pionowa;
}

int Prostokat::GetLiczbaWszystkich() {
	return Prostokat::liczbaWszystkich;
}

double Prostokat::GetPoleWszystkich() {
	return Prostokat::poleWszystkich;
}
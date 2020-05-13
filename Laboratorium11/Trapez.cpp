#include "Trapez.h"
#include <iostream>
#include <math.h>

int Trapez::liczbaWszystkich = 0;
double Trapez::poleWszystkich = 0;

Trapez::Trapez(double ax, double ay, double bx, double by, double gorna, int kierunek) {
	kierunek = (kierunek < 0) ? -1 : 1;
	if (gorna <= 0) {
		gorna *= -1;
		gorna += 1;
		printf("error - dl. gornej podstawy musi byc wartoscia dodatnia, zmieniam jej na %.1lf\n", gorna);
	}
	if (ay <= by) {
		double tmp1 = ax;
		double tmp2 = ay;
		ax = bx;
		ay = by;
		bx = tmp1;
		by = tmp2;
		printf("error - zamieniam podane wierzcholki miejscami, tak wierzcholek A [pierwszy wczytany] byl nad wierzcholkiem B [drugi wczyatny]\n");
	}
	if ((ax < bx && kierunek == 1 && gorna < 2 * abs(ax - bx) + 1.0) || (ax > bx&& kierunek == -1 && gorna < 2 * abs(ax - bx) + 1.0)) {
		kierunek = (kierunek < 0) ? 1 : -1;
		printf("error - aby mozna bylo narysowac trapez, zmieniam kierunek rysowania\n");
	}

	this->UstawFigure(ax, ay, bx, by, gorna, kierunek);
	Trapez::liczbaWszystkich++;
	Trapez::poleWszystkich += this->GetPole();
}

Trapez::Trapez() : 
	nastepny(NULL), 
	ax(1), ay(1), 
	bx(0), by(0), 
	gorna(1), 
	kierunek(1) {
	Trapez::liczbaWszystkich++;
	Trapez::poleWszystkich += this->GetPole();
}

Trapez::Trapez(Trapez& t) : 
	nastepny(NULL), 
	ax(t.ax), 
	ay(t.ay), 
	bx(t.bx), 
	by(t.by), 
	gorna(t.gorna), 
	kierunek(t.kierunek) {
	Trapez::liczbaWszystkich++;
	Trapez::poleWszystkich += this->GetPole();
}

Trapez::Trapez(Prostokat& p) :
	nastepny(NULL),
	ax(p.ax),
	bx(p.ax),
	gorna(p.pozioma),
	kierunek(p.kPoziomy) {
	if (p.kPionowy == 1) {
		this->ay = p.ay + p.pionowa;
		this->by = p.ay;
	}
	else {
		this->ay = p.ay;
		this->by = p.ay - p.pionowa;
	}
	Trapez::liczbaWszystkich++;
	Trapez::poleWszystkich += this->GetPole();
}

Trapez::~Trapez() {
	Trapez::liczbaWszystkich--;
	Trapez::poleWszystkich -= this->GetPole();
	delete this->nastepny;
}

void Trapez::UstawFigure(double ax, double ay, double bx, double by, double gorna, int kierunek) {
	this->nastepny = NULL;
	this->ax = ax;
	this->ay = ay;
	this->bx = bx;
	this->by = by;
	this->gorna = gorna;
	this->kierunek = kierunek;
}

void Trapez::Wypisz() {
	double dolna = ((this->ax < this->bx && this->kierunek == 1) || (this->ax > this->bx && this->kierunek == -1)) ? (this->gorna - 2 * abs(this->ax - this->bx)) : (this->gorna + 2 * abs(this->ax - this->bx));
	double tmp1 = this->ax + (this->gorna * this->kierunek);
	double tmp2 = this->bx + (dolna * this->kierunek);
	printf("wsp. gornej podstawy: (%.1lf, %.1lf) i (%.1lf, %.1lf)\tdl.: %.1lf  \n", Trapez::ax, Trapez::ay, tmp1, Trapez::ay, Trapez::gorna);
	printf("wsp. dolnej podstawy: (%.1lf, %.1lf) i (%.1lf, %.1lf)\tdl.: %.1lf\n\n", Trapez::bx, Trapez::by, tmp2, Trapez::by, dolna);
}

void Trapez::Symetria(double x) {
	this->ax = (this->ax < x) ? (x + abs(this->ax - x)) : (x - abs(this->ax - x));
	this->bx = (this->bx < x) ? (x + abs(this->bx - x)) : (x - abs(this->bx - x));
	this->kierunek = (this->kierunek < 0) ? 1 : -1;
}

void Trapez::Skaluj(double x) {
	double dolna = ((this->ax < this->bx && this->kierunek == 1) || (this->ax > this->bx&& this->kierunek == -1)) ? (this->gorna - 2 * abs(this->ax - this->bx)) : (this->gorna + 2 * abs(this->ax - this->bx));
	double wysokosc = abs(this->ay - this->by);

	this->gorna *= x;
	dolna *= x;
	wysokosc *= x;

	if (this->gorna < dolna) {
		this->by = this->ay - wysokosc;
		this->bx = this->ax + (dolna - this->gorna) / 2 * this->kierunek * -1;
	}
	else {
		this->ay = this->by + wysokosc;
		this->ax = this->bx + (this->gorna - dolna) / 2 * this->kierunek * -1;
	}
}

void Trapez::ZwiekszPole(Trapez& t) {
	double docelowePole = this->GetPole() + t.GetPole();
	double skala = sqrt(docelowePole / this->GetPole());
	this->Skaluj(skala);
}

Trapez* Trapez::SzukajDrugiego(Trapez* t) {
	if (this != t && Trapez::kierunek == (*t).kierunek &&abs(Trapez::gorna - (*t).gorna) < 0.001 &&
		abs(this->ax - (*t).ax) < 0.001 && abs(this->ay - (*t).ay) < 0.001 &&
		abs(this->bx - (*t).bx) < 0.001 && abs(this->by - (*t).by) < 0.001)
		return this;
	else if (this->nastepny != NULL) return this->nastepny->SzukajDrugiego(t);
	else return NULL;
}

void Trapez::SetNastepny(Trapez* t) {
	this->nastepny = t;
}

Trapez* Trapez::GetNastepny() {
	return this->nastepny;
}

double Trapez::GetPole() {
	double dolna = ((this->ax < this->bx && this->kierunek == 1) || (this->ax > this->bx&& this->kierunek == -1)) ? (this->gorna - 2 * abs(this->ax - this->bx)) : (this->gorna + 2 * abs(this->ax - this->bx));
	return (this->gorna + dolna) * 0.5 * (abs(this->ay - this->by));
}

int Trapez::GetLiczbaWszystkich() { // definicja metody statycznej
	return Trapez::liczbaWszystkich;
}

double Trapez::GetPoleWszystkich() { // definicja metody statycznej
	return Trapez::poleWszystkich;
}
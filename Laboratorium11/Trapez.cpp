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

	Trapez::UstawFigure(ax, ay, bx, by, gorna, kierunek);
	Trapez::liczbaWszystkich++;
	Trapez::poleWszystkich += Trapez::GetPole();
}

Trapez::Trapez() : 
	nastepny(NULL), 
	ax(1), ay(1), 
	bx(0), by(0), 
	gorna(1), 
	kierunek(1) {
	Trapez::liczbaWszystkich++;
	Trapez::poleWszystkich += Trapez::GetPole();
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
	Trapez::poleWszystkich += Trapez::GetPole();
}

Trapez::Trapez(Prostokat& p) :
	nastepny(NULL),
	ax(p.ax),
	bx(p.ax),
	gorna(p.pozioma),
	kierunek(p.kPoziomy) {
	if (p.kPionowy == 1) {
		Trapez::ay = p.ay + p.pionowa;
		Trapez::by = p.ay;
	}
	else {
		Trapez::ay = p.ay;
		Trapez::by = p.ay - p.pionowa;
	}
	Trapez::liczbaWszystkich++;
	Trapez::poleWszystkich += Trapez::GetPole();
}

Trapez::~Trapez() {
	Trapez::liczbaWszystkich--;
	Trapez::poleWszystkich -= Trapez::GetPole();
	delete Trapez::nastepny;
}

void Trapez::UstawFigure(double ax, double ay, double bx, double by, double gorna, int kierunek) {
	Trapez::nastepny = NULL;
	Trapez::ax = ax;
	Trapez::ay = ay;
	Trapez::bx = bx;
	Trapez::by = by;
	Trapez::gorna = gorna;
	Trapez::kierunek = kierunek;
}

void Trapez::Wypisz() {
	double dolna = ((ax < bx && kierunek == 1) || (ax > bx&& kierunek == -1)) ? (Trapez::gorna - 2 * abs(ax - bx)) : (Trapez::gorna + 2 * abs(ax - bx));
	double tmp1 = Trapez::ax + (Trapez::gorna * Trapez::kierunek);
	double tmp2 = Trapez::bx + (dolna * Trapez::kierunek);
	printf("wsp. gornej podstawy: (%.1lf, %.1lf) i (%.1lf, %.1lf)\tdl.: %.1lf  \n", Trapez::ax, Trapez::ay, tmp1, Trapez::ay, Trapez::gorna);
	printf("wsp. dolnej podstawy: (%.1lf, %.1lf) i (%.1lf, %.1lf)\tdl.: %.1lf\n\n", Trapez::bx, Trapez::by, tmp2, Trapez::by, dolna);
}

void Trapez::Symetria(double x) {
	Trapez::ax = (Trapez::ax < x) ? (x + abs(Trapez::ax - x)) : (x - abs(Trapez::ax - x));
	Trapez::bx = (Trapez::bx < x) ? (x + abs(Trapez::bx - x)) : (x - abs(Trapez::bx - x));
	Trapez::kierunek = (Trapez::kierunek < 0) ? 1 : -1;
}

void Trapez::Skaluj(double x) {
	double dolna = ((ax < bx && kierunek == 1) || (ax > bx&& kierunek == -1)) ? (Trapez::gorna - 2 * abs(ax - bx)) : (Trapez::gorna + 2 * abs(ax - bx));
	double wysokosc = abs(Trapez::ay - Trapez::by);

	Trapez::gorna *= x;
	dolna *= x;
	wysokosc *= x;

	if (Trapez::gorna < dolna) {
		Trapez::by = Trapez::ay - wysokosc;
		Trapez::bx = Trapez::ax + (dolna - gorna) / 2 * kierunek * -1;
	}
	else {
		Trapez::ay = Trapez::by + wysokosc;
		Trapez::ax = Trapez::bx + (gorna - dolna) / 2 * kierunek * -1;
	}
}

void Trapez::ZwiekszPole(Trapez& t) {
	double docelowePole = Trapez::GetPole() + t.GetPole();
	double skala = sqrt(docelowePole / Trapez::GetPole());
	Trapez::Skaluj(skala);
}

Trapez* Trapez::SzukajDrugiego(Trapez* t) {
	if (this != t && Trapez::kierunek == (*t).kierunek &&abs(Trapez::gorna - (*t).gorna) < 0.001 &&
		abs(Trapez::ax - (*t).ax) < 0.001 && abs(Trapez::ay - (*t).ay) < 0.001 &&
		abs(Trapez::bx - (*t).bx) < 0.001 && abs(Trapez::by - (*t).by) < 0.001)
		return this;
	else if (Trapez::nastepny != NULL) return Trapez::nastepny->SzukajDrugiego(t);
	else return NULL;
}

void Trapez::SetNastepny(Trapez* t) {
	Trapez::nastepny = t;
}

Trapez* Trapez::GetNastepny() {
	return Trapez::nastepny;
}

double Trapez::GetPole() {
	double dolna = ((ax < bx && kierunek == 1) || (ax > bx&& kierunek == -1)) ? (Trapez::gorna - 2 * abs(ax - bx)) : (Trapez::gorna + 2 * abs(ax - bx));
	return (Trapez::gorna + dolna) * 0.5 * (abs(Trapez::ay - Trapez::by));
}

int Trapez::GetLiczbaWszystkich() { // definicja metody statycznej
	return Trapez::liczbaWszystkich;
}

double Trapez::GetPoleWszystkich() { // definicja metody statycznej
	return Trapez::poleWszystkich;
}
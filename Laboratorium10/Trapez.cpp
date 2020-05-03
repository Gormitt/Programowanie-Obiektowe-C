#include "Trapez.h"
#include <iostream>
#include <math.h>

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
	if ((ax < bx && kierunek == 1 && gorna < 2 * abs(ax - bx) + 1.0) || (ax > bx && kierunek == -1 && gorna < 2 * abs(ax - bx) + 1.0)) {
		kierunek = (kierunek < 0) ? 1 : -1;
		printf("error - aby mozna bylo narysowac trapez, zmieniam kierunek rysowania\n");
	}
	
	Trapez::UstawFigure(ax, ay, bx, by, gorna, kierunek);
}

Trapez::Trapez() {
	Trapez::UstawFigure(1, 1, 0, 0, 1, 1);
}

void Trapez::UstawFigure(double ax, double ay, double bx, double by, double gorna, int kierunek) {
	Trapez::ax = ax;
	Trapez::ay = ay;
	Trapez::bx = bx;
	Trapez::by = by;
	Trapez::gorna = gorna;
	Trapez::kierunek = kierunek;
}

void Trapez::Wypisz() {
	double dolna = ((ax < bx && kierunek == 1) || (ax > bx && kierunek == -1)) ? (Trapez::gorna - 2 * abs(ax - bx)) : (Trapez::gorna + 2 * abs(ax - bx));
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

double Trapez::GetPole() {
	double dolna = ((ax < bx && kierunek == 1) || (ax > bx && kierunek == -1)) ? (Trapez::gorna - 2 * abs(ax - bx)) : (Trapez::gorna + 2 * abs(ax - bx));
	return (Trapez::gorna + dolna) * 0.5 * (abs(Trapez::ay - Trapez::by));
}
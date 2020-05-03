#include "Prostokat.h"
#include <iostream>
#include <math.h>

Prostokat::Prostokat(double ax, double ay, double pozioma, double pionowa, int kPoziomy, int kPionowy) {
	kPoziomy = (kPoziomy < 0) ? -1 : 1;
	kPionowy = (kPionowy < 0) ? -1 : 1;
	if (pozioma <= 0) {
		pozioma = 1;
		printf("error - dlugosc pozioma nie moze byc ujemna lub zerowa, zmieniam jej dlugosc na 1\n");
	}
	if (pionowa <= 0) {
		pionowa = 1;
		printf("error - dlugosc pionowa nie moze byc ujemna lub zerowa, zmieniam jej dlugosc na 1\n");
	}

	UstawFigure(ax, ay, pozioma, pionowa, kPoziomy, kPionowy);
}

Prostokat::Prostokat() {
	UstawFigure(0, 0, 1, 1, 1, 1);
}

void Prostokat::UstawFigure(double ax, double ay, double pozioma, double pionowa, int kPoziomy, int kPionowy) {
	Prostokat::ax = ax;
	Prostokat::ay = ay;
	Prostokat::pozioma = pozioma;
	Prostokat::pionowa = pionowa;
	Prostokat::kPoziomy = kPoziomy;
	Prostokat::kPionowy = kPionowy;
}

void Prostokat::Wypisz() {
	double bx = Prostokat::ax + Prostokat::pozioma * Prostokat::kPoziomy;
	double cy = Prostokat::ay + Prostokat::pionowa * Prostokat::kPionowy;
	double dx = Prostokat::ax + Prostokat::pozioma * Prostokat::kPoziomy;
	double dy = Prostokat::ay + Prostokat::pionowa * Prostokat::kPionowy;

	printf("wymiary: %.1lf x %.1lf\n", Prostokat::pozioma, Prostokat::pionowa);
	printf("wsp. podstawy A: (%.1lf, %.1lf) oraz (%.1lf, %.1lf)  \n", Prostokat::ax, Prostokat::ay, bx, Prostokat::ay);
	printf("wsp. podstawy B: (%.1lf, %.1lf) oraz (%.1lf, %.1lf)\n\n", Prostokat::ax, cy, dx, dy);
}

void Prostokat::Symetria(double x) {
	Prostokat::ax = (Prostokat::ax < x) ? (x + abs(Prostokat::ax - x)) : (x - abs(Prostokat::ax - x));
	Prostokat::kPoziomy = (Prostokat::kPoziomy < 0) ? 1 : -1;
}

void Prostokat::Skaluj(double x) {
	Prostokat::pozioma *= x;
	Prostokat::pionowa *= x;
}

void Prostokat::ZwiekszPole(Prostokat& p) {
	double docelowePole = Prostokat::GetPole() + p.GetPole();
	double skala = sqrt(docelowePole / Prostokat::GetPole());
	Prostokat::Skaluj(skala);
}

double Prostokat::GetPole() {
	return Prostokat::pozioma * Prostokat::pionowa;
}
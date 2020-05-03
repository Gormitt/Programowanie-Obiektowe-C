#include <iostream>

#include "Trapez.h"
#include "Prostokat.h"

int main() {
	Prostokat p1(-1, 1, 5, 2, 1, -1);
	Prostokat p2(0, 0, 2, 1, 1, 1);
	p1.Wypisz();
	printf("pole p1: %lf\n\n", p1.GetPole());
	p1.ZwiekszPole(p2);
	p1.Wypisz();
	printf("pole p1: %lf\n\n", p1.GetPole());
	return 0;
}
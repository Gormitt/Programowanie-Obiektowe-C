#include <iostream>

#include "Trapez.h"
#include "Prostokat.h"
#include "Kolekcja.h"

void Info() {
	printf("data: \t4 maj 2020\n");
	printf("autor: \tMateusz Wloczewski\n");
	printf("about: \tRealizacja programu na labolatoria nr. 10\n\n");
}

int main() {
	Info();
	// zadanie I poziomu
	Trapez* trapezA = new Trapez();
	Trapez* trapezB = new Trapez(2, 2, 0, 0, 3, 1);
	Trapez* trapezC = new Trapez(*trapezB);
	Prostokat* prostokatA = new Prostokat();
	Prostokat* prostokatB = new Prostokat(-1, 1, 3, 2, -1, -1);
	Prostokat* prostokatC = new Prostokat(*prostokatB);

	Kolekcja k;
	k.DodajTrapez(trapezA);
	k.DodajTrapez(trapezB);
	k.DodajTrapez(trapezC);
	k.DodajProstokat(prostokatA);
	k.DodajProstokat(prostokatB);
	k.DodajProstokat(prostokatC);

	k.WypiszTrapezy();
	k.WypiszProstokaty();
	k.Symetria(-1);
	k.Skala(2);
	k.WypiszTrapezy();
	k.WypiszProstokaty();

	delete trapezA;
	delete trapezB;
	delete trapezC;
	delete prostokatA;
	delete prostokatB;
	delete prostokatC;

	// zadanie II poziomu
	printf("trapez, ktory zostal stworzony na podstawie prostokata:\n");
	Prostokat* pr = new Prostokat(3, 1, 4, 2, 1, -1);
	Trapez* tr = new Trapez(*pr);
	(*tr).Wypisz();
	delete pr;
	delete tr;
	return 0;

	// wywolania konstruktorow : 7 [3 trapezy, 3 prostokaty, 1 kolekcja]
	// wywolania nastêpuja w miejscach gdzie tworzone sa obiekty tzn. linie 16-21 wlacznie oraz linia 23 [zadanie I poziomu]
	// wywolanie nastêpuje rowniez w liniach 46 i 47 [zadanie II poziomu]
}

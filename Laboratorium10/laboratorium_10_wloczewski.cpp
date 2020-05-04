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
	return 0;

	// wywo³ania konstruktorow : 7 [3 trapezy, 3 prostokaty, 1 kolekcja]
	// wywo³ania nastêuj¹ w miejscach gdzie tworzone s¹ obiekty tzn. linia 15-20 wlacznie oraz 22
}

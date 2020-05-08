#include <iostream>

#include "Trapez.h"
#include "Prostokat.h"
#include "Kolekcja.h"

void Info() {
	printf("data: \t8 maj 2020\n");
	printf("autor: \tMateusz Wloczewski\n");
	printf("about: \tRealizacja programu na labolatoria nr. 11\n\n");
}

int main() {
	Info();
	// zadanie I poziomu
	Trapez* trapezA = new Trapez();
	Trapez* trapezB = new Trapez(2, 2, 0, 0, 3, 1);
	Trapez* trapezC = new Trapez(3, 3, 0, 0, 7, -1);
	Prostokat* prostokatA = new Prostokat();
	Prostokat* prostokatB = new Prostokat(-1, 1, 3, 2, -1, -1);
	Prostokat* prostokatC = new Prostokat(-4, 5, 1, 3, 1, -1);

	Kolekcja* k = new Kolekcja();
	(*k).DodajTrapez(trapezA);
	(*k).DodajTrapez(trapezB);
	(*k).DodajTrapez(trapezC);
	(*k).DodajProstokat(prostokatA);
	(*k).DodajProstokat(prostokatB);
	(*k).DodajProstokat(prostokatC);

	(*k).WypiszTrapezy();
	(*k).WypiszProstokaty();

	Trapez* trLok1 = new Trapez(2, 2, 0, 0, 3, 1); // taki sam jak trapez B
	Prostokat* prLok1 = new Prostokat(-4, 5, 1, 3, 1, -1); // taki sam jak prostokat C

	(*k).Szukaj(trLok1);
	(*k).Szukaj(prLok1);
	delete k;
	delete trLok1;
	delete prLok1;

	// konstruktory : 
	// linie 16-21 [utworzenie obiektow klasy Trapez oraz Prostokat]
	// linia 23    [utworzenie obiektu klasy Kolekcja]
	// destruktory :
	// linia 39    [nastepuje dealokacja obiektu klasy Kolekcja - to powoduje usuniecie kazdego elementu z listy trapezow i prostokatow, zaalokowanych w liniach 16-21]
	// linie 40-41 [nastepuje dealokacja dwoch dodatkowych obiekow spoza listy, ktore sluzyly jako wzor do szukania]

	// zadanie II poziomu
	// nastapila dealokacja Kolekcji k oraz dealokacja trLok1 i prLok1, zatem zmienne statyczne klas Trapez oraz Prostokat w tym miejsu powinny byc wyzerowane
	printf("dealokacja zakonczona\n");
	printf("liczba trapezow:    %d\tpole wszystkich trapezow:    %lf  \n", Trapez::GetLiczbaWszystkich(), Trapez::GetPoleWszystkich());
	printf("liczba prostokatow: %d\tpole wszystkich prostokatow: %lf\n\n", Prostokat::GetLiczbaWszystkich(), Prostokat::GetPoleWszystkich());
	
	return 0;
}

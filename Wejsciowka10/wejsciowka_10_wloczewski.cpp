#include <iostream>
#include <cstdio>
#include <cstring>

#include "Stale.h"
#include "BazaEmail.h"
#include "Wykladowca.h"

int main() {
	char nazwisko1[DL_SLOWA] = "Kowalski";
	char nazwisko2[DL_SLOWA] = "Weiss";
	char nazwisko3[DL_SLOWA] = "Trojan";

	char plik1[DL_SLOWA] = "plik1.txt";
	char plik2[DL_SLOWA] = "plik2.txt";
	char plik3[DL_SLOWA] = "plik3.txt";
	char plik4[DL_SLOWA] = "plik4.txt";

	Wykladowca w1(nazwisko1);			// konstruktor nr. 1
	w1.DodajElement(plik1);
	w1.DodajElement(plik2);

	Wykladowca w2(nazwisko2, plik2);	// konstruktor nr. 2
	w2.DodajElement(plik3);

	Wykladowca w3(nazwisko3, w2);		// konstruktor nr. 3
	w3.DodajElement(plik4);

	w1.WypiszListe();
	w2.WypiszListe();
	w3.WypiszListe();

	// Oprocz konstuktorow oznaczonych w funkcji main:
	// Za kazdym razem, kiedy tworzony jest obiekt klasy wykladowca wywolywany jest rownoczesnie konstruktor klasy BazaEmail.
	// Dzieje sie tak, poniewaz kazdy wykladowca ma swoje grupy studenckie, a kazda grupa studencka jest "schowana" w obiekcie klasy BazaEmail.
	// Ponadto, podczas wywolania metody DodajElement na obiektach klasy Wykladowca, dodawa jest kolejna baza email, zatem wywolywany jest konstruktor tej klasy.
	
	// Zatem oprocz 3 konstruktorow w funkcji main nastepuje 5 wywolan konstruktora klasy BazaEmail.
	// W kodzie latwo to rozpoznac, bo konstruktor klasy BazaEmail jest wywolany tylko w metodzie, ktora za argument przyjmuje nazwe pliku.
	// Pozostale metody kopiuja wskaznik do istniejacej listy dynamicznej [zatem brak tu nowej alokacji konstruktorem] albo tworza pusty obiekt [iniciujac NULL-em].
	return 0;
}
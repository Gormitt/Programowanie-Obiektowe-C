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

	return 0;
}
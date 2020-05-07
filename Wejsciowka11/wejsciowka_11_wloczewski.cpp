#include <iostream>

#include "Wykladowca.h"
#include "Baza.h"

int main() {
	char plik1[DL_SLOWA] = "plik1.txt";
	char plik2[DL_SLOWA] = "plik2.txt";
	char plik3[DL_SLOWA] = "plik3.txt";
	char plik4[DL_SLOWA] = "plik4.txt";
	char plik5[DL_SLOWA] = "plik5.txt";

	Wykladowca w1("Trojanowski");
	w1.DodajGrupe(plik1);
	w1.DodajGrupe(plik2);
	w1.DodajGrupe(plik3);	
	Wykladowca w2("Kowalski", w1);
	w2.DodajGrupe(plik4);
	w2.DodajGrupe(plik5);
	Wykladowca w3("Wloczewski");

	w1.Wypisz();
	w2.Wypisz();
	w3.Wypisz();

	w2.SzukajId(3);
	w2.SzukajId(3);
	w3.SzukajId(3);

	return 0;
}
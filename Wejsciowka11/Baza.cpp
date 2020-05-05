#include <iostream>
#include "Baza.h"

Baza::Baza(int ileMaili) {
	Baza::nastepna = NULL;
	Baza::wielkosc = ileMaili;
	Baza::maile = new char*[ileMaili];
	for (int i = 0; i < ileMaili; i++) {
		Baza::maile[i] = new char[DL_SLOWA];
	}
}

Baza::Baza(Baza& b) {
	Baza::wielkosc = b.wielkosc;
	Baza::maile = new char* [b.wielkosc];
	for (int i = 0; i < b.wielkosc; i++) {
		Baza::maile[i] = new char[DL_SLOWA];
		Baza::SetMail(i, b.GetMail(i));
	}
	if (b.nastepna != NULL) {
		Baza::nastepna = new Baza(*b.nastepna);
	}
	else {
		Baza::nastepna = NULL;
	}
}

void Baza::SetMail(int numer, char* adres) {
	strcpy_s(Baza::maile[numer], DL_SLOWA, adres);
}

char* Baza::GetMail(int numer) {
	return maile[numer];
}
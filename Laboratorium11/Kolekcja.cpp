#include "Stale.h"
#include "Kolekcja.h"
#include "Trapez.h"
#include "Prostokat.h"

#include <iostream>

Kolekcja::Kolekcja() {
	Kolekcja::glowaT = Kolekcja::ogonT = NULL;
	Kolekcja::glowaP = Kolekcja::ogonP = NULL;
}

Kolekcja::~Kolekcja() {
	delete Kolekcja::glowaT; // destrukcja kazdego elementu wywola destrukcje kolejnego
	delete Kolekcja::glowaP;
}

void Kolekcja::DodajTrapez(Trapez* t) {
	if (Kolekcja::glowaT == NULL) {
		Kolekcja::glowaT = t;
		Kolekcja::ogonT = t;
	}
	else {
		Kolekcja::ogonT->SetNastepny(t);
		Kolekcja::ogonT = Kolekcja::ogonT->GetNastepny();
	}
}

void Kolekcja::DodajProstokat(Prostokat* p) {
	if (Kolekcja::glowaP == NULL) {
		Kolekcja::glowaP = p;
		Kolekcja::ogonP = p;
	}
	else {
		Kolekcja::ogonP->SetNastepny(p);
		Kolekcja::ogonP = Kolekcja::ogonP->GetNastepny();
	}
}

void Kolekcja::WypiszTrapezy() {
	printf(COLOR_CYAN "kolekcja trapezow\n");
	printf(COLOR_MAGENTA "{ilosc: %d, suma pol: % lf}\n" COLOR_RESET, Trapez::GetLiczbaWszystkich(), Trapez::GetPoleWszystkich());
	Trapez* tmp = Kolekcja::glowaT;
	while (tmp) {
		tmp->Wypisz();
		tmp = tmp->GetNastepny();
	}
}

void Kolekcja::WypiszProstokaty() {
	printf(COLOR_CYAN "kolekcja prostokatow\n");
	printf(COLOR_MAGENTA "{ilosc: %d, suma pol: %lf}\n" COLOR_RESET, Prostokat::GetLiczbaWszystkich(), Prostokat::GetPoleWszystkich());
	Prostokat* tmp = Kolekcja::glowaP;
	while (tmp) {
		tmp->Wypisz();
		tmp = tmp->GetNastepny();
	}
}

void Kolekcja::Symetria(double x) {
	printf("wykonuje symetrie wszystkich figur w kolekcji wg. osi x = %lf\n\n", x);
	Trapez* tmp1 = Kolekcja::glowaT;
	Prostokat* tmp2 = Kolekcja::glowaP;
	while (tmp1) {
		tmp1->Symetria(x);
		tmp1 = tmp1->GetNastepny();
	}
	while (tmp2) {
		tmp2->Symetria(x);
		tmp2 = tmp2->GetNastepny();
	}
}

void Kolekcja::Skala(double x) {
	printf("wykonuje skalowanie wszystkich figur w kolekcji wg. skali x = %lf\n\n", x);
	Trapez* tmp1 = Kolekcja::glowaT;
	Prostokat* tmp2 = Kolekcja::glowaP;
	while (tmp1) {
		tmp1->Skaluj(x);
		tmp1 = tmp1->GetNastepny();
	}
	while (tmp2) {
		tmp2->Skaluj(x);
		tmp2 = tmp2->GetNastepny();
	}
}

void Kolekcja::Szukaj(Trapez* t) {
	printf(COLOR_NIEBIESKI "info - szukam kopii trapezu o wskazniku %p\n", t);
	if (glowaT != NULL) {
		Trapez* tmp = Kolekcja::glowaT->SzukajDrugiego(t);
		if (tmp != NULL) {
			printf(COLOR_ZIELONY "info - identyczna figura ma wskaznik %p\n" COLOR_RESET, tmp);
			tmp->Wypisz();
		}
		else {
			printf(COLOR_ZOLTY "info - w liscie nie ma drugiej takiej samej figury\n\n" COLOR_RESET);
		}
	}
	else {
		printf(COLOR_CZERWONY "error - lista trapezow jest pusta\n\n" COLOR_RESET);
	}
}

void Kolekcja::Szukaj(Prostokat* p) {
	printf(COLOR_NIEBIESKI "info - szukam kopii prostokata o wskazniku %p\n", p);
	if (glowaP != NULL) {
		Prostokat* tmp = Kolekcja::glowaP->SzukajDrugiego(p);
		if (tmp != NULL) {
			printf(COLOR_ZIELONY "info - identyczna figura ma wskaznik %p\n" COLOR_RESET, tmp);
			tmp->Wypisz();
		}
		else {
			printf(COLOR_ZOLTY "info - w liscie nie ma drugiej takiej samej figury\n\n" COLOR_RESET);
		}
	}
	else {
		printf(COLOR_CZERWONY "error - lista prostokatow jest pusta\n\n" COLOR_RESET);
	}
}
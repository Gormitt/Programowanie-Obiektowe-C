#include "Kolekcja.h"
#include "Trapez.h"
#include "Prostokat.h"

#include <iostream>

Kolekcja::Kolekcja() {
	Kolekcja::glowaT = Kolekcja::ogonT = NULL;
	Kolekcja::glowaP = Kolekcja::ogonP = NULL;
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
	printf("kolekcja trapezow: \n");
	Trapez* tmp = Kolekcja::glowaT;
	while (tmp) {
		tmp->Wypisz();
		tmp = tmp->GetNastepny();
	}
}

void Kolekcja::WypiszProstokaty() {
	printf("kolekcja prostokatow: \n");
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
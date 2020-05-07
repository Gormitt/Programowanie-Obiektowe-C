#include <iostream>

#include "Wykladowca.h"
#include "Baza.h"

Wykladowca::Wykladowca(const char* nazwisko) {
	strcpy_s(Wykladowca::nazwisko, DL_SLOWA, nazwisko);
	Wykladowca::glowa = NULL;
	Wykladowca::ogon = NULL;
}

Wykladowca::Wykladowca(const char* nazwisko, char* plik) {
	strcpy_s(Wykladowca::nazwisko, DL_SLOWA, nazwisko);
	Wykladowca::glowa = new Baza(1, plik);
	Wykladowca::ogon = Wykladowca::glowa;
}

Wykladowca::Wykladowca(const char* nazwisko, Wykladowca& w) {
	strcpy_s(Wykladowca::nazwisko, DL_SLOWA, nazwisko);
	
	Wykladowca::glowa = NULL;
	Wykladowca::ogon = NULL;
	Baza* tmp = w.glowa;
	while (tmp) {
		if (Wykladowca::glowa == NULL) {
			Wykladowca::glowa = new Baza(1, *tmp);
			Wykladowca::ogon = Wykladowca::glowa;
		}
		else {
			Wykladowca::ogon->SetNastepna(new Baza(Wykladowca::ogon->GetId() + 1, *tmp));
			Wykladowca::ogon = Wykladowca::ogon->GetNastepny();
		}
		tmp = tmp->GetNastepny();
	}
}

Wykladowca::~Wykladowca() {
	/*
	while (Wykladowca::glowa) {
		Baza* tmp = Wykladowca::glowa->GetNastepny();
		delete Wykladowca::glowa;
		Wykladowca::glowa = tmp;
	}
	*/
	delete Wykladowca::glowa;
}

void Wykladowca::Wypisz() {
	printf(ANSI_COLOR_GREEN "prof. %s\n" ANSI_COLOR_RESET, Wykladowca::nazwisko);
	if (Wykladowca::glowa != NULL) {
		char litera = 'A';
		Baza* tmp = Wykladowca::glowa;
		while (tmp) {
			tmp->WypiszMaile();
			tmp = tmp->GetNastepny();
			litera++;
		}
		printf("\n");
	}
	else {
		printf("brak grup studenckich\n\n");
	}
}

void Wykladowca::DodajGrupe(char* plik) {
	if (Wykladowca::glowa == NULL) {
		Wykladowca::glowa = new Baza(1, plik);
		Wykladowca::ogon = Wykladowca::glowa;
	}
	else {
		Wykladowca::ogon->SetNastepna(new Baza(Wykladowca::ogon->GetId() + 1, plik));
		Wykladowca::ogon = Wykladowca::ogon->GetNastepny();
	}
}

void Wykladowca::SzukajId(int id) {
	printf("info - [prof. %s] rozpoczynam poszukiwania gr. o id: %d\n", Wykladowca::nazwisko, id);
	if (Wykladowca::glowa == NULL) {
		printf("error - prof. %s nie posiada zadnej przypisanej grupy\n\n", Wykladowca::nazwisko);
	}
	else {
		Baza* tmp = Wykladowca::glowa->SzukajId(id);
		if (tmp == NULL) {
			printf("info - prof. %s nie posiada grupy o ID: %d\n\n", Wykladowca::nazwisko, id);
		}
		else {
			printf("info - znaleziono grupe\n");
			tmp->WypiszMaile();
		}
	}
}
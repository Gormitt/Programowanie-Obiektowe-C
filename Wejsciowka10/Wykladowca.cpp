#include "Stale.h"
#include "Wykladowca.h"
#include <iostream>

Wykladowca::Wykladowca(char* nazwisko) {
	Wykladowca::baza = NULL;
	Wykladowca::ostatni = NULL;
	strcpy_s(Wykladowca::nazwisko, DL_SLOWA, nazwisko);
}

Wykladowca::Wykladowca(char* nazwisko, char* nazwa) {
	FILE* in;
	if (fopen_s(&in, nazwa, "r") == 0 && in != NULL) {
		int liczba = 0;
		char mail[DL_TABLICY] = { '\0' };
		while (!feof(in)) {
			fscanf_s(in, "%s", mail, DL_TABLICY);
			if (strlen(mail) > 0) liczba++;
		}
		rewind(in);

		BazaEmail* b = new BazaEmail(liczba);
		for (int i = 0; i < liczba; i++) {
			fscanf_s(in, "%s", mail, DL_TABLICY);
			(*b).SetEmail(mail, i);
		}
		Wykladowca::baza = b;
		Wykladowca::ostatni = b;
		fclose(in);
	}
	else {
		printf("error - nie udalo sie otworzyc pliku [utworzenie listy nieudane]\n");
		Wykladowca::baza = NULL;
		Wykladowca::ostatni = NULL;
	}
	strcpy_s(Wykladowca::nazwisko, DL_SLOWA, nazwisko);
}

Wykladowca::Wykladowca(char* nazwisko, Wykladowca& w) {
	Wykladowca::baza = NULL;
	Wykladowca::ostatni = NULL;
	if (w.baza != NULL) {
		BazaEmail* wsk = w.baza;
		while (wsk) {
			if (Wykladowca::baza == NULL) {
				Wykladowca::baza = new BazaEmail(*wsk);
				Wykladowca::ostatni = Wykladowca::baza;
			}
			else {
				BazaEmail* tmp = new BazaEmail(*wsk);
				Wykladowca::ostatni->SetNast(tmp);
				Wykladowca::ostatni = tmp;
			}
			wsk = wsk->GetNast();
		}
	}
	strcpy_s(Wykladowca::nazwisko, DL_SLOWA, nazwisko);
}

Wykladowca::~Wykladowca() {
	while (Wykladowca::baza) {
		BazaEmail* tmp = Wykladowca::baza->GetNast();
		for (int i = 0; i < Wykladowca::baza->GetIle(); i++) {
			printf("destruktor [%s] \tusuwam maila %s\n", Wykladowca::nazwisko, Wykladowca::baza->GetEmail(i));
			delete Wykladowca::baza->GetEmail(i); // usuwanie przydzialu pamieci na kazdego maila w bazie
		}
		printf("destruktor [%s]\tusuwam tablice maili\n", Wykladowca::nazwisko);
		delete Wykladowca::baza->GetEmaile(); // usuwanie przydzialu na wskazniki do kazdego maila w bazie
		printf("destruktor [%s]\tusuwam baze studnedow\n", Wykladowca::nazwisko);
		delete Wykladowca::baza; // usuwanie przydzialu pamieci na element listy dynamicznej
		Wykladowca::baza = tmp;
	}
}

void Wykladowca::DodajElement(const char* nazwa) {
	FILE* in;
	if (fopen_s(&in, nazwa, "r") == 0 && in != NULL) {
		int liczba = 0;
		char mail[DL_TABLICY] = { '\0' };
		while (!feof(in)) {
			fscanf_s(in, "%s", mail, DL_TABLICY);
			if (strlen(mail) > 0) liczba++;
		}
		rewind(in);

		BazaEmail* b = new BazaEmail(liczba);
		for (int i = 0; i < liczba; i++) {
			fscanf_s(in, "%s", mail, DL_TABLICY);
			(*b).SetEmail(mail, i);
		}

		if (Wykladowca::ostatni == NULL) { // dodajmey pierwszy element
			Wykladowca::baza = b;
			Wykladowca::ostatni = b;
		}
		else { // dodajemy niepierwszy element
			Wykladowca::ostatni->SetNast(b);
			Wykladowca::ostatni = b;
		}
		fclose(in);
	}
	else {
		printf("error - nie udalo sie otworzyc pliku [dodanie elementu nieudane]\n");
	}
}

void Wykladowca::WypiszListe(void) {
	BazaEmail* wsk = Wykladowca::baza;
	
	int numer = 1;
	printf("wykladowca: %s\n", Wykladowca::nazwisko);
	while (wsk) {
		printf("grupa studencka numer %d.\n", numer);
		for (int i = 0; i < wsk->GetIle(); i++) {
			printf("mail nr. %d: %s\n", i + 1, wsk->GetEmail(i));
		}
		printf("\n");
		
		numer++;
		wsk = wsk->GetNast();
	}
	printf("\n");
}
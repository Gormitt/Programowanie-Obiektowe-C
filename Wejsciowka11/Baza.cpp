#include <iostream>

#include "Baza.h"

Baza::Baza(int id, int ileMaili) {
	char tmp[DL_SLOWA] = "";
	Baza::nastepna = NULL;
	Baza::id = id;
	Baza::wielkosc = ileMaili;
	Baza::maile = new char*[ileMaili];
	for (int i = 0; i < ileMaili; i++) {
		Baza::maile[i] = new char[DL_SLOWA];
		Baza::SetMail(i, tmp);
	}
}

Baza::Baza(int id, Baza& b) {
	char tmp[DL_SLOWA] = "";
	Baza::id = id;
	Baza::wielkosc = b.wielkosc;
	Baza::maile = new char* [b.wielkosc];
	for (int i = 0; i < b.wielkosc; i++) {
		Baza::maile[i] = new char[DL_SLOWA];
		Baza::SetMail(i, tmp);
		Baza::SetMail(i, b.GetMail(i));
	}
	if (b.nastepna != NULL) {
		Baza::nastepna = new Baza(*b.nastepna);
	}
	else {
		Baza::nastepna = NULL;
	}
}

Baza::Baza(int id, char* plik) {
	Baza::nastepna = NULL;
	Baza::id = id;

	FILE* in;
	if (fopen_s(&in, plik, "r") == 0 && in != NULL) {
		int liczba = 0;
		char slowo[DL_SLOWA] = "";
		char poprzednie[DL_SLOWA] = "";
		
		while (!feof(in)) {
			fscanf_s(in, "%s", slowo, DL_SLOWA);
			if (memcmp(slowo, poprzednie, DL_SLOWA) == 0) {
				break;
			}
			else {
				liczba++;
				strcpy_s(poprzednie, DL_SLOWA, slowo);
			}
		}
		rewind(in);

		Baza::wielkosc = liczba;
		Baza::maile = new char* [wielkosc];
		for (int i = 0; i < liczba; i++) {
			fscanf_s(in, "%s", slowo, DL_SLOWA);
			Baza::maile[i] = new char[DL_SLOWA];
			Baza::SetMail(i, slowo);
		}
		fclose(in);
	}
	else {
		printf("error - blad podczas otwarcia pliku %s, nie udalo sie utworzyc bazy\n", plik);
		Baza::wielkosc = 0;
		Baza::maile = NULL;
	}
}

Baza::~Baza() {
	// 1. dealokacja dynamicznych elementow obiektu tj.: kazdego slowa w tablicy maile oraz tablicy maile
	// 2. instrukcja delete::nastepna wywola taki sam destruktor, ale dla kolejnego obiektu w lisccie itd. az do NULL
	// wniosek: dealokacja glowy spowoduje dealokacje calej listy, dlatego destruktor w wykladowcy dealokuje tylko pierwszy element
	for (int i = 0; i < Baza::wielkosc; i++) {
		//printf("usuwam slowo %s\n", Baza::maile[i]);
		delete Baza::maile[i];
	}
	//printf("usuwam tablice\n");
	delete Baza::maile;
	delete Baza::nastepna;
}

void Baza::WypiszMaile() {
	if (Baza::wielkosc != 0) {
		printf("ID grupy: %d ~ [rekordy: %d]\n", Baza::id , Baza::wielkosc);
		for (int i = 0; i < Baza::wielkosc; i++) {
			printf(ANSI_COLOR_BLUE "mail nr. %d: " ANSI_COLOR_RESET, i + 1);
			if (strlen(Baza::maile[i]) > 1) printf("%s\n", Baza::maile[i]);
			else printf("<brak_wartosci>\n");
		}
		printf("\n");
	}
	else {
		printf("baza maili jest pusta\n\n");
	}
}

Baza* Baza::SzukajId(int id) {
	if (Baza::id == id) return this;
	else if (Baza::nastepna != NULL) return Baza::GetNastepny()->SzukajId(id);
	else return NULL;
}

void Baza::SetMail(int numer, char* adres) {
	strcpy_s(Baza::maile[numer], DL_SLOWA, adres);
}

void Baza::SetNastepna(Baza* b) {
	Baza::nastepna = b;
}

char* Baza::GetMail(int numer) {
	return maile[numer];
}

int Baza::GetId() {
	return Baza::id;
}

Baza* Baza::GetNastepny() {
	return Baza::nastepna;
}
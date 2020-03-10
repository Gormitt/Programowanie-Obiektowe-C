#include <iostream>
#include <stdlib.h>
#include <string.h>

#define DL_NAP 20
#define DL_TAB 5

#define ERROR_DLUGOSC_SLOWA printf("error - podane slowo jest za dlugo, prosze spbouj ponownie: ");

struct Para {
	char napis[DL_NAP];
	int liczba;
};

/*
@ brief Funkcja do wypisania info o programie i autorze
*/
void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t8 mar 2020\n");
	printf("about: \tRozwiazanie wejsciowki nr. 4\n");
	printf("\tProgram wczytuje dane z pliku A, zmienia je i zapisuje do pliku B.\n\n");
}

/*
@ brief Funkcja do czyszczenia bufora.
*/
void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

/*
@ brief Funkcja do zainicjowania tablicy struktur
@ param *p - wskaznik do tablicy struktur
*/
void ZainicujKolekcje(struct Para* p) {
	for (int i = 0; i < DL_TAB; i++) {
		p[i].liczba = i;
		strcpy_s(p[i].napis, "napis");
	}
}

/*
@ brief Funkcja do wczytania slowa
@ param *s - wskaznik do tablicy przechowujacej slowo
*/
void WczytajSlowo(char* s) {
	while (scanf_s("%s", s, DL_NAP) != 1 || getchar() != '\n') {
		CzyszczenieBufora();
		ERROR_DLUGOSC_SLOWA
	}
}

/*
@ brief Funkcja do oczytania jednego wiersza z pliku.
@ param *f - wskaznik do otwartego pliku
@ param *p - wskaznik do tablicy par [para to struktura]
@ ret   0 - w przypadku niepoprawnego wczytania jednego wiersza
        1 - w przypadku poprawnego wczytania jednego wiersza
*/
int Wiersz(FILE* f, struct Para* p) {
	char napis[DL_NAP] = { '\0' };
	for (int i = 0; i < 3; i++) {
		fscanf_s(f, "%s", napis, DL_NAP);
		
		if (feof(f) && i < 1) {
			return 0;
		}
		else {
			// printf("%s\t", napis);
			if (i == 1) {
				//printf("nazwisko to: %s\t", napis);
				strcpy_s(p->napis, napis);
			}
			else if (i == 2) {
				//printf("ocena to: %d", atoi(napis));
				p->liczba = atoi(napis);
			}
		}
	}
	//printf("\n");
	return 1;
}

int main() {
	Info();

	FILE* plik;
	char nazwaWejscia[DL_NAP];
	char nazwaWyjscia[DL_NAP];
	struct Para dane[DL_TAB];
	
	ZainicujKolekcje(dane);

	printf("podaj nazwe pliku wejsciowego: ");
	WczytajSlowo(nazwaWejscia);
	printf("podaj nazwe pliku wyjsciowego: ");
	WczytajSlowo(nazwaWyjscia);
	printf("\n\n");
	
	int indeks = 0, liczbaLinii = 0;
	if (fopen_s(&plik, nazwaWejscia, "r") == 0 && plik != NULL) {
		while (!feof(plik)) {
			liczbaLinii += Wiersz(plik, &dane[indeks]);
			indeks++;
		}
		fclose(plik);
	}
	else {
		printf("error - nie udalo sie otworzyc podanego pliku\n");
	}

	for (int i = 0; i < liczbaLinii; i++) {
		printf("nazwisko: %s\tocena: %d\n", dane[i].napis, dane[i].liczba);
	}

	return 0;
}
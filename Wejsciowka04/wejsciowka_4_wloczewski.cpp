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

/*
@ brief Funkcja sprawdza czy dany znak to samogloska.
@ param c - sprawdzany znak
@ ret   0 - jezeli podany znak to NIE samogloska
@ ret   1 - jezeli podany to JEST samogloska
*/
int CzySamogloska(char c) {
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') return 1;
	else return 0;
}

int main() {
	Info(); // wyswietlenie info o programie

	FILE* plikWejscie, *plikWyjscie;
	char nazwaWejscia[DL_NAP]; // miejsce na nazwe pliku wejsciowego
	char nazwaWyjscia[DL_NAP]; // miejsca na nazwe pliku wyjsciowego
	struct Para dane[DL_TAB]; // tablica struktur, kazda struktura przechowuje nazwisko i ocene studenta
	
	ZainicujKolekcje(dane); // wpisanie do tablicy struktur poczatkowych wartosci

	printf("podaj nazwe pliku wejsciowego: ");
	WczytajSlowo(nazwaWejscia);
	printf("podaj nazwe pliku wyjsciowego: ");
	WczytajSlowo(nazwaWyjscia);
	printf("\n\n");
	
	int indeks = 0, liczbaLinii = 0;
	if (fopen_s(&plikWejscie, nazwaWejscia, "r" ) == 0 && plikWejscie != NULL && 
		fopen_s(&plikWyjscie, nazwaWyjscia, "a+") == 0 && plikWyjscie != NULL) {

		while (!feof(plikWejscie)) {
			int aktualnyStatus = Wiersz(plikWejscie, &dane[indeks]);
			if (aktualnyStatus) {
				char zakodowanyNapis[DL_NAP];
				int tmp = 0;
				while (dane[indeks].napis[tmp] != '\0') {
					if (CzySamogloska(dane[indeks].napis[tmp])) zakodowanyNapis[tmp] = '*';
					else zakodowanyNapis[tmp] = dane[indeks].napis[tmp];
					tmp++;
				}
				zakodowanyNapis[tmp] = '\0';
				fprintf(plikWyjscie, "%s %d\n", zakodowanyNapis, dane[indeks].liczba);
			}
			liczbaLinii += aktualnyStatus;
			indeks++;
		}
		fclose(plikWejscie);
		fclose(plikWyjscie);
	}
	else {
		printf("error - nie udalo sie otworzyc jednego z podanych plikow\n");
	}

	
	for (int i = 0; i < liczbaLinii; i++) {
		printf("nazwisko: %s\tocena: %d\n", dane[i].napis, dane[i].liczba);
	}
	

	return 0;
}
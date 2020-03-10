#include <iostream>
#include <stdlib.h>
#include <string.h>

#define DL_NAP 20
#define DL_TAB 5

struct Para {
	char napis[DL_NAP];
	char liczba[DL_NAP];
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
@ brief Funkcja do oczytania jednego wiersza z pliku.
@ param *f - wskaznik do otwartego pliku
@ param *p - wskaznik do tablicy par [para to struktura]
@ ret   0 - w przypadku niepoprawnego wczytania jednego wiersza
        1 - w przypadku poprawnego wczytania jednego wiersza
*/
int Wiersz(FILE* f, Para* p) {
	char napis[DL_NAP];
	for (int i = 0; i < 3; i++) {
		fscanf_s(f, "%s", napis, DL_NAP);
		
		if (feof(f) && i < 1) {
			return 0;
		}
		else {
			printf("%s\t", napis);
		}
	}
	printf("\n");
	return 1;
}

void Test1(Para *p) {
	*p->liczba = 5;
	strcpy_s(p->napis, "test");
}
void Test2(Para* p) {
	printf("%d\t%s\n", *p->liczba, p->napis);
}


int main() {	
	FILE* plik;
	Para dane [DL_TAB];
	char napis[DL_NAP];

	for (int i = 0; i < DL_TAB; i++) {
		Test1(&dane[i]);
		Test2(&dane[i]);
	}
	printf("\n\n");

	if (fopen_s(&plik, "plik_wejscie.txt", "r") == 0 && plik != NULL) {
		while (!feof(plik)) {
			Wiersz(plik, dane);
		}
		fclose(plik);
	}
	else {
		printf("error - nie udalo sie otworzyc podanego pliku\n");
	}

	return 0;
}
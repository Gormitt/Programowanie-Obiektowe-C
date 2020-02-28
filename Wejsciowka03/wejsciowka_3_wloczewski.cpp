#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define MAX_DLUGOSC_NAPISU 20
#define ILOSC_STRUKTUR 7
#define LICZBA_MAX 10

#define ANSI_ZIELONY "\x1b[35m"
#define ANSI_NIEBIESKI "\x1b[36m"
#define ANSI_BIALY "\x1b[0m"

struct struktura {
	char slowo[MAX_DLUGOSC_NAPISU];
	int liczba;
};

void UzupelnijKolekcje(struktura* wsk) {
	for (int i = 0; i < ILOSC_STRUKTUR; i++) {
		int liczba = rand() % LICZBA_MAX + 1;
		int iloscLiter = rand() % (MAX_DLUGOSC_NAPISU - 1) + 1;

		wsk[i].liczba = liczba;
		for (int j = 0; j < iloscLiter; j++) {
			char znak = rand() % ('z' - 'a' + 1) + 'a';
			wsk[i].slowo[j] = znak;
		}
		wsk[i].slowo[iloscLiter] = '\0';
	}
}

void WypiszKolekcje	(struktura* wsk) {
	for (int i = 0; i < ILOSC_STRUKTUR; i++) {
		printf("kolekcja nr. %d: \n", i + 1);
		printf("nazwa:\t");
		printf(ANSI_NIEBIESKI "%s\n" ANSI_BIALY, wsk[i].slowo);
		printf("liczba:\t");
		printf(ANSI_ZIELONY "%d\n\n" ANSI_BIALY, wsk[i].liczba);
	}
}

int main() {
	srand(time(NULL));
	struktura kolekcja[ILOSC_STRUKTUR];

	UzupelnijKolekcje(kolekcja);
	WypiszKolekcje(kolekcja);
	return 0;
}
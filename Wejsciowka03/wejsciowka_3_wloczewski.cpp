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

/*
@ brief Funkcja do wypisania informacji o programie.
*/
void Info() {
	printf("autor:\tMateusz Wloczewski\n");
	printf("data:\t28 lut 2020\n");
	printf("about: \tWejsciowka na laboratoria 3.\n\n\n");
}

/*
@ brief Funkcja do uzupelniania struktury danymi.
@ param *wsk - wskaznik tablicy struktur struktury
*/
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

/*
@ brief Funkcja do wypisania struktury na ekran.
@ param *wsk - wskaznik tablicy struktur struktury
*/
void WypiszKolekcje(struktura* wsk) {
	printf("Wypisuje kolekcje, czyli tablice struktur: \n");
	for (int i = 0; i < ILOSC_STRUKTUR; i++) {
		printf("kolekcja nr. %d: \n", i + 1);
		printf("nazwa:\t");
		printf(ANSI_NIEBIESKI "%s\n" ANSI_BIALY, wsk[i].slowo);
		printf("liczba:\t");
		printf(ANSI_ZIELONY "%d\n" ANSI_BIALY, wsk[i].liczba);
	}
	putchar('\n');
}

/*
@ brief Funkcja do skracania napisow w kolekcji struktur.
        Jezeli napis jest dluzszy niz liczba przechowywana
		przez strukture, to napisa jest skracany do dlugosci
		rownej przechowywanej liczbie. W pozostalym wypadku
		napis jest pozostawiony w niezmienionej formie.
@ param *wsk - wskaznik do tablicy struktur
*/
int SkrocNapisyWKolekcji(struktura* wsk) {
	int n = 0;
	for (int i = 0; i < ILOSC_STRUKTUR; i++) {
		int dlugoscNapisu = strlen(wsk[i].slowo); // pobieram dane o dlugosci slowa i slowie, aby wygodniej sie na nich operowalo
		int liczba = wsk[i].liczba;
		if (dlugoscNapisu > wsk[i].liczba) {
			wsk[i].slowo[liczba] = '\0';
		}
	}
	return n;
}

int main() {
	srand(time(NULL));
	struct struktura kolekcja[ILOSC_STRUKTUR];

	Info();
	UzupelnijKolekcje(kolekcja);
	WypiszKolekcje(kolekcja);
	
	int liczbaSkroconychNapisow = SkrocNapisyWKolekcji(kolekcja);
	printf("Program wykonal %d skrocen slow w kolekcjach.\n", liczbaSkroconychNapisow);
	WypiszKolekcje(kolekcja);

	printf("Koniec programu.\n\n");
	return 0;
}
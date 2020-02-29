#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define MAX_DLUGOSC_NAPISU 20
#define ILOSC_STRUKTUR 4
#define LICZBA_MAX 10

#define ERROR_WCZYTYWANIE printf("ERROR - blad podczas wczytywanie, prosze sprobuj ponownie: ");
#define ERROR_ZAKRES printf("ERROR - podana liczba wykracza poza zakres, prosze sprobuj ponownie: ");

#define ANSI_ZIELONY  "\x1b[32m"
#define ANSI_ROZOWY "\x1b[35m"
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
	printf("about: \tWejsciowka na laboratoria 3.\n\t**Poprzez kolekcje rozumie sie tablice struktur.\n\n");
}

/*
@ brief Funkcja do czyszczenia bufora.
*/
void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

/*
@ brief Funkcja do wczytywania liczby calkowitej z przedzialu domknietego [min, max].
@ param min - minimalna wartosc
@ param max - maksymalna wartosc
@ param *wsk - wskaznik do zmiennej, w ktorej ma wyladawac pobrana liczba
*/
void WczytajLiczbe(int min, int max, int* wsk) {
	int wpis = 0, pierwszaProba = 1;
	do {
		if (pierwszaProba) {
			pierwszaProba = 0;
			printf("wczytywanie liczby z przedzialu [%d, %d]: ", min, max);
		}
		else {
			ERROR_ZAKRES
		}
		while (scanf_s("%d", &wpis) != 1 || getchar() != '\n') {
			CzyszczenieBufora();
			ERROR_WCZYTYWANIE
		}
	} while (wpis < min || wpis > max);
	*wsk = wpis;
}

/*
@ brief Funkcja do wczytania slowa.
@ param *slowo - wskaznik do tablicy, gdzie ma wyladowac slowo
*/
void WczytajSlowo(char* slowo) {
	char wpis[MAX_DLUGOSC_NAPISU];
	printf("wczytywanie slowa: ");
	while (scanf_s("%s", wpis, (unsigned)_countof(wpis)) != 1 || getchar() != '\n') {
		CzyszczenieBufora();
		ERROR_WCZYTYWANIE
	}
	for (int i = 0; i < MAX_DLUGOSC_NAPISU; i++) {
		slowo[i] = wpis[i];
	}
}

/*
@ brief Funkcja do uzupelniania struktury danymi.
@ param *wsk - wskaznik tablicy struktur struktury
*/
void NadajKolekcjiWartosciPoczatkowe(struct struktura* wsk) {
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
void WypiszKolekcje(struct struktura* wsk) {
	printf("Wypisuje kolekcje, czyli tablice struktur: \n");
	for (int i = 0; i < ILOSC_STRUKTUR; i++) {
		printf("struktura " ANSI_ZIELONY "nr.%d" ANSI_BIALY ": ", i + 1);
		printf("liczba:" ANSI_ROZOWY "%2d " ANSI_BIALY, wsk[i].liczba);
		printf("slowo: " ANSI_NIEBIESKI "%s\n" ANSI_BIALY, wsk[i].slowo);
	}
	putchar('\n');
}

/*
@ brief Funkcja do skracania napisow w kolekcji struktur.
        Jezeli napis jest dluzszy niz liczba przechowywana
        przez strukture, to napisa jest skracany do dlugosci
        rownej przechowywanej liczbie. W przeciwnym wypadku
        napis jest pozostawiony w niezmienionej formie.
@ param *wsk - wskaznik do tablicy struktur
@ ret   n - ilosc wykonanych skrocen
*/
int SkrocNapisyWKolekcji(struct struktura* wsk) {
	int n = 0;
	for (int i = 0; i < ILOSC_STRUKTUR; i++) {
		int dlugoscNapisu = strlen(wsk[i].slowo); // pobieram dane o dlugosci slowa i slowie, aby wygodniej sie na nich operowalo
		int liczba = wsk[i].liczba;
		if (dlugoscNapisu > wsk[i].liczba) {
			n++;
			wsk[i].slowo[liczba] = '\0';
		}
	}
	return n;
}

/*
@ brief Funkcja do uzupelnienia kolekcji.
@ param *wsk - wskaznik do kolekcji
*/
void WpiszDaneDoKolekcji(struct struktura* wsk) {
	for (int i = 0; i < ILOSC_STRUKTUR; i++) {
		int wczytanaLiczba;
		char wczytaneSlowo[MAX_DLUGOSC_NAPISU];
		printf("prosze podaj liczbe, ");
		WczytajLiczbe(1, LICZBA_MAX, &wczytanaLiczba);
		printf("prosze podaj slowo, ");
		WczytajSlowo(wczytaneSlowo);

		wsk[i].liczba = wczytanaLiczba;
		for (int j = 0; j < MAX_DLUGOSC_NAPISU; j++) {
			wsk[i].slowo[j] = wczytaneSlowo[j];
		}
	}
}


int main() {
	srand(time(NULL)); // ustawienie ziarna losowania
	struct struktura kolekcja[ILOSC_STRUKTUR]; // zadeklarowanie tablicy struktur

	Info(); // wypisanie info o programie
	printf("Wygenerowano poczatkowe wartosci %d struktur.\n", ILOSC_STRUKTUR);
	NadajKolekcjiWartosciPoczatkowe(kolekcja); // nadanie kolekcji poczatkowych wartosci
	WypiszKolekcje(kolekcja); // wypisanie kolekcji z nadanymi wartosciami
	
	WpiszDaneDoKolekcji(kolekcja); // wczytanie od uzytkownika nowych danych do kolekcji

	int liczbaSkroconychNapisow = SkrocNapisyWKolekcji(kolekcja); // skrocenie napisow, tak jak prosza w zadaniu 
	printf("Program wykonal %d skrocen slow w kolekcjach.\n", liczbaSkroconychNapisow);	// wypisanie ilosci skrocen
	WypiszKolekcje(kolekcja); // wypisanie kolekcji

	printf("Koniec programu.\n\n");
	return 0;
}
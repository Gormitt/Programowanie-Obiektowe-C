#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DL_SLOWA 20
#define ROZMIAR_TAB 15
#define ERROR_ALOKACJA printf("error - blad podczas alokacji tablicy");
#define ERROR_LICZBA printf("error - blad podczas wczytywania liczby, prosze sprobuj ponownie: ");
#define ERROR_NAPIS printf("error - blad podczas wczytywania napisu, prosze sprobuj ponownie: ");
#define ERROR_ZAKRES printf("error - podana liczba jest spoza zakresu, prosze sprobuj ponownie: ");
#define ERROR_PLIK printf("error - nie udalo sie otworzyc pliku o podanej nazwie");

/*
@ brief Funkcja do wypisania informacji o programie i autorze
*/
void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t16 mar 2020\n");
	printf("about: \tWejsciowka na laboratoria nr. 5\n");
	printf("\tProgram wczyta z pliku liczby binarne i je przekonwertuje.\n");
	printf("\tW kolejnym kroku, uporzadkuje je malejaco.\n\n");
}

/*
@ brief Funkcja do czyszczenie bufora
*/
void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

/*
@ brief Funkcja do wczytywania liczby calkowitej z przedzialu [min, max]
@ param cost *info - wiadomosc tekstowa do uzytkownika
@ param *wpis - wskaznik do miejsca gdzie ma wyladowac wczytana liczba
@ param min - minimalna liczba
@ param max - maksymalna liczba
*/
void WczytajLiczbe(const char* info, int* wpis, int min, int max) {
	int pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("%s, wczytywanie liczby z przedzialu [%d, %d]: ", info, min, max);
		}
		else {
			ERROR_ZAKRES
		}
		while (scanf_s("%d", wpis) != 1 || getchar() != '\n') {
			CzyszczenieBufora();
			ERROR_LICZBA
		}
	} while (*wpis < min || *wpis > max);
}

/*
@ brief Funkcja do wczytania slowa
*/
void WczytajSlowo(const char* info, char* s) {
	printf("%s, wczytywanie slowa: ", info);
	while (scanf_s("%s", s, DL_SLOWA) != 1 || getchar() != '\n') {
		CzyszczenieBufora();
		ERROR_NAPIS
	}
}

/*
@ brief Funkcja do konwersji liczby binarner na decymalna, bez znajomosci dlugosci
		Funkcja nie zna dlugosci liczby, dlatego korzysta z postaci iloczynowej.
@ param *bin - wskaznik do tablicy binarner
@ ret   dec - wartosc liczby binarnej bin
*/
int Bin2Int(char* bin) {
	int dec = 0;
	for (int i = 0; bin[i] != '\0'; i++) {
		dec *= 2;
		dec += (int)(bin[i] - '0');
	}
	return dec;
}

/*
@ brief Funkcja do zaalokowania macierzy na chary
@ param n - liczba wierszy
@ param m - liczba rzedow
@ ret   **tab - wskaznik do nowa zaalokowanej tablicy
*/
char** ZaalokujTablice(int n, int m) {
	char** tab = (char**)calloc(sizeof(char*), n);
	if (tab != NULL) {
		for (int i = 0; i < n; i++) {
			tab[i] = (char*)calloc(sizeof(char), m);
		}
	}
	else {
		ERROR_ALOKACJA
	}
	return tab;
}

/*
@ brief Funkcja do dealokacji wskazanej tablicy
@ param **tab - wskaznik to tablicy
@ param n - ilosc rzedow (kazdy nalezy zdealokowac z osobna, a na koncu tablice)
*/
void DealokujTablice(char** tab, int n) {
	for (int i = 0; i < n; i++) {
		free(tab[i]);
	}
	free(tab);
}

/*
@ brief Funkcja do wczytania zawartosci pliku do przygotowanej tablicy
        Program zaklada, ze kazda liczba w pliku zaczyna sie od 1 oraz
        ze po sobie nie moga wystepowac identyczne liczby binarne.
@ param *in - wskaznik do otwartego pliku
@ param **tab - wskaznik do tablicy dwuwymiarowej (do przechowania liczb binarnych)
@ param m - szerokosc tablicy, tzn. jak dlugie slowo mozna wczytac
@ ret   indeks - liczba wczytanych liczb binarnych
*/
int WczytajPlik(FILE* in, char** tab, int m) {
	int indeks = 0;
	char linia[DL_SLOWA];

	printf("zawartosc pliku: \n");
	while (!feof(in)) {
		fscanf_s(in, "%s", linia, DL_SLOWA);

		if (linia[0] != '1') { 
			printf("error - plik jest pusty\n");
			return 0;
		}
		else if (indeks > 0 && strcmp(tab[indeks - 1], linia) == 0) {
			return indeks;
		}
		else {
			strcpy_s(tab[indeks], m, linia);
			printf("%10s -> %5d\n", linia, Bin2Int(linia));
			indeks++;
		}
	}
	return indeks;
}

/*
@ brief Funkcja do posortowania tablicy z liczbami binarnymi malejaco
        (wzgledem ich wartosci decymalnej)
@ param **tab - wskaznik do tablicy
@ param iloscLiczb - ile liczba binarnych jest w tablicy
@ ret   przestawienia - ilosc przestawien w tablicy
*/
int PosortujTablice(char** tab, int iloscLiczb) {
	int przestawienia = 0;
	for (int i = 0; i < iloscLiczb - 1; i++) {
		int najwNastepnik = 0;
		int indeks = 0;
		for (int j = i + 1; j < iloscLiczb; j++) {
			int nastepnik = Bin2Int(tab[j]);
			if (nastepnik > najwNastepnik) {
				najwNastepnik = nastepnik;
				indeks = j;
			}
		}
		if (najwNastepnik > Bin2Int(tab[i])) {
			char* wsk = tab[i];
			tab[i] = tab[indeks];
			tab[indeks] = wsk;
			przestawienia++;
		}
	}
	return przestawienia;
}

/*
@ brief Funkcja do wypisania tablicy z liczbami binarnymi wraz z wartosciami decynalnymi
@ param **tab - wskaznik do tablicy
@ param liczbaLinii - ile liczb zawiera tablica
*/
void WypiszTablice(char** tab, int liczbaLinii) {
	for (int i = 0; i < liczbaLinii; i++) {
		printf("%10s -> %5d\n", tab[i], Bin2Int(tab[i]));
	}
}

int main() {
	Info();

	FILE* in;
	int n = 0;
	int m = 0;
	char nazwaIn[DL_SLOWA];
	
	WczytajSlowo("podaj nazwe pliku wejsciowego, ktory ma liczby binarne", nazwaIn);
	if (fopen_s(&in, nazwaIn, "r") == 0 && in != NULL) {
		printf("poprawnie otworzono plik o nazwie %s\n\n", nazwaIn);
		
		WczytajLiczbe("podaj wysokosc tablicy [tyle liczb binarnych zmiesci sie w tab]", &n, 10, ROZMIAR_TAB);
		WczytajLiczbe("podaj szerokosc tablicy [liczba o takiej dlugosci zmiesci sie w tab]", &m, 10, ROZMIAR_TAB);
		char** tablica = ZaalokujTablice(n, m);
		int liczbaLinii = WczytajPlik(in, tablica, m);
		if (liczbaLinii > 0) {
			int przestawienia = PosortujTablice(tablica, liczbaLinii);
			printf("\npodczas sortowania dokonano %d przestawien\n", przestawienia);
			printf("posortowana tablica, zawierajaca dane wczytane z pliku:\n");
			WypiszTablice(tablica, liczbaLinii);
		}
		DealokujTablice(tablica, n);
		fclose(in);
	}
	else {
		ERROR_PLIK
	}

	return 0;
}
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define LICZBA_TROJKATOW 6
#define DLUGOSC_NAPISU 8

struct WynikiAnalizy {
	char czyIstnieje;
	int numerFigury;
	double wspX, wspY;
};

/*
@ brief Funkcja do wczytania liczby calkowitej z przedzialu [min, max]
@ param min - najmniejsza mozliwa liczba
@ param max - najwieksza mozliwa liczba
@ ret   wpis - zwraca wczytana liczbe z przedzialu [min, max]
*/
int WczytajLiczbe(int min, int max) {
	int wpis = 0, pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("wczytywanie wartosci z przedzialu [%d, %d]: ", min, max);
		}
		else {
			printf("error - podana liczba jest spoza zakresu, prosze sprobuj ponownie: ");
		}
		while (scanf_s("%d", &wpis) != 1 || getchar() != '\n') {
			printf("error - blad podczas wczytywania, prosze sprobuj ponownie: ");
			while (getchar() != '\n') {}
		}
	} while (wpis < min || wpis > max);
	return wpis;
}

/*
@ brief Funkcja do zaalokowania tablicy double o wymiarach n wierszy m kolumn
@ param n - liczba wierszy
@ param m - liczba kolumn
@ ret   **t - wskaznik do zaalokowanego miejsca na tablice
*/
double** ZaalokujTablice(int n, int m) {
	double** t = (double**)malloc(sizeof(double*) * n);
	for (int i = 0; i < n; i++) {
		t[i] = (double*)malloc(sizeof(double) * m);
	}
	return t;
}

/*
@ brief Funkcja do dealokacji tablicy o wymiarach n wierszy m kolumn
@ param **t - wskaznik do poczatku tablicy
@ param n - liczba wierszy
@ param m - liczba kolumn
*/
void DealokujTablice(double** t, int n, int m) {
	for (int i = 0; i < n; i++) {
		delete[] t[i];
	}
	delete[] t;
}

/*
@ brief Funkcja do wygenerowania pseudolosowej wartosci rzeczywistej z przedzialu [min, max]
@ param min - minimalna mozliwa do wylosowania wartosc
@ param max - maksymalna mozliwa do wylosowania wartosc
@ ret   dlugosc - losowa wartosc z przedzialu [min, max] : jest oznaczona jako dlugosc,
        bo pierw wyliczam skale przez ktora mnoze DLUGOSC odcinka od min do max i potem
        do ktorej dodaje wartosc min, co w wyniku daje wartosc z [min, max]
*/
double WygenerujDouble(double min, double max) {
	double skala = (double)rand() / (double)RAND_MAX;
	double dlugosc = max - min + 1;
	dlugosc *= skala;
	dlugosc += min;
	return dlugosc;
}

/*
@ brief Funkcja do wygenerowania wspolrzednych 3 wierzcholkow n trojkatow
@ param tab - tablica z trojkatami
@ param n - liczba trojkatow
*/
void WygenereujTrojkaty(double** tab, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 6; j++) {
			tab[i][j] = WygenerujDouble(0.0, 10.0);
		}
	}
}

/*
@ brief Funkcja do wypisania wspolrzednych wierzcholkow n trojkatow
@ param **tab - tablica do wspolrzednych
@ param n - liczba trojkatow
*/
void WypiszTrojkaty(double** tab, int n) {
	printf("wygenerowano %d fig.: \n", n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%lf ", tab[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
}

/*
@ brief Funkcja do wyliczenia problemu opisanego w zadaniu
@ param **tab - wskaznik do tablicy przechowujacej wspolrzedne wierzcholkow kolejnych trojkatow
@ param n - liczba trojkatow, ktorych wspolrzedne sa opisane w podanej tablicy
@ ret   zwraca typ strukturalny WynikiAnalizy, ktory przechowa czy z posrod podanych wspolrzednych
        mozna zbudowac chociaz jeden trojkat, poda numer trojkata, ktorego srodek ciezkosci jest
        najblizej poczatku uk. wsp i wypisze wspolrzedne tego srodka
*/
WynikiAnalizy AnalizaFigur(double** tab, int n) {
	char czyIstnieje = 'n';
	int numerFigury = -1;
	double najmniejszaOdleglosc = -1;
	double xNajblizszego = 0.0, yNajblizszego = 0.0;

	for (int i = 0; i < n; i++) {
		double lewa = (tab[i][2] - tab[i][0]) * (tab[i][5] - tab[i][1]);
		double prawa = (tab[i][4] - tab[i][0]) * (tab[i][3] - tab[i][1]);
		if (abs(lewa - prawa) < 0.0001) {
			continue;
		}
		else {
			czyIstnieje = 't';
			double x = (tab[i][0] + tab[i][2] + tab[i][4]) / 3;
			double y = (tab[i][1] + tab[i][3] + tab[i][5]) / 3;

			double odleglosc = sqrt(x * x + y * y);
			if (numerFigury == -1 || odleglosc < najmniejszaOdleglosc) {
				numerFigury = i;
				najmniejszaOdleglosc = odleglosc;
				xNajblizszego = x;
				yNajblizszego = y;
			}
		}
	}	
	return WynikiAnalizy{ czyIstnieje, numerFigury, xNajblizszego, yNajblizszego };
}

/*
@ brief Funkcja ktora sprawdzi, czy napis zawiera dokladnie same cyfry
@ param napis - tablica zawierajaca napis
@ ret   1 gdy napis zawiera same cyfry
        0 gdy napis zawiera tez inne znaki
*/
int CzyCyfry(char* napis) {
	int indeks = 0;
	while (napis[indeks] != '\0') {
		if (!isdigit(napis[indeks])) return 0;
		indeks++;
	}
	return 1;
}

/*
@ brief Funkcja wczytuje tak dlugo napis, az bedzie on zawierac tlyko cyfry
@ param napis - wskaznik do tablicy przechowujacej napis
*/
void WczytajLiczbeJakoNapis(char* napis) {
	int poprawne = 0;
	int pierwsza = 1;
	do {
		if (pierwsza) {
			printf("podaj liczbe: ");
			pierwsza = 0;
		}
		else {
			printf("error - podany napis zawiera litery, prosze spbouj ponownie: ");
		}
		while (scanf_s("%s", napis, DLUGOSC_NAPISU) != 1 || getchar() != '\n') {
			while (getchar() != '\n') {}
			printf("error - blad podczas wczytywanie, prosze sprobuj ponownie: ");
		}
		poprawne = CzyCyfry(napis);
	} while (!poprawne);
}

int main() {
	srand(time(NULL));

	// zadanie 1 poziomu
	printf("Zadanie nr. 1\n");
	printf("Podaj liczbe trojkatow: ");
	int n = WczytajLiczbe(1, LICZBA_TROJKATOW);
	double** trojkaty = ZaalokujTablice(n, 6);
	WygenereujTrojkaty(trojkaty, n);
	WypiszTrojkaty(trojkaty, n);
	struct WynikiAnalizy w1 = AnalizaFigur(trojkaty, n);
	printf("%c %d %lf %lf\n\n\n", w1.czyIstnieje, w1.numerFigury, w1.wspX, w1.wspY);
	
	DealokujTablice(trojkaty, n, 6);

	// zadanie 2 poziomu
	printf("Zadanie nr. 2\n");
	char napis[DLUGOSC_NAPISU];
	WczytajLiczbeJakoNapis(napis);
	int wart = atoi(napis);
	printf("wartosc napisu to: %d\n", wart);
	
	return 0;
}
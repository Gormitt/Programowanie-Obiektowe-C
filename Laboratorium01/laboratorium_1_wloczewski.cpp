#include <iostream>
#include <stdio.h>
#include <time.h>

#define N 4
#define M 6

using namespace std;

void WypiszMacierz(double(*macierz)[M]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%lf ", macierz[i][j]);
		}
		putchar('\n');
	}
}

void UzupelnijMacierz(double(*macierz)[M]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			double los = rand() / (RAND_MAX + 1.0);
			macierz[i][j] = los;
		}
	}
}

void ZnajdzElementMinimalnyWiersza(double(*macierz)[M], int* tab) {
	for (int i = 0; i < N; i++) {
		double najmniejsza;
		for (int j = 0; j < M; j++) {
			if (j == 0) {
				najmniejsza = macierz[i][j];
				tab[i] = j;
			}
			else if (macierz[i][j] < najmniejsza) {
				najmniejsza = macierz[i][j];
				tab[i] = j;
			}
		}
	}
}

void ZnajdzNajwiekszyElementKolumny(double(*macierz)[M], int* tab) {
	double najwiekszeWartosci[M] = { 0.0 };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (macierz[i][j] > najwiekszeWartosci[j]) {
				najwiekszeWartosci[j] = macierz[i][j];
				tab[j] = i;
			}
		}
	}
}

void WypiszTablice(int* tab, int wielkosc) {
	for (int i = 0; i < wielkosc; i++) {
		printf("%d ", tab[i]);
	}
	putchar('\n');
}

void Elementy(double(*macierz)[M], int* tab1, int* tab2) {
	double najmniejszy = 1.0;
	double najwiekszy = 0.0;

	for (int i = 0; i < N; i++) {
		if (macierz[i][tab1[i]] > najwiekszy) {
			najwiekszy = macierz[i][tab1[i]];
		}
	}

	for (int j = 0; j < M; j++) {
		if (macierz[tab2[j]][j] < najmniejszy) {
			najmniejszy = macierz[tab2[j]][j];
		}
	}

	printf("element najwiekszy z pierwszego zestawienia to: %lf\n", najwiekszy);
	printf("element najmniejszy z drugiego zestawienia to: %lf\n", najmniejszy);
}

void SortowanieMacierzy(double(*macierz)[M]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M - 1; j++) {
			for (int k = j + 1; k < M; k++) {
				if (macierz[i][k] < macierz[i][j]) {
					double bufor = macierz[i][j];
					macierz[i][j] = macierz[i][k];
					macierz[i][k] = bufor;
				}
			}
		}
	}
}

void ZnajdzMediane(double(*macierz)[M]) {
	for (int i = 0; i < N; i++) {
		double srednia = (macierz[i][M / 2 - 1] + macierz[i][M / 2]) / 2;
		printf("mediana w rzedzie %d wynosi: %lf\n", i, srednia);
	}
}

int main() {
	srand(time(NULL));

	double macierz[N][M];
	int tab1[N];
	int tab2[M];

	printf("Losowanie wartosci do macierzy\n");
	UzupelnijMacierz(macierz);
	printf("Wylosowana macierz to: \n");
	WypiszMacierz(macierz);
	putchar('\n');

	printf("pozycje najmniejszych elementow w kolejnych rzedach macierzy: ");
	ZnajdzElementMinimalnyWiersza(macierz, tab1);
	WypiszTablice(tab1, N);

	printf("pozycje najwiekszy elementow w kolejnych kolumnach macierzy: ");
	ZnajdzNajwiekszyElementKolumny(macierz, tab2);
	WypiszTablice(tab2, M);
	putchar('\n');

	Elementy(macierz, tab1, tab2);
	putchar('\n');

	SortowanieMacierzy(macierz);
	WypiszMacierz(macierz);
	ZnajdzMediane(macierz);

	return 0;
}
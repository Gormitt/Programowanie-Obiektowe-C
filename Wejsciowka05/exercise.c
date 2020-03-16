#include <stdio.h>
#include <stdlib.h>

#define MIN 0
#define MAX 1000000

void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

int WczytajLiczbe(int min, int max) {
	int wpis;
	int pierwszaProba = 1;
	do {
		if (pierwszaProba) {
			printf("wczytywanie liczby z przedzialu [%d, %d]: ", min, max);
			pierwszaProba = 0;
		}
		else {
			printf("error - liczba poza przedzialem, sprobuj ponownie: ");
		}
		while (scanf_s("%d", &wpis) != 1 || getchar() != '\n') {
			CzyszczenieBufora();
			printf("error - blad podczas wczytywania, sprobuj ponownie: ");
		}
	} while (wpis < min || wpis > max);
	return wpis;
}

void RysujTrojkat(int n) {
	int liczbaKolumn = 0; 
	int suma = 0; 
	while (suma < n) { 
		liczbaKolumn += 1; 
		suma += liczbaKolumn; 
	}

	int* start = (int*)calloc(liczbaKolumn, sizeof(int));
	if (start != NULL) {
		start[0] = 1;
		for (int i = 1; i < liczbaKolumn; i++) {
			start[i] = start[i - 1] + i;
		}

		for (int i = 0; i < liczbaKolumn; i++) {
			int wpisywanyElement = start[liczbaKolumn - i - 1];
			int roznica = liczbaKolumn - i + 1;
			while (wpisywanyElement <= n) {
				printf("%d ", wpisywanyElement);
				wpisywanyElement += roznica;
				roznica++;
			}
			printf("\n");
		}
		free(start);
	}
	else {
		printf("error - blad podczas alokacji tablicy, zawierajacej poczatek kazdego wiersza");
		return;
	}
}

int main() {
	int n = WczytajLiczbe(MIN, MAX);
	RysujTrojkat(n);
	
	return 0;
}
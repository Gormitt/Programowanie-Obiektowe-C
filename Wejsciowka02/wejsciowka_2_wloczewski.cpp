#include <iostream>
#include <cstdlib>

#define N 5 // wysokosc macierzy
#define M 5 // szerokosc macierzy
#define DLUGOSC 10 // dlugosc wczytywanego slowa

void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

void UzupelnijTablice(char** tab) {
	int indeks = 0;
	char wpis = 'a';
	char alfabet[N * M];
	for (int i = 0; i < N * M; i++) {
		if (wpis == 'q') wpis++;
		alfabet[i] = wpis++;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tab[i][j] = alfabet[indeks];
			indeks += N;
		}
		indeks -= N * M - 1;
	}
}

void WypiszTablice(char** tab) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%2c", tab[i][j]);
		}
		putchar('\n');
	}
}

void WczytajSlowo(char* tab) {
	for (int i = 0; i < DLUGOSC; i++) {
		tab[i] = getchar();
	}
	CzyszczenieBufora(); // po wczytaniu 10 znakow w buforze pozostaje enter, ktory trzeba usunac, zeby poprawnie wczytywac dalsze dane
}

void WypiszSlowo(char* tab) {
	for (int i = 0; i < DLUGOSC; i++) {
		printf("%c", tab[i]);
	}
	putchar('\n');
}

int main() {
	char** a = new char*[N];
	char* b = new char[DLUGOSC];
	char* slowo = new char[DLUGOSC];

	for (int i = 0; i < N; i++) {
		a[i] = new char[M];
	}
	for (int i = 0; i < DLUGOSC; i++) {
		b[i] = NULL;
	}

	UzupelnijTablice(a);
	WypiszTablice(a);
	WczytajSlowo(slowo);
	WypiszSlowo(slowo);

	for (int i = 0; i < N; i++) {
		delete[] a[i];
	}

	delete[] a;
	delete[] b;
	delete[] slowo;
	return 0;
}
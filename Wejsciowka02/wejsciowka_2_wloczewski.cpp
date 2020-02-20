#include <iostream>
#include <cstdlib>

#define N 5 // wysokosc macierzy
#define M 5 // szerokosc macierzy
#define DLUGOSC 10 // dlugosc wczytywanego slowa

void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

/*
@ brief		Funkcja do uzupelnienia tablicy jak podano w zadaniu
			Wiemy, �e tablica ma okre�lone wymiary. Wysoko��, jest
			zapisana w sta�en N, a szeroko�� w sta�ej M
@ param		**tab
			Wska�nik do tablicy wska�nik�w. Ka�dy z jej element�w
			to tablica typu char, przechowuj�ca alfabet.
*/
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

/*
@ brief		Funkcja do wypisania tablicy
			Wiemy, �e tablica ma okre�lone wymiary. Wysoko��, jest
			zapisana w sta�en N, a szeroko�� w sta�ej M
@ param		**tab 
			Wska�nik do tablicy wska�nik�w. Ka�dy z jej element�w
			to tablica typu char, przechowuj�ca alfabet.
*/
void WypiszTablice(char** tab) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%2c", tab[i][j]);
		}
		putchar('\n');
	}
}

/*
@ brief		Funkcja do wczytania s�owa.
			Wiemy, �e u�ytkownik poda s�owo o ustalnej d�ugo�ci,
			kt�ra jest zapisana w sta�ej oraz �e si� nie pomyli
			podczas wpisywania.
@ param		*tab
			Wska�nik do tablicy, kt�ra ma przechowa� s�owo.
*/
void WczytajSlowo(char* tab) {
	for (int i = 0; i < DLUGOSC; i++) {
		tab[i] = getchar();
	}
	CzyszczenieBufora(); // po wczytaniu 10 znakow w buforze pozostaje enter, ktory trzeba usunac, zeby poprawnie wczytywac dalsze dane
}

/*
@ brief		Funkcja do wypisania s�owa.
			Wiemy, �e podane przez u�ytkownika s�owo jest
			ustalonej d�ugo�ci, kt�ra jest przechowywana w sta�ej.
@ param		*tab
			Wska�nik do tablicy przechowuj�cej kolejne znaki.
*/
void WypiszSlowo(char* tab) {
	for (int i = 0; i < DLUGOSC; i++) {
		printf("%c", tab[i]);
	}
	putchar('\n');
}


int main() {
	char** a = new char*[N];
	char** b = new char*[DLUGOSC];
	char* slowo = new char[DLUGOSC];

	for (int i = 0; i < N; i++) {
		a[i] = new char[M];
	}
	for (int i = 0; i < DLUGOSC; i++) {
		b[i] = NULL;
	}

	printf("Uzupelniam tablice kodujaca alfabetem.\n");
	UzupelnijTablice(a);
	printf("Wygenerowana tablica: \n");
	WypiszTablice(a);
	printf("Podaj slowo o dokldnej dlugosci %d znakow: ", DLUGOSC);
	WczytajSlowo(slowo);

	for (int i = 0; i < DLUGOSC; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if (slowo[i] == a[j][k]) b[i] = &a[j][k];
			}
		}
	}

	printf("Podane slowo: ");
	for (int i = 0; i < DLUGOSC; i++) {
		printf("%c", *b[i]);
	}

	for (int i = 0; i < N; i++) {
		delete[] a[i];
	}

	delete[] a;
	delete[] b;
	delete[] slowo;
	return 0;
}
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
			Wiemy, ze tablica ma okreslone wymiary. Wysokosc, jest
			zapisana w stalen N, a szerokosc w stalej M.
@ param		**tab
			Wskaznik do tablicy wskaznikow. Kazdy z jej elementow
			to tablica typu char, przechowuj¹ca alfabet.
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
			Wiemy, ze tablica ma okreslone wymiary. Wysokosc, jest
			zapisana w stalen N, a szerokosc w stalej M.
@ param		**tab 
			Wskaznik do tablicy wskaznikow. Kazdy z jej elementow
			to tablica typu char, przechowuj¹ca alfabet.
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
@ brief		Funkcja do wczytania slowa.
			Wiemy, ze uzytkownik poda slowo o ustalnej dlugosci,
			ktora jest zapisana w stalej oraz ze siê nie pomyli
			podczas wpisywania.
@ param		*tab
			Wskaznik do tablicy, ktora ma przechowac slowo.
*/
void WczytajSlowo(char* tab) {
	for (int i = 0; i < DLUGOSC; i++) {
		tab[i] = getchar();
	}
	CzyszczenieBufora(); // po wczytaniu 10 znakow w buforze pozostaje enter, ktory trzeba usunac, zeby poprawnie wczytywac dalsze dane
}

/*
@ brief		Funkcja do wypisania slowa.
			Wiemy, ze podane przez uzytkownika slowo jest
			ustalonej dlugosci, ktora jest przechowywana w stalej.
@ param		*tab
			Wskaznik do tablicy przechowuj¹cej kolejne znaki.
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
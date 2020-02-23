#include <iostream>
#include <cstdlib>

#define N 5 // wysokosc macierzy
#define M 5 // szerokosc macierzy
#define DLUGOSC_SLOWA 5 // dlugosc wczytywanego slowa
#define DLUGOSC_ALFABETU 25
#define LICZBA_SZYFRUJACA 3 // ile rzedow zostanie przesunietych w gore, podczas przesuwania zawartosci tablicy

/*
@ brief		Funkcja do czyszczenia zawartosci bufora.
*/
void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

/*
@ brief		Funkcja do wypisania informacji o autorze i przeznaczeniu programu.
*/
void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t23 luty 2020\n");
	printf("about: \tWejsciowka na 2 laboratoria.\n");
	printf("\tProgram zaszyfrowuje slowo w nastepujacy sposob: \n");
	printf("\t1. generuje tablice znakow (alfabet) i prosi o podanie slowa, ktore sklada sie ze znakow z tablicy,\n");
	printf("\t2. program zapamieta pozycje komorek w tablicy, zawierajace litery podanego slowa,\n");
	printf("\t3. program przestawi tablice i odczyta zapamietane wspolrzedne [dzieki temu slowo jest zaszyforwane],\n");
	printf("\t4. na koniec przywroci stare ustawienie tablicy i ponownie wypisze zapamietane wspolrzedne [slowo zostanie odszyfrowane].\n\n");
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
	putchar('\n');
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
	for (int i = 0; i < DLUGOSC_SLOWA; i++) {
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
	for (int i = 0; i < DLUGOSC_SLOWA; i++) {
		printf("%c", tab[i]);
	}
	putchar('\n');
}

/*
@ brief		Funkcja do wypisania wartosci na jakie wskazuje tablica B
@ param		**tab
			Wskaznik do tablicy wskaznikow, ktorych wartosci wypiszemy na ekran,
			ktorej dlugosc jest w stalej DLUGOSC_SLOWA.
*/
void WypiszWartosciWskaznikow(char** tab) {
	for (int i = 0; i < DLUGOSC_SLOWA; i++) {
		printf("%c", *tab[i]);
	}
	putchar('\n');
}

/*
@ brief		Funkcja do przesuniecia rzedow w tablicy dwuwymiarowej 
			o podana liczbe w gore.
@ param		**tab
			Wskaznik do tablicy wskaznikow, czyli do tabeli na ktorej
			wykonamy operacje.
@ param		przesuniecie
			Liczba calkowita z przedzialu [-N, N] ktora informuje nas 
			o ile rzedow chcemy przemiescic kazdy istniejacy rzad W GORE.
			W przypadku liczby ujemnej, przemieszczenie nastepuje W DOL.
*/
void PrzemiescRzedy(char** tab, int przesuniecie) {
	// a.: zminimalizowanie przemieszczenia b.: zamiana na liczbe dodatnia
	przesuniecie = (przesuniecie % N) + N; 
	if (przesuniecie == 0) return; // takie przesuniecia doprowadza do punktu wyjsica
	
	char kopia[N][M];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			kopia[i][j] = tab[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tab[i][j] = kopia[(i + przesuniecie) % N][j];
		}
	}
}

int main() {
	char** a = new char*[N]; // alokacja tablicy dwuwymiarowej z charami
	char** b = new char*[DLUGOSC_SLOWA]; // alokacja tablicy jednowymiarowej ze wskaznikami
	char* slowo = new char[DLUGOSC_SLOWA]; // alokacja tablicy jednoywmiarowej z charami

	for (int i = 0; i < N; i++) { // alokacja rzedow w tablicy dwuwymiarowej 
		a[i] = new char[M];
	}
	for (int i = 0; i < DLUGOSC_SLOWA; i++) { // uzupelnienie tablicy ze wskaznikami wartosciami NULL
		b[i] = NULL;
	}

	Info();

	printf("Uzupelniam tablice kodujaca alfabetem.\n");
	UzupelnijTablice(a);
	printf("Wygenerowana tablica kodowania znakow: \n");
	WypiszTablice(a);

	printf("Podaj slowo o dokldnej dlugosci %d znakow. Znaki musza zawierac sie w powyzszej tablicy: ", DLUGOSC_SLOWA);
	WczytajSlowo(slowo);

	for (int i = 0; i < DLUGOSC_SLOWA; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if (slowo[i] == a[j][k]) b[i] = &a[j][k]; // zapamietanie wskaznikow do poszczegolnych liter slowa
			}
		}
	}

	printf("Podane slowo: ");
	WypiszWartosciWskaznikow(b); 
	PrzemiescRzedy(a, LICZBA_SZYFRUJACA);
	printf("Zakodowane slowo to: ");
	WypiszWartosciWskaznikow(b);
	PrzemiescRzedy(a, -LICZBA_SZYFRUJACA);
	printf("Rozkodowane slowo to: ");
	WypiszWartosciWskaznikow(b);

	for (int i = 0; i < N; i++) { // dealokacja rzedow w tablicy dwuwymiarowej
		delete[] a[i];
	}

	delete[] a; // dealokacja tablicy dwuwymiarowe
	delete[] b; // dealokacja tablicy ze wskaznikami
	delete[] slowo; // dealokacja tablicy z charami
	printf("Koniec programu.\n\n");

	return 0;
}
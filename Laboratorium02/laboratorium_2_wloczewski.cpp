#include <iostream>
#include <cstdlib>

#define N 5 // wysokosc macierzy
#define M 5 // szerokosc macierzy
#define DLUGOSC_SLOWA 20 // dlugosc wczytywanego slowa
#define DLUGOSC_ALFABETU 25
#define LICZBA_SZYFRUJACA 3 // ile rzedow zostanie przesunietych w gore, podczas przesuwania zawartosci tablicy
#define _CRT_SECURE_NO_WARNINGS

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
void UzupelnijTablice(char (*tab)[N]) {
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
void WypiszTablice(char (*tab)[N]) {
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
@ return	znaki
			Ilosc znakow podanych przez uzytkownika.
*/
int WczytajSlowo(char* tab) {
	//scanf("%s", tab);
	int znaki = 0;
	for (int i = 0; i < DLUGOSC_SLOWA; i++) {
		char znak = getchar();
		if (znak != '\n') {
			tab[i] = znak;
			znaki++;
		}
		else {
			break;
		}
	}
	if (znaki == DLUGOSC_SLOWA) {
		CzyszczenieBufora();
	}
	return znaki;
}

/*
@ brief		Funkcja do wypisania wartosci na jakie wskazuje tablica B
@ param		**tab
			Wskaznik do tablicy wskaznikow, ktorych wartosci wypiszemy na ekran,
			ktorej dlugosc jest w stalej DLUGOSC_SLOWA.
*/
void WypiszWartosciWskaznikow(char** tab) {
	for (int i = 0; i < DLUGOSC_SLOWA; i++) {
		if (tab[i] != NULL) printf("%c", *tab[i]);
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
void PrzemiescRzedy(char (*tab)[N], int przesuniecie) {
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
/*
@ biref		Funkcja do uzupelnienia tablicy B, jak prosza w zaadniu.
@ param		**a 
			Wskaznik do tablicy A
@ param     **b
			Wskaznik do tablicy wskaznikow [jego uzupelniamy]
@ param		*slowo
			Slowo, do ktrego liter szukamy wskaznikow
@ param		iloscZnakow
			Liczba, ktora nam mowi jak dlugie jest slowo [dla ulatwienia]
*/
void UzupelnijTabliceB(char (*a)[N], char** b, char* slowo, int iloscZnakow) {
	for (int i = 0; i < iloscZnakow; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if (slowo[i] == a[j][k]) b[i] = &a[j][k]; // zapamietanie wskaznikow do poszczegolnych liter slowa
			}
		}
	}
}

// funkcje potrzebne do zadania I
void UzupelnijTabliceC(char*** c, char** b, int iloscZnakow) {
	int indeksWpisywania = 0;
	for (int i = 0; i < iloscZnakow; i++) {
		if (!(*b[i] == 'a' || *b[i] == 'e' || *b[i] == 'i' || *b[i] == 'o' || *b[i] == 'u' || *b[i] == 'y')) {
			c[indeksWpisywania] = &b[i];
			indeksWpisywania++;
		}
	}
}

void WypiszTabliceC(char*** c, int iloscZnakow) {
	printf("\nlitery na ktore wskazuja wskazniki z tablicy c: ");
	for (int i = 0; i < iloscZnakow; i++) {
		if (c[i] != NULL) printf("%c", **c[i]);
		else break;
	}
	putchar('\n');
}

// funkcje potrzebne do zadania II
void UzupelnijTabliceB2(char(*a)[N], char** b, char** b2, int iloscZnakow) {
	for (int i = 0; i < DLUGOSC_SLOWA; i++) {
		if (b[i] != NULL) {
			char* wsk = b[i] - (LICZBA_SZYFRUJACA * M);
			if (wsk < &a[0][0]) {
				wsk += N * M;
			}
			b2[i] = wsk;
		}
	}
}


void WypiszTabliceB2(char** b2, int iloscZnakow) {
	printf("rozkodowane w trakcie slowo: ");
	for (int i = 0; i < iloscZnakow; i++) {
		if (b2[i] != NULL) printf("%c", *b2[i]);
	}
	putchar('\n');
}

int main() {
	char a[N][M]; // alokacja tablicy dwuwymiarowej z charami
	char** b = new char* [DLUGOSC_SLOWA]; // alokacja tablicy jednowymiarowej ze wskaznikami
	char** b2 = new char* [DLUGOSC_SLOWA];
	char*** c = new char** [DLUGOSC_SLOWA];
	char* slowo = new char[DLUGOSC_SLOWA]; // alokacja tablicy jednoywmiarowej z charami

	for (int i = 0; i < DLUGOSC_SLOWA; i++) { // uzupelnienie tablicy ze wskaznikami wartosciami NULL
		b[i] = NULL;
		b2[i] = NULL;
		c[i] = NULL;
	}

	Info();

	printf("Uzupelniam tablice kodujaca alfabetem.\n");
	UzupelnijTablice(a);
	printf("Wygenerowana tablica kodowania znakow: \n");
	WypiszTablice(a);

	printf("Podaj slowo o dokldnej dlugosci %d znakow. Znaki musza zawierac sie w powyzszej tablicy: ", DLUGOSC_SLOWA);
	int ilsocZnakow = WczytajSlowo(slowo);
	UzupelnijTabliceB(a, b, slowo, ilsocZnakow);

	printf("Podane slowo: ");
	WypiszWartosciWskaznikow(b);
	PrzemiescRzedy(a, LICZBA_SZYFRUJACA);
	printf("Zakodowane slowo to: ");
	WypiszWartosciWskaznikow(b);

	////////////////// zadanie poziomu II
	UzupelnijTabliceB2(a, b, b2, ilsocZnakow);
	WypiszTabliceB2(b2, ilsocZnakow);
	////////////////// koniec zadania poziomu II

	PrzemiescRzedy(a, -LICZBA_SZYFRUJACA);
	printf("Rozkodowane slowo to: ");
	WypiszWartosciWskaznikow(b);

	////////////////// zadanie poziomu I
	UzupelnijTabliceC(c, b, ilsocZnakow);
	WypiszTabliceC(c, ilsocZnakow);
	////////////////// koniec zadania poziomu I

	delete[] b; // dealokacja tablicy ze wskaznikami
	delete[] b2;
	delete[] c;
	delete[] slowo; // dealokacja tablicy z charami
	printf("Koniec programu.\n\n");

	return 0;
}
#include <iostream>
#include <stdlib.h>

#define DL_SLOWA 40
#define ELEMENTY_LINII 4
#define ERROR_LICZBA_ZAKRES printf("error - podana liczba jest spoza zakresu, prosze sprobuj ponownie: ");
#define ERROR_LICZBA_BLAD printf("error - blad podczsa wczytywania liczby, prosze sprobuj ponownie: ");
#define ERROR_SLOWO_BLAD printf("error - blad podczas wczytywania slowa, prosze sprobuj ponownie: ");
#define ERROR_PLIK printf("error - blad podczas otwierania pliku");
#define ERROR_ALOKACJA printf("error - blad podczas alokacji tablicy");

struct student {
	int id;
	char nazwisko[DL_SLOWA];
	char imie[DL_SLOWA];
	double punkty;
};

struct zestawienieStudentow {
	struct student* tab;
	int liczbaStudentow;
};

struct listaJednokierunkowa {
	struct student st;
	struct listaJednokierunkowa* kolejny;
};

/*
@ brief Funkcja do wypisania informacji o autorze i programie.
*/
void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t19 mar 2020\n");
	printf("about: \tRozwiazanie zadan na Laboratorium nr. 5\n");
	printf("\tProgram pobiera od uzytkownika nazwy plikow wejsciowego i wyjsciowego.\n");
	printf("\tWypisuje zestawienie studenow z pliku wejsciowego i pyta o id studena, ktorego usunac.\n");
	printf("\tZmodyfikowane zestawienie wypisuje na ekran i zapisuje do pliku wyjsciowego, ktory jest tworzony.\n\n");
}

/*
@ brief Funkcja do czyszczenia bufora.
*/
void CzyszczeniBufora() {
	while (getchar() != '\n') {}
}

/*
@ brief Funkcja do wczytania slowa.
@ param *info - wiadomosc do uzytkownika
@ param *slowo - wskaznik do tablicy przechowujacej
*/
void WczytajSlowo(const char* info, char* slowo) {
	printf("%s, wczytywanie slowa: ", info);
	while (scanf_s("%s", slowo, DL_SLOWA) != 1 || getchar() != '\n') {
		CzyszczeniBufora();
		ERROR_SLOWO_BLAD
	}
}

/*
@ brief Funkcja do wczytania liczby calkowitej.
@ param *info - wiadomosc do uzytkownika
@ param *wpis - wskaznik do zmiennej, ktora przechowa wczyt
@ param min - minimalna mozliwa do wczytania liczba
@ param max - maxymalna mozliwa do wczytania liczba
*/
void WczytajLiczbeCalkowita(const char* info, int* wpis, int min, int max) {
	int pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("%s, wczytywanie liczby z przedzialu [%d, %d]: ", info, min, max);
		}
		else {
			ERROR_LICZBA_ZAKRES
		}
		while (scanf_s("%d", wpis) != 1 || getchar() != '\n') {
			CzyszczeniBufora();
			ERROR_LICZBA_BLAD
		}
	} while (*wpis < min || *wpis > max);
}

/*
@ brief Funkcja do wczytania liczby zmiennoprzecinkowej.
@ param *info - wiadomosc do uzytkownika
@ param *wpis - wskaznik do zmiennej, ktora przechowa wczyt
@ param min - minimalna mozliwa do wczytania liczba
@ param max - maxymalna mozliwa do wczytania liczba
*/
void WczytajLiczbeZmiennoprzecinkowa(const char* info, double* wpis, double min, double max) {
	int pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("%s, wczytywanie liczby z przedzialu [%lf, %lf]: ", info, min, max);
		}
		else {
			ERROR_LICZBA_ZAKRES
		}
		while (scanf_s("%lf", wpis) != 1 || getchar() != '\n') {
			CzyszczeniBufora();
			ERROR_LICZBA_BLAD
		}
	} while (*wpis < min || *wpis > max);
}

// Funkcja nr. 1
/* 
@ brief Funkcja do liczenia linii "na pusto".
@ param *in - wskaznik do otwartego pliku
@ ret    liczbaLinii - liczba linii w pliku
*/
int ZliczLinie(FILE* in) {
	char linia[DL_SLOWA];
	int liczbaLinii = 0;
	
	while (!feof(in)) {
		for (int i = 0; i < ELEMENTY_LINII; i++) {
			fscanf_s(in, "%s", linia, DL_SLOWA);

			if (i < 1 && feof(in)) {
				return liczbaLinii;
			}
		}
		liczbaLinii++;
	}
	rewind(in);
	return liczbaLinii;
}

// Funkcja nr. 2
/*
@ brief Funkcja do wczytania zawartosci pliku i zapisania jego do struktur.
@ param *nazwaPliku - wskaznik do tablicy przechowujacej nazwe pliku wejsciowego
@ ret   zestawienieStudentow - struktura, ktora zawiera dwa pola:
        1. wskaznik do zaalokowanej tablicy ze studentami
        2. liczbe pol w tej tablicy
*/
struct zestawienieStudentow WczytajPlik(char* nazwaPliku) {
	FILE* in;
	if (fopen_s(&in, nazwaPliku, "r") == 0 && in != NULL) {
		int liczbaLinii = ZliczLinie(in);
		if (liczbaLinii == 0) {
			printf("info: podany plik nie zawiera zadnych danych.\n");
			fclose(in);
			exit(0);
		}
		
		struct student* tab = (struct student*)malloc(sizeof(struct student) * liczbaLinii);
		if (tab != NULL) {
			rewind(in);
			for (int i = 0; i < liczbaLinii; i++) {
				int id;
				char nazwisko[DL_SLOWA] = { '\0' };
				char imie[DL_SLOWA] = { '\0' };
				double punkty;
				fscanf_s(in, "%d", &id);
				fscanf_s(in, "%s", nazwisko, DL_SLOWA);
				fscanf_s(in, "%s", imie, DL_SLOWA);
				fscanf_s(in, "%lf", &punkty);

				strcpy_s(tab[i].nazwisko, DL_SLOWA, nazwisko);
				strcpy_s(tab[i].imie, DL_SLOWA, imie);
				tab[i].id = id;
				tab[i].punkty = punkty;
			}

			return zestawienieStudentow{ tab, liczbaLinii };
		}
		else {
			ERROR_ALOKACJA
			exit(0);
		}

		fclose(in);
	}
	else {
		ERROR_PLIK
		exit(0);
	}
}

// Funkcja nr. 3
/*
@ brief Funkcja do wczytania liczby calkowitej.
@ param z - wskaznik do struktury zawierajacej wskaznik do tablicy studentow oraz ich liczbe
*/
void WypiszZestawienie(struct zestawienieStudentow* z) {
	for (int i = 0; i < z->liczbaStudentow; i++) {
		printf("%d %s %s %.2lf\n", z->tab[i].id, z->tab[i].nazwisko, z->tab[i].imie, z->tab[i].punkty);
	}
}

/*
@ brief Funkcja do pobrania id. studenta, ze sprawdzeniem czy istnieje ono w zestawieniu.
@ param *s - wskaznik do tablicy, ktora zawiera dane studentow
@ ret   id - pobrane od uzytkownika id
*/
int PobierzIdStudenta(struct student* s, int liczba) {
	int id = 0, pierwsza = 1;
	do {
		if (pierwsza) {
			printf("podaj id studenta z zestawienia: ");
			pierwsza = 0;
		}
		else {
			printf("w zestawieniu nie ma studenta o podanym id, prosze sprobuj ponownie: ");
		}
		while (scanf_s("%d", &id) != 1 || getchar() != '\n') {
			CzyszczeniBufora();
			ERROR_LICZBA_BLAD
		}
		for (int i = 0; i < liczba; i++) {
			if (s[i].id == id) {
				return id;
			}
		}
	} while (1);
}

// Funkcja nr. 4
/*
@ brief Funkcja, ktora ususnie studenta z zestawienia.
@ param *z - wskaznik do istniejacego zestawienia, z ktorego bedziemy usuwac
@ ret   zestawienieStudentow - struktura, w ktorej polu tab, nie ma studenta o pobranym indeksie
*/
struct zestawienieStudentow UsunStudenta(struct zestawienieStudentow* z) {
	struct student* tmp = (struct student*)malloc(sizeof(struct student) * (z->liczbaStudentow - 1));
	if (tmp == NULL) {
		ERROR_ALOKACJA
		exit(0);
	}
	
	int id = PobierzIdStudenta(z->tab, z->liczbaStudentow); // id studenta ktorego chcemy usunac
	int spr = 0; // numer w tablicy studenta ktorego sprawdzamy
	int wst = 0; // numer indeksu, do ktorego wstawiamy kolejnego studenta
	while (spr < z->liczbaStudentow) {
		if (z->tab[spr].id != id) {
			strcpy_s(tmp[wst].nazwisko, DL_SLOWA, z->tab[spr].nazwisko);
			strcpy_s(tmp[wst].imie, DL_SLOWA, z->tab[spr].imie);
			tmp[wst].id = z->tab[spr].id;
			tmp[wst].punkty = z->tab[spr].punkty;
			wst++;
		}
		spr++;
	}
	struct student* wskDoZwolnienia = z->tab; 
	free(wskDoZwolnienia); // zwolnienie starej tablicy studentow

	return zestawienieStudentow{ tmp, z->liczbaStudentow - 1 }; // zwrocenie nowej struktury, z uaktualniona tablica (ona zostanie zwolniona na koncu)
}

/*
@ brief Funkcja do zapisania zestawienia do pliku tekstowego.
@ param *z - wskaznik do zestawienia
@ param *nazwaOut - nazwa pliku do ktorego zapisujemy dane
*/
void ZapiszKolekcje(struct zestawienieStudentow* z, char* nazwaOut) {
	FILE* out;
	if (fopen_s(&out, nazwaOut, "a+") == 0 && out != NULL) {
		for (int i = 0; i < z->liczbaStudentow; i++) {
			fprintf(out, "%d %s %s %.2lf\n", z->tab[i].id, z->tab[i].nazwisko, z->tab[i].imie, z->tab[i].punkty);
		}
	}
	else {
		ERROR_ALOKACJA
		exit(0);
	}
}

int main() {
	Info();

	FILE* in;
	char nazwaIn[DL_SLOWA];
	char nazwaOut[DL_SLOWA];
	WczytajSlowo("podaj nazwe pliku z danymi wejsciowymi", nazwaIn);
	WczytajSlowo("podaj nazwe pliku na zapisanie danych", nazwaOut);
	
	struct zestawienieStudentow zestawienie = WczytajPlik(nazwaIn);
	printf("\nwczytane z pliku zestawienie studentow: \n");
	WypiszZestawienie(&zestawienie);

	zestawienie = UsunStudenta(&zestawienie);
	printf("\nzestawienie studentow pomniejszone o jednego studenta: \n");
	WypiszZestawienie(&zestawienie);

	ZapiszKolekcje(&zestawienie, nazwaOut);

	free(zestawienie.tab); // zwolnienie tablicy zaalokowanej do zmiennej zestawienie
	return 0;
}
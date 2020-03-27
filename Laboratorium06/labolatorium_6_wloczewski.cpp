#include <iostream>
#include <stdlib.h>

#define DL_SLOWA 20
#define LICZBA_CZUJNIKOW 4
#define ERROR_ALOKACJA printf("error - blad podczas alokacji\n");
#define ERROR_PLIK_OTWARCIE printf("error - nie udalo sie otworzyc podanego pliku\n");
#define ERROR_PLIK_PUSTY printf("error - plik z danymi jest pusty\n");
#define ERROR_SLOWO_WCZYTYWANIE printf("error - blad podczas wczytywania slowa, prosze sprobuj ponownie: ");

struct pomiar {
	unsigned int nrPomiaru;
	unsigned int nrCzujnika;
	char data[DL_SLOWA];
	double temp;
	struct pomiar* nastepny;
};

struct listyCzujnikow {
	struct pomiar** czujniki;
};

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t24 mar 2020\n");
	printf("about: \tRozwiazanie zadania z lab. nr. 6\n\n");
}

/*
@ brief Funkcja do czyszczenia bufora
*/
void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

/*
@ brief Funkcja do wczytania slowa
@ param *info - komunikat dla uzytkownika
@ param *slowo - tablica na przechowanie wczytanego slowa
*/
void WczytajSlowo(const char* info, char* slowo) {
	printf("%s: ", info);
	while (scanf_s("%s", slowo, DL_SLOWA) != 1 || getchar() != '\n') {
		CzyszczenieBufora();
		ERROR_SLOWO_WCZYTYWANIE
	}
}

/*
@ brief Funkcja do dodania elementu do listy jednokierunkowej
@ param *in - wskaznik do konkretnego miejsca w plku, ktory zawiera linie obecnie wczytywana do listy
@ ret   *nowy - wskaznik do nowo zaalokowanego elementu listy
*/
struct pomiar* DodajElementListy(FILE* in) {
	struct pomiar* nowy = (struct pomiar*)malloc(sizeof(struct pomiar));
	if (nowy != NULL) {
		nowy->nastepny = NULL;

		unsigned int nrPomiaru;
		unsigned int nrCzujnika;
		char data[DL_SLOWA] = {'\0'};
		double temp;

		fscanf_s(in, "%d", &nrPomiaru);
		if (feof(in)) { // napotkana linia to koniec pliku
			return NULL;
		}

		fscanf_s(in, "%d", &nrCzujnika);
		fscanf_s(in, "%s", data, DL_SLOWA);
		fscanf_s(in, "%lf", &temp);

		nowy->nrPomiaru = nrPomiaru;
		nowy->nrCzujnika = nrCzujnika;
		nowy->temp = temp;
		strcpy_s(nowy->data, DL_SLOWA, data);

		return nowy;
	}
	else {
		ERROR_ALOKACJA
		exit(0);
	}
}

// Funkcja 3.
/*
@ brief Funkcja do wczytywania pliku do listy
@ param *in - wskaznik do poczatku otwartego wczesniej pliku z danymi wejsciowymi
@ ret   *glowa - wskaznik do pierwszego elementu listy
*/
struct pomiar* WczytajPlikDoListy(FILE* in) {
	struct pomiar* glowa = NULL;
	struct pomiar* ogon = NULL;
	while (!feof(in)) {
		if (glowa == NULL) {
			glowa = DodajElementListy(in);
			if (glowa != NULL) {
				ogon = glowa;
			}
			else { // jezeli funkcja chce dodac jako pierwszy element null to plik jest pusty
				ERROR_PLIK_PUSTY
				return NULL;
			}
		}
		else {
			ogon->nastepny = DodajElementListy(in);
			if (ogon->nastepny != NULL) {
				ogon = ogon->nastepny;
			}
		}
	}
	return glowa;
}

/*
@ brief Funkcja do dealokacji listy
@ param *glowa - wskaznik do poczatku listys
*/
void DealokujListe(struct pomiar* glowa) {
	struct pomiar* ogon = NULL;
	while (glowa) {
		ogon = glowa->nastepny;
		free(glowa);
		glowa = ogon;
	}
}

/*
@ brief Funkcja do podzialu listy jednokierunkowej na LICZBA_CZUJNIKOW list jednokierunkowych
@ param *lista - wskaznik do glowy listy, ktora dzielimy
@ param *pomiaryCzujnikow - tablica, ktora przechowa liczbe pomiarow z kadego czujnika
@ ret   struct listyCzujnikow - strukturalny typ danych ktory zawiera wskaznik do dynamicznej tablicy, 
        przechowujacej glowy list, czyli wskazniki do pierwszych
        elementow kazdej z utoroznych list
*/
struct listyCzujnikow UzupelnijCzujniki(struct pomiar** lista) {
	struct pomiar** czujniki = (struct pomiar**)calloc(sizeof(struct pomiar*), LICZBA_CZUJNIKOW);
	struct pomiar** dane = (struct pomiar**)calloc(sizeof(struct pomiar*), LICZBA_CZUJNIKOW);
	if (czujniki != NULL && dane != NULL) {
		while (*lista) {
			struct pomiar* tmp = (*lista)->nastepny;

			int numer = (*lista)->nrCzujnika - 1;
			if (czujniki[numer] == NULL) {
				czujniki[numer] = (*lista);
				dane[numer] = czujniki[numer];
			}
			else {
				dane[numer]->nastepny = (*lista);
				dane[numer] = dane[numer]->nastepny;
			}
			(*lista)->nastepny = NULL;
			(*lista) = tmp;
		}
		free(dane);
		(*lista) = NULL;
		return listyCzujnikow{ czujniki };
	}
	else {
		ERROR_ALOKACJA
		exit(0);
	}
}

/*
@ brief Funkcja do dealokowania list zawierajacych dane z kolejnych czujnikow
@ param **czujniki - tablica wskaznikow do kazdej z list
*/
void DealokujCzujniki(struct pomiar** czujniki) {
	for (int i = 0; i < LICZBA_CZUJNIKOW; i++) {
		DealokujListe(czujniki[i]);
	}
	free(czujniki);
}

// Funkcja 1
/*
@ brief Funkcja ktora otwiera plik po podanej nazwie i wywoluje wczytanie do listy. 
        Zapisana liste zwraca w postaci typu strukturalnego ktory zawiera wskaznik do listy dynamicznej
@ param *const nazwa - wskaznik do tablicy zawierajacej nazwe pliku z danymi
@ ret   struct pomiar* lista - wskaznik do struktury ktorej jedynym polem jest wskaznik do listy dynamicznej z rekordami
*/
struct pomiar* OtworzPlik(const char* nazwa) {
	FILE* in;
	if (fopen_s(&in, nazwa, "r") == 0 && in != NULL) {
		// Funkcja 3.
		struct pomiar* lista = WczytajPlikDoListy(in);
		fclose(in);
		return lista;
	}
}

// Funkcja 2.
/*
@ brief Funkcja do oblicznia ilosci rekordow, wyswietlenia tej liczby i wypisania pierwszego jak i ostatniego rekordu
@ param *lista - wskaznik do dynamicznej listy jednokierunkowej z rekordami
*/
void PoliczRekordy(struct pomiar* lista) {
	int liczbaRekordow = 0;
	struct pomiar* ostatni = lista, *pierwszy = lista;
	while (lista) {
		if (liczbaRekordow == 0) {
			pierwszy = lista;
		}
		else {
			ostatni = lista;
		}
		liczbaRekordow++;

		lista = lista->nastepny;
	}
	if (liczbaRekordow != 0) {
		printf("liczba rekordow: %d\n", liczbaRekordow);
		printf("pierwszy rekord: %d %d %s %lf\n", pierwszy->nrPomiaru, pierwszy->nrCzujnika, pierwszy->data, pierwszy->temp);
		printf("ostatni rekord: %d %d %s %lf\n", ostatni->nrPomiaru, ostatni->nrCzujnika, ostatni->data, ostatni->temp);
	}
}

// Funkcja 4.
/*
@ brief Funckja ktora znajduje najmniejszy element w danej liscie i wyrzuca go na koniec listy
@ param *lista - wskaznik do listy dynamicznej z rekordami
@ ret   wskaznik do poczatku zmodyfikowanej listy jednokierunkowej
*/
struct pomiar* ZnajdzNajmniejszy(struct pomiar* lista) { 
	if (lista == NULL) return NULL; // lista pusta
	else if (lista->nastepny == NULL) return lista; // lista jednoelementowa
	struct pomiar* tmp = lista;
	struct pomiar* wskNajmniejszy = NULL;
	struct pomiar* wskPoprzedzajacy = NULL;
	double najmniejszy = tmp->temp;
	int czyZnaleziono = 0;
	while (tmp) {
		if (tmp->nastepny != NULL && tmp->nastepny->temp < najmniejszy) {
			wskNajmniejszy = tmp->nastepny;
			wskPoprzedzajacy = tmp;
			najmniejszy = tmp->nastepny->temp;
			czyZnaleziono = 1;
		}
		else if (tmp->nastepny == NULL) { // dotarlismy do ostatniego elementu
			if (czyZnaleziono && wskNajmniejszy->nastepny == NULL) {
				return lista;
			}
			else if (czyZnaleziono) {
				wskPoprzedzajacy->nastepny = wskNajmniejszy->nastepny;
				tmp->nastepny = wskNajmniejszy;
				wskNajmniejszy->nastepny = NULL;
				return lista;
			}
			else {
				struct pomiar* zwrot = lista->nastepny;
				tmp->nastepny = lista;
				lista->nastepny = NULL;
				return zwrot;
			}
		}
		
		tmp = tmp->nastepny;
	}
}

int main() {
	Info();
	FILE* in;
	char nazwain[DL_SLOWA];
	
	// wczytywanie pliku do listy dynamicznej
	WczytajSlowo("podaj nazwe pliku wejsciowego", nazwain);
	struct pomiar* lista = OtworzPlik(nazwain);
	struct listyCzujnikow lc;

	printf("WSZYSTKIE POMIARY: \n");
	PoliczRekordy(lista);
	printf("\n");

	lc = UzupelnijCzujniki(&lista);
	for (int i = 0; i < LICZBA_CZUJNIKOW; i++) {
		printf("CZUJNIK NR. %d\n", i + 1);
		PoliczRekordy(lc.czujniki[i]);
		printf("\nZmodyfikowana lista rekordow\n");
		lc.czujniki[i] = ZnajdzNajmniejszy(lc.czujniki[i]);
		PoliczRekordy(lc.czujniki[i]);
		printf("\n\n");
	}
	
	DealokujListe(lista);
	DealokujCzujniki(lc.czujniki);

	return 0;
}
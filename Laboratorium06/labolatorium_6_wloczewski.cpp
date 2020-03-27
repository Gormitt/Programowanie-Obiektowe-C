#include <iostream>
#include <stdlib.h>
#include <math.h>

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

struct dwukierunkowa {
	unsigned int nrPomiaru;
	unsigned int nrCzujnika;
	char data[DL_SLOWA];
	double temp;
	struct dwukierunkowa* poprzedni;
	struct dwukierunkowa* nastepny;
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
	else {
		ERROR_PLIK_OTWARCIE
		exit(0);
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
	return NULL;
}

// Zadanie II poziomu

/*
@ brief Funkcja do uzupelniania jednego pola listy dynamicznej dwukierunkowej
@ param *doCzego - parametr, do jakiego istniejacego elementu listy doklejamy
@ param *jednokierunkowa - wskaznik do listy jednokierunkowej, ktory zawiera dane, ktore aktualnie kopiujemy
@ ret   *dwukierunkowa lista - wskaznik do swiezo zaalokowanego elemetnu
*/
struct dwukierunkowa* DodajDoDwukierunkowej(struct dwukierunkowa* doCzego, struct pomiar* jednokierunkowa) {
	struct dwukierunkowa* lista = (struct dwukierunkowa*)malloc(sizeof(struct dwukierunkowa));
	if (lista != NULL) {
		lista->poprzedni = doCzego;
		lista->nastepny = NULL;
		lista->nrPomiaru = jednokierunkowa->nrPomiaru;
		lista->nrCzujnika = jednokierunkowa->nrCzujnika;
		lista->temp = jednokierunkowa->temp;
		strcpy_s(lista->data, DL_SLOWA, jednokierunkowa->data);
		return lista;
	}
	else {
		ERROR_ALOKACJA
		exit(0);
	}
}

/*
@ brief Funkcja do utworzenia listy dwukierunkowej jako calosci
@ param *jednokierunkowa - wskaznik do listy dynamicznej jednokierunkowej z ktorej kopiujemy dane
@ ret   *dwukierunkowa - wskaznik zaalokowanej listy dwukierunkowej
*/
struct dwukierunkowa* StworzListeDwukierunkowa(struct pomiar* jednokierunkowa) {
	if (jednokierunkowa == NULL) {
		return NULL;
	}
	else {
		struct dwukierunkowa* glowa = NULL;
		struct dwukierunkowa* ogon = NULL;
		while (jednokierunkowa) {
			if (glowa == NULL) {
				glowa = DodajDoDwukierunkowej(NULL, jednokierunkowa);
				ogon = glowa;
			}
			else {
				ogon->nastepny = DodajDoDwukierunkowej(ogon, jednokierunkowa);
				if (ogon->nastepny != NULL) {
					ogon = ogon->nastepny;
				}
			}
			jednokierunkowa = jednokierunkowa->nastepny;
		}
		return glowa;
	}
}

/*
@ brief Funkcja do dealokacji listy dwukierunkowej
@ param *lista - wskaznik do poczatku listy dwukierunkowej
*/
void DealokujListeDwukierunkowa(struct dwukierunkowa* lista) {
	while (lista) {
		struct dwukierunkowa* tmp = lista->nastepny;
		free(lista);
		lista = tmp;
	}
}

/*
@ brief Funkcja do wyisania czesci rekordow z listy dwukierunkowej.
        Funkcja wypisuje pewien przedzial (malejaco albo rosnaco) o czym decyduja nr pierwszego i ostatniego elementu
        Funkcja zabezpiecza sie przed podaniem wspolrzednych wykraczajacych poza rozmiar listy
@ param *lista - wskaznik do listy dwukierunkowej
@ param pierwszy - nr. elementu ktory zostanie wypisany jako pierwszy
@ param ostatni - nr. elementu ktory zostanie wypisany jako ostatni
*/
void WypiszListeDwukierunkowa(struct dwukierunkowa* lista, int pierwszy, int ostatni) {
	if (lista == NULL) { // lista jest pusta
		printf("dynamiczna lista dwukierunkowa jest pusta.\n");
		return;
	}
	if (pierwszy == ostatni) {
		printf("info: pomiedzy %d a %d elementem nic nie ma\n", pierwszy, ostatni);
	}
	if (pierwszy < 0) {
		pierwszy = 0;
	}
	// szukanie wskaznika o numerze "pierwszy"
	int ind = 0;
	struct dwukierunkowa* wskaznik = lista;
	while (ind != pierwszy && wskaznik) {
		ind++;
		if (wskaznik->nastepny == NULL) {
			break;
		}
		else {
			wskaznik = wskaznik->nastepny;
		}
	}

	int roznica = pierwszy - ostatni;
	printf("rekordy od %d do %d jednego z czujnikow: ", pierwszy, ostatni);
	if (roznica < 0) printf("[wypisywanie do przodu]\n");
	else if (roznica == 0) printf("[wypisywanie jednego elementu]\n");
	else printf("[wypisywanie do tylu]\n");

	while (roznica != 0) {
		printf("%d %d %s %lf\n", wskaznik->nrPomiaru, wskaznik->nrCzujnika, wskaznik->data, wskaznik->temp);
		if (roznica < 0) { // odczytywanie do przodu
			if (wskaznik->nastepny == NULL) {
				return;
			}
			else {
				wskaznik = wskaznik->nastepny;
			}
			roznica++;
		}
		else if (roznica > 0) { // odczytywanie jednego elementu
			if (wskaznik->poprzedni == NULL) {
				return;
			}
			else {
				wskaznik = wskaznik->poprzedni;
			}
			roznica--;
		}
	}
}

/*
@ brief Funkcja do wypisania calej listy dynamicznej w obie strony
@ param *lista - wskaznik do listy
*/
void WypiszCalaListeDwukierunkowa(struct dwukierunkowa* lista) {
	while (1) {
		printf("%d %d %s %lf\n", lista->nrPomiaru, lista->nrCzujnika, lista->data, lista->temp);
		if (lista->nastepny == NULL) break;
		else lista = lista->nastepny;
	}
	printf("\n\n");
	while (lista) {
		printf("%d %d %s %lf\n", lista->nrPomiaru, lista->nrCzujnika, lista->data, lista->temp);
		if (lista->poprzedni == NULL) break;
		else lista = lista->poprzedni;
	}
}

int main() {
	Info();
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
		if (lc.czujniki[i] != NULL) {	
			PoliczRekordy(lc.czujniki[i]);
			printf("\nZmodyfikowana lista rekordow\n");
			lc.czujniki[i] = ZnajdzNajmniejszy(lc.czujniki[i]);
			PoliczRekordy(lc.czujniki[i]);
			printf("\n\n");
		}	
		else {
			printf("dana lista jest pusta.\n\n");
		}
	}
	
	printf("lista dwukierunkowa: \n");
	struct dwukierunkowa* listaDwukierunkowa = StworzListeDwukierunkowa(lc.czujniki[3]);
	
	WypiszListeDwukierunkowa(listaDwukierunkowa, 50, 20);
	//WypiszCalaListeDwukierunkowa(listaDwukierunkowa);

	DealokujListe(lista);
	DealokujCzujniki(lc.czujniki);
	DealokujListeDwukierunkowa(listaDwukierunkowa);

	return 0;
}
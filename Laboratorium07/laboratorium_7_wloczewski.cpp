#include <iostream>
#include <stdlib.h>

#define MAX_LICZBA_CZUJNIKOW 10
#define MAX_DLUGOSC_SLOWA 20

#define ANSI_ZIELONY "\x1b[32m"
#define ANSI_NIEBIESKI "\x1b[34m"
#define ANSI_CYAN "\x1b[36m"
#define ANSI_ZOLTY "\x1b[33m"
#define ANSI_BIALY "\x1b[0m"
#define ANSI_MAGNETA "\x1b[35m"

struct pomiar {
	int nrPomiaru;
	int nrCzujnika;
	char data[MAX_DLUGOSC_SLOWA];
	double temperatura;
	struct pomiar* poprzedni;
	struct pomiar* nastepny;
};

struct tablicaPomiarow {
	struct pomiar** pomiary;
	int liczbaPomiarow;
};

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t3 kwi 2020\n");
	printf("about: \tProgram na Laboratoria nr. 7\n");
	printf("\tProgram wczyta dane z pliku dane.txt do listy. Potem rozdzieli ja na tyle list ile jest czujnikow.\n");
	printf("\tNastepnie dla kazdej listy wypisze liczbe rekordow, pierwszy i ostatni rekord.\n");
	printf("\tNa koniec znajdzie i skopiuje rekord z najwyzsza temperatura na koniec kazdej z listy i ponownie\n");
	printf("\twypisze liczbe rekordow wraz z pierwszym i ostatnim zapisem.\n\n");
}

void WypiszElement(struct pomiar* element) {
	printf("%d %d %s %.2lf\n", element->nrPomiaru, element->nrCzujnika, element->data, element->temperatura);
}

void WypiszListe(struct pomiar* lista) {
	if (lista == NULL) {
		printf("info: lista nie zawiera elementow\n");
		return;
	}
	while (lista) {
		WypiszElement(lista);
		if (lista->nastepny == NULL) break;
		else lista = lista->nastepny;
	}
	printf("---\n");
	while (lista) {
		WypiszElement(lista);
		if (lista->poprzedni == NULL) break;
		else lista = lista->poprzedni;
	}
	printf("\n");
}

struct pomiar* DodajDoListy(FILE* in, struct pomiar* poprzedni) {
	struct pomiar* element = (struct pomiar*)calloc(sizeof(struct pomiar), 1);
	if (element) {
		int a, b;
		char c[MAX_DLUGOSC_SLOWA] = { '\0' };
		double d;

		fscanf_s(in, "%d", &a);
		if (feof(in)) {
			return NULL;
		}
		fscanf_s(in, "%d", &b);
		fscanf_s(in, "%s", c, MAX_DLUGOSC_SLOWA);
		fscanf_s(in, "%lf", &d);

		element->poprzedni = poprzedni;
		element->nastepny = NULL;
		element->nrPomiaru = a;
		element->nrCzujnika = b;
		element->temperatura = d;
		strcpy_s(element->data, MAX_DLUGOSC_SLOWA, c);
		return element;
	}
	else {
		printf("error - blad podczas alokacji\nkoniec programu\n");
		exit(0);
	}
}

struct pomiar* DodajElement(struct pomiar* najwyzsza, struct pomiar* poprzedni) {
	struct pomiar* element = (struct pomiar*)calloc(sizeof(struct pomiar), 1);
	if (element) {
		element->poprzedni = poprzedni;
		element->nastepny = NULL;
		element->nrPomiaru = najwyzsza->nrPomiaru;
		element->nrCzujnika = najwyzsza->nrCzujnika;
		element->temperatura = najwyzsza->temperatura;
		strcpy_s(element->data, MAX_DLUGOSC_SLOWA, najwyzsza->data);
		return element;
	}
	else {
		printf("error - blad podczas alokacji\nkoniec programu\n");
		exit(0);
	}
}

// Funkcja nr. 1
struct pomiar* OtworzPlik(const char* nazwain) {
	FILE* in;
	if (fopen_s(&in, nazwain, "r") == 0 && in != NULL) {
		printf("info: poprawnie otwarto plik %s\n", nazwain);

		struct pomiar* glowa = NULL;
		struct pomiar* ogon = NULL;
		while (!feof(in)) {
			if (glowa == NULL) {
				glowa = DodajDoListy(in, NULL);
				if (glowa != NULL) {
					ogon = glowa;
				}
			}
			else {
				ogon->nastepny = DodajDoListy(in, ogon);
				if (ogon->nastepny != NULL) {
					ogon = ogon->nastepny;
				}
			}
		}

		printf("info: poprawnie zamknieto plik %s\n\n", nazwain);
		fclose(in);
		return glowa;
	}
	else {
		printf("error - blad podczas otwierania pliku wejsciowego\nkoniec programu\n\n");
		exit(0);
	}
}

// Funkcja nr. 2
void PoliczElementy(struct pomiar* lista) {
	int suma = 0;
	struct pomiar* pierwszy = NULL, * ostatni = NULL;
	while (lista) {
		if (suma == 0) pierwszy = lista;
		if (lista->nastepny == NULL) ostatni = lista;
		
		suma++;
		lista = lista->nastepny;
	}
	printf(ANSI_MAGNETA "info: liczba rekordow = %d\n" ANSI_BIALY, suma);
	printf(ANSI_CYAN "pierwszy element: " ANSI_BIALY);
	WypiszElement(pierwszy);
	printf(ANSI_CYAN "ostatni element: " ANSI_BIALY);
	WypiszElement(ostatni);
	printf("\n");
}

// Funkcja nr. 3
struct tablicaPomiarow Scal(struct pomiar** lista) {
	struct pomiar** glowa = (struct pomiar**)calloc(sizeof(struct pomiar*), MAX_LICZBA_CZUJNIKOW);
	struct pomiar** ogon = (struct pomiar**)calloc(sizeof(struct pomiar*), MAX_LICZBA_CZUJNIKOW);
	if (glowa != NULL && ogon != NULL) {
		int liczbaCzujnikow = 0;
		while ((*lista)) {
			struct pomiar* tmp = (*lista)->nastepny;
			if (glowa[(*lista)->nrCzujnika - 1] == NULL) {
				glowa[(*lista)->nrCzujnika - 1] = (*lista);
				glowa[(*lista)->nrCzujnika - 1]->poprzedni = NULL;
				glowa[(*lista)->nrCzujnika - 1]->nastepny = NULL;
				ogon[(*lista)->nrCzujnika - 1] = glowa[(*lista)->nrCzujnika - 1];
			}
			else {
				ogon[(*lista)->nrCzujnika - 1]->nastepny = (*lista);
				ogon[(*lista)->nrCzujnika - 1]->nastepny->poprzedni = ogon[(*lista)->nrCzujnika - 1];
				ogon[(*lista)->nrCzujnika - 1]->nastepny->nastepny = NULL;
				ogon[(*lista)->nrCzujnika - 1] = ogon[(*lista)->nrCzujnika - 1]->nastepny;
			}
			if ((*lista)->nrCzujnika > liczbaCzujnikow) {
				liczbaCzujnikow = (*lista)->nrCzujnika;
			}
			(*lista) = tmp; // po przejrzeniu ostatniego rekordu, lista wskazuje na NULL czyli jest pusta
		}
		free(ogon);
		return tablicaPomiarow{ glowa, liczbaCzujnikow };
	}
	else {
		printf("error - blad podczas alokacji\nkoniec programu\n");
		exit(0);
	}
}

// Funkcja nr. 4
struct pomiar* NajwyzszyNaKoniec(struct pomiar* lista) {
	struct pomiar* wsk = lista;
	struct pomiar* kopia = lista;
	int pierwszy = 1;
	double najwyzsza = 0;
	while (true) {
		if (pierwszy || lista->temperatura > najwyzsza) {
			if (pierwszy) pierwszy = 0;
			najwyzsza = lista->temperatura;
			wsk = lista;
		}
		if (lista->nastepny == NULL) break;
		else lista = lista->nastepny;
	}
	// teraz wskaznik jest ustawiony na ostatnim elemencie
	printf(ANSI_ZOLTY "najwyzsza temperatura: " ANSI_BIALY);
	WypiszElement(wsk);
	lista->nastepny = DodajElement(wsk, lista);

	return kopia;
}

void DealokujListe(struct pomiar* lista) {
	while (lista) {
		struct pomiar* tmp = lista->nastepny;
		free(lista);
		lista = tmp;
	}
}

void DealokujTabliceCzujnikow(struct tablicaPomiarow* tab) {
	for (int i = 0; i < tab->liczbaPomiarow; i++) {
		DealokujListe(tab->pomiary[i]); // zwolnienie pamieci przeznaczonej na rekordy danego czujnika
		tab->pomiary[i] = NULL; // ustawienie wskaznika na ten obszar jako NULL, aby nie miec do niego dostepu
	}
}

// Zadanie II poziomu
void FiltrowanieMedianowe(struct pomiar* lista) {
	if (lista == NULL) {
		printf("info: lista jest pusta, dlatego nie mozna na niej wykonac filtrowania medianowego\n");
		return;
	}
	else if (lista->nastepny == NULL) {
		printf("info: lista zawiera tylko jeden element, dlatego nie mozna na niej wykonac filtrowania medianowego\n");
		return;
	}
	double staraWartosc = lista->temperatura;
	while (lista->nastepny) {
		if (lista->poprzedni != NULL && lista->nastepny != NULL) {
			double tmp = lista->temperatura;
			if ((staraWartosc > lista->temperatura && staraWartosc < lista->nastepny->temperatura) ||
				(staraWartosc < lista->temperatura && staraWartosc > lista->nastepny->temperatura)) { // mediana to lewy element
				lista->temperatura = staraWartosc;
			}
			else if ((lista->nastepny->temperatura > lista->temperatura && lista->nastepny->temperatura < staraWartosc) ||
					 (lista->nastepny->temperatura < lista->temperatura && lista->nastepny->temperatura > staraWartosc)) {
				lista->temperatura = lista->nastepny->temperatura;
			}
			staraWartosc = tmp;
		}
		else if (lista->nastepny == NULL) {
			return;
		}
		lista = lista->nastepny;
	}
}

void ZapiszListeDoPliku(const char* nazwaout, struct pomiar* lista) {
	FILE* out;
	if (fopen_s(&out, nazwaout, "w+") == 0 && out != NULL) {
		printf("info: poprawnie otwarto plik %s\n", nazwaout);
		while (lista) {
			fprintf(out, "%d\t%d\t%s\t%lf\n", lista->nrPomiaru, lista->nrCzujnika, lista->data, lista->temperatura);
			lista = lista->nastepny;
		}
		printf("info: zapisano do liste, zmodyfikowana filtrowaniem medianowym\n");
		printf("info: zamknieto plik %s\n", nazwaout);
		fclose(out);
	}
	else {
		printf("error - blad podczas otwierania pliku wyjsciowego\nkoniec programu\n");
		exit(0);
	}
}

int main() {
	Info();
	char nazwain[MAX_DLUGOSC_SLOWA] = "dane.txt";
	char nazwaout[MAX_DLUGOSC_SLOWA] = "wynik_dla_dane.txt";

	struct pomiar* lista = OtworzPlik(nazwain);
	if (lista) {
		printf(ANSI_ZIELONY "wszystkie czujniki:\n" ANSI_BIALY);
		PoliczElementy(lista);

		struct tablicaPomiarow tablica = Scal(&lista);
		
		for (int i = 0; i < tablica.liczbaPomiarow; i++) {
			printf(ANSI_ZIELONY "czujnik nr. %d:\n" ANSI_BIALY, i + 1);
			if (tablica.pomiary[i] != NULL) {
				PoliczElementy(tablica.pomiary[i]);
				tablica.pomiary[i] = NajwyzszyNaKoniec(tablica.pomiary[i]);
				printf("info: skopiowano rekord z najwyzsza temperatura na koniec\n\n");
				PoliczElementy(tablica.pomiary[i]);
			}
			else {
				printf("info: lista nie zawiera rekordow\n\n");
			}
		}
		
		// Zadanie II. poziomu
		FiltrowanieMedianowe(tablica.pomiary[0]);
		ZapiszListeDoPliku(nazwaout, tablica.pomiary[0]);

		DealokujTabliceCzujnikow(&tablica); // nie trzeba dealokowac listy, bo po rozdzieleniu listy lista wskazuja na NULL
	}
	else {
		printf("error: plik z danymi nie zawiera rekordow\n");
	}
	printf("\nkoniec programu\n");

	return 0;
}
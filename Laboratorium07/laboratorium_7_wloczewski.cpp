#include <iostream>
#include <stdlib.h>

#define MAX_LICZBA_CZUJNIKOW 10
#define MAX_DLUGOSC_SLOWA 20

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
	if (lista == NULL) {
		printf("info: lista nie zawiera elementow\n\n");
		return;
	}
	int suma = 0;
	struct pomiar* pierwszy = NULL, * ostatni = NULL;
	while (lista) {
		if (suma == 0) pierwszy = lista;
		if (lista->nastepny == NULL) ostatni = lista;
		
		suma++;
		lista = lista->nastepny;
	}
	printf("info: lista posiada %d rekordow\n", suma);
	printf("pierwszy element: ");
	WypiszElement(pierwszy);
	printf("ostatni element: ");
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
			(*lista) = tmp;
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
	if (lista == NULL) return NULL;
	
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
	printf("najwyzsza temperatura: ");
	WypiszElement(wsk);
	printf("\n");
	lista->nastepny = DodajElement(wsk, lista);

	return kopia;
}

void DealokujTabliceCzujnikow(struct tablicaCzujnikow* tab) {

}

int main() {
	char nazwain[MAX_DLUGOSC_SLOWA] = "test1.txt";

	struct pomiar* lista = OtworzPlik(nazwain);
	if (lista) {
		printf("wszystkie czujniki:\n");
		PoliczElementy(lista);

		struct tablicaPomiarow tablica = Scal(&lista);
		for (int i = 0; i < tablica.liczbaPomiarow; i++) {
			printf("czujnik nr. %d:\n", i + 1);
			PoliczElementy(tablica.pomiary[i]);
			tablica.pomiary[i] = NajwyzszyNaKoniec(tablica.pomiary[i]);
			PoliczElementy(tablica.pomiary[i]);
		}


	}
	else {
		printf("error: plik z danymi nie zawiera rekordow\n");
	}
	printf("\nkoniec programu\n");

	return 0;
}
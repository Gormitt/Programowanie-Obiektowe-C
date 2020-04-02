#include <iostream>
#include <stdlib.h>
#include <string.h>

#define MAX_LICZBA_CZUJNIKOW 10
#define MAX_DLUGOSC_SLOWA 30

struct pomiar {
	int nrPomiaru;
	int nrCzujnika;
	double temperatura;
	char data[MAX_DLUGOSC_SLOWA];

	struct pomiar* poprzedni;
	struct pomiar* nastepny;
};

struct tablicaPomiarow {
	int wielkosc;
	struct pomiar** pomiary;
};

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t2 kwi 2020\n");
	printf("about: \tRozwiazanie wejsciowki nr. 7\n");
	printf("\tProgram otwiera plik dane.txt, wczytuje z niego rekordy do kilku list.\n");
	printf("\tNastepnie zlicza i wypisuje ile jest elementow w kazdej z nich.\n");
	printf("\tW kolejnym kroku przenosi rekordy do jednej listy (w kolejnosci od najwczesniejszego),\n");
	printf("\ttak ze poprzednie 4 listy sa puste. Na koniec zapisuje wszystko do pliku.\n\n");
}

struct pomiar* DodajRekordDoListy(struct pomiar* poprzedni, int* nrPomiart, int* nrCzujnika, char* data, double* temperatura) {
	struct pomiar* element = (struct pomiar*)calloc(sizeof(struct pomiar), 1);
	if (element) {
		element->poprzedni = poprzedni;
		element->nastepny = NULL;

		element->nrPomiaru = *nrPomiart;
		element->nrCzujnika = *nrCzujnika;
		element->temperatura = *temperatura;
		strcpy_s(element->data, MAX_DLUGOSC_SLOWA, data);

		return element;
	}
	else {
		printf("error - blad podczas alokacji\n");
		exit(0);
	}
}

struct tablicaPomiarow OtworzPlik(char* nazwain) {
	FILE* in;
	if (fopen_s(&in, nazwain, "r") == 0 && in != NULL) {
		printf("info: poprawnie otwarto plik %s\n", nazwain);

		int liczbaCzujnikow = 0;
		struct pomiar** glowa = (struct pomiar**)calloc(sizeof(struct pomiar*), MAX_LICZBA_CZUJNIKOW);
		struct pomiar** za = (struct pomiar**)calloc(sizeof(struct pomiar*), MAX_LICZBA_CZUJNIKOW);
		if (glowa != NULL && za != NULL) {
			while (!feof(in)) {
				int nrPomiaru;
				int nrCzujnika;
				double temperatura;
				char data[MAX_DLUGOSC_SLOWA];

				fscanf_s(in, "%d", &nrPomiaru);
				if (feof(in)) {
					break;
				}
				fscanf_s(in, "%d", &nrCzujnika);
				fscanf_s(in, "%s", data, MAX_DLUGOSC_SLOWA);
				fscanf_s(in, "%lf", &temperatura);

				if (glowa[nrCzujnika - 1] == NULL) {
					glowa[nrCzujnika - 1] = DodajRekordDoListy(NULL, &nrPomiaru, &nrCzujnika, data, &temperatura);
					za[nrCzujnika - 1] = glowa[nrCzujnika - 1];
				}
				else {
					za[nrCzujnika - 1]->nastepny = DodajRekordDoListy(za[nrCzujnika - 1], &nrPomiaru, &nrCzujnika, data, &temperatura);
					za[nrCzujnika - 1] = za[nrCzujnika - 1]->nastepny;
				}
			}
			int iterator = 0;
			while (iterator < MAX_LICZBA_CZUJNIKOW) {
				if (glowa[iterator]) {
					liczbaCzujnikow = iterator + 1;
				}
				iterator++;
			}
			free(za);
			fclose(in);
			printf("info: plik %s zostal zamkniety\n\n", nazwain);
			
			if (liczbaCzujnikow == 0) return tablicaPomiarow{ liczbaCzujnikow, NULL }; // przypadek pustego pliku
			else return tablicaPomiarow{ liczbaCzujnikow, glowa }; // przypadek niepustego pliku
		}
		else {
			printf("error - blad podczas alokacji tablicy\n");
			free(za);
			fclose(in);
			exit(0);
		}
	}
	else {
		printf("error - blad podczas otwierania pliku z danymi\n");
		exit(0);
	}
}

void DealokujListe(struct pomiar* lista) {
	struct pomiar* tmp = NULL;
	while (lista) {
		tmp = lista->nastepny;
		free(lista);
		lista = tmp;
	}
}

struct tablicaPomiarow DealokujTabliceList(struct tablicaPomiarow* tab) {
	for (int i = 0; i < tab->wielkosc; i++) {
		DealokujListe(tab->pomiary[i]);
	}
	return tablicaPomiarow{ 0, NULL };
}

int PoliczElementy(struct tablicaPomiarow* tab) {
	int suma = 0;
	struct pomiar** tmp = (struct pomiar**)calloc(sizeof(struct pomiar*), tab->wielkosc);
	if (tmp != NULL) {
		for (int i = 0; i < tab->wielkosc; i++) {
			tmp[i] = tab->pomiary[i];
		}
	}
	else {
		printf("error - blad podczas alokacji tablicy\n");
		exit(0);
	}

	printf("liczba pomiarow z czujnikow, oraz najnizsza zanotowana temperatura:\n");
	for (int i = 0; i < tab->wielkosc; i++) {
		if (tab->pomiary[i] != NULL) {
			int liczba = 0;
			struct pomiar* najwiekszy = tab->pomiary[i];
			while (tab->pomiary[i]) {
				liczba++;
				if (tab->pomiary[i]->temperatura < najwiekszy->temperatura) {
					najwiekszy = tab->pomiary[i];
				}
				tab->pomiary[i] = tab->pomiary[i]->nastepny;
			}
			suma += liczba;
			printf("liczba rekordow czujnika nr. %d: %d\t", i + 1, liczba);
			printf("najnizsza: %d %d %s %.2lf\n", najwiekszy->nrPomiaru, najwiekszy->nrCzujnika, najwiekszy->data, najwiekszy->temperatura);
		}
		else {
			printf("czujnik nr. %d nie wykonal rzadnych pomiarow\n", i + 1);
		}
	}
	putchar('\n');

	for (int i = 0; i < tab->wielkosc; i++) {
		tab->pomiary[i] = tmp[i];
	}

	free(tmp);
	return suma;
}

struct pomiar* Scal(struct tablicaPomiarow* tab) {
	int przenos = 1;
	struct pomiar* glowa = NULL;
	struct pomiar* ogon = NULL;
	while (przenos) {
		for (int i = 0; i < tab->wielkosc; i++) {
			if (tab->pomiary[i] != NULL) {
				przenos = 1;
				break; // ciagle istnieje element do przeniesienia
			}
			przenos = 0;
		}
		if (przenos) {
			int pierwszy = 1;
			int indeks = 0;
			char dataNajmniejsza[MAX_DLUGOSC_SLOWA] = { '\0' };
			struct pomiar* wskNajnizsza = NULL;
			for (int i = 0; i < tab->wielkosc; i++) {
				if ((tab->pomiary[i] != NULL && pierwszy) || (tab->pomiary[i] != NULL && memcmp(tab->pomiary[i]->data, dataNajmniejsza, MAX_DLUGOSC_SLOWA) < 0)) {
					if (pierwszy) pierwszy = 0;
					strcpy_s(dataNajmniejsza, MAX_DLUGOSC_SLOWA, tab->pomiary[i]->data);
					indeks = i;
					wskNajnizsza = tab->pomiary[i];
				}
			}
			tab->pomiary[indeks] = tab->pomiary[indeks]->nastepny;

			if (glowa == NULL && wskNajnizsza != NULL) {
				glowa = wskNajnizsza;
				glowa->poprzedni = NULL;
				glowa->nastepny = NULL;
				ogon = glowa;
			}
			else if (wskNajnizsza != NULL) {
				ogon->nastepny = wskNajnizsza;
				ogon->nastepny->poprzedni = ogon;
				ogon->nastepny->nastepny = NULL;
				ogon = ogon->nastepny;
			}

		}
	}
	return glowa;
}

void ZapiszListeDoPliku(struct pomiar* lista, int liczbaRekordow, int liczbaCzujnikow) {
	FILE* out;
	if (fopen_s(&out, "wynik.txt", "w+") == 0 && out != NULL) {
		fprintf(out, "REKORDY\nliczba wszystkich pomiarow: %d\nliczba wszystkich czujnikow: %d\n\n", liczbaRekordow, liczbaCzujnikow);
		while (lista) {
			fprintf(out, "%d\t%d\t%s\t%.2lf\n", lista->nrPomiaru, lista->nrCzujnika, lista->data, lista->temperatura);
			lista = lista->nastepny;
		}
		fclose(out);
		printf("info: poprawnie utworzono, zapelniono rekordami i zamknieto plik wynik.txt\n");
	}
	else {
		printf("error - blad podczas otwierania pliku wynikowego\n");
		exit(0);
	}
}

int main() {
	Info();
	char nazwain[MAX_DLUGOSC_SLOWA] = "dane.txt";
	struct tablicaPomiarow tab = OtworzPlik(nazwain);
	
	if (tab.pomiary != NULL) {
		int suma = PoliczElementy(&tab);
		struct pomiar* lista = Scal(&tab);
		ZapiszListeDoPliku(lista, suma, tab.wielkosc);
		DealokujListe(lista);
	}
	else {
		printf("error - plik z danymi jest pusty\n");
	}
	tab = DealokujTabliceList(&tab);

	return 0;
}
#include <iostream>
#include <stdlib.h>

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
		printf("info: poprawnie otworzono plik %s\n", nazwain);

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

void PoliczElementy(struct tablicaPomiarow* tab) {
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
			printf("liczba rekordow czujnika nr. %d: %d\t", i + 1, liczba);
			printf("najnizsza: %d %d %s %.2lf\n", najwiekszy->nrPomiaru, najwiekszy->nrCzujnika, najwiekszy->data, najwiekszy->temperatura);
		}
		else {
			printf("czujnik nr. %d nie wykonal rzadnych pomiarow\n", i + 1);
		}
	}
	for (int i = 0; i < tab->wielkosc; i++) {
		tab->pomiary[i] = tmp[i];
	}
	free(tmp);
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
			double wartoscNajnizsza = 0;
			struct pomiar* wskNajnizsza = NULL;
			for (int i = 0; i < tab->wielkosc; i++) {
				if ((tab->pomiary[i] != NULL && pierwszy) || (tab->pomiary[i] != NULL && tab->pomiary[i]->temperatura < wartoscNajnizsza)) {
					if (pierwszy) pierwszy = 0;
					indeks = i;
					wartoscNajnizsza = tab->pomiary[i]->temperatura;
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

void ZapiszListeDoPliku(struct pomiar* lista) {
	FILE* out;
	if (fopen_s(&out, "wynik.txt", "w+") == 0 && out != NULL) {
		while (lista) {
			fprintf(out, "%d %d %s %lf\n", lista->nrPomiaru, lista->nrCzujnika, lista->data, lista->temperatura);
			struct pomiar* tmp = lista->nastepny;
			free(lista);
			lista = tmp;
		}
		fclose(out);
		printf("info: lista zostala zapisana do pliku\n");
		printf("info: lista zostala zdealokowana\n\n");
	}
	else {
		printf("error - blad podczas otwierania pliku wynikowego\n");
		exit(0);
	}
}

int main() {
	char nazwain[MAX_DLUGOSC_SLOWA] = "test.txt";
	struct tablicaPomiarow tab = OtworzPlik(nazwain);
	
	if (tab.pomiary != NULL) {
		PoliczElementy(&tab);
		struct pomiar* lista = Scal(&tab);
		ZapiszListeDoPliku(lista);
	}
	else {
		printf("error - plik z danymi jest pusty\n");
	}

	tab = DealokujTabliceList(&tab);
	return 0;
}
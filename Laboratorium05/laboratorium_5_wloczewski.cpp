#include <iostream>
#include <stdlib.h>

#define DL_SLOWA 40
#define ELEMENTY_LINII 4
#define ERROR_LICZBA_ZAKRES printf("error - podana liczba jest spoza zakresu, prosze sprobuj ponownie: ");
#define ERROR_LICZBA_BLAD printf("error - blad podczsa wczytywania liczby, prosze sprobuj ponownie: ");
#define ERROR_SLOWO_BLAD printf("error - blad podczas wczytywania slowa, prosze sprobuj ponownie: ");
#define ERROR_PLIK printf("error - blad podczas otwierania pliku");
#define ERROR_ALOKACJA printf("error - blad podczas alokacji tablicy");

struct pojazd {
	char marka[DL_SLOWA];
	char model[DL_SLOWA];
	int rokProdukcji;
	float pojemnoscSilnika;
};

struct kolekcjaPojazdow {
	struct pojazd* tab;
	int liczbaElementow;
};

void CzyszczeniBufora() {
	while (getchar() != '\n') {}
}

void WczytajLiczbe(const char* info, int* wpis, int min, int max) {
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

void WczytajSlowo(const char* info, char* slowo) {
	printf("%s, wczytywanie slowa: ", info);
	while (scanf_s("%s", slowo, DL_SLOWA) != 1 || getchar() != '\n') {
		CzyszczeniBufora();
		ERROR_SLOWO_BLAD
	}
}

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

struct kolekcjaPojazdow WczytajPlik(char* nazwaPliku) {
	FILE* in;
	if (fopen_s(&in, nazwaPliku, "r") == 0 && in != NULL) {
		int liczbaLinii = ZliczLinie(in);
		if (liczbaLinii == 0) {
			fclose(in);
			exit(0);
		}
		
		struct pojazd* tab = (struct pojazd*)malloc(sizeof(struct pojazd) * liczbaLinii);
		if (tab != NULL) {
			rewind(in);
			for (int i = 0; i < liczbaLinii; i++) {
				char marka[DL_SLOWA] = { '\0' };
				char model[DL_SLOWA] = { '\0' };
				int rokProdukcji;
				float pojemnosc;
				fscanf_s(in, "%s", marka, DL_SLOWA);
				fscanf_s(in, "%s", model, DL_SLOWA);
				fscanf_s(in, "%d", &rokProdukcji);
				fscanf_s(in, "%f", &pojemnosc);

				strcpy_s(tab[i].marka, DL_SLOWA, marka);
				strcpy_s(tab[i].model, DL_SLOWA, model);
				tab[i].rokProdukcji = rokProdukcji;
				tab[i].pojemnoscSilnika = pojemnosc;
			}

			for (int i = 0; i < liczbaLinii; i++) {
				//printf("%s %s %d %f\n", tab->marka, tab->model, tab->rokProdukcji, tab->pojemnoscSilnika);
			}

			return kolekcjaPojazdow {tab, liczbaLinii};
		}
		else {
			ERROR_ALOKACJA
			exit(0);
		}

		fclose(in);
	}
	else {
		exit(0);
	}
}

int main() {
	FILE* in;

	char nazwaIn[DL_SLOWA];
	WczytajSlowo("podaj nazwe pliku z danymi wejsciowymi", nazwaIn);
	
	struct kolekcjaPojazdow k = WczytajPlik(nazwaIn);
	for (int i = 0; i < k.liczbaElementow; i++) {
		printf("%s %s %d %f\n", k.tab[i].marka, k.tab[i].model, k.tab[i].rokProdukcji, k.tab[i].pojemnoscSilnika);
	}

	free(k.tab);
	return 0;
}
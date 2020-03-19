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

void WczytajSlowo(const char* info, char* slowo) {
	printf("%s, wczytywanie slowa: ", info);
	while (scanf_s("%s", slowo, DL_SLOWA) != 1 || getchar() != '\n') {
		CzyszczeniBufora();
		ERROR_SLOWO_BLAD
	}
}

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

void WczytajLiczbeZmiennoprzecinkowa(const char* info, float* wpis, float min, float max) {
	int pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("%s, wczytywanie liczby z przedzialu [%f, %f]: ", info, min, max);
		}
		else {
			ERROR_LICZBA_ZAKRES
		}
		while (scanf_s("%f", wpis) != 1 || getchar() != '\n') {
			CzyszczeniBufora();
			ERROR_LICZBA_BLAD
		}
	} while (*wpis < min || *wpis > max);
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
			printf("info: podany plik nie zawiera zadnych danych.\n");
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

void WypiszKolekcje(kolekcjaPojazdow k) {
	for (int i = 0; i < k.liczbaElementow; i++) {
		printf("%s %s %d %.2f\n", k.tab[i].marka, k.tab[i].model, k.tab[i].rokProdukcji, k.tab[i].pojemnoscSilnika);
	}
}

void PobierzNoweAuto(struct pojazd* k) {
	int rok;
	float pojemnosc;
	char wpis[DL_SLOWA];
	WczytajSlowo("podaj marke nowego samochodu", wpis);
	strcpy_s(k->marka, DL_SLOWA, wpis);
	WczytajSlowo("podaj model nowego samochodu", wpis);
	strcpy_s(k->model, DL_SLOWA, wpis);
	
	WczytajLiczbeCalkowita("podaj rok nowego samochodu", &rok, 1900, 2020);
	WczytajLiczbeZmiennoprzecinkowa("podaj pojemnosc silnika nowego samochodu", &pojemnosc, 1.0, 10.0);
	k->rokProdukcji = rok;
	k->pojemnoscSilnika = pojemnosc;
}

struct kolekcjaPojazdow PowiekszKolekcje(kolekcjaPojazdow k) {
	struct pojazd* tmp = (struct pojazd*)realloc(k.tab, sizeof(struct pojazd) * (k.liczbaElementow + 1));
	if (tmp == NULL) {
		printf("info - nie udalo sie powiekszyc tablicy instrukcja realloc, program tworzy tablice od nowa i przywraca dane\n");
		struct pojazd* nowa = (struct pojazd*)malloc(sizeof(struct pojazd) * (k.liczbaElementow + 1));
		if (nowa != NULL) {
			for (int i = 0; i < k.liczbaElementow; i++) {
				strcpy_s(nowa[i].marka, DL_SLOWA, k.tab[i].marka);
				strcpy_s(nowa[i].model, DL_SLOWA, k.tab[i].model);
				nowa[i].rokProdukcji = k.tab[i].rokProdukcji;
				nowa[i].pojemnoscSilnika = k.tab[i].pojemnoscSilnika;
			}
			free(k.tab);
			PobierzNoweAuto(&nowa[k.liczbaElementow]);
			return kolekcjaPojazdow{ nowa, k.liczbaElementow + 1 };
		}
		else {
			ERROR_ALOKACJA
			exit(0);
		}
	}
	else {
		PobierzNoweAuto(&tmp[k.liczbaElementow]);
		return kolekcjaPojazdow{ tmp, k.liczbaElementow + 1 };
	}
}

void ZapiszKolekcje(struct kolekcjaPojazdow k, char* nazwaOut) {
	FILE* out;
	if (fopen_s(&out, nazwaOut, "a+") == 0 && out != NULL) {
		for (int i = 0; i < k.liczbaElementow; i++) {
			fprintf(out, "%s %s %d %.2f\n", k.tab[i].marka, k.tab[i].model, k.tab[i].rokProdukcji, k.tab[i].pojemnoscSilnika);
		}
	}
	else {
		ERROR_ALOKACJA
		exit(0);
	}
}

int main() {
	FILE* in;

	char nazwaIn[DL_SLOWA];
	char nazwaOut[DL_SLOWA];
	WczytajSlowo("podaj nazwe pliku z danymi wejsciowymi", nazwaIn);
	WczytajSlowo("podaj nazwe pliku na zapisanie danych", nazwaOut);
	
	struct kolekcjaPojazdow kol = WczytajPlik(nazwaIn);
	printf("\nwczytana z pliku kolekcja samochodow: \n");
	WypiszKolekcje(kol);

	kol = PowiekszKolekcje(kol);
	printf("\nkolekcja powiekszona o jeden pojazd podany wg. specyfikacji uzytkownika: \n");
	WypiszKolekcje(kol);

	ZapiszKolekcje(kol, nazwaOut);

	free(kol.tab);
	return 0;
}
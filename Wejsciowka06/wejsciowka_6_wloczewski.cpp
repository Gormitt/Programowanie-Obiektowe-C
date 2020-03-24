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

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t24 mar 2020\n");
	printf("about: \tRozwiazanie wejsciowki na laboratoria nr. 6\n");
	printf("\tProgram wczytan dane czujnikow temperatury z pliku: dane.txt do listy jednokierunkowej.\n");
	printf("\tNastepnie zamknie plik i podzieli liste (poprzez przenoszenie elementow) na mniejsze listy\n");
	printf("\tktore zawiera odczyty odpowiednio z kolejnych czujnikow. Na koniec wypisze liczbe\n");
	printf("\tpomiarow z kazdego z nich, poprosi o nawe pliku wyjsciowego i utworzy dla kazdego czujnika plik\n");
	printf("\t(dodajac indeks to podanej nazwy) zapisujac do niego dane z konkretnego urzadzenia pomiarowego.\n\n");
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
				exit(0);
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
@ ret   **czujniki - wskaznik do dynamicznej tablicy, przechowujacej glowy list, czyli wskazniki do pierwszych
        elementow kazdej z utoroznych list
*/
struct pomiar** UzupelnijCzujniki(struct pomiar* lista, int* pomiaryCzujnikow) {
	struct pomiar** czujniki = (struct pomiar**)calloc(sizeof(struct pomiar*), LICZBA_CZUJNIKOW);
	struct pomiar** dane = (struct pomiar**)calloc(sizeof(struct pomiar*), LICZBA_CZUJNIKOW);
	if (czujniki != NULL && dane != NULL) {
		while (lista) {
			struct pomiar* tmp = lista->nastepny;
			
			int numer = lista->nrCzujnika - 1;
			if (czujniki[numer] == NULL) {
				czujniki[numer] = lista;
				dane[numer] = czujniki[numer];
			}
			else {
				dane[numer]->nastepny = lista;
				dane[numer] = dane[numer]->nastepny;
			}
			pomiaryCzujnikow[numer] += 1;
			lista->nastepny = NULL;
			lista = tmp;
		}
		free(dane);
		return czujniki;
	}
	else {
		ERROR_ALOKACJA
		exit(0);
	}
}

/*
@ brief Funkcja do zapisania listy do pliku
@ param *out - wskaznik do poczatku pliku otwartego w trybie w+ (utworz lub zastap plik nowym - do zapisu)
@ param *lista - wskaznik do poczatku zapisywanej listy
*/
void ZapiszListeDoPliku(FILE* out, struct pomiar* lista) {
	while (lista) {
		fprintf(out, "%d %d %s %lf\n", lista->nrPomiaru, lista->nrCzujnika, lista->data, lista->temp);
		lista = lista->nastepny;
	}
}

int main() {
	Info();
	FILE* in;
	FILE* out;

	int* pomiaryCzujnikow = (int*)calloc(sizeof(int), LICZBA_CZUJNIKOW);
	if (pomiaryCzujnikow == NULL) {
		ERROR_ALOKACJA
		exit(0);
	}
	else if (fopen_s(&in, "dane.txt", "r") == 0 && in != NULL) {
		struct pomiar* lista = WczytajPlikDoListy(in);
		struct pomiar** czujniki = UzupelnijCzujniki(lista, pomiaryCzujnikow);;
		lista = NULL;

		for (int i = 0; i < LICZBA_CZUJNIKOW; i++) {
			printf("liczba pomiarow wykonanych przez czujnik nr. %d: %d\n", i + 1, pomiaryCzujnikow[i]);
		}
		
		char nazwaout[DL_SLOWA];
		WczytajSlowo("podaj nazwe pliku wyjsciowego [do nazwy zostanie automatycznie dodany numer czujnika]", nazwaout);
		for (int i = 0; i < LICZBA_CZUJNIKOW; i++) {
			char tmp[DL_SLOWA + 1] = { '\0' };
			char ind[DL_SLOWA] = { '1' + i, '.', 't', 'x', 't', '\0' };
			strcpy_s(tmp, DL_SLOWA + 1, nazwaout);
			strcat_s(tmp, DL_SLOWA + 1, ind);
			if (fopen_s(&out, tmp, "w+") == 0 && out != NULL) {
				ZapiszListeDoPliku(out, czujniki[i]);
				fclose(out);
			}
			else {
				ERROR_PLIK_OTWARCIE
			}
		}

		free(czujniki);
		free(pomiaryCzujnikow);
		DealokujListe(lista);
	}
	else {
		ERROR_PLIK_OTWARCIE
		exit(0);
	}

	return 0;
}
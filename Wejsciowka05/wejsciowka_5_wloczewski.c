#include <stdio.h>

#define DL_SLOWA 20
#define ERROR_LICZBA printf("error - blad podczas wczytywania liczby, prosze sprobuj ponownie: ");
#define ERROR_NAPIS printf("error - blad podczas wczytywania napisu, prosze sprobuj ponownie: ");
#define ERROR_ZAKRES printf("error - podana liczba jest spoza zakresu, prosze sprobuj ponownie: ");

/*
@ brief Funkcja do wypisania informacji o programie i autorze
*/
void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t16 mar 2020\n");
	printf("about: \tWejsciowka na laboratoria nr. 5\n");
	printf("\tProgram wczyta z pliku liczby binarne i je przekonwertuje.\n");
	printf("\tW kolejnym kroku, uporzadkuje je malejaco.\n\n");
}

/*
@ brief Funkcja do czyszczenie bufora
*/
void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

/*
@ brief Funkcja do wczytywania liczby calkowitej z przedzialu [min, max]
@ param cost *info - wiadomosc tekstowa do uzytkownika
@ param *wpis - wskaznik do miejsca gdzie ma wyladowac wczytana liczba
@ param min - minimalna liczba
@ param max - maksymalna liczba
*/
void WczytajLiczbe(const char* info, int* wpis, int min, int max) {
	int pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("%s, wczytywanie liczby z przedzialu [%d, %d]: ", info, min, max);
		}
		else {
			ERROR_ZAKRES
		}
		while (scanf_s("%d", wpis) != 1 || getchar() != '\n') {
			CzyszczenieBufora();
			ERROR_LICZBA
		}
	} while (*wpis < min || *wpis > max);
}

/*
@ brief Funkcja do wczytania slowa
*/
void WczytajSlowo(const char* info, char* s) {
	printf("%s, wczytywanie slowa: ", info);
	while (scanf_s("%s", s, DL_SLOWA) != 1 || getchar() != '\n') {
		CzyszczenieBufora();
		ERROR_NAPIS
	}
}

/*
@ brief Funkcja do konwersji liczby binarner na decymalna, bez znajomosci dlugosci
		Funkcja nie zna dlugosci liczby, dlatego korzysta z postaci iloczynowej.
@ param *bin - wskaznik do tablicy binarner
@ param *dec - wskaznik to zmiennej, ktora przechowa wartosc tej liczby
*/
void Bin2Int(char* bin, int* dec) {
	for (int i = 0; bin[i] != '\0'; i++) {
		*dec *= 2;
		*dec += (int)(bin[i] - '0');
	}
}

int main() {
	Info();

	char nazwaIn[DL_SLOWA];
	WczytajSlowo("podaj nazwe pliku wejsciowego, ktory ma liczby binarne", nazwaIn);


	return 0;
}
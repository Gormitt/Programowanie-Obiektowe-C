#include <iostream>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define DLUGOSC_SLOWA 20
#define ERROR_NAPIS printf("error - blad podczas wczytywania napisu, prosze sprobuj ponownie: ");
#define ERROR_PLIK printf("error - blad podczas otwierania jednego z plikow %s %s\n", nazwaIn, nazwaOut);

/*
@ brief Funkcja do wypisania informacji o autorze i przeznaczeniu programu.
*/
void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t13 mar 2020\n");
	printf("about: \tLaboratorium 4\n");
	printf("\tProgram wczyta slowo z pliku wejsciowego, kazda wielka litere zamieni na mala,\n");
	printf("\tkazda mala litere zamieni na '_'. Tak zmienione slowo zapisze do pliku wyjsciowego.\n");
	printf("\tPlik wyjsciowy jest tworzony podczas dzialania programu.\n\n");
}

/*
@ brief Funkcja do czyszczenie bufora
*/
void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

/*
@ brief Funkcja do wczytania napisu o dlugosci zdefiniowanej stala
@ param *komunikat - komunikat do uzytkownika o tym co jest wczytywane
@ param *slowo - wskaznik do tablicy, ktora przechowa napis
*/
void WczytajNapis(const char* komunikat, char* slowo) {
	printf("%s: ", komunikat);
	while (scanf_s("%s", slowo, DLUGOSC_SLOWA) != 1 || getchar() != '\n') {
		CzyszczenieBufora();
		ERROR_NAPIS
	}
}

/*
@ brief Funkcja do zmiany liter w slowie wg. zasad okreslonych w zadaniu
@ param *slowo - wskaznik do tablicy zawierajacej slowo
*/
void PrzekonwertujSlowo(char* slowo) {
	int indeks = 0;
	while (slowo[indeks] != '\0') {
		if (isalpha(slowo[indeks])) { // jezeli sprawdzany znak slowa to jest litera
			if (isupper(slowo[indeks])) {
				slowo[indeks] = (char)tolower(slowo[indeks]);
			}
			else {
				slowo[indeks] = '_';
			}
		}
		indeks++;
	}
}

/*
@ brief Funkcja do przekonwertowania wszystkich slow w pliku, tak
        jak okresla to zadanie.
@ param *in - wskaznik do otwartego pliku, gdzie sa slowa do zamiany
@ param *out - wskaznik do otwartego pliku, gdzie maja sie znalezc zmienione slowa
*/
void PrzekonwertujPlik(FILE* in, FILE* out) {
	int liczbaSlow = 0;
	char a[DLUGOSC_SLOWA] = {'\0'};
	char b[DLUGOSC_SLOWA] = {'\0'};
	while (!feof(in)) {
		fscanf_s(in, "%s", a, DLUGOSC_SLOWA);
		
		if (liczbaSlow == 0 || memcmp(a, b, sizeof(a)) != 0) {
			strcpy_s(b, a);
			
			char kopia[DLUGOSC_SLOWA];
			strcpy_s(kopia, a);
			printf("slowo pobrane: %s\t", kopia);
			PrzekonwertujSlowo(kopia);
			printf("slowo zmienione: %s\n", kopia);
			fprintf(out, "%s\n", kopia);

			liczbaSlow++;
		}
		else {
			break;
		}
		
	}
	printf("liczba slow w pliku wejsciowym: %d\n", liczbaSlow);
}

int main() {
	Info();	

	FILE *in, *out;
	char nazwaIn[DLUGOSC_SLOWA];
	char nazwaOut[DLUGOSC_SLOWA];
	WczytajNapis("podaj nazwe pliku wejsciowego", nazwaIn);
	WczytajNapis("podaj nazwe pliku wyjsciowego", nazwaOut);
	
	if (fopen_s(&in, nazwaIn, "r") == 0 && in != NULL && fopen_s(&out, nazwaOut, "a+") == 0 && out != NULL) {
		printf("poprawnie otworzono pliki %s oraz %s\n\n", nazwaIn, nazwaOut);

		PrzekonwertujPlik(in, out);

		fclose(in);
		fclose(out);
	}
	else {
		ERROR_PLIK
	}

	return 0;
}
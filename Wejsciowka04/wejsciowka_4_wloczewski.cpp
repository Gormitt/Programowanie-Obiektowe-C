#include <iostream>
#include <stdlib.h>
#include <string.h>

#define DLUGOSC_NAPISU 20
#define WIELKOSC_TABLICY 5

struct Para {
	char napis[DLUGOSC_NAPISU];
	int liczba;
};

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t8 mar 2020\n");
	printf("about: \tRozwiazanie wejsciowki nr. 4\n");
	printf("\tProgram wczytuje dane z pliku A, zmienia je i zapisuje do pliku B.\n\n");
}

/*
@ brief Funkcja do oczytania jednego wiersza z pliku.
@ param *f - wskaznik do otwartego pliku
@ param *p - wskaznik do tablicy par [para to struktura]
@ ret   0 - w przypadku niepoprawnego wczytania jednego wiersza
        1 - w przypadku poprawnego wczytania jednego wiersza
*/
int Wiersz(FILE* f, struct para* p) {
	return 1;
}

int main() {	
	char buf[DLUGOSC_NAPISU];
	FILE* stream;
	errno_t err = fopen_s(&stream, "plik_wejscie.txt", "r");
	/*
	if (err != 0) {
		printf("error - can't open plik_wejscie.txt\n");
	}
	else {
		printf("file plikl_wejscie.txt was opened succesfuly\n");
	}
	*/
	if (stream != NULL) {
		while (!feof(stream)) {
			fscanf_s(stream, "%s", buf, DLUGOSC_NAPISU);
			printf("pobrana linia: %s\n", buf);
		}
		fclose(stream);
	}

	return 0;
}
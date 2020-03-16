#include <iostream>

#define ERROR_LICZBA printf("error - blad podczas wczytywania liczby, prosze sprobuj ponownie: ");
#define ERROR_ZAKRES printf("error - podana liczba jest spoza zakresu, prosze sprobuj ponownie: ");

/*
@ brief Funkcja do wypisania informacji o programie i autorze
*/
void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t16 mar 2020\n");
	printf("about: \tWejsciowka na laboratoria nr. 5\n\n");
}

/*
@ brief Funkcja do czyszczenie bufora
*/
void Czyszczeniebufora() {
	while (getchar() != '\n') {}
}

/*
@ brief Funkcja do wczytywania liczby calkowitej z przedzialu [min, max]
@ param min - minimalna liczba
@ param max - maksymalna liczba
@ ret   wpis - pobrana liczba calkowita
*/
int WczytajLiczbe(int min, int max) {
	int wpis = 0, pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("wczytywanie liczby z przedzialu [%d, %d]: ", min, max);
		}
		else {
			ERROR_ZAKRES
		}
		while (scanf_s("%d", &wpis) != 1 || getchar() != '\n') {
			Czyszczeniebufora();
			ERROR_LICZBA
		}
	} while (wpis < min || wpis > max);
	return wpis;
}

int main() {
	
	return 0;
}
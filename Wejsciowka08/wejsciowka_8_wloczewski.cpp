#include <iostream> 
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define DL_SLOWA 20
#define MIN 1
#define MAX 20

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t8 kwi 2020\n");
	printf("about: \tRealizacja Programu - Wejsciowka nr. 8\n");
	printf("\tProgram to gra zrecznosciowa. Komputer pobierze nazwe uzytkownika i liczbe calkowita.\n");
	printf("\tNastepnie wylosuje okreslona przez wczytana liczbe ilosc liter, ktore uzytkownik musi\n");
	printf("\twpisac na klawiaturze w jak najkrotszym czasie. Wynik bedzie zapisny do pliku tekstowego.\n\n");
}

void CzyszczenieBufora() {
	while (getchar() != '\n') {}
}

void WczytajSlowo(const char* info, char* slowo) {
	printf("%s: ", info);
	while (scanf_s("%s", slowo, DL_SLOWA - 4) != 1 || getchar() != '\n') {
		CzyszczenieBufora();
		printf("error - blad podczas wczytywania slowa, prosze sprobuj ponownie: ");
	}
}

int WczytajLiczbe(const char* info, int min, int max) {
	int liczba;
	int pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("%s (przedzial domkniety [%d, %d]): ", info, min, max);
		}
		else {
			printf("error - podana liczba wykracza poza zakres, prosze sprobuj ponownie: ");
		}
		while (scanf_s("%d", &liczba) != 1 || getchar() != '\n') {
			CzyszczenieBufora();
			printf("error - blad podczas wczytywania liczby, prosze sprobuj ponownie: ");
		}
	} while (liczba < min || liczba > max);
	return liczba;
}

void PrzeprowadzTest() {
	int poprawne = 0, niepoprawne = 0;
	int liczba = WczytajLiczbe("wczytaj liczbe naturalna", MIN, MAX);

	time_t start, finish;
	time(&start);
	for (int i = 0; i < liczba; i++) {
		char litera = rand() % ('z' - 'a' + 1) + 'a';
		printf("$%c ", litera);
		char wpis = (char)_getch();

		if (wpis == litera) poprawne++;
		else niepoprawne++;
	}
	time(&finish);

	double czas = difftime(finish, start);
	printf("\npoprawne: %d\nniepoprawne: %d\tczas: %lf\n", poprawne, niepoprawne, czas);
}

int main() {
	srand(time(NULL));
	Info();

	FILE* zapis;
	char nick[DL_SLOWA] = { '\0' };

	WczytajSlowo("podj nick", nick);
	strcat_s(nick, DL_SLOWA, ".txt");

	if (fopen_s(&zapis, nick, "w") == 0 && zapis != NULL) {
		printf("info - otworzono istniejacy plik o nazwie %s\n", nick);
		PrzeprowadzTest();
	}
	else if (fopen_s(&zapis, nick, "w+") == 0 && zapis != NULL) {
		printf("info - plik o nazwie %s nie isnial i zostal dopiero utworzony\n", nick);
		PrzeprowadzTest();
	}

	return 0;
}
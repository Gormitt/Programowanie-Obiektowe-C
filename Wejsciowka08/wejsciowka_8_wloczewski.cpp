#include <iostream> 
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define DL_SLOWA 50
#define DL_SCIEZKI 150
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

int CzyPlikIstnieje(char* nazwa) {
	FILE* plik = NULL;
	if (fopen_s(&plik, nazwa, "r+") == 0 && plik != NULL) {
		fclose(plik);
		return 1;
	}
	else {
		return 0;
	}
}

void WyluskajSciezke(char* sciezka, const char* nazwaProjektu, const char* nazwaPliku) {
	int dlugosc = strlen(sciezka) - 1;
	int drugieZalamanie = 0;
	while (sciezka[dlugosc] != '\\' || !drugieZalamanie) {
		if (sciezka[dlugosc] == '\\') drugieZalamanie = 1;
		dlugosc--;
	}
	sciezka[dlugosc] = '\0';
	
	int tmp = dlugosc + 1;
	while (sciezka[tmp] != '\0') {
		sciezka[tmp] = ' ';
		tmp++;
	}
	sciezka[tmp] = ' ';
	
	strcat_s(sciezka, DL_SCIEZKI, "\\");
	strcat_s(sciezka, DL_SCIEZKI, nazwaProjektu);
	strcat_s(sciezka, DL_SCIEZKI, "\\");
	strcat_s(sciezka, DL_SCIEZKI, nazwaPliku);
	dlugosc += strlen(nazwaProjektu) + strlen(nazwaPliku) + 2 - 1;
}

void ZapiszCzas(char* data) {
	struct tm czasinfo;
	__time64_t czas;

	// pobierz czas jako 64 bitowy integer
	_time64(&czas);
	// przekonwertuj na czas lokalny [do struktury tm* czasinfo]
	if (_localtime64_s(&czasinfo, &czas)) {
		printf("Invalid argument to _localtime64_s.");
		exit(1);
	}
	// konwersja na reprezentacje znakami ACII
	if (strftime(data, DL_SLOWA, "%d.%m.%Y %H:%M:%S", &czasinfo) == 0) {
		printf("error - niepoprawny argument w funkcji strftime, koniec programu");
		exit(1);
	}
}

void PrzeprowadzTest(FILE* zapis, FILE* log, char* data, char* nick) {
	fprintf(zapis, "data:\t%s\n", data);

	int poprawne = 0, niepoprawne = 0;
	int liczba = WczytajLiczbe("wczytaj liczbe naturalna", MIN, MAX);
	ZapiszCzas(data);
	fprintf(log, "%s\tuzytkownik %s podal liczbe: %d\n", data, nick, liczba);

	// zmienne potrzebne do przechowania wartosci czasowych
	time_t start, finish, aktualny;
	// rozpoczecie odliczania do konca testu + zapisanie rozpoczecia testu
	time(&start);
	time(&aktualny);
	for (int i = 0; i < liczba; i++) {
		// wylosowanie litery
		char litera = rand() % ('z' - 'a' + 1) + 'a';
		// wypisanie i wczytanie litery
		printf("$%c ", litera);
		ZapiszCzas(data);
		fprintf(log, "%s\tw grze uzytkownika %s wylosowano litere %c\n", data, nick, litera);
		char wpis = (char)_getch();
		ZapiszCzas(data);
		// sprawdzenie czy podana litera jest poprawna
		if (wpis == litera) {
			poprawne++;
			fprintf(log, "%s\tuzytkownik %s podal poprawna odpowiedz\n", data, nick);
		}
		else {
			niepoprawne++;
			fprintf(log, "%s\tuzytkownik %s podal niepoprawna odpowiedz [%c]\n", data, nick, wpis);
		}
	}
	time(&finish);
	double czas = difftime(finish, start); // konwersja czasu rozpoczecia na date

	printf("\ninfo - zapisuje wynik do pliku gracza\n");
	fprintf(zapis, "litery:\t%d\n", liczba);
	fprintf(zapis, "dobre:\t%d\n", poprawne);
	fprintf(zapis, "zle:\t%d\n", niepoprawne);
	fprintf(zapis, "czas:\t%.1lf sekund\n\n", czas);
	ZapiszCzas(data);
	fprintf(log, "%s\tzapisanie wyniku do pliku [%d dobrych, %d zlych] zakonczenie gry gracza %s\n", data, poprawne, niepoprawne, nick);
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	Info();

	FILE* zapis = NULL;
	FILE* log = NULL;
	char nazwaProjektu[DL_SLOWA] = "Wejsciowka08";
	char nazwa[DL_SLOWA] = { '\0' };
	char nick[DL_SLOWA] = { '\0' };
	char sciezka[DL_SCIEZKI] = { '\0' };
	char* data = (char*)calloc(sizeof(char), DL_SLOWA);

	// otwarcie pliku z logami
	if (fopen_s(&log, "log.txt", "a") == 0 && log != NULL && data != NULL) {
		// wczytanie nazwy uzytkownika i utworzenie z niej nazwy pliku
		WczytajSlowo("podj nick", nick);
		strcpy_s(nazwa, DL_SLOWA, nick);
		strcat_s(nazwa, DL_SLOWA, ".txt");
		strcpy_s(sciezka, DL_SCIEZKI, argv[0]);
		WyluskajSciezke(sciezka, nazwaProjektu, nazwa);

		ZapiszCzas(data);
		fprintf(log, "%s\tpobranie slowa: %s\n", data, nick);

		// sprawdzenie czy plik uzytkownika istnieje i poinformowanie o skutku
		if (CzyPlikIstnieje(nazwa)) {
			// jezeli plik istnieje to zostaje otwarty w trybie do dolaczania
			printf("info - plik o nazwie %s istnieje\n", nazwa);
			if (fopen_s(&zapis, nazwa, "a") == 0 && zapis != NULL) {
				ZapiszCzas(data);
				fprintf(log, "%s\trozpoznanie uzytkownika, otwarcie pliku %s\n", data, nazwa);

				PrzeprowadzTest(zapis, log, data, nick);
				fclose(zapis);

				ZapiszCzas(data);
				fprintf(log, "%s\tzamkniecie pliku %s\n", data, nazwa);
			}
		}
		else {
			// jezeli plik nie istnieje to zostaje utworzony	
			printf("info - plik o nazwie %s nie istnieje\n", nazwa);
			printf("info - sciezka do utworzonego pliku: %s\n", sciezka); // TODO 
			if (fopen_s(&zapis, nazwa, "w+") == 0 && zapis != NULL) {
				ZapiszCzas(data);
				fprintf(log, "%s\tdodanie nowego uzytkownika, utworzenie i otwarcie pliku %s\n", data, nazwa);

				PrzeprowadzTest(zapis, log, data, nick);
				fclose(zapis);

				ZapiszCzas(data);
				fprintf(log, "%s\tzamkniecie pliku %s\n", data, nazwa);
			}
		}
		fclose(log);
		free(data);
	}

	return 0;
}
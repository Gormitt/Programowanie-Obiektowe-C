#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <io.h>

#define DL_SLOWA 20
#define DL_DATY 80
#define DL_SCIEZKI 150

void WyczyscBufor() {
	while (getchar() != '\n') {}
}

void WczytajSlowo(const char* info, char* slowo) {
	printf("%s: ", info);
	while (scanf_s("%s", slowo, DL_SLOWA) != 1 || getchar() != '\n') {
		printf("error - blad podczas pobierania slowa, prosze sprobuj ponownie: ");
		WyczyscBufor();
	}
}

int WczytajLiczbe(const char* info, int min, int max) {
	int liczba;
	int pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("%s [%d, %d]: ", info, min, max);
		}
		else {
			printf("error - podana liczba wykracza poza zakres, prosze sprobuj ponownie: ");
		}
		while (scanf_s("%d", &liczba) != 1 || getchar() != '\n') {
			WyczyscBufor();
			printf("error - blad podczas wczytywania liczby, prosze sprobuj ponownie: ");
		}
	} while (liczba < min || liczba > max);
	return liczba;
}

void ZapamietajDate(char* data) {
	struct tm czasInfo;
	__time64_t czas;
	_time64(&czas); // zapisanie czasu jako 64 bitowy integer
	_localtime64_s(&czasInfo, &czas); // przekonwertowanie na czas lokalny
	strftime(data, DL_DATY, "%d.%m.%Y\t%H:%M:%S", &czasInfo); // przedstawienie w postaci reprezentacji ASCII
}

void ZapiszLog(FILE* log, const char* tresc) {
	char data[DL_DATY] = { '\0' };
	ZapamietajDate(data);
	fprintf(log, "%s\t%s", data, tresc);
}

void ZapiszLog(FILE* log, char* nick, const char* tresc) {
	char data[DL_DATY] = { '\0' };
	ZapamietajDate(data);
	fprintf(log, "%s\t[%s] %s", data, nick, tresc);
}

void Graj(FILE* log, FILE* zapisGracza, char* data, char* nick) {
	ZapamietajDate(data);
	fprintf(zapisGracza, "data: %s\n", data);
	
	int liczba = WczytajLiczbe("podaj liczbe par do wylosowania", 3, 20);
	int tak = 0, nie = 0;

	__time64_t poczatek, koniec;
	_time64(&poczatek);
	for (int i = 0; i < liczba; i++) {
		int dobry;
		char litera1 = rand() % ('z' - 'a' + 1) + 'a';
		char litera2 = rand() % ('z' - litera1 + 1) + litera1;
		printf("[%d / %d] podaj dowolny znak z przedzialu %c - %c: ", i + 1, liczba, litera1, litera2);
		char wpis = (char)_getch();
		if (wpis >= litera1 && wpis <= litera2) {
			dobry = 1;
			tak++;
		}
		else {
			dobry = 0;
			nie++;
		}
		printf("\n");
		fprintf(zapisGracza, "[%d / %d] wylosowany przedzial: %c - %c\twpis: %c\t%d\n", i + 1, liczba, litera1, litera2, wpis, dobry);
	}
	_time64(&koniec);

	double czas = _difftime64(koniec, poczatek);
	fprintf(zapisGracza, "czas gry [sek]: %.2lf\npoprawne wpisy: %d\nniepoprawne wpisy: %d\n\n", czas, tak, nie);
}

int main() {
	srand(time(NULL));

	FILE* log, *zapisGracza;
	if (fopen_s(&log, "log.txt", "a+") == 0 && log != NULL) {
		char data[DL_DATY] = { '\0' };
		char nick[DL_SLOWA] = { '\0' };
		char nazwa[DL_SLOWA + 8] = "gra-";
		ZapiszLog(log, "uruchomienie programu\n");

		WczytajSlowo("podaj nick", nick);
		strcat_s(nazwa, DL_SLOWA + 8, nick);
		strcat_s(nazwa, DL_SLOWA + 8, ".txt");
		ZapiszLog(log, "wczytanie nicku od uzytkownika\n");

		int gra = 1;
		while (gra) {
			ZapiszLog(log, nick, "rozpoczecie rozgrywki gracza\n");
			printf("\ninfo - rozpoczecie gry gracza %s\n", nick);

			if (_access(nazwa, 0) == 0) { // sprawdzamy czy plik istnieje i zapisujemy odpowiedni log
				ZapiszLog(log, nick, "znalezienie i otwarcie pliku gracza "); 
				fprintf(log, "%s\n", nazwa);
			}
			else {
				ZapiszLog(log, nick, "utworzenie i otwarcie pliku gracza ");
				fprintf(log, "%s\n", nazwa);
			}

			// uwaga: nie potrafie okreslic dlaczego dzialanie bledu powoduje przerwanie programu wyskakujacym oknem, a nie zaprogramowana wiadomoscia :(
			errno_t numerBledu = fopen_s(&zapisGracza, nazwa, "a+"); 
			if (numerBledu == 0 && zapisGracza != NULL) { // otwarcie fopen_s w trybie a+ tworzy lub nadpisuje plik
				Graj(log, zapisGracza, data, nick);
				ZapiszLog(log, nick, "zakonczenie rozgrywki, zapisanie logow do pliku\n");

				ZapiszLog(log, nick, "zamkniecie pliku gracza ");
				fprintf(log, "%s\n", nazwa);
				fclose(zapisGracza);
			}
			else {
				char trescBledu[DL_SCIEZKI] = { '\0' };
				ZapiszLog(log, "error - blad podczas otwarcia pliku ");
				strerror_s(trescBledu, DL_SCIEZKI, numerBledu);
				fprintf(log, "%s - %s\n", nazwa, trescBledu);
			}
			
			int decyduje = 1;
			while (decyduje) {
				printf("info:\taby zakonczyc gre wpisz 0\n\taby zagrac ponownie wpisz 1\n");
				int tmp = WczytajLiczbe("wybor", 0, 1);
				if (tmp == 0) {
					decyduje = 0;
					gra = 0;
					ZapiszLog(log, nick, "decyzja gracza o zakonczeniu rozgrywki\n");
				}
				else if (tmp == 1) {
					decyduje = 0;
					ZapiszLog(log, nick, "decyzja gracza o powtorzeniu rozgrywki\n");
				}
			}
		}

		ZapiszLog(log, "zamkniecie programu\n\n");
		printf("\ninfo - zakonczenie gry gracza %s\n", nick);
		fclose(log);
	}
}
#include <iostream>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define DLUGOSC_SLOWA 20
#define PRZESUNIECIE 2
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

// FUNKCJE POTRZEBNE DO ROZWIAZANIA ZADANIA PIERWSZEGO POZIOMU
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
		
		// jezeli wczytujemy piewrsze slowo LUB
		// jezeli wczytujemy slowo niepierwsze i NIE jest ono takie same jak poprzednie 
		// mechanizm ten unika przerobienia ostatniego slowa dwukrotnie, bo jezeli plik nie jest zakonczony
		// enterem to nic sie nie zmienia, lecz jezeli jest, to ostatnie slowo wystepuje dwa razy, dzieki temu nie rozpatrujemy powtorzenia
		if (liczbaSlow == 0 || memcmp(a, b, sizeof(a)) != 0) { 
			strcpy_s(b, a);
			
			char kopia[DLUGOSC_SLOWA];
			strcpy_s(kopia, a);
			//printf("slowo pobrane: %s\t", kopia);
			PrzekonwertujSlowo(kopia);
			//printf("slowo zmienione: %s\n", kopia);
			fprintf(out, "%s\n", kopia);

			liczbaSlow++;
		}
		else {
			break;
		}
		
	}
}




// FUNKCJE POTRZEBNE DO ROZWIAZANIA ZADANIA DRUGIEGO POZIOMU
/*
@ brief Funkcja zaszyfrowuje slowo kodem cezara, z danym przesunieciem
@ param *slowo - tablica zawierajaca slowo do zaszyfrowania
@ param n - przesuniecie
*/
void PrzekonwertujSlowoCezarem(char* slowo, int n) {
	// zamiana liter slowa na male
	int indeks = 0;
	while (slowo[indeks] != '\0') {
		if (isalpha(slowo[indeks]) && isupper(slowo[indeks])) {
			slowo[indeks] = (char)tolower(slowo[indeks]);
		}
		indeks++;
	}
	// zamiana liczby szyfrujacen na dodatnia
	while (n < 0) n += 'z' - 'a' + 1;
	// szyfrowanie cezarem
	indeks = 0;
	while (slowo[indeks] != '\0') {
		if (isalpha(slowo[indeks])) {
			slowo[indeks] = (slowo[indeks] - 'a' + n) % ('z' - 'a' + 1) + 'a';
			
		}
		indeks++;
	}
}

/*
@ brief Funkcja do przekonwertowania wszystkich slow w pliku szyfrem cezara.
@ param *in - wskaznik do otwartego pliku, gdzie sa slowa do zamiany
@ param *out - wskaznik do otwartego pliku, gdzie maja sie znalezc zmienione slowa
@ ret   liczbaSlow - zwraca liczbe zakodowanych slow
*/
int PrzekonwertujPlikCezarem(FILE* in, FILE* out) {
	int liczbaSlow = 0;
	char a[DLUGOSC_SLOWA] = { '\0' };
	char b[DLUGOSC_SLOWA] = { '\0' };
	while (!feof(in)) {
		fscanf_s(in, "%s", a, DLUGOSC_SLOWA);

		// jezeli wczytujemy piewrsze slowo LUB
		// jezeli wczytujemy slowo niepierwsze i NIE jest ono takie same jak poprzednie 
		// mechanizm ten unika przerobienia ostatniego slowa dwukrotnie, bo jezeli plik nie jest zakonczony
		// enterem to nic sie nie zmienia, lecz jezeli jest, to ostatnie slowo wystepuje dwa razy, dzieki temu nie rozpatrujemy powtorzenia
		if (liczbaSlow == 0 || memcmp(a, b, sizeof(a)) != 0) {
			strcpy_s(b, a);

			char kopia[DLUGOSC_SLOWA];
			strcpy_s(kopia, a);
			PrzekonwertujSlowoCezarem(kopia, PRZESUNIECIE);
			fprintf(out, "%s\n", kopia);

			liczbaSlow++;
		}
		else {
			break;
		}

	}
	printf("liczba slow w pliku wejsciowym, ktore zostaly zaszyfrowane: %d\n", liczbaSlow);
	return liczbaSlow;
}

/*
@ brief Funkcja do wypisania zaszyfrowanych slow z pliku a nastepnia odszyfrowania.
@ param *plik - wskaznik do pliku
@ param liczbaSlow - ilosc slow w pliku
*/
void WypiszZakodowaneSlowa(FILE* plik, int liczbaSlow) {
	for (int i = 0; i < liczbaSlow; i++) {
		char slowo[DLUGOSC_SLOWA] = {'\0'};
		char rozkodowane[DLUGOSC_SLOWA] = {'\0'};
		fscanf_s(plik, "%s", slowo, DLUGOSC_SLOWA);
		strcpy_s(rozkodowane, slowo);
		PrzekonwertujSlowoCezarem(rozkodowane, -PRZESUNIECIE);
		printf("slowo zaszyfrowane: %s\tslowo odszyfrowane: %s\n", slowo, rozkodowane);
	}
}

int main() {
	Info();	
	char nazwaIn[DLUGOSC_SLOWA];
	char nazwaOut[DLUGOSC_SLOWA];

	// rozwiazanie zadanie pierwszego poziomu
	FILE *in, *out;
	printf("Dolaczony plik z danymi to in.txt [moze, ale nie musi byc zakonczony ENTEREM]\n");
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
	// rozwiazanie zadanie drugiego poziomu
	int liczbaSlow = 0;
	FILE* inCezar, *outCezar, *plikZakodowane;
	printf("Dolaczony plik z danymi to inCezar.txt [moze, ale nie musi byc zakonczony ENTEREM]\n");
	WczytajNapis("podaj nazwe pliku wejsciowego", nazwaIn);
	WczytajNapis("podaj nazwe pliku wyjsciowego", nazwaOut);

	if (fopen_s(&inCezar, nazwaIn, "r") == 0 && inCezar != NULL && fopen_s(&outCezar, nazwaOut, "a+") == 0 && outCezar != NULL) {
		printf("poprawnie otworzono pliki %s oraz %s\n\n", nazwaIn, nazwaOut);

		liczbaSlow = PrzekonwertujPlikCezarem(inCezar, outCezar);

		fclose(inCezar);
		fclose(outCezar);
	}
	else {
		ERROR_PLIK
	}

	printf("oto zaszyfrowane slowa, ktore sa obecnie w pliku %s oraz ich odszyfrowane wersje:\n", nazwaOut);
	if (fopen_s(&plikZakodowane, nazwaOut, "r") == 0 && plikZakodowane != NULL) {
		WypiszZakodowaneSlowa(plikZakodowane, liczbaSlow);
	}

	// Program nie posiada funkcji odszyfrowauj¹cej, bo odszyfrowanie polega na wywo³aniu funkcji z przeciwnym argumentem 
	// tzn. je¿eli szyfrowanie odbywa³o siê kluczem 2, to odszyfrowanie nast¹pi po wywo³aniu funkcji szyfrujacej z kluczem -2.
	return 0;
}
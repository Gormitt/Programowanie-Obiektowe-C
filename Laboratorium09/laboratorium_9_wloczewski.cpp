#include <iostream>
#include <math.h>
#include <conio.h>

#define ILOSC_FIGUR 2

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t24 kwi 2020\n");
	printf("about: \tWejsciowka nr. 9\n");
	printf("\tProgram wczyta od uzytkownika wspolrzedne dwoch wierzcholkow, jednego ramienia trapezu rownoramiennego.\n\n");
}

void WyczyscBufor(void) {
	while (getchar() != '\n') {}
}

void WczytajLiczbe(const char* info, double* wpis, double min, double max) {
	int pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("%s: ", info);
		}
		else {
			printf("error - podana liczba jest spoza zakresu, prosze sprobuj ponownie: ");
		}
		while (scanf_s("%lf", wpis) != 1 || getchar() != '\n') {
			WyczyscBufor();
			printf("error - blad podczas wczytywania liczby, prosze sprobuj ponownie: ");
		}
	} while (*wpis < min || *wpis > max);
}

void WczytajLiczbeCalkowita(const char* info, int* wpis, int min, int max) {
	int pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("%s: ", info);
		}
		else {
			printf("error - podana liczba jest spoza zakresu, prosze sprobuj ponownie: ");
		}
		while (scanf_s("%d", wpis) != 1 || getchar() != '\n') {
			WyczyscBufor();
			printf("error - blad podczas wczytywania liczby, prosze sprobuj ponownie: ");
		}
	} while (*wpis < min || *wpis > max);
}

void WczytajKierunek(const char* info, int* k) {
	int pierwsza = 1;
	do {
		if (pierwsza) {
			pierwsza = 0;
			printf("%s (-1 [lewo] / 1 [prawo]): ", info);
		}
		else {
			printf("error - kierunek musi byc rowny -1 lub 1, prosze sprobuj ponownie: ");
		}
		while (scanf_s("%d", k) != 1 || getchar() != '\n') {
			WyczyscBufor();
			printf("error - blad podczas wczytywania liczby, prosze sprobuj ponownie: ");
		}
	} while (*k != -1 && *k != 1);
}

class Trapez {
public:
	void KonfigurujFigure(double xA, double yA, double dlGorna, double xB, double yB, double k) {
		if (dlGorna <= 0 || yA == yB || (((xA < xB && k == 1) || (xA > xB&& k == -1)) && dlGorna < abs(xA - xB) * 2 + 1.0)) {
			printf("error - podanej figury nie mozna narysowac, zmieniam parametry na predefiniowane bezpieczne\n");
			xA = 0; yA = 1;
			xB = 0; yB = 0;
			dlGorna = 1;
			k = 1;
		}

		this->xA = xA; this->yA = yA;
		this->xB = xB; this->yB = yB;
		this->dlGorna = dlGorna;
		this->kierunek = k;
	}

	void WypiszWspolrzedne() {
		double dlDolna = 0, tmp1 = 0, tmp2 = 0;
		if (this->kierunek == -1) {
			dlDolna = (this->xA > this->xB) ? (this->dlGorna - 2 * abs(this->xA - this->xB)) : (this->dlGorna + 2 * abs(this->xA - this->xB));
			tmp1 = this->xA - this->dlGorna;
			tmp2 = this->xB - dlDolna;
		}
		else if (this->kierunek == 1) {
			dlDolna = (this->xA < this->xB) ? (this->dlGorna - 2 * abs(this->xA - this->xB)) : (this->dlGorna + 2 * abs(this->xA - this->xB));
			tmp1 = this->xA + this->dlGorna;
			tmp2 = this->xB + dlDolna;
		}
		printf("dane o trapezie:\n");
		printf("wsp. gornej podstawy: (%.2lf, %.2lf) oraz (%.2lf, %.2lf)\tdl. gornej podstawy: %.2lf\n", this->xA, this->yA, tmp1, this->yA, this->dlGorna);
		printf("wsp. dolnej podstawy: (%.2lf, %.2lf) oraz (%.2lf, %.2lf)\tdl. dolnej podstawy: %.2lf\n", this->xB, this->yB, tmp2, this->yB, dlDolna);
	}

	void OdbicieSymetryczne(double x) {
		double odlegloscA = abs(this->xA - x);
		double odlegloscB = abs(this->xB - x);

		this->xA = this->xA < x ? x + odlegloscA : x - odlegloscA;
		this->xB = this->xB < x ? x + odlegloscB : x - odlegloscB;
		this->kierunek = this->kierunek == 1 ? -1 : 1;
	}

	double Pole(Trapez* t) {
		double dlDolna = 0;
		if ((*t).kierunek == -1) {
			dlDolna = ((*t).xA > (*t).xB) ? ((*t).dlGorna - 2 * abs((*t).xA - (*t).xB)) : ((*t).dlGorna + 2 * abs((*t).xA - (*t).xB));
		}
		else if ((*t).kierunek == 1) {
			dlDolna = ((*t).xA < (*t).xB) ? ((*t).dlGorna - 2 * abs((*t).xA - (*t).xB)) : ((*t).dlGorna + 2 * abs((*t).xA - (*t).xB));
		}
		return 0.5 * ((*t).dlGorna + dlDolna) * (abs((*t).yA - (*t).yB));
	}

	double Dodaj(Trapez* t) {
		return Pole(this) + Pole(t);
	}
private:
	int kierunek;
	double xA, yA, dlGorna; // wsp. x i y lewego wierzcholka podstawy a oraz jej dlugosc
	double xB, yB;
};

class Prostokat {
public:
	void KonfigurujFigure(double xA, double yA, double dlGorna, double xB, double yB, double k) {
		if (dlGorna <= 0 || yA == yB || xA != xB) {
			printf("error - podanej figury nie mozna narysowac, zmieniam parametry na predefiniowane bezpieczne\n");
			xA = 0; yA = 1;
			xB = 0; yB = 0;
			dlGorna = 1;
			k = 1;
		}
		if (yA < yB) {
			printf("error - wierzcholki podano w niewlasciwej kolejnosci, zamieniam je miejscami\n");
			double tmp = yA;
			yA = yB;
			yB = tmp;
		}

		this->xA = xA; this->yA = yA;
		this->xB = xB; this->yB = yB;
		this->dlGorna = dlGorna;
		this->kierunek = k;
	}

	void WypiszWspolrzedne() {
		double tmp1 = 0, tmp2 = 0;
		double wys = abs(this->yA - this->yB);
		if (kierunek == -1) {
			tmp1 = this->xA - this->dlGorna;
			tmp2 = this->xB - this->dlGorna;
		}
		else if (kierunek == 1) {
			tmp1 = this->xA + this->dlGorna;
			tmp2 = this->xB + this->dlGorna;
		}
		printf("dane o prostokacie:\n");
		printf("wsp. gornej podstawy: (%.2lf, %.2lf) oraz (%.2lf, %.2lf)\twymiary: %lf x %lf\n", this->xA, this->yA, tmp1, this->yA, this->dlGorna, wys);
		printf("wsp. dolnej podstawy: (%.2lf, %.2lf) oraz (%.2lf, %.2lf)\twymiary: %lf x %lf\n", this->xB, this->yB, tmp2, this->yB, this->dlGorna, wys);
	}

	void OdbicieSymetryczne(double x) {
		double odlegloscA = abs(this->xA - x);
		double odlegloscB = abs(this->xB - x);

		this->xA = this->xA < x ? x + odlegloscA : x - odlegloscA;
		this->xB = this->xB < x ? x + odlegloscB : x - odlegloscB;
		this->kierunek = this->kierunek == 1 ? -1 : 1;
	}

	void Skaluj(double x) {
		if (x <= 0) {
			printf("error - nie moge przeskalowa prostokata wg. skali ujemnej, pozostawiam go w niezmienionym stanie\n");
			return;
		}

		double wys = abs(this->yA - this->yB) * x;
		this->yB = this->yA - wys;
		this->dlGorna *= x;
	}

	double Pole(Prostokat* p) {
		return (*p).dlGorna * abs((*p).yA - (*p).yB);
	}

	double Dodaj(Prostokat* p) {
		return Pole(this) + Pole(p);
	}
private:
	int kierunek;
	double xA, yA, dlGorna;
	double xB, yB;
};

int main() {
	Info();

	Trapez t[ILOSC_FIGUR];
	Prostokat p[ILOSC_FIGUR];

	int k = 1;
	double xa = 0, ya = 0;
	double xb = 0, yb = 0;
	double dlGora = 0;
	double x = 0;

	for (int i = 0; i < ILOSC_FIGUR; i++) {
		printf("\nwczytywanie danych do trapezu nr. %d z %d\n", i + 1, ILOSC_FIGUR);
		WczytajLiczbe("podaj wsp. x gornego wierzcholka", &xa, -100, 100);
		WczytajLiczbe("podaj wsp. y gornego wierzcholka", &ya, -100, 100);
		WczytajLiczbe("podaj wsp. x dolnego wierzcholka", &xb, -100, 100);
		WczytajLiczbe("podaj wsp. y dolnego wierzcholka", &yb, -100, 100);
		WczytajLiczbe("podaj dl. gornej podstawy", &dlGora, -20, 20);
		WczytajKierunek("podaj kierunek rysowania", &k);

		t[i].KonfigurujFigure(xa, ya, dlGora, xb, yb, k);

		printf("\nwczytywanie danych do prostokata nr. %d z %d\n", i + 1, ILOSC_FIGUR);
		WczytajLiczbe("podaj wsp. x gornego wierzcholka", &xa, -100, 100);
		WczytajLiczbe("podaj wsp. y gornego wierzcholka", &ya, -100, 100);
		WczytajLiczbe("podaj wsp. x dolnego wierzcholka", &xb, -100, 100);
		WczytajLiczbe("podaj wsp. y dolnego wierzcholka", &yb, -100, 100);
		WczytajLiczbe("podaj dl. gornej podstawy", &dlGora, -20, 20);
		WczytajKierunek("podaj kierunek rysowania", &k);

		p[i].KonfigurujFigure(xa, ya, dlGora, xb, yb, k);
	}

	while (true) {
		printf("\njaka figure chcesz edytowac ('p' - prostokat, 't' - trapez)\naby wyjsc napisz 'q'\n");
		char wpis;
		int indeks, opcja;
		do {
			printf("wybor: ");
			wpis = (char)_getch();
		} while (wpis != 'p' && wpis != 't' && wpis != 'q');
		
		if (wpis == 'q') break;

		printf("podaj indeks figury (od %d do %d)", 0, ILOSC_FIGUR - 1);
		WczytajLiczbeCalkowita("", &indeks, 0, ILOSC_FIGUR - 1);
		WczytajLiczbeCalkowita("'0' - zmiana wartosci, '1' - odbicie, '2' skalowanie (tylko prostokat) - wybor", &opcja, 0, 2);

		if (opcja == 0) {
			if (wpis == 't') printf("\nwczytywanie danych do trapezu nr. %d z %d\n", indeks + 1, ILOSC_FIGUR);
			else printf("\nwczytywanie danych do prostokata nr. %d z %d\n", indeks + 1, ILOSC_FIGUR);

			WczytajLiczbe("podaj wsp. x gornego wierzcholka", &xa, -100, 100);
			WczytajLiczbe("podaj wsp. y gornego wierzcholka", &ya, -100, 100);
			WczytajLiczbe("podaj wsp. x dolnego wierzcholka", &xb, -100, 100);
			WczytajLiczbe("podaj wsp. y dolnego wierzcholka", &yb, -100, 100);
			WczytajLiczbe("podaj dl. gornej podstawy", &dlGora, -20, 20);
			WczytajKierunek("podaj kierunek rysowania", &k);

			if (wpis == 't') {
				t[indeks].KonfigurujFigure(xa, ya, dlGora, xb, yb, k);
				t[indeks].WypiszWspolrzedne();
			}
			else {
				p[indeks].KonfigurujFigure(xa, ya, dlGora, xb, yb, k);
				p[indeks].WypiszWspolrzedne();
			}
		}
		else if (opcja == 1) {
			WczytajLiczbe("podaj wsp. x osi symetrii", &x, -20, 20);

			if (wpis == 't') {
				t[indeks].OdbicieSymetryczne(x);
				t[indeks].WypiszWspolrzedne();
			}
			else {
				p[indeks].OdbicieSymetryczne(x);
				p[indeks].WypiszWspolrzedne();
			}
		}
		else if (opcja == 2) {
			if (wpis == 't') {
				printf("error - nie ma skalowania trapezow\n");
				break;
			}
			WczytajLiczbe("podaj wielkosc skali, wg. ktorej odbedzie sie operacja (pivot to pierwszy z podanych punktow)", &x, -20, 20);
			p[indeks].Skaluj(x);
			p[indeks].WypiszWspolrzedne();
		}
	}
	
	// zadanie II poziomu
	while (true) {
		char wpis;
		int a = 0, b = 0;
		do {
			printf("wybierz typ figury, jakiej pola zostana do siebie dodane ('t' - trapezy, 'p' - prostokaty)\n");
			printf("aby wyjsc wcisnij 'q'\nwybor: ");
			wpis = (char)_getch();
		} while (wpis != 'p' && wpis != 't' && wpis != 'q');

		if (wpis == 'q') break;

		WczytajLiczbeCalkowita("wczytaj indeks pierwszej figury", &a, 0, ILOSC_FIGUR - 1);
		WczytajLiczbeCalkowita("wczytaj indeks drugiej figury (moze byc ta sama)", &b, 0, ILOSC_FIGUR - 1);
	
		double przed = 0, po = 0;
		if (wpis == 't') {
			przed = t[a].Pole(&t[a]);
			po = t[a].Dodaj(&t[b]);
			printf("pole pierwszej figury przed dodaniem: %lf\n", przed);
			printf("pole pierwszej figury po dodaniu: %lf\n\n", po);
		}
		else {
			przed = p[a].Pole(&p[a]);
			po = p[a].Dodaj(&p[b]);
			printf("pole pierwszej figury przed dodaniem: %lf\n", przed);
			printf("pole pierwszej figury po dodaniu: %lf\n\n", po);
		}
	}

	return 0;
}
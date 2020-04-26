#include <iostream>
#include <math.h>

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t24 kwi 2020\n");
	printf("about: \tWejsciowka nr. 9\n");
	printf("\tProgram wczyta od uzytkownika wspolrzedne dwoch wierzcholkow, jednego ramienia trapezu rownoramiennego.\n");
	printf("\tNastepnie poprosi o dlugosc gornej podstawy i kierunek rysowania (1 oznacza prawo, -1 oznacza lewo).\n");
	printf("\tKolejnym krokiem bedzie wygenerowanie wszystkich wierzcholkow trapezu, tak aby byl polozony rownolegle do OX.\n");
	printf("\tNa koniec, zapyta o podanie wsp. x pionowej osi, wg. ktorej figura \nzostanie odbita (dwukrotnie, aby sprawdzic czy wroci na stare miejsce)\n\n");
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
		if (yA < yB) {
			printf("error - wierzcholki podano w niewlasciwej kolejnosci, zamieniam je miejscami\n");
			double tmp = yA;
			yA = yB;
			yB = tmp;

			tmp = xA;
			xA = xB;
			xB = tmp;
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
		printf("\ndane o figurze:\n");
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
private:
	int kierunek;
	double xA, yA, dlGorna; // wsp. x i y lewego wierzcholka podstawy a oraz jej dlugosc
	double xB, yB;
};

int main() {
	Info();

	Trapez t;
	int k = 1;
	double xa = 0, ya = 0;
	double xb = 0, yb = 0;
	double dlGora = 0;

	WczytajLiczbe("podaj wsp. x gornego wierzcholka", &xa, -100, 100);
	WczytajLiczbe("podaj wsp. y gornego wierzcholka", &ya, -100, 100);
	WczytajLiczbe("podaj wsp. x dolnego wierzcholka", &xb, -100, 100);
	WczytajLiczbe("podaj wsp. y dolnego wierzcholka", &yb, -100, 100);
	WczytajLiczbe("podaj dl. gornej podstawy", &dlGora, -20, 20);
	WczytajKierunek("podaj kierunek rysowania", &k);

	t.KonfigurujFigure(xa, ya, dlGora, xb, yb, k);
	t.WypiszWspolrzedne();

	double x = 0;
	WczytajLiczbe("podaj wsp. x osi pionowej, wg. ktorej zostanie odbita figura", &x, -80, 80);

	t.OdbicieSymetryczne(x);
	t.WypiszWspolrzedne();
	t.OdbicieSymetryczne(x);
	t.WypiszWspolrzedne();

	return 0;
}
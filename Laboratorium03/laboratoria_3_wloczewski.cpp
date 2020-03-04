#include <iostream>
#include <math.h>

#define LICZBA_TROJKATOW 2

struct WynikiAnalizy {
	char czyIstniejeTrojkat;
	int numerNajmniejszej;
	double poleNajmniejszej;
};

WynikiAnalizy AnalizaZestawienia(double (*trojkaty)[3], int n) {
	char czyDaSie = 'n';
	int numerNajmniejszej = -1;
	float poleNajmniejszej = -1;
	for (int i = 0; i < n; i++) {
		char tmp = 't';
		if (trojkaty[i][0] + trojkaty[i][1] <= trojkaty[i][2]) tmp = 'n';
		else if (trojkaty[i][0] + trojkaty[i][2] <= trojkaty[i][1]) tmp = 'n';
		else if (trojkaty[i][1] + trojkaty[i][2] <= trojkaty[i][0]) tmp = 'n';

		if (tmp == 't') {
			czyDaSie = 't';
			double polowaObw = (trojkaty[i][0] + trojkaty[i][1] + trojkaty[i][2]) * 0.5;
			double pole = sqrt(polowaObw * (polowaObw - trojkaty[i][0]) * (polowaObw - trojkaty[i][1]) * (polowaObw - trojkaty[i][2]));
			if (numerNajmniejszej == -1 || pole < poleNajmniejszej) {
				poleNajmniejszej = pole;
				numerNajmniejszej = i;
			}
		}
	}
	return WynikiAnalizy{ czyDaSie, numerNajmniejszej, poleNajmniejszej };
}

int main() {
	struct WynikiAnalizy w1;
	double trojkaty[LICZBA_TROJKATOW][3] { {3.0, 4.0, 5.0}, {3.0, 4.0, 8.0} };
	w1 = AnalizaZestawienia(trojkaty, LICZBA_TROJKATOW);

	printf("czy istnieje chociaz jeden trojkat: %c\nnumer najmniejszego trojkata: %d\npole: %lf\n\n", w1.czyIstniejeTrojkat, w1.numerNajmniejszej, w1.poleNajmniejszej);
	return 0;
}


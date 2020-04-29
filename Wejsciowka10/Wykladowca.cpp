#include "Stale.h"
#include "Wykladowca.h"
#include <iostream>

using namespace std;

Wykladowca::Wykladowca() {
	Wykladowca::baza = NULL;
}

Wykladowca::Wykladowca(const char* nazwa) {
	FILE* in;
	if (fopen_s(&in, nazwa, "r") == 0 && in != NULL) {
		int liczba = 0;
		char mail[DL_TABLICY] = { '\0' };
		while (!feof(in)) {
			fscanf_s(in, "%s", mail, DL_TABLICY);
			if (strlen(mail) > 0) {
				liczba++;
			}
		}
		rewind(in);

		BazaEmail b(liczba);
		for (int i = 0; i < liczba; i++) {
			fscanf_s(in, "%s", mail, DL_TABLICY);
			b.Setemail(mail, i);
		}
		
		Wykladowca::baza = &b;
	}
	else {
		printf("error - nie udalo sie otworzyc pliku\n");
		Wykladowca::baza = NULL;
	}
}

Wykladowca::Wykladowca(Wykladowca& w) {
	Wykladowca::baza = NULL;
}

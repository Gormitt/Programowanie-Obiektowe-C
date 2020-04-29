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
			if (strlen(mail) > 0) liczba++;
		}
		rewind(in);

		BazaEmail* b = new BazaEmail(liczba);
		for (int i = 0; i < liczba; i++) {
			fscanf_s(in, "%s", mail, DL_TABLICY);
			(*b).SetEmail(mail, i);
		}
		Wykladowca::baza = b;
	}
	else {
		printf("error - nie udalo sie otworzyc pliku\n");
		Wykladowca::baza = NULL;
	}
}

Wykladowca::Wykladowca(Wykladowca& w) {
	Wykladowca::baza = NULL;
}

Wykladowca::~Wykladowca() {
	for (int i = 0; i < Wykladowca::baza->GetIle(); i++) {
		delete Wykladowca::baza->GetEmail(i); // usuwanie przydzialu pamieci na kazdego maila w bazie
	}
	delete Wykladowca::baza->GetEmaile(); // usuwanie przydzialu na wskazniki do kazdego maila w bazie
	delete Wykladowca::baza; // usuwanie przydzialu pamieci na element listy dynamicznej
}
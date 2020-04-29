#include "Stale.h"
#include "BazaEmail.h"
#include <iostream>

BazaEmail::BazaEmail(int x) {
	BazaEmail::nast = NULL;
	BazaEmail::ile = x;
	BazaEmail::email = (char**)calloc(sizeof(char*), x);
	if (BazaEmail::email != NULL) {
		for (int i = 0; i < x; i++) {
			BazaEmail::email[i] = (char*)calloc(sizeof(char), DL_TABLICY);
		}
	}
}

BazaEmail::BazaEmail(BazaEmail& mk) {
	BazaEmail::nast = NULL;
	BazaEmail::ile = mk.ile;
	BazaEmail::email = (char**)calloc(sizeof(char*), mk.ile);

	if (BazaEmail::email != NULL) {
		for (int i = 0; i < ile; i++) {
			BazaEmail::email[i] = (char*)calloc(sizeof(char), DL_TABLICY);
			if (BazaEmail::email[i] != NULL) {
				strcpy_s(BazaEmail::email[i], DL_TABLICY, mk.email[i]);
			}
		}
	}
}

void BazaEmail::Setemail(char* adres, int idx) {
	strcpy_s(BazaEmail::email[idx], DL_TABLICY, adres);
}

char* BazaEmail::Getemail(int idx) {
	return BazaEmail::email[idx];
}

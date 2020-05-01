#include "Stale.h"
#include "BazaEmail.h"
#include <iostream>

BazaEmail::BazaEmail(int x) {
	BazaEmail::nast = NULL;
	BazaEmail::ile = x;
	BazaEmail::email = new char* [x];
	if (BazaEmail::email != NULL) {
		for (int i = 0; i < x; i++) {
			BazaEmail::email[i] = new char[DL_TABLICY];
		}
	}
}

BazaEmail::BazaEmail(BazaEmail& b) {
	BazaEmail::nast = NULL;
	BazaEmail::ile = b.ile;
	BazaEmail::email = new char* [b.ile];

	if (BazaEmail::email != NULL) {
		for (int i = 0; i < ile; i++) {
			email[i] = new char[DL_TABLICY];
			if (BazaEmail::email[i] != NULL) {
				strcpy_s(BazaEmail::email[i], DL_TABLICY, b.GetEmail(i));
			}
		}
	}
}

void BazaEmail::SetEmail(char* adres, int idx) {
	strcpy_s(BazaEmail::email[idx], DL_TABLICY, adres);
}

void BazaEmail::SetNast(BazaEmail* element) {
	BazaEmail::nast = element;
}

char** BazaEmail::GetEmaile(void) {
	return BazaEmail::email;
}

char* BazaEmail::GetEmail(int idx) {
	return BazaEmail::email[idx];
}

int BazaEmail::GetIle(void) {
	return BazaEmail::ile;
}

BazaEmail* BazaEmail::GetNast(void) {
	return BazaEmail::nast;
}

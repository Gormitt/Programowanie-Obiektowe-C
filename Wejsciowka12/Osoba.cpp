#include <iostream>
#include "Osoba.h"

Osoba::Osoba() :
	nst(NULL),
	zdefiniowana(0),
	stanowisko(0) {
	char tmp[DL] = "";
	strcpy_s(this->imie, DL, tmp);
	strcpy_s(this->nazwisko, DL, tmp);
	strcpy_s(this->mail, DL, tmp);
}

Osoba::Osoba(const char* imie, const char* nazwisko, const char* mail, int stanowisko) :
	nst(NULL),
	zdefiniowana(1),
	stanowisko(stanowisko) {
	strcpy_s(this->imie, DL, imie);
	strcpy_s(this->nazwisko, DL, nazwisko);
	strcpy_s(this->mail, DL, mail);
}

Osoba::Osoba(Osoba& o) :
	nst(NULL),
	zdefiniowana(1),
	stanowisko(o.stanowisko) {
	strcpy_s(this->imie, DL, o.imie);
	strcpy_s(this->nazwisko, DL, o.nazwisko);
	strcpy_s(this->mail, DL, o.mail);
}

void Osoba::Wypisz() {
	if (this->zdefiniowana) {
		printf("imie:\t\t%s\n", this->imie);
		printf("nazwisko:\t%s\n", this->nazwisko);
		printf("mail:\t\t%s\n", this->mail);
		if (this->stanowisko == 1) printf("stanowisko:\twykladowca\n\n");
		else printf("stanowisko:\tstudent\n\n");
	}
	else {
		printf("Osoba nie zostala zdefiniowana\n\n");
	}
}

void Osoba::WypiszDalsze() {
	Osoba* tmp = this;
	while (tmp) {
		tmp->Wypisz();
		tmp = tmp->GetNst();
	}
}

// settery
void Osoba::SetNst(Osoba* o) { this->nst = o; }
void Osoba::SetImie(const char* i) { strcpy_s(this->imie, DL, i); }
void Osoba::SetNazwisko(const char* n) { strcpy_s(this->nazwisko, DL, n); }
void Osoba::SetMail(const char* m) { strcpy_s(this->mail, DL, m); }
void Osoba::SetStanowisko(int s) { this->stanowisko = s; }
// gettery
Osoba* Osoba::GetNst() { return this->nst; }
char* Osoba::GetImie() { return this->imie; }
char* Osoba::GetNazwisko() { return this->nazwisko; }
char* Osoba::GetMail() { return this->mail; }
int Osoba::GetStanowisko() { return this->stanowisko; }
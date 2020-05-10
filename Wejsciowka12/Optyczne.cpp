#include <iostream>
#include "Optyczne.h"

Optyczne::Optyczne() :
	nst(NULL),
	zdefiniowane(0),
	masa(0),
	srednica(0),
	ogniskowa(0),
	stabilizacja(0) {
}

Optyczne::Optyczne(double masa, double srednica, double ogniskowa, int stabilizacja) :
	nst(NULL),
	zdefiniowane(1),
	masa(masa),
	srednica(srednica),
	ogniskowa(ogniskowa),
	stabilizacja(stabilizacja) {
}

Optyczne::Optyczne(Optyczne& o) :
	nst(NULL),
	zdefiniowane(1),
	masa(o.masa),
	srednica(o.srednica),
	ogniskowa(o.ogniskowa),
	stabilizacja(o.stabilizacja) {
}

Optyczne::~Optyczne() {
	delete this->nst;
}

void Optyczne::Wypisz() {
	if (this->zdefiniowane) {
		printf("masa:\t\t%lf\n", this->masa);
		printf("srednica:\t%lf\n", this->srednica);
		printf("ogniskowa:\t%lf\n", this->ogniskowa);
		if (this->stabilizacja) printf("stabilizacja:\tTAK\n\n");
		else printf("stabilizacja:\tNIE\n\n");
	}
	else {
		printf("urzadzenie optycznie nie zostalo zdefiniowane\n\n");
	}
}

void Optyczne::WypiszDalsze() {
	Optyczne* tmp = this;
	while (tmp) {
		tmp->Wypisz();
		tmp = tmp->GetNst();
	}
}

// settery
void Optyczne::SetNst(Optyczne* o) { this->nst = o; }
void Optyczne::SetMasa(double m) { this->masa = m; }
void Optyczne::SetSrednica(double s) { this->srednica = s; }
void Optyczne::SetOgniskowa(double o) { this->ogniskowa = o; }
void Optyczne::SetStabilizacja(int s) { this->stabilizacja = s; }

// gettery
Optyczne* Optyczne::GetNst() { return this->nst; }
double Optyczne::GetMasa() { return this->masa; }
double Optyczne::GetSrednica() { return this->srednica; }
double Optyczne::GetOgniskowa() { return this->ogniskowa; }
int	Optyczne::GetStabilizacja() { return this->stabilizacja; }
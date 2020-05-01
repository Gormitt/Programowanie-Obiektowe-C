#pragma once
#include "BazaEmail.h"

class Wykladowca {
private:
	BazaEmail*	baza;
	BazaEmail*	ostatni;
	char		nazwisko[DL_SLOWA];
public:
	Wykladowca(char*);
	Wykladowca(char*, char*);
	Wykladowca(char*, Wykladowca&);
	~Wykladowca();
	void	DodajElement(const char*);
	void	WypiszListe(void);
};
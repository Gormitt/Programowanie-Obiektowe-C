#pragma once
#include "BazaEmail.h"

class Wykladowca {
private:
	BazaEmail* baza;
public:
	Wykladowca();
	Wykladowca(const char*);
	Wykladowca(Wykladowca&);
	~Wykladowca();
};
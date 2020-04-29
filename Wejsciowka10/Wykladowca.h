#pragma once
#include "BazaEmail.h"

class Wykladowca {
	BazaEmail* baza;
public:
	Wykladowca();
	Wykladowca(const char*);
	Wykladowca(Wykladowca&);
};
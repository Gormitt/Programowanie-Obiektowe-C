#pragma once

#include "Trapez.h"
#include "Prostokat.h"

class Kolekcja {
private:
	Trapez*		glowaT, *ogonT;
	Prostokat*	glowaP, *ogonP;
public:
	Kolekcja();
	void	DodajTrapez(Trapez* t);
	void	DodajProstokat(Prostokat* p);
	void	WypiszTrapezy();
	void	WypiszProstokaty();
	void	Symetria(double x);
	void	Skala(double x);
};
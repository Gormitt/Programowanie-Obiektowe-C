#pragma once
#include "Baza.h"

class Wykladowca {
private:
	char	nazwisko[DL_SLOWA];
	Baza*	glowa;
	Baza*	ogon;
public:
	Wykladowca(const char* nazwisko);
	Wykladowca(const char* nazwisko, char* plik);
	Wykladowca(const char* nazwisko, Wykladowca& w);
	~Wykladowca();
	void	Wypisz();
	void	DodajGrupe(char* plik);
	void	SzukajId(int id);
};


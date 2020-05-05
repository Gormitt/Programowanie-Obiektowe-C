#pragma once
#define DL_SLOWA 50

class Baza {
private:
	Baza*	nastepna;
	int		wielkosc;
	char**	maile;
public:
	Baza(int ileEmaili);
	Baza(Baza& baza);
	void	SetMail(int numer, char* adres);
	char*	GetMail(int numer);
};


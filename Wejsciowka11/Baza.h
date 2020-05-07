#pragma once
#define DL_SLOWA 50
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

class Baza {
private:
	Baza*	nastepna;
	int		id;
	int		wielkosc;
	char**	maile;
public:
	Baza(int id, int ileEmaili);
	Baza(int id, Baza& baza);
	Baza(int id, char* plik);
	~Baza();
	void	WypiszMaile();
	Baza*	SzukajId(int id);
	void	SetMail(int numer, char* adres);
	void	SetNastepna(Baza* b);
	char*	GetMail(int numer);
	int		GetId();
	Baza*	GetNastepny();
};


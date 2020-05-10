#pragma once

#define DL 50

class Osoba {
private:
	int		zdefiniowana;
protected:
	Osoba*	nst;
	char	imie[DL];
	char	nazwisko[DL];
	char	mail[DL];
	int		stanowisko;
public:
	Osoba();
	Osoba(const char* imie, const char* nazwisko, const char* mail, int rola);
	Osoba(Osoba&);
	void	Wypisz();
	void	WypiszDalsze();
	// settery
	void	SetNst(Osoba*);
	void	SetImie(const char*);
	void	SetNazwisko(const char*);
	void	SetMail(const char*);
	void	SetStanowisko(int);
	// gettery
	Osoba*	GetNst();
	char*	GetImie();
	char*	GetNazwisko();
	char*	GetMail();
	int		GetStanowisko();
};


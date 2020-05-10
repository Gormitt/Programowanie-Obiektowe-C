#pragma once

#define DL 30

class Samochod {
private:
	int			zdefiniowany;
protected:
	Samochod*	nst;
	int			rocznik;
	int			przebieg;
	char		marka[DL];
	char		model[DL];
public:
	Samochod();
	Samochod(int rocznik, int przebieg, const char* marka, const char* model);
	Samochod(Samochod& samochod);
	~Samochod();
	void	Wypisz();
	void	WypiszDalsze();
	// settery
	void	SetNst(Samochod*);
	void	SetRocznik(int);
	void	SetPrzebieg(int);
	void	SetMarka(char*);
	void	SetModel(char*);
	// gettery
	Samochod* GetNst();
	int		GetRocznik();
	int		GetPrzebieg();
	char*	GetMarka();
	char*	GetModel();
};


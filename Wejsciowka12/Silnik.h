#pragma once

class Silnik {
private:
	int		zdefiniowany;
protected:
	Silnik* nst;
	int		moc;
	double	pojemnosc;
public:
	Silnik();
	Silnik(int moc, double pojemnosc);
	Silnik(Silnik&);
	~Silnik();
	void	Wypisz();
	void	WypiszDalsze();
	// settery
	void	SetNst(Silnik* s);
	void	SetMoc(int);
	void	SetPojemnosc(double);
	// gettery
	Silnik* GetNst();
	int		GetMoc();
	double	GetPojemnosc();
};


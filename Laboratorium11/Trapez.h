#pragma once
#include "Prostokat.h"

class Trapez {
private:
	static int		liczbaWszystkich;
	static double	poleWszystkich;
	Trapez* nastepny;
	double	ax, ay;
	double	bx, by;
	double	gorna;
	int		kierunek;
	void	UstawFigure(double ax, double ay, double bx, double by, double gorna, int kierunek);
public:
	Trapez();
	Trapez(double ax, double ay, double bx, double by, double gorna, int kierunek);
	Trapez(Trapez& t);
	Trapez(Prostokat& p);
	~Trapez();
	void	Wypisz();
	void	Symetria(double x);
	void	Skaluj(double x);
	void	ZwiekszPole(Trapez& t);
	Trapez* SzukajDrugiego(Trapez* t);
	void	SetNastepny(Trapez* t);
	Trapez* GetNastepny();
	double	GetPole();
	static int GetLiczbaWszystkich();
	static double GetPoleWszystkich();
};


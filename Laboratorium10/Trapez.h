#pragma once

class Trapez {
private:
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
	void	Wypisz();
	void	Symetria(double x);
	void	Skaluj(double x);
	void	ZwiekszPole(Trapez& t);
	void	SetNastepny(Trapez* t);
	Trapez* GetNastepny();
	double	GetPole();
};


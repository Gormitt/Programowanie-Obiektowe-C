#pragma once

class Trapez {
private:
	double	ax, ay;
	double	bx, by;
	double	gorna;
	int		kierunek;
	void	UstawFigure(double ax, double ay, double bx, double by, double gorna, int kierunek);
public:
	Trapez();
	Trapez(double ax, double ay, double bx, double by, double gorna, int kierunek);
	void	Wypisz();
	void	Symetria(double x);
	void	Skaluj(double x);
	void	ZwiekszPole(Trapez& t);
	double	GetPole();
};


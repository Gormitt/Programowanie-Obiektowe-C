#pragma once

class Trapez {
private:
	double	ax, ay;
	double	bx, by;
	double	gorna;
	int		kierunek;
public:
	Trapez();
	Trapez(double ax, double ay, double bx, double by, double gorna, int kierunek);
	void	Wypisz();
};


#pragma once
class Prostokat {
private:
	double	ax, ay;
	double	pozioma;
	double	pionowa;
	int		kPoziomy, kPionowy;
	void	UstawFigure(double ax, double ay, double pozioma, double pionowa, int kPoziomy, int kPionowy); 
public:
	Prostokat();
	Prostokat(double ax, double ay, double gorna, double pionowa, int kPoziomy, int kPionowy);
	void	Wypisz();
	void	Symetria(double x);
	void	Skaluj(double x);
	void	ZwiekszPole(Prostokat& p);
	double	GetPole();
};


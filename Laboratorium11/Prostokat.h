#pragma once

class Prostokat {
private:
	static int liczbaWszystkich;
	static double poleWszystkich;
	Prostokat* nastepny;
	double		ax, ay;
	double		pozioma;
	double		pionowa;
	int			kPoziomy, kPionowy;
	void		UstawFigure(double ax, double ay, double pozioma, double pionowa, int kPoziomy, int kPionowy);
public:
	Prostokat();
	Prostokat(double ax, double ay, double gorna, double pionowa, int kPoziomy, int kPionowy);
	Prostokat(Prostokat& p);
	~Prostokat();
	void		Wypisz();
	void		Symetria(double x);
	void		Skaluj(double x);
	void		ZwiekszPole(Prostokat& p);
	Prostokat*	SzukajDrugiego(Prostokat* p);
	void		SetNastepny(Prostokat* p);
	Prostokat*	GetNastepny();
	double		GetPole();
	static int		GetLiczbaWszystkich();
	static double	GetPoleWszystkich();

	friend class Trapez;
};


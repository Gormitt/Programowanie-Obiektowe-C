#pragma once
class Prostokat {
private:
	Prostokat*	nastepny;
	double		ax, ay;
	double		pozioma;
	double		pionowa;
	int			kPoziomy, kPionowy;
	void		UstawFigure(double ax, double ay, double pozioma, double pionowa, int kPoziomy, int kPionowy); 
public:
	Prostokat();
	Prostokat(double ax, double ay, double gorna, double pionowa, int kPoziomy, int kPionowy);
	Prostokat(Prostokat& p);
	void		Wypisz();
	void		Symetria(double x);
	void		Skaluj(double x);
	void		ZwiekszPole(Prostokat& p);
	void		SetNastepny(Prostokat* p);
	Prostokat*	GetNastepny();
	double		GetPole();
};


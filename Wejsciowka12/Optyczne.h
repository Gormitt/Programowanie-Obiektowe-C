#pragma once

class Optyczne {
private:
	int			zdefiniowane;
protected:
	Optyczne*	nst;
	double		masa;
	double		srednica;
	double		ogniskowa;
	int			stabilizacja;
public:
	Optyczne();
	Optyczne(double masa, double srednica, double ogniskowa, int stabilizacja);
	Optyczne(Optyczne&);
	~Optyczne();
	void	Wypisz();
	void	WypiszDalsze();
	// settery
	void	SetNst(Optyczne*);
	void	SetMasa(double);
	void	SetOgniskowa(double);
	void	SetSrednica(double);
	void	SetStabilizacja(int);
	// gettery
	Optyczne* GetNst();
	double	GetMasa();
	double	GetOgniskowa();
	double	GetSrednica();
	int		GetStabilizacja();
};


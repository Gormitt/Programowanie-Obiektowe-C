#pragma once

class Silnik {
protected:
	Silnik* nastepny;
	int liczbaCylindrow;
	int maxObroty;
	float pojemnosc;
public:
	Silnik();
	Silnik(Silnik& s);
	Silnik(int liczbaCylindrow, int maxObroty, float pojemnosc);
	~Silnik();

	void Wypisz();
	void operator += (const Silnik& silnik);
	// setter
	void SetNastepny(Silnik* silnik);
	void SetLiczbaCylindrow(int liczbaCylindrow);
	void SetMaxObroty(int maxObroty);
	void SetPojemnosc(float pojemnosc);
	// gettery
	Silnik* GetNastepny();
	int GetLiczbaCylindrow();
	int GetMaxObroty();
	float GetPojemnosc();
};


#pragma once

#define DL 30

class Samochod {
protected:
	Samochod* nastepny;
	int rocznik;
	int przebieg;
	char marka[DL];
	char model[DL];
public:
	Samochod();
	Samochod(Samochod& samochod);
	Samochod(int rocznik, int przebieg, char* marka, char* model);
	~Samochod();
	// Do wybory sa dwie deklaracje
	// 1.: void Wypisz(FILE* out); - metoda niepolimorficzna [kompilator podczas wywolania wyszuka metode z klasy Samochod]
	// 2.: virtual void Wypisz(FILE* out) = 0; - metoda polimorficzna [kompilator podczas wywolania poszuka definicji z klasy dziedziczacej]
	void Wypisz(FILE* out);
	
	// Do wybory sa dwie deklaracje
	// 1.: void WypiMniejszyNizsz(FILE* out, float wielkosc); - metoda niepolimorficzna [kompilator podczas wywolania wyszuka metode z klasy Samochod]
	// 2.: virtual void MniejszyNiz(FILE* out, float wielkosc) = 0; - metoda polimorficzna [kompilator podczas wywolania poszuka definicji z klasy dziedziczacej]
	void MniejszyNiz(FILE* out, float wielkosc);

	// settery
	void SetNastepny(Samochod* nastepnySamochod);
	void SetRocznik(int rocznik);
	void SetPrzebieg(int przebieg);
	void SetMarka(char* marka);
	void SetModel(char* marka);
	// gettery
	Samochod* GetNastepny();
	int GetRocznik();
	int GetPrzebieg();
	char* GetMarka();
	char* GetModel();
};
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
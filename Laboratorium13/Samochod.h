#pragma once

#define DL 30

class Samochod {
protected:
	Samochod* nastepny;
	int rocznik;
	int przebieg;
	std::string marka;
	std::string model;
public:
	Samochod();
	Samochod(Samochod& samochod);
	Samochod(int rocznik, int przebieg, std::string marka, std::string model);
	~Samochod();

	virtual void Wypisz() = 0;

	// settery
	void SetNastepny(Samochod* nastepnySamochod);
	void SetRocznik(int rocznik);
	void SetPrzebieg(int przebieg);
	void SetMarka(std::string marka);
	void SetModel(std::string marka);
	// gettery
	Samochod* GetNastepny();
	int GetRocznik();
	int GetPrzebieg();
	std::string GetMarka();
	std::string GetModel();
	virtual std::string GetTyp() = 0;
};
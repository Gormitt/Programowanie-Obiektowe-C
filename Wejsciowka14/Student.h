#pragma once
#include "Osoba.h"
class Student : public Osoba {
private:
	Student* nast;
	int rok;
	std::string uczelnia;
public:
	Student();
	Student(std::string imie, int wiek, int liczbaZainteresowan, int rok, std::string uczelnia);
	~Student();
	void operator += (Student& student);
	virtual void Wypisz();

	// set
	void Set_nastepny(Student* wykladowca);
	// get
	Student* Get_nastepny();
};


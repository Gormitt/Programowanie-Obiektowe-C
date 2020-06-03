#include <iostream>
#include "Student.h"

Student::Student() :
	Osoba(),
	nast(NULL),
	rok(0),
	uczelnia("") {
}

Student::Student(std::string imie, int wiek, int liczbaZainteresowan, int rok, std::string uczelnia) :
	Osoba(imie, wiek, liczbaZainteresowan),
	nast(NULL),
	rok(rok),
	uczelnia(uczelnia) {
}

Student::~Student() {
	delete this->nast;
}

void Student::operator += (Student& student) {
	Osoba::operator+=(student);
	this->rok = (this->rok > student.rok) ? this->rok : student.rok;
	this->rok = (this->rok != 0) ? this->rok : student.rok;
	this->uczelnia = "";
}

void Student::Wypisz() {
	std::cout << "student";
	if (this->imie.length() > 0) std::cout << "\nimie: " << this->imie;
	std::cout << "\nwiek: " << this->wiek;
	std::cout << "\nliczba zainteresowan: " << this->liczbaZainteresowan;
	std::cout << "\nrok: " << this->rok;
	if (this->uczelnia.length() > 0) std::cout << "\nszkola: " << this->uczelnia << "\n\n";
	else std::cout << "\n\n";
}


// set
void Student::Set_nastepny(Student* w) { this->nast = w; }
// get
Student* Student::Get_nastepny() { return this->nast; }
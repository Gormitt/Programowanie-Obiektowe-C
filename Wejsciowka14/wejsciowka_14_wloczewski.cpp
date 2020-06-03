#include <iostream>
#include <fstream>

#include "Student.h"
#include "Wykladowca.h"

template <class T>
T Sumuj_elementy(T* tmp) {
	T suma;
	while (tmp) {
		suma += (*tmp);
		tmp = tmp->Get_nastepny();
	}
	return suma;
}

template <class T>
void Dodaj_element(T** glowa, T** ogon, T* element) {
	if ((*glowa) == NULL) {
		(*glowa) = element;
		(*ogon) = element;
	}
	else {
		(*ogon)->Set_nastepny(element);
		(*ogon) = (*ogon)->Get_nastepny();
	}
}

// metoda testowa do wypisania listy
template <class T>
void Wypisz_liste(T* tmp) {
	if (tmp == NULL) std::cout << "(i) info - lista jest pusta\n\n";
	while (tmp) {
		tmp->Wypisz();
		tmp = tmp->Get_nastepny();
	}
}

int main() {
	Osoba* go = NULL, *oo = NULL;
	Student* gs = NULL, *os = NULL;
	Wykladowca* gw = NULL, *ow = NULL;

	std::string nazwa = "in.txt";
	std::ifstream plik(nazwa);
	
	if (plik.good() && plik.is_open()) {
		if (plik.peek() != std::ifstream::traits_type::eof()) {
			while (plik.good()) {
				std::string imie;
				int wiek;
				int liczbaZainteresowan;
				char typ;
				plik >> typ;
				plik >> imie;
				plik >> wiek;
				plik >> liczbaZainteresowan;

				Dodaj_element<Osoba>(&go, &oo, new Osoba(imie, wiek, liczbaZainteresowan));

				if (typ == 's') {
					int rok;
					std::string uczelnia;
					plik >> rok;
					plik >> uczelnia;

					Dodaj_element<Student>(&gs, &os, new Student(imie, wiek, liczbaZainteresowan, rok, uczelnia));
				}
				else if (typ == 'w') {
					std::string przedmiot;
					std::string stopien;
					int liczbaGrup;
					plik >> liczbaGrup;
					plik >> przedmiot;
					plik >> stopien;

					Dodaj_element<Wykladowca>(&gw, &ow, new Wykladowca(imie, wiek, liczbaZainteresowan, liczbaGrup, przedmiot, stopien));
				}
			}
		}
	}

	// UWAGA:
	// sumaO zawiera sume wszystkich instancji klasy Osoba. Operator += w Osobie sumuje wiek i liczbe zainteresowan
	// sumaS zawiera sume -----------||------------- Student. Operator += dziala podobnie jak w osobie, ale dodatkowo zapisuje najwieksza wartosc z pola rok wszystkich sumowanych instancji
	// sumaW zawiera sume -----------||------------- Wykladowca. Operator += sumuje dodatkowo liczbe grup studenckich.
	// operatory += w klasach pochodnych wykorzystuja wywolanie Osoba::operator+=(...) aby nie duplikowac kodu + sumuja pola charakterystyczne dla klas pochodnych

	Osoba sumaO = Sumuj_elementy<Osoba>(go);
	Student sumaS = Sumuj_elementy<Student>(gs);
	Wykladowca sumaW = Sumuj_elementy<Wykladowca>(gw);
	std::cout << "suma wszystkich instancji klasy pierwotnej Osoba <Studencji + Wykladowcy>:\n";
	sumaO.Wypisz();
	std::cout << "suma wszystkich instancji klasy Student:\n";
	sumaS.Wypisz();
	std::cout << "suma wszystkich instancji klasy Wykladowca:\n";
	sumaW.Wypisz();

	// testowe wypisanie list
	// Wypisz_liste<Student>(gs);
	// Wypisz_liste<Wykladowca>(gw);
	
	delete go;
	delete gs;
	delete gw;
	go = oo = NULL;
	gs = os = NULL;
	gw = ow = NULL;

	// testowe wypisanie list [po dealokacji, funkcja powinna powiadomic o pustych listach]
	// Wypisz_liste<Student>(gs);
	// Wypisz_liste<Wykladowca>(gw);
	return 0;
}
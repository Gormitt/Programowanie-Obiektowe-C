#include <iostream>
#include <fstream>

#include "Osobowy.h"
#include "Ciezarowy.h"

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t15 maj 2020\n");
	printf("about: \tRealizacja programu na laboratoria nr. 13\n\n");
}

template <class T1, class T2, class T3>
void DodajDoListy(T1** glowa, T1** ogon, int rocznik, int przebieg, std::string marka, std::string model, T2 param1, T3 param2) {
	if (*glowa == NULL) {
		*glowa = new T1(rocznik, przebieg, marka, model, param1, param2);
		*ogon = *glowa;
	}
	else {
		(*ogon)->SetNastepny(new T1(rocznik, przebieg, marka, model, param1, param2));
		*ogon = (*ogon)->GetNastepny();
	}
}

int main() {
	Info();
	
	std::string nazwaIn = "in.txt";
	std::ifstream in(nazwaIn);
	if (in.good() && in.is_open()) {
		if (in.peek() == std::ifstream::traits_type::eof()) {
			std::cout << "info  - plik jest pusty" << std::endl;
		}
		else {
			Osobowy * glowaO = NULL, * ogonO = NULL;
			Ciezarowy * glowaC = NULL, * ogonC = NULL;

			int typ, rok, przebieg;
			std::string marka, model;
			std::cout << "info - poprawnie otwarto plik " << nazwaIn << std::endl;
			while (in.good()) {
				in >> typ;
				in >> rok;
				in >> przebieg;
				in >> marka;
				in >> model;
				if (typ == 0) {
					float bagaznik;
					char sylwetka;
					in >> bagaznik;
					in >> sylwetka;

					DodajDoListy<Osobowy, float, char>(&glowaO, &ogonO, rok, przebieg, marka, model, bagaznik, sylwetka);
				}
				else if (typ == 1) {
					float ladownosc;
					int kola;
					in >> ladownosc;
					in >> kola;

					DodajDoListy<Ciezarowy, float, int>(&glowaC, &ogonC, rok, przebieg, marka, model, ladownosc, kola);
				}
			}

			Osobowy sumaO;
			Osobowy* tmp1 = glowaO;
			Ciezarowy sumaC;
			Ciezarowy* tmp2 = glowaC;
			while (tmp1) {
				sumaO += *tmp1;
				tmp1 = tmp1->GetNastepny();
			}

			while (tmp2) {
				sumaC += *tmp2;
				tmp2 = tmp2->GetNastepny();
			}

			sumaO.Wypisz();
			sumaC.Wypisz();

			delete glowaO;
			delete glowaC;
		}
	}
	else {
		std::cout << "error - blad podczas otwarcia pliku" << std::endl;
	}

	return 0;
}
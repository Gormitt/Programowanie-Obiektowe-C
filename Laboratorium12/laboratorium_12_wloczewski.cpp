#include <iostream>

#include "Samochod.h"
#include "Osobowy.h"
#include "Ciezarowy.h"

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t15 maj 2020\n");
	printf("about: \tRealizacja programu na laboratoria nr. 12\n\n");
}

int main() {
	Info();
	FILE* in = NULL;
	FILE* out = NULL;
	
	if (fopen_s(&in, "in.txt", "r") == 0 && in != NULL && fopen_s(&out, "out[polimorfizm - off].txt", "w+") == 0 && out != NULL) {
		// zadanie I poziomu
		Samochod* glowa = NULL;
		Samochod* ogon = NULL;

		while (!feof(in)) {
			int rodzaj;
			fscanf_s(in, "%d", &rodzaj);
			if (feof(in)) {
				break;
			}
			else {
				int rocznik, przebieg;
				char marka[DL], model[DL];
				fscanf_s(in, "%d\t%d", &rocznik, &przebieg);
				fscanf_s(in, "%s\t%s", marka, DL, model, DL);
				if (rodzaj == 0) {
					float pojemnoscBagaznika;
					char sylwetka;
					fscanf_s(in, "%f\t%c", &pojemnoscBagaznika, &sylwetka, 1);

					if (glowa == NULL) {
						glowa = new Osobowy(rocznik, przebieg, marka, model, pojemnoscBagaznika, sylwetka);
						ogon = glowa;
					}
					else {
						ogon->SetNastepny(new Osobowy(rocznik, przebieg, marka, model, pojemnoscBagaznika, sylwetka));
						ogon = ogon->GetNastepny();
					}
				}
				else if (rodzaj == 1) {
					float maxLadownosc;
					int liczbaKol;
					fscanf_s(in, "%f\t%d", &maxLadownosc, &liczbaKol);

					if (glowa == NULL) {
						glowa = new Ciezarowy(rocznik, przebieg, marka, model, maxLadownosc, liczbaKol);
						ogon = glowa;
					}
					else {
						ogon->SetNastepny(new Ciezarowy(rocznik, przebieg, marka, model, maxLadownosc, liczbaKol));
						ogon = ogon->GetNastepny();
					}
				}
			}
		}

		ogon = glowa;
		while (ogon) {
			ogon->Wypisz(out);
			ogon = ogon->GetNastepny();
		}
		printf("poprawnie wczytano plik do listy dynamicznej jednokierunkowej\n");
		printf("poprawnie zapisano liste dynamiczna jednokierunkowa do pliku\n\n");
		
		// zadanie II poziomu
		FILE* mn;
		if (fopen_s(&mn, "mniejszyNiz[polimorfizm - off].txt", "w+") == 0 && mn != NULL) {
			glowa->MniejszyNiz(mn, 2010);
			fclose(mn);
		}

		printf("poprawnie zdealokowano liste dynamiczna jednokierunkowa\n");
		delete glowa;
		fclose(in);
		fclose(out);
	}
	else {
		printf("error - nie udalo sie otworzyc pliku\n\n");
	}

	return 0;
}
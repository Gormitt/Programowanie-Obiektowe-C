#include <iostream>

#include "Silnik.h"

void Info() {
	printf("autor: \tMateusz Wloczewski\n");
	printf("data: \t17 maj 2020\n");
	printf("about: \tProgram realizujacy wejsciowke nr. 13\n");
	printf("\tProgram demonstruje dodawanie instacji obiektow tej samej klasy do siebie.\n\n");
}

int main() {
	/*
	Dodawanie Silnikow:
	Program interpretuje polaczony silnik jako:
	1. sume ilosci cylindrow
	2. sume pojemnosci
	3. maxObroty najslabszego ogniwa tzn. po dodaniu obiektu B do A
	gdzie A::maxObroty = 10000 oraz B::maxObroty = 9000, w obiekcie
	A maxObroty zostana zmniejszone z 10000 do 9000 obr/min
	*/
	Info();
	
	FILE* in;
	if (fopen_s(&in, "in.txt", "r") == 0 && in != NULL) {
		Silnik* glowa = NULL;
		Silnik* tmp = NULL;
		int liczbaCylindrow = 0;
		int maxObroty = 0;
		float pojemnosc = 0.0;
		while (!feof(in)) {
			fscanf_s(in, "%d", &liczbaCylindrow);
			fscanf_s(in, "%d", &maxObroty);
			fscanf_s(in, "%f", &pojemnosc);
			if (feof(in)) break;

			if (glowa == NULL) {
				glowa = new Silnik(liczbaCylindrow, maxObroty, pojemnosc);
				tmp = glowa;
			}
			else {
				tmp->SetNastepny(new Silnik(liczbaCylindrow, maxObroty, pojemnosc));
				tmp = tmp->GetNastepny();
			}
		}
		tmp = glowa;

		Silnik* suma = new Silnik();
		printf("lista silnikow z pliku:\n");
		while (tmp) {
			(*suma) += (*tmp);
			tmp->Wypisz();
			tmp = tmp->GetNastepny();
		}
		printf("obiekt silnik bedacy suma listy:\n");
		suma->Wypisz();
		
		fclose(in);
		delete glowa;
		delete suma;
		glowa = NULL;
		tmp = NULL;
		suma = NULL;
	}

	return 0;
}
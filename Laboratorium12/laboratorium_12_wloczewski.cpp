#include <iostream>

#include "Samochod.h"
#include "Osobowy.h"

int main() {
	FILE* out1 = NULL;

	char marka[DL] = "Toyota";
	char model[DL] = "Careena";
	Osobowy o1(1997, 100000, marka, model, 10.0, 'H');
	
	o1.Wypisz(out1);
	return 0;
}
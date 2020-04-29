#include <iostream>
#include <cstdio>
#include <cstring>

#include "Stale.h"
#include "BazaEmail.h"
#include "Wykladowca.h"

using namespace std;

int main() {
	char email1[DL_TABLICY] = "m.wloczewski@gmail.com";
	char email2[DL_TABLICY] = "k.kowalczyk@gmail.com";

	BazaEmail b1(3);
	b1.Setemail(email1, 0);
	
	BazaEmail b2(b1);
	b2.Setemail(email2, 0);

	Wykladowca w1("in.txt");

	return 0;
}
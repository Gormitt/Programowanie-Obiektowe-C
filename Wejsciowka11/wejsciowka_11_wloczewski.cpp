#include <iostream>

#include "Baza.h"

int main() {
	char email1[DL_SLOWA] = "mateusz.wloczewski00@gmail.com";
	char email2[DL_SLOWA] = "mikolaj.grzegorzewski@gmail.com";

	Baza b1(2);
	b1.SetMail(0, email1);
	b1.SetMail(1, email2);
	
	printf("%s\n%s\n\n", b1.GetMail(0), b1.GetMail(1));

	Baza b2(b1);

	printf("%s\n%s\n\n", b2.GetMail(0), b2.GetMail(1));
	return 0;
}
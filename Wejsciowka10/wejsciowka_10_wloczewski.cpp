#include <cstdio>
#include <cstring>

#define DL_SLOWA 30

using namespace std;

class MojaKlasa {
	char** email;
	int ile;
public:
	MojaKlasa(int x);
	MojaKlasa(MojaKlasa& mk);	// konstruktor kopiuj¹cy
	void setemail(char* adres, int idx) { strcpy(email[idx], adres); }
	char* getemail(int idx) { return email[idx]; }
};

MojaKlasa::MojaKlasa(int x) {
	email = new char* [ile = x];
	for (int i = 0; i < ile; i++) email[i] = new char[100];
}

MojaKlasa::MojaKlasa(MojaKlasa& mk) {
	email = mk.email;			// czy to jest OK?
}

/*
MojaKlasa::MojaKlasa(MojaKlasa& mk) {
	email = new char*[mk.ile];
	ile = mk.ile;
	for (int i=0;i<ile;i++) {
		email[i] = new char[100];
		strcpy(email[i],mk.email[i]);
	}
}
*/
int main() {
	char email1[DL_SLOWA] = "m.wloczewski@gmail.com";
	char email2[DL_SLOWA] = "k.kowalczyk@gmail.com";

	MojaKlasa MK(3);
	MK.setemail(email1, 0);
	MojaKlasa MK2(MK);
	printf("%s\n", MK2.getemail(0));
	MK.setemail(email2, 0);
	printf("%s\n", MK2.getemail(0));
	return 0;
}
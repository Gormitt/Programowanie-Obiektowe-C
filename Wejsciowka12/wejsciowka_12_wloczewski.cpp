#include <iostream>

#include "Silnik.h"
#include "Samochod.h"
#include "Optyczne.h"
#include "Osoba.h"

int main() {
	Silnik*		glowaSi = NULL;
	Samochod*	glowaSa = NULL;
	Optyczne*	glowaOp = NULL;
	Osoba*		glowaOs = NULL;
	
	glowaSi = new Silnik();
	glowaSi->SetNst(new Silnik(100, 1.5));
	glowaSi->GetNst()->SetNst(new Silnik(150, 2.0));
	glowaSi->GetNst()->GetNst()->SetNst(new Silnik(120, 1.9));
	glowaSi->GetNst()->GetNst()->GetNst()->SetNst(new Silnik());

	glowaSa = new Samochod();
	glowaSa->SetNst(new Samochod(1997, 100000, "Toyota", "Careena"));
	glowaSa->GetNst()->SetNst(new Samochod(2003, 50000, "Volvo", "S40"));
	glowaSa->GetNst()->GetNst()->SetNst(new Samochod(2010, 120000, "Toyota", "Avensis III"));
	glowaSa->GetNst()->GetNst()->GetNst()->SetNst(new Samochod());

	glowaOp = new Optyczne;
	glowaOp->SetNst(new Optyczne(0.25, 67, 300, 1));
	glowaOp->GetNst()->SetNst(new Optyczne(0.20, 72, 20, 1));
	glowaOp->GetNst()->GetNst()->SetNst(new Optyczne(0.10, 58, 50, 0));
	glowaOp->GetNst()->GetNst()->GetNst()->SetNst(new Optyczne());

	glowaOs = new Osoba();
	glowaOs->SetNst(new Osoba("Mateusz", "Wloczewski", "mateusz.wloczewski@gmail.com", 2));
	glowaOs->GetNst()->SetNst(new Osoba("Bartek", "Witwicki", "bartek.witwicki@gmail.com", 2));
	glowaOs->GetNst()->GetNst()->SetNst(new Osoba("Michal", "Kabacinski", "michal.kabacinski@gmail.com", 1));
	glowaOs->GetNst()->GetNst()->GetNst()->SetNst(new Osoba());

	glowaSi->WypiszDalsze();
	glowaSa->WypiszDalsze();
	glowaOp->WypiszDalsze();
	glowaOs->WypiszDalsze();

	delete glowaSi;
	delete glowaSa;
	delete glowaOp;
	delete glowaOs;
	return 0;
}
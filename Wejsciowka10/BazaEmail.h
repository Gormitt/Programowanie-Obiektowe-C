#pragma once

class BazaEmail {
	BazaEmail*	nast;
	char**		email;
	int			ile;
public:
	BazaEmail(int);
	BazaEmail(BazaEmail&);
	void	Setemail(char*, int);
	char*	Getemail(int);
};

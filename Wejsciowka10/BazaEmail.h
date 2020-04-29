#pragma once

class BazaEmail {
private:
	BazaEmail*	nast;
	char**		email;
	int			ile;
public:
	BazaEmail(int);
	BazaEmail(BazaEmail&);
	void	SetEmail(char*, int);
	char**	GetEmaile(void);
	char*	GetEmail(int);
	int		GetIle(void);
};

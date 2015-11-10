#ifndef PESQUISA_H
#define PESQUISA_H

#include <iostream>
#include <string>
using namespace std;

class Pesquisa{
	private:
		int cod;	
		string nome;

	public:
		Pesquisa();
		Pesquisa(string n, int c);
		~Pesquisa();
		void setNome(string n);
		string getNome ();
		void setCod (int c);
		int getCod ();
		Pesquisa clone ();			
};

#endif
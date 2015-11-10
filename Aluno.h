#ifndef ALUNO_H
#define ALUNO_H

#include <iostream>
#include <string>
#include "stdlib.h"
using namespace std;

class Aluno{
	private:
		int pesquisa;	
		int nome;
		int array[2];

	public:
		Aluno();
		Aluno(string dados);
		~Aluno();
		void setNome(int n);
		int getNome ();
		void setPesq (int p);
		int getPesq ();
		Aluno clone ();
		void liseDados (string dados);
		int toInt(string s);
};

#endif
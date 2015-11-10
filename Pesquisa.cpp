#include <string>
#include <iostream>
#include "Pesquisa.h"
using namespace std;

	
Pesquisa::Pesquisa(){
	cod = 0;
	nome = "";
}//construtor


Pesquisa::Pesquisa(string n, int c){
	nome = n;
	cod = c;
}//end construtor


Pesquisa::~Pesquisa(){	
}//destrutor		


/** metodo que seta o nome da area de pesquisa */
void Pesquisa::setNome (string n){
	nome = n;
}//end setNome			


/**  metoque que retorna o nome da area de pesquisa */
string Pesquisa::getNome (){
		return nome;
}//end getNome


/**metodo que seta o cod da area de pesquisa*/
void Pesquisa::setCod (int c){
	cod = c;
}//end setCod


/**metodo que retorna o cod da area de pesquisa*/
int Pesquisa::getCod (){
	return cod;
}//end getCod


/**metodo que faz um clone do objeto corrente e retorna o clone*/
Pesquisa Pesquisa::clone(){
	Pesquisa P;

	P.nome = this -> nome;
	P.cod = this -> cod;

	return P;
}//end clone
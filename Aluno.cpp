#include <string>
#include <iostream>
#include "Aluno.h"
#include "stdlib.h"
using namespace std;

	
Aluno::Aluno(){
	pesquisa = 0;
	nome = 0;
	cluster = -1;
}//construtor


Aluno::Aluno(string dados){
	liseDados(dados);
	nome = array[0];
	pesquisa = array[1];
}//end construtor


Aluno::~Aluno(){	
}//destrutor	


/** metodo que seta o cluster que o aluno pertence */
void Aluno::setCluster(int c){
	cluster = c;
}//end setCluster


/** metodo que retorna o cluster que o aluno pertence */
int Aluno::getCluster(){
	return cluster;
}//end getCluster


/** metodo que seta o nome da area de pesquisa */
void Aluno::setNome (int n){
	nome = n;
}//end setNome			


/**  metoque que retorna o nome da area de pesquisa */
int Aluno::getNome (){
		return nome;
}//end getNome


/**metodo que seta o cod da area de pesquisa*/
void Aluno::setPesq (int p){
	pesquisa = p;
}//end setCod


/**metodo que retorna o cod da area de pesquisa*/
int Aluno::getPesq (){
	return pesquisa;
}//end getCod


/**metodo que faz um clone do objeto corrente e retorna o clone*/
Aluno Aluno::clone(){
	Aluno A;

	A.nome = this -> nome;
	A.pesquisa = this -> pesquisa;

	return A;
}//end clone


/** 
  metodo que recebe uma string com os dados e armazena-os em um array
*/
void Aluno::liseDados(string dados){
	string controle = "";

	//int k = 0;

	for (int i=0; i < dados.length(); i++){
		
       if  (dados[i] != ' ') {

       		controle = controle + dados[i]; 

       		if (i == (dados.length() -1))       			
       			array[1] = toInt(controle);       		
       }
       else{        	 
       	 array [0] = toInt(controle);       	 
         controle = "";
       }//end if1

     }//end for     
}//end lise dados


/* metodo que transforma string em inteiro */
int Aluno::toInt(string s)	{
	return atoi(s.c_str());
}//end toInt
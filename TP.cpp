/*
	Trabalho Prático Grafo

	Thiago Henrique Balbino Dias
*/

#include <iostream>
#include <fstream>  //tratar arquivos
#include <string>
#include "Pesquisa.h"
#include "Aluno.h"
#include "stdlib.h"
using namespace std;

class TP{
	private:
		int countPesq;	 //quantidade de pesquisas
		int countAlu;	 //quantidade de alunos
		int matrizDissimilar[20][20];
		Pesquisa arrayPesquisa[20];		//pesquisas
		Aluno *arrayAluno;              //alunos	

		/**
		  *metodo que ler o arquivo "areaPesquisaNome.txt"
		  *e armazena os nomes em um array de Pesquisa
		*/
		void lerNomePesquisa (){
			//arquivo constante
			ifstream fin ("areaPesquisaNome.txt");  //abre arquivo
			string nome;

			obterCountPesq();			

			for (int i = 0; i < countPesq; i++){
				getline(fin, nome);
				Pesquisa pesquisa (nome, (i+1));
				arrayPesquisa[i] = pesquisa.clone(); 
			}//end for

			fin.close(); //fecha arquivo
		}//end lerNomePesquisa


		/**
			metodo que que ler o arquivo "entrada.txt"
			e armazena os alunos em um array de Aluno
		*/
		void lerAluno (){
			ifstream fin ("entrada.txt"); //abre arquivo
			string dados;
			obterCountAlu();
			arrayAluno = new Aluno[countAlu];			

			for (int i = 0; i < countAlu; i++){
				getline(fin, dados);
				Aluno aluno (dados);
				arrayAluno[i] = aluno.clone();											
			}//end for

			fin.close();//fecha arquivo
		}//end lerAluno



		/**
		  *metodo que obtem quantidade de nomes de pesquisa
		*/
		void obterCountPesq (){
			ifstream fin ("areaPesquisaNome.txt");
			string nome;

			while (getline(fin, nome))	countPesq++;

			fin.close();
		}//end obterCountPesq


		/**
		  metodo que obtem quantidade de alunos
		*/
		void obterCountAlu(){
			ifstream fin ("entrada.txt");
			string nome;

			while (getline(fin, nome))	countAlu++;

			fin.close();
		}//end obterCountAlu


		/* metodo que monta a matriz dissimilar */
		void montarMatrizDissimilar(){
			//arquivo constante
			ifstream fin ("areaPesquisa.txt"); //abre arquivo 
			string relacao;

			for (int i = 0; i < countPesq; i++){
				getline(fin, relacao);
				inserirMatriz (relacao, i);								
			}//end for

			fin.close();//fecha arquivo
		}//end montarMatrizDissimilar


		/*
			metodo que insere uma pesquisa na matriz dissimilar
			@param s: linha com valores a quem pesquisa se relaciona
			@param pesquisa: pesquisa atual
		*/
		void inserirMatriz (string s, int pesquisa){
			int tam = s.size();
			string valor = "";  //controle
			int k, cont; //controle
			k = cont = 0;			

			for (int i = 0; i < tam; i++){
				if (s[i] != ' ')
					valor = valor + s[i];
				else { 					
					k = toInt (valor);					
					matrizDissimilar[pesquisa][cont] = k;					
					cont++;
					valor = "";
				}//end if
			}//end for

			k = toInt (valor);
			matrizDissimilar[pesquisa][cont] = k;
		}//end inserirMatriz


		/* metodo que transforma string em inteiro */
		int toInt(string s)	{
    		return atoi(s.c_str());
		}//end toInt


		/** metodo que monta o grafo */
		void montarGrafo(){
			int grafo [countAlu] [countAlu];
			int pesq1, pesq2;			

			//preenchendo grafo
			for (int i = 0; i < countAlu; i++){
				pesq1 = arrayAluno[i].getPesq(); //cout << "\n"<<pesq1;

				for (int j = 0; j < countAlu; j++){
					pesq2 = arrayAluno[j].getPesq(); //cout <<" "<<pesq2;
					grafo[i][j] = matrizDissimilar[pesq1-1][pesq2-1];
				}//end for
				//cout << "\n";
			}//end for

			//teste mostrar grafo
			//for (int i = 0; i < countAlu; i++){				
			//	for (int j = 0; j < countAlu; j++){
					//cout << " " << grafo[i][j];	
			//	}
				//cout << endl;
			//}	

		}//end montarGrafo

	public:
		/* contrutor */
		TP(){
			countPesq = 0;
			countAlu = 0;
		}//end contrutor


		/* destrutor */
		~TP(){
			//delete arrayAluno; //nao sei pq o problema			
		}//end destrutor	


		/* metodo controle */
		void controle (){
			lerNomePesquisa();
			lerAluno();
			montarMatrizDissimilar(); 
			montarGrafo();

			//for (int i = 0; i < countPesq; i++){
				
			//	for (int j = 0; j < countPesq; j++){
			//		cout << " " << matrizDissimilar[i][j];					
			//	}
			//	cout << endl;
			//}			

			//testes

		}//end controle
};


//--------------------------------------------------------------------------

/* CLASSE Grupo */
class Grupo{
	public:
		/* construtor */
		Grupo (){}//end construtor

		/* destrutor */
		~Grupo (){}//end destrutor
};//end class Grupo


//--------------------------------------------------------------------------



/* metodo principal */
int main (){
	TP tp;	

	tp.controle();

	cout << "\n\nOK, funcionando.\n\n\n";
	
}//end main
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
		int countProf;   //quantidade de professores
		int matrizDissimilar[20][20];
		Pesquisa arrayPesquisa[20];		//pesquisas
		Aluno *arrayAluno;		
		int *arrayAresta;
		int pesq1, pesq2;
		

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


		/**
			metodo que obtem quantidade de professores
		*/
		void obterCountProf(){
			int num;
			cout << "\n\nNumero de Professores: ";
			cin >> num;

			if (num > countAlu){
				cout << "O numero de professores deve ser menor/igual que o de alunos!";
				obterCountProf();
			}
			else
				countProf = num;
		}//end obterCountProf


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
			int agm [countAlu][countAlu];
			arrayAresta = new int [countAlu*countAlu];
			//int clust1, clust2;
			int k = 0;
			int numArestaAgm = 0;

			//preenchendo grafo e inicializando agm
			for (int i = 0; i < countAlu; i++){
				pesq1 = arrayAluno[i].getPesq();

				for (int j = 0; j < countAlu; j++){
					pesq2 = arrayAluno[j].getPesq(); 
					grafo[i][j] = matrizDissimilar[pesq1-1][pesq2-1];
					agm[i][j] = -1;
				}//end for
				//cout << "\n";
			}//end for

			//preenchendo arrayAresta
			for (int i = 0; i < countAlu; i++){				
				for (int j = 0; j < countAlu; j++){
					arrayAresta[k] = grafo[i][j];
					k++; 
				}//end for								
			}//end for

			//ordena o array de arestas
			OrdenarArrayAresta(); 

			
			//trabalhando na agm			
				
			for (int x = 10; x < (countAlu*countAlu); x++){  //for do arrayAresta

				if (numArestaAgm < (countAlu-1)){ //se nao tiver (n-1) arestas

					for (int i = 0; i < countAlu; i++){	//for linha do grafo

						for (int j = 0; j < countAlu; j++){	//for coluna do grafo						

							if (i == j)   //diagonal principal
								agm [i][j] = -1; //faz nada
							else{
								if (grafo[i][j] == arrayAresta[x]){
									if (agm[i][j] == -1){ //se nao tem aresta
										agm[i][j] = arrayAresta[x]; //insere na agm
										agm[j][i] = arrayAresta[x];//insere na agm mesma aresta
										x++;
										numArestaAgm++; 
										i = j = countAlu; //sair dos 2 for //ir para o proximo x
									}//end if
								}//end if
							}//end if 
								
						}//end for
					}//end for
				}//end if
				else{
					x = (countAlu*countAlu); //sair do for					
				}
			}//end for
			


			//teste arrayAresta
			//k = 0;
			//for (int i = 0; i < (countAlu); i++){
			//	for (int j = 0; j < countAlu; j++){
			//		cout << arrayAresta[k] << " ";
			//		k++;
			//	}
			//	cout << "\n";
			//}

			//teste mostrar grafo
			for (int i = 0; i < countAlu; i++){				
				for (int j = 0; j < countAlu; j++){
					cout << " " << agm[i][j];	
				}
				cout << endl;
			}	

		}//end montarGrafo



	/**
	 * Algoritmo de ordenacao por insercao.
	 */
	void OrdenarArrayAresta() {
		for (int i = 1; i < (countAlu*countAlu); i++) {
			int tmp = arrayAresta[i];
        	int j = i - 1;

        	while ((j >= 0) && (arrayAresta[j] > tmp)) {
            	arrayAresta[j + 1] = arrayAresta[j];
            	j--;
         	}//end while
         	arrayAresta[j + 1] = tmp;
      	}//end for
	}//end ordenarInsercao


		


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
			obterCountProf();



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


/* metodo principal */
int main (){
	TP tp;	

	tp.controle();

	cout << "\n\nOK, funcionando.\n\n\n";
	
}//end main
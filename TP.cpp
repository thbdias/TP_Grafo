/*
	Trabalho Prático Grafo

	Thiago Henrique Balbino Dias
*/

#include <iostream>
#include <fstream>  //tratar arquivos
#include <string>
#include <stdlib.h> //calloc
#include "Pesquisa.h"
#include "Aluno.h"	
#include "stdlib.h"

#define NAOVISITADO 0
#define VISITADO 1
#define ENCONTRADO 1
#define NAOENCONTRADO 0
#define NULO -1

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
		int *arrayArestaAgm;
		int pesq1, pesq2;
		int **grafo;
		int **agm;
		int busca;
		int numArestaAgm;
		int *arrayFila; //para busca largura
		int inicioFila;	//para busca largura
		int fimFila;	//para busca largura

		

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

			//alocacao de memoria
			grafo = (int**) calloc(countAlu, sizeof(int*));//linha			
			for (int i = 0; i < countAlu; i++)
				grafo[i] = (int*) calloc(countAlu, sizeof(int));//coluna

			//preenchendo grafo
			for (int i = 0; i < countAlu; i++){
				pesq1 = arrayAluno[i].getPesq();

				for (int j = 0; j < countAlu; j++){
					pesq2 = arrayAluno[j].getPesq(); 
					grafo[i][j] = matrizDissimilar[pesq1-1][pesq2-1];					
				}//end for
				
			}//end for

		}//end montarGrafo


		/** metodo que mostra o grafo na tela */
		void mostrarGrafo(){
			cout << "\n\n";
			for (int i = 0; i < countAlu; i++){				
				for (int j = 0; j < countAlu; j++){
					cout << " " << grafo[i][j];	
				}
				cout << endl;
			}//end for
		}//end mostrarGrafo


		/** metodo que inicializa o arrayAresta */
		void montarArrayAresta (){
			int k = 0;
			arrayAresta = new int [countAlu*countAlu];

			//preenchendo arrayAresta
			for (int i = 0; i < countAlu; i++){				
				for (int j = 0; j < countAlu; j++){
					arrayAresta[k] = grafo[i][j];
					k++; 
				}//end for								
			}//end for

			OrdenarArrayAresta(); 
		}//end montarArrayAresta


		/** metodo que mostra o arrayAresta */
		void mostrarArrayAresta (){
			int k = 0;

			for (int i = 0; i < (countAlu); i++){
				for (int j = 0; j < countAlu; j++){
					cout << arrayAresta[k] << " ";
					k++;
				}
				cout << "\n";
			}//end for
		}//end mostrarArrayAresta


		/** metodo que monta o grafo agm */
		void montarAgm(){			
			numArestaAgm = 0;

			//alocacao de memoria
			agm = (int**) calloc(countAlu, sizeof(int*));//linha			
			for (int i = 0; i < countAlu; i++)
				agm[i] = (int*) calloc(countAlu, sizeof(int));//coluna
			

			//inicializando agm
			for (int i = 0; i < countAlu; i++)
				for (int j = 0; j < countAlu; j++)
					agm[i][j] = -1;						

			
			//algoritmo de kruskal			
			for (int x = 10; x < (countAlu*countAlu); x++){  //for do arrayAresta

				if (numArestaAgm < (countAlu-1)){ //se nao tiver (n-1) arestas

					for (int i = 0; i < countAlu; i++){	//for linha do grafo

						for (int j = 0; j < countAlu; j++){	//for coluna do grafo						

							if (i == j)   //diagonal principal
								agm [i][j] = -1; //faz nada
							else{
								if (grafo[i][j] == arrayAresta[x]){
									if (agm[i][j] == -1){ //se nao tem aresta
										//tem caminho entre i e j?
										if ( !(hasCaminho(i, j)) ){ //se nao tem caminho
											agm[i][j] = arrayAresta[x]; //insere na agm
											agm[j][i] = arrayAresta[x];//insere na agm mesma aresta											
											numArestaAgm++; 		
											x++;
											i = j = countAlu; //sair dos 2 for //ir para o proximo x
										}//end if			
										
									}//end if
								}//end if
							}//end if 
								
						}//end for
					}//end for
				}//end if
				else{
					x = (countAlu*countAlu); //sair do for //laco do arrayAresta					
				}
			}//end for	

			//testar aki a busca em profundidade	
			//tem caminho entre o vertice 3 e 8?
			//bool teste = hasCaminho(2, 2); 
			//cout << "\n\n" << "tem caminho? = " << teste;
						
		}//end montarAgm


		/** metodo que mostra a agm na tela */
		void mostrarAgm (){
			cout << "\n\n";
			for (int i = 0; i < countAlu; i++){				
				for (int j = 0; j < countAlu; j++)
					cout << " " << agm[i][j];	
				
				cout << endl;
			}	
		}//end mostrarAgm


		/**
			metodo que aplica a busca em profundidade 
			para descobrir se tem um caminho entre dois vertices
		*/
		bool hasCaminho (int vi, int vf){
			bool resp = false;
			busca = NAOENCONTRADO;
			//alocacao de memoria
			int *arrayVisitado = (int*)calloc(countAlu, sizeof(int));

			//iniciando arrayVisitado como nao visitado
			for (int i = 0; i < countAlu; i++)
				arrayVisitado[i] = NAOVISITADO;

			//para cada vertice nao visitado, visitar
			//for (int i = 0; i < countAlu; i++)
			//	if (arrayVisitado[i] == NAOVISITADO)
					visita (vi, vf, arrayVisitado);			

			if (busca == ENCONTRADO)
				resp = true;

			return resp;
		}//end hasCaminho


		/** metodo usado pela busca em profundidade */
		void visita (int vertice, int vf, int *arrayVisitado){
			arrayVisitado[vertice] = VISITADO;			

			for (int i = 0; i < countAlu; i++){

				if ( agm[vertice][i] != -1 ){ //se tem vizinho

					if (i == vf){
						busca = ENCONTRADO;
					}
					else{
						if ( arrayVisitado[i] == NAOVISITADO ){
							visita (i, vf, arrayVisitado);
						}//end if
					}//end if
				}//end if

			}//end for
		}//end visita


		/** metodo usado pela busca em largura */
		void visitaLarg (int vertice, int *arrayVisitado, int cluster){
			arrayVisitado[vertice] = VISITADO;
			arrayAluno[vertice].setCluster(cluster);
			int elemento = NULO;

			for (int i = 0; i < countAlu; i++){

				if (agm[vertice][i] != -1) { //se tem vizinho
					//se vizinho não foi vizitado
					if (arrayVisitado[i] == NAOVISITADO){
						//inserir vizinho nao visitado na fila
						//e marca como vizitado
						inserirFila(i); 
						arrayVisitado[i] == VISITADO;
					}
				}//end if

			}//end for

			//mostrarFila(); //teste

			//retirar primeiro elemento da fila
			elemento = removerFila();
			if (elemento != NULO)
				visitaLarg(elemento, arrayVisitado, cluster);


		}//end visitaLarg



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


		/**
		 * Algoritmo de ordenacao por insercao.
		 */
		void ordenarArrayArestaAgm() {
			for (int i = 1; i < (numArestaAgm); i++) {
				int tmp = arrayArestaAgm[i];
	        	int j = i - 1;

	        	while ((j >= 0) && (arrayArestaAgm[j] > tmp)) {
	            	arrayArestaAgm[j + 1] = arrayArestaAgm[j];
	            	j--;
	         	}//end while
	         	arrayArestaAgm[j + 1] = tmp;
	      	}//end for
		}//end ordenarArrayArestaAgm


		/***/
		void montarCluster (){
			obterCountProf();  //numero professores
			int corte = (countProf-1); //numero de cortes na agm
			montarArrayArestaAgm();
			int k = numArestaAgm - corte; 
			int cluster = 0;
			arrayFila = new int [countAlu]; //para busca Largura
			inicioFila = fimFila = 0;
			//alocacao de memoria
			int *arrayVisitado = (int*)calloc(countAlu, sizeof(int));
			
			
			//atualizar agm com cortes
			for (int i = 0; i < countAlu; i++){				
				for (int j = (i+1); j < countAlu; j++){
					
					if (agm[i][j] != -1){ //se tiver aresta

						for (int w = k; w < numArestaAgm; w++){ //andar sobre arrayArestaAgm

							if (arrayArestaAgm[w] == agm[i][j]){
								agm[i][j] = -1; //fazendo corte na agm
								agm[j][i] = -1; //fazendo corte na agm
							}										

						}//end for

					}//end if	

				}//end for
			}//end for


			//iniciando arrayVisitado como nao visitado
			for (int i = 0; i < countAlu; i++)
				arrayVisitado[i] = NAOVISITADO;


			//busca largura
			//para cada vertice nao visitado, visitar
			for (int i = 0; i < countAlu; i++){
				if (arrayVisitado[i] == NAOVISITADO){
					if (cluster < countProf){
						cluster++;
						arrayAluno[i].setCluster(cluster);
						visitaLarg (i, arrayVisitado, cluster);
					}
					else {
						arrayAluno[i].setCluster(countProf);
						visitaLarg (i, arrayVisitado, countProf);
					}//end if						
				}//end if
			}//end for


			
			//testes
			//mostrarArrayArestaAgm(); //funcionando
			//mostrarAgm();
			//for (int i = 0; i < countAlu; i++)
			//	cout << "\n" << "arrayVisitado["<<i<<"] = "<< arrayVisitado[i];
			cout << "\n\n" << "cluster = " << cluster;
			for (int i = 0; i < countAlu; i++)
				cout << "\n" << "aluno["<<(i+1)<<"] = "<< arrayAluno[i].getCluster();
			


		}//end montarCluster


		/** metodo que coloca as arestas da agm em um array e pede pra ordenar*/
		void montarArrayArestaAgm(){
			int k = 0;
			
			arrayArestaAgm = new int [numArestaAgm];	

			for (int i = 0; i < countAlu; i++){				
				for (int j = (i+1); j < countAlu; j++){
					if (agm[i][j] != -1){
						arrayArestaAgm[k] = agm[i][j];
						k++; 
					}//end if
				}//end for								
			}//end for			

			ordenarArrayArestaAgm();
		}//end montarArrayArestaAgm


		/** metodo que mostra o arrayArestaAgm*/
		void mostrarArrayArestaAgm(){		

			for (int i = 0; i < (numArestaAgm); i++)		
				cout << arrayArestaAgm[i] << " ";			
		}//end mostrarArrayArestaAgm


		//Insere elemento na fila, no indice "fim".
		void inserirFila(int elemento) {
   			if (((fimFila + 1) % countAlu) == inicioFila) {
      			cout << "Erro ao inserir!";
   			} 
   			else {
		      arrayFila[fimFila] = elemento;
		      fimFila = (fimFila + 1) % countAlu;
			}
		}//end inserirFila


		//Remove elemento da fila, do indice "inicio".
		int removerFila() {
		   int elemento = NULO;

		   if (inicioFila == fimFila) {
		      //cout << "Erro ao remover!";
		   } 
		   else {
		      elemento = arrayFila[inicioFila];
		      inicioFila = (inicioFila + 1) % countAlu;
		   }		   
		   return elemento;
		}//end removerFila


		//Mostra os array separados por espacos.
		void mostrarFila() {
		   printf("[ ");

		   int i = inicioFila;
		   while (i != fimFila) {
		      printf("%d ", arrayFila[i]);
		      i = ((i + 1) % countAlu); // Fila circular.
		   }

		   printf("] \n");
		}




		


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
			montarArrayAresta();
			//mostrarGrafo();
			montarAgm();
			//mostrarAgm();
			//mostrarArrayAresta();
			montarCluster();
			//mostrarAgm();



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
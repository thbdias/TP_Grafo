#include <stdio.h>
using namespace std;

int main(void)
{
	char url[]="notas.txt";
	float nota,
	      media=0.0;
	FILE *arq;
	
	arq = fopen(url, "w");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		printf("Nota de Matematica: ");
		scanf("%f", &nota);
		fprintf(arq, "Matematica: %.2f\n", nota);
		media+=nota;
		
		printf("Nota de Fisica: ");
		scanf("%f", &nota);
		fprintf(arq, "Fisica: %.2f\n", nota);
		media+=nota;
		
		printf("Nota de Quimica: ");
		scanf("%f", &nota);
		fprintf(arq, "Quimica: %.2f\n", nota);
		media+=nota;
		
		media /= 3;
		fprintf(arq, "Media final: %.2f\n", media);
	}
	fclose(arq);
	
	return 0;
}
#include <iostream>
using namespace std;

void gravar (int ma [][3], int n){

	for (int i = 0; i < n; i++){
		for (int j = 0; j < 3; j++){
			ma[i][j] = 2;
		}
	}

}




int main(){
	int matriz [2][3];

	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++){
			matriz[i][j] = -1;
		}
	}

	gravar (matriz, 2);

	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++){
			cout << " " << matriz[i][j];
		}
		cout << "\n";
	}

}//end main
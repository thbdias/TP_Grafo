// Arquivo main.cpp

#include <iostream>
using namespace std;
#include "Cachorro.h"

int main(void) {
    Cachorro cachorro;
    cachorro.tamanho = 40;
    cachorro.raca = "Doberman";
    cachorro.nome = "Rex"; // Muito criativo, não?

    cachorro.latir();

    return 0;
}
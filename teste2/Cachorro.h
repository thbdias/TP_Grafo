// Arquivo cachorro.h
#ifndef CACHORRO_H
#define CACHORRO_H

#include <iostream>
#include <string>
using namespace std;

class Cachorro {
public:
    int tamanho;
    string raca;
    string nome;

    Cachorro();
    ~Cachorro();
    void latir();
};

#endif
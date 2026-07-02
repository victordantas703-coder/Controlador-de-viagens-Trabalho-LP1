#ifndef CLASSE_VIAGEM
#define CLASSE_VIAGEM

#include <iostream>
#include <vector>
#include <cmath>
#include "classeTransporte.h"
#include "classePassageiro.h"
#include "classeCidade.h"
using namespace std;

class Viagem { 
private: 
    Transporte* transporte; 
    vector<Passageiro*> passageiros; 
    Cidade* origem; 
    Cidade* destino;
    Viagem* proxima;
    double horasEmTransito;
    bool emAndamento;
    double distanciaTrajeto; // distancia total da etapa
public: 
    Viagem(Transporte* transporte, vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, double distanciaTrajeto);
    void iniciarViagem(); 
    double avancarHoras(double horas);
    void relatarEstado(); 
    bool isEmAndamento();
    Transporte* getTransporte();
    vector<Passageiro*>& getPassageiros();
    Cidade* getOrigem();
    Cidade* getDestino();
    Viagem* getProxima();
    void setProxima(Viagem* prox);
};

#endif

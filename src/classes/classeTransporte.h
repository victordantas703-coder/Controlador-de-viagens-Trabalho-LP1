#ifndef CLASSE_TRANSPORTE_H
#define CLASSE_TRANSPORTE_H

#include <string>
#include "classeCidade.h"
using namespace std;

class Transporte { 
private: 
    string nome; 
    char tipo; // 'A' para Aquático, 'T' para Terrestre 
    int capacidade; // número de passageiros 
    int velocidade; // km/h 
    int distancia_entre_descansos; // em km 
    int tempo_de_descanso; // em horas 
    int tempo_de_descanso_atual;  // horas restantes de descanso (0 = não descansando)
    Cidade* localAtual;
    double distancia_percorrida_no_trecho; // kms percorridos desde o último descanso
    bool emViagem; // verdadeiro caso esteja em viagem
public: 
    Transporte(string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual); 
    string getNome(); 
    char getTipo(); 
    int getCapacidade(); 
    int getVelocidade(); 
    int getDistanciaEntreDescansos();
    int getTempoDescanso(); 
    int getTempoDescansoAtual();
    Cidade* getLocalAtual(); 
    void setLocalAtual(Cidade* local);
    void setTempoDescansoAtual(int t);
    double getDistanciaPercorridaNoTrecho();
    void setDistanciaPercorridaNoTrecho(double d);
    bool isEmViagem();
    void setEmViagem(bool v);
};

#endif

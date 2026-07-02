#ifndef CLASSE_PASSAGEIRO
#define CLASSE_PASSAGEIRO

#include <string>
#include "classeCidade.h"
using namespace std;

class Passageiro { 
private: 
    string nome; 
    Cidade* localAtual; 
public:
    Passageiro();
    Passageiro(string nome, Cidade* localAtual); 
    string getNome(); 
    Cidade* getLocalAtual(); 
    void setLocalAtual(Cidade* local); 
};

#endif 
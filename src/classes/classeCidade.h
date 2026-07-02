#ifndef CLASSE_CIDADE
#define CLASSE_CIDADE

#include <string>
using namespace std;

class Cidade { 
private: 
    string nome;
    int visitasRecebidas; // Contador de chegadas para poder mostrar as cidades mais visitadas
public: 
    Cidade(string nome);
    Cidade(string nome, int visitas);
    string getNome();
    void registrarVisita();
    int getVisitas();
};

#endif

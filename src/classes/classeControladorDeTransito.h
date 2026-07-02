#ifndef CLASSE_CONTROLADOR_DE_TRANSITO
#define CLASSE_CONTROLADOR_DE_TRANSITO

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <queue>
#include <cmath>
#include <climits>
#include "classeCidade.h"
#include "classeTrajeto.h"
#include "classeTransporte.h"
#include "classePassageiro.h"
#include "classeViagem.h"
using namespace std;

class ControladorDeTransito { 
private: 
    vector<Cidade*> cidades; 
    vector<Trajeto*> trajetos; 
    vector<Transporte*> transportes; 
    vector<Passageiro*> passageiros; 
    vector<Viagem*> viagens;
    vector<Trajeto*> encontrarMelhorRota(Cidade* origem, Cidade* destino, char tipoTransporte);  // Tenta buscar o caminho mais curto entre uma cidade e outra
    void salvarPassageiros();  // Atualiza o local onde os passageiros chegaram no arquivo de cadastro dos passageiros ao terminar a viagem
    void salvarTransporte();  // Atualiza o local onde o transporte chegou no arquivo de cadastro de transportes ao terminar a viagem
    void salvarVisitas();  // Atualiza número de visitas de uma cidade no arquivo de cadastro ao terminar a viagem
public:
    ControladorDeTransito(); // Carrega todos os dados cadastrados ao iniciar o programa
    void cadastrarCidade(string nome); 
    void cadastrarTrajeto(string nomeOrigem, string nomeDestino, char tipo, int distancia); 
    void cadastrarTransporte(string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, string localAtual);
    void cadastrarPassageiro(string nome, string localAtual); 
    void iniciarViagem(string nomeTransporte, vector<string> nomesPassageiros, string nomeOrigem, string nomeDestino); 
    void avancarHoras(int horas); 
    void relatarEstado(); 
};

#endif

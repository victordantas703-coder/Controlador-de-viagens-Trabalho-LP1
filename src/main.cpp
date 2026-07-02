#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

#include "classes/classeControladorDeTransito.h"

int main(){

    ControladorDeTransito controlador;

    string comando;

    while (cin >> comando) {

        if (comando == "fim") {
            break;  // Termina o programa
        }
        else if (comando == "cadastrar_cidade") {
            string linha;
            getline(cin >> ws, linha);

            stringstream ss(linha);
            string cidade;

            if(!(ss >> quoted(cidade))){  // Condição para que a entrada fique no formato exato
                cout << ">- Erro: Formato de entrada inválido." << endl;
            }

            string extra;
            if (ss >> extra) {  // Condição para caso a entrada tenha parâmetros extras
                cout << ">- Erro: Parâmetros extras encontrados." << endl;
            }
            else controlador.cadastrarCidade(cidade); // Função para cadastrar cidade

        }
        else if (comando == "cadastrar_trajeto") {
            string linha;
            string extra;
            getline(cin >> ws, linha);

            stringstream ss(linha);

            string origem, destino;
            char tipo;
            int distancia;

            if (!(ss >> quoted(origem) >> quoted(destino) >> tipo >> distancia)) {
                cout << ">- Erro: Formato de entrada inválido." << endl;
            }
            else if (ss >> extra) {
                cout << ">- Erro: Parâmetros extras encontrados." << endl;
            }
            else if (origem == destino) {
                cout << ">- Erro: A cidade de origem e destino não podem ser iguais." << endl;
            }
            else if (tipo != 'A' && tipo != 'T') {
                cout << ">- Erro: Tipo de trajeto indefinido. Use T para terrestre ou A para aquático." << endl;
            }
            else if (distancia < 1) {
                cout << ">- Erro: Distância entre cidades menor ou igual a 0." << endl;
            }
            else controlador.cadastrarTrajeto(origem, destino, tipo, distancia); // Função para cadastrar trajeto
            
        }
        else if (comando == "cadastrar_transporte") {
            string linha;
            string extra;
            getline(cin >> ws, linha);

            stringstream ss(linha);

            string nomeTransporte, localAtual;
            char tipo;
            int capacidade, velocidade, distanciaEntreDescansos, tempoDeDescanso;

            if (!(ss >> quoted(nomeTransporte) >> tipo >> capacidade >> velocidade >> distanciaEntreDescansos >> tempoDeDescanso >> quoted(localAtual))) {
                cout << ">- Erro: Formato de entrada inválido." << endl;
            } 
            else if (ss >> extra) {
                cout << ">- Erro: Parâmetros extras encontrados." << endl;
            }
            else if (tipo != 'A' && tipo != 'T') {
                cout << ">- Erro: Tipo de transporte indefinido. Use T para terrestre ou A para aquático." << endl;
            }
            else if (capacidade < 1) {
                cout << ">- Erro: Capacidade do transporte menor ou igual a 0." << endl;
            }
            else if (velocidade < 1) {
                cout << ">- Erro: Velocidade do transporte menor ou igual a 0." << endl;
            }
            else if (distanciaEntreDescansos < 0) {
                cout << ">- Erro: Distância entre descansos do transporte menor do que 0." << endl;
            }
            else if (tempoDeDescanso < 0) {
                cout << ">- Erro: Tempo de descanso do transporte menor do que 0." << endl;
            }
            else controlador.cadastrarTransporte(nomeTransporte, tipo, capacidade, velocidade, distanciaEntreDescansos, tempoDeDescanso, localAtual); // Função para cadastrar transporte

        }
        else if (comando == "cadastrar_passageiro") {
            string linha;
            string extra;
            getline(cin >> ws, linha);

            stringstream ss(linha);

            string nomePassageiro, localAtual;
            if(!(ss >> quoted(nomePassageiro) >> quoted(localAtual))){
                cout << ">- Erro: Formato de entrada inválido." << endl;
            } 
            else if (ss >> extra) {
                cout << ">- Erro: Parâmetros extras encontrados." << endl;
            }
            else controlador.cadastrarPassageiro(nomePassageiro, localAtual); // Função para cadastrar passageiro

        }
        else if (comando == "iniciar_viagem") {
            string linha;
            getline(cin >> ws, linha);

            stringstream ss(linha);

            string nomeTransporte;
            int numPassageiros;
            vector<string> nomesPassageiros;
            string nomeOrigem, nomeDestino;

            bool validacaoEntrada = true;

            if (!(ss >> quoted(nomeTransporte) >> numPassageiros)) {
                validacaoEntrada = false;
            }

            for (int i = 0; i < numPassageiros; i++) {
                string nome;

                if (!(ss >> quoted(nome))) {
                    validacaoEntrada = false;
                }

                nomesPassageiros.push_back(nome);
            }

            if (!(ss >> quoted(nomeOrigem) >> quoted(nomeDestino))) {
                validacaoEntrada = false;
            }

            string resto;
            if (ss >> resto) {
                cout << ">- Erro: Parâmetros extras encontrados." << endl;
                validacaoEntrada = false;
            }

            if (!validacaoEntrada) cout << ">- Erro: formato inválido." << endl;
            else if (nomeOrigem == nomeDestino) {
                cout << ">- Erro: A cidade de origem e destino não podem ser iguais." << endl;
            }
            else if (numPassageiros < 1) {
                cout << ">- Erro: Número de passageiros menor ou igual a 0." << endl;
            }
            else if (nomesPassageiros.size() != numPassageiros) {
                cout << ">- Erro: Número de passageiros não corresponde à quantidade de nomes." << endl;
            }
            else controlador.iniciarViagem(nomeTransporte, nomesPassageiros, nomeOrigem, nomeDestino); // Função para iniciar viagem
        }
        else if (comando == "avancar_horas") {
            string linha;
            string extra;
            getline(cin >> ws, linha);

            stringstream ss(linha);
            
            int horas;

            if (!(ss >> horas)) {
                cout << ">- Erro: Formato de entrada inválido." << endl;
            }
            else if (ss >> extra) {
                cout << ">- Erro: Parâmetros extras encontrados." << endl;
            }
            else if (horas < 1) {
                cout << ">- Erro: Número de horas menor ou igual a 0." << endl;
            }
            else controlador.avancarHoras(horas); // Função para avançar horas

        }
        else if (comando == "relatar_estado") {
            controlador.relatarEstado(); // Função para relatar estado do sistema
        }
          
    }
}
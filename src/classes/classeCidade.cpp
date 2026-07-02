#include "classeCidade.h"

Cidade::Cidade(string nome) {
    this->nome = nome;
    this->visitasRecebidas = 0;
}

Cidade::Cidade(string nome, int visitas) {
    this->nome = nome;
    this->visitasRecebidas = visitas;
}

string Cidade::getNome() {
    return nome;
}

void Cidade::registrarVisita() {
    visitasRecebidas++;
}

int Cidade::getVisitas() {
    return visitasRecebidas;
}

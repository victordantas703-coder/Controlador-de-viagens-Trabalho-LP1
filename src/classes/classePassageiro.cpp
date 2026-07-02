#include "classePassageiro.h"

Passageiro::Passageiro() {}

Passageiro::Passageiro(string nome, Cidade* localAtual) {
    this->nome = nome;
    this->localAtual = localAtual;
}

string Passageiro::getNome() {
    return this->nome;
}

Cidade* Passageiro::getLocalAtual() {
    return this->localAtual;
}

void Passageiro::setLocalAtual(Cidade* local) {
    this->localAtual = local;
}
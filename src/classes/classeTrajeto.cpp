#include "classeTrajeto.h"

Trajeto::Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia) {
    this->origem = origem;
    this->destino = destino;
    this->tipo = tipo;
    this->distancia = distancia;
}

Cidade* Trajeto::getOrigem() {
    return this->origem;
}

Cidade* Trajeto::getDestino() {
    return this->destino;
}

char Trajeto::getTipo() {
    return this->tipo;
}

int Trajeto::getDistancia() {
    return this->distancia;
}
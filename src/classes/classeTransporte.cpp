#include "classeTransporte.h"

Transporte::Transporte(string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual) {
    this->nome = nome;
    this->tipo = tipo;
    this->capacidade = capacidade;
    this->velocidade = velocidade;
    this->distancia_entre_descansos = distancia_entre_descansos;
    this->tempo_de_descanso = tempo_de_descanso;
    this->tempo_de_descanso_atual = 0;
    this->distancia_percorrida_no_trecho = 0;
    this->emViagem = false;
    this->localAtual = localAtual;
}

string Transporte::getNome(){
    return nome;
}

char Transporte::getTipo() {
    return tipo;
}

int Transporte::getCapacidade() {
    return capacidade;
}

int Transporte::getVelocidade() {
    return velocidade;
}

int Transporte::getDistanciaEntreDescansos() {
    return distancia_entre_descansos;
}

int Transporte::getTempoDescanso() {
    return tempo_de_descanso;
}

int Transporte::getTempoDescansoAtual() {
    return tempo_de_descanso_atual;
}

Cidade* Transporte::getLocalAtual() {
    return localAtual;
}

void Transporte::setLocalAtual(Cidade* local) {
    this->localAtual = local;
}

void Transporte::setTempoDescansoAtual(int t) {
    tempo_de_descanso_atual = t;
}

double Transporte::getDistanciaPercorridaNoTrecho() {
    return distancia_percorrida_no_trecho;
}

void Transporte::setDistanciaPercorridaNoTrecho(double d) {
    distancia_percorrida_no_trecho = d;
}

bool Transporte::isEmViagem() {
    return emViagem;
}

void Transporte::setEmViagem(bool v) {
    emViagem = v;
}
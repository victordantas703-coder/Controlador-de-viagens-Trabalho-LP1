#include "classeViagem.h"

Viagem::Viagem(Transporte* transporte, vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, double distanciaTrajeto) {
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;
    this->proxima = nullptr;
    this->horasEmTransito = 0;
    this->emAndamento = false;
    this->distanciaTrajeto = distanciaTrajeto;
}

void Viagem::iniciarViagem() {
    emAndamento = true;
    transporte->setEmViagem(true);
}


// Retorna as horas que sobraram após a viagem terminar, mas se estiver em andamento retorna -1
double Viagem::avancarHoras(double horas) {
    
    // Se não estiver em andamento, não calcula nada
    if (!emAndamento) {
        return -1;
    }

    double horasRestantes = horas;

    // Enquanto estiver horas restantes, avança na viagem
    while (horasRestantes > 0) {

        // Processo de descanso
        if (transporte->getTempoDescansoAtual() > 0) {
            double descansando = transporte->getTempoDescansoAtual();
            
            // Se as horas restantes for maior que o tempo restante de descanço, então o descanço acabou
            if (horasRestantes >= descansando) {
                horasRestantes -= descansando;
                transporte->setTempoDescansoAtual(0);
            }
            // Se não, atualiza o que resta de descanço e retorna que não terminou a viagem
            else {
                transporte->setTempoDescansoAtual((int)(descansando - horasRestantes));
                horasEmTransito += horasRestantes;
                horasRestantes = 0;
                break;
            }
        }
        // Fim do processo de descanço


        // Processo de movimento
        double distanciaPercorrida = transporte->getDistanciaPercorridaNoTrecho();
        double distanciaRestanteViagem = distanciaTrajeto - distanciaPercorrida;

        // Se a distância restante da viagem for 0 ou menor, então quer dizer que chegou no destino e retorna as horas que sobrou dessa viagem para aproveitar na próxima
        if (distanciaRestanteViagem <= 0) {
            emAndamento = false;
            transporte->setEmViagem(false);
            transporte->setDistanciaPercorridaNoTrecho(0);
            destino->registrarVisita();
            return horasRestantes;
        }

        // kms até o próximo descanso
        double kmParaProximoDescanso = transporte->getDistanciaEntreDescansos() - fmod(distanciaPercorrida, transporte->getDistanciaEntreDescansos());
        
        // Se a distâncias entres os descanços for 0, então deixa como até o final da viagem
        if (transporte->getDistanciaEntreDescansos() == 0) {
            kmParaProximoDescanso = distanciaRestanteViagem;
        }

        
        double kmPossiveisNestaHora = transporte->getVelocidade() * horasRestantes;  // O que pode pecorrer com as horas que tem

        // Verifica se o que vai pecorrer termina a viagem
        if (kmPossiveisNestaHora >= distanciaRestanteViagem) {

            // Verifica se tem um descanço no caminho
            if (kmPossiveisNestaHora >= kmParaProximoDescanso && kmParaProximoDescanso < distanciaRestanteViagem) {
                double horasAteDescanso = kmParaProximoDescanso / transporte->getVelocidade();
                horasEmTransito += horasAteDescanso;
                horasRestantes -= horasAteDescanso;
                transporte->setDistanciaPercorridaNoTrecho(distanciaPercorrida + kmParaProximoDescanso);
                transporte->setTempoDescansoAtual(transporte->getTempoDescanso());
            }
            
            // Se não, quer dizer que chegou no destino da viagem
            else {
                double horasAteDestino = distanciaRestanteViagem / transporte->getVelocidade();
                horasEmTransito += horasAteDestino;
                horasRestantes -= horasAteDestino;
                transporte->setDistanciaPercorridaNoTrecho(0);
                emAndamento = false;
                transporte->setEmViagem(false);
                destino->registrarVisita();
                return horasRestantes;
            }
        }

        // Se o que vai andar não teminar a viagem, verifica também se vai ter descanço
        else {
            if (kmPossiveisNestaHora >= kmParaProximoDescanso) {
                double horasAteDescanso = kmParaProximoDescanso / transporte->getVelocidade();
                horasEmTransito += horasAteDescanso;
                horasRestantes -= horasAteDescanso;
                transporte->setDistanciaPercorridaNoTrecho(distanciaPercorrida + kmParaProximoDescanso);
                transporte->setTempoDescansoAtual(transporte->getTempoDescanso());
            }
            else {
                transporte->setDistanciaPercorridaNoTrecho(distanciaPercorrida + kmPossiveisNestaHora);
                horasEmTransito += horasRestantes;
                horasRestantes = 0;
            }
        }
        // Fim do processo de movimento
    }
    

    return -1; // Ainda em andamento
}

void Viagem::relatarEstado() {
    cout << "  Transporte : " << transporte->getNome() << endl;
    cout << "  Trecho     : " << origem->getNome() << " -> " << destino->getNome() << endl;
    cout << "  Distância  : " << distanciaTrajeto << " km" << endl;
    cout << "  Percorrido : " << transporte->getDistanciaPercorridaNoTrecho() << " km" << endl;
    cout << "  Passageiros: " << endl;
    for (auto p : passageiros) {
        cout << "   > " << p->getNome() << endl;
    }
    cout << endl;
}

bool Viagem::isEmAndamento() {
    return emAndamento;
}

Viagem* Viagem::getProxima() {
    return proxima;
}

void Viagem::setProxima(Viagem* prox) {
    proxima = prox;
}
Transporte* Viagem::getTransporte() {
    return transporte;
}
vector<Passageiro*>& Viagem::getPassageiros() {
    return passageiros;
}
Cidade* Viagem::getOrigem() {
    return origem;
}
Cidade* Viagem::getDestino() {
    return destino;
}

#include "classeControladorDeTransito.h"

ControladorDeTransito::ControladorDeTransito() {

    // Abre arquivo de cidades e carrega as cidades existentes
    // Cadastro das cidades: <nome_da_cidade>
    ifstream arquivoCidades("cadastros/cidades.txt");

    if(arquivoCidades.is_open()) {
        string linha;
        while(getline(arquivoCidades, linha)) {
            if(linha.empty()) continue;
            
            stringstream ss(linha);
            string nomeCiade, visitas;

            getline(ss, nomeCiade, '|');
            getline(ss, visitas, '|');

            int visitasInt = stoi(visitas);

            this->cidades.push_back(new Cidade(nomeCiade, visitasInt));
        }
        arquivoCidades.close();
    }
    for (auto& cidade : this->cidades){
        cout << ">- Cidade carregada: " << cidade->getNome() << " (" << cidade->getVisitas() << (cidade->getVisitas() == 1? " visita)" : " visitas)" ) << endl;
    }


    // Abre arquivo de trajetos e carrega os trajetos existentes
    // Cadastro dos trajetos: <nome_da_cidade_origem>|<nome_da_cidade_destino>|<tipo_de_transporte>|<distancia_em_km>
    ifstream arquivoTrajetos("cadastros/trajetos.txt");

    if(arquivoTrajetos.is_open()) {
        string linha;
        while(getline(arquivoTrajetos, linha)) {
            if(linha.empty()) continue;

            stringstream ss(linha);
            string nomeOrigem, nomeDestino, tipoStr, distanciaStr;
            
            getline(ss, nomeOrigem, '|');
            getline(ss, nomeDestino, '|');
            getline(ss, tipoStr, '|');
            getline(ss, distanciaStr);

            char tipo = tipoStr[0];
            int distancia = stoi(distanciaStr);

            Cidade* cidadeOrigemEndereco = nullptr;
            Cidade* cidadeDestinoEndereco = nullptr;
            for(auto& cidade : this->cidades) {
                if(cidade->getNome() == nomeOrigem) {
                    cidadeOrigemEndereco = cidade;
                }
                if(cidade->getNome() == nomeDestino) {
                    cidadeDestinoEndereco = cidade;
                }
            }

            if(cidadeOrigemEndereco && cidadeDestinoEndereco){
                this->trajetos.push_back(new Trajeto(cidadeOrigemEndereco, cidadeDestinoEndereco, tipo, distancia));
            }
        }
        arquivoTrajetos.close();
    }
    for(auto& trajeto : this->trajetos){
        cout << ">- Trajeto carregado: " << trajeto->getOrigem()->getNome() << " -> " << trajeto->getDestino()->getNome()
             << " | Tipo: " << (trajeto->getTipo()=='T'? "terrestre" : "aquático")
             << " | Distância: " << trajeto->getDistancia() << " km"
             << endl;
    }


    // Abre arquivo de transportes e carrega os transportes existentes
    // Cadastro dos transportes: <nome_do_transporte>|<tipo_de_transporte>|<capacidade_em_passageiros>|<velocidade_em_km/h>|<distancia_entre_descansos_em_km>|<tempo_de_descanso_em_horas>|<nome_da_cidade_atual>
    ifstream arquivoTransportes("cadastros/transportes.txt");

    if(arquivoTransportes.is_open()) {
        string linha;
        while(getline(arquivoTransportes, linha)) {
            if(linha.empty()) continue;

            stringstream ss(linha);
            string nome, tipoStr, capacidadeStr, velocidadeStr, distanciaDescStr, tempoDescStr, localAtual;

            getline(ss, nome, '|');
            getline(ss, tipoStr, '|');
            getline(ss, capacidadeStr, '|');
            getline(ss, velocidadeStr, '|');
            getline(ss, distanciaDescStr, '|');
            getline(ss, tempoDescStr, '|');
            getline(ss, localAtual);

            char tipo = tipoStr[0];
            int capacidade = stoi(capacidadeStr);
            int velocidade = stoi(velocidadeStr);
            int distanciaDesc = stoi(distanciaDescStr);
            int tempoDesc = stoi(tempoDescStr);

            Cidade* cidadeLocalAtualEndereco = nullptr;
            for(auto& cidade : this->cidades) {
                if(cidade->getNome() == localAtual) {
                    cidadeLocalAtualEndereco = cidade;
                    break;
                }
            }

            if(cidadeLocalAtualEndereco){
                this->transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distanciaDesc, tempoDesc, cidadeLocalAtualEndereco));
            }
        }
        arquivoTransportes.close();
    }
    for(auto& transporte : this->transportes){
        cout << ">- Transporte carregado: " << transporte->getNome()
             << " | Tipo: " << (transporte->getTipo()=='T'?"terrestre":"aquático")
             << " | Cap: " << transporte->getCapacidade()
             << " | Vel: " << transporte->getVelocidade() << " km/h"
             << " | Local: " << transporte->getLocalAtual()->getNome()
             << endl;
    }
    

    // Abre arquivo de passageiros e carrega os passageiros existentes
    // Cadastro dos passageiros: <nome_do_passageiro>|<nome_da_cidade_atual>
    ifstream arquivoPassageiros("cadastros/passageiros.txt");

    if(arquivoPassageiros.is_open()) {
        string linha;
        while(getline(arquivoPassageiros, linha)) {
            if(linha.empty()) continue;

            stringstream ss(linha);
            string nome, localAtual;
            getline(ss, nome, '|');
            getline(ss, localAtual);

            Cidade* cidadeLocalAtualEndereco = nullptr;
            for(auto& cidade : this->cidades) {
                if(cidade->getNome() == localAtual) {
                    cidadeLocalAtualEndereco = cidade;
                    break;
                }
            }

            if(cidadeLocalAtualEndereco){
                this->passageiros.push_back(new Passageiro(nome, cidadeLocalAtualEndereco));
            }
        }
        arquivoPassageiros.close();
    }
    for(auto& passageiro : this->passageiros){
        cout << ">- Passageiro carregado: " << passageiro->getNome() << " | Local: " << passageiro->getLocalAtual()->getNome() << endl;
    }

}

// Função para cadastrar as cidades
void ControladorDeTransito::cadastrarCidade(string nome) {

    // Inicio de verifição por cidades duplicadas
    ifstream arquivoCidadesDuplicadas("cadastros/cidades.txt");

    if(!arquivoCidadesDuplicadas.is_open()) {
        ofstream arquivoCidades("cadastros/cidades.txt");  // Cria um arquivo para cidades caso não exista

        if(!arquivoCidades.is_open()) {
            cout << ">- Erro ao criar o arquivo de cidades." << endl;
            return;
        }

        cout << ">- Novo arquivo para cadastro de cidades criado." << endl;

        arquivoCidades << nome << endl;  // Escreve o nome da cidade no arquivo

        cout << ">- A cidade " << nome << " foi cadastrada com sucesso." << endl;

        this->cidades.push_back(new Cidade(nome));  // Adiciona a nova cidade no vetor de cidades

        arquivoCidades.close(); // Fecha o arquivo
        return;
    }

    // Verifica se a cidade já está cadastrada
    for(auto& cidade : this->cidades) {
        if(cidade->getNome() == nome) {
            cout << ">- Erro: Cidade já cadastrada." << endl;
            arquivoCidadesDuplicadas.close();  // Fecha o arquivo
            return;
        }
    }

    arquivoCidadesDuplicadas.close();  // Fecha o arquivo
    // Fim de verifição por cidades duplicadas


    ofstream arquivoCidades("cadastros/cidades.txt", ios::app);  // Abre o arquivo em modo de adição

    if(!arquivoCidades.is_open()) {
        cout << ">- Erro ao abrir o arquivo de cidades." << endl;
        return;
    }

    arquivoCidades << nome << '|' << 0 << endl;  // Escreve o nome da cidade e o total de visitas como 0 no arquivo

    cout << ">- A cidade " << nome << " foi cadastrada com sucesso." << endl;

    this->cidades.push_back(new Cidade(nome));  // Adiciona a nova cidade no vetor de cidades

    arquivoCidades.close();  // Fecha o arquivo
}

// Função para cadastrar os trajetos
void ControladorDeTransito::cadastrarTrajeto(string nomeOrigem, string nomeDestino, char tipo, int distancia) {
    
    // Inicio da verificação das cidades no cadastro
    Cidade* cidadeOrigemEndereco = nullptr;
    Cidade* cidadeDestinoEndereco = nullptr;

    if(this->cidades.size() < 2) {
        cout << ">- Erro: Cidades insuficientes." << endl;
        return;
    }

    for(auto& cidade : this->cidades) {
        if(cidade->getNome() == nomeOrigem) cidadeOrigemEndereco = cidade;
        if(cidade->getNome() == nomeDestino) cidadeDestinoEndereco = cidade;
    }

    if(!cidadeOrigemEndereco || !cidadeDestinoEndereco) {
        cout << ">- Erro: Uma ou ambas as cidades não existem." << endl;
        return;
    }
    // Fim da verificação das cidades no cadastro
    
    // Inicio de verifição por trajetos duplicados
    ifstream arquivoTrajetosDuplicados("cadastros/trajetos.txt");

    if(!arquivoTrajetosDuplicados.is_open()) {

        ofstream arquivoTrajetos("cadastros/trajetos.txt");  // Cria um arquivo para o cadastro de trajetos

        if(!arquivoTrajetos.is_open()) {
            cout << ">- Erro ao criar o arquivo de trajetos." << endl;
            return;
        }

        cout << ">- Novo arquivo para cadastro de trajetos criado." << endl;

        arquivoTrajetos << nomeOrigem << "|" << nomeDestino << "|" << tipo << "|" << distancia << endl;  // Escreve os dados do trajeto no arquivo

        cout << ">- Trajeto de " << nomeOrigem << " para " << nomeDestino << " do tipo " << ((tipo == 'T')? "terrestre" : "aquático") << "com distância de" << distancia << " km criado com sucesso." << endl;
        
        this->trajetos.push_back(new Trajeto(cidadeOrigemEndereco, cidadeDestinoEndereco, tipo, distancia));  // Adiciona o novo trajeto no vetor de trajetos

        arquivoTrajetos.close();  // Fecha o arquivo
        
        return;
    }

    // Verifica se o trajeto já está cadastrado
    for(auto& trajeto : this->trajetos) {
        if(trajeto->getOrigem()->getNome() == nomeOrigem && trajeto->getDestino()->getNome() == nomeDestino && trajeto->getTipo() == tipo && trajeto->getDistancia() == distancia) {
            cout << ">- Erro: Trajeto já cadastrado." << endl;
            arquivoTrajetosDuplicados.close();
            return;
        }
    }

    arquivoTrajetosDuplicados.close(); // Fecha o arquivo
    // Fim de verifição por trajetos duplicados

    ofstream arquivoTrajetos("cadastros/trajetos.txt", ios::app);  // Abre o arquivo em modo de adição

    if(!arquivoTrajetos.is_open()) {
        cout << ">- Erro ao abrir o arquivo de trajetos." << endl;
        return;
    }

    arquivoTrajetos << nomeOrigem << "|" << nomeDestino << "|" << tipo << "|" << distancia << endl;  // Escreve os dados do trajeto no arquivo

    cout << ">- Trajeto de " << nomeOrigem << " para " << nomeDestino << " do tipo " << ((tipo == 'T')? "terrestre" : "aquático") << " com distância de " << distancia << " km criado com sucesso." << endl;
    
    this->trajetos.push_back(new Trajeto(cidadeOrigemEndereco, cidadeDestinoEndereco, tipo, distancia));  // Adiciona o novo trajeto no vetor de trajetos

    arquivoTrajetos.close();  // Fecha o arquivo
    
    return;
}

// Função para cadastrar os transportes
void ControladorDeTransito::cadastrarTransporte(string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, string localAtual) {
    
    // Verificação da cidade no cadastro
    Cidade* cidadeLocalAtualEndereco = nullptr;
    for(auto& cidade : this->cidades) {
        if(cidade->getNome() == localAtual) {
            cidadeLocalAtualEndereco = cidade;
            break;
        }
    }
    if(!cidadeLocalAtualEndereco) {
        cout << ">- Erro: A cidade de local atual não existe." << endl;
        return;
    }
    
    // Inicio de verifição por transportes duplicados
    ifstream arquivoTransportesDuplicados("cadastros/transportes.txt");

    if(!arquivoTransportesDuplicados.is_open()) {

        ofstream arquivoTransportes("cadastros/transportes.txt");  // Cria um arquivo para cadastro de transportes

        if(!arquivoTransportes.is_open()) {
            cout << ">- Erro ao criar o arquivo de transportes." << endl;
            return;
        }

        arquivoTransportes << nome << "|" << tipo << "|" << capacidade << "|" << velocidade << "|" << distancia_entre_descansos << "|" << tempo_de_descanso << "|" << localAtual << endl;  // Escreve os dados do transporte no arquivo
        
        cout << ">- Transporte " << nome << " do tipo " << ((tipo == 'T')? "terrestre" : "aquático") << " com características:" << endl;
        cout << "    > Capacidade: " << capacidade << " passageiros" << endl;
        cout << "    > Velocidade: " << velocidade << " km/h" << endl;
        cout << "    > Distância entre descansos: " << distancia_entre_descansos << " km" << endl;
        cout << "    > Tempo entre descansos: " << tempo_de_descanso << " h" << endl;
        cout << "    > Localização: " << localAtual << endl;
        cout << "   cadastrado com sucesso." << endl;

        this->transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, cidadeLocalAtualEndereco));  // Adiciona o novo transporte ao vetor de transportes
        
        arquivoTransportes.close();  // Fecha o arquivo
        
        return;
    }

    // Verifica se o transporte está cadastrado
    for(auto& t : this->transportes) {
        if(t->getNome() == nome) {
            cout << ">- Erro: Transporte já cadastrado." << endl;
            arquivoTransportesDuplicados.close();
            return;
        }
    }

    arquivoTransportesDuplicados.close();  // Fecha o arquivo
    // Fim de verifição por transportes duplicados


    ofstream arquivoTransportes("cadastros/transportes.txt", ios::app);  // Abre o arquivo em modo de adição

    if(!arquivoTransportes.is_open()) {
        cout << ">- Erro ao abrir o arquivo de transportes." << endl;
        return;
    }

    arquivoTransportes << nome << "|" << tipo << "|" << capacidade << "|" << velocidade << "|" << distancia_entre_descansos << "|" << tempo_de_descanso << "|" << localAtual << endl;  // Escreve os dados do transporte no arquivo
    
    cout << ">- Transporte " << nome << " do tipo " << ((tipo == 'T')? "terrestre" : "aquático") << " com características:" << endl;
    cout << "    > Capacidade: " << capacidade << " passageiros" << endl;
    cout << "    > Velocidade: " << velocidade << " km/h" << endl;
    cout << "    > Distância entre descansos: " << distancia_entre_descansos << " km" << endl;
    cout << "    > Tempo entre descansos: " << tempo_de_descanso << " h" << endl;
    cout << "    > Localização: " << localAtual << endl;
    cout << "   cadastrado com sucesso." << endl;

    this->transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, cidadeLocalAtualEndereco));  // Adiciona o novo transporte ao vetor de transportes
    
    arquivoTransportes.close();  // Fecha o arquivo
    
    return;
}

// Função para cadastrar os passageiros
void ControladorDeTransito::cadastrarPassageiro(string nome, string localAtual) {
    
    // Verificação da cidade no cadastro
    Cidade* cidadeLocalAtualEndereco = nullptr;
    for(auto& cidade : this->cidades) {
        if(cidade->getNome() == localAtual) {
            cidadeLocalAtualEndereco = cidade;
            break;
        }
    }
    if(!cidadeLocalAtualEndereco) {
        cout << ">- Erro: A cidade de local atual não existe." << endl;
        return;
    }

    // Inicio de verifição por passageiros duplicados
    ifstream arquivoPassageirosDuplicados("cadastros/passageiros.txt");

    if(!arquivoPassageirosDuplicados.is_open()) {

        ofstream arquivoPassageiros("cadastros/passageiros.txt");  // Cria um arquivo para o cadastro de passageiros

        if(!arquivoPassageiros.is_open()) {
            cout << ">- Erro ao criar o arquivo de passageiros." << endl;
            return;
        }

        arquivoPassageiros << nome << "|" << localAtual << endl;  // Escreve os dados do passageiro no arquivo

        cout << ">- Passageiro " << nome << " em " << localAtual << " cadastrado com sucesso." << endl;

        this->passageiros.push_back(new Passageiro(nome, cidadeLocalAtualEndereco));  // Adiciona o novo passageiro no vetor de passageiros

        arquivoPassageiros.close();  // Fecha o arquivo
        
        return;
    }

    for(auto& passageiro : this->passageiros) {
        if(passageiro->getNome() == nome) {
            cout << ">- Erro: Passageiro já cadastrado." << endl;
            arquivoPassageirosDuplicados.close();
            return;
        }
    }

    arquivoPassageirosDuplicados.close();  // Fecha o arquivo
    // Fim de verifição por passageiros duplicados


    ofstream arquivoPassageiros("cadastros/passageiros.txt", ios::app);  // Abre o arquivo em modo de adição

    if(!arquivoPassageiros.is_open()) {
        cout << ">- Erro ao abrir o arquivo de passageiros." << endl;
        return;
    }

    arquivoPassageiros << nome << "|" << localAtual << endl;  // Escreve os dados do passageiro no arquivo

    cout << ">- Passageiro " << nome << " em " << localAtual << " cadastrado com sucesso." << endl;

    this->passageiros.push_back(new Passageiro(nome, cidadeLocalAtualEndereco));  // Adiciona o novo passageiro no vetor de passageiros

    arquivoPassageiros.close();  // Fecha o arquivo
    
    return;
}

// Função para encontrar a melhor caminho entre uma cidade e outra
vector<Trajeto*> ControladorDeTransito::encontrarMelhorRota(Cidade* origem, Cidade* destino, char tipo) {
    
    map<Cidade*, int> distanciaMinima;  // Dicionário para encontrar a distancia mínima até uma cidade chave
    map<Cidade*, Trajeto*> trajetoParaDestino; // Indica qual trajeto levou para uma cidade chave
    map<Cidade*, Cidade*> cidadePai;  // Cidade que levou a essa cidade chave

    // Marca todas as cidades com distância máxima
    for(auto& cidade : this->cidades) {
        distanciaMinima[cidade] = INT_MAX;
    }

    distanciaMinima[origem] = 0;  // Marca a cidade de origem com distância mínima

    // Min-heap (distancia, cidade)
    priority_queue<pair<int,Cidade*>, vector<pair<int,Cidade*>>, greater<pair<int,Cidade*>>> minHeap;
    
    minHeap.push({0, origem});  // Calculo da menor distância parte da origem

    while(!minHeap.empty()) {
        auto [distancia, cidade] = minHeap.top(); // Retorna o par com a menor distância
        minHeap.pop();  

        if(distancia > distanciaMinima[cidade]) continue;  // Ignora distâncias maiores para uma cidade

        for(auto& trajeto : this->trajetos) {

            // Só usa trajeto compatível com o tipo e com a origem sendo analisada
            if(trajeto->getTipo() != tipo) continue;
            if(trajeto->getOrigem() != cidade) continue;

            // Pega a cidade destino do trajeto e calcula a distância nova encontrada de uma origem até esse destino
            Cidade* destinoTrajeto = trajeto->getDestino();
            int novaDistancia = distanciaMinima[cidade] + trajeto->getDistancia();

            // Verifica se essa distância calculada é a menor já encontrada
            if(novaDistancia < distanciaMinima[destinoTrajeto]) {
                distanciaMinima[destinoTrajeto] = novaDistancia;  // Atualiza a menor distância até esse destino
                trajetoParaDestino[destinoTrajeto] = trajeto;  // Registra o trajeto que levou até esse destino
                cidadePai[destinoTrajeto] = cidade;  // Registra a cidade que levou até esse destino
                minHeap.push({novaDistancia, destinoTrajeto});  // Insere esse destino com a nova distância no min-heap para calcular novamente com os caminhos vizinhos
            }
        }
    }

    // Se a distância para o destino continuar como o máximo, então o caminho para ele não foi calculado e por isso ficou como o máximo
    if(distanciaMinima[destino] == INT_MAX) return {};  

    // Cria o trajeto do melhor caminho encontrado da origem até o destino
    vector<Trajeto*> melhorCaminho;
    Cidade* atual = destino;
    while(atual != origem) {
        melhorCaminho.push_back(trajetoParaDestino[atual]);  // Vai adicionando os trajetos que levaram a cidade atual/destino
        atual = cidadePai[atual];
    }
    reverse(melhorCaminho.begin(), melhorCaminho.end());  // Como a referência para a construção do caminho foi o destino, inverte o vetor para ficar origem -> destino

    return melhorCaminho;
}

// Salva no cadastro o local onde os passageiros chegaram
void ControladorDeTransito::salvarPassageiros() {
    
    ofstream arquivoPassageiros("cadastros/passageiros.txt");

    if(!arquivoPassageiros.is_open()) {
        cout << ">- Erro ao abrir o arquivo de passageiros." << endl;
        return;
    }

    // Substitui os cadastros dos passageiros para atualizar onde eles chegaram
    for(auto& passageiro : this->passageiros){
        arquivoPassageiros << passageiro->getNome() << "|" << passageiro->getLocalAtual()->getNome() << endl;
    }

    arquivoPassageiros.close();  // Fecha o arquivo 
}

// Salva no cadastro o local onde o transporte chegou
void ControladorDeTransito::salvarTransporte() {
    
    ofstream arquivoTransportes("cadastros/transportes.txt");

    if(!arquivoTransportes.is_open()) {
        cout << ">- Erro ao abrir o arquivo de transportes." << endl;
        return;
    }

    // Substitui os cadastros dos trasnportes para atualizar onde ele chegou
    for(auto& transporte : this->transportes){
        arquivoTransportes << transporte->getNome() << "|" << transporte->getTipo() << "|" << transporte->getCapacidade() << "|" << transporte->getVelocidade() << "|" << transporte->getDistanciaEntreDescansos() << "|" << transporte->getTempoDescanso() << "|" << transporte->getLocalAtual()->getNome() << endl;  // Escreve os dados do transporte no arquivo
    }

    arquivoTransportes.close();  // Fecha o arquivo 
}

// Atualiza no arquivo de cadastro o número de visitas das cidades
void ControladorDeTransito::salvarVisitas() {
    
    ofstream arquivoCidades("cadastros/cidades.txt");

    if(!arquivoCidades.is_open()) {
        cout << ">- Erro ao abrir o arquivo de cidades." << endl;
        return;
    }

    // Substitui os cadastros das cidades para atualizar o número de visitas
    for(auto& cidade : this->cidades){
        arquivoCidades << cidade->getNome() << "|" << cidade->getVisitas() << endl;
    }

    arquivoCidades.close();  // Fecha o arquivo 
}

void ControladorDeTransito::iniciarViagem(string nomeTransporte, vector<string> nomesPassageiros, string nomeOrigem, string nomeDestino) {
    
    // Verifica se o transporte está cadastrado
    Transporte* transporteCadastrado = nullptr;
    for(auto& transporte : this->transportes) {
        if(transporte->getNome() == nomeTransporte) {
            transporteCadastrado = transporte;
            break;
        }
    }
    if(!transporteCadastrado) {
        cout << ">- Erro: Transporte " << nomeTransporte << " não cadastrado no sistema." << endl;
        return;
    }

    // Verifica se o trasporte está em viagem
    if(transporteCadastrado->isEmViagem()) {
        cout << ">- Erro: Transporte " << nomeTransporte << " está em viagem." << endl;
        return;
    }

    // Inicio da verificação das cidades no cadastro
    Cidade* cidadeOrigemEndereco = nullptr;
    Cidade* cidadeDestinoEndereco = nullptr;

    if(this->cidades.size() < 2) {
        cout << ">- Erro: Cidades insuficientes." << endl;
        return;
    }

    for(auto& cidade : this->cidades) {
        if(cidade->getNome() == nomeOrigem) cidadeOrigemEndereco = cidade;
        if(cidade->getNome() == nomeDestino) cidadeDestinoEndereco = cidade;
    }

    if(!cidadeOrigemEndereco || !cidadeDestinoEndereco) {
        cout << ">- Erro: Uma ou ambas as cidades não existem." << endl;
        return;
    }
    // Fim da verificação das cidades no cadastro

    // Verifica se o transporte está na origem
    if(transporteCadastrado->getLocalAtual() != cidadeOrigemEndereco) {
        cout << ">- Erro: Transporte " << nomeTransporte << " não está em " << nomeOrigem << "." << endl;
        return;
    }

    // Verifica se os passageiros estão cadastrados e se estão na origem
    bool verficacaoPassageiros = true;
    vector<Passageiro*> passageirosViagem;
    for(auto& passageiroDaViagem : nomesPassageiros) {
        Passageiro* passageiro = nullptr;

        // Verifica se o passageiro está cadastrado
        for(auto& passageiroVerificacao : this->passageiros) {
            if(passageiroVerificacao->getNome() == passageiroDaViagem) {
                passageiro = passageiroVerificacao;
                break;
            }
        }
        if(!passageiro) {
            cout << ">- Erro: Passageiro " << passageiroDaViagem << " não cadastrado." << endl;
            verficacaoPassageiros = false;
        }

        // Verifica se o passageiro está na origem
        if(passageiro){
            if(passageiro->getLocalAtual() != cidadeOrigemEndereco) {
                cout << ">- Erro: Passageiro " << passageiroDaViagem << " não está em " << nomeOrigem << "." << endl;
                verficacaoPassageiros = false;
            }
        }
        
        if(verficacaoPassageiros) passageirosViagem.push_back(passageiro);
    }
    if(!verficacaoPassageiros) return;

    // Verifica se a quantidade de passageiros para a viagem cabe no transporte da viagem
    if(passageirosViagem.size() > transporteCadastrado->getCapacidade()) {
        cout << ">- Erro: Número de passageiros incompatível com a capacidade do transporte." << endl;
        return;
    }

    // Verifica se existe um caminho entre essas duas cidades, se sim pega o menor caminho
    vector<Trajeto*> caminho = encontrarMelhorRota(cidadeOrigemEndereco, cidadeDestinoEndereco, transporteCadastrado->getTipo());
    if(caminho.empty()) {
        cout << ">- Erro: Não existe um caminho de " << nomeOrigem << " até " << nomeDestino << " do tipo " << (transporteCadastrado->getTipo()=='T'? "terrestre" : "aquático") << "." << endl;
        return;
    }

    // Cria o encadeamento de trajetos para fazer o caminho
    Viagem* primeiraViagem = nullptr;
    Viagem* trajetoParaDestino = nullptr;
    for(auto& trajeto : caminho) {
        Viagem* viagemCadeia = new Viagem(transporteCadastrado, passageirosViagem, trajeto->getOrigem(), trajeto->getDestino(), (double)trajeto->getDistancia());
        if(!primeiraViagem) primeiraViagem = viagemCadeia;
        if(trajetoParaDestino) trajetoParaDestino->setProxima(viagemCadeia);
        trajetoParaDestino = viagemCadeia;
    }

    // Inicia a viagem
    primeiraViagem->iniciarViagem();
    this->viagens.push_back(primeiraViagem);

    cout << ">- Viagem iniciada: Transporte: " << nomeTransporte << ". De " << nomeOrigem << " para " << nomeDestino;
    if(caminho.size() > 1) {
        cout << " (com " << caminho.size() - 1 << (caminho.size() - 1 == 1? " conexão: " : " conexões: ");
        for(int i = 1; i < caminho.size(); i++){
            cout << caminho[i]->getOrigem()->getNome() << (i<caminho.size()-1?", ":"");
        }
        cout << ")";
    }
    cout << endl;
    cout << "   Passageiros: " << endl;
    for(auto& passageiro : passageirosViagem) {
        cout << "    > " << passageiro->getNome() << endl;
    }
    cout << endl;
}

// Função para avançar as horas do sistema
void ControladorDeTransito::avancarHoras(int horas) {
    
    cout << ">- Avançando " << horas << (horas == 1?" hora..." : " horas...") << endl;

    // Avança todas as viagens do vetor de viagens
    for(auto& viagem : this->viagens) {
        
        Viagem* etapaAtual = viagem;

        while(etapaAtual && !etapaAtual->isEmAndamento()) {
            etapaAtual = etapaAtual->getProxima();
        }
        if(!etapaAtual) continue; // Se após pegar a próxima viagem der um nullptr, então a cadeia chegou no final

        double horasRestantes = (double)horas;

        // Avança pelas etapas enquanto houver horas sobrando
        while(etapaAtual && horasRestantes > 0) {
            double sobra = etapaAtual->avancarHoras(horasRestantes);

            if(sobra < 0.0) {
                horasRestantes = 0;  // Etapa ainda em andamento
            }
            else {
                // Transporte chegou ao destino da etapa
                Cidade* cidadeChegada = etapaAtual->getDestino();
                cout << ">- " << etapaAtual->getTransporte()->getNome() << " chegou a " << cidadeChegada->getNome() << "." << endl;

                // Inicio da verificação para saber se ainda tem outra etapa
                Viagem* proximaViagem = etapaAtual->getProxima();
                
                // Se tiver outra etapa, inicia com as horas restantes
                if(proximaViagem) {
                    proximaViagem->iniciarViagem();
                    etapaAtual = proximaViagem;
                    horasRestantes = sobra;
                }
        
                // Se não tiver, então a viagem acabou e ignora as horas restantes
                else {
                    Cidade* destinoFinal = cidadeChegada;

                    etapaAtual->getTransporte()->setLocalAtual(destinoFinal);

                    for(auto& passageiro : etapaAtual->getPassageiros()) {
                        passageiro->setLocalAtual(destinoFinal);
                    }

                    cout << ">- Viagem concluida! Passageiros chegaram a " << destinoFinal->getNome() << "." << endl;

                    salvarPassageiros();  // Salva no cadastro o local onde os passageiros chegaram
                    salvarTransporte();  // Salva no cadastro o local onde o transporte chegou
                    salvarVisitas(); // Atualiza o número de visitas das cidades visitadas

                    etapaAtual = nullptr;
                    horasRestantes = 0;
                }
                // Fim da verificação para saber se ainda tem outra etapa
            }
        }
    }

    // Remove viagens em que a cadeia foi concluida
    viagens.erase(
        remove_if(viagens.begin(), viagens.end(), [](Viagem* viagem) {
            // Uma cadeia está concluída se nenhuma etapa está em andamento
            Viagem* atual = viagem;
            while(atual) {
                if(atual->isEmAndamento()) {
                    return false;
                }
                atual = atual->getProxima();
            }
            return true;
        }),
        viagens.end()
    );
}

// Função para relatar estado do sistema
void ControladorDeTransito::relatarEstado() {

    cout << "\n========================================" << endl;

    cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << "|         Relatório do Sistema        |" << endl;
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;


    cout << "\n-*-*- Passageiros -*-*-" << endl;

    // Busca pelas viagens quais passageiros estão em trânsito e em qual viagem da cadeia
    map<Passageiro*, Viagem*> passageirosEmTransito;
    for(auto& viagem : this->viagens) {
        Viagem* atual = viagem;
        
        // Procura pela cadeia a viagem que está em andamento
        while(atual) {
            if(atual->isEmAndamento()) {
                for(auto& passageiroViagem : atual->getPassageiros()) {
                    passageirosEmTransito[passageiroViagem] = atual;
                }
                break;
            }
            atual = atual->getProxima();  // Se a viagem atual não estiver em andamento, pega a próxima da cadeia
        }
    }

    // Escreve os passageiros e diz a situação deles
    bool existePassageiro = false;
    for(auto& passageiro : this->passageiros) {
        
        existePassageiro = true;
        
        // Verifica se o passageiro está no dicionário de passageiros em viagem
        auto it = passageirosEmTransito.find(passageiro);
        if(it != passageirosEmTransito.end()) {
            
            // Se está, pega a viagem que ele se encontra
            Viagem* viagemPassageiro = it->second;
            
            // Pega o destino final do passageiro
            Viagem* atual = viagemPassageiro;
            while(atual->getProxima()) {
                atual = atual->getProxima();
            }
            Cidade* destino = atual->getDestino();

            cout << "  " << passageiro->getNome() << " : em trânsito ("
                 << viagemPassageiro->getOrigem()->getNome() << " -> " << viagemPassageiro->getDestino()->getNome()
                 << ", destino final: " << destino->getNome() << ", transporte: " << viagemPassageiro->getTransporte()->getNome() 
                 << ")" << endl;

        } else {
            // Se não está no dicionário, então escreve só a cidade em que o passageiro está
            cout << "  " << passageiro->getNome() << " : " << passageiro->getLocalAtual()->getNome() << endl;
        }
    }
    if(!existePassageiro) cout << "  Nenhum passageiro cadastrado." << endl;


    cout << "\n-*-*- Transportes -*-*-" << endl;

    bool existeTransporte = false;
    for(auto& transporte : this->transportes) {
        
        existeTransporte = true;
        
        if(transporte->isEmViagem()) {
            
            // Procura pela viagem que o transporte está
            Viagem* etapaAtiva = nullptr;
            for(auto& viagem : this->viagens) {
                Viagem* atual = viagem;
                while(atual) {
                    if(atual->isEmAndamento() && atual->getTransporte() == transporte) {
                        etapaAtiva = atual;
                        break;
                    }
                    atual = atual->getProxima();
                }
                if(etapaAtiva) break;
            }
            if(etapaAtiva) {
                // Busca pelo destino final do transporte
                Viagem* atual = etapaAtiva;
                while(atual->getProxima()) {
                    atual = atual->getProxima();
                }

                cout << "  " << transporte->getNome()
                     << " : em trânsito ("
                     << etapaAtiva->getOrigem()->getNome() << " -> " << etapaAtiva->getDestino()->getNome()
                     << ", destino final: " << atual->getDestino()->getNome()
                     << ")" << endl;
            } else {
                cout << "  " << transporte->getNome() << " : em viagem (sem detalhes)" << endl;
            }
        } else {
            cout << "  " << transporte->getNome() << " : " << transporte->getLocalAtual()->getNome() << endl;
        }
    }
    if(!existeTransporte) cout << "  Nenhum transporte cadastrado." << endl;


    cout << "\n-*-*- Viagens em Andamento -*-*-" << endl;
    
    bool temViagemEmAndamento = false;
    for(auto& viagem : this->viagens) {
        Viagem* atual = viagem;
        while(atual) {
            if(atual->isEmAndamento()) {
                temViagemEmAndamento = true;
                atual->relatarEstado();
                break;
            }
            atual = atual->getProxima();
        }
    }
    if(!temViagemEmAndamento) cout << "  Nenhuma viagem em andamento.\n" << endl;


    cout << "-*-*- Ranking das Cidades Mais Visitadas -*-*-" << endl;
    
    vector<Cidade*> ordenadas = this->cidades;
    sort(ordenadas.begin(), ordenadas.end(), [](Cidade* a, Cidade* b) {
        return a->getVisitas() > b->getVisitas();
    });

    int rank = 0;
    for(auto& cidade : ordenadas) {
        rank++;
        cout << "  " << rank << "° " << cidade->getNome() << " : " << cidade->getVisitas() << (cidade->getVisitas() == 1? " visita" : " visitas" ) << endl;
    }

    cout << "\n========================================\n" << endl;
}

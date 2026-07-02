# Controlador de Viagens - Trabalho LP1

![Git Hub](https://img.shields.io/badge/github-repository-blue?logo=github)
![LPI-UFRN](https://img.shields.io/badge/LPI-UFRN-blue.svg)
![C++](https://img.shields.io/badge/-C++-blue?logo=cplusplus)

## Sumário

- [Introdução](#introdução)
- [Compilação](#compilação)
- [Uso do Controlador de Viagens](#uso-do-controlador-de-viagens)
- [Integrante](#integrante)

## Introdução

Trabalho de controlador de viagens referente à disciplina de Linguagem de Programação do curso de BTI/UFRN.

## Compilação

__1.__ Execute

```shell
git clone https://github.com/victordantas703-coder/Controlador-de-viagens-Trabalho-LP1.git
```

ou baixe o arquivo compactado do projeto [por aqui](https://github.com/victordantas703-coder/Controlador-de-viagens-Trabalho-LP1/archive/refs/heads/main.zip) e extraia a pasta contida nele.

__2.__ Acesse a pasta clonada ou baixada pelo terminal e depois execute

```shell
g++ .\src\classes\classeCidade.cpp .\src\classes\classeTrajeto.cpp .\src\classes\classeTransporte.cpp .\src\classes\classePassageiro.cpp .\src\classes\classeViagem.cpp .\src\classes\classeControladorDeTransito.cpp .\src\main.cpp -o sistema
```

para compilar o projeto.

## Uso do Controlador de Viagens

Execute o programa compilado a partir do terminal.

Com o programa aberto, agora é possível usar os comandos do controlador de viagens.

Vale resaltar que

- Argumentos com aspas devem usar as aspas obrigatoriamente e o conteúdo dentro das aspas é um nome qualquer;
- `tipo` deve ser apenas `T` para trajetos ou transportes __terrestres__ e `A` para __aquáticos__;
- Qualquer argumento diferente do primeiro que não esteja em aspas é um número inteiro, ex.: `distância`, `velocidade`, etc.

Os comando possíveis são:

- __Cadastro de Cidade__ : Use `cadastrar_cidade "nome_cidade"` para cadastrar uma cidade no sistema.
- __Cadastro de Trajeto__ : Use `cadastrar_trajeto "nome_cidade_origem" "nome_cidade_destino" tipo distância` para cadastrar um trajeto de uma cidade à outra de um tipo e de uma certa distância;
- __Cadastro de Transporte__ : Use `cadastrar_transporte "nome_transporte" tipo capacidade_passageiros velocidade distância_entre_descanços horas_de_descanço "nome_cidade_local"` para cadastrar um transporte os dados parametros definidos;
- __Cadastro de Passageiro__ : Use `cadastrar_passageiro "nome_passageiro" "nome_cidade_local"` para cadastrar um passageiro em uma determinada cidade;
- __Iniciar uma Viagem__ : Use `iniciar_viagem "nome_transporte" quantidade_n_passageiros "nome_passageiro_1" "nome_passageiro_2" ... "nome_passageiro_n" "nome_cidade_origem" "nome_cidade_destino"` para iniciar uma viagem com uma quantidade n de passageiros em um transporte de uma cidade até outra;
- __Avançar Horas do Sistema__ : Use `avancar_horas quant_horas` para avançar uma certa quantidade de horas do sistema;
- __Relatar Estado do Sistema__ : Use `relatar_estado` para visualizar os passageiros e os transportes cadastrados e onde se encontram ou o momento atual do trânsito, saber quais viagens estão andamento e seus detalhes e saber quais as cidades mais visitadas.

## Integrante

Victor Matheus de Abreu Dantas

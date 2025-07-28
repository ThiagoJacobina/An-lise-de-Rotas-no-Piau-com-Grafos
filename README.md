# Projeto: Análise de Rotas no Piauí com Grafos (em C)

Este projeto implementa um grafo direcionado para representar cidades do estado do Piauí e suas conexões rodoviárias,
atendendo aos seguintes requisitos acadêmicos:

## Estrutura do Grafo
- As cidades são representadas como vértices numerados de 0 a 9.
- As conexões entre cidades (estradas) são representadas como arestas direcionadas.
- Usa-se Lista de Adjacência para representar o grafo.

## Cidades e Índices
```
0 → Corrente
1 → Gilbués
2 → Bom Jesus
3 → Floriano
4 → Oeiras
5 → Teresina
6 → Campo Maior
7 → Piripiri
8 → Luís Correia
9 → Parnaíba
```

## Conexões (arestas)
As arestas foram adicionadas com base nas rotas especificadas:
- Corrente → Gilbués
- Gilbués → Bom Jesus
- Bom Jesus → Floriano
- Floriano → Oeiras
- Oeiras → Teresina
- Teresina → Campo Maior
- Campo Maior → Piripiri
- Piripiri → Luís Correia
- Luís Correia → Parnaíba

Rotas alternativas:
- Teresina → Parnaíba
- Bom Jesus → Teresina

## Como ele funciona?

O mapa (grafo):Temos 10 cidades (Corrente, Gilbués, Bom Jesus, ..., Parnaíba) listadas em um vetor chamado cidades.
As conexões entre elas são como setas apontando de uma cidade para outra, armazenadas em listas (uma cidade sabe para quais outras ela pode ir diretamente).

-Principais funções:
- GRAPHinit: Cria o mapa com espaço para as 10 cidades.
- GRAPHinsertArc: Adiciona uma conexão (ex.: Corrente → Gilbués).
- GRAPHprint: Mostra o mapa, listando cada cidade e para onde ela leva.
- findAllPaths: Explora todas as rotas possíveis de Corrente a Parnaíba, como um viajante testando todos os caminhos.
- findPathsFromCorrenteToParnaiba: Organiza a busca e mostra os resultados.
- freeGraph: Limpa tudo no final para não deixar bagunça na memória.

A lógica da viagem:O programa usa uma técnica chamada busca em profundidade (DFS) para testar todas as rotas possíveis, como se fosse um GPS bem curioso.
Ele marca as cidades por onde passa para não se perder em loops e guarda cada caminho que chega em Parnaíba.
Enquanto explora, ele acompanha qual caminho tem menos paradas (mais curto) e qual passa por mais cidades (mais longo).



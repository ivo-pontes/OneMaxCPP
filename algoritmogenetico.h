#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H


class AlgoritmoGenetico
{
public:
    AlgoritmoGenetico();
    void executar();
    void inicializaPopulacao();
    void mostrarPopulacao();
    int obterPontuacao(vector<int> individuo);
    void mutacao(vector<int>& individuo);
    void cruzamento(int pai_1, int pai_2, vector<int>& filho);
    int obterMelhor();
    int tam_genes;
    int tam_populacao;
    int tam_torneio;
    int geracoes;
    double probabilidade_mutacao;
    double probabilidade_cruzamento;
    vector<vector<int>> populacao;

};

#endif // ALGORITMOGENETICO_H

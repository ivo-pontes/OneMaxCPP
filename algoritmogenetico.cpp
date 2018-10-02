#include "algoritmogenetico.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

AlgoritmoGenetico::AlgoritmoGenetico()
{
    tam_genes = 10;
    tam_populacao = 50;
    tam_torneio = 20;
    geracoes = 100;
    probabilidade_mutacao = 0.2;
    probabilidade_cruzamento = 0.7;
}



void AlgoritmoGenetico::executar()
{
    cout << "Resolução do Problema da OneMax\n";

    srand(time(NULL));

   this->inicializaPopulacao();


    for(int i = 0; i < geracoes; i++ )
    {
        for(int j = 0; j < tam_torneio; j++)
        {
            double probabilidade = ((double) rand() / ((double)RAND_MAX + 1));

            if(probabilidade < probabilidade_cruzamento)
            {
                int i_pai_1 = rand() % tam_populacao;
                int i_pai_2;

                do
                {
                    i_pai_2 = rand() % tam_populacao;
                }while(i_pai_1 == i_pai_2);

                vector <int> filho;
                this->cruzamento(i_pai_1, i_pai_2, filho);

                probabilidade = ((double) rand() / ((double)RAND_MAX + 1));

                if(probabilidade < probabilidade_mutacao)
                {
                    this->mutacao(filho);
                }

                int score_pai = this->obterPontuacao(populacao[i_pai_1]);
                int score_filho = this->obterPontuacao(filho);

                if(score_filho > score_pai)
                {
                    for(int k=0; k < tam_genes; k++)
                    {
                        this->populacao[i_pai_1][k] = filho[k];
                    }
                }
            }
        }

        cout << "Geração " << (i+1) << endl;
        cout << "Melhor: ";

        int i_melhor = this->obterMelhor();
        int score_melhor = this->obterPontuacao(populacao[i_melhor]);

        for(int j=0; j < tam_genes; j++)
        {
            cout << populacao[i_melhor][j] << " ";
        }

        cout << "\nPontuação: " << score_melhor << "\n\n";

        if(score_melhor == tam_genes)
            break;
    }
}


void AlgoritmoGenetico::inicializaPopulacao()
{
    for (int i = 0; i < tam_populacao; i++)
    {
        vector<int> individuo;

        for(int j = 0; j < tam_genes; j++)
        {
            int num = rand() % 2;
            individuo.push_back(num);
        }

        populacao.push_back(individuo);
    }
}

void AlgoritmoGenetico::mostrarPopulacao()
{
    for(int i = 0; i < tam_populacao; i++)
    {
        for(int j = 0; j < tam_genes; j++)
        {
            cout << populacao[i][j] << " ";
        }
        cout << endl;
    }
}

int AlgoritmoGenetico::obterPontuacao(vector<int> individuo)
{
    int soma = 0;
    for(int i=0; i < tam_genes; i++)
    {
        soma += individuo[i];
    }
    return soma;
}

void AlgoritmoGenetico::mutacao(vector<int>& individuo)
{
    int gene = rand() % tam_genes;

    if(individuo[gene] == 0)
       individuo[gene] = 1;
    else
       individuo[gene] = 0;
}

void AlgoritmoGenetico::cruzamento(int pai_1, int pai_2, vector<int>& filho)
{
    int ponto = rand() % tam_genes;

    for(int i = 0; i <= ponto; i++)
    {
        filho.push_back(populacao[pai_1][i]);
    }

    for(int i = ponto+1; i < tam_genes; i++)
    {
        filho.push_back(populacao[pai_2][i]);
    }
}

int AlgoritmoGenetico::obterMelhor()
{
    int i_melhor = 0;
    int score_melhor = this->obterPontuacao(populacao[0]);

    for(int i=0; i < tam_populacao; i++)
    {
        int score = this->obterPontuacao(populacao[i]);

        if(score > score_melhor)
        {
            i_melhor = i;
            score_melhor = score;
        }
    }

    return i_melhor;
}

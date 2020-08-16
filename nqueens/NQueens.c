/*
    Aluno:
        41829611 - Gabriel Coelho da Cunha
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "Auxiliary.h"

struct posicao
{
    char tipo;
    bool valida;
};

// Cria o tabuleiro
struct posicao ** cria_tabuleiro(int tamanho)
{
    struct posicao ** tabuleiro = (struct posicao **) malloc(tamanho * sizeof(struct posicao *));
    for(int linha=0; linha<tamanho; linha++)
    {
        tabuleiro[linha] = (struct posicao *) malloc(tamanho * sizeof(struct posicao));
    }
    return tabuleiro;
}

// Define os valores da posicao
void preenche_posicao(struct posicao ** tabuleiro, int linha, int coluna, char tipo, bool valida)
{
    tabuleiro[linha][coluna].tipo = tipo;
    tabuleiro[linha][coluna].valida = valida;
}

// Imprime o tabuleiro
void imprime_tabuleiro(struct posicao ** tabuleiro, int tamanho, bool valida)
{
    if (valida) printf("Tipo:Valida\n");

    for(int linha=0; linha<tamanho; linha++)
    {
        for(int coluna=0; coluna<tamanho; coluna++)
        {
            if (valida) printf("%02c:%c ", tabuleiro[linha][coluna].tipo, tabuleiro[linha][coluna].valida ? 'T' : 'F');
            else printf("%03c ", tabuleiro[linha][coluna].tipo);
        };
        printf("\n");
    };

    printf("\n");
}

// Popula o tabuleiro com '-'
void popula_tabuleiro(struct posicao ** tabuleiro, int tamanho)
{
    for(int linha=0; linha<tamanho; linha++)
    {
        for(int coluna=0; coluna<tamanho; coluna++)
        {
            preenche_posicao(tabuleiro, linha, coluna, '-', true);
        };
    };
}

// Valida o tipo presente na posicao
bool valida_tipo(struct posicao ** tabuleiro, int linha, int coluna, char tipo)
{
    if (tabuleiro[linha][coluna].tipo == tipo)
    {
        return true;
    }
    return false;
}

bool e_valida(struct posicao ** tabuleiro, int linha, int coluna)
{
    return tabuleiro[linha][coluna].valida;
}

// Valida a posicao da rainha posicionada na linha e na coluna
bool valida_posicao(struct posicao ** tabuleiro, int tamanho, int linha, int coluna)
{
    int l = linha;
    int c = coluna;

    // Norte
    l = linha-1;
    while (l >= 0)
    {
        if (valida_tipo(tabuleiro, l--, coluna, 'r')) return false;
    }

    // Nordeste
    l = linha-1;
    c = coluna+1;
    while (l >= 0 && c < tamanho)
    {
        if (valida_tipo(tabuleiro, l--, c++, 'r')) return false;
    }

    // Leste
    c = coluna+1;
    while (c < tamanho)
    {
        if (valida_tipo(tabuleiro, linha, c++, 'r')) return false;
    }

    // Sudeste
    l = linha+1;
    c = coluna+1;
    while (l < tamanho && c < tamanho)
    {
        if (valida_tipo(tabuleiro, l++, c++, 'r')) return false;
    }

    // Sul
    l = linha+1;
    while (l < tamanho)
    {
        if (valida_tipo(tabuleiro, l++, coluna, 'r')) return false;
    }

    // Sudoeste
    l = linha+1;
    c = coluna-1;
    while (l < tamanho && c >= 0)
    {
        if (valida_tipo(tabuleiro, l++, c--, 'r')) return false;
    }

    // Oeste
    c = coluna-1;
    while (c >= 0)
    {
        if (valida_tipo(tabuleiro, linha, c--, 'r')) return false;
    }

    // Nororeste
    l = linha-1;
    c = coluna-1;
    while (l >= 0 && c >= 0)
    {
        if (valida_tipo(tabuleiro, l--, c--, 'r')) return false;
    }

    return true;
}

// Define se e posicao valida de acordo com o tipo de peca 
void marca_posicoes(struct posicao ** tabuleiro, int tamanho)
{
    for(int linha=0; linha<tamanho; linha++)
    {
        for(int coluna=0; coluna<tamanho; coluna++)
        {
            if (valida_tipo(tabuleiro, linha, coluna, '-'))
            {
                tabuleiro[linha][coluna].valida = valida_posicao(tabuleiro, tamanho, linha, coluna);
            }
            else
            {
                tabuleiro[linha][coluna].valida = false;
            }
        }
    }
}

// Coloca as rainhas na posicao inicial
void posicao_inicial_rainhas(struct posicao ** tabuleiro, int tamanho, bool aleatoria)
{
    srand(time(NULL));
    int linha_r = 0;
    int coluna_r = 0;

    for(int rainha=0; rainha<tamanho; rainha++)
    {
        if (aleatoria)
        {
            while (tabuleiro[linha_r][coluna_r].tipo != '-')
            {
                linha_r = gera_numero_aleatorio(tamanho);
                coluna_r = gera_numero_aleatorio(tamanho);
            }
            preenche_posicao(tabuleiro, linha_r, coluna_r, 'r', false);
        }
        else
        {
            preenche_posicao(tabuleiro, tamanho-1, rainha, 'r', false);
        }
    }

    marca_posicoes(tabuleiro, tamanho);
}

// Move a rainha da posicao origem para a destino
void move_rainha(struct posicao ** tabuleiro, int tamanho, int l_origem, int c_origem, int l_destino, int c_destino, bool forcar)
{
    bool movimento_valido;

    if (forcar) movimento_valido = true;
    else movimento_valido = valida_posicao(tabuleiro, tamanho, l_origem, c_origem);

    if (movimento_valido)
    {
        preenche_posicao(tabuleiro, l_origem, c_origem, '-', valida_posicao(tabuleiro, tamanho, l_origem, c_origem));
        preenche_posicao(tabuleiro, l_destino, c_destino, 'r', false);
    }

    marca_posicoes(tabuleiro, tamanho);
    imprime_tabuleiro(tabuleiro, tamanho, true);
}

void metodo_ingenuo(struct posicao ** tabuleiro, int tamanho)
{
    int rainha = 0, linha = 0, coluna = tamanho-1;
    bool valida = true;

    posicao_inicial_rainhas(tabuleiro, tamanho, false);

    imprime_tabuleiro(tabuleiro, tamanho, true);

    while (rainha < tamanho)
    {
        if (valida)
        {
            while (coluna >= 0)
            {
                for(int l=tamanho-1; l>0; l--)
                {
                    move_rainha(tabuleiro, tamanho, l, coluna, l-1, coluna, true);
                    linha = l;
                }
                //move_rainha(tabuleiro, tamanho, linha, coluna, , coluna, true);
                coluna--;
            }
            valida = false;
        }
        else rainha++;
    }
}

void metodo_backtracking(struct posicao ** tabuleiro, int tamanho)
{
    int rainha = 0;
    int linha = 0;
    int count = 0;
    int * p_anteriores = (int *) malloc(tamanho * sizeof(int));
    bool valida = true;

    while (rainha >= 0 && rainha < tamanho)
    {
        for(int l=0; l<tamanho; l++)
        {
            if (!valida_tipo(tabuleiro, l, rainha, 'r'))
            {
                valida = valida_posicao(tabuleiro, tamanho, l, rainha) && e_valida(tabuleiro, l, rainha);
            }
            else valida = false;

            if (valida) 
            {
                linha = l;
                break;
            }
        }

        if (valida)
        {
            preenche_posicao(tabuleiro, linha, rainha, 'r', false);
            marca_posicoes(tabuleiro, tamanho);
            p_anteriores[rainha] = linha;
            rainha++;
        }
        else
        {
            for(int l=0; l<=p_anteriores[rainha-1]; l++)
            {
                preenche_posicao(tabuleiro, l, rainha-1, '-', false);
            }
            marca_posicoes(tabuleiro, tamanho);
            for(int l=0; l<=p_anteriores[rainha-1]; l++)
            {
                preenche_posicao(tabuleiro, l, rainha-1, '-', false);
            }
            rainha--;
        }

        
        if (rainha == 0)
        {
            count++;
            marca_posicoes(tabuleiro, tamanho);
            for(int l=0; l<count; l++)
            {
                preenche_posicao(tabuleiro, l, rainha, '-', false);
            }
        }
        //imprime_tabuleiro(tabuleiro, tamanho, true);
    }
    imprime_tabuleiro(tabuleiro, tamanho, false);
}

int main()
{
    int n = 15;
    struct posicao ** tabuleiro = cria_tabuleiro(n);
    double tempo_decorrido = 0.0;

    popula_tabuleiro(tabuleiro, n);
    //metodo_ingenuo(tabuleiro, n);
    clock_t comeco = clock();
    metodo_backtracking(tabuleiro, n);
    clock_t fim = clock();

    tempo_decorrido += (double) (fim - comeco) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %f segundos\n", tempo_decorrido);

    return 0;
}
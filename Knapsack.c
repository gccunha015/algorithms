/*
    Aluno:
        41829611 - Gabriel Coelho da Cunha
*/

#include <stdio.h>
#include <stdlib.h>

// Cria a tabela que ira armazenar os valores dos passos da mochila ate chegar a capacidade maxima e a quantidade de itens
int ** cria_tabela(int quantidade_linhas, int quantidade_colunas)
{
    int ** tabela = (int **) malloc(quantidade_linhas * sizeof(int *));
    for(int linha=0; linha<quantidade_linhas; linha++)
    {
        tabela[linha] = (int *) malloc(quantidade_colunas * sizeof(int));
    }
    return tabela;
}

// Popula a 'tabela_valores' com o valor '-1'
void popula_tabela_valores(int ** tabela_valores, int quantidade_maxima_itens, int capacidade_maxima_mochila)
{
    for(int linha=0; linha<quantidade_maxima_itens; linha++)
    {
        for(int coluna=0; coluna<=capacidade_maxima_mochila; coluna++)
        {
            tabela_valores[linha][coluna] = -1;
        };
    };
}

// Imprime a 'tabela_valores'
void imprime_tabela_valores(int ** tabela_valores, int quantidade_maxima_itens, int capacidade_maxima_mochila)
{
    for(int linha=0; linha<quantidade_maxima_itens; linha++)
    {
        for(int coluna=0; coluna<=capacidade_maxima_mochila; coluna++)
        {
            printf("%03d ", tabela_valores[linha][coluna]);
        };
        printf("\n");
    };
}

// Compara e indica qual o maior valor entre 'valor1' e 'valor2'
int maior_entre(int valor1, int valor2)
{
    if(valor1 > valor2) return valor1;
    return valor2;
}

// Preenche a 'tabela_valores' com o valor da mochila em determinada 'quantidade_itens' e 'capacidade_mochila'
int valor_maximo_mochila(int quantidade_itens, int capacidade_mochila, 
                            int valores[], int pesos[], int ** tabela_valores)
{
    // Variavel auxiliar para facilitar visualizacao, no codigo, de qual 'item' atual sera incluido ou nao
    int item = quantidade_itens - 1;
    // Inicializa a variavel 'valor' com '-1', ja que a 'tabela_valores' esta toda preenchida com o mesmo
    int valor = -1;

    // Se o valor nas coordenadas 'item' e 'capacidade_mochila' ja estiver calculado, nao ha necessidade de calcular novamente
    if(tabela_valores[item][capacidade_mochila] != -1) return tabela_valores[item][capacidade_mochila];
    // Percorre a 'tabela_valores' de baixo para cima
    if(quantidade_itens >= 2) valor = valor_maximo_mochila(quantidade_itens-1, capacidade_mochila, valores, pesos, tabela_valores);
    
    if(capacidade_mochila > 0)
    {
        // Percorre a 'tabela_valores' da direita para a esquerda
        valor = valor_maximo_mochila(quantidade_itens, capacidade_mochila-1, valores, pesos, tabela_valores);
        // Como nao ha valores para se buscar na 'tabela_valores' na primeira linha, apenas inclui o valor do item com menor peso
        if(quantidade_itens == 1) valor = valores[item];
        else
        {
            if(pesos[item] <= capacidade_mochila)
            {
                // Valor da mochila sem incluir o 'item' atual
                int valor_sem_item_adicional = tabela_valores[item-1][capacidade_mochila];
                // Valor da mochila incluido o 'item' atual
                int valor_com_item_adicional = valores[item] + tabela_valores[item-1][capacidade_mochila-pesos[item]];

                // Decide se o 'item' atual deve ser incluido na mochila
                valor = maior_entre(valor_sem_item_adicional, valor_com_item_adicional);
            }
            // Se o peso do 'item' atual for maior do que a 'capacidade_mochila', nao deve ser incluido
            else valor = tabela_valores[item-1][capacidade_mochila];
        }
        
    }
    // No caso da 'capacidade_mochila' ser '0', nao pode incluir nenhum 'item'
    if(capacidade_mochila == 0) valor = 0;
    // Preeche a 'tabela_valores', nas coordenadas 'item' e 'capacidade_mochila' de acordo com o valor calculado
    return tabela_valores[item][capacidade_mochila] = valor;
}

int main()
{
    // Itens inputados ja ordenados pelo peso
    int pesos[]   = {1, 2, 3, 4, 5};
    int valores[] = {1, 4, 4, 5, 7};
    //int valores[] = {2, 1, 5, 8, 9};
    int capacidade_maxima_mochila = 9;

    //int pesos[]   = { 1,  2,  5,  6,  7,  9, 11};
    //int valores[] = { 1,  6, 18, 22, 28, 40, 60};
    //int capacidade_maxima_mochila = 23;

    int quantidade_maxima_itens = sizeof(valores) / sizeof(valores[0]);

    int ** tabela_valores = cria_tabela(quantidade_maxima_itens, capacidade_maxima_mochila+1);
    
    popula_tabela_valores(tabela_valores, quantidade_maxima_itens, capacidade_maxima_mochila);
    valor_maximo_mochila(quantidade_maxima_itens, capacidade_maxima_mochila, valores, pesos, tabela_valores);
    imprime_tabela_valores(tabela_valores, quantidade_maxima_itens, capacidade_maxima_mochila);

    return 0;
}
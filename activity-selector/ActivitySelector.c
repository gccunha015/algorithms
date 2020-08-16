#include <stdio.h>
#include <stdlib.h>

int * cria_vetor(int tamanho)
{
    int * vetor = (int *) malloc(tamanho * sizeof(int));
    return vetor;
}

void popula_vetor(int * vetor, int tamanho)
{
    for(int elemento=0; elemento<tamanho; elemento++)
    {
        vetor[elemento] = 0;
    };
}

void imprime_vetor(int * vetor, int tamanho, char titulo[])
{
    printf("%23s: ", titulo);
    for(int elemento=0; elemento < tamanho; elemento++)
    {
        printf("%02d ", vetor[elemento]);
    };
    printf("\n");
}

void imprime_atividades_a_realizar(int * atividades_a_realizar, int quantidade_atividades)
{
    char titulo[] = "Atividades a realizar";
    printf("\n%23s: ", titulo);
    for(int atividade=0; atividade < quantidade_atividades; atividade++)
    {
        if(atividades_a_realizar[atividade] == 1)
        {
            printf("%02d ", atividade+1);
        }
    }
    printf("\n");
}

void selecao_de_atividades(int tempo_inicial[], int tempo_final[], int atividade_anterior, 
                            int quantidade_atividades, int atividades_a_realizar[])
{
    int atividade_atual = atividade_anterior + 1;
    if(atividade_anterior == 0) atividades_a_realizar[atividade_anterior] = 1;
    while(atividade_atual < quantidade_atividades && tempo_inicial[atividade_atual] < tempo_final[atividade_anterior])
    {
        atividade_atual += 1;
    }
    if(atividade_atual < quantidade_atividades)
    {
        atividades_a_realizar[atividade_atual] = 1;
        selecao_de_atividades(tempo_inicial, tempo_final, atividade_atual, quantidade_atividades, atividades_a_realizar);
    }
}

int main()
{
    int atividades[]     = {1, 2, 3, 4, 5, 6,  7,  8,  9, 10, 11};
    int tempo_incicial[] = {1, 3, 0, 5, 3, 5,  6,  8,  8,  2, 12};
    int tempo_final[]    = {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    int quantidade_atividades = sizeof(tempo_incicial) / sizeof(tempo_incicial[0]);
    int * atividades_a_realizar = cria_vetor(quantidade_atividades);
    popula_vetor(atividades_a_realizar, quantidade_atividades);

    imprime_vetor(atividades, quantidade_atividades, "Atividade");
    imprime_vetor(tempo_incicial, quantidade_atividades, "Tempo inicial");
    imprime_vetor(tempo_final, quantidade_atividades, "Tempo final");

    selecao_de_atividades(tempo_incicial, tempo_final, 0, quantidade_atividades, atividades_a_realizar);
    imprime_atividades_a_realizar(atividades_a_realizar, quantidade_atividades);
    
    return 0;
}
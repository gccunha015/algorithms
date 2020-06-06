import triangular

def menor_linha(quantidade_equacoes, coeficientes, coluna):
    for linha in range(coluna, quantidade_equacoes):
        if coeficientes[linha][coluna] != 0:
            return linha
    return -1

def troca_elementos(coeficientes, coluna, p):
    auxiliar = coeficientes[coluna]
    coeficientes[coluna] = coeficientes[p]
    coeficientes[p] = auxiliar

def efetua_operacoes(quantidade_equacoes, coeficientes, linha, coluna):
    multiplicador = coeficientes[linha][coluna] / coeficientes[coluna][coluna]
    for i in range(quantidade_equacoes+1):
        coeficientes[linha][i] -= multiplicador * coeficientes[coluna][i]

def pivotamento(quantidade_equacoes, coeficientes):
    incognitas = [0 for i in range(quantidade_equacoes)]
    for coluna in range(quantidade_equacoes):
        p = menor_linha(quantidade_equacoes, coeficientes, coluna)
        if p == -1:
            return -1, incognitas
        if p != coluna:
            troca_elementos(coeficientes, coluna, p)
        for linha in range(coluna+1, quantidade_equacoes):
            efetua_operacoes(quantidade_equacoes, coeficientes, linha, coluna)
    if coeficientes[quantidade_equacoes-1][quantidade_equacoes-1] == 0:
        return -1, incognitas
    incognitas = triangular.triangular(quantidade_equacoes, coeficientes)
    return 0, incognitas
    
if __name__ == "__main__":
    matriz_criada = False
    
    coeficientes = [[  1,  -1,   2,  -1,  -8], 
                    [  2,  -2,   3,  -3, -20], 
                    [  1,   1,   1,   0,  -2], 
                    [  1,  -1,   4,   3,   4]]
    matriz_criada = True
    
    if not matriz_criada:
        equacoes = int(input('Quantidade de equacoes: '))
        coeficientes = triangular.cria_matriz_aumentada(linhas, colunas)
    triangular.imprime_matriz_aumentada(coeficientes)
    print('Pivotando...')
    respostas = pivotamento(len(coeficientes), coeficientes)
    if respostas[0] == 0:
        triangular.imprime_matriz_aumentada(coeficientes)
        triangular.imprime_incognitas(respostas[1])
    else:
        print('Não ha solucoes unicas existentes.')
# cria uma matriz aumentada de acordo com a quantidade de equacoes desejadas
def cria_matriz_aumentada(equacoes):
    matriz = [[0 for x in range(equacoes+1)] for y in range(equacoes)]
    for i in range(equacoes):
        for j in range(equacoes+1):
            if j == equacoes: matriz[i][j] = int(input(f'Resposta da equação {i+1}: '))
            else: matriz[i][j] = int(input(f'Coeficiente {j+1} da equação {i+1}: '))
    return matriz

# imprime a matriz aumentada no terminal
def imprime_matriz_aumentada(matriz):
    print('Matriz Aumentada:')
    for i in range(len(matriz)):
        for j in range(len(matriz[0])):
            if j == len(matriz[0])-1: print(f'| {matriz[i][j]:5}', end=' ')
            else: print(f'{matriz[i][j]:5}', end=' ')
        print('')

# imprime as incognitas no terminal
def imprime_incognitas(incognitas):
    print('Incognitas:')
    for i in range(len(incognitas)):
        print(f'x{i+1}: {incognitas[i]:5}')

# realiza o somatorio da multiplicacao dos coeficientes da equacao com suas incognitas
def somatorio(incognitas, coeficientes, linha):
    somatorio = 0
    for coluna in range(linha, len(coeficientes[0])-1):
        somatorio += coeficientes[linha][coluna]*incognitas[coluna]
    return somatorio

# resolve um sistema de equacoes lineares no formato triangular superior
def triangular(quantidade_equacoes, coeficientes):
    # valores das incognitas do sistema
    incognitas = [0 for i in range(quantidade_equacoes)]
    # calcula o valor da ultima incognita
    incognitas[-1] = (coeficientes[quantidade_equacoes-1][quantidade_equacoes]/
                        coeficientes[quantidade_equacoes-1][quantidade_equacoes-1])
    # para cada linha da matriz aumentada, calcula o valor das incognitas ainda nao calculadas, de baixo para cima
    for i in range(quantidade_equacoes-2, -1, -1):
        incognitas[i] = ((coeficientes[i][quantidade_equacoes]-
                            somatorio(incognitas, coeficientes, i))/
                            coeficientes[i][i])
    return incognitas

if __name__ == "__main__":
    matriz_criada = False
    
    coeficientes = [[  1,   1,   0,   3,   4], 
                    [  0,  -1,  -1,  -5,  -7], 
                    [  0,   0,   3,  13,  13], 
                    [  0,   0,   0, -13, -13]]
    matriz_criada = True
    
    if not matriz_criada:
        equacoes = int(input('Quantidade de equacoes: '))
        coeficientes = cria_matriz_aumentada(equacoes)
    imprime_matriz_aumentada(coeficientes)
    incognitas = triangular(len(coeficientes), coeficientes)
    imprime_incognitas(incognitas)
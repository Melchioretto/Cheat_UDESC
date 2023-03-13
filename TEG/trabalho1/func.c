#include <stdio.h>
#include <stdlib.h>
#include "func.h"

// 1.Carga do grafo
int **carregarGrafo(int *a)
{
    FILE *arq;
    arq = fopen("grafo.txt", "r"); // abertura arquivo
    fscanf(arq, "%d\n", a);        // o valor salvo em a é o numero de vertices do grafo
    int **matriz;                  // iniciado dessa maneira para fazer a alocação dinamica da matriz
    matriz = criarMatriz(*a, *a);  // chama função para criar a matriz
    int x, y;
    while (fscanf(arq, "%d %d\n", &x, &y) != EOF) // x e y representam os vertices que possuem arestas
    {
        adicionaAresta(x - 1, y - 1, matriz); // como a matriz vai de 0 a N, e os valores são passados de 1 a N+1, é necessario remover 1 de x e y
    }
    fclose(arq); // fechamento arquivo
    return matriz;
}
// 1.função para validar o grafo (Somatorio dos graus = 2 * numero de arestas)
int validarGrafo(int **matriz, int tamanho)
{
    int status = 0;                               // sera retornado status 0 se o grafo não for validado
    int somatorio = somagrau(matriz, tamanho);    // chama a função do somatorio de graus
    int arestas = numeroArestas(matriz, tamanho); // chama a função do numero de arestas
    if (somatorio == (2 * arestas))
    {
        status = 1; // sera retornado status 1 se o grafo for validado
    }
    return status;
}
// 1.função para alocar dinamicamente a matriz e iniciar todos os valores como 0
int **criarMatriz(int linhas, int colunas)
{
    int **matriz = (int **)malloc(linhas * sizeof(int *)); // alocação dinamica matriz
    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = (int *)malloc(colunas * sizeof(int)); // alocação de cada linha da matriz
    }
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matriz[i][j] = 0; // iniciando a matriz como 0
        }
    }
    return matriz;
}
// 1.funcao para adicionar as arestas, recebendo a linha e a coluna como parâmetro, a função adiciona 1 na posição matriz[linha][coluna] e 1 na posição matriz[coluna][linha]
// o mesmo ocorre se linha == coluna
int **adicionaAresta(int linha, int coluna, int **matriz)
{
    matriz[linha][coluna] += 1; // adiciona 1 na matriz de adjacência, considerando a linha e a coluna
    matriz[coluna][linha] += 1;
    return matriz;
}
// 2.Função para imprimir as arestas do grafo
void imprimeMatriz(int **matriz, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}
// 2.Função para calcular o numero de arestas
int numeroArestas(int **matriz, int tamanho)
{
    int soma = 0;
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            if (i < j) // considerando apenas valores abaixo da diagonal principal, de outra maneira as arestas seriam contadas 2 vezes
            {
                soma += matriz[i][j]; // adiciona o valor em matriz[i][j], pois pode ser uma aresta dupla
            }
            else if (i == j) // considerando diagonal principal
            {
                soma += matriz[i][j] / 2; // divide por 2 o valor salvo em matriz[i][j], pois apesar de ser representado como 2 arestas na matriz, um laço é apenas uma aresta
            }
        }
    }
    return soma;
}
// 3.Função para exibir arestas em laço
void lacos(int **matriz, int tamanho)
{
    int cont = 0; // referencia sera utilizada ao final para verificar caso não tenha laço no grafo
    for (int i = 0; i < tamanho; i++)
    {
        if (matriz[i][i] >= 1) // matriz[i][i] pos apenas podem existir laços na diagonal principal, se o valor for >=1 significa que tem um laço nessa posição
        {
            cont++; // adiciona 1 a um contador para marcar a presença do laço
            printf("\nExiste um laco no vertice: %d\n", i + 1);
        }
    }
    if (cont == 0) // se cont == 0 não há laços no grafo
    {
        printf("\nNao existem lacos nesse grafo.\n");
    }
}
// 4.Função para exibir arestas multiplas do grafo
void arestasMultiplas(int **matriz, int tamanho)
{
    int cont = 0; // valor de referencia para verificar se há arestas multiplas
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = i; j < tamanho; j++)
        {
            if (matriz[i][j] > 1)
            {
                if (i != j) // considerando apenas se não é um laço
                {
                    printf("\nExiste uma aresta multipla entre os vertices V[%d] e V[%d]\n", i + 1, j + 1); // +1 em i e j devem ser adicionados devido ao modo que a matriz foi salva
                    printf("\nO numero de arestas desse par eh: %d\n", matriz[i][j]);
                    cont++;
                }
            }
        }
    }
    if (cont == 0)
    {
        printf("\nNao existem arestas duplas nesse grafo.\n");
    }
}
// 5.Função para verificar o grau de um vertice especifico recebido como parâmetro
// o valor passado como referencia deve ter seu valor diminuido em 1 devido as posições que a matriz é salva
// vale destacar que apesar de não ser uma arestas multipla, um laço tem peso 2 no calculo do grau, por isso não há uma divisão quando [vertice - 1] ==[i]
int grauV(int **matriz, int vertice, int tamanho)
{
    int soma = 0;
    if ((vertice - 1 >= tamanho) || (vertice - 1 < 0)) // algumas checagens são feitas para não acessar um valor inexistente da matriz
    {
        soma--; // retorna -1 caso um valor invalido tenha sido digitado
    }
    else
    {
        for (int i = 0; i < tamanho; i++)
        {
            soma += matriz[vertice - 1][i]; // soma de todos os valores da linha
        }
        return soma;
    }
    return soma;
}
// 6.Função para somatório de graus
int somagrau(int **matriz, int tamanho)
{
    int soma = 0;
    for (int i = 1; i < tamanho + 1; i++)
    {
        soma += grauV(matriz, i, tamanho); // chama a função do grau de um vertice diversas vezes para o somatorio
    }
    return soma;
}
// 7.Função para identificar vertices isolados
void isolados(int **matriz, int tamanho)
{
    int soma;
    int cont = 0; // valor de referencia para verificar se há vertices isolados
    for (int i = 0; i < tamanho; i++)
    {
        soma = 0;
        for (int j = 0; j < tamanho; j++)
        {
            if (i != j) // laços não são considerados na checagem de vertices isolados
            {
                soma += matriz[i][j]; // para ser isolado a soma das demais arestas do vertice deve ser 0
            }
        }
        if (soma == 0)
        {
            cont++;
            printf("\nO vertice V[%d] esta isolado\n", i + 1);
        }
    }
    if (cont == 0)
    {
        printf("\nNao ha vertices isolados\n");
    }
}
// 9.Função para verificar se o numero total de vertices com grau impar é par
void verticesImpar(int **matriz, int tamanho)
{
    int cont = 0;
    int grau = 0;
    for (int i = 0; i < tamanho; i++)
    {
        grau = grauV(matriz, i + 1, tamanho);
        if (grau % 2 != 0)
        {
            cont++; // contador para o numero de vertices com grau impar
        }
    }
    if (cont % 2 == 0)
    {
        printf("\nO numero de vertices com grau impar(%d) eh par\n", cont); // Se o grafo estiver certo sempre deve imprimir essa opção, o valor entre parenteses é o número de vertices com grau impar
    }
    else
    {
        printf("\nO numero de vertices com grau impar(%d) eh impar\n", cont);
    }
}
// 8.Função para verificar se o número de arestas é no máximo igual ao número de Vertices tomadas 2 a 2 (E <= n * (n-1)/2)
void teoremaArestas(int **matriz, int tamanho)
{
    int num = numeroArestas(matriz, tamanho); // recebe o numero de arestas
    int teorema = 0;
    teorema = tamanho * (tamanho - 1) / 2;
    if (num < teorema)
    {
        printf("\nO numero de arestas (%d) eh menor que o numero de combinacoes de |V| tomadas 2 a 2 (%d)\n", num, teorema);
    }
    else if (num == teorema)
    {
        printf("\nO numero de arestas (%d) eh igual ao numero de combinacoes de |V| tomadas 2 a 2 (%d)\n", num, teorema);
    }
    else
    {
        printf("\nO numero de arestas (%d) eh maior que o numero de combinacoes de |V| tomadas 2 a 2 (%d)\n", num, teorema);
    }
}
// 10.Função para verificar se o grafo é simples
// Não pode possuir nem laço e nem arestas multiplas
void grafoSimples(int **matriz, int tamanho)
{
    int cont = 0; // valor utilizado como referência para checar se o grafo é simples
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            if (matriz[i][j] > 1) // apenas um teste é realizado, pois se uma aresta é um laço a representação dela na matriz de adjacência são 2 arestas, portanto se qualquer valor da matriz[i][j] > 1 o grafo não é simples
            {
                cont++;
            }
        }
    }
    if (cont > 0)
    {
        printf("\nO grafo nao eh um grafo simples.\n");
    }
    else
    {
        printf("\nO grafo eh um grafo simples.\n");
    }
}
// 11.Função para verificar se o grafo é completo
// Um grafo completo é um grafo simples em que todos os vertices possuem arestas entre si
void grafoCompleto(int **matriz, int tamanho)
{
    int cont = 0; // valor sera utilizado para verificar se o grafo é completo
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            if (i == j) // teste para laço
            {
                if (matriz[i][j] > 0) // se tiver um laço o grafo não é completo
                {
                    cont++; // altera o contador
                    break;
                }
            }
            else
            {
                if (matriz[i][j] != 1) // se algum outro valor diferente do laço for igual a 0 então o grafo não é completo
                {
                    cont++; // altera o contador
                    break;
                }
            }
        }
    }
    if (cont != 0)
    {
        printf("\nO grafo nao eh completo.\n");
    }
    else // se o contador não foi alterado o grafo é completo
    {
        printf("\nO grafo eh completo.\n");
    }
}
// 12.Função para verificar se o grafo é regular
// para o grafo ser regular todos os vertices possuem o mesmo grau
void grafoRegular(int **matriz, int tamanho)
{
    int grau = grauV(matriz, 1, tamanho); // recebe o grau do primeiro vertice e utilizará ele para comparar com os demais
    int comparar;
    int cont = 0; // valor sera utilizado como referência para checar se o grafo é regular
    if (tamanho != 1)
    {
        for (int i = 1; i < tamanho; i++)
        {
            comparar = grauV(matriz, i + 1, tamanho); // recebe os grau para comparação
            if (grau != comparar)
            {
                cont++; // altera esse valor se o grafo for diferente
            }
        }
    }
    if (cont == 0) // se o valor não for alterado o grafo é regular
    {
        printf("\nO grafo eh regular e o valor de seus graus eh %d.\n", grau);
    }
    else
    {
        printf("\nO grafo nao eh regular.\n");
    }
}
// 13.Função para verificar se pode ocorrer um passeio e se ele vai passar por todos os vertices ou não
// não encontramos uma maneira de exibir o trajeto, pois podem ser feitas diversas combinações
void passeio(int **matriz, int tamanho)
{
    printf("\nDigite o comprimento do passeio.\n");
    int c;
    scanf("%d", &c);
    int grauTotal = somagrau(matriz, tamanho); // o somatorio dos graus é o tamanho do trajeto total
    if (grauTotal == 0)                        // o passeio apenas não irá ocorrer se a matriz for nula
    {
        printf("O passeio nao pode ser realizado pois a matriz eh nula.\n");
    }
    else if (c == grauTotal) // se o comprimento for igual ao valor do grauTotal o caminho sera passado por todas as arestas
    {
        printf("O passeio pode ser realizado passando por todas as arestas do grafo.\n");
    }
    else if (c < grauTotal)
    {
        printf("O passeio pode ser realizado, porem nao sera passado por todas as arestas do grafo.\n");
    }
    else
    {
        printf("O passeio pode ser realizado passando mais de uma vez por algumas arestas.\n");
    }
}
// 14.Função para remover aresta
int **removerAresta(int **matriz, int tamanho)
{
    int x, y;
    printf("\nDigite a aresta que deseja remover.\n");
    scanf("%d %d", &x, &y);
    if (x > tamanho || y > tamanho || x <= 0 || y <= 0) // verificação para não acessar um endereço inexistente da matriz
    {
        printf("Esses vertices nao existem.\n");
    }
    else
    {
        if (matriz[x - 1][y - 1] == 0) // se o valor da matriz entre esses vertices for 0 significa que não há aresta entre esses vertices
        {
            printf("Nao existe uma aresta entre esses 2 vertices.\n");
        }
        else
        {
            matriz[x - 1][y - 1]--; // se o valor é diferente de zero então a operação de remoção de aresta pode ser realizado, apenas uma aresta é removida de cada vez
            matriz[y - 1][x - 1]--; // a aresta precisa ser removida tanto de matriz[x-1][y-1] como de matriz[y-1][x-1] para ser removida completamente do grafo
            printf("Aresta removida com sucesso.\n");
        }
    }
    return matriz;
}
// 15.Função para remover vertice
// basicamente a função cria uma matriz nova para receber os valores da matriz antiga sem o vertice excluido, porém isso vai causar uma alteração na disposição da posição
// dos valores na matriz que estão após o vertice excluido, em outras palavras, vai ocorrer um redimensionamento da matriz
int **removerVertice(int **matriz, int *tamanho)
{
    int vertice;
    printf("\nDigite o vertice que deseja remover.\n");
    scanf("%d", &vertice);
    int **matrizNova;
    if (vertice > *tamanho || vertice <= 0) // verificação se o vertice existe antes de tentar realizar um acesso ao endereço da matriz
    {
        printf("Esse vertice nao existe.\n");
        return matriz; // retorna a matriz existente caso o vertice não exista
    }
    else
    {
        matrizNova = criarMatriz(*tamanho - 1, *tamanho - 1); // é criada uma nova matriz que receberá os valores da matriz existente sem o vertice excluido
        for (int i = 0; i < *tamanho - 1; i++)
        {
            for (int j = 0; j < *tamanho - 1; j++)
            {
                if (i < vertice - 1) // se a posição i for menor que o vertice excluido, a aresta se manterá na mesma linha na matriz nova
                {
                    if (j < vertice - 1) // se a posição j  for menor que o vertice excluido, a aresta se manterá na mesma coluna na matriz nova
                    {
                        matrizNova[i][j] = matriz[i][j];
                    }
                    if (j >= vertice - 1) // se a posição j for maior que o vertice excluido, a aresta será adicionada uma coluna antes na matriz nova
                    {
                        matrizNova[i][j] = matriz[i][j + 1];
                    }
                }
                else
                {
                    if (i >= vertice - 1) // se a posição i for maior que o vertice excluido, a aresta será adicionada uma linha antes na matriz nova
                    {
                        if (j < vertice - 1) // se a posição j  for menor que o vertice excluido, a aresta se manterá na mesma coluna na matriz nova
                        {
                            matrizNova[i][j] = matriz[i + 1][j];
                        }
                        else
                        {
                            matrizNova[i][j] = matriz[i + 1][j + 1]; // se a posição j for maior que o vertice excluido, a aresta será adicionada uma coluna antes na matriz nova
                        }
                    }
                }
            }
        }
    }
    (*tamanho)--;                   // se a função chegou nesse ponto o vertice foi removido, então é diminuido 1 no tamanho da matriz que é enviado como parâmetro de quase todas as funções
    liberaMatriz(matriz, *tamanho); // como a matriz foi substituida, é necessária uma função para liberar a matriz anterior
    printf("\nVertice removido com sucesso!\n");
    return matrizNova;
}
// 16. Função para salvar o grafo em um arquivo txt
// função não é muito bem otimizada por possuir 3 for em laço, porém está funcionando
void salvarGrafo(int **matriz, int tamanho)
{
    FILE *arq;
    arq = fopen("grafo.txt", "w"); // é aberto o grafo com a função write para sobreescrever o arquivo existente
    fprintf(arq, "%i", tamanho);   // primeiro valor salvo é o tamanho
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = i; j < tamanho; j++)
        {
            if (matriz[i][j] != 0) // apenas sera adicionada uma linha no arquivo se houver uma aresta
            {
                int arestas = matriz[i][j]; // aqui será salvo o número de arestas que existem nessa posição da matriz
                if (i == j)
                {
                    arestas = arestas / 2; // se for em um laço o número de arestas precisa ser divido por 2 antes de ser adicionado, pois apesar de ser apenas uma aresta, são salvas 2 na matriz
                }
                for (int k = 0; k < arestas; k++)
                {
                    fprintf(arq, "\n%i %i", i + 1, j + 1);
                }
            }
        }
    }
    printf("\nGrafo salvo com sucesso.\n");
    fclose(arq); // fechamento do arquivo
}
// 15. Função para desalocar a matriz
void liberaMatriz(int **matriz, int a)
{
    for (int i = 0; i < a; i++)
    {
        free(matriz[i]); // desaloca linha a linha
    }
    free(matriz); // após desalocar as linha desaloca a matriz
}
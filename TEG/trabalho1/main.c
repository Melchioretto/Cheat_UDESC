#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main()
{
    int a; // a é o numero de vertices
    int **matriz = carregarGrafo(&a);
    int vertice, grau, soma;
    int k = -1;
    if (validarGrafo(matriz, a) == 1)
    {
        printf("\nGrafo validado com sucesso.\n");
        while (k != 0)
        {
            system("cls");
            printf("\nMenu:\n");
            printf("1 - Exibicao nos e arestas\n");
            printf("2 - Nos com arestas em laco\n");
            printf("3 - Arestas Duplas\n");
            printf("4 - Grau de um vertice\n");
            printf("5 - Somatorio dos graus\n");
            printf("6 - Vertices isolados\n");
            printf("7 - Verificacao maximo de arestas.\n");
            printf("8 - Vertices com grau impar eh par?\n");
            printf("9 - Grafo eh simples?\n");
            printf("10 - Grafo eh completo?\n");
            printf("11 - Grafo eh regular?\n");
            printf("12 - Passeio\n");
            printf("13 - Remocao aresta.\n");
            printf("14 - Remocao vertice.\n");
            printf("15 - Salvar grafo.\n");
            printf("0 - Sair\n");
            scanf("%d", &k);
            switch (k)
            {
            case 1:
                printf("\nNumero de nos: %d\n", a);
                imprimeMatriz(matriz, a);
                printf("\nNumero de arestas: %d\n", numeroArestas(matriz, a));
                system("pause");
                break;
            case 2:
                lacos(matriz, a);
                system("pause");
                break;
            case 3:
                arestasMultiplas(matriz, a);
                system("pause");
                break;
            case 4:
                printf("\nQue vertice deseja analisar?\n");
                scanf("%d", &vertice);
                grau = grauV(matriz, vertice, a);
                if (grau == -1)
                {
                    printf("\nEsse vertice nao existe\n");
                }
                else
                {
                    printf("\nGrau do vertice V[%d] = %d\n", vertice, grau);
                }
                system("pause");
                break;
            case 5:
                soma = somagrau(matriz, a);
                printf("\nO somatorio dos graus eh: %d\n", soma);
                system("pause");
                break;
            case 6:
                isolados(matriz, a);
                system("pause");
                break;
            case 7:
                teoremaArestas(matriz, a);
                system("pause");
                break;
            case 8:
                verticesImpar(matriz, a);
                system("pause");
                break;
            case 9:
                grafoSimples(matriz, a);
                system("pause");
                break;
            case 10:
                grafoCompleto(matriz, a);
                system("pause");
                break;
            case 11:
                grafoRegular(matriz, a);
                system("pause");
                break;
            case 12:
                passeio(matriz, a);
                system("pause");
                break;
            case 13:
                matriz = removerAresta(matriz, a);
                system("pause");
                break;
            case 14:
                matriz = removerVertice(matriz, &a);

                system("pause");
                break;
            case 15:
                salvarGrafo(matriz, a);
                system("pause");
                break;
            case 0:
                printf("Finalizando\n");
                break;
            default:
                printf("Digite novamente!\n");
                break;
            }
        }
    }
    else
    {
        printf("\nGrafo nao eh valido.");
    }

    return 0;
}

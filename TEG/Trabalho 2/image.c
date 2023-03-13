#include "headImage.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows, cols, p;
    int **matrix = createMatrix(&rows, &cols);
    printf("\n");
    int **registers = createRegister();
    do
    {
        do
        {
            printf("\n[1]: Componentes conexos usando viz-4");
            printf("\n[2]: Componentes conexos usando viz-8");
            printf("\n[3]: Imprimir imagem binaria");
            printf("\n[0]: Sair\n\n");
            scanf("%i", &p);
        } while (p < 0 || p > 3);
        switch (p)
        {
        case 1:
            printf("\n");
            printf("Componentes = %i\n", countComponents(matrix, registers));
            printComponents();
            registers = clearRegisterMatrix(registers);
            break;
        case 2:
            printf("\n");
            printf("Componentes = %i\n", countComponentsEight(matrix, registers));
            printComponents();
            registers = clearRegisterMatrix(registers);
            break;
        case 3:
            printf("\n");
            printMatrix(matrix);
            break;
        }
    } while (p != 0);

    return 0;
}
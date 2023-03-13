typedef struct Componente componente;
struct Componente
{
    int baricentroX, baricentroY, numeroDePixels;
};
componente *lista;
int **createMatrix(int *mainRows, int *mainCols);
int **createRegister();
void printMatrix(int **matrix);
void printComponents();
int countComponents(int **matrix, int **registers);
int countComponentsEight(int **matrix, int **registers);
void deepSearch(int **matrix, int **registers, int row, int col);
void deepSearchEight(int **matrix, int **registers, int row, int col);
int **clearRegisterMatrix(int **registers);
int R, C, count;
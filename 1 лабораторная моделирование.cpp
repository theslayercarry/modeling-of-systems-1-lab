#include <iostream>
#define CONST 20

double определитель_матрицы(double matrix[CONST][CONST], int n);
void функция_ошибки(int X, int N, const double входные_воздействия[CONST][CONST], double входные_воздействия_изм[CONST][CONST], const double выходные_воздействия_изм[CONST], double матрица_столбец[CONST][1]);

void отображение_мат_модели(int size, double входные_воздействия_изм[CONST][CONST], double матрица_столбец[CONST][1]);
void заполнение_таблицы(int N, int X, double входные_воздействия[][CONST], double выходные_воздействия[CONST]);
void отображение_таблиц(int X, int N, const double входные_воздействия[][CONST], const double выходные_воздействия[CONST], double выходные_воздействия_изм[CONST]);
void Производные_функции(int X, int N, const double входные_воздействия[CONST][CONST], const double входные_воздействия_изм[CONST][CONST], const double выходные_воздействия_изм[CONST], double матрица_столбец[CONST][1]);
void символ(char S, int n);
void копирование_матриц(int X, double massiv_copy[CONST][CONST], const double входные_воздействия_изм[CONST][CONST]);
void замена_столбцов(int X, int q, double massiv_copy[CONST][CONST], double матрица_столбец[CONST][1]);

void subMatrix(double mat[CONST][CONST], double temp[CONST][CONST], int p, int q, int n);

int main()
{
    setlocale(LC_ALL, "rus");
    //////////////////////////////////////////
    double входные_воздействия [CONST][CONST];
    double выходные_воздействия[CONST];
    //////////////////////////////////////////                                    
    double входные_воздействия_изм[CONST][CONST] = { 0 };
    double выходные_воздействия_изм[CONST];
    double матрица_столбец[CONST][1] = { 0 };
    //////////////////////////////////////////
    double massiv_copy[CONST][CONST];
    double коэффициенты[CONST];
    double определитель;
    //////////////////////////////////////////
    int N, X;  // Количество экспериментов и входных воздействий
    puts("6 Вариант:");
    printf("\ny* = 1 / y, (Xj)* = Xj, aj = (aj)*\n\n");
    fputs("Введите количество входных воздействий: ", stdout);
    scanf_s("%i", &X);
    putchar('\n');
    fputs("Введите количество экспериментов: ", stdout);
    scanf_s("%i", &N);
    putchar('\n');
    puts("Заполните таблицу экспериментальных данных: ");
    заполнение_таблицы(X, N, входные_воздействия, выходные_воздействия);
    printf("\n\n");
    отображение_таблиц(X, N, входные_воздействия, выходные_воздействия, выходные_воздействия_изм);
    функция_ошибки(X, N, входные_воздействия, входные_воздействия_изм, выходные_воздействия_изм, матрица_столбец);
    printf("\n\n");
    Производные_функции(X, N, входные_воздействия, входные_воздействия_изм, выходные_воздействия, матрица_столбец);
    printf("\n\n");
    puts("Решим полученную систему линейных уравнений методом Крамера: ");
    putchar('\n');
    отображение_мат_модели(X, входные_воздействия_изм, матрица_столбец);
    printf("\n\n");
    определитель = определитель_матрицы(входные_воздействия_изм, X + 1);
    if (определитель == 0)
    {
        printf("Данная матрица вырожденная, решений бесконечное множество\n");
    }
    else
    {
        for (int i = 0; i < X + 1; i++)
        {
            копирование_матриц(X, massiv_copy, входные_воздействия_изм);
            замена_столбцов(X, i, massiv_copy, матрица_столбец);
            коэффициенты[i] = определитель_матрицы(massiv_copy, X + 1) / определитель;
        }
        printf("Таким образом, искомые параметры математической модели равны:\n\n");
        for (int i = 0; i < X + 1; i++)
        {
            printf("a%i = %.3lf\n", i, коэффициенты[i]);
        }
        printf("\n\nОтвет: y = 1 / ( ");
        for (int i = 0; i < X + 1; i++)
        {
            (i == 0) ? printf("%.3lf ", коэффициенты[i]) : printf("%+.3lf(x%i) ", коэффициенты[i], i);
        }
        printf(")");
        putchar('\n');
    }
}
void заполнение_таблицы(int X, int N, double входные_воздействия[][CONST], double выходные_воздействия[CONST])
{
    for (int i = 0; i < N; i++)
    {
        printf("\nДанные для %i эксперимента:\n", i + 1);
        for (int j = 0; j < X; j++)
        {
            printf ("x%i = ", j + 1);
            scanf_s("%lf", &входные_воздействия[j][i]);
        }
        printf ("y  = ");
        scanf_s("%lf", &выходные_воздействия[i]);
    }
}
void отображение_таблиц(int X, int N, const double входные_воздействия[][CONST], const double выходные_воздействия[CONST], double выходные_воздействия_изм[CONST])
{
    int i, help;
    bool logic = false;
    puts("Исходные экспериментальные данные:");
    символ('=', 11 + 7 * N);
    putchar('\n');
    for (i = help = 0; i < X; i++, help++)
    {
        if (logic)
        {
            символ('=', 11 + 7 * N);
            putchar('\n');
        }
        printf("|x%i = ", help + 1);
        for (int j = 0; j < N; j++)
        {
            printf("%+3.3lf | ", входные_воздействия[i][j]);
        }
        putchar('\n');
        logic = true;
    }
    символ('=', 11 + 7 * N);
    putchar('\n');
    printf("|y  = ");
    for (int i = 0; i < N; i++)
    {
        printf("%+3.3lf | ", выходные_воздействия[i]);
        выходные_воздействия_изм[i] = 1 / выходные_воздействия[i]; 
        
    }
    putchar('\n');
    символ('=', 11 + 7 * N);
    putchar('\n'); putchar('\n'); putchar('\n');
    logic = false;
    puts("Линеаризация значений исходных переменных:");
    printf("\ny* = 1 / y, (Xj)* = Xj\n\n");
    //////////////////////////////////////////////////////////////////
    символ('=', 15 + 7 * N);
    putchar('\n');
    for (i = help = 0; i < X; i++, help++)
    {
        if (logic)
        {
            символ('=', 15 + 7 * N);
            putchar('\n');
        }
        printf("|(x%i)* = ", help + 1);
        for (int j = 0; j < N; j++)
        {
            printf("%+3.3lf | ", входные_воздействия[i][j]);
        }
        putchar('\n');
        logic = true;
    }
    символ('=', 15 + 7 * N);
    putchar('\n');
    printf("|(y)*  = ");
    for (int i = 0; i < N; i++)
    {
        printf("%+3.3lf | ", выходные_воздействия_изм[i]);
    }
    putchar('\n');
    символ('=', 15 + 7 * N);
    putchar('\n');
}

void символ(char S, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", S);
    }
    
}
void отображение_мат_модели(int size, double входные_воздействия_изм[CONST][CONST], double матрица_столбец[CONST][1])
{
    for (int i = 0; i < size + 1; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%.3lfa%i* + ", входные_воздействия_изм[i][j], j);
        }
        printf("%.3lfa%i* = %.3lf\n", входные_воздействия_изм[i][size], size, матрица_столбец[i][0]);
    }
}
void Производные_функции(int X, int N, const double входные_воздействия[CONST][CONST], const double входные_воздействия_изм[CONST][CONST], const double выходные_воздействия_изм[CONST], double матрица_столбец[CONST][1])
{      
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool logic = true;
        int i = 0;
        printf("dI/d(a%i)* = ", i);
        for (int j = 0; j < N - 1; j++)
        {
            for (int k = 0; k < X; k++)
            {
                if (logic)
                {
                    printf("2[a%i ", k);
                }
                logic = false;
                printf("+ %.3lf(a%i) ", входные_воздействия[k][j], k + 1);

                if (k == X - 1)
                {
                    printf("%+.3lf] + ", выходные_воздействия_изм[j] * -1);
                }
            }
            logic = true;
            if (j == N - 2)
            {

                for (int k = 0; k < X; k++)
                {
                    if (logic)
                    {
                        printf("2[a%i ", k);
                    }
                    logic = false;

                    printf("+ %.3lf(a%i) ", входные_воздействия[k][j + 1], k + 1);

                    if (k == X - 1)
                    {
                        printf("%+.3lf] = ", выходные_воздействия_изм[j + 1] * -1);

                        
                         for (int j = 0; j < X; j++)
                         {
                            printf("%.3lf(a%i) + ", входные_воздействия_изм[i][j], j);
                         }
                         printf("%.3lf(a%i) %+.3lf\n", входные_воздействия_изм[i][X], X, матрица_столбец[i][0] * -1);
                        
                    }
                }
            }
        }
        printf("\n\n");
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    logic = true;
    for (int i = 0; i < X; i++)
    {
        printf("dI/d(a%i)* = ", i + 1);
        for (int j = 0; j < N - 1; j++)
        {

            for (int k = 0; k < X; k++)
            {
                if (logic)
                {
                    printf("2[a%i ", k);
                }
                logic = false;

                printf("+ %.3lf(a%i) ", входные_воздействия[k][j], k + 1);
               
                if (k == X - 1)
                {
                    printf("%+.3lf]%.3lf + ", выходные_воздействия_изм[j] * -1, входные_воздействия[i][j]);
                }

            }
            logic = true;
            if (j == N - 2)
            {

                for (int k = 0; k < X; k++)
                {
                    if (logic)
                    {
                        printf("2[a%i ", k);
                    }
                    logic = false;

                    printf("+ %.3lf(a%i) ", входные_воздействия[k][j + 1], k + 1);

                    if (k == X - 1)
                    {
                        printf("%+.3lf]%.3lf = ", выходные_воздействия_изм[j + 1] * -1, входные_воздействия[i][j + 1]);

                        
                        for (int j = 0; j < X; j++)
                        {
                           printf("%.3lf(a%i) + ", входные_воздействия_изм[i + 1][j], j);
                        }
                        printf("%.3lf(a%i) %+.3lf\n", входные_воздействия_изм[i + 1][X], X, матрица_столбец[i + 1][0] * -1);
                        
                    }
                }
                logic = true;
            }
        }
        printf("\n\n");
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void функция_ошибки(int X, int N, const double входные_воздействия[CONST][CONST], double входные_воздействия_изм[CONST][CONST], const double выходные_воздействия_изм[CONST], double матрица_столбец[CONST][1])
{
    int i, j, k;
    double sum, столбец, a0;
    for (i = 0; i < X; i++)
    {
          for (k = a0 = sum = столбец = 0; k < N; k++)
          {
              a0      += 1 * 2;
              sum     += входные_воздействия[i][k] * 2;
              столбец += выходные_воздействия_изм[k] * 2;
          }
          входные_воздействия_изм[0][0] = a0;
          матрица_столбец[0][0] = столбец;
          входные_воздействия_изм[0][i + 1] = sum;
    }

    for (i = 0; i < X; i++)
    {
        for (j = 0; j < X; j++)
        {
            for (k = a0 = sum = столбец = 0; k < N; k++)
            {
                a0      += 1 * 2 * входные_воздействия[i][k];
                sum     += входные_воздействия[i][k] * 2 * входные_воздействия[j][k];
                столбец += выходные_воздействия_изм[k] * 2 * входные_воздействия[i][k];
                
            }
            входные_воздействия_изм[i + 1][0] = a0;
            входные_воздействия_изм[i + 1][j + 1] = sum;
            матрица_столбец[i + 1][0] = столбец;
        }
    }
}

void копирование_матриц(int X, double massiv_copy[CONST][CONST], const double входные_воздействия_изм[CONST][CONST])
{
    int matrix_size = X + 1;
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {

            massiv_copy[i][j] = входные_воздействия_изм[i][j];

        }
    }
}
void замена_столбцов(int X, int q, double massiv_copy[CONST][CONST], double матрица_столбец[CONST][1])
{
    int matrix_size = X + 1;
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            massiv_copy[j][q] = матрица_столбец[j][0];
        }
    }
}

void subMatrix(double mat[CONST][CONST], double temp[CONST][CONST], int p, int q, int n) 
{
    int i = 0, j = 0;
    // filling the sub matrix
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // skipping if the current row or column is not equal to the current
            // element row and column
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
double определитель_матрицы(double matrix[CONST][CONST], int n)
{
    int determinant = 0;
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    double temp[CONST][CONST], sign = 1;
    for (int i = 0; i < n; i++) {
        subMatrix(matrix, temp, 0, i, n);
        determinant += sign * matrix[0][i] * определитель_матрицы(temp, n - 1);
        sign = -sign;
    }
    return determinant;
}
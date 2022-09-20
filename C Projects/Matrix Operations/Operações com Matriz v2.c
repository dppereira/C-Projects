#include <stdio.h>
#include <stdlib.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////////////////////
// SUB-ROTINAS
void *determinante(int ordem, int mat[ordem][ordem]);
void *SisTriangInf(int ordem, int mat[ordem][ordem], float vetB[ordem], float vetX[ordem]);
void *SisTriangSup(int ordem, int mat[ordem][ordem], float vetB[ordem], float vetX[ordem]);
float *DecompLU(int n, float (*mat)[n]);
float *Cholesky(int n, float (*A)[n]);
float *GaussSimp(int ordem, float aux[ordem][ordem]);
float *GaussPivot(int ordem, float aux[ordem][ordem], float aux2[ordem][ordem]);
float *MatInv(int ordem, float aux[ordem][ordem]);
float jacobi(int n, float A[n][n]);
float *GaussSeidel(int n, float (*A)[n]);
float dr(float *x0, float *x1, unsigned int n);
float MOD(float x);
///////////////////////////////////////////////////////////////////////////////////////////////
// MAIN E FUNCOES

int main(void)
{
    int reprocessamento, escolha_operacoes, ordem, i, j, l;

    printf("Digite a ordem, ou da matriz, ou do sistema:\n");
    scanf("%d", &ordem);

    int mat[ordem][ordem];
    float vetX[ordem], vetB[ordem];
    float *matresult, *vetresult;

    printf("Digite sua matriz ou matriz dos coeficientes:\n");

    for (i = 0; i < ordem; i++)
    {
        for (j = 0; j < ordem; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }

    do
    {
        do
        {
            printf("Escolha qual rotina deseja utilizar: \n(1) Determinante\n(2) Sistema Triangular Inferior\n(3) Sistema Triangular Superior\n(4) Decomposicao LU\n(5) Cholesky\n(6) Gauss Simples\n(7) Gauss Pivoteamento Parcial\n(8) Matriz Inversa\n(9) Jacobi\n(10) Gauss Seidel\n");
            scanf("%d", &escolha_operacoes);

        } while (escolha_operacoes == 1 && escolha_operacoes == 2 && escolha_operacoes == 3 && escolha_operacoes == 4 && escolha_operacoes == 5 && escolha_operacoes == 6 && escolha_operacoes == 7 && escolha_operacoes == 8 && escolha_operacoes == 9 && escolha_operacoes == 10);

        switch (escolha_operacoes)
        {
        case 1:
        {
            determinante(ordem, mat);

            break;
        }
        case 2:
        {
            printf("Digite o vetor de termos independentes:\n");

            for (l = 0; l < ordem; l++)
            {

                scanf(" %f", &vetB[l]);
            }

            SisTriangInf(ordem, mat, vetB, vetX);

            break;
        }
        case 3:
        {
            printf("Digite o vetor de termos independentes:\n");

            for (l = 0; l < ordem; l++)
            {

                scanf(" %f", &vetB[l]);
            }

            SisTriangSup(ordem, mat, vetB, vetX);

            break;
        }
        case 4:
        {
            float aux[ordem][ordem];

            for (i = 0; i < ordem; i++)
            {
                for (j = 0; j < ordem; j++)
                {

                    aux[i][j] = (float)mat[i][j];
                }
            }

            vetresult = DecompLU(ordem, aux);

            for (i = 0; i < ordem; i++)
            {
                printf("x[%d] = %0.2f ", i + 1, vetresult[i]);
            }

            break;
        }
        case 5:
        {
            float aux[ordem][ordem];

            for (i = 0; i < ordem; i++)
            {
                for (j = 0; j < ordem; j++)
                {

                    aux[i][j] = (float)mat[i][j];
                }
            }

            vetresult = Cholesky(ordem, aux);

            for (i = 0; i < ordem; i++)
            {
                printf("x[%d] = %0.2f ", i + 1, vetresult[i]);
            }

            break;
        }
        case 6:
        {
            float aux[ordem][ordem];

            for (i = 0; i < ordem; i++)
            {
                for (j = 0; j < ordem; j++)
                {

                    aux[i][j] = (float)mat[i][j];
                }
            }

            vetresult = GaussSimp(ordem, aux);

            for (i = 0; i < ordem; i++)
            {
                printf("x[%d] = %0.2f ", i + 1, vetresult[i]);
            }

            break;
        }
        case 7:
        {
            // Trocando a matriz de int para float

            float aux[ordem][ordem];
            float aux2[ordem][ordem];

            for (i = 0; i < ordem; i++)
            {
                for (j = 0; j < ordem; j++)
                {
                    aux[i][j] = (float)mat[i][j];
                    aux2[i][j] = 0;
                }
            }

            vetresult = GaussPivot(ordem, aux, aux2);

            for (i = 0; i < ordem; i++)
            {
                printf("x[%d] = %0.2f ", i + 1, vetresult[i]);
            }

            break;
        }
        case 8:
        {
            // Trocando a matriz de int para float

            float aux[ordem][ordem];

            for (i = 0; i < ordem; i++)
            {
                for (j = 0; j < ordem; j++)
                {
                    aux[i][j] = (float)mat[i][j];
                }
            }

            matresult = MatInv(ordem, aux);

            printf("A matriz inversa eh:\n");

            for (i = 0; i < ordem; i++)
            {
                if (i != 0)
                {
                    printf("\n");
                }

                for (j = 0; j < ordem; j++)
                {
                    printf("%.03f | ", matresult[(i * ordem) + j]);
                }
            }

            break;
        }
        case 9:
        {
            float r;
            float aux[ordem][ordem];

            for (i = 0; i < ordem; i++)
            {
                for (j = 0; j < ordem; j++)
                {

                    aux[i][j] = (float)mat[i][j];
                }
            }

            r = jacobi(ordem, aux);

            break;
        }
        case 10:
        {
            float aux[ordem][ordem];

            for (i = 0; i < ordem; i++)
            {
                for (j = 0; j < ordem; j++)
                {

                    aux[i][j] = (float)mat[i][j];
                }
            }

            vetresult = GaussSeidel(ordem, aux);

            for (i = 0; i < ordem; i++)
            {
                printf("x[%d] = %0.2f ", i + 1, vetresult[i]);
            }

            break;
        }
        }

        printf("\n");

        do
        {
            printf("Deseja resolver novamente? Sim = 1 e Nao = 0\n");
            scanf("%d", &reprocessamento);
        } while (reprocessamento == 1 && reprocessamento == 0);

        if (reprocessamento == 0)
        {
            free(matresult);
            free(vetresult);
            break;
        }

    } while (reprocessamento == 1);
}

void *determinante(int ordem, int mat[ordem][ordem])
{
    float a[ordem][ordem], ratio, det = 1;
    int i, j, k;

    for (i = 0; i < ordem; i++)
    {
        for (j = 0; j < ordem; j++)
        {
            a[i][j] = (float)mat[i][j];
        }
    }

    for (i = 0; i < ordem; i++)
    {

        for (j = i + 1; j < ordem; j++)
        {
            ratio = a[j][i] / a[i][i];

            for (k = 0; k < ordem; k++)
            {
                a[j][k] = a[j][k] - ratio * a[i][k];
            }
        }
    }

    for (i = 0; i < ordem; i++)
    {
        det = det * a[i][i];
    }

    printf("O determinante da matriz dada: %0.f", det);

    return 0;
}

void *SisTriangInf(int ordem, int mat[ordem][ordem], float vetB[ordem], float vetX[ordem])
{
    int i, j;
    float temp = 0.0;

    vetX[0] = vetB[0] / mat[0][0];
    for (i = 1; i < ordem; i++)
    {
        temp = 0;
        for (j = 0; j <= (i - 1); j++)
        {
            temp = temp + (mat[i][j] * vetX[j]);
        }
        vetX[i] = (vetB[i] - temp) / mat[i][i];
    }
    for (i = 0; i < ordem; i++)
    {
        printf("x[%d]= %0.2f ", (i + 1), vetX[i]);
    }

    return 0;
}

void *SisTriangSup(int ordem, int mat[ordem][ordem], float vetB[ordem], float vetX[ordem])
{
    int i, j;
    float temp = 0.0;

    vetX[ordem - 1] = vetB[ordem - 1] / mat[ordem - 1][ordem - 1];
    for (i = (ordem - 2); i >= 0; i--)
    {
        temp = 0;
        for (j = (i + 1); j < ordem; j++)
        {
            temp = temp + (mat[i][j] * vetX[j]);
        }
        vetX[i] = (vetB[i] - temp) / mat[i][i];
    }
    for (i = 0; i < ordem; i++)
    {
        printf("x[%d]= %f ", (i + 1), vetX[i]);
    }

    return 0;
}

float *DecompLU(int n, float (*mat)[n])
{
    float b[n], x[n], y[n];
    int i, j;
    float matrizL[n][n], matrizU[n][n];
    float s = 0;
    float *vetresult = malloc(n * sizeof(int));

    printf("Digite os valores do vetor b:\n");

    for (i = 0; i < n; i++)
    {
        printf("b[%d]= ", (i + 1));
        scanf(" %f", &b[i]);
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrizL[i][j] = 0;
            matrizU[i][j] = mat[i][j];
        }
    }
    for (j = 0; j < n; j++)
    {
        for (i = j + 1; i < n; i++)
        {
            if (matrizU[i][j] == 0)
            {
            }
            else
            {
                matrizL[i][j] = matrizU[i][j] / matrizU[j][j];
                int c = 0;
                for (c = j; c < n; c++)
                {
                    matrizU[i][c] = matrizU[i][c] + matrizU[j][c] * (-1 * (matrizL[i][j]));
                }
            }
        }
    }

    for (i = 0; i < n; i++)
        matrizL[i][i] = 1;

    y[0] = b[0] / matrizL[0][0];
    for (i = 1; i < n; i++)
    {
        s = 0.0;
        for (j = 0; j <= (i - 1); j++)
        {
            s = s + (matrizL[i][j] * y[j]);
        }
        y[i] = (b[i] - s) / matrizL[i][i];
    }

    printf("\n");
    printf("\n");

    i = 0;
    s = 0;
    j = 0;

    x[n - 1] = y[n - 1] / matrizU[n - 1][n - 1];
    for (i = (n - 2); i >= 0; i--)
    {
        s = 0;
        for (j = (i + 1); j < n; j++)
        {
            s = s + (matrizU[i][j] * x[j]);
        }
        x[i] = (y[i] - s) / matrizU[i][i];
    }

    for (i = 0; i < n; i++)
    {
        vetresult[i] = x[i];
    }

    return vetresult;
}

float *Cholesky(int n, float (*A)[n])
{
    int i, j, k;
    double sum;
    float G[n][n], GT[n][n], b[n], x[n], y[n];
    float s = 0.0;
    float *vetresult = malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            if (A[i][j] != A[j][i])
            {
                printf("SEM SIMETRIA!");
            }
        }
    }

    printf("Digite os valores do vetor b:\n");

    for (i = 0; i < n; i++)
    {
        printf("b[%d]= ", (i + 1));
        scanf(" %f", &b[i]);
    }

    for (k = 0; k < n; k++)
        for (i = 0; i <= k; i++)
        {
            sum = 0;
            for (j = 0; j < i; j++)
            {
                sum += G[i][j] * G[k][j];
            }

            if (i == k)
            {
                if (A[i][i] - sum <= 0)
                    printf("NAO DEFINIDA POSITIVA");
                G[i][i] = sqrt(A[i][i] - sum);
            }
            else
                G[k][i] = 1.0 / G[i][i] * (A[k][i] - sum);
        }

    y[0] = b[0] / G[0][0];
    for (i = 1; i < n; i++)
    {
        s = 0.0;
        for (j = 0; j <= (i - 1); j++)
        {
            s = s + (G[i][j] * y[j]);
        }
        y[i] = (b[i] - s) / G[i][i];
    }

    for (i = 0; i < n; i = i + 1)
    {
        for (j = 0; j < n; j = j + 1)
        {
            GT[j][i] = G[i][j];
        }
    }

    printf("\n");
    printf("\n");

    i = 0;
    s = 0;
    j = 0;

    x[n - 1] = y[n - 1] / GT[n - 1][n - 1];
    for (i = (n - 2); i >= 0; i--)
    {
        s = 0;
        for (j = (i + 1); j < n; j++)
        {
            s = s + (GT[i][j] * x[j]);
        }
        x[i] = (y[i] - s) / GT[i][i];
    }
    for (i = 0; i < n; i++)
    {
        printf("x[%d]= %.2f ", (i + 1), x[i]);
        printf("\n");
    }

    for (i = 0; i < n; i++)
    {
        vetresult[i] = x[i];
    }

    return vetresult;
}

float *GaussSimp(int ordem, float aux[ordem][ordem])
{

    int i, j, k;
    float b, sub, indep[ordem], result[ordem];
    float *vetresult = malloc(ordem * sizeof(int));

    printf("Digite o vetor de termos independentes:\n");

    for (i = 0; i < ordem; i++)
    {
        scanf("%f", &indep[i]);
        result[i] = 0;
    }

    // Ordenando a matriz

    for (i = 0; i < ordem; i++)
    {
        for (j = 0; j < ordem; j++)
        {
            if (j > i)
            {
                b = ((aux[j][i]) / (aux[i][i]));

                for (k = 0; k < ordem; k++)
                {
                    aux[j][k] = aux[j][k] - b * aux[i][k];
                }

                indep[j] = indep[j] - b * indep[i];
            }
        }
    }

    // Visualizacao da matriz para verificacao das funcoes

    /*printf("Matriz pronta\n");

    for (j = 0; j < ordem; j++)
    {

        for (k = 0; k < ordem; k++)
        {
            printf("%f ", aux[j][k]);
        }

        printf("%f", indep[j]);
        printf("\n");
    }*/

    // Resolvendo o sistema linear

    for (i = ordem - 1; i >= 0; i--)
    {
        sub = 0;

        for (k = ordem - 1; k >= 0; k--)
        {
            sub += result[k] * aux[i][k];
        }

        result[i] = (indep[i] - sub) / aux[i][i];
    }

    for (i = 0; i < ordem; i++)
    {
        vetresult[i] = result[i];
    }

    return vetresult;
}

float *GaussPivot(int ordem, float aux[ordem][ordem], float aux2[ordem][ordem])
{

    int i, j, k;
    float b, sub, indep[ordem], ax[ordem], result[ordem];
    float *vetresult = malloc(ordem * sizeof(int));

    printf("Digite o vetor de termos independentes::\n");

    for (i = 0; i < ordem; i++)
    {
        scanf("%f", &indep[i]);
        ax[i] = 0;
        result[i] = 0;
    }

    // Ordenando a matriz

    for (i = 0; i < ordem; i++)
    {
        for (j = i; j < ordem; j++)
        {
            if (aux[i][i] < aux[j][i])
            {
                for (k = 0; k < ordem; k++)
                {

                    aux2[j][k] = aux[j][k];
                    aux[j][k] = aux[i][k];
                    aux[i][k] = aux2[j][k];

                    ax[k] = indep[j];
                    indep[j] = indep[i];
                    indep[i] = ax[k];
                }
            }
        }

        for (j = 0; j < ordem; j++)
        {
            if (j > i)
            {
                b = ((aux[j][i]) / (aux[i][i]));

                for (k = 0; k < ordem; k++)
                {
                    aux[j][k] = aux[j][k] - b * aux[i][k];
                }
                indep[j] = indep[j] - b * indep[i];
            }
        }
    }

    // Visualizacao da matriz para verificacao das funcoes

    /*printf("Matriz pronta\n");

    for (j = 0; j < ordem; j++)
    {

        for (k = 0; k < ordem; k++)
        {
            printf("%f ", aux[j][k]);
        }

        printf("%f", indep[j]);
        printf("\n");
    }*/

    // Resolvendo o sistema linear

    for (i = ordem - 1; i >= 0; i--)
    {
        sub = 0;

        for (k = ordem - 1; k >= 0; k--)
        {
            sub += result[k] * aux[i][k];
        }

        result[i] = (indep[i] - sub) / aux[i][i];
    }

    for (i = 0; i < ordem; i++)
    {
        vetresult[i] = result[i];
    }

    return vetresult;
}

float *MatInv(int ordem, float aux[ordem][ordem])
{
    int i, j, k;
    float pivo = 0, b;
    float *matresult = malloc(ordem * ordem * sizeof(int));
    float ident[ordem][ordem];

    // Completando a matriz identidade

    for (i = 0; i < ordem; i++)
    {
        for (j = 0; j < ordem; j++)
        {

            if (i == j)
            {
                ident[i][j] = 1;
            }
            else
                ident[i][j] = 0;
        }
    }

    // Formando a Matriz Inversa

    for (j = 0; j < ordem; j++)
    {
        pivo = aux[j][j];

        for (k = j; k < ordem; k++)
        {
            aux[j][k] = aux[j][k] / pivo;
        }

        for (k = 0; k < ordem; k++)
        {
            ident[j][k] = ident[j][k] / pivo;
        }

        for (i = 0; i < ordem; i++)
        {
            if (i != j)
            {
                b = aux[i][j];
                for (k = 0; k < ordem; k++)
                {
                    aux[i][k] = (aux[i][k]) - (b * aux[j][k]);
                    ident[i][k] = (ident[i][k]) - (b * ident[j][k]);
                }
            }
        }
    }

    // Copiando a Matriz Inversa em um vetor que vai printar o resultado na funcao main

    for (i = 0; i < ordem; i++)
    {
        for (j = 0; j < ordem; j++)
        {
            matresult[(i * ordem) + j] = ident[i][j];
        }
    }

    return matresult;
}

float jacobi(int n, float A[n][n])
{
    int i, j, k, cont = 0, it = 0;
    float soma, erro = 1, max1, max2;
    float X[n], Xa[n];
    float B[n], max = 0, pr, X0[n];

    printf("Digite os valores do vetor b:\n");
    for (i = 0; i < n; i++)
    {
        printf("b[%d] =", i + 1);
        scanf("%f", &B[i]);
    }

    printf("Precisao: ");
    scanf("%f", &pr);

    printf("maximo de iteracoes: ");
    scanf("%d", &it);

    printf("Vetor x0:\n");
    for (i = 0; i < n; i++)
    {
        printf("x0[%d] = ", i + 1);
        scanf("%f", &X0[i]);
    }

    for (i = 0; i < n; i++)
    {
        X[i] = X0[i];
    }

    while (erro > pr && cont < it)
    {
        for (i = 0; i < n; i++)
        {
            Xa[i] = X[i];
        }

        cont++;

        for (i = 0; i < n; i++)
        {
            soma = 0;

            for (j = 0; j < n; j++)
            {
                if (j != i)
                {
                    soma = soma + A[i][j] * Xa[j];
                }
            }

            X[i] = ((B[i] - soma) / A[i][i]);
        }

        max1 = -1;
        for (i = 0; i < n; i++)
        {
            if (MOD(X[i] - Xa[i]) > max1)
            {
                max1 = MOD(X[i] - Xa[i]);
            }
        }

        max2 = -1;
        for (i = 0; i < n; i++)
        {
            if (MOD(X[i] > max2))
            {
                max2 = MOD(X[i]);
            }
        }

        erro = max1 / max2;
    }
    printf("\n");
    for (i = 0; i < n; i++)
    {
        printf("X[%d] = %.4f\n", i + 1, X[i]);
    }
    printf("\n");
    printf("Erro = %.4f < %.4f\n", erro, pr);
    printf("iteracoes = %d\n", cont);

    return 0.0;
}

float *GaussSeidel(int n, float (*A)[n])
{
    double e = 0.0005;
    int i, j, k;
    float sum;
    float x0[n];
    float x1[n];
    float b[n];
    float *vetresult = malloc(n * sizeof(int));

    printf("Digite os valores do vetor b:\n");

    for (i = 0; i < n; i++)
    {
        printf("b[%d]= ", (i + 1));
        scanf(" %f", &b[i]);
    }

    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
            if (A[i][j] != A[j][i])
                printf("SEM SIMETRIA!");
    }

    for (i = 0; i < n; i++)
        x0[i] = x1[i] = 0;

    do
    {
        k++;

        for (i = 0; i < n; i++)
            x0[i] = x1[i];

        for (i = 0; i < n; i++)
        {
            sum = 0;

            for (j = 0; j < i; j++)
                sum += A[i][j] * x1[j];

            for (j = i + 1; j < n; j++)
                sum += A[i][j] * x0[j];

            x1[i] = (b[i] - sum) / A[i][i];
        }
    } while (dr(x0, x1, n) > e && k < 1000);

    for (i = 0; i < n; i++)
    {
        vetresult[i] = x1[i];
    }

    return vetresult;
}

float dr(float *x0, float *x1, unsigned int n)
{
    float dr, x_max;
    unsigned int i;

    dr = 0;
    x_max = 0;

    for (i = 0; i < n; i++)
    {
        if (fabs(x1[i] - x0[i]) > dr)
            dr = fabs(x1[i] - x0[i]);
        if (fabs(x1[i]) > x_max)
            x_max = fabs(x1[i]);
    }
    dr = dr / x_max;
    return dr;
}

float MOD(float x)
{
    if (x < 0)
    {
        x = x * (-1);
    }

    return x;
}
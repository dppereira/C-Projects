#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////////////////////
// SUB-ROTINAS
void *determinante(int ordem, int mat[ordem][ordem]);
void *SisTriangInf(int ordem, int mat[ordem][ordem], float vetB[ordem], float vetX[ordem]);
void *SisTriangSup(int ordem, int mat[ordem][ordem], float vetB[ordem], float vetX[ordem]);
float *DecompLU(int ordem, int mat[ordem][ordem]);
float *Cholesky(int ordem, int mat[ordem][ordem]);
float *GaussSimp(int ordem, float aux[ordem][ordem]);
float *GaussPivot(int ordem, float aux[ordem][ordem], float aux2[ordem][ordem]);
float *MatInv(int ordem, float aux[ordem][ordem]);
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
            printf("Escolha qual rotina deseja utilizar: \n(1) Determinante\n(2) Sistema Triangular Inferior\n(3) Sistema Triangular Superior\n(4) Decomposicao LU\n(5) Cholesky\n(6) Gauss Simples\n(7) Gauss Pivoteamento Parcial\n(8) Matriz Inversa\n");
            scanf("%d", &escolha_operacoes);

        } while (escolha_operacoes == 1 && escolha_operacoes == 2 && escolha_operacoes == 3 && escolha_operacoes == 4 && escolha_operacoes == 5 && escolha_operacoes == 6 && escolha_operacoes == 7 && escolha_operacoes == 8);

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

            matresult = DecompLU(ordem, mat);

            break;
        }
        case 5:
        {

            matresult = Cholesky(ordem, mat);

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

float *DecompLU(int ordem, int mat[ordem][ordem])
{

    float *matresult = malloc(ordem * ordem * sizeof(int));

    return matresult;
}

float *Cholesky(int ordem, int mat[ordem][ordem])
{

    float *matresult = malloc(ordem * ordem * sizeof(int));

    return matresult;
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
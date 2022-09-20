#include <stdio.h>
#include <stdlib.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////////////////////
// SUB-ROTINAS
void InterpolarLagrange(int tam, float mat[tam][tam], float px);
float InetrpolarNewton(int qtd_pontos, float matriz_tabela[qtd_pontos][qtd_pontos], float ponto);
float NewtonGregory(int qtd_num, float matriz_tabela[qtd_num][qtd_num], float ponto);
void AjusteReta(int n, float mat[n][n] ,float *m, float *b);
void AjusteExponencial(int tam, float mat[tam][tam]);
void trend(float m, float b, int n, float mat[n][n]);
///////////////////////////////////////////////////////////////////////////////////////////////
// MAIN E FUNCOES

int main(void)
{
    int reprocessamento, escolha_operacoes, ordem, i, j;
    float result, ponto, m, b;

    printf("Quantos pontos serao:");
    scanf("%d", &ordem);

    float mat[ordem][ordem];

    printf("Digite seus pontos:\n");

    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < ordem; j++)
        {
            printf("Valor de x para o ponto %d: ", j+1);
            scanf("%f",&mat[0][j]);
            printf("Valor de y para o ponto %d: ", j+1);
            scanf(" %f",&mat[1][j]);
        }
    }

    do
    {
        do
        {
            printf("Escolha qual rotina deseja utilizar: \n(1) InterpolarLagrange\n(2) Interpolador Newton\n(3) Interpolador Newton Gregory\n(4) Ajuste de Reta\n(5) Ajuste Polinomial\n(6) Ajuste Exponencial\n");
            scanf("%d", &escolha_operacoes);

        } while (escolha_operacoes == 1 && escolha_operacoes == 2 && escolha_operacoes == 3 && escolha_operacoes == 4 && escolha_operacoes == 5 && escolha_operacoes == 6);

        switch (escolha_operacoes)
        {
        case 1:
        {
            printf("Insira o ponto para achar p(x): ");
            scanf("%f",&ponto);

            InterpolarLagrange(ordem, mat, ponto);

            break;
        }
        case 2:
        {
            printf("Insira o ponto para achar p(x): ");
            scanf("%f", &ponto);

            result = InetrpolarNewton(ordem, mat, ponto);

            printf("p(x) = %.2f", result);

            break;
        }
        case 3:
        {
            printf("Não realizada!\n");

            break;
        }
        case 4:
        {

            AjusteReta(ordem, mat, &m, &b);

            trend(m, b, ordem, mat);

            break;
        }
        case 5:
        {

           printf("Não realizada!\n");

            break;
        }
        case 6:
        {

           void AjusteExponencial(int tam, float mat[tam][tam]);

        break;
        }
        }

        do
        {
            printf("Deseja resolver novamente? Sim = 1 e Nao = 0\n");
            scanf("%d", &reprocessamento);
        } while (reprocessamento != 1 && reprocessamento != 0);

        if (reprocessamento == 0)
        {
            break;
        }
    } while (reprocessamento == 1);
}

void InterpolarLagrange(int tam, float mat[tam][tam], float px)
{
int i,j;
float fx[tam], x[tam];
float pxdef, num, div, lx;

    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < tam; j++)
        {
            x[i] = mat[0][j];
            fx[i] = mat[1][j];
        } 
    }
    

    pxdef = 0;

    for (i = 0; i < tam; i++)
    {

        num = 1;
        div = 1;
        lx = 1;

        for (j = 0; j < tam; j++)
        {
            if (i == j)
            {
                
                if(j+1 == tam)
                {
                    lx = (num / div);
                    break;
                }

                j++;
                
            }

            num *= px - x[j];

            div *= x[i] - x[j];

            if (j == tam - 1)
            {
                lx = (num / div);
            }
        }

        pxdef += fx[i] * lx;

    }

    printf("O valor de p(%.2f) e : %.4f", px, pxdef);
}

float InetrpolarNewton(int qtd_pontos, float matriz_tabela[qtd_pontos][qtd_pontos], float ponto)
{
    float matriz_aux[qtd_pontos][qtd_pontos], mlt = 1, resultado = 0;
    int i, j;

    for(i = 0; i < qtd_pontos; i++)
    {
        for(j = 0; j < qtd_pontos-i; j++)
        {
            if(i == 0)
            {
                matriz_aux[j][i] = matriz_tabela[1][j];
            }
            else
                matriz_aux[j][i] = (matriz_aux[j+1][i-1] - matriz_aux[j][i-1])/ (matriz_tabela[0][j+i] - matriz_tabela[0][j]);
        }
    }

   
    resultado = 0;

    for(i = qtd_pontos-1; i >= 0; i--)
    {
        mlt = matriz_aux[0][qtd_pontos - 1 - i];
        for(j = 0; j < qtd_pontos - i - 1; j++)
        {
            mlt = mlt*(ponto - matriz_tabela[0][j]);
        }

        resultado = resultado + mlt;
    }

    return resultado;
}

float NewtonGregory(int qtd_num, float matriz_tabela[qtd_num][qtd_num], float ponto)
{
    float matriz_aux[qtd_num][qtd_num], mtl = 1, div, a, resultado;
    int i, j;
    int fat;

    a = fabs(matriz_tabela[0][0] - matriz_tabela[0][1]);

    for(i = 0; i < qtd_num; i++)
    {
        for(j = 0; j < qtd_num-i; j++)
        {
            if(i == 0)
            {
                matriz_aux[j][i] = matriz_tabela[1][j];
            }
            
            else
                matriz_aux[j][i] = matriz_aux[j+1][i-1]-matriz_aux[j][i-1];
        }
    }

    resultado = 0;

    for(i = qtd_num-1; i >= 0; i--)
    {
        fat = fatorial(qtd_num - i - 1);
        div = matriz_aux[0][qtd_num - i - 1]/(pow(a, qtd_num - 1 - i)*fat);
        for(j = 0; j < qtd_num - 1 - i; j++)
        {
            mtl = mtl * (ponto - matriz_tabela[0][j]);
        }
        resultado = resultado + (mtl*div);
        mtl = 1;
    }

    return resultado;
}

void AjusteReta(int n, float mat[n][n] ,float *m, float *b)
{
    int i, j;
    float sumYX = 0.;
    float sumX = 0.;
    float sumY = 0.;
    float sumX2 = 0.;
    float sum2X = 0.;
    float x[n], y[n];

    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < n; j++)
        {
            x[i] = mat[0][j];
            y[i] = mat[1][j];
        } 
    }

    for(i = 0; i < n; i++) {
        sumYX += x[i] * y[i];
        sumX += x[i];
        sumY += y[i];
        sumX2 += x[i] * x[i];
    }
    sum2X = sumX * sumX;

    *m = (sumYX - (sumX * sumY) / (float)n) / (sumX2 - sum2X / (float)n);
    *b = sumY / (float)n - *m * sumX / (float)n;

    printf("coeficiente m: %.2f \ntermo independente b: %.2f \n", *m, *b);
    
}

void trend(float m, float b, int n, float mat[n][n])
{

    int i;
    float y, x[n];

    for (i = 0; i < n; i++)
    {
        x[i] = mat[0][i];
    }
    

    for (i = 0; i < n; i++)
    {
        y = 0.0;
        y = (m*x[i]) + b;
        printf("Y[%d] = %.2f", i, y);
    }
}

void AjusteExponencial(int tam, float mat[tam][tam])
{
    float x[tam];
    float y[tam];
    int i, j, k;

    for (i = 0; i < 1; i++)
    {
        for (j = 0; j < tam; j++)
        {
            x[i] = mat[0][j];
            y[i] = mat[1][j];
        } 
    }
    float soma_x, soma_x2, soma_y, soma_xy;

    for (i = 0; i < tam; i++)
    {
        soma_x += x[i];
        soma_x2 += (x[i] * x[i]);
        soma_y += y[i];
        soma_xy += (x[i] * y[i]);
    }

    // 5b + 14,4a = 68
    // 14,4b + 58,4a = 249,99

    float aux[2][2], b2, sub, indep[2], result[2];
    float *vetresult = malloc(2 * sizeof(int));

    aux[0][0] = tam;
    aux[0][1] = soma_x;
    aux[1][0] = soma_x;
    aux[1][1] = soma_x2;

    indep[0] = soma_y;
    indep[1] = soma_xy;

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if (j > i)
            {
                b2 = ((aux[j][i]) / (aux[i][i]));

                for (k = 0; k < 2; k++)
                {
                    aux[j][k] = aux[j][k] - b2 * aux[i][k];
                }

                indep[j] = indep[j] - b2 * indep[i];
            }
        }
    }

    for (i = 2 - 1; i >= 0; i--)
    {
        sub = 0;

        for (k = 2 - 1; k >= 0; k--)
        {
            sub += result[k] * aux[i][k];
        }

        result[i] = (indep[i] - sub) / aux[i][i];
    }

    float coef_a, coef_b, vety[tam], aux2;

    coef_b = result[0];
    coef_a = result[1];

    printf("O coeficiente de 'a' eh: %f\n", coef_a);
    printf("O coeficiente de 'b' eh: %f\n\n", coef_b);

    for (i = 0; i < tam; i++)
    {
        aux2 = 1;

        for (j = 0; j <= x[i]; j++)
        {
            aux2 *= coef_b;
        }

        vety[i] = coef_a * aux2;
    }

    printf("Os valores ajustados de Y sao: \n");

    for (i = 0; i < tam; i++)
    {
        printf("y%d: %.2f \n",i+1, vety[i]);
    }
  
}


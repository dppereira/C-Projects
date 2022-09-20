//Projeto-1 feito por Diogo Paiva Pereira, RA: 211152129, Período Noturno.

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////////
//ESTRUTURAS
void cabecalho(p2, x, aux, linha_coluna);
void limiarizacao(p2, limiar, linha_coluna);
void negativo(p2, neg, linha_coluna);
void histograma(p2, hist, linha_coluna);
///////////////////////////////////////////////////////////////////////////////////////////////
//FUNCOES

int main(void)
{
    int reprocessamento, escolha_operacoes;
    int *linha_coluna;

    linha_coluna = malloc(2 * sizeof(int));

    FILE *p2;

    do
    {

        p2 = fopen("exemplo.pgm", "rt");

        if (p2 == NULL)
        {
            printf("Erro ao abrir");
            return 0;
        }

        do
        {
            printf("Escolha qual operacao deseja resolver: \n(1) Limiarizacao\n(2) Negativo\n(3) Histograma\n");
            scanf("%d", &escolha_operacoes);

        } while (escolha_operacoes == 1 && escolha_operacoes == 2 && escolha_operacoes == 3);

        switch (escolha_operacoes)
        {
        case 1:
        {
            FILE *limiar;

            limiar = fopen("limiarizacao.pgm", "wt");

            if (limiar == NULL)
            {
                printf("Erro ao abrir");
                return 0;
            }
            limiarizacao(p2, limiar, linha_coluna);

            fclose(p2);
            fclose(limiar);

            break;
        }
        case 2:
        {
            FILE *neg;

            neg = fopen("negativo.pgm", "wt");

            if (neg == NULL)
            {
                printf("Erro ao abrir");
                return 0;
            }

            negativo(p2, neg, linha_coluna);

            fclose(p2);
            fclose(neg);

            break;
        }
        case 3:
        {
            FILE *hist;

            hist = fopen("histograma.txt", "wt");

            if (hist == NULL)
            {
                printf("Erro ao abrir");
                return 0;
            }

            histograma(p2, hist, linha_coluna);

            fclose(p2);
            fclose(hist);

            break;
        }
        }

        do
        {
            printf("Deseja resolver novamente? Sim = 1 e Nao = 0\n");
            scanf("%d", &reprocessamento);
        } while (reprocessamento == 1 && reprocessamento == 0);

        if (reprocessamento == 0)
        {
            break;
        }

    } while (reprocessamento == 1);
}

void cabecalho(FILE *p2, FILE *x, int aux, int *linha_coluna)
{
    char line[10];
    int intensidade_max;

    fscanf(p2, "%[^\n]\n", line);

    for (int i = 0; i < 2; i++)
    {
        fscanf(p2, "%d ", &linha_coluna[i]);
    }

    fscanf(p2, "%d", &intensidade_max);

    if (aux == 0)
    {
        fprintf(x, "%s\n", line);

        for (int i = 0; i < 2; i++)
        {
            fprintf(x, "%d ", linha_coluna[i]);
        }

        fprintf(x, "\n%d\n", intensidade_max);
    }
}

void limiarizacao(FILE *p2, FILE *limiar, int *linha_coluna)
{
    int linha, coluna, i, j, pixel, aux = 0;

    cabecalho(p2, limiar, aux, linha_coluna);

    for (i = 0; i < linha_coluna[0]; i++)
    {
        for (j = 0; j < linha_coluna[1]; j++)
        {
            fscanf(p2, "%d", &pixel);

            if (pixel > 150)
            {
                pixel = 255;
            }
            else
                pixel = 0;

            fprintf(limiar, "%d\n", pixel);
        }
    }

    printf("A operacao foi concluida com exito\n");
}

void negativo(FILE *p2, FILE *neg, int *linha_coluna)
{
    int linha, coluna, i, j, pixel, aux = 0;

    cabecalho(p2, neg, aux, linha_coluna);

    for (i = 0; i < linha_coluna[0]; i++)
    {
        for (j = 0; j < linha_coluna[1]; j++)
        {
            fscanf(p2, "%d", &pixel);

            pixel = 255 - pixel;

            fprintf(neg, "%d\n", pixel);
        }
    }

    printf("A operacao foi concluida com exito\n");
}

void histograma(FILE *p2, FILE *hist, int *linha_coluna)
{
    int linha, coluna, i, j, pixel, aux = 1;
    int histo[256];

    cabecalho(p2, hist, aux, linha_coluna);

    for (i = 0; i < 256; i++)
    {
        histo[i] = 0;
    }

    for (i = 0; i < linha_coluna[0]; i++)
    {
        for (j = 0; j < linha_coluna[1]; j++)
        {
            fscanf(p2, "%d", &pixel);

            histo[pixel] += 1;
        }
    }

    for (i = 0; i < 256; i++)
    {
        fprintf(hist, "Tonalidade %d = %d\n", i, histo[i]);
    }

    printf("A operacao foi concluida com exito\n");
}
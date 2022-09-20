#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define TAM_NAME 50
#define MAX_PRODUTOS 5

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ESTRUTURAS

typedef struct PRODUTOS
{
    char name[TAM_NAME];
    float price_buy;
    float price_sale;
    int quantidade;
    int sales;
    int id;
} PRODUTOS;

typedef struct REGISTRO
{
    char chave[TAM_NAME];
    int index;
} REGISTRO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SUB-ROTINAS
void partition(int Esq, int Dir, int *i, int *j, REGISTRO *v);
void sort(int Esq, int Dir, REGISTRO *v);
void quicksort(REGISTRO *v, int n);
void openFILE();
void cadastro(FILE *fp_chaveProdutos, FILE *fp_infoProdutos);
void posicionaProduto(FILE *fp, int key);
void sellProducts(FILE *fp_chaveProdutos, FILE *fp_infoProdutos);
void new_product(FILE *fp_chaveProdutos, FILE *fp_infoProdutos);
void showProducts(FILE *fp_infoprodutos, FILE *fp_chaveprodutos);
void profit(FILE *fp_infoprodutos, FILE *fp_chaveProdutos);
void deleteProducts(FILE *fp_infoprodutos, FILE *fp_chaveProdutos);
void totalSales(FILE *fp_chaveProdutos, FILE *fp_infoProdutos);
void reload(FILE *fp_chaveProdutos, FILE *fp_infoProdutos);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN E FUNCOES

int main()
{
    int menu;
    openFILE();

    FILE *fp_chaveProdutos, *fp_infoProdutos;

    fp_chaveProdutos = fopen("chave.bin", "r+b");
    fp_infoProdutos = fopen("infs.bin", "r+b");

    if (fp_chaveProdutos == NULL || fp_infoProdutos == NULL)
    {
        printf("Falha ao criar o arquivo\n");
        return 0;
    }

    cadastro(fp_chaveProdutos, fp_infoProdutos);

    fclose(fp_chaveProdutos);
    fclose(fp_infoProdutos);

    fflush(stdin);
    do
    {
        printf("\n---------------------------MENU---------------------------\n");
        printf("1-Vender\n2-Cadastrar novo produto\n3-Remover do estoque\n4-Consultar estoque\n5-Consultar lucro\n6-Repor estoque\n0-Sair\n");
        printf("Escolha uma opçao do menu: ");
        scanf("%d", &menu);
        fflush(stdin);

        fp_chaveProdutos = fopen("chave.bin", "r+b");
        fp_infoProdutos = fopen("infs.bin", "r+b");

        if (fp_chaveProdutos == NULL || fp_infoProdutos == NULL)
        {
            printf("Falha ao criar o arquivo\n");
            return 0;
        }

        switch (menu)
        {
        case 1:
            printf("\n---------------------------VENDA---------------------------\n");
            sellProducts(fp_chaveProdutos, fp_infoProdutos);
            fclose(fp_infoProdutos);
            fclose(fp_chaveProdutos);
            break;
        case 2:
        {
            printf("\n---------------------------NOVO PRODUTO---------------------------\n");
            new_product(fp_chaveProdutos, fp_infoProdutos);
            fclose(fp_infoProdutos);
            fclose(fp_chaveProdutos);
        }
        break;
        case 3:
            printf("Remover produto...");
            break;
        case 4:
            printf("\n---------------------------CONSULTAR ESTOQUE---------------------------\n");
            showProducts(fp_infoProdutos, fp_chaveProdutos);
            fclose(fp_infoProdutos);
            fclose(fp_chaveProdutos);
            break;
        case 5:
            printf("\n---------------------------LUCRO---------------------------\n");
            profit(fp_infoProdutos, fp_chaveProdutos);
            fclose(fp_infoProdutos);
            fclose(fp_chaveProdutos);
            break;
        case 6:
            printf("\n---------------------------REABASTECER ESTOQUE---------------------------\n");
            reload(fp_chaveProdutos, fp_infoProdutos);
            fclose(fp_infoProdutos);
            fclose(fp_chaveProdutos);
            break;
        case 0:
            printf("\n---------------------------SAIR---------------------------\n");
            totalSales(fp_chaveProdutos, fp_infoProdutos);
            fclose(fp_infoProdutos);
            fclose(fp_chaveProdutos);
            printf("Finalizando o programa, obrigado volte sempre!");
            break;
        default:
            printf("opcao invalida");
            break;
        }
    } while (menu != 0);
}

void partition(int Esq, int Dir, int *i, int *j, REGISTRO *v)
{
    REGISTRO x, w;
    *i = Esq;
    *j = Dir;
    x = v[(*i + *j) / 2];

    do
    {
        while (strcmp(x.chave, v[*i].chave) > 0)
            (*i)++;
        while (strcmp(x.chave, v[*j].chave) < 0)
            (*j)--;

        if (*i <= *j)
        {

            w = v[*i];
            v[*i] = v[*j];
            v[*j] = w;
            (*i)++;
            (*j)--;
        }

    } while (*i <= *j);
}
void sort(int Esq, int Dir, REGISTRO *v)
{
    int i, j;
    partition(Esq, Dir, &i, &j, v);
    if (Esq < j)
        sort(Esq, j, v);
    if (i < Dir)
        sort(i, Dir, v);
}
void quicksort(REGISTRO *v, int n)
{
    // printf("\nENTROU");
    sort(0, n - 1, v);
}

void openFILE()
{
    FILE *fp_chaveProdutos;
    FILE *fp_infoProdutos;

    fp_chaveProdutos = fopen("chave.bin", "w+b");
    fp_infoProdutos = fopen("infs.bin", "w+b");

    fclose(fp_infoProdutos);
    fclose(fp_chaveProdutos);
}

void cadastro(FILE *fp_chaveProdutos, FILE *fp_infoProdutos)
{
    PRODUTOS produtos;
    REGISTRO v[5];
    REGISTRO reg;
    int count;
    char opcao[TAM_NAME], mais_prod;
    do
    {
        count = 0;
        int i = 0;
        fseek(fp_chaveProdutos, 0L, SEEK_SET);
        while (fread(&v[count], sizeof(REGISTRO), 1, fp_chaveProdutos) > 0)
        {
            count++;
        }
        printf("Digite o nome do produto que deseja cadastrar!: \n");
        scanf(" %[^\n]%*c", opcao);
        strcpy(produtos.name, opcao);

        produtos.id = count;
        printf("DIGITE O PRECO DE COMPRA: \n");
        scanf("%f", &produtos.price_buy);
        fflush(stdin);
        printf("DIGITE O PRECO DE VENDA: \n");
        scanf("%f", &produtos.price_sale);
        fflush(stdin);
        printf("DIGITE A QUANTIDADE NO ESTOQUE: \n");
        scanf("%d", &produtos.quantidade);
        fflush(stdin);
        printf("DIGITE A QUANTIDADE NO VENDIDA: \n");
        scanf("%d", &produtos.sales);
        fflush(stdin);

        strcpy(reg.chave, produtos.name);

        reg.index = count * sizeof(PRODUTOS);
        posicionaProduto(fp_infoProdutos, produtos.id);

        fseek(fp_chaveProdutos, 0L, SEEK_END);
        fwrite(&reg, sizeof(REGISTRO), 1, fp_chaveProdutos);
        fseek(fp_infoProdutos, 0L, SEEK_END);
        fwrite(&produtos, sizeof(PRODUTOS), 1, fp_infoProdutos);
        fflush(stdin);

        fseek(fp_chaveProdutos, 0L, SEEK_SET);
        while (fread(&v[i], sizeof(REGISTRO), 1, fp_chaveProdutos) > 0)
        {
            i++;
        }
        quicksort(v, i);

        printf("Produto cadastrado com sucesso!\n\n");
        fflush(stdin);
        printf("Deseja cadastrar mais um produto?: ");
        scanf(" %c", &mais_prod);
    } while ((strchr("S", toupper(mais_prod)) && (count <= 3)));
    if (count >= 3)
    {
        printf("O maximo de produtos foi atingido!\n\n");
    }
}

void posicionaProduto(FILE *fp, int key)
{
    fseek(fp, (key) * sizeof(PRODUTOS), SEEK_SET);
}

void sellProducts(FILE *fp_chaveProdutos, FILE *fp_infoProdutos)
{
    PRODUTOS produtos;
    PRODUTOS prod;
    REGISTRO reg;
    REGISTRO v[5];
    int i, quantidade, count = 0;
    float valor_final = 0.0;
    char opcao[50];

    fflush(stdin);
    fseek(fp_chaveProdutos, 0L, SEEK_SET);
    while (fread(&v[count], sizeof(REGISTRO), 1, fp_chaveProdutos) > 0)
    {
        count++;
    }

    fread(v, sizeof(REGISTRO), count, fp_chaveProdutos);

    printf("Digite o nome do produto que deseja comprar: \n");
    scanf(" %[^\n]%*c", opcao);
    fflush(stdin);

    for (i = 0; i < count; i++)
    {
        if (strcmp(opcao, v[i].chave) == 0)
        {
            break;
        }
    }
    if (i == count)
    {
        printf("Nenhum produto encontrado\n");
        return;
    }

    fseek(fp_infoProdutos, v[i].index, SEEK_SET);
    int x = ftell(fp_infoProdutos);

    fread(&prod, sizeof(PRODUTOS), 1, fp_infoProdutos);

    fflush(stdin);
    printf("\nValor do produto: %.2f", prod.price_sale);

    fflush(stdin);
    printf("\nDigite a quantidade que deseja comprar: ");
    scanf("%d", &quantidade);
    if (prod.quantidade < quantidade)
    {
        fflush(stdin);
        printf("Nao ha quantidade suficiente para atender a venda!\n");
        return;
    }
    fflush(stdin);
    prod.sales = prod.sales + quantidade;
    prod.quantidade = prod.quantidade - quantidade;
    valor_final = prod.price_sale * quantidade;
    printf("\nValor da compra: %.2f\n", valor_final);
    fflush(stdin);
    printf("Compra realizada com sucesso!\n\n");
    fflush(stdin);
    fseek(fp_infoProdutos, sizeof(PRODUTOS), SEEK_SET);
    fwrite(&prod, sizeof(PRODUTOS), 1, fp_infoProdutos);
}

void new_product(FILE *fp_chaveProdutos, FILE *fp_infoProdutos)
{
    PRODUTOS produtos;
    REGISTRO v[5];
    REGISTRO reg;
    int i = 0, count = 0;
    char opcao[TAM_NAME];

    fseek(fp_chaveProdutos, 0L, SEEK_SET);
    while (fread(&v[count], sizeof(REGISTRO), 1, fp_chaveProdutos) > 0)
    {
        count++;
    }
    if (count >= 5)
    {
        printf("O maximo de produtos foi atingido!\n\n");
        return;
    }
    printf("Digite o nome do novo produto que deseja cadastrar: \n");
    scanf(" %[^\n]%*c", opcao);
    strcpy(produtos.name, opcao);

    produtos.id = count;
    printf("DIGITE O PRECO DE COMPRA: \n");
    scanf("%f", &produtos.price_buy);
    fflush(stdin);
    printf("DIGITE O PRECO DE VENDA: \n");
    scanf("%f", &produtos.price_sale);
    fflush(stdin);
    printf("DIGITE A QUANTIDADE NO ESTOQUE: \n");
    scanf("%d", &produtos.quantidade);
    fflush(stdin);
    printf("DIGITE A QUANTIDADE NO VENDIDA: \n");
    scanf("%d", &produtos.sales);
    fflush(stdin);

    strcpy(reg.chave, produtos.name);

    reg.index = count * sizeof(PRODUTOS);
    posicionaProduto(fp_infoProdutos, produtos.id);

    fseek(fp_chaveProdutos, 0L, SEEK_END);
    fwrite(&reg, sizeof(REGISTRO), 1, fp_chaveProdutos);
    fseek(fp_infoProdutos, 0L, SEEK_END);
    fwrite(&produtos, sizeof(PRODUTOS), 1, fp_infoProdutos);
    fflush(stdin);

    fseek(fp_chaveProdutos, 0L, SEEK_SET);
    while (fread(&v[i], sizeof(REGISTRO), 1, fp_chaveProdutos) > 0)
    {
        i++;
    }

    quicksort(v, i);

    printf("Produto cadastrado com sucesso!\n\n");
    fflush(stdin);
}

void showProducts(FILE *fp_infoprodutos, FILE *fp_chaveprodutos)
{
    PRODUTOS produtos;
    REGISTRO reg;
    float aux_valor, valor_total = 0;
    int aux_qnt;

    fseek(fp_chaveprodutos, 0L, SEEK_SET);
    while (fread(&reg, sizeof(REGISTRO), 1, fp_chaveprodutos) > 0)
    {

        aux_valor = 0;

        fseek(fp_infoprodutos, reg.index, SEEK_SET); // posiciona o ponteiro dentro do arquivo na posicao index
        fread(&produtos, sizeof(PRODUTOS), 1, fp_infoprodutos);

        fflush(stdin);
        printf("Produto: %s\n", produtos.name);
        printf("Quantidade: %d\n", produtos.quantidade);
        aux_valor = ((float)produtos.quantidade) * produtos.price_buy;
        valor_total += ((float)produtos.quantidade) * produtos.price_buy;
        printf("Valor total: %.2f\n", aux_valor);
    }
    printf("Valor total do estoque: %.2f\n\n", valor_total);
    fflush(stdin);
}

void profit(FILE *fp_infoprodutos, FILE *fp_chaveProdutos)
{
    PRODUTOS produtos;
    REGISTRO v[5];
    float valor_total = 0.0;
    int i, count = 0;

    while (fread(&v[count], sizeof(REGISTRO), 1, fp_chaveProdutos) > 0)
    {
        count++;
    }

    for (i = 0; i < count; i++)
    {
        fseek(fp_infoprodutos, 0L, SEEK_SET);
        posicionaProduto(fp_infoprodutos, i);
        fread(&produtos, sizeof(PRODUTOS), 1, fp_infoprodutos);
        if (produtos.id != -1)
        {
            valor_total = ((float)produtos.sales) * produtos.price_sale;
            fflush(stdin);
            printf("Valor total vendido de %s: %.2f\n\n", produtos.name, valor_total);
            fflush(stdin);
        }
    }
}

void deleteProducts(FILE *fp_infoprodutos, FILE *fp_chaveProdutos)
{
    int count = 0, opcao;
    REGISTRO v[5];

    while (fread(&v[count], sizeof(REGISTRO), 1, fp_chaveProdutos) > 0)
    {
        count++;
    }
    fflush(stdin);
    printf("1-Suco\n2-Refrigerente\n3-Salgadinho frito\n4-Salgadinho assado\n5-Doce\n");
    do
    {
        fflush(stdin);
        printf("\nEscolha uma opçao do menu: ");
        scanf("%d", &opcao);
    } while (opcao < 1 || opcao > 5);
    fflush(stdin);
}

void totalSales(FILE *fp_chaveProdutos, FILE *fp_infoProdutos)
{
    PRODUTOS produtos;
    REGISTRO reg;
    float valor_total, lucro_estoque = 0;
    int aux_qnt, i;

    fseek(fp_chaveProdutos, 0L, SEEK_SET);
    while (fread(&reg, sizeof(REGISTRO), 1, fp_chaveProdutos) > 0)
    {

        valor_total = 0;

        fseek(fp_infoProdutos, reg.index, SEEK_SET);
        fread(&produtos, sizeof(PRODUTOS), 1, fp_infoProdutos);

        fflush(stdin);
        printf("Produto: %s", produtos.name);
        printf(", quantidade vendida: %d", produtos.sales);
        printf(", quantidade que restou no estoque: %d", produtos.quantidade);
        valor_total = ((float)produtos.quantidade) * produtos.price_buy;
        printf(", valor do produto: %.2f", produtos.price_sale);
        printf(", valor em estoque: %.2f\n\n", valor_total);
        lucro_estoque += produtos.sales * produtos.price_sale;
    }
    printf("Lucro total do dia: %.2f\n\n", lucro_estoque);
}

void reload(FILE *fp_chaveProdutos, FILE *fp_infoProdutos)
{
    PRODUTOS produtos;
    PRODUTOS prod;
    REGISTRO reg;
    REGISTRO v[5];
    int i, quantidade, count = 0;
    float valor_final = 0.0;
    char opcao[50];

    fflush(stdin);
    fseek(fp_chaveProdutos, 0L, SEEK_SET);
    while (fread(&v[count], sizeof(REGISTRO), 1, fp_chaveProdutos) > 0)
    {
        count++;
    }

    fread(v, sizeof(REGISTRO), count, fp_chaveProdutos);

    printf("Digite o nome do produto que deseja repor no estoque: \n");
    scanf(" %[^\n]%*c", opcao);
    fflush(stdin);

    for (i = 0; i < count; i++)
    {
        if (strcmp(opcao, v[i].chave) == 0)
        {
            break;
        }
    }
    if (i == count)
    {
        printf("Nenhum produto encontrado\n");
        return;
    }
    fseek(fp_infoProdutos, v[i].index * sizeof(PRODUTOS), SEEK_SET);

    fread(&prod, sizeof(PRODUTOS), 1, fp_infoProdutos);
    fflush(stdin);
    printf("Digite a quantidade que quer repor de(o) %s: ", prod.name);
    do
    {
        scanf("%d", &quantidade);
    } while (quantidade <= 0);

    fflush(stdin);
    prod.quantidade = prod.quantidade + quantidade;
    printf("\nNova quantidade do estoque: %d\n", prod.quantidade);
    printf("Reposicao realizada com sucesso!\n\n");
    fseek(fp_infoProdutos, sizeof(PRODUTOS), SEEK_SET);
    fwrite(&prod, sizeof(PRODUTOS), 1, fp_infoProdutos);
}


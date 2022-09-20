#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////////////////////
// ESTRUTURAS

typedef struct prod
{
    float valor_compra, valor_venda, estoque_fix, estoque_var, inativo;
} produc;

typedef struct pro
{
    char nome[50];
    int num;
} produ;

///////////////////////////////////////////////////////////////////////////////////////////////
// SUB-ROTINAS

int Venda(produc *produto, produ *product, int cont_produto);
void quicksort(produ *product, int cont_produto);
void sort(int Esq, int Dir, produ *product);
void partition(int Esq, int Dir, int *i, int *j, produ *product);
int Cadastro_Produtos(produc *produto, produ *product, int cont_produto);
int Remover_Estoque(produc *produto, produ *product, int cont_produto);
int Consulta_Estoque(produc *produto, produ *product, int cont_produto);
int Consulta_Lucro(produc *produto, produ *product, int cont_produto);
int Repor_Estoque(produc *produto, produ *product, int cont_produto);
int Sair(produc *produto, produ *product, int cont_produto, FILE *chave, FILE *infos);

///////////////////////////////////////////////////////////////////////////////////////////////
// FUNCOES

int main(void)
{
    int escolha_operacoes, cont_produto = 1;

    FILE *chave, *infos;

    chave = fopen("chave.bin", "wb");
    infos = fopen("infs.bin", "wb");

    if (chave == NULL || infos == NULL)
    {
        printf("Erro na criacao do arquivo\n");
        return 0;
    }

    produc produto[10];
    produ product[10];

    Cadastro_Produtos(produto, product, cont_produto);

    do
    {

        do
        {

            printf("Escolha a opcao desejada: \n(1) Vender\n(2) Cadastrar novo produto\n(3) Remover produto do estoque\n(4) Consultar estoque\n(5) Consultar lucro\n(6) Repor estoque\n(0) Sair\n");
            scanf("%d", &escolha_operacoes);

        } while (escolha_operacoes == 1 && escolha_operacoes == 2 && escolha_operacoes == 3 && escolha_operacoes == 4 && escolha_operacoes == 5 && escolha_operacoes == 6 && escolha_operacoes == 0);

        switch (escolha_operacoes)
        {
        case 1:
        {

            switch (Venda(produto, product, cont_produto))
            {
            case 0:
            {
                break;
            }
            case 1:
            {
                printf("ERRO: Produto nao encontrado\n");
                break;
            }
            }

            break;
        }
        case 2:
        {

            cont_produto++;
            Cadastro_Produtos(produto, product, cont_produto);

            break;
        }
        case 3:
        {

            Remover_Estoque(produto, product, cont_produto);

            break;
        }
        case 4:
        {

            Consulta_Estoque(produto, product, cont_produto);

            break;
        }
        case 5:
        {

            Consulta_Lucro(produto, product, cont_produto);

            break;
        }
        case 6:
        {

            switch (Repor_Estoque(produto, product, cont_produto))
            {

            case 0:
            {
                break;
            }
            case 1:
            {
                printf("ERRO: Produto nao encontrado\n");
                break;
            }
            }

            break;
        }
        case 0:
        {

            Sair(produto, product, cont_produto, chave, infos);
            fclose(chave);
            fclose(infos);

            break;
        }
        }

    } while (escolha_operacoes != 0);
}

int Venda(produc *produto, produ *product, int cont_produto)
{

    int i;
    float quant;
    char aux[50];

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]%*c", aux);

    for (i = 0; i < cont_produto; i++)
    {
        if (strcmp(aux, product[i].nome) == 0)
        {
            printf("O valor do produto eh de R$%.2f\n", produto[i].valor_venda);

            do
            {
                printf("Informe a quantidade desejada: ");
                scanf("%f", &quant);

                if (quant < produto[i].estoque_var && quant > 0)
                {
                    printf("O valor da compra eh de R$%.2f\n", produto[i].valor_venda * quant);

                    produto[i].estoque_var -= quant;
                }
                else
                    printf("Nao ha estoque disponivel para atender a venda\n");
            } while (quant > produto[i].estoque_var || quant < 1);

            return 0;
        }
    }

    return 1;
}

void partition(int Esq, int Dir, int *i, int *j, produ *product)
{
    produ x, w;
    *i = Esq;
    *j = Dir;

    // pivô
    x = product[(*i + *j) / 2];

    do
    {
        while (strcmp(x.nome, product[*i].nome) > 0)
            (*i)++;
        while (strcmp(x.nome, product[*j].nome) < 0)
            (*j)--;

        if (*i <= *j)
        {

            w = product[*i];
            product[*i] = product[*j];
            product[*j] = w;
            (*i)++;
            (*j)--;
        }

    } while (*i <= *j);
}

void sort(int Esq, int Dir, produ *product)
{
    int i, j;
    partition(Esq, Dir, &i, &j, product);
    if (Esq < j)
        sort(Esq, j, product);
    if (i < Dir)
        sort(i, Dir, product);
}

void quicksort(produ *product, int cont_produto)
{
    sort(0, cont_produto - 1, product);
}

int Cadastro_Produtos(produc *produto, produ *product, int cont_produto)
{

    int i;
    float aux, estoque_fix, valor_compra, valor_venda;

    for (i = 0; i < cont_produto; i++)
    {
        if (produto[i].inativo == 1)
        {
            printf("Digite o nome do produto: ");
            scanf(" %[^\n]", product[i].nome);

            printf("Digite o estoque do produto: ");
            scanf(" %f", &estoque_fix);

            produto[i].estoque_fix = estoque_fix;

            printf("Digite o valor de compra do produto: ");
            scanf("%f", &valor_compra);

            produto[i].valor_compra = valor_compra;

            printf("Digite o valor de venda do produto: ");
            scanf("%f", &valor_venda);

            produto[i].valor_venda = valor_venda;

            aux = produto[i].estoque_fix;
            produto[i].estoque_var = aux;

            produto[i].inativo = 0;

            quicksort(product, cont_produto);

            return 0;
        }
    }

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", product[cont_produto - 1].nome);

    printf("Digite o estoque do produto: ");
    scanf(" %f", &estoque_fix);

    produto[cont_produto - 1].estoque_fix = estoque_fix;

    printf("Digite o valor de compra do produto: ");
    scanf("%f", &valor_compra);

    produto[cont_produto - 1].valor_compra = valor_compra;

    printf("Digite o valor de venda do produto: ");
    scanf("%f", &valor_venda);

    produto[cont_produto - 1].valor_venda = valor_venda;

    aux = produto[cont_produto - 1].estoque_fix;
    produto[cont_produto - 1].estoque_var = aux;

    produto[cont_produto - 1].inativo = 0;

    quicksort(product, cont_produto);

    return 0;
}

int Remover_Estoque(produc *produto, produ *product, int cont_produto)
{
    int i;
    char aux[50];

    printf("Digite o produto que deve ser removido do estoque: ");
    scanf(" %[^\n]%*c", aux);

    for (i = 0; i < cont_produto; i++)
    {
        if (strcmp(aux, product[i].nome) == 0)
        {
            produto[i].inativo = 1;
            product[i].nome[0] = '\0';

            return 0;
        }
    }

    quicksort(product, cont_produto);

    return 1;
}

int Consulta_Estoque(produc *produto, produ *product, int cont_produto)
{
    int i;
    float aux = 0;

    for (i = 0; i < cont_produto; i++)
    {

        printf("Produto: %s\nQuantidade em estoque: %.0f\n", product[i].nome, produto[i].estoque_var);

        printf("Valor do estoque: R$%.2f\n", produto[i].valor_venda * produto[i].estoque_var);

        aux += (produto[i].valor_venda * produto[i].estoque_var);
    }

    printf("Valor total do estoque: R$%.2f\n", aux);

    return 0;
}

int Consulta_Lucro(produc *produto, produ *product, int cont_produto)
{
    int i;

    for (i = 0; i < cont_produto; i++)
    {
        printf("O produto %s gerou R$%.2f de lucro\n", product[i].nome, (produto[i].estoque_fix - produto[i].estoque_var) * produto[i].valor_venda);
    }

    return 0;
}

int Repor_Estoque(produc *produto, produ *product, int cont_produto)
{

    int i;
    float quant;
    char aux[50];

    printf("Digite o nome do produto que deseja repor o estoque: ");
    scanf(" %[^\n]%*c", aux);

    for (i = 0; i < cont_produto; i++)
    {
        if (strcmp(aux, product[i].nome) == 0)
        {
            do
            {
                printf("Informe quantas unidades serao repostas: ");
                scanf("%f", &quant);

            } while (quant < 1);

            produto[i].estoque_fix += quant;
            produto[i].estoque_var += quant;

            printf("O novo estoque eh de %.0f produtos e custou R$%.2f\n", produto[i].estoque_var, quant * produto[i].valor_compra);

            return 0;
        }
    }

    return 1;
}

int Sair(produc *produto, produ *product, int cont_produto, FILE *chave, FILE *infos)
{
    int i, count = 0;
    float aux = 0, aux2 = 0, aux3 = 0;

    fseek(chave, 0, SEEK_SET);
    fseek(infos, 0, SEEK_SET);

    while (fread(&product[count], sizeof(produ), 1, chave) > 0)
    {
        count++;

        product[count].num = count * sizeof(produ);
    }

    count = 0;

    while (fread(&produto[count], sizeof(produc), 1, infos) > 0)
    {
        count++;
    }

    fseek(chave, 0, SEEK_SET);
    fseek(infos, 0, SEEK_SET);

    for (i = 0; i < cont_produto; i++)
    {
        if (produto[i].inativo == 0)
        {
            fwrite(&product[i].nome, sizeof(produ), 1, chave);

            fputs("\n", chave);

            fwrite(&produto[i].estoque_fix, sizeof(produc), 1, infos);
            fwrite(&produto[i].estoque_var, sizeof(produc), 1, infos);
            fwrite(&produto[i].valor_compra, sizeof(produc), 1, infos);
            fwrite(&produto[i].valor_venda, sizeof(produc), 1, infos);
            fputs("\n", infos);
            fflush(stdin);
        }
    }

    for (i = 0; i < cont_produto; i++)
    {
        if (produto[i].inativo == 0)
        {
            printf("Produto: %s\nQuantidade vendida: %.0f\n", product[i].nome, produto[i].estoque_fix - produto[i].estoque_var);

            printf("Quantidade no estoque: %.0f\nPreco do produto: R$%.2f\n", produto[i].estoque_var, produto[i].valor_venda);

            printf("Valor em estoque desse produto: R$%.2f\n\n", produto[i].estoque_var * produto[i].valor_venda);

            aux += (produto[i].estoque_fix - produto[i].estoque_var);
            aux2 += ((produto[i].estoque_fix - produto[i].estoque_var) * produto[i].valor_venda);
            aux3 += (produto[i].estoque_var * produto[i].valor_venda);
        }
    }

    printf("Valor total em estoque: R$%.2f\n", aux3);
    printf("Total de vendas efetuadas: %.0f\n", aux);
    printf("Lucro total do dia: R$%.2f\n", aux2);

    return 0;
}

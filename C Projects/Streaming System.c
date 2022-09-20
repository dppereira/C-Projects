#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ESTRUTURAS

typedef struct cid
{
    int CPF, status;
    char nome[50], email[50], telefone[15]; // telefone = 19-9-XXXX-XXXX
} client;

enum gen
{
    AVENTURA,
    COMEDIA,
    DRAMA,
    TERROR,
    ACAO,
    ROMANCE
};

enum class
{
    LIVRE,
    MAIS_10,
    MAIS_12,
    MAIS_14,
    MAIS_16,
    MAIS_18
};

typedef struct film
{
    int codigo, genero, classificacao; // codigo comeca no 1001 e vai incrementando +1
    char nome[50];
} Filme;

typedef struct basic
{
    float valor_base, valor_excedente; // excedente por filme adicional assistido
    int quantidade_filmes;             // quantidade de filmes por mes
} basicos;

typedef struct vip
{
    float valor_base;
} premiums;

typedef union aplan
{
    basicos basico;
    premiums premium;
} Aplano;

typedef struct plan
{
    Aplano uniao_plano;
} planos;

enum pag
{
    DEBITO = 0,
    CREDITO
};

typedef struct deb
{
    int num_agencia, num_conta;
} Debito;

typedef struct cred
{
    int num_card_cred;
} Credito;

typedef union PAgamento
{
    Credito credito;
    Debito debito;
} TPagamento;

typedef struct SPagamento
{
    TPagamento uniao_pagamento;
} Pagamento;

typedef struct contract
{
    int CPF, tipo_plano, tipo_pagamento; // cliente somente pode ter 1 contrato
    Pagamento pagamento;
    planos plano;
    int data_contract_dia, data_contract_mes;
    int data_cancel_dia, data_cancel_mes; // data = dia/mes e data_cancel(standard)=00/00

} Contrato;

typedef struct hist
{
    int codigo_filme, data_filme; //matriz [10][30] / maximo de filmes por mes = 30
} hist_men;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SUB-ROTINAS
int cadastrarCliente(client *cliente, int cont_cliente);                                                                                                                                                            //1
int cadastrarFilme(Filme *filme, int cont_filme);                                                                                                                                                                   //2
int cadastrarBasico(basicos *basico);                                                                                                                                                                               //3
int cadastrarPremium(premiums *premium);                                                                                                                                                                            //4
int cadastrarContrato(Contrato *contrato, client *cliente, int data_mes, int cont_cliente, int cont_contrato);                                                                                                      //5
int carregarFilme(hist_men historico[][30], Filme *filme, client *cliente, Contrato *contrato, basicos *basico, premiums *premium, int cont_cliente, int cont_filme, int cont_contrato, int larg);                  //6
int cancelarContrato(client *cliente, Contrato *contrato, basicos *basico, premiums *premium, hist_men historico[][30], int cont_contrato, int cont_cliente, int larg, int data_mes);                               //7
int Fatura(int tam, client *cliente, hist_men historico[][30], int cont_cliente, Contrato *contrato, int cont_contrato, basicos *basico, premiums *premium, int cont_filme, int larg, Filme *filme, int *data_mes); //8
int listardadosCliente(client *cliente, int tam);                                                                                                                                                                   //9
int listarhistCliente(hist_men historico[0][30], client *cliente, Filme *filme, int cont_cliente, int cont_filme, int larg, int data_mes);                                                                          //10
int listarClienteexcedente(hist_men historico[][30], client *cliente, Contrato *contrato, int cont_cliente, int cont_contrato, basicos basico, int larg);                                                           //11
int frequenciaFilme(hist_men historico[][30], Filme *filme, int cont_filme, int tam, int larg);                                                                                                                     //12
int recomendarFilme(hist_men historico[][30], client *cliente, Filme *filme, int cont_filme, int cont_cliente, int larg);                                                                                           //13
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN E FUNCOES

int main(void) //0
{
    const int tam = 10, larg = 30;
    int i, j, menu, data_mes = 1; // data_mes = 1 = janeiro
    int cont_cliente = 0, cont_filme = 0, cont_contrato = 0;

    client cliente[tam];
    Filme filme[tam];
    basicos basico;
    premiums premium;
    Contrato contrato[tam];
    hist_men historico[tam][larg];

    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < larg; j++)
        {
            historico[i][j].codigo_filme = 0;
            historico[i][j].data_filme = 0;
        }
    }

    do
    {
        //printf("Escolha no menu de opcao: 1-13, pra sair: 0");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
        {
            if (cont_cliente == tam)
            {
                printf("ERRO: Numero maximo de clientes no sistema atingido\n");
            }
            else
            {
                switch (cadastrarCliente(cliente, cont_cliente))
                {
                case 0:
                {
                    printf("ERRO: CPF do cliente ja cadastrado\n");
                    break;
                }
                case 1:
                {
                    printf("Cliente cadastrado com sucesso\n");
                    cont_cliente++;
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case 2:
        {
            if (cont_filme == tam)
            {
                printf("ERRO: Numero maximo de filmes no sistema atingido\n");
            }
            else
            {
                switch (cadastrarFilme(filme, cont_filme))
                {
                case 0:
                {
                    printf("Filme cadastrado com sucesso\n");
                    cont_filme++;
                }
                default:
                    break;
                }
            }
            break;
        }
        case 3:
        {
            switch (cadastrarBasico(&basico))
            {
            case 1:
            {
                printf("Plano Basico cadastrado com sucesso\n");
                break;
            }
            default:
                break;
            }
            break;
        }
        case 4:
        {
            switch (cadastrarPremium(&premium))
            {
            case 1:
            {
                printf("Plano Premium cadastrado com sucesso\n");
                break;
            }
            default:
                break;
            }
            break;
        }
        case 5:
        {
            if (cont_cliente == 0)
            {
                printf("ERRO: Nenhum cliente cadastrado no sistema\n");
                break;
            }
            else if (cont_contrato == tam)
            {
                printf("ERRO: Numero maximo de contratos no sistema atingido\n");
            }
            else
            {
                switch (cadastrarContrato(contrato, cliente, data_mes, cont_cliente, cont_contrato))
                {
                case 0:
                {
                    printf("ERRO: Cliente nao cadastrado\n");
                    break;
                }
                case 1:
                {
                    printf("ERRO: Cliente com contrato existente\n");
                    break;
                }
                case 2:
                {
                    printf("Contrato cadastrado com sucesso\n");
                    cont_contrato++;
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
            break;
        }
        case 6:
        {
            if (cont_contrato == 0)
            {
                printf("ERRO: Nenhum cliente cadastrado no sistema\n");
                break;
            }
            else
            {
                switch (carregarFilme(historico, filme, cliente, contrato, &basico, &premium, cont_cliente, cont_filme, cont_contrato, larg))
                {
                case 0:
                {
                    printf("ERRO: Cliente nao ativo\n");
                    break;
                }
                case 1:
                {
                    printf("ERRO: Cliente nao cadastrado\n");
                    break;
                }
                case 2:
                {
                    printf("ERRO: Numero maximo de filmes no sistema atingido\n");
                    break;
                }
                case 3:
                {
                    printf("ERRO: Filme nao encontrado\n");
                    break;
                }
                case 4:
                {
                    printf("ERRO: Taxa adicional negada\n");
                    break;
                }
                case 5:
                {
                    printf("Filme carregado com sucesso\n");
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
            break;
        }
        case 7:
        {
            if (cont_contrato == 0)
            {
                printf("ERRO: Nenhum contrato cadastrado no sistema\n");
                break;
            }
            else
            {
                switch (cancelarContrato(cliente, contrato, &basico, &premium, historico, cont_contrato, cont_cliente, larg, data_mes))
                {
                case 0:
                {
                    printf("ERRO: Cliente nao ativo\n");
                    break;
                }
                case 1:
                {
                    printf("ERRO: Cliente nao cadastrado\n");
                    break;
                }
                case 2:
                {
                    printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
                    break;
                }
                case 3:
                {
                    printf("Cancelamento feito com sucesso\n");
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
            break;
        }
        case 8:
        {
            switch (Fatura(tam, cliente, historico, cont_cliente, contrato, cont_contrato, &basico, &premium, cont_filme, larg, filme, &data_mes))
            {
            case 0:
            {
                printf("ERRO: Cliente nao cadastrado\n");
                break;
            }
            case 1:
            {
                printf("ERRO: Cliente nao possui contrato\n");
                break;
            }
            default:
            {
                break;
            }
            }
            break;
        }
        case 9:
        {
            if (cont_cliente == 0)
            {
                printf("ERRO: Nenhum cliente cadastrado no sistema\n");
                break;
            }
            else
            {
                switch (listardadosCliente(cliente, tam))
                {
                case 0:
                {
                    printf("ERRO: Cliente nao cadastrado\n");
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
            break;
        }
        case 10:
        {
            if (cont_cliente == 0)
            {
                printf("ERRO: Nenhum cliente cadastrado no sistema\n");
                break;
            }
            else
            {
                switch (listarhistCliente(historico, cliente, filme, cont_cliente, cont_filme, larg, data_mes))
                {
                case 0:
                    printf("ERRO: Cliente nao cadastrado\n");
                    break;
                case 1:
                    printf("ERRO: Nenhum filme assistido\n");
                    break;
                }
            }
            break;
        }
        case 11:
        {
            switch (listarClienteexcedente(historico, cliente, contrato, cont_cliente, cont_contrato, basico, larg))
            {
            case 0:
            {
                printf("ERRO: Nenhum cliente excedente\n");
                break;
            }
            default:
            {
                break;
            }
            }
            break;
        }
        case 12:
        {
            if (cont_filme == 0)
            {
                printf("ERRO: Nenhum filme cadastrado no sistema\n");
                break;
            }
            else
            {
                switch (frequenciaFilme(historico, filme, cont_filme, tam, larg))
                {
                case 0:
                {
                    printf("ERRO: Nenhum filme assistido\n");
                    break;
                }
                case 1:
                {
                    printf("ERRO: Codigo invalido\n");
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
            break;
        }
        case 13:
        {
            if (cont_cliente == 0)
            {
                printf("ERRO: Nenhum cliente cadastrado no sistema\n");
            }
            else
            {
                switch (recomendarFilme(historico, cliente, filme, cont_filme, cont_cliente, larg))
                {
                case 0:
                {
                    printf("ERRO: Cliente nao ativo\n");
                    break;
                }
                case 1:
                {
                    printf("ERRO: Cliente nao cadastrado\n");
                    break;
                }
                case 2:
                {
                    printf("ERRO: Nenhum filme assistido\n");
                    break;
                }
                case 3:
                {
                    printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
            break;
        }
        case 0:
        {
            printf("Finalizando programa...");
            break;
        }
        default:
        {
            printf("ERRO: Opcao invalida\n");
            break;
        }
        }
    } while (menu != 0);
}

int cadastrarCliente(client *cliente, int cont_cliente) //1
{
    int CPF, i;

    //printf("Digite seu CPF");
    scanf(" %d", &CPF);

    for (i = 0; i < cont_cliente; i++)
    {
        if (CPF == cliente[i].CPF)
        {
            return 0;
        }
    }

    cliente[cont_cliente].CPF = CPF;
    //printf("Digite seu nome");
    scanf(" %[^\n]", cliente[cont_cliente].nome);
    //printf("Digite seu email");
    scanf(" %[^\n]", cliente[cont_cliente].email);
    //printf("Digite seu telefone");
    scanf(" %[^\n]", cliente[cont_cliente].telefone);
    cliente[cont_cliente].status = 0;

    return 1;
}

int cadastrarFilme(Filme *filme, int cont_filme) //2
{
    int genero, classificacao;

    filme[cont_filme].codigo = 1001 + cont_filme;

    //printf("Digite o nome do filme");
    scanf(" %[^\n]", filme[cont_filme].nome);

    do
    {
        //printf("Digite o genero do filme");
        scanf(" %d", &genero);

        if (genero <= ROMANCE || genero >= AVENTURA)
        {
            filme[cont_filme].genero = genero;
            break;
        }
        else
            printf("ERRO: Genero invalido\n");

    } while (genero > ROMANCE || genero < AVENTURA);

    do
    {
        //printf("Digite a classificacao do filme");
        scanf(" %d", &classificacao);

        if (classificacao <= MAIS_18 || classificacao >= LIVRE)
        {
            filme[cont_filme].classificacao = classificacao;
            break;
        }
        else
            printf("ERRO: Classificao invalida\n");

    } while (classificacao > MAIS_18 || classificacao < LIVRE);

    return 0;
}

int cadastrarBasico(basicos *basico) //3
{
    //printf("Digite quantidade de filmes por mes");
    scanf("%d", &basico->quantidade_filmes);
    //printf("Digite o valor base do plano");
    scanf("%f", &basico->valor_base);
    //printf("Digite o valor exedente");
    scanf("%f", &basico->valor_excedente);
    return 1;
}

int cadastrarPremium(premiums *premium) //4
{
    //printf("Digite o valor base do plano");
    scanf("%f", &premium->valor_base);

    return 1;
}

int cadastrarContrato(Contrato *contrato, client *cliente, int data_mes, int cont_cliente, int cont_contrato) //5
{
    int i, CPF, tipo_plano, tipo_pagamento, dia_contrato, aux, aux2, cont;

    aux = 0;
    cont = 0;

    //printf("Digite o CPF do Cliente(Chave de busca)");
    scanf("%d", &CPF);

    for (i = 0; i < cont_cliente; i++)
    {
        if (CPF == cliente[i].CPF)
        {
            if (cliente[i].status == 1)
            {
                return 1;
            }
            else
            {
                aux++;
                break;
            }
        }
        cont++;
    }

    if (aux == 0)
    {
        return 0;
    }
    else
    {
        contrato[cont_contrato].CPF = cliente[cont].CPF;

        do
        {
            //printf("Qual seu tipo de plano? 0-1")
            scanf("%d", &tipo_plano);

            switch (tipo_plano)
            {
            case 0:
            {
                contrato[cont_contrato].tipo_plano = tipo_plano;
                aux2 = 0;
                break;
            }
            case 1:
            {
                contrato[cont_contrato].tipo_plano = tipo_plano;
                aux2 = 0;
                break;
            }
            default:
            {
                printf("ERRO: Tipo de plano invalido\n");
                aux2 = 1;
                break;
            }
            }
        } while (aux2 == 1);

        do
        {
            //printf("Qual seu tipo de pagamento? 0-1")
            scanf("%d", &tipo_pagamento);

            switch (tipo_pagamento)
            {
            case DEBITO:
            {
                contrato[cont_contrato].tipo_pagamento = tipo_pagamento;
                scanf("%d %d", &contrato[cont_contrato].pagamento.uniao_pagamento.debito.num_agencia, &contrato[cont_contrato].pagamento.uniao_pagamento.debito.num_conta);
                aux2 = 0;
                break;
            }
            case CREDITO:
            {
                contrato[cont_contrato].tipo_pagamento = tipo_pagamento;
                //printf("Numero cartao de credito")
                scanf("%d", &contrato[cont_contrato].pagamento.uniao_pagamento.credito.num_card_cred);
                aux2 = 0;
                break;
            }
            default:
            {
                printf("ERRO: Tipo de pagamento invalido\n");
                aux2 = 1;
                break;
            }
            }
        } while (aux2 == 1);
    }

    do
    {
        //printf("Qual o dia do inicio do contrato?")
        scanf("%d", &dia_contrato);

        if (dia_contrato > 0 && dia_contrato < 32)
        {
            contrato[cont_contrato].data_contract_dia = dia_contrato;
            aux2 = 0;
        }
        else
        {
            printf("ERRO: Dia invalido\n");
            aux2 = 1;
        }

    } while (aux2 == 1);

    contrato[cont_contrato].data_contract_mes = data_mes;
    contrato[cont_contrato].data_cancel_dia = 0;
    contrato[cont_contrato].data_cancel_mes = 0;
    cliente[cont].status = 1;
    return 2;
}

int carregarFilme(hist_men historico[][30], Filme *filme, client *cliente, Contrato *contrato, basicos *basico, premiums *premium, int cont_cliente, int cont_filme, int cont_contrato, int larg) //6
{
    int i, CPF, cont_vetor_cliente, cont_vetor_contrato, cont_vetor_historico, cont_filmes_assistidos, dia, tipo_lista;
    int cod_filme, valor_extra, tipo_restricao, aux, aux2;

    aux2 = 0;
    aux = 0;
    cont_vetor_cliente = 0;
    cont_vetor_contrato = 0;
    cont_vetor_historico = 0;
    cont_filmes_assistidos = 0;

    //printf("Digite o CPF do Cliente(Chave de busca)");
    scanf("%d", &CPF);

    for (i = 0; i < cont_cliente; i++)
    {
        if (CPF == cliente[i].CPF)
        {
            if (cliente[i].status == 0)
            {
                return 0;
            }
            else
            {
                aux++;
                break;
            }
        }
        cont_vetor_cliente++;
    }

    if (aux == 0)
    {
        return 1;
    }
    else
    {
        aux = 0;

        for (i = 0; i < larg; i++)
        {
            if (historico[cont_vetor_cliente][i].codigo_filme == 0)
            {
                aux = 1;
                break;
            }
        }

        if (aux == 0)
        {
            return 2;
        }

        for (i = 0; i < cont_contrato; i++)
        {
            if (CPF == contrato[i].CPF)
            {
                break;
            }
            cont_vetor_contrato++;
        }

        do
        {
            //printf("Digite o dia");
            scanf("%d", &dia);

            if (dia > 0 && dia < 32)
            {
                aux2 = 0;
            }
            else
            {
                printf("ERRO: Dia invalido\n");
                aux2 = 1;
            }

        } while (aux2 == 1);

        do
        {
            //printf("Ver lista por: gen(0) ou class(1)";
            scanf(" %d", &tipo_lista);

            if (tipo_lista >= 0 && tipo_lista < 2)
            {
                aux2 = 0;
            }
            else
            {
                printf("ERRO: Escolha invalida\n");
                aux2 = 1;
            }

        } while (aux2 == 1);

        do
        {
            //printf("Ver por restricoes: generos(6) ou classificacoes(6)";
            scanf(" %d", &tipo_restricao);

            if (tipo_restricao >= 0 && tipo_restricao < 6)
            {
                aux2 = 0;
            }
            else
            {
                printf("ERRO: Escolha invalida\n");
                aux2 = 1;
            }

        } while (aux2 == 1);

        for (i = 0; i < cont_filme; i++)
        {
            if (tipo_lista == 0)
            {
                if (tipo_restricao == filme[i].genero)
                {
                    printf("Codigo: %d\n", filme[i].codigo);
                    printf("Nome: %s\n", filme[i].nome);
                }
            }
            else
            {
                if (tipo_restricao == filme[i].classificacao)
                {
                    printf("Codigo: %d\n", filme[i].codigo);
                    printf("Nome: %s\n", filme[i].nome);
                }
            }
        }

        aux = 0;

        //printf("Colocar codigo do filme";
        scanf("%d", &cod_filme);

        for (i = 0; i < cont_filme; i++)
        {
            if (cod_filme == filme[i].codigo)
            {
                aux++;
                break;
            }
        }
        if (aux == 0)
        {
            return 3;
        }
        switch (contrato[cont_vetor_contrato].tipo_plano)
        {
        case 0:
        {
            for (i = 0; i < basico->quantidade_filmes; i++)
            {
                if (historico[cont_vetor_cliente][i].codigo_filme == 0)
                {
                    break;
                }
                else
                {
                    cont_filmes_assistidos++;
                }
                cont_vetor_historico++;
            }
            if (cont_filmes_assistidos >= basico->quantidade_filmes)
            {
                aux2 = 0;
                do
                {
                    //printf("Deseja assistir pagando-se um valor extra a ser adicionado na fatura? N(0) ou S(1)";
                    scanf("%d", &valor_extra);
                    if (valor_extra == 0)
                    {
                        return 4;
                    }
                    else if (valor_extra == 1)
                    {
                        for (i = 0; i < larg; i++)
                        {
                            if (historico[cont_vetor_cliente][i].codigo_filme == 0)
                            {
                                aux2++;
                                break;
                            }
                            cont_vetor_historico++;
                        }
                    }
                    else
                        printf("ERRO: Escolha invalida\n");

                } while (aux2 == 0);
            }
        }
        case 1:
        {
            for (i = 0; i < larg; i++)
            {
                if (historico[cont_vetor_cliente][i].codigo_filme == 0)
                {
                    break;
                }
                cont_vetor_historico++;
            }
            break;
        }
        }

        historico[cont_vetor_cliente][cont_vetor_historico].codigo_filme = cod_filme;
        historico[cont_vetor_cliente][cont_vetor_historico].data_filme = dia;
        return 5;
    }
}

int cancelarContrato(client *cliente, Contrato *contrato, basicos *basico, premiums *premium, hist_men historico[][30], int cont_contrato, int cont_cliente, int larg, int data_mes) //7
{
    int i, CPF, cont_vetor_cliente, cont_vetor_contrato, cont, aux, dia;
    float fatura;

    aux = 0;
    cont_vetor_cliente = 0;
    cont_vetor_contrato = 0;

    //printf("Digite o CPF do Cliente(Chave de busca)");
    scanf("%d", &CPF);

    for (i = 0; i < cont_cliente; i++)
    {
        if (CPF == cliente[i].CPF)
        {
            if (cliente[i].status == 0)
            {
                return 0;
            }
            else
            {
                aux++;
                break;
            }
        }
        cont_vetor_cliente++;
    }

    if (aux == 0)
    {
        return 1;
    }
    else
    {
        aux = 0;
        for (i = 0; i < cont_contrato; i++)
        {
            if (CPF == contrato[i].CPF)
            {
                break;
            }
            cont_vetor_contrato++;
        }

        do
        {
            //printf("Digite o dia");
            scanf("%d", &dia);

            if (dia > 0 && dia < 32)
            {
                aux = 0;
            }
            else
            {
                printf("ERRO: Dia invalido\n");
                aux = 1;
            }

        } while (aux == 1);

        if (contrato[cont_vetor_contrato].data_contract_mes == data_mes)
        {
            if (dia > contrato[cont_vetor_contrato].data_contract_dia)
            {
                if (contrato[cont_vetor_contrato].tipo_plano == 0)
                {
                    cont = 0;
                    for (i = 0; i < basico->quantidade_filmes; i++)
                    {
                        if (historico[cont_vetor_cliente][i].codigo_filme == 0)
                        {
                            fatura = basico->valor_base;
                        }
                    }

                    for (i = 0; i < larg; i++)
                    {
                        if (historico[cont_vetor_cliente][i].codigo_filme == 0)
                        {
                            break;
                        }
                        else
                            cont++;
                    }

                    if (cont >= basico->quantidade_filmes)
                    {
                        aux = cont - basico->quantidade_filmes;
                        fatura = basico->valor_base + (aux * basico->valor_excedente);
                    }
                }
                else
                    fatura = premium->valor_base;

                contrato[cont_vetor_contrato].data_cancel_dia = dia;
                contrato[cont_vetor_contrato].data_cancel_mes = data_mes;
                cliente[cont_vetor_cliente].status = 0;

                printf("Valor devido: %.2f\n", fatura);
            }
            else if (dia < contrato[cont_vetor_contrato].data_contract_dia)
                return 2;
        }
        else
        {
            if (contrato[cont_vetor_contrato].tipo_plano == 0)
            {
                cont = 0;
                aux = 0;
                for (i = 0; i < basico->quantidade_filmes; i++)
                {
                    if (historico[cont_vetor_cliente][i].codigo_filme == 0)
                    {
                        fatura = basico->valor_base;
                    }
                }
                for (i = 0; i < larg; i++)
                {
                    if (historico[cont_vetor_cliente][i].codigo_filme == 0)
                    {
                        break;
                    }
                    else
                        cont++;
                }
                if (cont >= basico->quantidade_filmes)
                {
                    aux = cont - basico->quantidade_filmes;
                    fatura = basico->valor_base + (aux * basico->valor_excedente);
                }
            }
            else
                fatura = premium->valor_base;

            contrato[cont_vetor_contrato].data_cancel_dia = dia;
            contrato[cont_vetor_contrato].data_cancel_mes = data_mes;
            cliente[cont_vetor_cliente].status = 0;
        }

        printf("Valor devido: %.2f\n", fatura);
    }
    return 3;
}

int Fatura(int tam, client *cliente, hist_men historico[][30], int cont_cliente, Contrato *contrato, int cont_contrato, basicos *basico, premiums *premium, int cont_filme, int larg, Filme *filme, int *data_mes) //8
{

    int i, j, k, l, CPF, aux, cont_vetor_cliente, cont_vetor_contrato, cont_vetor_historico;
    int escolha, cont = 0, cont2 = 0, filmes_basicos;
    float fatura;

    aux = 0;

    do
    {
        //printf("Digite sua escolha");
        scanf("%d", &escolha);

        if (escolha >= 0 && escolha < 2)
        {
            aux++;
        }
        else
            printf("ERRO: Escolha invalida\n");

    } while (aux == 0);

    if (escolha == 0)
    {
        if (cont_cliente == 0)
        {
            printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        }
        else
        {
            //printf("Digite o CPF do Cliente(Chave de busca)");
            scanf("%d", &CPF);

            for (i = 0; i < cont_cliente; i++)
            {
                if (CPF == cliente[i].CPF)
                {
                    if (cliente[i].status == 0)
                    {
                        return 0;
                    }
                    else
                    {
                        aux++;
                        break;
                    }
                }
                cont_vetor_cliente++;
            }

            if (aux == 0)
            {
                return 1;
            }
            else
            {

                for (i = 0; i < cont_contrato; i++)
                {
                    if (CPF == contrato[i].CPF)
                    {
                        break;
                    }
                    cont_vetor_contrato++;
                }
                if (contrato[cont_vetor_cliente].tipo_plano == 1)
                {
                    fatura = premium->valor_base;
                    for (i = 0; i < larg; i++)
                    {
                        if (historico[cont_vetor_cliente][i].codigo_filme == 0)
                        {
                            cont_vetor_historico = i;
                            break;
                        }
                        else
                        {
                            cont_vetor_historico = larg;
                        }
                    }
                    for (i = 0; i <= cont_vetor_historico; i++)
                    {
                        for (j = 0; j < cont_filme; j++)
                        {
                            if (historico[cont_vetor_cliente][i].codigo_filme == filme[j].codigo)
                            {
                                printf("Nome: %s\n", filme[j].nome);
                                printf("Data: %d/%d\n", historico[cont_vetor_cliente][i].data_filme, *data_mes);
                            }
                        }
                    }
                    printf("Valor devido: %.2f\n", fatura);
                }
                if (contrato[cont_vetor_cliente].tipo_plano == 0)
                {
                    filmes_basicos = basico->quantidade_filmes;
                    for (i = 0; i < filmes_basicos; i++)
                    {
                        if (historico[cont_vetor_cliente][i].codigo_filme == 0)
                        {
                            fatura = basico->valor_base;
                            for (k = 0; k < filmes_basicos; k++)
                            {
                                for (j = 0; j < cont_filme; j++)
                                {
                                    if (historico[cont_vetor_cliente][k].codigo_filme == filme[j].codigo)
                                    {
                                        printf("Nome: %s\n", filme[j].nome);
                                        printf("Data: %d/%d\n", historico[cont_vetor_cliente][k].data_filme, *data_mes);
                                    }
                                }
                            }
                        }
                    }
                    for (i = 0; i < larg; i++)
                    {
                        if (historico[cont_vetor_cliente][i].codigo_filme != 0)
                        {
                            cont++;
                        }
                        if (historico[cont_vetor_cliente][i].codigo_filme == 0)
                        {
                            break;
                        }
                    }
                    if (cont >= filmes_basicos)
                    {
                        cont2 = cont - filmes_basicos;
                        fatura = basico->valor_base + (cont2 * basico->valor_excedente);

                        for (i = 0; i < larg; i++)
                        {
                            for (j = 0; j < cont_filme; j++)
                            {
                                if (historico[cont_vetor_cliente][i].codigo_filme == filme[j].codigo)
                                {
                                    printf("Nome: %s\n", filme[j].nome);
                                    printf("Data: %d/%d\n", historico[cont_vetor_cliente][i].data_filme, *data_mes);
                                }
                            }
                        }
                    }
                    printf("Valor devido: %.2f\n", fatura);
                    return 4;
                }
            }
        }
    }
    if (escolha == 1)
    {
        for (i = 0; i < cont_contrato; i++)
        {
            for (j = 0; j < cont_cliente; j++)
            {
                if (contrato[i].CPF == cliente[j].CPF)
                {
                    if (cliente[j].status == 1)
                    {
                        if (contrato[i].tipo_plano == 1)
                        {
                            fatura = premium->valor_base;
                            printf("CPF: %d\n", contrato[j].CPF);
                            printf("Nome: %s\n", cliente[j].nome);
                            printf("Valor devido: %.2f\n", fatura);
                        }
                        if (contrato[i].tipo_plano == 0)
                        {
                            filmes_basicos = basico->quantidade_filmes;
                            for (k = 0; k <= filmes_basicos; k++)
                            {
                                if (historico[j][k].codigo_filme == 0)
                                {
                                    fatura = basico->valor_base;
                                    printf("CPF: %d\n", contrato[j].CPF);
                                    printf("Nome: %s\n", cliente[j].nome);
                                    printf("Valor devido: %.2f\n", fatura);
                                }
                            }
                            for (l = 0; l < larg; l++)
                            {
                                if (historico[j][l].codigo_filme != 0)
                                {
                                    cont++;
                                }
                            }
                            if (cont >= filmes_basicos)
                            {
                                cont2 = cont - filmes_basicos;
                                fatura = basico->valor_base + (cont2 * basico->valor_excedente);
                                printf("CPF: %d\n", contrato[j].CPF);
                                printf("Nome: %s\n", cliente[j].nome);
                                printf("Valor devido: %.2f\n", fatura);
                            }
                        }
                    }
                }
            }
        }
        printf("Mes vigente apos a fatura: %d\n", *data_mes + 1);
        for (i = 0; i < tam; i++)
        {
            for (j = 0; j < larg; j++)
            {
                historico[i][j].codigo_filme = 0;
                historico[i][j].data_filme = 0;
            }
        }
        *data_mes += 1;
    }
    return 4;
}

int listardadosCliente(client *cliente, int tam) //9
{
    int i, CPF, aux, cont;

    aux = 0;

    //printf("Digite o CPF do Cliente(Chave de busca)");
    scanf(" %d", &CPF);

    for (i = 0; i < tam; i++)
    {
        if (CPF == cliente[i].CPF)
        {
            aux++;
            break;
        }
        cont++;
    }

    if (aux == 0)
    {
        return 0;
    }
    else
    {
        printf("Nome: %s\n", cliente[cont].nome);
        printf("Email: %s\n", cliente[cont].email);
        printf("Telefone: %s\n", cliente[cont].telefone);
        printf("Status: %d\n", cliente[cont].status);
    }
    return 1;
}

int listarhistCliente(hist_men historico[0][30], client *cliente, Filme *filme, int cont_cliente, int cont_filme, int larg, int data_mes) //10
{
    int i, j, CPF, aux, cont, cont2;
    const char *const genero[] = {"aventura", "comedia", "drama", "terror", "acao", "romance"};
    const char *const classificacao[] = {"livre", "+10", "+12", "+14", "+16", "+18"};

    aux = 0;
    cont = 0;
    cont2 = 0;

    //printf("Digite o CPF do Cliente(Chave de busca)");
    scanf(" %d", &CPF);

    for (i = 0; i < cont_cliente; i++)
    {
        if (CPF == cliente[i].CPF)
        {
            aux++;
            break;
        }
        cont++;
    }

    if (aux == 0)
    {
        return 0;
    }
    else
    {
        for (i = 0; i < larg; i++)
        {
            if (historico[cont][i].codigo_filme == 0)
            {
                break;
            }
            else
                cont2++;
        }

        if (cont2 > 0)
        {
            if (cliente[cont].status == 0)
            {
                printf("Estado: Inativo\n");
            }
            else
            {
                printf("Estado: Ativo\n");
            }

            for (i = 0; i < larg; i++)
            {
                for (j = 0; j < cont_filme; j++)
                {
                    if (historico[cont][i].codigo_filme == filme[j].codigo)
                    {
                        printf("Codigo: %d\n", filme[j].codigo);
                        printf("Nome: %s\n", filme[j].nome);
                        printf("Genero: %s\n", genero[filme[j].genero]);
                        printf("Classificacao: %s\n", classificacao[filme[j].classificacao]);
                        printf("Data do carregamento: %d/%d\n", historico[cont][i].data_filme, data_mes);
                        printf("\n");
                    }
                }
            }
            return 2;
        }
        else
        {
            if (cliente[cont].status == 0)
            {
                printf("Estado: Inativo\n");
            }
            else
            {
                printf("Estado: Ativo\n");
            }
            return 1;
        }
    }
}

int listarClienteexcedente(hist_men historico[][30], client *cliente, Contrato *contrato, int cont_cliente, int cont_contrato, basicos basico, int larg) //11
{
    int i, j, cont, cont2, aux;
    float excedente;

    aux = 0;

    for (i = 0; i < cont_contrato; i++)
    {
        cont = 0;
        cont2 = 0;

        if (contrato[i].tipo_plano == 0 && contrato[i].data_cancel_mes == 0 && contrato[i].data_cancel_dia == 0)
        {
            for (j = 0; j < cont_cliente; j++)
            {
                if (cliente[j].CPF == contrato[i].CPF)
                {
                    break;
                }
                cont++;
            }

            for (j = 0; j < larg; j++)
            {
                if (historico[cont][j].codigo_filme == 0)
                {
                    break;
                }
                cont2++;
            }

            if (cont2 > basico.quantidade_filmes)
            {
                aux++;
                excedente = (cont2 - basico.quantidade_filmes) * basico.valor_excedente;
                printf("CPF: %d\n", cliente[cont].CPF);
                printf("Nome: %s\n", cliente[cont].nome);
                printf("Valor excedente: %.2f\n\n", excedente);
            }
        }
    }

    if (aux == 0)
    {
        return 0;
    }
    return 4;
}

int frequenciaFilme(hist_men historico[][30], Filme *filme, int cont_filme, int tam, int larg) //12
{
    int i, j, aux, cont, cod_filme;
    float freq, porcentagem;

    aux = 0;
    cont = 0;

    //printf("Informar codigo do filme a ser calculada a frequencia:")
    scanf("%d", &cod_filme);

    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < cont_filme; j++)
        {
            if (historico[i][j].codigo_filme != 0)
            {
                aux = 1;
                break;
            }
        }
    }
    if (aux == 0)
    {
        return 0;
    }
    else
    {
        aux = 0;

        for (i = 0; i < cont_filme; i++)
        {
            if (cod_filme == filme[i].codigo)
            {
                aux = 1;
            }
        }

        if (aux == 0)
        {
            return 1;
        }
        else
        {
            aux = 0;
            cont = 0;

            for (i = 0; i < tam; i++)
            {
                for (j = 0; j < larg; j++)
                {
                    if (cod_filme == historico[i][j].codigo_filme)
                    {
                        aux++;
                    }

                    if (historico[i][j].codigo_filme == 0)
                    {
                        break;
                    }
                    else
                        cont++;
                }
            }

            porcentagem = 100;
            freq = ((float)aux) / cont;

            printf("Frequencia: %.2f%%\n", porcentagem * freq);
        }
    }
    return 2;
}

int recomendarFilme(hist_men historico[][30], client *cliente, Filme *filme, int cont_filme, int cont_cliente, int larg) //13
{
    const int tam = 6;
    int i, j, k, CPF, aux, cont, cont2, film;
    int vetor_filme[tam], *vetor_filme1, maior, cont_gen;
    const char *const genero[] = {"aventura", "comedia", "drama", "terror", "acao", "romance"};
    const char *const classificacao[] = {"livre", "+10", "+12", "+14", "+16", "+18"};

    aux = 0;
    cont = 0;
    cont2 = 1;
    maior = 0;
    cont_gen = 0;
    film = 0;

    for (i = 0; i < tam; i++)
    {
        vetor_filme[i] = 0;
    }

    vetor_filme1 = malloc(sizeof(int));

    //printf("Digite o CPF do Cliente(Chave de busca)");
    scanf(" %d", &CPF);

    for (i = 0; i < cont_cliente; i++)
    {
        if (CPF == cliente[i].CPF)
        {
            aux++;
            if (cliente[i].status == 0)
            {
                return 0;
            }
            break;
        }
        cont++;
    }

    if (aux == 0)
    {
        return 1;
    }
    else
    {
        if (historico[cont][0].codigo_filme == 0)
        {
            return 2;
        }
        else
        {

            for (i = 0; i < tam; i++)
            {
                if (historico[cont][i].codigo_filme == 0)
                {
                    break;
                }
                else
                {
                    for (j = 0; j < cont_filme; j++)
                    {
                        if (historico[cont][i].codigo_filme == filme[j].codigo)
                        {
                            switch (filme[j].genero)
                            {
                            case 0:
                                vetor_filme[0] += 1;
                                break;
                            case 1:
                                vetor_filme[1] += 1;
                                break;
                            case 2:
                                vetor_filme[2] += 1;
                                break;
                            case 3:
                                vetor_filme[3] += 1;
                                break;
                            case 4:
                                vetor_filme[4] += 1;
                                break;
                            case 5:
                                vetor_filme[5] += 1;
                                break;
                            }
                            break;
                        }
                    }
                }
            }

            for (i = 0; i < tam; i++)
            {
                if (vetor_filme[i] == 0)
                {
                    continue;
                }
                else if (vetor_filme[i] > maior)
                {
                    maior = vetor_filme[i];
                    vetor_filme1[cont2 - 1] = i;
                }
                else if (vetor_filme[i] == maior)
                {
                    cont2++;
                    vetor_filme1 = realloc(vetor_filme1, sizeof(int) * cont2);
                    vetor_filme1[cont2 - 1] = i;
                }
            }

            for (i = 0; i < cont_filme; i++)
            {
                if (filme[i].genero == vetor_filme1[cont2 - 1])
                {
                    cont_gen++;
                }
            }

            if (maior >= cont_gen)
            {
                return 3;
            }

            for (i = 0; i < cont2; i++)
            {
                for (j = 0; j < cont_filme; j++)
                {
                    film = 0;

                    if (vetor_filme1[i] == filme[j].genero)
                    {
                        for (k = 0; k < tam; k++)
                        {
                            if (historico[cont][k].codigo_filme == filme[j].codigo)
                            {
                                film = 1;
                                break;
                            }
                            else if (historico[cont][k].codigo_filme == 0)
                            {
                                break;
                            }
                        }

                        if (film == 0)
                        {
                            printf("Codigo: %d\n", filme[j].codigo);
                            printf("Nome: %s\n", filme[j].nome);
                            printf("Genero: %s\n", genero[filme[j].genero]);
                            printf("Classificacao: %s\n", classificacao[filme[j].classificacao]);
                        }
                    }
                }
            }
        }
    }
    return 4;
}

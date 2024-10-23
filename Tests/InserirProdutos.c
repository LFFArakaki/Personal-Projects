#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARACTERES 200

int ch;
struct produtos {
        int codigo;
        char nome[CARACTERES];
        char descricao[CARACTERES];
        float preco;
        int quantidade;
    };
    
void inserirProdutos(struct produtos* produto, int numeroDeProdutos);
void mudarProdutos(struct produtos* produto, int i);
void ordenar(struct produtos* produto, int numeroDeProdutos);
void exibirProdutos(struct produtos* produto, int numeroDeProdutos);
void menuOpcoes(struct produtos* produto, int numeroDeProdutos);
void faseCompra(struct produtos* produto, int numeroDeProdutos);
int checarCodigoValido(struct produtos* produto, int numeroDeProdutos, int codCompra);
int confirmarResposta();

int main()
{
    int numeroDeProdutos, x;
    x=0;
    
    printf("FASE - Inserção de produtos:\n\n");
    printf("Quantos produtos diferentes a loja oferece?\n");
    scanf("%i",&numeroDeProdutos);
    while((ch = getchar()) != '\n' && ch != EOF);
    
    struct produtos produto[numeroDeProdutos];
    
    inserirProdutos(produto, numeroDeProdutos);
    ordenar(produto, numeroDeProdutos);
    menuOpcoes(produto, numeroDeProdutos);
    

    return 0;
}

void inserirProdutos(struct produtos* produto, int numeroDeProdutos)
{
    for(int i=0;i<numeroDeProdutos;i++)
    {
        produto[i].codigo = i+1;
        printf("Qual o nome do produto %i?\n",i+1);
        fgets(produto[i].nome, 200, stdin);
        printf("Dê uma descrição para esse produto\n");
        fgets(produto[i].descricao, 200, stdin);
        printf("Qual o preço desse produto?\n");
        scanf("%f",&produto[i].preco);
        printf("Quantos desse produto tem em estoque?\n");
        scanf("%i",&produto[i].quantidade);
        while((ch = getchar()) != '\n' && ch != EOF);
    }
    return;
}

void ordenar(struct produtos* produto, int numeroDeProdutos)
{
    int mudancas, intTemporario;
    char stringTemporaria[CARACTERES];
    mudancas = 1;
    
    while(mudancas == 1)
    {
        mudancas = 0;
        
        for(int i = 0;i<numeroDeProdutos;i++)
        {
            if(strcmp(produto[i].nome, produto[i+1].nome) > 0)
            {
                mudarProdutos(produto, i);
                mudancas = 1;
            }
        }
    }
    return;
}

void mudarProdutos(struct produtos* produto, int i)
{
    int intTemporario;
    float fltTemporario;
    char stringTemporaria[CARACTERES];
    
    strcpy(stringTemporaria, produto[i].nome);
    strcpy(produto[i].nome, produto[i+1].nome);
    strcpy(produto[i+1].nome, stringTemporaria);
    
    strcpy(stringTemporaria, produto[i].descricao);
    strcpy(produto[i].descricao, produto[i+1].descricao);
    strcpy(produto[i+1].descricao, stringTemporaria);
    
    fltTemporario = produto[i].preco;
    produto[i].preco = produto[i+1].preco;
    produto[i+1].preco = fltTemporario;
    
    intTemporario = produto[i].quantidade;
    produto[i].quantidade = produto[i+1].quantidade;
    produto[i+1].quantidade = intTemporario;
    
    intTemporario = produto[i].codigo;
    produto[i].codigo = produto[i+1].codigo;
    produto[i+1].codigo = intTemporario;
    
    return;
    
}

void exibirProdutos(struct produtos* produto, int numeroDeProdutos)
{
    printf("\n------------------------------------------------------------------------------------------------------\n");
    printf("|                                         TABELA DE PRODUTOS                                         |\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("|CODIGO|        NOME        |                     DESCRIÇÃO                     |  PREÇO  |QUANTIDADE|\n");
    for(int i=0;i<numeroDeProdutos;i++)
    {
        produto[i].nome[strcspn(produto[i].nome, "\n")] = '\0';
        produto[i].descricao[strcspn(produto[i].descricao, "\n")] = '\0';
        printf("------------------------------------------------------------------------------------------------------\n");   
        printf("|%-6i|%-20s|%-51s|%9.2f|%10i|\n",produto[i].codigo, produto[i].nome, produto[i].descricao, produto[i].preco, produto[i].quantidade);
    }
    printf("------------------------------------------------------------------------------------------------------\n"); 
    return;
}

void menuOpcoes(struct produtos* produto, int numeroDeProdutos)
{
    int resposta;
    
    printf("\nO que deseja fazer?\n");
    printf("0 - Finalizar compra/1 - Comprar um produto/2 - Ver lista de produtos\n");
    
    scanf("%i",&resposta);
    
    if(resposta < 0 || resposta > 2)
    {
        printf("Resposta inválida!\n");
        printf("Digite o número ao lado da ação que deseja tomar\n");
        menuOpcoes(produto, numeroDeProdutos);
    }
    else
    {
        switch(resposta)
        {
            case 0:
                printf("Obrigado por comprar conosco!\n");
                printf("Encerrando o programa!");
                exit (0);
                break;
            case 1:
                faseCompra(produto, numeroDeProdutos);
                menuOpcoes(produto, numeroDeProdutos);
                break;
            case 2:
                exibirProdutos(produto, numeroDeProdutos);
                menuOpcoes(produto, numeroDeProdutos);
                break;
        }
    }
}

void faseCompra(struct produtos* produto, int numeroDeProdutos)
{
    int codCompra, quantidadeCompra;
    
    printf("FASE - Compra de produtos:\n\n");
    printf("Digite o código do produto que deseja comprar: ");
    scanf("%i",&codCompra);
    printf("Deseja mesmo comprar o produto '%s'?\n",produto[checarCodigoValido(produto, numeroDeProdutos, codCompra)].nome);
    if(confirmarResposta() == 0)
    {
        menuOpcoes(produto, numeroDeProdutos);
    }
    printf("Quantos(as) '%s' deseja comprar?\n",produto[checarCodigoValido(produto, numeroDeProdutos, codCompra)].nome);
    printf("(Quantidade em estoque: %i)\n",produto[checarCodigoValido(produto, numeroDeProdutos, codCompra)].quantidade);
    scanf("%i",&quantidadeCompra);
    if(quantidadeCompra > produto[checarCodigoValido(produto, numeroDeProdutos, codCompra)].quantidade)
    {
        printf("Quantidade insuficiente em estoque\n");
        menuOpcoes(produto, numeroDeProdutos);
    }
    printf("Deseja mesmo comprar %i unidade(s) do produto '%s'?\n",quantidadeCompra, produto[checarCodigoValido(produto, numeroDeProdutos, codCompra)].nome);
    if(confirmarResposta() == 0)
    {
        menuOpcoes(produto, numeroDeProdutos);
    }
    else
    {
        produto[checarCodigoValido(produto, numeroDeProdutos, codCompra)].quantidade = 
        produto[checarCodigoValido(produto, numeroDeProdutos, codCompra)].quantidade - quantidadeCompra;
        printf("Compra realizada com sucesso!\n");
        menuOpcoes(produto, numeroDeProdutos);
    }
}

int checarCodigoValido(struct produtos* produto, int numeroDeProdutos, int codCompra)
{
    for(int i=0;i<numeroDeProdutos;i++)
    {
        if(produto[i].codigo == codCompra)
        {
            return i;
        }
    }
    
    printf("Produto inexistente\n");
    menuOpcoes(produto, numeroDeProdutos);
}

int confirmarResposta()
{
    int resposta;
    
    printf("0 - Não/ 1 - Sim\n");
    scanf("%i",&resposta);
    if(resposta < 0 || resposta > 1)
    {
        printf("Resposta inválida!\n");
        printf("Digite o número ao lado da opção que deseja\n");
        confirmarResposta();
    }
    return resposta;
}
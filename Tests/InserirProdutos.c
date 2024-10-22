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

int main()
{
    int numeroDeProdutos;
    
    printf("FASE - Inserção de produtos:\n\n");
    printf("Quantos produtos diferentes a loja oferece?\n");
    scanf("%i",&numeroDeProdutos);
    while((ch = getchar()) != '\n' && ch != EOF);
    
    struct produtos produto[numeroDeProdutos];
    
    inserirProdutos(produto, numeroDeProdutos);
    ordenar(produto, numeroDeProdutos);
    exibirProdutos(produto, numeroDeProdutos);

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
    
}

void exibirProdutos(struct produtos* produto, int numeroDeProdutos)
{
    printf("\n|CODIGO|        NOME        |                     DESCRIÇÃO                    |  PREÇO  |QUANTIDADE|\n");
    for(int i=0;i<numeroDeProdutos;i++)
    {
        produto[i].nome[strcspn(produto[i].nome, "\n")] = '\0';
        produto[i].descricao[strcspn(produto[i].descricao, "\n")] = '\0';
        printf("|%-6i|%-20s|%-50s|%9.2f|%10i|\n",produto[i].codigo, produto[i].nome, produto[i].descricao, produto[i].preco, produto[i].quantidade);
    }
    return;
}
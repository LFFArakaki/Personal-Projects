#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHARACTERS 100
#define MAXPRODUTOS 500

struct produto {
        int codigo;
		char nome[CHARACTERS];
		int quantidade;
		double preco;
	};
	
int menuOpcoes();
void incluirProduto();
void alterarProduto();
void excluirProduto();
void comprarProduto();
void consultarProduto();
void listarProdutos(struct produto *ponteiroProdutos);

int main()
{
    int loop;
    struct produto produtos[MAXPRODUTOS];
    struct produto *ponteiroProdutos = produtos;
    loop=0;
    
    while(loop == 0)
    {
        switch (menuOpcoes())
        {
            case 0:
            printf("Obrigado por utilizar nosso programa!\n");
            fflush(stdin);
            return 0;
            break;
            case 1:
            listarProdutos(ponteiroProdutos);
            break;
            case 2:
            fflush(stdin);
            break;
            case 3:
            printf("D");
            break;
            case 4:
            printf("E");
            break;
            case 5:
            printf("F");
            break;
            case 6:
            printf("G");
            break;
        }
    }
	
	return 0;
}

int menuOpcoes()
{
    int resposta;
    
    printf("O que deseja fazer?\n");
    printf("0 - Finalizar compra\n");
    printf("1 - Incluir um produto\n");
    printf("2 - Alterar um produto\n");
    printf("3 - Excluir um produto\n");
    printf("4 - Comprar um produto\n");
    printf("5 - Consultar um produto\n");
    printf("6 - Ver lista de produtos\n");
    
    scanf("%i",&resposta);
    
    if(resposta < 0 || resposta > 6)
    {
        printf("Resposta inválida!\n");
        printf("Digite o numero ao lado da ação que deseja tomar\n");
        menuOpcoes(ponteiroProdutos);
    }
    else
    {
        return resposta;
    }
}

void incluirProduto()
{
    
}

void alterarProduto()
{
    
}

void excluirProduto()
{
    
}

void comprarProduto()
{
    
}

void consultarProduto()
{
 
}

void listarProdutos(struct produto *ponteiroProdutos)
{
    printf("\n----------------------------------------------------\n");
    printf("|                TABELA DE PRODUTOS                |\n");
    printf("----------------------------------------------------\n");
    printf("|  ID  |        NOME        |   PREÇO   |QUANTIDADE|\n");
    for(int i=0;i<MAXPRODUTOS;i++)
    {
        (ponteiroProdutos + i)->nome[strcspn((ponteiroProdutos + i)->nome, "\n")] = '\0';
        printf("----------------------------------------------------\n");   
        printf("|%-6i|%-20s|%11.2f|%10i|\n",(ponteiroProdutos + i)->codigo, (ponteiroProdutos + i)->nome, (ponteiroProdutos + i)->preco, (ponteiroProdutos + i)->quantidade);
    }
    printf("----------------------------------------------------\n"); 
    return;
}
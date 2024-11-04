#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CARACTERES 100
#define MAXPRODUTOS 3

int ch;
struct produto {
        int codigo;
		char nome[CARACTERES];
		int quantidade;
		float preco;
	};
	
int menuOpcoes();
void incluirProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos);
void alterarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos);
void excluirProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos);
void comprarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos);
void consultarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos);
void listarProdutos(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos);
void mudarProdutos(struct produto *ponteiroProdutos, int i);

int main()
{
    int loop, numeroDeProdutos;
    int *ponteiroNumeroDeProdutos = &numeroDeProdutos;
    struct produto produtos[MAXPRODUTOS];
    struct produto *ponteiroProdutos = produtos;
    
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
            if(numeroDeProdutos == MAXPRODUTOS)
            {
                printf("Não é possível cadastrar mais produtos no momento!\n");
                printf("Exclua um produto e tente novamente!\n");
                break;
            }
            incluirProduto(ponteiroProdutos, ponteiroNumeroDeProdutos);
            break;
            case 2:
            alterarProduto(ponteiroProdutos, ponteiroNumeroDeProdutos);
            break;
            case 3:
            excluirProduto(ponteiroProdutos, ponteiroNumeroDeProdutos);
            break;
            case 4:
            comprarProduto(ponteiroProdutos, ponteiroNumeroDeProdutos);
            break;
            case 5:
            consultarProduto(ponteiroProdutos, ponteiroNumeroDeProdutos);
            break;
            case 6:
            listarProdutos(ponteiroProdutos, ponteiroNumeroDeProdutos);
            break;
        }
    }
	
	return 0;
}

int menuOpcoes()
{
    int resposta;
    
    printf("\nO que deseja fazer?\n");
    printf("0 - Finalizar compra\n");
    printf("1 - Incluir um produto\n");
    printf("2 - Alterar um produto\n");
    printf("3 - Excluir um produto\n");
    printf("4 - Comprar um produto\n");
    printf("5 - Consultar um produto\n");
    printf("6 - Ver lista de produtos\n");
    
    scanf("%i",&resposta);
    while((ch = getchar()) != '\n' && ch != EOF);
    
    if(resposta < 0 || resposta > 6)
    {
        printf("Resposta inválida!\n");
        printf("Digite o numero ao lado da ação que deseja tomar\n");
        menuOpcoes();
    }
    else
    {
        return resposta;
    }
}

void incluirProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos)
{
    (ponteiroProdutos + *ponteiroNumeroDeProdutos)->codigo = *ponteiroNumeroDeProdutos+1;
    printf("Qual o nome do produto %i?\n",*ponteiroNumeroDeProdutos+1);
    fgets((ponteiroProdutos + *ponteiroNumeroDeProdutos)->nome, 100, stdin);
    printf("Qual o preço desse produto?\n");
    scanf("%f",&(ponteiroProdutos + *ponteiroNumeroDeProdutos)->preco);
    printf("Quantos desse produto tem em estoque?\n");
    scanf("%i",&(ponteiroProdutos + *ponteiroNumeroDeProdutos)->quantidade);
    while((ch = getchar()) != '\n' && ch != EOF);
    
    *ponteiroNumeroDeProdutos = *ponteiroNumeroDeProdutos+1;
    
    return;
}

void alterarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos)
{
    
}

void excluirProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos)
{
    
}

void comprarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos)
{
    
}

void consultarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos)
{

}

void listarProdutos(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos)
{
    printf("\n----------------------------------------------------\n");
    printf("|                TABELA DE PRODUTOS                |\n");
    printf("----------------------------------------------------\n");
    printf("|  ID  |        NOME        |   PREÇO   |QUANTIDADE|\n");
    for(int i=0;i<*ponteiroNumeroDeProdutos;i++)
    {
        (ponteiroProdutos + i)->nome[strcspn((ponteiroProdutos + i)->nome, "\n")] = '\0';
        printf("----------------------------------------------------\n");   
        printf("|%-6i|%-20s|%11.2f|%10i|\n",(ponteiroProdutos + i)->codigo, (ponteiroProdutos + i)->nome, (ponteiroProdutos + i)->preco, (ponteiroProdutos + i)->quantidade);
    }
    printf("----------------------------------------------------\n"); 
    return;
}

void mudarProdutos(struct produto *ponteiroProdutos, int i)
{
    int intTemporario;
    float fltTemporario;
    char stringTemporaria[CARACTERES];
    
    strcpy(stringTemporaria, (ponteiroProdutos + i)->nome);
    strcpy((ponteiroProdutos + i)->nome, (ponteiroProdutos + i+1)->nome);
    strcpy((ponteiroProdutos + i+1)->nome, stringTemporaria);
    
    fltTemporario = (ponteiroProdutos + i)->preco;
    (ponteiroProdutos + i)->preco = (ponteiroProdutos + i+1)->preco;
    (ponteiroProdutos + i+1)->preco = fltTemporario;
    
    intTemporario = (ponteiroProdutos + i)->quantidade;
    (ponteiroProdutos + i)->quantidade = (ponteiroProdutos + i+1)->quantidade;
    (ponteiroProdutos + i+1)->quantidade = intTemporario;
    
    intTemporario = (ponteiroProdutos + i)->codigo;
    (ponteiroProdutos + i)->codigo = (ponteiroProdutos + i+1)->codigo;
    (ponteiroProdutos + i+1)->codigo = intTemporario;
    
    return;
    
}
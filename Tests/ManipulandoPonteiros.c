#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CARACTERES 100
#define MAXPRODUTOS 500
#define INICIO 0

int ch;
struct produto {
        int codigo;
		char nome[CARACTERES];
		int quantidade;
		float preco;
	};
	
int menuOpcoes();
void incluirProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos, int *ponteiroProdutosExcluidos);
void alterarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos);
void excluirProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos, int *ponteiroProdutosExcluidos);
void comprarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos);
void consultarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos);
void listarProdutos(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos, int inicio);
void mudarProdutos(struct produto *ponteiroProdutos, int i);
int checarCodigoValido(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos, int codCompra);
int confirmarResposta();

int main()
{
    int loop, numeroDeProdutos, produtosExcluidos;
    int *ponteiroNumeroDeProdutos = &numeroDeProdutos;
    int *ponteiroProdutosExcluidos = &produtosExcluidos;
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
            incluirProduto(ponteiroProdutos, ponteiroNumeroDeProdutos, ponteiroProdutosExcluidos);
            break;
            case 2:
            alterarProduto(ponteiroProdutos, ponteiroNumeroDeProdutos);
            break;
            case 3:
            excluirProduto(ponteiroProdutos, ponteiroNumeroDeProdutos, ponteiroProdutosExcluidos);
            break;
            case 4:
            comprarProduto(ponteiroProdutos, ponteiroNumeroDeProdutos);
            break;
            case 5:
            consultarProduto(ponteiroProdutos, ponteiroNumeroDeProdutos);
            break;
            case 6:
            listarProdutos(ponteiroProdutos, ponteiroNumeroDeProdutos, INICIO);
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

void incluirProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos, int *ponteiroProdutosExcluidos)
{
    (ponteiroProdutos + *ponteiroNumeroDeProdutos)->codigo = *ponteiroNumeroDeProdutos+(*ponteiroProdutosExcluidos+1);
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
    int codCompra, resposta, i;
    
    printf("Digite o codigo do produto que deseja alterar: ");
    scanf("%i",&codCompra);
    
    if(checarCodigoValido(ponteiroProdutos, ponteiroNumeroDeProdutos, codCompra)<0)
    {
        return;
    }
    
    i = checarCodigoValido(ponteiroProdutos, ponteiroNumeroDeProdutos, codCompra);
    
    retorno:
    printf("O que deseja alterar no produto %s?\n",(ponteiroProdutos + i)->nome);
    printf("0 - Encerrar alterações\n");
    printf("1 - Alterar nome\n");
    printf("2 - Alterar preço\n");
    printf("3 - Alterar quantidade em estoque\n");
    scanf("%i",&resposta);
    
    switch(resposta)
    {
        case 0:
        return;
        break;
        case 1:
        char novoNome[CARACTERES];
        printf("Qual nome deseja colocar?\n");
        printf("(Nome atual: '%s')\n",(ponteiroProdutos + i)->nome);
        scanf("%s",novoNome);
        strcpy((ponteiroProdutos + i)->nome, novoNome);
        break;
        case 2:
        float novoPreco;
        printf("Qual preço deseja colocar?\n");
        printf("(Preço atual: '%.2f')\n",(ponteiroProdutos + i)->preco);
        scanf("%f",&novoPreco);
        (ponteiroProdutos + i)->preco = novoPreco;
        break;
        case 3:
        int novaQuantidade;
        printf("Qual quantidade deseja colocar?\n");
        printf("(Quantidade atual: '%i')",(ponteiroProdutos + i)->quantidade);
        scanf("%i",&novaQuantidade);
        (ponteiroProdutos + i)->quantidade = novaQuantidade;
        break;
    }
    
    printf("Deseja alterar mais algo nesse produto?\n");
    if(confirmarResposta() == 0)
    {
        return;
    }
    else
    {
        goto retorno;
    }
}

void excluirProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos, int *ponteiroProdutosExcluidos)
{
    int codCompra, i;
    
    printf("Digite o codigo do produto que deseja excluir: ");
    scanf("%i",&codCompra);
    
    if(checarCodigoValido(ponteiroProdutos, ponteiroNumeroDeProdutos, codCompra)<0)
    {
        return;
    }
    
    i = checarCodigoValido(ponteiroProdutos, ponteiroNumeroDeProdutos, codCompra);
    
    printf("Tem certeza que deseja excluir o produto %s?\n",(ponteiroProdutos + i)->nome);
    if(confirmarResposta() == 0)
    {
        return;
    }
    strcpy((ponteiroProdutos + i)->nome, " ");
    (ponteiroProdutos + i)->codigo = 0;
    (ponteiroProdutos + i)->preco = 0;
    (ponteiroProdutos + i)->quantidade = 0;
    
    for(i=i;i<*ponteiroNumeroDeProdutos;i++)
    {
        mudarProdutos(ponteiroProdutos, i);
    }
    
    *ponteiroNumeroDeProdutos = *ponteiroNumeroDeProdutos-1;
    *ponteiroProdutosExcluidos = *ponteiroProdutosExcluidos+1;
    
    printf("Produto excluído com sucesso!\n");
    return;
}

void comprarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos)
{
    int codCompra, quantidadeCompra, i;
    float precoCompra;
    
    printf("Digite o codigo do produto que deseja comprar: ");
    scanf("%i",&codCompra);
    
    if(checarCodigoValido(ponteiroProdutos, ponteiroNumeroDeProdutos, codCompra)<0)
    {
        return;
    }
    
    i = checarCodigoValido(ponteiroProdutos, ponteiroNumeroDeProdutos, codCompra);
    
    printf("Tem certeza que deseja comprar o produto %s?\n",(ponteiroProdutos + i)->nome);
    if(confirmarResposta() == 0)
    {
        return;
    }
    
    printf("Quantos(as) '%s' deseja comprar?\n",(ponteiroProdutos + i)->nome);
    printf("(Quantidade em estoque: %i)\n",(ponteiroProdutos + i)->quantidade);
    scanf("%i",&quantidadeCompra);
    if(quantidadeCompra > (ponteiroProdutos + i)->quantidade)
    {
        printf("Quantidade insuficiente em estoque\n");
        return;
    }
    if(quantidadeCompra < 1)
    {
        printf("Impossível comprar menos de 1 unidade\n");
        return;
    }
    
    precoCompra = (ponteiroProdutos + i)->preco*quantidadeCompra;
    printf("Deseja mesmo comprar %i unidade(s) do produto '%s'?\n",quantidadeCompra, (ponteiroProdutos + i)->nome);
    printf("A compra irá custar R$%.2f\n",precoCompra);
    if(confirmarResposta() == 0)
    {
        return;
    }
    (ponteiroProdutos + i)->quantidade = (ponteiroProdutos + i)->quantidade - quantidadeCompra;
    printf("Compra realizada com sucesso!\n");
    return;
}

void consultarProduto(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos)
{
    int codCompra, i;
    int *ponteiroIndex = &i;
    
    printf("Digite o codigo do produto que deseja consultar: ");
    scanf("%i",&codCompra);
    
    if(checarCodigoValido(ponteiroProdutos, ponteiroNumeroDeProdutos, codCompra)<0)
    {
        return;
    }
    
    i = checarCodigoValido(ponteiroProdutos, ponteiroNumeroDeProdutos, codCompra);
    *ponteiroIndex = *ponteiroIndex+1;
    
    listarProdutos(ponteiroProdutos, ponteiroIndex, i-1);
    
    return;
}

void listarProdutos(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos, int inicio)
{
    printf("\n----------------------------------------------------\n");
    printf("|                TABELA DE PRODUTOS                |\n");
    printf("----------------------------------------------------\n");
    printf("|  ID  |        NOME        |   PREÇO   |QUANTIDADE|\n");
    for(int i=inicio;i<*ponteiroNumeroDeProdutos;i++)
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

int checarCodigoValido(struct produto *ponteiroProdutos, int *ponteiroNumeroDeProdutos, int codCompra)
{
    for(int i=0;i<*ponteiroNumeroDeProdutos;i++)
    {
        if((ponteiroProdutos + i)->codigo == codCompra)
        {
            return i;
        }
    }
    
    printf("Produto inexistente\n");
    return -1;
}

int confirmarResposta()
{
    int resposta;
    
    printf("0 - Não/ 1 - Sim\n");
    scanf("%i",&resposta);
    if(resposta < 0 || resposta > 1)
    {
        printf("Resposta inválida!\n");
        printf("Digite o numero ao lado da opção que deseja\n");
        confirmarResposta();
    }
    return resposta;
}
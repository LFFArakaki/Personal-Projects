#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define TAMANHOPILHA 5
#define TAMANHOENTRADA 200

char entrada[TAMANHOENTRADA];
int contador;
float calculadora[TAMANHOPILHA];

void converter(char entrada[TAMANHOENTRADA]);
void soma();
void subtracao();
void multiplicacao();
void divisao();
void operacaoSeguida(int i);
void passarValor(float resultado);

int main()
{
    scanf("%s",entrada);
	
	converter(entrada);
    
    for(int i=1;i<TAMANHOPILHA;i++)
    {
        printf("\n%.2f",calculadora[i]);
    }

    return 0;
}

void converter(char entrada[TAMANHOENTRADA]){
    
    float convertido;
    int comprimento = strlen(entrada);
    
    for(int i=0;i<comprimento;i++)
    {
        if(isdigit(entrada[i]))
        {
		    convertido = convertido * 10 + ( entrada[i] - '0' );
        }
        else
        {
            contador++;
            if(contador>=TAMANHOPILHA)
            {
                printf("Expressão inválida!\n");
                return;
            }
            calculadora[contador] = convertido;
            convertido = 0;
            if(entrada[i] == '+')
            {
                operacaoSeguida(i);
                soma();
            }
            if(entrada[i] == '-')
            {
                operacaoSeguida(i);
                subtracao();
            }
            if(entrada[i] == '*')
            {
                operacaoSeguida(i);
                multiplicacao();
            }
            if(entrada[i] == '/')
            {
                operacaoSeguida(i);
                divisao();
            }
        }
	}
}

void soma(){
    
    float resultado;
    
    if(contador <= 1)
    {
        return;
    }
    else
    {
        resultado = calculadora[contador-1] + calculadora[contador];
        passarValor(resultado);
    }
}

void subtracao(){
    
    float resultado;
    
    if(contador <= 1)
    {
        calculadora[contador] = calculadora[contador] - 2*calculadora[contador];
        return;
    }
    else
    {
        resultado = calculadora[contador-1] - calculadora[contador];
        passarValor(resultado);
    }
}

void multiplicacao(){
    
    float resultado;
    
    if(contador <= 1)
    {
        calculadora[contador] = 0;
        return;
    }
    else
    {
        resultado = calculadora[contador-1]*calculadora[contador];
        passarValor(resultado);
    }
}

void divisao(){
    
    float resultado;
    
    if(contador <= 1)
    {
        calculadora[contador] = 0;
        return;
    }
    else
    {
        resultado = calculadora[contador-1]/calculadora[contador];
        passarValor(resultado);
    }
}

void operacaoSeguida(int i){
    
    if(isdigit(entrada[i-1]) == 0)
    {
        contador--;
    }
}

void passarValor(float resultado){
    
    calculadora[contador-1] = resultado;
    calculadora[contador] = 0;
    contador--;
}
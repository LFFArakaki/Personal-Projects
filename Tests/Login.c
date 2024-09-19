#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXUSERS 100
#define MAXUSERNAME 100
#define MAXPASSWORD 100

int users;
char usernames[MAXUSERS][MAXUSERNAME], passwords[MAXUSERS][MAXPASSWORD];

void cadastro();
void login();

int main(){
   
    int answer = 1;
    
    while(answer != 0)
    {
        printf("\nQual processo deseja realizar?\n");
        printf("(1-Cadastro/2-Login/0-Finalizar)\n");
        scanf("%i",&answer);
        if(answer<0 || answer>2)
        {
            printf("Resposta inválida\n");
            main();
        }
        else
        {
            switch(answer)
            {
                case 1:
                cadastro();
                break;
               
                case 2:
                if(users == 0)
                {
                    printf("Não existem usuários registrados ainda\n");
                    main();
                }
                else
                {
                    login();
                    break;
                }
            }
        }
    }
   
   return 0;
}

void cadastro(){
    
    printf("Insira seu username: ");
    scanf("%s",usernames[users]);
    
    if(users>0)
    {
        for(int i=0;i<users;i++)
        {   
            int comp = strcmp(usernames[users-1], usernames[i]);
            if(comp == 0)
            {
                printf("Este username já está registrado\n");
                return;
            }
        }
    }
    
    printf("Insira sua senha: ");
    scanf("%s",passwords[users]);
    
    users++;
}

void login(){
    
    int user;
    char username[MAXUSERNAME], password[MAXPASSWORD];
    
    printf("Insira seu username: ");
    scanf("%s",username);
    
    for(int i=0;i<users;i++)
    {   
        int comp = strcmp(usernames[i], username);
        if(comp == 0)
        {
            user = i;
            break;
        }
        else
        {
            if(i == users-1)
            {
                printf("Este username não existe\n");
                return;
            }
        }
    }
    
    printf("Insira sua senha: ");
    scanf("%s",password);
    
    int comp = strcmp(passwords[user], password);
    if(comp != 0)
    {
        printf("Senha incorreta!\n");
        return;
    }
    else
    {
        printf("Login realizado com sucesso!\n");
    }
}

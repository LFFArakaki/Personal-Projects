#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define CHARACTERS 6
#define LANES 6

int yourKills, yourDamage, yourDeaths, yourVision, yourHeal, yourTank, towers, itemValue, goldValue, result;
float kda, killParticipation, damageParticipation, deathParticipation, visionParticipation, tankParticipation, healParticipation;

void upperCase(char answer[CHARACTERS]);
void enterData();
void summonersRift();
void checkValidRole(char answer[CHARACTERS]);
void summonersRiftData();
void jungleData();
void calculateResultsSR(char role[CHARACTERS]);
void aram();
void calculateResultsAram();
void displayResults();

int main(){
    
    char mode[CHARACTERS];
    
    printf("Qual modo de jogo estava jogando?\n");
    printf("(ARAM/SR)\n");
    scanf("%s",mode);
    upperCase(mode);
    
    if(strcmp(mode, "ARAM") == 0)
    {
        aram();
    }
    else
    {
        if(strcmp(mode, "SR") == 0)
        {
            summonersRift();
        }
        else
        {
            printf("Por favor, insira uma resposta válida\n\n");
            main();
        }
    }
    
    return 0;
}

void summonersRift(){
    
    char role[CHARACTERS];
    
    printf("Qual lane voce jogou?\n");
    printf("(TOP/JNG/MID/ADC/SUP)\n");
    scanf("%s",role);
    upperCase(role);
    checkValidRole(role);
    
    enterData();
    summonersRiftData();
}

void aram(){
    
    enterData();
    displayResults();
}

void enterData(){
    
    int kills, assists, teamKills, teamDamage, teamDeaths, teamTank, teamHeal;
    
    printf("Quantas kills voce pegou?\n");
    scanf("%i",&kills);
    printf("Quantas assists voce pegou?\n");
    scanf("%i",&assists);
    printf("Quantas vezes voce morreu?\n");
    scanf("%i",&yourDeaths);
    printf("Quanta cura/escudo voce deu?\n");
    printf("(Para aliados)\n");
    scanf("%i",&yourHeal);
    printf("Quanto dano voce deu?\n");
    scanf("%i",&yourDamage);
    printf("Quanto dano voce levou?\n");
    scanf("%i",&yourTank);
    printf("Quantos itens completos voce comprou?\n");
    printf("(Sem contar botas)\n");
    scanf("%i",&itemValue);
    printf("Quanto gold voce gerou?\n");
    printf("(Gold gasto em itens + gold que sobrou)\n");
    scanf("%i",&goldValue);
    printf("Quantas kills seu time pegou?\n");
    printf("(Incluindo as suas)\n");
    scanf("%i",&teamKills);
    printf("Quantas vezes seu time morreu?\n");
    printf("(Incluindo as suas)\n");
    scanf("%i",&teamDeaths);
    printf("Quanta cura/escudo seu time teve?\n");
    printf("(Incluindo a sua)\n");
    scanf("%i",&teamHeal);
    printf("Quanto dano seu time deu?\n");
    printf("(Incluindo o seu)\n");
    scanf("%i",&teamDamage);
    printf("Quanto dano seu time levou?\n");
    printf("(Incluindo o seu)\n");
    scanf("%i",&teamTank);
    
    yourKills = kills+assists;
    killParticipation = yourKills/teamKills;
    deathParticipation = (yourDeaths/teamDeaths)*100;
    damageParticipation = (yourDamage/teamDamage)*100;
    healParticipation = (yourHeal/teamHeal)*100;
    tankParticipation = (yourTank/teamTank)*100;
    if(yourDeaths == 0)
    {
        kda = yourKills;
    }
    else
    {
        kda = yourKills/yourDeaths;
    }
    
}

void summonersRiftData(){
    
    int teamVision;
    
    printf("Qual foi seu placar de visão?\n");
    scanf("%i",&yourVision);
    printf("Quantas torres voce levou?\n");
    scanf("%i",&towers);
    printf("Qual foi o placar de visão do seu time?\n");
    printf("(Incluindo o seu)\n");
    scanf("%i",&teamVision);
    
    visionParticipation = (yourVision/teamVision)*100;
}

void jungleData(){
    
}

void calculateResultsAram(){
    
    
}

void calculateResultsSR(char role[CHARACTERS]){
    
}

void upperCase(char answer[CHARACTERS]){
    
    for (int i=0;i<strlen(answer);i++) 
    {
        answer[i] = toupper(answer[i]);
    }
}

void checkValidRole(char answer[CHARACTERS]){
    
    char lanes[LANES][CHARACTERS] = 
    {"TOP", "JNG", "MID", "ADC", "SUP"};
    
    for (int i=0;i<LANES;i++)
    {
        if(strcmp(lanes[i], answer) == 0)
        {
            return;
        }
    }
    
    printf("Por favor, insira uma resposta válida\n\n");
    summonersRift();
}

void displayResults(){
    
    printf("Voce fez %i de dano e participou de %i kills \n", yourDamage, yourKills);
    printf("Voce morreu %i vezes\n", yourDeaths);
    printf("Voce teve parte em %.2d das kills do seu time\n");
    
}
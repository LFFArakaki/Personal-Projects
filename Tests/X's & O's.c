#include <stdio.h>
#include <string.h>

#define MAXBOARDHEIGHT 3
#define MAXBOARDLENGTH 3
#define CHARACTERS 2

char board[MAXBOARDHEIGHT][MAXBOARDLENGTH][CHARACTERS] = {
    {"1", "2", "3"},
    {"4", "5", "6"},
    {"7", "8", "9"}
};
int plays;

void printBoard();
void play(char square[CHARACTERS]);
int entry();
char* convert(int placement);
int checkWinner();

int main()
{
    for(int i=0;i<9;i++)
    {
        printBoard();
        play(convert(entry()));
    }
    return 0;
}

int entry()
{
    int placement;
    
    printf("Digite em qual casa quer jogar");
    scanf("%i",&placement);
    
    return placement;
}

char* convert(int placement)
{
    switch (placement)
    {
        case 1:
        return board[0][0];
        break;
        
        case 2:
        return board[0][1];
        break;
        
        case 3:
        return board[0][2];
        break;
        
        case 4:
        return board[1][0];
        break;
        
        case 5:
        return board[1][1];
        break;
        
        case 6:
        return board[1][2];
        break;
        
        case 7:
        return board[2][0];
        break;
        
        case 8:
        return board[2][1];
        break;
        
        case 9:
        return board[2][2];
        break;
    }
}

void play(char square[CHARACTERS])
{
    char symbol[2];
    
    if(plays%2 == 0)
    {
        strcpy(symbol, "X");
    }
    else
    {
        strcpy(symbol, "O");
    }
    
    strcpy(square, symbol);
    
    plays++;
    
    return;
}

void printBoard()
{
    for(int i=0;i<MAXBOARDLENGTH;i++)
    {
        printf("|");
        for(int j=0;j<MAXBOARDHEIGHT;j++)
        {
            printf("%c|",board[i][j][0]);
        }
        printf("\n");
    }
    
    return;
}

int checkWinner()
{
    
}
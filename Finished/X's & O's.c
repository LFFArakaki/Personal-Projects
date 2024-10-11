#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXBOARDHEIGHT 3
#define MAXBOARDLENGTH 3
#define CHARACTERS 2

char board[MAXBOARDHEIGHT][MAXBOARDLENGTH][CHARACTERS] = {
    {" ", " ", " "},
    {" ", " ", " "},
    {" ", " ", " "}
};
int plays, placement;

void printBoard();
void play(char square[CHARACTERS]);
void entry();
char* convert(int placement);
void checkWinner();
void checkLine();
void checkColumn();
void checkOppositeDiagonal();
void checkMainDiagonal();
void checkDiagonal();
void checkTie();
void checkPossible(char square[CHARACTERS]);
void winMessage();

int main()
{
    int i;
    i = 0;
    
    while(i==0)
    {
        printBoard();
        entry();
        play(convert(placement));
        checkWinner();
    }
    return 0;
}

void entry()
{
    printf("Digite em qual casa quer jogar: \n");
    printf("(1 é a casa no canto superior esquerdo, 9 é a casa no canto inferior direito)\n");
    scanf("%i",&placement);
    if(placement < 1 || placement > 9)
    {
        printf("Por favor, digite um numero de 1 a 9\n");
        entry();
    }
    printf("\n");
    
    checkPossible(convert(placement));
    
    return;
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
    plays++;
    
    if(plays%2 == 0)
    {
        strcpy(symbol, "X");
    }
    else
    {
        strcpy(symbol, "O");
    }
    
    strcpy(square, symbol);
    
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
    printf("\n");
    
    return;
}

void checkWinner()
{
    checkLine();
    checkColumn();
    checkDiagonal();
    checkTie();
    
    return;
}

void checkLine()
{
    int winCount;
    
    for(int i=0;i<MAXBOARDHEIGHT;i++)
    {
        winCount = 1;
        
        for(int j=0;j<MAXBOARDLENGTH;j++)
        {
            if(strcmp(board[i][j], board[i][j+1]) != 0)
            {
                break;
            }
            else
            {
                if(board[i][j][0] == ' ')
                {
                    break;
                }
                else
                {
                    winCount++;
                }
            }
        }
        if(winCount == MAXBOARDLENGTH)
        {
            printBoard();
            winMessage();
            exit(0);
        }
    }
    
    return;
}

void checkColumn()
{
    int winCount;
    
    for(int j=0;j<MAXBOARDLENGTH;j++)
    {
        winCount = 1;
        
        for(int i=0;i<MAXBOARDHEIGHT;i++)
        {
            if(strcmp(board[i][j], board[i+1][j]) != 0)
            {
                break;
            }
            else
            {
                if(board[i][j][0] == ' ')
                {
                    break;
                }
                else
                {
                    winCount++;
                }
            }
        }
        if(winCount == MAXBOARDHEIGHT)
        {
            printBoard();
            winMessage();
            exit(0);
        }
    }
    
    return;
}

void checkOppositeDiagonal()
{
    int j, winCount;
    winCount = 1;
    j = MAXBOARDLENGTH-1;
    
    for(int i=0;i<MAXBOARDHEIGHT;i++)
    {
        if(strcmp(board[i][j], board[i+1][j-1]) != 0)
        {
            break;
        }
        else
        {
            if(board[i][j][0] == ' ')
            {
                break;
            }
            else
            {
                winCount++;
            }
        }
        j--;
    }
    if(winCount == MAXBOARDHEIGHT)
    {
        printBoard();
        winMessage();
        exit(0);
    }
    
    return;
}

void checkMainDiagonal()
{
    int j, winCount;
    winCount = 1;
    j = 0;
    
    for(int i=0;i<MAXBOARDHEIGHT;i++)
    {
        if(strcmp(board[i][j], board[i+1][j+1]) != 0)
        {
            break;
        }
        else
        {
            if(board[i][j][0] == ' ')
            {
                break;
            }
            else
            {
                winCount++;
            }
        }
        j++;
    }
    if(winCount == MAXBOARDHEIGHT)
    {
        printBoard();
        winMessage();
        exit(0);
    }
    
    return;
}

void checkDiagonal()
{
    checkMainDiagonal();
    checkOppositeDiagonal();
    
    return;
}

void checkTie()
{
    int possibility;
    possibility = 0;
    
    for(int j=0;j<MAXBOARDLENGTH;j++)
    {
        for(int i=0;i<MAXBOARDHEIGHT;i++)
        {
            if(board[i][j][0] == ' ')
            {
                possibility++;
                break;
            }
        }
        if(possibility > 0)
        {
            return;
        }
    }
    
    printBoard();
    printf("Deu Velha");
    exit(0);
}

void checkPossible(char square[CHARACTERS])
{
    if(square[0] == ' ')
    {
        return;
    }
    else
    {
        printf("Esta casa já está ocupada\n");
        entry();
    }
}

void winMessage()
{
    if(plays%2 == 0)
    {
        printf("X venceu");
    }
    else
    {
        printf("O venceu");
    }
    
    return;
}
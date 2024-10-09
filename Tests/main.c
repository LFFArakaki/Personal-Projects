#include <stdio.h>

#define MAXBOARDHEIGHT 3
#define MAXBOARDLENGTH 3
#define CHARACTERS 2

char board[MAXBOARDLENGTH][MAXBOARDHEIGHT][CHARACTERS] = {
    {"1", "2", "3"},
    {"4", "5", "6"},
    {"7", "8", "9"}
};
int plays;

void printBoard();

int main()
{
    printBoard();
    return 0;
}

void play()
{
    
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
}
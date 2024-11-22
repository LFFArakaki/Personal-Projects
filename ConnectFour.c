#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINES 6
#define COLUMNS 7
#define CHARACTERS 16
#define YELLOWBG "\e[43m"
#define REDBG "\e[41m"
#define RESET "\e[0m"

void printBoard(char board[LINES][COLUMNS][CHARACTERS]);
void turn(char board[LINES][COLUMNS][CHARACTERS]);
bool placePiece(char board[LINES][COLUMNS][CHARACTERS], char* piece, int* column);

int main()
{
    char board[LINES][COLUMNS][CHARACTERS] = {
        {"   ", "   ", "   ", "   ", "   ", "   ", "   "},
        {"   ", "   ", "   ", "   ", "   ", "   ", "   "},
        {"   ", "   ", "   ", "   ", "   ", "   ", "   "},
        {"   ", "   ", "   ", "   ", "   ", "   ", "   "},
        {"   ", "   ", "   ", "   ", "   ", "   ", "   "},
        {"   ", "   ", "   ", "   ", "   ", "   ", "   "}
    };
    int loop = 1;
    
    printBoard(board);
    
    while(loop==1)
    {
        turn(board);
        printBoard(board);
        scanf("%i",&loop);
    }
    
    fflush(stdin);
    return 0;
}

void printBoard(char board[LINES][COLUMNS][CHARACTERS])
{
    char border[CHARACTERS];
    strcpy(border, RESET "|");
    
    printf(" ----------------------------\n");
    for(int i=0;i<LINES;i++)
    {
        printf("%s",border);
        for(int j=0;j<COLUMNS;j++)
        {
            printf("%s%s",board[i][j], border);
        }
        printf("\n ----------------------------\n");
    }
}

void turn(char board[LINES][COLUMNS][CHARACTERS])
{
    int turnCounter, column;
    int* columnPointer = &column;
    char piece[CHARACTERS];
    
    if(turnCounter%2 == 0)
    {
        printf("\nRed's turn\n");
        strcpy(piece, REDBG "   ");
    }
    else
    {
        printf("\nYellow's turn\n");
        strcpy(piece, YELLOWBG "   ");
    }
    
    printf("In which column would you like to place your piece?\n");
    printf("(1-7)\n");
    scanf("%i",&column);
    if(column > 7 || column < 1)
    {
        printf("Invalid column!\n");
        return;
    }
    else
    {
        column = column-1;
        if(placePiece(board, piece, columnPointer))
        {
            turnCounter++;
            return;
        }
        else
        {
            return;
        }
    }
}

bool placePiece(char board[LINES][COLUMNS][CHARACTERS], char* piece, int* column)
{
    for(int i=LINES;i>0;i--)
    {
        if(strcmp(board[i-1][*column], "   ") == 0)
        {
            strcpy(board[i-1][*column], piece);
            return true;
        }
    }
    
    printf("Column full!");
    return false;
}
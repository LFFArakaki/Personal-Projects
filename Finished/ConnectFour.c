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
bool checkWinner(char board[LINES][COLUMNS][CHARACTERS]);
bool checkWinRow(char board[LINES][COLUMNS][CHARACTERS]);
bool checkWinColumn(char board[LINES][COLUMNS][CHARACTERS]);
bool checkWinMainDiagonals(char board[LINES][COLUMNS][CHARACTERS]);
bool checkWinOppositeDiagonals(char board[LINES][COLUMNS][CHARACTERS]);

int turnCounter;

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
    
    printBoard(board);
    
    while(1)
    {
        turn(board);
        printBoard(board);
        if(checkWinner(board))
        {
            break;
        }
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
    int column;
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
    
    column = column-1;
    
    if(!placePiece(board, piece, columnPointer))
    {
        return;
    }
    
    turnCounter++;
    return;
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

bool checkWinRow(char board[LINES][COLUMNS][CHARACTERS])
{
    int winCounter;
    winCounter = 0;
    
    for(int i=0;i<LINES;i++)
    {
        for(int j=1;j<COLUMNS;j++)
        {
            if(strcmp(board[i][j], board[i][j-1]) == 0 && strcmp(board[i][j], "   ") != 0)
            {
                winCounter++;
            }
            else
            {
                winCounter = 0;
            }
            
            if(winCounter >= 3)
            {
                return true;
            }
        }
    }
    
    return false;
}

bool checkWinColumn(char board[LINES][COLUMNS][CHARACTERS])
{
    int winCounter;
    winCounter = 0;
    
    for(int j=0;j<COLUMNS;j++)
    {
        for(int i=1;i<LINES;i++)
        {
            if(strcmp(board[i][j], board[i-1][j]) == 0 && strcmp(board[i][j], "   ") != 0)
            {
                winCounter++;
            }
            else
            {
                winCounter = 0;
            }
            
            if(winCounter >= 3)
            {
                return true;
            }
        }
    }
    
    return false;
}

bool checkWinMainDiagonals(char board[LINES][COLUMNS][CHARACTERS])
{
    int winCounter, subCounter;
    winCounter = 0;
    subCounter = 0;
    
    for(int j=1;j<COLUMNS;j++)
    {
        for(int i=1;i<LINES;i++)
        {
            if(j == COLUMNS)
            {
                break;
            }
            
            if(strcmp(board[i][j], board[i-1][j-1]) == 0 && strcmp(board[i][j], "   ") != 0)
            {
                winCounter++;
            }
            else
            {
                winCounter = 0;
            }
            
            if(winCounter >= 3)
            {
                return true;
            }
            
            subCounter++;
            j++;
        }
        j = j-subCounter;
        subCounter = 0;
    }
    
    for(int i=2;i<LINES;i++)
    {
        for(int j=1;j<COLUMNS;j++)
        {
            if(i == LINES)
            {
                break;
            }
            
            if(strcmp(board[i][j], board[i-1][j-1]) == 0 && strcmp(board[i][j], "   ") != 0)
            {
                winCounter++;
            }
            else
            {
                winCounter = 0;
            }
            
            if(winCounter >= 3)
            {
                return true;
            }
            
            subCounter++;
            i++;
        }
        i = i-subCounter;
        subCounter = 0;
    }
    
    return false;
}

bool checkWinOppositeDiagonals(char board[LINES][COLUMNS][CHARACTERS])
{
    int winCounter, subCounter;
    winCounter = 0;
    subCounter = 0;
    
    for(int j=COLUMNS-2;j>=0;j--)
    {
        for(int i=1;i<LINES;i++)
        {
            if(j < 0)
            {
                break;
            }
            
            if(strcmp(board[i][j], board[i-1][j+1]) == 0 && strcmp(board[i][j], "   ") != 0)
            {
                winCounter++;
            }
            else
            {
                winCounter = 0;
            }
            
            if(winCounter >= 3)
            {
                return true;
            }
            
            subCounter++;
            j--;
        }
        j = j+subCounter;
        subCounter = 0;
    }
    
    for(int i=2;i<LINES;i++)
    {
        for(int j=COLUMNS-2;j>=0;j--)
        {
            if(i == LINES)
            {
                break;
            }
            
            if(strcmp(board[i][j], board[i-1][j+1]) == 0 && strcmp(board[i][j], "   ") != 0)
            {
                winCounter++;
            }
            else
            {
                winCounter = 0;
            }
            
            if(winCounter >= 3)
            {
                return true;
            }
            
            subCounter++;
            i++;
        }
        i = i-subCounter;
        subCounter = 0;
    }
    
    return false;
}

bool checkWinner(char board[LINES][COLUMNS][CHARACTERS])
{
    if(checkWinRow(board) || checkWinColumn(board) || checkWinMainDiagonals(board) || checkWinOppositeDiagonals(board))
    {
        printf("Win!");
        return true;
    }
    else
    {
        return false;
    }
}
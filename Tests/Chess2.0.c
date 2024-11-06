#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLACKPIECES "\x1b[30m"
#define WHITEPIECES "\x1b[37m"
#define LIGHTBACKGROUND "\e[0;104m"
#define DARKBACKGROUND "\e[44m"
#define RESET "\e[0m"
#define LINES 8
#define COLUMNS 8
#define CHARACTERS 20
#define PIECES 50
#define BORDERS 10
#define FRONTROW 8

struct pieces {
    char representation[CHARACTERS];
    char type[CHARACTERS];
    char color[CHARACTERS];
    int line;
    int column;
    bool hasMoved;
    bool canMove;
};

void printBoard(struct pieces board[LINES][COLUMNS]);
void movePiece(struct pieces* piece, struct pieces* destination);
void checkCheckStraight(struct pieces* piece, struct pieces board[LINES][COLUMNS]);

int main()
{
    struct pieces board[LINES][COLUMNS] = {
        {
            {"Rk1", "Rook", "Black", 1, 1, false, true},
            {"Kt1", "Knight", "Black", 1, 2, false, true},
            {"Bp1", "Bishop", "Black", 1, 3, false, true},
            {"Kg1", "King", "Black", 1, 4, false, true},
            {"Qn1", "Queen", "Black", 1, 5, false, true},
            {"Bp2", "Bishop", "Black", 1, 6, false, true},
            {"Kt2", "Knight", "Black", 1, 7, false, true},
            {"Rk2", "Rook", "Black", 1, 8, false, true},
        },
        {
            {"Pn1", "Pawn", "Black", 2, 1, false, true},
            {"Pn2", "Pawn", "Black", 2, 2, false, true},
            {"Pn3", "Pawn", "Black", 2, 3, false, true},
            {"Pn4", "Pawn", "Black", 2, 4, false, true},
            {"Pn5", "Pawn", "Black", 2, 5, false, true},
            {"Pn6", "Pawn", "Black", 2, 6, false, true},
            {"Pn7", "Pawn", "Black", 2, 7, false, true},
            {"Pn8", "Pawn", "Black", 2, 8, false, true},
        },
        {
            {"   ", "Empty", "Empty", 3, 1, false, false},
            {"   ", "Empty", "Empty", 3, 2, false, false},
            {"   ", "Empty", "Empty", 3, 3, false, false},
            {"   ", "Empty", "Empty", 3, 4, false, false},
            {"   ", "Empty", "Empty", 3, 5, false, false},
            {"   ", "Empty", "Empty", 3, 6, false, false},
            {"   ", "Empty", "Empty", 3, 7, false, false},
            {"   ", "Empty", "Empty", 3, 8, false, false},
        },
        {
            {"   ", "Empty", "Empty", 4, 1, false, false},
            {"   ", "Empty", "Empty", 4, 2, false, false},
            {"   ", "Empty", "Empty", 4, 3, false, false},
            {"   ", "Empty", "Empty", 4, 4, false, false},
            {"   ", "Empty", "Empty", 4, 5, false, false},
            {"   ", "Empty", "Empty", 4, 6, false, false},
            {"   ", "Empty", "Empty", 4, 7, false, false},
            {"   ", "Empty", "Empty", 4, 8, false, false},
        },
        {
            {"   ", "Empty", "Empty", 5, 1, false, false},
            {"   ", "Empty", "Empty", 5, 2, false, false},
            {"   ", "Empty", "Empty", 5, 3, false, false},
            {"   ", "Empty", "Empty", 5, 4, false, false},
            {"   ", "Empty", "Empty", 5, 5, false, false},
            {"   ", "Empty", "Empty", 5, 6, false, false},
            {"   ", "Empty", "Empty", 5, 7, false, false},
            {"   ", "Empty", "Empty", 5, 8, false, false},
        },
        {
            {"   ", "Empty", "Empty", 6, 1, false, false},
            {"   ", "Empty", "Empty", 6, 2, false, false},
            {"   ", "Empty", "Empty", 6, 3, false, false},
            {"   ", "Empty", "Empty", 6, 4, false, false},
            {"   ", "Empty", "Empty", 6, 5, false, false},
            {"   ", "Empty", "Empty", 6, 6, false, false},
            {"   ", "Empty", "Empty", 6, 7, false, false},
            {"   ", "Empty", "Empty", 6, 8, false, false},
        },
        {
            {"Pn1", "Pawn", "White", 7, 1, false, true},
            {"Pn2", "Pawn", "White", 7, 2, false, true},
            {"Pn3", "Pawn", "White", 7, 3, false, true},
            {"Pn4", "Pawn", "White", 7, 4, false, true},
            {"Pn5", "Pawn", "White", 7, 5, false, true},
            {"Pn6", "Pawn", "White", 7, 6, false, true},
            {"Pn7", "Pawn", "White", 7, 7, false, true},
            {"Pn8", "Pawn", "White", 7, 8, false, true},
        },
        {
            {"Rk1", "Rook", "White", 8, 1, false, true},
            {"Kt1", "Knight", "White", 8, 2, false, true},
            {"Bp1", "Bishop", "White", 8, 3, false, true},
            {"Kg1", "King", "White", 8, 4, false, true},
            {"Qn1", "Queen", "White", 8, 5, false, true},
            {"Bp2", "Bishop", "White", 8, 6, false, true},
            {"Kt2", "Knight", "White", 8, 7, false, true},
            {"Rk2", "Rook", "White", 8, 8, false, true},
        }
    };
    
    struct pieces* pointerPiece = &board[1][3];
    struct pieces* pointerDestination = &board[4][0];
    
    printBoard(board);
    movePiece(pointerPiece, pointerDestination);
    checkCheckStraight(pointerPieceCheck, board)

    fflush(stdin);
    return 0;
}

void printBoard(struct pieces board[LINES][COLUMNS]){
    
    char borders[BORDERS][CHARACTERS] = {
    RESET " |", RESET "8|", RESET "7|", RESET "6|", RESET "5|", RESET "4|", RESET "3|", RESET "2|", RESET "1|",  RESET "|"
    };
    char line[100], index[100], primarySquare[CHARACTERS], secondarySquare[CHARACTERS];
    char* pieceColor;
    int counter;
    
    strcpy(line, RESET "  --------------------------------------------------------");
    strcpy(index, RESET "     a      b      c      d      e      f      g      h");
  
    printf("\n%s\n",line);
    for(int i=0;i<LINES;i++)
    {
        counter = 0;
        printf("%s",borders[0]);
        if(i%2==0)
        {
            strcpy(primarySquare, LIGHTBACKGROUND "  ");
            strcpy(secondarySquare, DARKBACKGROUND "  ");
        }
        else
        {
            strcpy(primarySquare, DARKBACKGROUND "  ");
            strcpy(secondarySquare, LIGHTBACKGROUND "  ");
        }
        for(counter=counter;counter<COLUMNS/2;counter++)
        {
            printf("%s     %s     ",primarySquare, secondarySquare);
        }
        printf("%s",borders[BORDERS-1]);
        printf("\n");
        printf("%s",borders[i+1]);
        for(int j=0;j<COLUMNS;j++)
        {
            if(strcmp(board[i][j].color, "Black") == 0)
            {
                pieceColor = BLACKPIECES;
            }
            else
            {
                pieceColor = WHITEPIECES;
            }
            if(j%2==0)
            {
                printf("%s%s%s%s",primarySquare, pieceColor, board[i][j].representation, primarySquare);
            }
            else
            {
                printf("%s%s%s%s",secondarySquare, pieceColor, board[i][j].representation, secondarySquare);
            }
        }
        counter = 0;
        printf("%s",borders[BORDERS-1]);
        printf("\n");
        printf("%s",borders[0]);
        for(counter=counter;counter<COLUMNS/2;counter++)
        {
            printf("%s     %s     ",primarySquare, secondarySquare);
        }
        printf("%s\n",borders[BORDERS-1]);
    }
    printf("%s", line);
    printf("\n%s\n\n",index);
    
    counter=0;
    
    return;
}

void movePiece(struct pieces* piece, struct pieces* destination)
{
    strcpy(destination->representation, piece->representation);
    strcpy(piece->representation, "   ");
    strcpy(destination->type, piece->type);
    strcpy(piece->type, "Empty");
    strcpy(destination->color, piece->color);
    strcpy(piece->color, "Empty");
    
    (piece)->hasMoved = true;
}

void checkCheckStraight(struct pieces* piece, struct pieces board[LINES][COLUMNS])
{
    for(int i=1;i<(LINES-(piece->line-1));i++)
    {
        if(strcmp((piece + COLUMNS*i)->type, "Rook")==0 || strcmp((piece + COLUMNS*i)->type, "Queen")==0 && strcmp((piece + COLUMNS*i)->color, piece->color)!=0)
        {
            printf("Check");
            return;
        }
        else
        {
            if(strcmp((piece + COLUMNS*i)->color, piece->color)==0)
            {
                printf("No check");
                return;
            }
            if(strcmp((piece + COLUMNS*i)->color, "Empty")!=0 && strcmp((piece + COLUMNS*i)->type, "Rook")!=0 && strcmp((piece + COLUMNS*i)->type, "Queen")!=0)
            {
                printf("No check");
                return;
            }
        }
    }
    for(int i=1;i<(0+piece->line);i++)
    {
        if(strcmp((piece - COLUMNS*i)->type, "Rook")==0 || strcmp((piece - COLUMNS*i)->type, "Queen")==0 && strcmp((piece - COLUMNS*i)->color, piece->color)!=0)
        {
            printf("Check");
            return;
        }
        else
        {
            if(strcmp((piece - COLUMNS*i)->color, piece->color)==0)
            {
                printf("No check");
                return;
            }
            if(strcmp((piece - COLUMNS*i)->color, "Empty")!=0 && strcmp((piece - COLUMNS*i)->type, "Rook")!=0 && strcmp((piece - COLUMNS*i)->type, "Queen")!=0)
            {
                printf("No check");
                return;
            }
        }
    }
    for(int i=1;i<(COLUMNS-(piece->column-1));i++)
    {
        if(strcmp((piece + i)->type, "Rook")==0 || strcmp((piece + i)->type, "Queen")==0 && strcmp((piece + i)->color, piece->color)!=0)
        {
            printf("Check");
            return;
        }
        else
        {
            if(strcmp((piece + i)->color, piece->color)==0)
            {
                printf("No check");
                return;
            }
            if(strcmp((piece + i)->color, "Empty")!=0 && strcmp((piece + i)->type, "Rook")!=0 && strcmp((piece + i)->type, "Queen")!=0)
            {
                printf("No check");
                return;
            }
        }
    }
    for(int i=1;i<(0+piece->column);i++)
    {
        if(strcmp((piece - i)->type, "Rook")==0 || strcmp((piece - i)->type, "Queen")==0 && strcmp((piece - i)->color, piece->color)!=0)
        {
            printf("Check");
            return;
        }
        else
        {
            if(strcmp((piece - i)->color, piece->color)==0)
            {
                printf("No check");
                return;
            }
            if(strcmp((piece - i)->color, "Empty")!=0 && strcmp((piece - i)->type, "Rook")!=0 && strcmp((piece - i)->type, "Queen")!=0)
            {
                printf("No check");
                return;
            }
        }
    }
}
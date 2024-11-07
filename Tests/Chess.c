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
#define EMPTY 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6
#define BLACK 1
#define WHITE 2

struct pieces {
    char representation[CHARACTERS];
    int type;
    int color;
    int line;
    int column;
    bool hasMoved;
    bool canMove;
    bool justMoved;
};

void printBoard(struct pieces board[LINES][COLUMNS]);
void movePiece(struct pieces* piece, struct pieces* destination);
void checkCheckStraight(struct pieces* piece);
void checkCheckDiagonal(struct pieces* piece);

int main()
{
    struct pieces board[LINES][COLUMNS] = {
        {
            {"Rk1", ROOK, BLACK, 1, 1, false, true},
            {"Kt1", KNIGHT, BLACK, 1, 2, false, true},
            {"Bp1", BISHOP, BLACK, 1, 3, false, true},
            {"Kg1", KING, BLACK, 1, 4, false, true},
            {"Qn1", QUEEN, BLACK, 1, 5, false, true},
            {"Bp2", BISHOP, BLACK, 1, 6, false, true},
            {"Kt2", KNIGHT, BLACK, 1, 7, false, true},
            {"Rk2", ROOK, BLACK, 1, 8, false, true},
        },
        {
            {"Pn1", PAWN, BLACK, 2, 1, false, true},
            {"Pn2", PAWN, BLACK, 2, 2, false, true},
            {"Pn3", PAWN, BLACK, 2, 3, false, true},
            {"Pn4", PAWN, BLACK, 2, 4, false, true},
            {"Pn5", PAWN, BLACK, 2, 5, false, true},
            {"Pn6", PAWN, BLACK, 2, 6, false, true},
            {"Pn7", PAWN, BLACK, 2, 7, false, true},
            {"Pn8", PAWN, BLACK, 2, 8, false, true},
        },
        {
            {"   ", EMPTY, EMPTY, 3, 1, false, false},
            {"   ", EMPTY, EMPTY, 3, 2, false, false},
            {"   ", EMPTY, EMPTY, 3, 3, false, false},
            {"   ", EMPTY, EMPTY, 3, 4, false, false},
            {"   ", EMPTY, EMPTY, 3, 5, false, false},
            {"   ", EMPTY, EMPTY, 3, 6, false, false},
            {"   ", EMPTY, EMPTY, 3, 7, false, false},
            {"   ", EMPTY, EMPTY, 3, 8, false, false},
        },
        {
            {"   ", EMPTY, EMPTY, 4, 1, false, false},
            {"   ", EMPTY, EMPTY, 4, 2, false, false},
            {"   ", EMPTY, EMPTY, 4, 3, false, false},
            {"   ", EMPTY, EMPTY, 4, 4, false, false},
            {"   ", EMPTY, EMPTY, 4, 5, false, false},
            {"   ", EMPTY, EMPTY, 4, 6, false, false},
            {"   ", EMPTY, EMPTY, 4, 7, false, false},
            {"   ", EMPTY, EMPTY, 4, 8, false, false},
        },
        {
            {"   ", EMPTY, EMPTY, 5, 1, false, false},
            {"   ", EMPTY, EMPTY, 5, 2, false, false},
            {"   ", EMPTY, EMPTY, 5, 3, false, false},
            {"   ", EMPTY, EMPTY, 5, 4, false, false},
            {"   ", EMPTY, EMPTY, 5, 5, false, false},
            {"   ", EMPTY, EMPTY, 5, 6, false, false},
            {"   ", EMPTY, EMPTY, 5, 7, false, false},
            {"   ", EMPTY, EMPTY, 5, 8, false, false},
        },
        {
            {"   ", EMPTY, EMPTY, 6, 1, false, false},
            {"   ", EMPTY, EMPTY, 6, 2, false, false},
            {"   ", EMPTY, EMPTY, 6, 3, false, false},
            {"   ", EMPTY, EMPTY, 6, 4, false, false},
            {"   ", EMPTY, EMPTY, 6, 5, false, false},
            {"   ", EMPTY, EMPTY, 6, 6, false, false},
            {"   ", EMPTY, EMPTY, 6, 7, false, false},
            {"   ", EMPTY, EMPTY, 6, 8, false, false},
        },
        {
            {"Pn1", PAWN, WHITE, 7, 1, false, true},
            {"Pn2", PAWN, WHITE, 7, 2, false, true},
            {"Pn3", PAWN, WHITE, 7, 3, false, true},
            {"Pn4", PAWN, WHITE, 7, 4, false, true},
            {"Pn5", PAWN, WHITE, 7, 5, false, true},
            {"Pn6", PAWN, WHITE, 7, 6, false, true},
            {"Pn7", PAWN, WHITE, 7, 7, false, true},
            {"Pn8", PAWN, WHITE, 7, 8, false, true},
        },
        {
            {"Rk1", ROOK, WHITE, 8, 1, false, true},
            {"Kt1", KNIGHT, WHITE, 8, 2, false, true},
            {"Bp1", BISHOP, WHITE, 8, 3, false, true},
            {"Kg1", KING, WHITE, 8, 4, false, true},
            {"Qn1", QUEEN, WHITE, 8, 5, false, true},
            {"Bp2", BISHOP, WHITE, 8, 6, false, true},
            {"Kt2", KNIGHT, WHITE, 8, 7, false, true},
            {"Rk2", ROOK, WHITE, 8, 8, false, true},
        }
    };
    
    struct pieces* pointerPiece = &board[3][6];
    struct pieces* pointerDestination;
    
    printBoard(board);
    checkCheckDiagonal(pointerPiece);

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
            if(board[i][j].color == BLACK)
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
    destination->type = piece->type;
    piece->type = EMPTY;
    destination->color = piece->color;
    piece->color = EMPTY;
    
    piece->hasMoved = false;
    piece->justMoved = false;
    destination->hasMoved = true;
    destination->justMoved = true;
}

void checkCheckStraight(struct pieces* piece)
{
    for(int i=1;i<(LINES-(piece->line-1));i++)
    {
        if((piece + COLUMNS*i)->type == ROOK || (piece + COLUMNS*i)->type == QUEEN && (piece + COLUMNS*i)->color != piece->color)
        {
            printf("Check");
            return;
        }
        else
        {
            if((piece + COLUMNS*i)->color == piece->color)
            {
                printf("No check");
                break;
            }
            if((piece + COLUMNS*i)->color != EMPTY && (piece + COLUMNS*i)->type != ROOK && (piece + COLUMNS*i)->type != QUEEN)
            {
                printf("No check");
                break;
            }
        }
    }
    for(int i=1;i<(0+piece->line);i++)
    {
        if((piece - COLUMNS*i)->type == ROOK || (piece - COLUMNS*i)->type == QUEEN && (piece - COLUMNS*i)->color != piece->color)
        {
            printf("Check");
            return;
        }
        else
        {
            if((piece - COLUMNS*i)->color == piece->color)
            {
                printf("No check");
                break;
            }
            if((piece - COLUMNS*i)->color != EMPTY && (piece - COLUMNS*i)->type != ROOK && (piece - COLUMNS*i)->type != QUEEN)
            {
                printf("No check");
                break;
            }
        }
    }
    for(int i=1;i<(COLUMNS-(piece->column-1));i++)
    {
        if((piece + i)->type == ROOK || (piece + i)->type == QUEEN && (piece + i)->color != piece->color)
        {
            printf("Check");
            return;
        }
        else
        {
            if((piece + i)->color == piece->color)
            {
                printf("No check");
                break;
            }
            if((piece + i)->color != EMPTY && (piece + i)->type != ROOK && (piece + i)->type != QUEEN)
            {
                printf("No check");
                break;
            }
        }
    }
    for(int i=1;i<(0+piece->column);i++)
    {
        if((piece - i)->type == ROOK || (piece - i)->type == QUEEN && (piece - i)->color != piece->color)
        {
            printf("Check");
            return;
        }
        else
        {
            if((piece - i)->color == piece->color)
            {
                printf("No check");
                break;
            }
            if((piece - i)->color != EMPTY && (piece - i)->type != ROOK && (piece - i)->type != QUEEN)
            {
                printf("No check");
                break;
            }
        }
    }
    return;
}

void checkCheckDiagonal(struct pieces* piece)
{
    int limit;
    
    if(piece->column <= piece->line)
    {
        limit = piece->line-1;
    }
    else
    {
        limit = piece->column-1;
    }
    
    for(int i=1;i<(LINES-limit);i++)
    {
        if((piece + ((COLUMNS*i)+i))->type == BISHOP || (piece + ((COLUMNS*i)+i))->type == QUEEN && (piece + ((COLUMNS*i)+i))->color != piece->color)
        {
            printf("Check");
            return;
        }
        else
        {
            if((piece + ((COLUMNS*i)+i))->color == piece->color)
            {
                printf("No check");
                break;
            }
            if((piece + ((COLUMNS*i)+i))->color != EMPTY && (piece + ((COLUMNS*i)+i))->type != BISHOP && (piece + ((COLUMNS*i)+i))->type != QUEEN)
            {
                printf("No check");
                break;
            }
        }
    }
    
    if(piece->line + piece->column >= COLUMNS+1)
    {
        limit = piece->line-1;
    }
    else
    {
        limit = COLUMNS - piece->column;
    }
    
    for(int i=1;i<(LINES-limit);i++)
    {
        if((piece + ((COLUMNS*i)-i))->type == BISHOP || (piece + ((COLUMNS*i)-i))->type == QUEEN && (piece + ((COLUMNS*i)-i))->color != piece->color)
        {
            printf("Check");
            return;
        }
        else
        {
            if((piece + ((COLUMNS*i)-i))->color == piece->color)
            {
                printf("No check");
                break;
            }
            if((piece + ((COLUMNS*i)-i))->color != EMPTY && (piece + ((COLUMNS*i)-i))->type != BISHOP && (piece + ((COLUMNS*i)-i))->type != QUEEN)
            {
                printf("No check");
                break;
            }
        }
    }
    
    if(piece->column >= piece->line)
    {
        limit = piece->line-1;
    }
    else
    {
        limit = piece->column-1;
    }
    
    for(int i=1;i<(1+limit);i++)
    {
        if((piece - ((COLUMNS*i)-i))->type == BISHOP || (piece - ((COLUMNS*i)-i))->type == QUEEN && (piece - ((COLUMNS*i)-i))->color != piece->color)
        {
            printf("Check");
            return;
        }
        else
        {
            if((piece - ((COLUMNS*i)-i))->color == piece->color)
            {
                printf("No check");
                break;
            }
            if((piece - ((COLUMNS*i)-i))->color != EMPTY && (piece - ((COLUMNS*i)-i))->type != BISHOP && (piece - ((COLUMNS*i)-i))->type != QUEEN)
            {
                printf("No check");
                break;
            }
        }
    }
    
    if(piece->line + piece->column >= COLUMNS+1)
    {
        limit = COLUMNS - piece->column;
    }
    else
    {
        limit = piece->line-1;
    }
    
    for(int i=1;i<(1+limit);i++)
    {
        if((piece - ((COLUMNS*i)+i))->type == BISHOP || (piece - ((COLUMNS*i)+i))->type == QUEEN && (piece - ((COLUMNS*i)+i))->color != piece->color)
        {
            printf("Check");
            return;
        }
        else
        {
            if((piece - ((COLUMNS*i)+i))->color == piece->color)
            {
                printf("No check");
                break;
            }
            if((piece - ((COLUMNS*i)+i))->color != EMPTY && (piece - ((COLUMNS*i)+i))->type != BISHOP && (piece - ((COLUMNS*i)+i))->type != QUEEN)
            {
                printf("No check");
                break;
            }
        }
    }
}
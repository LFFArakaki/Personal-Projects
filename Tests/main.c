#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

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

int ch;
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
void movePiece(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS]);
void checkCheckStraight(struct pieces* piece);
void checkCheckDiagonal(struct pieces* piece);
void checkCheckKnight(struct pieces* piece);
void checkCheckPawn(struct pieces* piece);
void checkCheck(struct pieces board[LINES][COLUMNS], int* turnIndex);
void turn(struct pieces board[LINES][COLUMNS], int* turnCounter);

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
    
    int turnCounter, loop;
    turnCounter = 0;
    int* turnCounterPointer = &turnCounter;
    loop = 0;
    
    printBoard(board);
    
    while(loop == 0)
    {
        turn(board, turnCounterPointer);
    }
    
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
        if(i%2 == 0)
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
            if(j%2 == 0)
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

void movePiece(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS])
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
    
    printBoard(board);
}

void checkCheckStraight(struct pieces* piece)
{
    for(int i=1;i<(LINES-(piece->line-1));i++)
    {
        if(((piece + COLUMNS*i)->type == ROOK || (piece + COLUMNS*i)->type == QUEEN) && (piece + COLUMNS*i)->color != piece->color)
        {
            printf("Rook/Queen check\n");
            return;
        }
        else
        {
            if((piece + COLUMNS*i)->color == piece->color)
            {
                break;
            }
            if((piece + COLUMNS*i)->color != EMPTY && (piece + COLUMNS*i)->type != ROOK && (piece + COLUMNS*i)->type != QUEEN)
            {
                break;
            }
        }
    }
    for(int i=1;i<(0+piece->line);i++)
    {
        if(((piece - COLUMNS*i)->type == ROOK || (piece - COLUMNS*i)->type == QUEEN) && (piece - COLUMNS*i)->color != piece->color)
        {
            printf("Rook/Queen check\n");
            return;
        }
        else
        {
            if((piece - COLUMNS*i)->color == piece->color)
            {
                break;
            }
            if((piece - COLUMNS*i)->color != EMPTY && (piece - COLUMNS*i)->type != ROOK && (piece - COLUMNS*i)->type != QUEEN)
            {
                break;
            }
        }
    }
    for(int i=1;i<(COLUMNS-(piece->column-1));i++)
    {
        if(((piece + i)->type == ROOK || (piece + i)->type == QUEEN) && (piece + i)->color != piece->color)
        {
            printf("Rook/Queen check\n");
            return;
        }
        else
        {
            if((piece + i)->color == piece->color)
            {
                break;
            }
            if((piece + i)->color != EMPTY && (piece + i)->type != ROOK && (piece + i)->type != QUEEN)
            {
                break;
            }
        }
    }
    for(int i=1;i<(0+piece->column);i++)
    {
        if(((piece - i)->type == ROOK || (piece - i)->type == QUEEN) && (piece - i)->color != piece->color)
        {
            printf("Rook/Queen check\n");
            return;
        }
        else
        {
            if((piece - i)->color == piece->color)
            {
                break;
            }
            if((piece - i)->color != EMPTY && (piece - i)->type != ROOK && (piece - i)->type != QUEEN)
            {
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
        if(((piece + ((COLUMNS*i)+i))->type == BISHOP || (piece + ((COLUMNS*i)+i))->type == QUEEN) && (piece + ((COLUMNS*i)+i))->color != piece->color)
        {
            printf("Bishop/Queen check\n");
            return;
        }
        else
        {
            if((piece + ((COLUMNS*i)+i))->color == piece->color)
            {
                break;
            }
            if((piece + ((COLUMNS*i)+i))->color != EMPTY && (piece + ((COLUMNS*i)+i))->type != BISHOP && (piece + ((COLUMNS*i)+i))->type != QUEEN)
            {
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
        if(((piece + ((COLUMNS*i)-i))->type == BISHOP || (piece + ((COLUMNS*i)-i))->type == QUEEN) && (piece + ((COLUMNS*i)-i))->color != piece->color)
        {
            printf("Bishop/Queen check\n");
            return;
        }
        else
        {
            if((piece + ((COLUMNS*i)-i))->color == piece->color)
            {
                break;
            }
            if((piece + ((COLUMNS*i)-i))->color != EMPTY && (piece + ((COLUMNS*i)-i))->type != BISHOP && (piece + ((COLUMNS*i)-i))->type != QUEEN)
            {
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
        if(((piece - ((COLUMNS*i)+i))->type == BISHOP || (piece - ((COLUMNS*i)+i))->type == QUEEN) && (piece - ((COLUMNS*i)+i))->color != piece->color)
        {
            printf("Bishop/Queen check\n");
            return;
        }
        else
        {
            if((piece - ((COLUMNS*i)+i))->color == piece->color)
            {
                break;
            }
            if((piece - ((COLUMNS*i)+i))->color != EMPTY && (piece - ((COLUMNS*i)+i))->type != BISHOP && (piece - ((COLUMNS*i)+i))->type != QUEEN)
            {
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
        if(((piece - ((COLUMNS*i)-i))->type == BISHOP || (piece - ((COLUMNS*i)-i))->type == QUEEN) && (piece - ((COLUMNS*i)-i))->color != piece->color)
        {
            printf("Bishop/Queen check\n");
            return;
        }
        else
        {
            if((piece - ((COLUMNS*i)-i))->color == piece->color)
            {
                break;
            }
            if((piece - ((COLUMNS*i)-i))->color != EMPTY && (piece - ((COLUMNS*i)-i))->type != BISHOP && (piece - ((COLUMNS*i)-i))->type != QUEEN)
            {
                break;
            }
        }
    }
    
    return;
}

void checkCheckKnight(struct pieces* piece)
{
    if((piece - COLUMNS - 2)->type == KNIGHT && (piece - COLUMNS - 2)->color != piece->color)
    {
        printf("Knight check\n");
        return;
    }
    
    if((piece - COLUMNS + 2)->type == KNIGHT && (piece - COLUMNS + 2)->color != piece->color)
    {
        printf("Knight check\n");
        return;
    }
    
    if((piece + COLUMNS - 2)->type == KNIGHT && (piece + COLUMNS - 2)->color != piece->color)
    {
        printf("Knight check\n");
        return;
    }
    
    if((piece + COLUMNS + 2)->type == KNIGHT && (piece + COLUMNS + 2)->color != piece->color)
    {
        printf("Knight check\n");
        return;
    }
    
    if((piece - 2*COLUMNS - 1)->type == KNIGHT && (piece - 2*COLUMNS - 1)->color != piece->color)
    {
        printf("Knight check\n");
        return;
    }
    
    if((piece - 2*COLUMNS + 1)->type == KNIGHT && (piece - 2*COLUMNS + 1)->color != piece->color)
    {
        printf("Knight check\n");
        return;
    }
    
    if((piece + 2*COLUMNS - 1)->type == KNIGHT && (piece + 2*COLUMNS - 1)->color != piece->color)
    {
        printf("Knight check\n");
        return;
    }
    
    if((piece + 2*COLUMNS + 1)->type == KNIGHT && (piece + 2*COLUMNS + 1)->color != piece->color)
    {
        printf("Knight check\n");
        return;
    }
    
    return;
}

void checkCheckPawn(struct pieces* piece)
{
    if(piece->color == BLACK)
    {
        if((piece + COLUMNS + 1)->type == PAWN && (piece + COLUMNS + 1)->color != piece->color)
        {
            printf("Pawn check\n");
            return;
        }
        if((piece + COLUMNS - 1)->type == PAWN && (piece + COLUMNS - 1)->color != piece->color)
        {
            printf("Pawn check\n");
            return;
        }
    }
    else
    {
        if((piece - COLUMNS + 1)->type == PAWN && (piece - COLUMNS + 1)->color != piece->color)
        {
            printf("Pawn check\n");
            return;
        }
        if((piece - COLUMNS - 1)->type == PAWN && (piece - COLUMNS - 1)->color != piece->color)
        {
            printf("Pawn check\n");
            return;
        }
    }
}

void checkCheck(struct pieces board[LINES][COLUMNS], int* turnIndex)
{
    bool pieceFound;
    struct pieces* piecePointer;
    char kingRepresentation[CHARACTERS];
    
    strcpy(kingRepresentation, "Kg1");
    
    for(int i=0;i<LINES;i++)
    {
        for(int j=0;j<COLUMNS;j++)
        {
            if(strcmp(kingRepresentation, board[i][j].representation) == 0 && *turnIndex != board[i][j].color)
            {
                piecePointer = &board[i][j];
                pieceFound = true;
                break;
            }
            else
            {
                pieceFound = false;
            }
        }
        if(pieceFound)
        {
            break;
        }
    }
    
    checkCheckStraight(piecePointer);
    checkCheckDiagonal(piecePointer);
    checkCheckKnight(piecePointer);
    checkCheckPawn(piecePointer);
    
    return;
}

void turn(struct pieces board[LINES][COLUMNS], int* turnCounter)
{
    bool pieceFound;
    int turnIndex, destinationLine, destinationColumn;
    char movedPiece[CHARACTERS], destinationNotation[CHARACTERS];
    int* turnIndexPointer = &turnIndex;
    struct pieces* piecePointer;
    struct pieces* destinationPointer;
    
    if(*turnCounter%2 == 0)
    {
        printf("White's turn to move!\n");
        turnIndex = WHITE;
    }
    else
    {
        printf("Black's turn to move!\n");
        turnIndex = BLACK;
    }
    
    printf("\nWhat piece would you like to move?\n");
    printf("Type it's representation\n");
    printf("(e.g: 'Qn1' for the queen)\n");
    scanf("%s",movedPiece);
    
    for(int i=0;i<LINES;i++)
    {
        for(int j=0;j<COLUMNS;j++)
        {
            if(strcmp(movedPiece, board[i][j].representation) == 0 && turnIndex == board[i][j].color)
            {
                printf("Piece found!\n");
                piecePointer = &board[i][j];
                pieceFound = true;
                break;
            }
            else
            {
                pieceFound = false;
            }
        }
        if(pieceFound)
        {
            break;
        }
    }
    
    if(!pieceFound)
    {
        printf("Piece not found!\n");
        return;
    }
    
    printf("\nWhere would you like to move it to?\n");
    printf("Type it's notation\n");
    printf("(e.g: 'a1' for the bottom-left corner square)\n");
    scanf("%s", destinationNotation);
    
    switch(destinationNotation[0])
    {
        case 'a':
        destinationColumn = 0;
        break;
        case 'b':
        destinationColumn = 1;
        break;
        case 'c':
        destinationColumn = 2;
        break;
        case 'd':
        destinationColumn = 3;
        break;
        case 'e':
        destinationColumn = 4;
        break;
        case 'f':
        destinationColumn = 5;
        break;
        case 'g':
        destinationColumn = 6;
        break;
        case 'h':
        destinationColumn = 7;
        break;
        default:
        printf("Informed column doesn't exist!\n");
        printf("(Columns are: a-h)");
        return;
    }
    
    switch(destinationNotation[1])
    {
        case '8':
        destinationLine = 0;
        break;
        case '7':
        destinationLine = 1;
        break;
        case '6':
        destinationLine = 2;
        break;
        case '5':
        destinationLine = 3;
        break;
        case '4':
        destinationLine = 4;
        break;
        case '3':
        destinationLine = 5;
        break;
        case '2':
        destinationLine = 6;
        break;
        case '1':
        destinationLine = 7;
        break;
        default:
        printf("Informed line doesn't exist!\n");
        printf("(Lines are: 1-8)");
        return;
    }
    
    destinationPointer = &board[destinationLine][destinationColumn];
    *turnCounter = *turnCounter+1;
    
    movePiece(piecePointer, destinationPointer, board);
    checkCheck(board, turnIndexPointer);
    
    return;
}
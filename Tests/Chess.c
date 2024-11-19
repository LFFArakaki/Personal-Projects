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
	bool checking;
};

void printBoard(struct pieces board[LINES][COLUMNS]);
void movePiece(struct pieces* piece, struct pieces* destination);
int checkCheck(struct pieces* piece);
int checkCheckStraight(struct pieces* piece);
int checkCheckDiagonal(struct pieces* piece);
int checkCheckKnight(struct pieces* piece);
int checkCheckPawn(struct pieces* piece);
int checkCheckType(struct pieces* piece);
void singleCheckProtocol(struct pieces board[LINES][COLUMNS], int* turnIndex, struct pieces* piece);
void multipleCheckProtocol(struct pieces board[LINES][COLUMNS], int* turnIndex);
void turn(struct pieces board[LINES][COLUMNS], int* turnCounter);
bool checkPossible(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS]);
bool checkPossiblePawn(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS]);
bool checkPossibleKnight(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS]);
bool checkPossibleBishop(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS]);
bool checkPossibleRook(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS]);
bool checkPossibleQueen(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS]);
bool checkPossibleKing(struct pieces* piece, struct pieces* destination);
bool checkKingCanMove(struct pieces board[LINES][COLUMNS], struct pieces* piece);
void enPassant(struct pieces* piece, struct pieces* destination);
void piecesCantMove(struct pieces board[LINES][COLUMNS], int* turnIndex);
void clearTemporary(struct pieces board[LINES][COLUMNS]);
bool checkCaptureProtocol(struct pieces board[LINES][COLUMNS]);
bool checkBlockDiagonalProtocol(struct pieces board[LINES][COLUMNS]);
bool checkBlockStraightProtocol(struct pieces board[LINES][COLUMNS]);
void bringBackPiece(struct pieces* temporaryPiece, struct pieces* piece);
bool checkPossibleCheck(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS]);
void promotion(struct pieces* piece);

int main()
{
	struct pieces board[LINES][COLUMNS] = {
		{
			{"Rk1", ROOK, BLACK, 1, 1, false, true, false, false},
			{"Kt1", KNIGHT, BLACK, 1, 2, false, true, false, false},
			{"Bp1", BISHOP, BLACK, 1, 3, false, true, false, false},
			{"Qn1", QUEEN, BLACK, 1, 4, false, true, false, false},
			{"Kg1", KING, BLACK, 1, 5, false, true, false, false},
			{"Bp2", BISHOP, BLACK, 1, 6, false, true, false, false},
			{"Kt2", KNIGHT, BLACK, 1, 7, false, true, false, false},
			{"Rk2", ROOK, BLACK, 1, 8, false, true, false, false},
		},
		{
			{"Pn1", PAWN, BLACK, 2, 1, false, true, false, false},
			{"Pn2", PAWN, BLACK, 2, 2, false, true, false, false},
			{"Pn3", PAWN, BLACK, 2, 3, false, true, false, false},
			{"Pn4", PAWN, BLACK, 2, 4, false, true, false, false},
			{"Pn5", PAWN, BLACK, 2, 5, false, true, false, false},
			{"Pn6", PAWN, BLACK, 2, 6, false, true, false, false},
			{"Pn7", PAWN, BLACK, 2, 7, false, true, false, false},
			{"Pn8", PAWN, BLACK, 2, 8, false, true, false, false},
		},
		{
			{"   ", EMPTY, EMPTY, 3, 1, false, false, false, false},
			{"   ", EMPTY, EMPTY, 3, 2, false, false, false, false},
			{"   ", EMPTY, EMPTY, 3, 3, false, false, false, false},
			{"   ", EMPTY, EMPTY, 3, 4, false, false, false, false},
			{"   ", EMPTY, EMPTY, 3, 5, false, false, false, false},
			{"   ", EMPTY, EMPTY, 3, 6, false, false, false, false},
			{"   ", EMPTY, EMPTY, 3, 7, false, false, false, false},
			{"   ", EMPTY, EMPTY, 3, 8, false, false, false, false},
		},
		{
			{"   ", EMPTY, EMPTY, 4, 1, false, false, false, false},
			{"   ", EMPTY, EMPTY, 4, 2, false, false, false, false},
			{"   ", EMPTY, EMPTY, 4, 3, false, false, false, false},
			{"   ", EMPTY, EMPTY, 4, 4, false, false, false, false},
			{"   ", EMPTY, EMPTY, 4, 5, false, false, false, false},
			{"   ", EMPTY, EMPTY, 4, 6, false, false, false, false},
			{"   ", EMPTY, EMPTY, 4, 7, false, false, false, false},
			{"   ", EMPTY, EMPTY, 4, 8, false, false, false, false},
		},
		{
			{"   ", EMPTY, EMPTY, 5, 1, false, false, false, false},
			{"   ", EMPTY, EMPTY, 5, 2, false, false, false, false},
			{"   ", EMPTY, EMPTY, 5, 3, false, false, false, false},
			{"   ", EMPTY, EMPTY, 5, 4, false, false, false, false},
			{"   ", EMPTY, EMPTY, 5, 5, false, false, false, false},
			{"   ", EMPTY, EMPTY, 5, 6, false, false, false, false},
			{"   ", EMPTY, EMPTY, 5, 7, false, false, false, false},
			{"   ", EMPTY, EMPTY, 5, 8, false, false, false, false},
		},
		{
			{"   ", EMPTY, EMPTY, 6, 1, false, false, false, false},
			{"   ", EMPTY, EMPTY, 6, 2, false, false, false, false},
			{"   ", EMPTY, EMPTY, 6, 3, false, false, false, false},
			{"   ", EMPTY, EMPTY, 6, 4, false, false, false, false},
			{"   ", EMPTY, EMPTY, 6, 5, false, false, false, false},
			{"   ", EMPTY, EMPTY, 6, 6, false, false, false, false},
			{"   ", EMPTY, EMPTY, 6, 7, false, false, false, false},
			{"   ", EMPTY, EMPTY, 6, 8, false, false, false, false},
		},
		{
			{"Pn1", PAWN, WHITE, 7, 1, false, true, false, false},
			{"Pn2", PAWN, WHITE, 7, 2, false, true, false, false},
			{"Pn3", PAWN, WHITE, 7, 3, false, true, false, false},
			{"Pn4", PAWN, WHITE, 7, 4, false, true, false, false},
			{"Pn5", PAWN, WHITE, 7, 5, false, true, false, false},
			{"Pn6", PAWN, WHITE, 7, 6, false, true, false, false},
			{"Pn7", PAWN, WHITE, 7, 7, false, true, false, false},
			{"Pn8", PAWN, WHITE, 7, 8, false, true, false, false},
		},
		{
			{"Rk1", ROOK, WHITE, 8, 1, false, true, false, false},
			{"Kt1", KNIGHT, WHITE, 8, 2, false, true, false, false},
			{"Bp1", BISHOP, WHITE, 8, 3, false, true, false, false},
			{"Qn1", QUEEN, WHITE, 8, 4, false, true, false, false},
			{"Kg1", KING, WHITE, 8, 5, false, true, false, false},
			{"Bp2", BISHOP, WHITE, 8, 6, false, true, false, false},
			{"Kt2", KNIGHT, WHITE, 8, 7, false, true, false, false},
			{"Rk2", ROOK, WHITE, 8, 8, false, true, false, false},
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

void printBoard(struct pieces board[LINES][COLUMNS]) {

	char borders[BORDERS][CHARACTERS] = {
		RESET " |", RESET "8|", RESET "7|", RESET "6|", RESET "5|", RESET "4|", RESET "3|", RESET "2|", RESET "1|",  RESET "|"
	};
	char line[100], index[100], primarySquare[CHARACTERS], secondarySquare[CHARACTERS];
	char* pieceColor;
	int counter;

	strcpy(line, RESET "  --------------------------------------------------------");
	strcpy(index, RESET "     a      b      c      d      e      f      g      h");

	printf("\n%s\n",line);
	for(int i=0; i<LINES; i++)
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
		for(counter=counter; counter<COLUMNS/2; counter++)
		{
			printf("%s     %s     ",primarySquare, secondarySquare);
		}
		printf("%s",borders[BORDERS-1]);
		printf("\n");
		printf("%s",borders[i+1]);
		for(int j=0; j<COLUMNS; j++)
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
		for(counter=counter; counter<COLUMNS/2; counter++)
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

	piece->canMove = false;
	piece->hasMoved = false;
	piece->justMoved = false;
	destination->canMove = true;
	destination->hasMoved = true;
	destination->justMoved = true;

	return;
}

int checkCheckStraight(struct pieces* piece)
{
	int checks = 0;

	for(int i=1; i<(LINES-(piece->line-1)); i++)
	{
		if(((piece + COLUMNS*i)->type == ROOK || (piece + COLUMNS*i)->type == QUEEN) && (piece + COLUMNS*i)->color != piece->color)
		{
			(piece + COLUMNS*i)->canMove = true;
			(piece + COLUMNS*i)->checking = true;
			checks++;
			break;
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
	for(int i=1; i<(0+piece->line); i++)
	{
		if(((piece - COLUMNS*i)->type == ROOK || (piece - COLUMNS*i)->type == QUEEN) && (piece - COLUMNS*i)->color != piece->color)
		{
			(piece - COLUMNS*i)->canMove = true;
			(piece - COLUMNS*i)->checking = true;
			checks++;
			break;
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
	for(int i=1; i<(COLUMNS-(piece->column-1)); i++)
	{
		if(((piece + i)->type == ROOK || (piece + i)->type == QUEEN) && (piece + i)->color != piece->color)
		{
			(piece + i)->canMove = true;
			(piece + i)->checking = true;
			checks++;
			break;
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
	for(int i=1; i<(0+piece->column); i++)
	{
		if(((piece - i)->type == ROOK || (piece - i)->type == QUEEN) && (piece - i)->color != piece->color)
		{
			(piece - i)->canMove = true;
			(piece - i)->checking = true;
			checks++;
			break;
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

	return checks;
}

int checkCheckDiagonal(struct pieces* piece)
{
	int limit, checks;
	checks = 0;

	if(piece->column <= piece->line)
	{
		limit = piece->line-1;
	}
	else
	{
		limit = piece->column-1;
	}

	for(int i=1; i<(LINES-limit); i++)
	{
		if(((piece + ((COLUMNS*i)+i))->type == BISHOP || (piece + ((COLUMNS*i)+i))->type == QUEEN) && (piece + ((COLUMNS*i)+i))->color != piece->color)
		{
			(piece + ((COLUMNS*i)+i))->canMove = true;
			(piece + ((COLUMNS*i)+i))->checking = true;
			checks++;
			break;
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

	for(int i=1; i<(LINES-limit); i++)
	{
		if(((piece + ((COLUMNS*i)-i))->type == BISHOP || (piece + ((COLUMNS*i)-i))->type == QUEEN) && (piece + ((COLUMNS*i)-i))->color != piece->color)
		{
			(piece + ((COLUMNS*i)-i))->canMove = true;
			(piece + ((COLUMNS*i)-i))->checking = true;
			checks++;
			break;
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

	for(int i=1; i<(1+limit); i++)
	{
		if(((piece - ((COLUMNS*i)+i))->type == BISHOP || (piece - ((COLUMNS*i)+i))->type == QUEEN) && (piece - ((COLUMNS*i)+i))->color != piece->color)
		{
			(piece - ((COLUMNS*i)+i))->canMove = true;
			(piece - ((COLUMNS*i)+i))->checking = true;
			checks++;
			break;
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

	for(int i=1; i<(1+limit); i++)
	{
		if(((piece - ((COLUMNS*i)-i))->type == BISHOP || (piece - ((COLUMNS*i)-i))->type == QUEEN) && (piece - ((COLUMNS*i)-i))->color != piece->color)
		{
			(piece - ((COLUMNS*i)-i))->canMove = true;
			(piece - ((COLUMNS*i)-i))->checking = true;
			checks++;
			break;
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

	return checks;
}

int checkCheckKnight(struct pieces* piece)
{
	int checks = 0;

	if((piece - COLUMNS - 2)->type == KNIGHT && (piece - COLUMNS - 2)->color != piece->color)
	{
		(piece - COLUMNS - 2)->canMove = true;
		(piece - COLUMNS - 2)->checking = true;
		checks++;
	}

	if((piece - COLUMNS + 2)->type == KNIGHT && (piece - COLUMNS + 2)->color != piece->color)
	{
		(piece - COLUMNS + 2)->canMove = true;
		(piece - COLUMNS + 2)->checking = true;
		checks++;
	}

	if((piece + COLUMNS - 2)->type == KNIGHT && (piece + COLUMNS - 2)->color != piece->color)
	{
		(piece + COLUMNS - 2)->canMove = true;
		(piece + COLUMNS - 2)->checking = true;
		checks++;
	}

	if((piece + COLUMNS + 2)->type == KNIGHT && (piece + COLUMNS + 2)->color != piece->color)
	{
		(piece + COLUMNS + 2)->canMove = true;
		(piece + COLUMNS + 2)->checking = true;
		checks++;
	}

	if((piece - 2*COLUMNS - 1)->type == KNIGHT && (piece - 2*COLUMNS - 1)->color != piece->color)
	{
		(piece - 2*COLUMNS - 1)->canMove = true;
		(piece - 2*COLUMNS - 1)->checking = true;
		checks++;
	}

	if((piece - 2*COLUMNS + 1)->type == KNIGHT && (piece - 2*COLUMNS + 1)->color != piece->color)
	{
		(piece - 2*COLUMNS + 1)->canMove = true;
		(piece - 2*COLUMNS + 1)->checking = true;
		checks++;
	}

	if((piece + 2*COLUMNS - 1)->type == KNIGHT && (piece + 2*COLUMNS - 1)->color != piece->color)
	{
		(piece + 2*COLUMNS - 1)->canMove = true;
		(piece + 2*COLUMNS - 1)->checking = true;
		checks++;
	}

	if((piece + 2*COLUMNS + 1)->type == KNIGHT && (piece + 2*COLUMNS + 1)->color != piece->color)
	{
		(piece + 2*COLUMNS + 1)->canMove = true;
		(piece + 2*COLUMNS + 1)->checking = true;
		checks++;
	}

	return checks;
}

int checkCheckPawn(struct pieces* piece)
{
	int checks = 0;

	if(piece->type == EMPTY)
	{
		if(piece->color == BLACK)
		{
			if((piece + COLUMNS)->type == PAWN && (piece + COLUMNS)->color != piece->color)
			{
				(piece + COLUMNS)->canMove = true;
				(piece + COLUMNS)->checking = true;
				checks++;
			}
			if((piece + COLUMNS)->type == EMPTY)
			{
				if((piece + (2*COLUMNS))->type == PAWN && (piece + (2*COLUMNS))->color != piece->color && !(piece + (2*COLUMNS))->hasMoved)
				{
					(piece + (2*COLUMNS))->canMove = true;
					(piece + (2*COLUMNS))->checking = true;
					checks++;
				}
			}
		}
		else
		{
			if((piece - COLUMNS)->type == PAWN && (piece - COLUMNS)->color != piece->color)
			{
				(piece - COLUMNS)->canMove = true;
				(piece - COLUMNS)->checking = true;
				checks++;
			}
			if((piece - COLUMNS)->type == EMPTY)
			{
				if((piece - (2*COLUMNS))->type == PAWN && (piece - (2*COLUMNS))->color != piece->color && !(piece - (2*COLUMNS))->hasMoved)
				{
					(piece - (2*COLUMNS))->canMove = true;
					(piece - (2*COLUMNS))->checking = true;
					checks++;
				}
			}
		}
	}
	else
	{
		if(piece->color == BLACK)
		{
			if((piece + COLUMNS + 1)->type == PAWN && (piece + COLUMNS + 1)->color != piece->color && piece->column != 8)
			{
				(piece + COLUMNS + 1)->canMove = true;
				(piece + COLUMNS + 1)->checking = true;
				checks++;
			}
			if((piece + COLUMNS - 1)->type == PAWN && (piece + COLUMNS - 1)->color != piece->color && piece->column != 1)
			{
				(piece + COLUMNS - 1)->canMove = true;
				(piece + COLUMNS - 1)->checking = true;
				checks++;
			}
		}
		else
		{
			if((piece - COLUMNS + 1)->type == PAWN && (piece - COLUMNS + 1)->color != piece->color && piece->column != 8)
			{
				(piece - COLUMNS + 1)->canMove = true;
				(piece - COLUMNS + 1)->checking = true;
				checks++;
			}
			if((piece - COLUMNS - 1)->type == PAWN && (piece - COLUMNS - 1)->color != piece->color && piece->column != 1)
			{
				(piece - COLUMNS - 1)->canMove = true;
				(piece - COLUMNS - 1)->checking = true;
				checks++;
			}
		}
	}

	return checks;
}

int checkCheck(struct pieces* piece)
{
	return checkCheckStraight(piece)+checkCheckDiagonal(piece)+checkCheckKnight(piece)+checkCheckPawn(piece);
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
	fgets(movedPiece, CHARACTERS, stdin);
	movedPiece[strcspn(movedPiece, "\n")] = '\0';

	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			if(strcmp(movedPiece, board[i][j].representation) == 0 && turnIndex == board[i][j].color)
			{
				if(!board[i][j].canMove)
				{
					printf("Immovable piece!\n");
					break;
				}
				else
				{
					piecePointer = &board[i][j];
					pieceFound = true;
					break;
				}
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
	fgets(destinationNotation, CHARACTERS, stdin);
	destinationNotation[strcspn(destinationNotation, "\n")] = '\0';

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

	if(!checkPossible(piecePointer, destinationPointer, board))
	{
		printf("Impossible move!\n");
		printBoard(board);
		return;
	}
	else
	{
		*turnCounter = *turnCounter+1;

		clearTemporary(board);
		movePiece(piecePointer, destinationPointer);
		printBoard(board);

		for(int i=0; i<LINES; i++)
		{
			for(int j=0; j<COLUMNS; j++)
			{
				if(board[i][j].type == KING && turnIndex != board[i][j].color)
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

		if(checkCheck(piecePointer) >= 1)
		{
			if(checkCheck(piecePointer) == 1)
			{
				singleCheckProtocol(board, turnIndexPointer, piecePointer);
			}
			else
			{
				multipleCheckProtocol(board, turnIndexPointer);
			}
		}
		return;
	}
}

bool checkPossible(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS])
{
	switch(piece->type)
	{
	case PAWN:
		return checkPossiblePawn(piece, destination, board);
		break;
	case KNIGHT:
		return checkPossibleKnight(piece, destination, board);
		break;
	case BISHOP:
		return checkPossibleBishop(piece, destination, board);
		break;
	case ROOK:
		return checkPossibleRook(piece, destination, board);
		break;
	case QUEEN:
		return checkPossibleQueen(piece, destination, board);
		break;
	case KING:
		return checkPossibleKing(piece, destination);
		break;
	}
	return false;
}

bool checkPossiblePawn(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS])
{
	if(!checkPossibleCheck(piece, destination, board))
	{
		return false;
	}
	if(!piece->canMove)
	{
		return false;
	}
	if(destination->column > piece->column+1 || destination->column < piece->column-1)
	{
		return false;
	}
	if(piece->color == BLACK)
	{
		if(destination->column != piece->column && destination->line == piece->line+1)
		{
			if(destination->color == piece->color)
			{
				return false;
			}
			else
			{
				if(destination->color == EMPTY)
				{
					if((destination - COLUMNS)->type == PAWN && (destination - COLUMNS)->justMoved)
					{
						enPassant(piece, destination);
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if(destination->line == 8)
					{
						//promotion(piece);
					}
					return true;
				}
			}
		}
		if(destination->line <= piece->line)
		{
			return false;
		}
		if(piece->hasMoved)
		{
			if(destination->line > piece->line+1)
			{
				return false;
			}
		}
		else
		{
			if(destination->line > piece->line+2)
			{
				return false;
			}
			if(destination->line == piece->line+2)
			{
				if(destination->column != piece->column)
				{
					return false;
				}
				if((destination - COLUMNS)->color != EMPTY)
				{
					return false;
				}
			}
		}
	}
	if(piece->color == WHITE)
	{
		if(destination->column != piece->column && destination->line == piece->line-1)
		{
			if(destination->color == piece->color)
			{
				return false;
			}
			else
			{
				if(destination->color == EMPTY)
				{
					if((destination + COLUMNS)->type == PAWN && (destination + COLUMNS)->justMoved)
					{
						enPassant(piece, destination);
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if(destination->line == 1)
					{
						//promotion(piece);
					}
					return true;
				}
			}
		}
		if(destination->line >= piece->line)
		{
			return false;
		}
		if(piece->hasMoved)
		{
			if(destination->line < piece->line-1)
			{
				return false;
			}
		}
		else
		{
			if(destination->line < piece->line-2)
			{
				return false;
			}
			if(destination->line == piece->line-2)
			{
				if(destination->column != piece->column)
				{
					return false;
				}
				if((destination + COLUMNS)->color != EMPTY)
				{
					return false;
				}
			}
		}
	}
	if(destination->color != EMPTY)
	{
		return false;
	}
	else
	{
		if(destination->line == 8 && piece->color == BLACK)
		{
			//promotion(piece);
		}
		if(destination->line == 1 && piece->color == WHITE)
		{
			//promotion(piece);
		}
		return true;
	}
}

bool checkPossibleKnight(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS])
{
	if(!checkPossibleCheck(piece, destination, board))
	{
		return false;
	}
	if(!piece->canMove)
	{
		return false;
	}
	if(destination->line > piece->line+2 || destination->line < piece->line-2)
	{
		return false;
	}
	if(destination->column > piece->column+2 || destination->column < piece->column-2)
	{
		return false;
	}
	if(destination->line == piece->line || destination->column == piece->column)
	{
		return false;
	}
	if(abs(destination->line - piece->line) == abs(destination->column - piece->column))
	{
		return false;
	}
	if(destination->type != EMPTY)
	{
		if(destination->color == piece->color)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}

bool checkPossibleBishop(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS])
{
	/*if(!checkPossibleCheck(piece, destination, board))
	{
		return false;
	}*/
	if(!piece->canMove)
	{
		return false;
	}
	if(abs(destination->line - piece->line) != abs(destination->column - piece->column))
	{
		return false;
	}
	if(destination->line == piece->line && destination->column == piece->column)
	{
		return false;
	}
	if(destination->color == piece->color)
	{
		return false;
	}
	if(destination->line > piece->line && destination->column > piece->column)
	{
		for(int i=1; i<(destination->line - piece->line)+1; i++)
		{
			if((piece + ((COLUMNS*i)+i))->line != destination->line)
			{
				if((piece + ((COLUMNS*i)+i))->color != EMPTY)
				{
					return false;
				}
			}
		}
		return true;
	}
	if(destination->line > piece->line && destination->column < piece->column)
	{
		for(int i=1; i<(destination->line - piece->line)+1; i++)
		{
			if((piece + ((COLUMNS*i)-i))->line != destination->line)
			{
				if((piece + ((COLUMNS*i)-i))->color != EMPTY)
				{
					return false;
				}
			}
		}
		return true;
	}
	if(destination->line < piece->line && destination->column < piece->column)
	{
		for(int i=1; i<(piece->line - destination->line)+1; i++)
		{
			if((piece - ((COLUMNS*i)+i))->line != destination->line)
			{
				if((piece - ((COLUMNS*i)+i))->color != EMPTY)
				{
					return false;
				}
			}
		}
		return true;
	}
	if(destination->line < piece->line && destination->column > piece->column)
	{
		for(int i=1; i<(piece->line - destination->line)+1; i++)
		{
			if((piece - ((COLUMNS*i)-i))->line != destination->line)
			{
				if((piece - ((COLUMNS*i)-i))->color != EMPTY)
				{
					return false;
				}
			}
		}
		return true;
	}
}

bool checkPossibleRook(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS])
{
	/*if(!checkPossibleCheck(piece, destination, board))
	{
		return false;
	}*/
	if(!piece->canMove)
	{
		return false;
	}
	if(destination->line == piece->line && destination->column == piece->column)
	{
		return false;
	}
	if(destination->color == piece->color)
	{
		return false;
	}
	if(destination->line != piece->line && destination->column != piece->column)
	{
		return false;
	}
	if(destination->line > piece->line)
	{
		for(int i=1; i<(destination->line - piece->line)+1; i++)
		{
			if((piece + (COLUMNS*i))->line != destination->line)
			{
				if((piece + (COLUMNS*i))->color != EMPTY)
				{
					return false;
				}
			}
		}
		return true;
	}
	if(destination->line < piece->line)
	{
		for(int i=1; i<(piece->line - destination->line)+1; i++)
		{
			if((piece - (COLUMNS*i))->line != destination->line)
			{
				if((piece - (COLUMNS*i))->color != EMPTY)
				{
					return false;
				}
			}
		}
		return true;
	}
	if(destination->column > piece->column)
	{
		for(int i=1; i<(destination->column - piece->column); i++)
		{
			if((piece + i)->column != destination->column)
			{
				if((piece + i)->color != EMPTY)
				{
					return false;
				}
			}
		}
		return true;
	}
	if(destination->column < piece->column)
	{
		for(int i=1; i<(piece->column - destination->column); i++)
		{
			if((piece - i)->column != destination->column)
			{
				if((piece - i)->color != EMPTY)
				{
					return false;
				}
			}
		}
		return true;
	}
}

bool checkPossibleQueen(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS])
{
	if(!checkPossibleBishop(piece, destination, board))
	{
		return checkPossibleRook(piece, destination, board);
	}
	else
	{
		return true;
	}
}

bool checkPossibleKing(struct pieces* piece, struct pieces* destination)
{
	int temporaryColor;

	if(!piece->canMove)
	{
		return false;
	}
	if(destination->line == piece->line && destination->column == piece->column)
	{
		return false;
	}
	if(destination->color == piece->color)
	{
		return false;
	}
	if(destination->line > piece->line+1 || destination->column > piece->column+1)
	{
		return false;
	}
	if(destination->line < piece->line-1 || destination->column < piece->column-1)
	{
		return false;
	}

	temporaryColor = destination->color;
	destination->color = piece->color;

	if(checkCheck(destination) > 0)
	{
		destination->color = temporaryColor;
		return false;
	}
	else
	{
		destination->color = temporaryColor;
		return true;
	}
}

bool checkKingCanMove(struct pieces board[LINES][COLUMNS], struct pieces* piece)
{
	int kingLine, kingColumn;
	struct pieces* destinationPointer;

	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			if(board[i][j].color == piece->color && board[i][j].type == KING)
			{
				kingLine = i;
				kingColumn = j;
				break;
			}
		}
	}

	destinationPointer = &board[kingLine][kingColumn+1];
	if(checkPossibleKing(piece, destinationPointer))
	{
		return true;
	}
	destinationPointer = &board[kingLine][kingColumn-1];
	if(checkPossibleKing(piece, destinationPointer))
	{
		return true;
	}
	destinationPointer = &board[kingLine+1][kingColumn];
	if(checkPossibleKing(piece, destinationPointer))
	{
		return true;
	}
	destinationPointer = &board[kingLine-1][kingColumn];
	if(checkPossibleKing(piece, destinationPointer))
	{
		return true;
	}
	destinationPointer = &board[kingLine+1][kingColumn+1];
	if(checkPossibleKing(piece, destinationPointer))
	{
		return true;
	}
	destinationPointer = &board[kingLine-1][kingColumn+1];
	if(checkPossibleKing(piece, destinationPointer))
	{
		return true;
	}
	destinationPointer = &board[kingLine+1][kingColumn-1];
	if(checkPossibleKing(piece, destinationPointer))
	{
		return true;
	}
	destinationPointer = &board[kingLine-1][kingColumn-1];
	if(checkPossibleKing(piece, destinationPointer))
	{
		return true;
	}

	piece->canMove = false;
	return false;
}

void multipleCheckProtocol(struct pieces board[LINES][COLUMNS], int* turnIndex)
{
	struct pieces* piecePointer;

	piecesCantMove(board, turnIndex);

	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			if(board[i][j].color != *turnIndex && board[i][j].type == KING)
			{
				piecePointer = &board[i][j];
				break;
			}
		}
	}

	if(!checkKingCanMove(board, piecePointer))
	{
		printf("Check Mate!");
		fflush(stdin);
		exit(0);
	}
	else
	{
		return;
	}
}

void singleCheckProtocol(struct pieces board[LINES][COLUMNS], int* turnIndex, struct pieces* piece)
{
	piecesCantMove(board, turnIndex);

	switch(checkCheckType(piece))
	{
	case BISHOP:
		if(!checkBlockDiagonalProtocol(board))
		{
			if(!checkKingCanMove(board, piece))
			{
				printf("Check Mate!");
				fflush(stdin);
				exit(0);
			}
			else
			{
				return;
			}
		}
		break;
	case ROOK:
		if(!checkBlockStraightProtocol(board))
		{
			if(!checkKingCanMove(board, piece))
			{
				printf("Check Mate!");
				fflush(stdin);
				exit(0);
			}
			else
			{
				return;
			}
		}
		break;
	case KNIGHT:
		if(!checkCaptureProtocol(board))
		{
			if(!checkKingCanMove(board, piece))
			{
				printf("Check Mate!");
				fflush(stdin);
				exit(0);
			}
			else
			{
				return;
			}
		}
		break;
	case PAWN:
		if(!checkCaptureProtocol(board))
		{
			if(!checkKingCanMove(board, piece))
			{
				printf("Check Mate!");
				fflush(stdin);
				exit(0);
			}
			else
			{
				return;
			}
		}
		break;
	}
	return;
}

void enPassant(struct pieces* piece, struct pieces* destination)
{
	if(piece->color == WHITE)
	{
		strcpy((destination + COLUMNS)->representation, "   ");
		(destination + COLUMNS)->type = EMPTY;
		(destination + COLUMNS)->color = EMPTY;
		(destination + COLUMNS)->canMove = false;
		(destination + COLUMNS)->hasMoved = false;
		(destination + COLUMNS)->justMoved = false;
	}
	else
	{
		strcpy((destination - COLUMNS)->representation, "   ");
		(destination - COLUMNS)->type = EMPTY;
		(destination - COLUMNS)->color = EMPTY;
		(destination - COLUMNS)->canMove = false;
		(destination - COLUMNS)->hasMoved = false;
		(destination - COLUMNS)->justMoved = false;
	}

	return;
}

void piecesCantMove(struct pieces board[LINES][COLUMNS], int* turnIndex)
{
	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			if(board[i][j].color != *turnIndex && board[i][j].type != KING)
			{
				board[i][j].canMove = false;
			}
		}
	}

	return;
}

void clearTemporary(struct pieces board[LINES][COLUMNS])
{
	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			board[i][j].justMoved = false;
			board[i][j].checking = false;
			if(board[i][j].type != EMPTY)
			{
				board[i][j].canMove = true;
			}
		}
	}
}

int checkCheckType(struct pieces* piece)
{
	if(checkCheckDiagonal(piece) > 0)
	{
		return BISHOP;
	}
	if(checkCheckStraight(piece) > 0)
	{
		return ROOK;
	}
	if(checkCheckKnight(piece) > 0)
	{
		return KNIGHT;
	}
	if(checkCheckPawn(piece) > 0)
	{
		return PAWN;
	}
}

bool checkCaptureProtocol(struct pieces board[LINES][COLUMNS])
{
	struct pieces* piecePointer;

	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			if(board[i][j].checking)
			{
				piecePointer = &board[i][j];
			}
		}
	}

	if(checkCheck(piecePointer) >= 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool checkBlockDiagonalProtocol(struct pieces board[LINES][COLUMNS])
{
	struct pieces* piecePointer;
	struct pieces* kingPointer;
	bool canBlock;
	int temporaryColor;
	canBlock = false;

	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			if(board[i][j].checking)
			{
				piecePointer = &board[i][j];
			}
		}
	}

	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			if(board[i][j].type == KING && board[i][j].color != piecePointer->color)
			{
				kingPointer = &board[i][j];
			}
		}
	}

	if(kingPointer->line > piecePointer->line && kingPointer->column > piecePointer->column)
	{
		for(int i=0; i<(kingPointer->line - piecePointer->line); i++)
		{
			temporaryColor = (piecePointer+(i*COLUMNS)+i)->color;
			(piecePointer+(i*COLUMNS)+i)->color = piecePointer->color;

			if(checkCheck(piecePointer+(i*COLUMNS)+i) >= 1)
			{
				canBlock = true;
			}

			(piecePointer+(i*COLUMNS)+i)->color = temporaryColor;
		}
	}

	if(kingPointer->line > piecePointer->line && kingPointer->column < piecePointer->column)
	{
		for(int i=0; i<(kingPointer->line - piecePointer->line); i++)
		{
			temporaryColor = (piecePointer+(i*COLUMNS)-i)->color;
			(piecePointer+(i*COLUMNS)-i)->color = piecePointer->color;

			if(checkCheck(piecePointer+(i*COLUMNS)-i) >= 1)
			{
				canBlock = true;
			}

			(piecePointer+(i*COLUMNS)-i)->color = temporaryColor;
		}
	}

	if(kingPointer->line < piecePointer->line && kingPointer->column > piecePointer->column)
	{
		for(int i=0; i<(piecePointer->line - kingPointer->line); i++)
		{
			temporaryColor = (piecePointer-(i*COLUMNS)+i)->color;
			(piecePointer-(i*COLUMNS)+i)->color = piecePointer->color;

			if(checkCheck(piecePointer-(i*COLUMNS)+i) >= 1)
			{
				canBlock = true;
			}

			(piecePointer-(i*COLUMNS)+i)->color = temporaryColor;
		}
	}

	if(kingPointer->line < piecePointer->line && kingPointer->column < piecePointer->column)
	{
		for(int i=0; i<(piecePointer->line - kingPointer->line); i++)
		{
			temporaryColor = (piecePointer-(i*COLUMNS)-i)->color;
			(piecePointer-(i*COLUMNS)-i)->color = piecePointer->color;

			if(checkCheck(piecePointer-(i*COLUMNS)-i) >= 1)
			{
				canBlock = true;
			}

			(piecePointer-(i*COLUMNS)-i)->color = temporaryColor;
		}
	}

	return canBlock;
}

bool checkBlockStraightProtocol(struct pieces board[LINES][COLUMNS])
{
	struct pieces* piecePointer;
	struct pieces* kingPointer;
	bool canBlock;
	int temporaryColor;
	canBlock = false;

	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			if(board[i][j].checking)
			{
				piecePointer = &board[i][j];
			}
		}
	}

	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			if(board[i][j].type == KING && board[i][j].color != piecePointer->color)
			{
				kingPointer = &board[i][j];
			}
		}
	}

	if(kingPointer->line > piecePointer->line)
	{
		for(int i=0; i<(kingPointer->line - piecePointer->line); i++)
		{
			temporaryColor = (piecePointer+(i*COLUMNS))->color;
			(piecePointer+(i*COLUMNS))->color = piecePointer->color;

			if(checkCheck(piecePointer+(i*COLUMNS)) >= 1)
			{
				canBlock = true;
			}

			(piecePointer+(i*COLUMNS))->color = temporaryColor;
		}
	}

	if(kingPointer->line < piecePointer->line)
	{
		for(int i=0; i<(piecePointer->line - kingPointer->line); i++)
		{
			temporaryColor = (piecePointer-(i*COLUMNS))->color;
			(piecePointer-(i*COLUMNS))->color = piecePointer->color;

			if(checkCheck(piecePointer-(i*COLUMNS)) >= 1)
			{
				canBlock = true;
			}

			(piecePointer-(i*COLUMNS))->color = temporaryColor;
		}
	}

	if(kingPointer->column > piecePointer->column)
	{
		for(int i=0; i<(kingPointer->column - piecePointer->column); i++)
		{
			temporaryColor = (piecePointer+i)->color;
			(piecePointer+i)->color = piecePointer->color;

			if(checkCheck(piecePointer+i) >= 1)
			{
				canBlock = true;
			}

			(piecePointer+i)->color = temporaryColor;
		}
	}

	if(kingPointer->column < piecePointer->column)
	{
		for(int i=0; i<(piecePointer->column - kingPointer->column); i++)
		{
			temporaryColor = (piecePointer-i)->color;
			(piecePointer-i)->color = piecePointer->color;

			if(checkCheck(piecePointer-i) >= 1)
			{
				canBlock = true;
			}

			(piecePointer-i)->color = temporaryColor;
		}
	}

	return canBlock;
}

void bringBackPiece(struct pieces* temporaryPiece, struct pieces* piece)
{
	strcpy(piece->representation, temporaryPiece->representation);
	piece->type = temporaryPiece->type;
	piece->color = temporaryPiece->color;
	piece->canMove = temporaryPiece->canMove;
	piece->hasMoved = temporaryPiece->hasMoved;
	piece->justMoved = temporaryPiece->justMoved;
}

bool checkPossibleCheck(struct pieces* piece, struct pieces* destination, struct pieces board[LINES][COLUMNS])
{
	struct pieces temporaryPiece;
	struct pieces temporaryDestination;
	struct pieces* temporaryPiecePointer;
	struct pieces* temporaryDestinationPointer;
	struct pieces* kingPointer;
	temporaryPiece = *piece;
	temporaryDestination = *destination;
	temporaryPiecePointer = &temporaryPiece;
	temporaryDestinationPointer = &temporaryDestination;

	for(int i=0; i<LINES; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			if(board[i][j].type == KING && board[i][j].color == piece->color)
			{
				kingPointer = &board[i][j];
			}
		}
	}

	movePiece(piece, destination);

	if(checkCheck(kingPointer) >= 1)
	{
		bringBackPiece(temporaryPiecePointer, piece);
		bringBackPiece(temporaryDestinationPointer, destination);
		return false;
	}
	else
	{
		bringBackPiece(temporaryPiecePointer, piece);
		bringBackPiece(temporaryDestinationPointer, destination);
		return true;
	}
}

/*void promotion(struct pieces* piece)
{
	int promotionPiece, promotionCounterBlack, promotionCounterWhite, promotionNumber;
	char promotionDigit, promotionType[CHARACTERS];

	printf("\nWhat piece would you like to promote to?\n");
	printf("1 - Queen\n");
	printf("2 - Rook\n");
	printf("3 - Bishop\n");
	printf("4 - Knight\n");
	printf("(Type the number next to the option you would like to choose!)\n");
	scanf("%i",&promotionPiece);

	switch(promotionPiece)
	{
	case 1:
		if(piece->color == BLACK)
		{
			promotionNumber = 1 + promotionCounterBlack;
		}
		else
		{
			promotionNumber = 1 + promotionCounterWhite;
		}
		promotionDigit = promotionNumber + '0';
		strcpy(promotionType, "Qn");
		strncat(promotionType, &promotionDigit, 1);
		printf("%s",promotionType);
		strcpy(piece->representation, promotionType);
		piece->type = QUEEN;
		break;
	case 2:
		if(piece->color == BLACK)
		{
			promotionNumber = 2 + promotionCounterBlack;
		}
		else
		{
			promotionNumber = 2 + promotionCounterWhite;
		}
		promotionDigit = promotionNumber + '0';
		strcpy(promotionType, "Rk");
		strncat(promotionType, &promotionDigit, 1);
		strcpy(piece->representation, promotionType);
		piece->type = ROOK;
		break;
	case 3:
		if(piece->color == BLACK)
		{
			promotionNumber = 2 + promotionCounterBlack;
		}
		else
		{
			promotionNumber = 2 + promotionCounterWhite;
		}
		promotionDigit = promotionNumber + '0';
		strcpy(promotionType, "Bp");
		strncat(promotionType, &promotionDigit, 1);
		strcpy(piece->representation, promotionType);
		piece->type = BISHOP;
		break;
	case 4:
		if(piece->color == BLACK)
		{
			promotionNumber = 2 + promotionCounterBlack;
		}
		else
		{
			promotionNumber = 2 + promotionCounterWhite;
		}
		promotionDigit = promotionNumber + '0';
		strcpy(promotionType, "Kt");
		strncat(promotionType, &promotionDigit, 1);
		strcpy(piece->representation, promotionType);
		piece->type = KNIGHT;
		break;
	default:
		printf("Invalid option!");
		promotion(piece);
		break;
	}
	if(piece->color == BLACK)
	{
		promotionCounterBlack++;
	}
	else
	{
		promotionCounterWhite++;
	}
	return;
}*/
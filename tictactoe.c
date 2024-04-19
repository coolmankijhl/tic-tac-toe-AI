#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define SIZE 9

void printBoard();
int evaluateBoard();
void placePiece(char playerPiece, char currentTurnPiece);

char board[SIZE] = {
	'-','-','-',
	'-','-','-',
	'-','-','-'
};

const int winningCombinations[8][3] = {
	{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
	{0, 3, 6}, {1, 4, 7}, {2, 5, 8},
	{0, 4, 8}, {2, 4, 6}
};

// Returns the char of the player who won, returns '-' if game is still going, returns 'D' if game is a draw
char checkWinner()
{
	for(int i = 0; i < 8; i++)
	{
		int a = winningCombinations[i][0];
		int b = winningCombinations[i][1];
		int c = winningCombinations[i][2];

		if(board[a] == board[b] && board[b] == board[c] && board[c] != '-')
			return board[a];
	}

	for(int i = 0; i < SIZE; i++)
	{
		if(board[i] == '-')
			return '-';

	}

	return 'D';
}

// Evaluates the current score of the board
int evaluate()
{
	switch(checkWinner())
	{
		case('X'):
			return 10;
		case('O'):
			return -10;
		case('D'):
			return 1;
		default:
			return 0;
	}
}

// Prints board to screen
void printBoard()
{

	printf("\n");
	printf(" 1 | 2 | 3\n");
	printf("---|---|---\n");
	printf(" 4 | 5 | 6\n");
	printf("---|---|---\n");
	printf(" 7 | 8 | 9\n");

	printf("\n");
	printf(" %c | %c | %c\n", board[0], board[1], board[2]);
	printf("---|---|---\n");
	printf(" %c | %c | %c\n", board[3], board[4], board[5]);
	printf("---|---|---\n");
	printf(" %c | %c | %c\n", board[6], board[7], board[8]);
	printf("\n");
}

// Handles User/Bot Input and places piece on board accordingly
void placePiece(char playerPiece, char currentTurnPiece)
{
	int selectedSlot;
	do
	{
		if(playerPiece == currentTurnPiece)
			scanf("%d", &selectedSlot);
		else
			selectedSlot = rand()%9+1;
	}
	while(!(selectedSlot > 0 && selectedSlot < 10) || board[selectedSlot-1] != '-');

	board[selectedSlot-1] = currentTurnPiece;
}

// Initalizes game settings and handles turns
int main()
{
	srand(time(NULL));

	int isXTurn = 1;

	printf("Would you like to be X or O: ");
	char playerPiece = getchar();

	while(checkWinner() ==  '-')
	{
		printBoard();
		if(isXTurn)
		{
			placePiece(playerPiece, 'X');
			isXsTurn = 0;
		}
		else
		{
			placePiece(playerPiece, 'O');
			isXsTurn = 1;
		}
	}
	printBoard();
}

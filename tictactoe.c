#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 9

void printBoard();
int evaluate();
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

// Minimax algorithm, X is maximizer, O is minimizer
int minimax(int isMaximizing)
{
	if(checkWinner() != '-')
		return evaluate();

	// if current move is X
	if(isMaximizing)
	{
		int maxScore = INT_MIN;
		int maxScoreIndex = -1;
		for(int i = 0; i < SIZE; i++)
		{
			if(board[i] == '-')
			{
				board[i] = 'X';
				int score = minimax(0);
				if(maxScore < score)
				{
					maxScore = score;
					maxScoreIndex = i;
				}
				board[i] = '-';
			}
		}
		return maxScore;
	}
	else
	{
		int minScore = INT_MAX;
		int minScoreIndex = -1;
		for(int i = 0; i < SIZE; i++)
		{
			if(board[i] == '-')
			{
				board[i] = 'O';
				int score = minimax(1);
				if(minScore > score)
				{
					minScore = score;
					minScoreIndex = i;
				}
				board[i] = '-';
			}
		}
		return minScore;
	}
}

int findBestMove(int isMaximizing)
{
	int bestMove = -1;
	int bestScore = isMaximizing ? INT_MIN : INT_MAX;
	for (int i = 0; i < SIZE; i++)
       	{
		if(board[i] == '-') 
		{
			board[i] = isMaximizing ? 'X' : 'O';
			int score = minimax(!isMaximizing);
			board[i] = '-';
			if((isMaximizing && score > bestScore) || (!isMaximizing && score < bestScore)) 
			{
				bestScore = score;
				bestMove = i;
			}
		}
	}
	return bestMove + 1; // Convert to 1-based indexing
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
		{
			if(currentTurnPiece == 'X')
				selectedSlot = findBestMove(1);
			else
				selectedSlot = findBestMove(0);
			printf("Bot picked %d\n", selectedSlot);
		}
	}
	while(!(selectedSlot > 0 && selectedSlot < 10) || board[selectedSlot-1] != '-');

	board[selectedSlot-1] = currentTurnPiece;
}

// Initalizes game settings and handles turns
int main()
{
	int isXTurn = 1;

	printf("Would you like to be X or O: ");
	char playerPiece = getchar();

	while(checkWinner() ==  '-')
	{
		printBoard();
		if(isXTurn)
		{
			placePiece(playerPiece, 'X');
			isXTurn = 0;
		}
		else
		{
			placePiece(playerPiece, 'O');
			isXTurn = 1;
		}
	}
	printBoard();
}

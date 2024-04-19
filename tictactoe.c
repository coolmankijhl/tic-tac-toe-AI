#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void printBoard();
int placePiece(int pos, char piece);
int evaluateBoard();
int minimax(int isXsTurn);

char playerPiece;
char botPiece;
char userInput[5];

char board[9] = {
	'1','2','3',
	'4','5','6',
	'7','8','9'
};

const int winningCombinations[8][3] = {
	{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
	{0, 3, 6}, {1, 4, 7}, {2, 5, 8},
	{0, 4, 8}, {2, 4, 6}
};

// Handles User/Bot Input and places piece on board accordingly
int placePiece(int pos, char piece)
{
	if(playerPiece == piece)
	{
		printf("%c's turn: ", piece);

		scanf(" %d", &pos);

		if(board[pos-1] > 48 && board[pos-1] < 58 && pos < 10 && pos > 0)
		{
			board[pos-1] = piece;
			return 1;
		}
	}
	else
	{
		int bestMoveScore = INT_MIN;
		int bestMoveIndex = -1;

		for(int i = 0; i < 9; i++)
		{
			if(board[i] != 'X' && board[i] != 'O')
			{
				board[i] = botPiece;
				int moveScore = minimax(0);
				board[i] = (i + 49);

				if(moveScore > bestMoveScore)
				{
					bestMoveScore = moveScore;
					bestMoveIndex = i;
				}
			}
		}
		printf("The bot picked %d\n", bestMoveIndex+1);
		board[bestMoveIndex] = botPiece;
		return 1;	
	}

	printBoard();
	printf("Piece placement failed, try again\n");
	return 0;
}

// Evaluates the current score of the board, can be used to check whether the game is over or not
int evaluateBoard()
{
	for (int i = 0; i < 8; i++)
	{
		int a = winningCombinations[i][0],  b = winningCombinations[i][1], c = winningCombinations[i][2];

		if (board[a] == board[b] && board[b] == board[c] && board[a] != (a + '1'))
		{
			if (board[a] == 'X')
			{
				//X wins
				return -1;
			}
			else if (board[a] == 'O')
			{
				//O Wins
				return 1;
			}
		}
	}	

	for(int i = 0; i < 9; i++)
	{
		if(board[i] != 'X' && board[i] != 'O')
		{
			return 0;
		}
		
		if(i == 8)
		{
			//Tie
			return 0;
		}
	}

	return 0;
}

// Recursively searches for possible moves and their scores
int minimax(int isXsTurn)
{
	int score = evaluateBoard();

	if(score != 0)
		return score;

	if(isXsTurn)
	{
		int bestScore = INT_MIN;
		for(int i = 0; i < 9; i++)
		{
			if(board[i] != 'X' && board[i] != 'O')
			{
				board[i] = 'X';
				bestScore = ((bestScore > minimax(0)) ? bestScore : minimax(0));
				board[i] = (i + 49);
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = INT_MAX;
		for(int i = 0; i < 9; i++)
		{
			if(board[i] != 'X' && board[i] != 'O')
			{
				board[i] = 'O';
				bestScore = ((bestScore > minimax(1)) ? bestScore : minimax(1));
				board[i] = (i + 49);
			}
		}	
	}
}

// Prints board to screen
void printBoard()
{
	printf("\n");
	printf(" %c | %c | %c\n", board[0], board[1], board[2]);
	printf("---|---|---\n");
	printf(" %c | %c | %c\n", board[3], board[4], board[5]);
	printf("---|---|---\n");
	printf(" %c | %c | %c\n", board[6], board[7], board[8]);
	printf("\n");
}

// Initalizes game settings and handles turns
int main()
{
	int isXsTurn = 1;
	int pos;

	printf("Would you like to be X or O: ");

	fgets(userInput, sizeof(userInput), stdin);
	playerPiece = userInput[0];

	if(playerPiece == 'X')
		botPiece = 'O';
	else
		botPiece = 'X';

	while(1)
	{
		printBoard();
		if(isXsTurn)
		{
			while(!placePiece(pos, 'X'));
			isXsTurn = 0;
		}
		else
		{
			while(!placePiece(pos, 'O'));
			isXsTurn = 1;
		}
	}
	printBoard();
}

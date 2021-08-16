#include <iostream>
#include <vector>
#include <array>

using namespace std;

const int WIN_COMBINATIONS = 8;
const char X = 'x';
const char O = 'o';


void printBoard(int (&board)[3][3]);
bool isValidMove(int (&board)[3][3], int row, int col);
bool isWinner(int(&winConditions)[WIN_COMBINATIONS][3][2], int(&board)[3][3], int row, int col);

int main() {
	
	int board[3][3] = { {'.','.','.'}, {'.','.','.'}, {'.','.','.'} };
	int winConditions[WIN_COMBINATIONS][3][2] = { 
		{ {0,0 }, { 1,0 }, { 2,0 } }, 
		{ {0,1 }, { 1,1 }, { 2,1 } }, 
		{ {0,2 }, { 1,2 }, { 2,2 } }, 
		{ {0,0 }, { 0,1 }, { 0,2 } }, 
		{ {1,0 }, { 1,1 }, { 1,2 } },
		{ {2,0 }, { 2,1 }, { 2,2 } },
		{ {0,0 }, { 1,1 }, { 2,2 } },
		{ {0,2 }, { 1,1 }, { 2,0 } },
	};
	int playerTurn = 0;
	char currentTurn;
	int round = 1;
	int row, col;
	cout << "GAME START\n----------\n";
	while (round < 10) {
		currentTurn = playerTurn % 2 == 0 ? X : O;
		printBoard(board);
		cout << "Player " << currentTurn << " it's your turn! Enter a row and a col: ";
		cin >> row >> col;
		if (isValidMove(board, row, col)) {
			board[row][col] = currentTurn;
			if (isWinner(winConditions, board, row, col)) {
				printBoard(board);
				cout <<"CONGRATS! " << currentTurn << " is the WINNER!\n";
				break;
			}
			round++;
			playerTurn++;
		}
		else {
			cout << "Not a valid move. Please try again!" << endl;
		}
	}
	printBoard(board);
	cout << "DRAW!\n";
}

bool isWinner(int (&winConditions)[WIN_COMBINATIONS][3][2], int (&board)[3][3], int row, int col)
{
	for (int i = 0; i < WIN_COMBINATIONS; i++) {
		bool isWinner = true;
		char currentChoice = board[winConditions[i][0][0]][winConditions[i][0][1]];
		for (int j = 0; j < 3; j++) {
			int row = winConditions[i][j][0];
			int col = winConditions[i][j][1];
			char currentSelection = board[row][col];
			if (isWinner && (currentChoice != currentSelection || currentSelection == '.')) {
				isWinner = false;
			}
		}
		if (isWinner) return true;
	}
	return false;
}

bool isValidMove(int (&board)[3][3], int row, int col) {
	if ((row >= 0 && row < 3) && (col >= 0 && col < 3)) {
		char currentBoardSelection = board[row][col];
		return currentBoardSelection == '.';
	} 
	return false;
}

void printBoard(int (&board)[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			char currentSelection = board[i][j];
			cout << currentSelection << (j == 2 ? "" : " | ");
		}
		cout << endl << "---------" << endl;
	}
}
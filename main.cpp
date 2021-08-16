#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <array>

using namespace std;

const int WIN_COMBINATIONS = 8;
const char X = 'x';
const char O = 'o';
const int WIN_CONDITIONS[WIN_COMBINATIONS][3][2] = {
		{ {0,0 }, { 1,0 }, { 2,0 } },
		{ {0,1 }, { 1,1 }, { 2,1 } },
		{ {0,2 }, { 1,2 }, { 2,2 } },
		{ {0,0 }, { 0,1 }, { 0,2 } },
		{ {1,0 }, { 1,1 }, { 1,2 } },
		{ {2,0 }, { 2,1 }, { 2,2 } },
		{ {0,0 }, { 1,1 }, { 2,2 } },
		{ {0,2 }, { 1,1 }, { 2,0 } },
};


void printBoard(int (&board)[3][3]);
bool isValidMove(int (&board)[3][3], int row, int col);
bool isWinner(int(&board)[3][3], int row, int col);
vector<array<int, 2>> findAvailableChoices(int(&board)[3][3]);
void onePlayerGame();
void twoPlayerGame();

int main() {
	srand(time(nullptr));  //seeding random function with current system time
	int gameSelection;
	cout << "Welcome to Tic Tac Toe! Please select either a (1) Player Game or a (2) Player Game!\n1 or 2 players: ";
	cin >> gameSelection;
	cout << "GAME START\n----------\n";
	if (gameSelection == 1) {
		onePlayerGame();
	}
	else {
		twoPlayerGame();
	}
}

void onePlayerGame()
{
	//player will be x, cpu will be 0
	int board[3][3] = { {'.','.','.'}, {'.','.','.'}, {'.','.','.'} };
	int playerTurn = 0;
	char currentTurn;
	int round = 1;
	int row, col;
	while (round < 10) {
		currentTurn = playerTurn % 2 == 0 ? X : O;
		printBoard(board);
		if (currentTurn == X) {
			cout << "Human, it's your turn! Enter a row and a col: ";
			cin >> row >> col;
			if (!isValidMove(board, row, col)) {
				cout << "Not a valid move. Please try again!" << endl;
				continue;
			}
			board[row][col] = currentTurn;

		}
		else {
			vector<array<int, 2>> availableMoves = findAvailableChoices(board);
			int random_index = rand() % availableMoves.size();
			row = availableMoves[random_index][0];
			col = availableMoves[random_index][1];
			cout << "Computer chooses to place at row: " << row << ", col: " << col << endl;
		}
		board[row][col] = currentTurn;
		if (isWinner(board, row, col)) {
			printBoard(board);
			string winMessage = currentTurn == X ? "You WIN! You beat the computer!" : "Sorry, you have LOST to the computer!";
			cout << winMessage << endl;
			break;
		} else {
			round++;
			playerTurn++;
		}
	}
	printBoard(board);
	if (round >= 10) {
		cout << "DRAW!\n";
	}
}

void twoPlayerGame() {
	int board[3][3] = { {'.','.','.'}, {'.','.','.'}, {'.','.','.'} };
	int playerTurn = 0;
	char currentTurn;
	int round = 1;
	int row, col;
	while (round < 10) {
		currentTurn = playerTurn % 2 == 0 ? X : O;
		printBoard(board);
		cout << "Player " << currentTurn << " it's your turn! Enter a row and a col: ";
		cin >> row >> col;
		if (isValidMove(board, row, col)) {
			board[row][col] = currentTurn;
			if (isWinner(board, row, col)) {
				printBoard(board);
				cout << "CONGRATS! " << currentTurn << " is the WINNER!\n";
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

vector<array<int, 2>> findAvailableChoices(int(&board)[3][3])
{
	vector<array<int, 2>> availableChoices = {};
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (isValidMove(board, row, col)) {
				availableChoices.push_back(array<int, 2>{row, col});
			}
		}
	}
	return availableChoices;
}

bool isWinner(int (&board)[3][3], int row, int col)
{
	for (int i = 0; i < WIN_COMBINATIONS; i++) {
		bool isWinner = true;
		char currentChoice = board[WIN_CONDITIONS[i][0][0]][WIN_CONDITIONS[i][0][1]];
		for (int j = 0; j < 3; j++) {
			int row = WIN_CONDITIONS[i][j][0];
			int col = WIN_CONDITIONS[i][j][1];
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
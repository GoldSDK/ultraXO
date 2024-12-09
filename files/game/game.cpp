#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "../save/save.h"
using namespace std;

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

void printBoard(const vector<vector<char>>& board) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cout << board[i][j];
			if (j < 2) cout << "|";
		}
		cout << endl;
		if (i < 2) cout << "-----" << endl;
	}
}

bool makeMove(vector<vector<char>>& board, int row, int col, char player) {
	// Преобразуем 1-индексацию в 0-индексацию
	row--;
	col--;
	if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != EMPTY) {
		return false;
	}
	board[row][col] = player;
	return true;
}

bool checkWin(const vector<vector<char>>& board, char player) {
	for (int i = 0; i < 3; ++i) {
		if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
			return true;
		}
	}
	return (board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

bool isBoardFull(const vector<vector<char>>& board) {
	for (const auto& row : board) {
		for (char cell : row) {
			if (cell == EMPTY) {
				return false;
			}
		}
	}
	return true;
}

void vsBot() {
	vector<vector<char>> board(3, vector<char>(3, EMPTY));
	string plName, botName = "Бот";
	plName = playerName(1);
	char currentPlayer = PLAYER_X;
	srand(static_cast<unsigned int>(time(0)));

	while (true) {
		printBoard(board);
		int row, col;
		cout << playerName << ", введите строку и столбец (1, 2 или 3): ";
		cin >> row >> col;
		while (!makeMove(board, row, col, currentPlayer)) {
			cout << "Некорректный ход, попробуйте снова: ";
			cin >> row >> col;
		}
		if (checkWin(board, currentPlayer)) {
			printBoard(board);
			cout << playerName << " выиграл!" << endl;
			winPoint();
			return;
		}
		if (isBoardFull(board)) {
			printBoard(board);
			cout << "Ничья!" << endl;
			return;
		}

		// Ход бота
		currentPlayer = PLAYER_O;
		int botRow, botCol;
		do {
			botRow = rand() % 3 + 1; // Генерация случайного числа от 1 до 3
			botCol = rand() % 3 + 1; // Генерация случайного числа от 1 до 3
		} while (!makeMove(board, botRow, botCol, currentPlayer));

		cout << botName << " поставил O на клетку (" << botRow << ", " << botCol << ")" << endl;

		if (checkWin(board, currentPlayer)) {
			printBoard(board);
			losePoint();
			cout << botName << " выиграл!" << endl;
			return;
		}
		if (isBoardFull(board)) {
			printBoard(board);
			cout << "Ничья!" << endl;
			return;
		}

		currentPlayer = PLAYER_X; // Смена игрока
	}
}

void vsPlayer() {
	vector<vector<char>> board(3, vector<char>(3, EMPTY));
	string player1Name, player2Name;
	player1Name = playerName(1); player2Name = playerName(2);

	char currentPlayer = PLAYER_X;
	while (true) {
		printBoard(board);
		int row, col;
		cout << (currentPlayer == PLAYER_X ? player1Name : player2Name) << ", введите строку и столбец (1, 2 или 3): ";
		cin >> row >> col;
		while (!makeMove(board, row, col, currentPlayer)) {
			cout << "Некорректный ход, попробуйте снова: ";
			cin >> row >> col;
		}
		if (checkWin(board, currentPlayer)) {
			printBoard(board);
			cout << (currentPlayer == PLAYER_X ? player1Name : player2Name) << " выиграл!" << endl;
			if (currentPlayer == PLAYER_X) {
				winPoint();
			}
			else {
				losePoint();
			}
			return;
		}
		if (isBoardFull(board)) {
			printBoard(board);
			cout << "Ничья!" << endl;
			return;
		}

		currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X; // Смена игрока
	}
}

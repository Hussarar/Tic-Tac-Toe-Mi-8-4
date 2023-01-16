#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdbool.h>

// Defines für den Computerspieler
#define AI 'X'    // Computerspieler
#define HUMAN 'O' // Mensch

// Schwierigkeitsgrade für Lesbarkeit
#define EASY 1
#define MEDIUM 2
#define HARD 3

// Struct um Zeilen und Spalten der Array Position für der Computerspieler zu speichern
typedef struct
{
    int row;
    int col;
} move_t;

char checkWinner(char board[3][3]);

void init_board(char board[3][3]);

void bestMove(char board[3][3]);

int minimax(char board[3][3], bool isMaximizing);

int getMin(int val1, int val2);

int getMax(int val1, int val2);

bool equals3(char a, char b, char c);

void ComputerPlayer(char board[3][3], int difficulty);

void randomMove(char board[3][3]);

void startCurses();

int setAndCheckMove(char board[3][3], int pos, char currentPlayer);

#endif
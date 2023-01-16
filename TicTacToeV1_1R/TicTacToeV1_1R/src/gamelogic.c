#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <pdcurses.h>
#include "gamelogic.h"

/*
 * Funktion: ComputerPlayer
 * Steuert den zweiten Spieler
 * ---------------------
 * board: 3x3 Spielfeld auf dem der Zug gemacht wird
 * difficulty: Schwierigkeitsgrad Leicht (1), Mittel (2), Schwer (3),
 * wenn es sich um einen Computerspieler handelt
 */
void ComputerPlayer(char board[3][3], int difficulty)
{
    switch (difficulty)
    {
    case EASY:
        randomMove(board);
        break;
    case MEDIUM:
        if ((rand() % 101) > 50)
        {
            randomMove(board);
        }
        else
        {
            bestMove(board);
        }
        break;
    case HARD:
        bestMove(board);
        break;
    }
}

/*
 * Funktion: randomMove
 * Macht einen zufälligen Zug anhand der rand() Funktion
 * ---------------------
 * board: 3x3 Spielfeld auf dem ein Zug gemacht wird
 */
void randomMove(char board[3][3])
{
    while (1)
    {
        int row = rand() % 3;
        int col = rand() % 3;

        if (board[row][col] == ' ')
        {
            board[row][col] = AI;
            break;
        }
    }
}

/*
 * Funktion: bestMove
 * Findet mithilfe minimax den best möglichen Zug
 * den der Computerspieler machen kann und setzt diesen
 * ---------------------
 * board: 3x3 Spielfeld auf dem der Zug gemacht wird
 */
void bestMove(char board[3][3])
{
    int bestScore = (int)-INFINITY;
    move_t move;
    // Alle Spielfeld Positionen werden iteriert
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            // Ist der Platz verfügbar?
            if (board[i][j] == ' ')
            {
                board[i][j] = AI;
                int score = minimax(board, false);
                board[i][j] = ' ';
                /*Mithilfe vom Minimax ermittelten Score
                wird die beste Position festgelegt*/
                if (score > bestScore)
                {
                    bestScore = score;
                    move.row = i;
                    move.col = j;
                }
            }
        }
    }
    board[move.row][move.col] = AI;
}

/*
 * Funktion: scoreLookup
 * Wertet das Ergebnis der CheckWinner Funktion aus
 * ---------------------
 * result: Ergebnis der checkWinner Funktion
 *
 * Gibt eine positive Punktzahl zurück, wenn der Computer gewinnen würde
 * Gibt eine negative Punktzahl zurück, wenn der Computer verlieren würde
 * Gibt 0 zurück, bei allen anderen Fällen
 */
int scoreLookup(char result)
{
    if (result == AI)
    {
        return 1;
    }
    else if (result == HUMAN)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/*
 * Funktion: minimax
 * Iteriert ALLE möglichen Zustände des Spielfelds mithilfe
 * von Rekursion und findet so den besten möglichen Zug
 * ---------------------
 * board: 3x3 Spielfeld auf dem der Zug gemacht wird
 * isMaximizing: Wahrheitswert, ob es sich um den minimierenden oder maximierenden Spieler handelt
 */
int minimax(char board[3][3], bool isMaximizing)
{
    int result = checkWinner(board);
    if (result != 'N')
    {
        return scoreLookup(result);
    }
    /*
     * Wenn es der maximierende Spieler (Computer) ist,
     * soll die höchste Punktzahl ermittelt werden
     */
    if (isMaximizing)
    {
        int bestScore = (int)-INFINITY;
        // Alle Spielfeld Positionen werden iteriert
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                // Ist der Platz verfügbar?
                if (board[i][j] == ' ')
                {
                    board[i][j] = AI;
                    int score = minimax(board, false);
                    board[i][j] = ' ';
                    bestScore = getMax(score, bestScore);
                }
            }
        }
        return bestScore;
        /*
         * Wenn es der minimierende Spieler (Mensch) ist,
         * soll die niedrigste Punktzahl ermittelt werden
         */
    }
    else
    {
        int bestScore = (int)INFINITY;
        // Alle Spielfeld Positionen werden iteriert
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                // Ist der Platz verfügbar?
                if (board[i][j] == ' ')
                {
                    board[i][j] = HUMAN;
                    int score = minimax(board, true);
                    board[i][j] = ' ';
                    bestScore = getMin(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

/*
 * Funktion: getMin
 * Liefert den kleinesten Wert von zwei Zahlen
 * ---------------------
 * val1: erste Zahl
 * val2: zweite Zahl
 */
int getMin(int val1, int val2)
{
    if (val1 > val2)
    {
        return val2;
    }
    return val1;
}

/*
 * Funktion: getMin
 * Liefert den größten Wert von zwei Zahlen
 * ---------------------
 * val1: erste Zahl
 * val2: zweite Zahl
 */
int getMax(int val1, int val2)
{
    if (val1 < val2)
    {
        return val2;
    }
    return val1;
}

/*
 * Funktion: init_board
 * Initialisiert das Spielfeld mit Leerzeichen
 * ---------------------
 * board: 3x3 Spielfeld welches initialisiert werden soll
 */
void init_board(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

/*
 * Funktion: checkWinner
 * Überprüft das Spielfeld auf einen Gewinner
 * ---------------------
 * board: 3x3 Spielfeld welches geprüft werden soll
 *
 * Gibt ein 'N' zurück, wenn kein Gewinner feststeht
 * Gibt ein 'T' zurück, wenn es ein Unentschieden ist
 * Gibt ein 'X' zurück, wenn X gewinnt
 * Gibt ein 'O' zurück, wenn O gewinnt
 */
char checkWinner(char board[3][3])
{
    char winner = 'N';

    // Horizontale Prüfung
    for (int i = 0; i < 3; i++)
    {
        if (equals3(board[i][0], board[i][1], board[i][2]))
        {
            winner = board[i][0];
        }
    }

    // Vertikale Prüfung
    for (int i = 0; i < 3; i++)
    {
        if (equals3(board[0][i], board[1][i], board[2][i]))
        {
            winner = board[0][i];
        }
    }

    // Diagonale Prüfung
    if (equals3(board[0][0], board[1][1], board[2][2]))
    {
        winner = board[0][0];
    }
    if (equals3(board[2][0], board[1][1], board[0][2]))
    {
        winner = board[2][0];
    }

    int openSpots = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                openSpots++;
            }
        }
    }
    /* Wenn noch kein Gewinner feststeht und alle Plätze belegt sind,
     * wird 'T' (untentschieden) als Rückgabewert festgelegt
     */
    if (winner == 'N' && openSpots == 0)
    {
        return 'T';
    }
    else
    {
        return winner;
    }
}

/*
 * Funktion: equals3
 * Überprüft, ob 3 Zeichen gleich und kein Leerzeichen sind
 * ---------------------
 * a: Zeichen 1
 * b: Zeichen 2
 * c: Zeichen 3
 *
 * Gibt einen Wahrheitswert zurück
 */
bool equals3(char a, char b, char c)
{
    return a == b && b == c && a != ' ';
}

/*
 * Funktion: startCurses()
 * Wechselt zu den Curses Window-System und konfiguriert Curses
 * ---------------------
 *
 */
void startCurses()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
}

/*
 * Funktion: setAndCheckMove(char board[3][3], int pos, char currentPlayer)
 * Überprüft ob der Zug erlaubt ist und setzt diesen
 * ---------------------
 * board: 3x3 Spielfeld welches geprüft werden soll
 * pos: Position an der, der Zug gemacht wurde
 * currentPlayer: Wer der momentane Spieler ist,
 * damit das korrekte Zeichen gesetzt
 *
 * Gibt einen Wahrheitswert zurück, ob der Zug erlaubt ist
 */
int setAndCheckMove(char board[3][3], int pos, char currentPlayer)
{
    switch (pos)
    {
    case 1:
        if (board[0][0] != ' ')
        {
            return 0;
        }
        board[0][0] = currentPlayer;
        return 1;
    case 2:
        if (board[0][1] != ' ')
        {
            return 0;
        }
        board[0][1] = currentPlayer;
        return 1;
    case 3:
        if (board[0][2] != ' ')
        {
            return 0;
        }
        board[0][2] = currentPlayer;
        return 1;
    case 4:
        if (board[1][0] != ' ')
        {
            return 0;
        }
        board[1][0] = currentPlayer;
        return 1;
    case 5:
        if (board[1][1] != ' ')
        {
            return 0;
        }
        board[1][1] = currentPlayer;
        return 1;
    case 6:
        if (board[1][2] != ' ')
        {
            return 0;
        }
        board[1][2] = currentPlayer;
        return 1;
    case 7:
        if (board[2][0] != ' ')
        {
            return 0;
        }
        board[2][0] = currentPlayer;
        return 1;
    case 8:
        if (board[2][1] != ' ')
        {
            return 0;
        }
        board[2][1] = currentPlayer;
        return 1;
    case 9:
        if (board[2][2] != ' ')
        {
            return 0;
        }
        board[2][2] = currentPlayer;
        return 1;
    }
    return 0;
}

#include <pdcurses.h>
#include <time.h>
#include <stdlib.h>
#include "gamevisuals.h"
#include "color.h"
#include "gamelogic.h"

int main()
{
    int position = 0;
    int mode = 0;
    int validMove = 1;
    char winResult = 'N';
    char answer = 'y';
    char currentPlayer = 'X'; // Es startet immer X
    char board[3][3];

    //Spiel wird initialisiert
    init_board(board);
    startCurses();
    if (checkWindowSize() == 1)
        return 1;
    init_colors();
    srand(time(NULL));
    
    while (1) // Main-Loop beginnt
    {
        mode = startmenu(); // Startmenü wird aufgerufen
        erase();
        if (mode == EASY || mode == MEDIUM || mode == HARD) // Spielmodus gegen Computer
        {
            curs_set(1);
            gamearena(); // Spielfeld wird ausgegeben
            while (1)    // Loop Spieler gegen Computer
            {
                if (validMove == 1) // Nach einem gültigem Zug vom Menschen ist der Computer dran
                {
                    ComputerPlayer(board, mode);
                    validMove = 0;
                }
                loadboard(board);
                winResult = checkWinner(board);
                if (winResult != 'N') // Verlasse Schleife wenn unentschieden oder gewonnen
                {
                    break;
                }
                position = choose_field(); //choose_field Eingabe des Spielers mit den Pfeiltasten
                validMove = setAndCheckMove(board, position, HUMAN); //Überprüft ob man eine valide Position angegeben hat und übersetzt die position
                loadboard(board); //Board neuladen
                winResult = checkWinner(board);

                if (winResult != 'N') // Verlasse Schleife wenn unentschieden oder gewonnen
                {
                    break;
                }
            }
            curs_set(0);
        }
        else if (mode == 4) // Spieler gegen Spieler
        {
            gamearena();
            while (1) // Loop Spieler gegen Spieler
            {
                mvprintw(getmaxy(stdscr) - 4, 0, "Es ist %c dran!", currentPlayer);
                curs_set(1);
                loadboard(board);
                position = choose_field();
                validMove = setAndCheckMove(board, position, currentPlayer);
                loadboard(board);
                refresh();
                // Mit dieser if wird immer der Spieler
                // nach gültigen Zug gewechselt
                if (currentPlayer == 'X' && validMove == 1)
                {
                    currentPlayer = 'O';
                }
                else if (currentPlayer == 'O' && validMove == 1)
                {
                    currentPlayer = 'X';
                }
                winResult = checkWinner(board);
                if (winResult != 'N')
                {
                    break;
                }
            }
            curs_set(0);
        }
        else if (mode == 5) // Farbeinstellungen
        {
            start_color_options();
        }

        if (winResult == 'X' || winResult == 'O') // Win Screen
        {
            mvprintw(getmaxy(stdscr) - 4, 0, "Es hat %c gewonnen!", winResult);
        }
        else
        {
            mvprintw(getmaxy(stdscr) - 4, 0, "Es hat niemand gewonnen!");
        }

        if (mode != 5) // End Screen ob man nochmal spielen möchte
        {
            mvprintw(getmaxy(stdscr) - 2, 0, "Wollen Sie zurueck zum Hauptmenue (y)?");
            nodelay(stdscr, FALSE);
            answer = getch();
            nodelay(stdscr, TRUE);
            if (answer != 'y')
            {
                break;
            }
            // Spiel wird resetet
            init_board(board);
            validMove = 1;
            currentPlayer = 'X';
            winResult = 'N';
        }
        erase();
    }
}

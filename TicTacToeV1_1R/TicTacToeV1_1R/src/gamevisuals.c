#include <pdcurses.h>
#include "gamevisuals.h"
#include "color.h"

// Funktion erstellt das Spielfeld anhand der höhe des Terminals
// Ein senkrechter Strich entspricht drei waagerechte Striche
void gamearena()
{
    int maxy = getmaxy(stdscr) - 5; // Maximale höhe des Spielfelds
    while (maxy % 3 != 0)
    {
        maxy--;
    }
    int maxyD3 = maxy / 3;

    for (int j = 0; j < maxy * 3; j++)
    {
        mvaddch(maxyD3, j, '-');
        mvaddch(maxyD3 * 2, j, '-');
    }

    for (int i = 0; i < maxy; i++)
    {
        mvaddch(i, maxy, '|');
        mvaddch(i, maxy * 2, '|');
    }

    mvaddch(0, maxy, ' ');
    mvaddch(0, maxy * 2, ' ');
    refresh();
}

// Funktion erstellt das X
void printx(int a, int b)
{
    int maxy = getmaxy(stdscr) - 5;
    while (maxy % 3 != 0)
    {
        maxy--;
    }
    int maxyD2 = maxy / 2;
    int maxyD3 = maxy / 3;
    int maxyD6 = maxy / 6;

    int y = maxyD6 + (maxyD3 * a);
    int x = maxyD2 + (maxy * b);

    for (int i = 0; i < maxyD3 / 2; i++) // Zählt bis höhe des Feldes erreicht
    {
        mvaddch((y - 1 * i), (x - 2 * i), 'X'); // Oben links
        mvaddch((y - 1 * i), (x + 2 * i), 'X'); // Oben rechts
        mvaddch((y + 1 * i), (x - 2 * i), 'X'); // Unten links
        mvaddch((y + 1 * i), (x + 2 * i), 'X'); // Unten rechts
    }
    refresh();
}

void printCircle(int xc, int yc, int x, int y)
{
    mvaddch(yc + y, xc + x, 'O');
    mvaddch(yc + y, xc - x, 'O');
    mvaddch(yc - y, xc + x, 'O');
    mvaddch(yc - y, xc - x, 'O');
    mvaddch(yc + x, xc + y, 'O');
    mvaddch(yc + x, xc - y, 'O');
    mvaddch(yc - x, xc + y, 'O');
    mvaddch(yc - x, xc - y, 'O');
}

// Funktion erstellt das O mittels Bresenham's Algorithmus
void printo(int a, int b)
{
    int maxy = getmaxy(stdscr) - 5;
    while (maxy % 3 != 0)
    {
        maxy--;
    }
    int maxyD3 = maxy / 3;
    int maxyD6 = maxy / 6;
    int r = maxyD6 - 1;           // Radius
    int xc = maxy / 2 + maxy * b; // Mitte eines Feldes auf der y-Achse
    int yc = maxyD6 + maxyD3 * a; // Mitte eines Feldes auf der x-Achse
    int x = 0;
    int y = r;
    int d = 3 - (2 * r);

    printCircle(xc, yc, x, y);

    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
        printCircle(xc, yc, x, y);
    }
    refresh();
}

// Funktion überprüft die Fenstergröße
int checkWindowSize()
{
    if (getmaxy(stdscr) >= 30 && (getmaxy(stdscr) - 5) * 3 <= getmaxx(stdscr)) // Benötigte Fenstergröße für das Programm
    {
        return 0;
    }
    else // Fehlermeldung
    {
        nodelay(stdscr, FALSE);
        erase();
        mvprintw(0, 0, "Programm passt nicht in die Fenstergroesse!");
        mvprintw(2, 0, "Weitere Informationen finden Sie in der readme.txt");
        mvprintw(4, 0, "Druecke eine Taste um das Programm zu schliessen.");
        refresh();
        getch();
        return 1;
    }
}

// Funktion ermöglicht das Auswählen der Felder mittels Pfeiltasten
int choose_field()
{
    int maxy = getmaxy(stdscr) - 5;
    while (maxy % 3 != 0)
    {
        maxy--;
    }
    int maxyD3 = maxy / 3;
    int maxyD6 = maxy / 6;

    int pressed_key;
    int x = maxy / 2;
    int y = maxyD6;
    int iy = 0;
    int ix = 0;
    move(y, x);
    while (1)
    {
        pressed_key = getch();
        switch (pressed_key)
        {
        case ERR:
            napms(10);
            break;
        case 258: // Pfeiltaste unten
            y = y + maxyD3;
            move(y, x);
            iy++;
            break;
        case 259: // Pfeiltaste oben
            y = y - maxyD3;
            move(y, x);
            iy--;
            break;
        case 260: // Pfeiltaste links
            x = x - maxy;
            move(y, x);
            ix--;
            break;
        case 261: // Pfeiltaste rechts
            x = x + maxy;
            move(y, x);
            ix++;
            break;
        case 10:
            if (ix == 0 && iy == 0)
                return 1;
            if (ix == 1 && iy == 0)
                return 2;
            if (ix == 2 && iy == 0)
                return 3;
            if (ix == 0 && iy == 1)
                return 4;
            if (ix == 1 && iy == 1)
                return 5;
            if (ix == 2 && iy == 1)
                return 6;
            if (ix == 0 && iy == 2)
                return 7;
            if (ix == 1 && iy == 2)
                return 8;
            if (ix == 2 && iy == 2)
                return 9;
            break;
        }
        // Pfeiltasten sind nur im Bereich des Spielfeldes nutzbar
        if (ix < 0)
        {
            ix = 2;
            x = maxy / 2 + maxy * ix;
            move(y, x);
        }
        if (ix > 2)
        {
            ix = 0;
            x = maxy / 2 + maxy * ix;
            move(y, x);
        }
        if (iy < 0)
        {
            iy = 2;
            y = maxyD6 + maxyD3 * iy;
            move(y, x);
        }
        if (iy > 2)
        {
            iy = 0;
            y = maxyD6 + maxyD3 * iy;
            move(y, x);
        }
        refresh();
    }
}

int startmenu()
{
    int row = 3; //Jetzige Reihe des Cursors
    int pressed_key; //Eingaben werden als int gespeichert
    char ausgabe = '>'; //Cursor Zeichen

    while (1)
    {
        pressed_key = getch(); //Eingabe des Nutzers abfragen (Wir suchen aber nur nach Pfeiltaste-Up und Pfeiltaste-Down oder Enter

        switch (pressed_key)
        {
        case 259:
            mvprintw(row, 5, "%c", ' '); //Feldleeren wo der Cursor vorher war
            row = row - 3;  //Position des Cursors 3 Zeilen nach oben verschieben
            break;
        case 258: 
            mvprintw(row, 5, "%c", ' ');  //Feldleeren wo der Cursor vorher war
            row = row + 3; //Position des Cursors 3 Zeilen nach unten verschieben
            mvprintw(row, 5, "%c", ' ');  //Feldleeren wo der Cursor vorher war
            break;
        case 10: //Enter
            if (row == 3)
            {
                return 1; //Easy
            }
            if (row == 6)
            {
                return 2; //Normal
            }
            if (row == 9)
            {
                return 3; //Hard
            }
            if (row == 12)
            {
                return 4; //2 Player
            }
            if (row == 15)
            {
                return 5; //Color Settings
            }
            break;
        }
        //Collisiondetection damit man nicht mit dem Cursor weiter geht als gedacht
        if (row < 3)
        {
            row = 15;
        }
        if (row > 15)
        {
            row = 3;
        }
        // ===== Ausgabe =====
        //Anzeigen der Gamemodes auf dem Bildschirm
        mvprintw(3, 10, "Einfach");
        mvprintw(6, 10, "Mittel");
        mvprintw(9, 10, "Schwer");
        mvprintw(12, 10, "2 Spieler");
        mvprintw(15, 10, "Farbeinstellungen");

        mvprintw(row, 5, "%c", ausgabe); //Cursor an Cursorposition anzeigen
        refresh(); //Console aktualsieren
    }
}
//Funktion zum aktualsieren des Spielfelds
void loadboard(char arr[3][3])
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (arr[x][y] == 'X')
            {
                if (get_color() != 1) // Wenn Rot nicht vergeben...
                    color_set(1, 0); // ...dann Rot...
                else
                    color_set(2, 0); // ...sonst Blau
                    printx(x, y);
            }
            if (arr[x][y] == 'O')
            {
                color_set(get_color(), 0); // Farbe von Datei
                printo(x, y);
            }
        }
    }
    color_set(7, 0); // Weiss
    refresh();
}
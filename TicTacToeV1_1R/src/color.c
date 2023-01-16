#include <stdio.h>
#include <pdcurses.h>
#include "color.h"

// Funktion um die Farbe, die in der Datei steht zu bekommen
int get_color()
{
    int num;
    FILE *fp;
    fp = fopen("settings_color.txt", "r"); // Öffne & Lese Datei
    if (fp == NULL)
    {
        erase();
        refresh();
        printf("Error! Kein Zugriffsrecht auf Datei!\n");
        printf("Farbe wird auf Blau gesetzt!");
        napms(2000);
        erase();
        refresh();
        return 7;
    }
    fseek(fp, 8, SEEK_SET); // Setze Position ab 8 vom Anfang
    fscanf(fp, "%d", &num); // Lese ab der Position die Zahl ein
    fclose(fp);             // Schließe Datei
    return num;
}

// Funktion zur Initialisierung der Farben
void init_colors()
{
    init_pair(1, COLOR_BLUE, COLOR_BLACK);    // Rot
    init_pair(2, COLOR_RED, COLOR_BLACK);     // Blau
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   // Grün
    init_pair(4, COLOR_CYAN, COLOR_BLACK);    // Gelb
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);  // Hell Blau
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK); // Pink
    init_pair(7, COLOR_WHITE, COLOR_BLACK);   // Weiss
}

// Funktion um die Möglichkeiten zu zeigen
void display_options()
{
    color_set(1, 0);
    mvprintw(3, 10, "Rot");

    color_set(2, 0);
    mvprintw(6, 10, "Blau");

    color_set(3, 0);
    mvprintw(9, 10, "Gruen");

    color_set(4, 0);
    mvprintw(12, 10, "Gelb");

    color_set(5, 0);
    mvprintw(15, 10, "Hellblau");

    color_set(6, 0);
    mvprintw(18, 10, "Pink");

    color_set(7, 0);
    mvprintw(21, 10, "Zurueck");

    char color = get_color(); // Farbe die in der Textdatei steht

    if (color == ' ') // Falls in der Datei statt der Farbzahl nichts steht
    {
        color_set(7, 0);
        mvprintw(25, 10, "Derzeitige Farbe: Spieler O");
    }
    else
    {
        color_set(7, 0);
        mvprintw(25, 10, "Derzeitige Farbe: ");
        color_set(color, 0);
        mvprintw(25, 28, "Spieler O");
        color_set(7, 0);
    }
    refresh();
}

// Funktion zur Auswahl der Farben
int color_menu()
{
    int pressed_key;
    int i = 3;
    mvprintw(i, 5, ">");
    while (1)
    {
        pressed_key = getch();
        switch (pressed_key)
        {
        case ERR:
            napms(10);
            break;
        case 258: // Pfeiltaste unten
            i = i + 3;
            mvprintw(i - 3, 5, " ");
            break;
        case 259: // Pfeiltaste oben
            i = i - 3;
            mvprintw(i + 3, 5, " ");
            break;
        case 10:
            if (i == 3)
                return 1; // Rot
            if (i == 6)
                return 2; // Blau
            if (i == 9)
                return 3; // Grün
            if (i == 12)
                return 4; //Gelb
            if (i == 15)
                return 5; //Hellblau
            if (i == 18)
                return 6; //Pink
            if (i == 21)
                return 7; //Zurück
            break;
        }
        // Wenn i außerhalb des Steuerungsbereich, dann auf de anderen Seite wieder gehen
        if (i < 3)
            i = 21;
        if (i > 21)
            i = 3;
        mvprintw(i, 5, ">");
        refresh();
    }
}

// Funktion um die Datei mit den Farbwerten zu erstellen
void settings_print(int colornum)
{
    FILE *fp;
    fp = fopen("settings_color.txt", "w"); // Schreiben/erstellen
    if (fp == NULL)
    {
        erase();
        refresh();
        printf("Error! Datei konnte nicht erstellt werden!");
        napms(2000);
        erase();
    }
    fprintf(fp, "color = %d", colornum);
    fclose(fp);
}

void start_color_options()
{
    erase();
    refresh();
    init_colors();
    display_options();
    int colornum = color_menu();                  // Ausgewählte Farbe von Programm
    if (colornum != get_color() && colornum != 7) // Überprüft, ob nicht dieselbe Farbe gewählt wurde, die schon in der Datei steht
    {
        settings_print(colornum);
    }
    erase();
    refresh();
}
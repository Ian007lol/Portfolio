// Wurm.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "random.h"
#include "gotoxy.h"
#include "wait.h"
#include <conio.h>
#include "clearscreen.h"

const int MAX_HOEHE = 30;
const int MAX_BREITE = 50;
const int zeichen_viereck = 219; // ausgefülltes Viereck
const int zeichen_blank = 32; // Blank (Leerzeichen)
const int zeichen_futter = 207; // ASCII-Code fuer die "Made"
const int MAX_LIFES = 3;
int lifes = MAX_LIFES;
int verkakt = 0;
char zeichen_stern = '*';


struct str_Level
{
	int breite;
	int hoehe;
	int anzahl_steine;
	int anzahl_futter;
	int speed;
	int LVL;
	int HUD_xposition;
	int HUD_yposition;
};


void setze_randomchar(int p_spielfeld[MAX_BREITE][MAX_HOEHE], int p_breite, int p_hoehe, int p_zeichen, int p_anzahl_zeichen)
{
	int random_x, random_y;
	int anzahl_zeichen_gesetzt = 0;

	do
	{
		random_x = getrandom_int(2, p_breite - 3);
		random_y = getrandom_int(2, p_hoehe - 3);

		if (p_spielfeld[random_x][random_y] == zeichen_blank)
		{
			p_spielfeld[random_x][random_y] = p_zeichen;
			anzahl_zeichen_gesetzt++;
		}

	} while (anzahl_zeichen_gesetzt < p_anzahl_zeichen);

}
void initialisiere_spielfeld(int p_spielfeld[MAX_BREITE][MAX_HOEHE], int p_breite, int p_hoehe)
{
	int i, j;

	// Belegung des Arrays spielfeld mit "Blank"
	for (i = 0; i < p_breite; i++)
	{
		for (j = 0; j < p_hoehe; j++)
		{
			p_spielfeld[i][j] = zeichen_blank;
		}
	}

	// 1.1 Rand oben / unten
	for (i = 0; i < p_breite; i++)
	{
		p_spielfeld[i][0] = zeichen_viereck;
		p_spielfeld[i][p_hoehe - 1] = zeichen_viereck;
	}

	// 1.2 Rand links / rechts
	for (i = 0; i < p_hoehe; i++)
	{
		p_spielfeld[0][i] = zeichen_viereck;
		p_spielfeld[p_breite - 1][i] = zeichen_viereck;
	}

} // Ende von UP initialisiere_spielfeld
void zeichne_spielfeld(int p_spielfeld[MAX_BREITE][MAX_HOEHE], int p_breite, int p_hoehe)
{
	int i, j;
	// Belegung des Arrays spielfeld
	for (i = 0; i < p_breite; i++)
	{
		for (j = 0; j < p_hoehe; j++)
		{
			gotoxy(i, j);
			printf("%c", p_spielfeld[i][j]);
		}
	}
}
void get_richtung(int & p_xpos_delta, int & p_ypos_delta)
{
	int key = ' ';
	if (_kbhit())
	{
		key = _getch();
		if (key == 0xE0) // Code 224 beim ersten Aufruf ==> Pfeiltaste wurde gedrückt
		{
			key = _getch(); // der zweite Aufruf gibt den eigentlichen Tastencode zurück
		}
	}

	switch (key)
	{
	case 'A':
	case 'a':
	case 75:
		p_xpos_delta = -1;
		p_ypos_delta = 0;
		break;
	case 'D':
	case 'd':
	case 77:
		p_xpos_delta = 1;
		p_ypos_delta = 0;
		break;
	case 'W':
	case 'w':
	case 72:
		p_xpos_delta = 0;
		p_ypos_delta = -1;
		break;
	case 'S':
	case 's':
	case 80:
		p_xpos_delta = 0;
		p_ypos_delta = 1;
		break;
	}

}
void initialisiere_wurm(char p_wurm[], int p_xpos[], int p_ypos[], int p_laenge_wurm)
{
	
	for (int i = 0; i <= p_laenge_wurm; i++)
	{
		p_xpos[i] = 1;
		p_ypos[i] = 1;
		p_wurm[i] = zeichen_stern;
		
	}
	p_wurm[p_laenge_wurm] = ' ';
	
}
void verlaengere_wurm(char p_wurm[], int & p_laenge_wurm)
{
	// Wurm wird laenger:
	p_wurm[p_laenge_wurm] = zeichen_stern;
	p_laenge_wurm++;
	p_wurm[p_laenge_wurm] = ' ';
}
void zeichne_wurm(char p_wurm[], int p_xpos[], int p_ypos[], int p_laenge_wurm)
{
	// Wurm-Array zeichnen
	for (int i = 0; i <= p_laenge_wurm; i++)
	{
		gotoxy(p_xpos[i], p_ypos[i]);
		printf("%c", p_wurm[i]);
	}
	
}
void bewege_wurm(int p_xpos_delta, int p_ypos_delta, char p_wurm[], int p_xpos[], int p_ypos[], int p_laenge_wurm)
{
	// Wurm-Array shiften
	
for (int i = p_laenge_wurm; i >= 1; i--)
	{
		p_xpos[i] = p_xpos[i - 1];
		p_ypos[i] = p_ypos[i - 1];
	}
	
	
	p_xpos[0] += p_xpos_delta;
	p_ypos[0] += p_ypos_delta;
}
void HUD(str_Level p_level, int p_anzahl_futter_gefressen)
{
	gotoxy(p_level.HUD_xposition, p_level.HUD_yposition - 10);
	printf("LEVEL %i", p_level.LVL);
	gotoxy(p_level.HUD_xposition, p_level.HUD_yposition - 9);
	printf("BASE SPEED: %i", p_level.speed);
	gotoxy(p_level.HUD_xposition, p_level.HUD_yposition - 8);
	printf("FOOD IN LVL: %i", p_level.anzahl_futter);
	gotoxy(p_level.HUD_xposition, p_level.HUD_yposition - 7);
	printf("YOU ATE %i PIECES OF FRUIT", p_anzahl_futter_gefressen);
	gotoxy(p_level.HUD_xposition, p_level.HUD_yposition - 6);
	printf("YOU HAVE %i LIFES LEFT", lifes);
	
}

void MainLevel( str_Level p_level )
{   int flg_kollission = false;

int anzahl_futter_gefressen = 0;
	do
	{
		anzahl_futter_gefressen = 0;
		flg_kollission = false;
		ClearScreen();
		const int laenge_wurm_max = 50;
		int laenge_wurm = 7;
		char wurm[laenge_wurm_max];
		int xpos[laenge_wurm_max];
		int ypos[laenge_wurm_max];
		
		int spielfeld[MAX_BREITE][MAX_HOEHE];
		



		

		initialisiere_spielfeld(spielfeld, p_level.breite, p_level.hoehe);

		// 2. Steine per Zufallsgenerator verteilen
		setze_randomchar(spielfeld, p_level.breite, p_level.hoehe, zeichen_viereck, p_level.anzahl_steine);

		// 3. "Futtersteine" per Zufallsgenerator verteilen
		setze_randomchar(spielfeld, p_level.breite, p_level.hoehe, zeichen_futter, p_level.anzahl_futter);

		zeichne_spielfeld(spielfeld, p_level.breite, p_level.hoehe);

		initialisiere_wurm(wurm, xpos, ypos, laenge_wurm);

		int xpos_delta = 0, ypos_delta = 0;
		xpos_delta = 0;
		ypos_delta = 0;

		
		do
		{
			HUD(p_level, anzahl_futter_gefressen);

			get_richtung(xpos_delta, ypos_delta);

			bewege_wurm(xpos_delta, ypos_delta, wurm, xpos, ypos, laenge_wurm);

			zeichne_wurm(wurm, xpos, ypos, laenge_wurm);

			//hier fängst du an, es ist unnötig aber ich will das machen
			


			if (spielfeld[xpos[0]][ypos[0]] == zeichen_viereck)
			{
				// Kollission!!
				flg_kollission = true;
			}

			if (spielfeld[xpos[0]][ypos[0]] == zeichen_futter)
			{
				spielfeld[xpos[0]][ypos[0]] = ' ';
				verlaengere_wurm(wurm, laenge_wurm);
				anzahl_futter_gefressen++;
			}
		
			
			// Cursor aufräumen
			gotoxy(0, 0);

			// Pruefen, ob Leertaste gedrueckt ist
			if ((GetKeyState(' ') & 0x8000) == 0x8000)
			{
				// TURBO
				wait_milliseconds(40);

			}
			else
			{
				wait_milliseconds(p_level.speed);
			}
			


		} while (flg_kollission == false && anzahl_futter_gefressen < p_level.anzahl_futter);

		gotoxy(0, p_level.hoehe + 2);

		if (flg_kollission)
		{
			verkakt++;
			lifes--;
		}


	} while (lifes > 0 && anzahl_futter_gefressen < p_level.anzahl_futter);
	

	
}

int main(void)
{
	
	str_Level level[5];

	level[0].anzahl_futter = 5;
	level[0].anzahl_steine = 5;
	level[0].breite = 50;
	level[0].hoehe = 30;
	level[0].speed = 200;
	level[0].LVL = 1;
	level[0].HUD_xposition = 51;
	level[0].HUD_yposition = 22;

	level[1].anzahl_futter = 7;
	level[1].anzahl_steine = 7;
	level[1].breite = 40;
	level[1].hoehe = 25;
	level[1].speed = 175;
	level[1].LVL = 2;
	level[1].HUD_xposition = 41;
	level[1].HUD_yposition = 20;

	level[2].anzahl_futter = 9;
	level[2].anzahl_steine = 9;
	level[2].breite = 30;
	level[2].hoehe = 20;
	level[2].speed = 150;
	level[2].LVL = 3;
	level[2].HUD_xposition = 31;
	level[2].HUD_yposition = 17;

	level[3].anzahl_futter = 11;
	level[3].anzahl_steine = 11;
	level[3].breite = 20;
	level[3].hoehe = 15;
	level[3].speed = 125;
	level[3].LVL = 4;
	level[3].HUD_xposition = 21;
	level[3].HUD_yposition = 15;

	level[4].anzahl_futter = 13;
	level[4].anzahl_steine = 13;
	level[4].breite = 20;
	level[4].hoehe = 15;
	level[4].speed = 100;
	level[4].LVL = 5;
	level[4].HUD_xposition = 21;
	level[4].HUD_yposition = 15;
	
	int i = 0;
	do
	{
		
		
		MainLevel(level[i]);

		i++;

	} while (lifes > 0 && i < 6);

	if (lifes == 0)
	{
		ClearScreen();
		gotoxy(15, 15);
		printf("GAME OVER");
	}
	else if( lifes > 0)
	{
		ClearScreen();
		gotoxy(15, 15);
		printf("YOU WIN");
	}
	gotoxy(0, 0);
	return(0);
}




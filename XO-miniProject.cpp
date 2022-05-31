#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

char name[2][101];
char g[3][3];
char nat;

void gotoxy(short x, short y)
{
	// change coordination of cursor
	COORD xy = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void game_display()
{
	// clear memory
	int i, j;
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			g[i][j] = 0;
		}
	}

	// board of game
	system("cls");
	srand(time(NULL));
	int p = rand() % 2;
	printf("Player X: %s\nPlayer O: %s\n", name[p], name[1 - p]);
	printf("_______\n| | | |\n|_|_|_|\n| | | |\n|_|_|_|\n| | | |\n|_|_|_|\n");
}

char game_win()
{
	// possibilities of win
	if (g[0][0] == g[0][1] && g[0][1] == g[0][2])
	{
		return g[0][0];
	}
	else if (g[1][0] == g[1][1] && g[1][1] == g[1][2])
	{
		return g[1][0];
	}
	else if (g[2][0] == g[2][1] && g[2][1] == g[2][2])
	{
		return g[2][0];
	}
	else if (g[0][0] == g[1][0] && g[1][0] == g[2][0])
	{
		return g[0][0];
	}
	else if (g[0][1] == g[1][1] && g[1][1] == g[2][1])
	{
		return g[0][1];
	}
	else if (g[0][2] == g[1][2] && g[1][2] == g[2][2])
	{
		return g[0][2];
	}
	else if (g[0][0] == g[1][1] && g[1][1] == g[2][2])
	{
		return g[0][0];
	}
	else if (g[0][2] == g[1][1] && g[1][1] == g[2][0])
	{
		return g[0][2];
	}
	else
	{
		return 0;
	}
}

void game_coord(int* n, int* m)
{
	int x, y;
	while (1)
	{
		char c = _getch();
		switch (c)
		{
		case -32:
			c = _getch();
			if (c == 77) //right
			{
				*n = *n;
				(*m)++;
				x = *m % 3 * 2 + 1;
				y = *n % 3 * 2 + 3;
				gotoxy(x, y);
				//return *m;
			}
			if (c == 72) //up
			{
				(*n)--;
				*m = *m;
				x = *m % 3 * 2 + 1;
				y = *n % 3 * 2 + 3;
				gotoxy(x, y);
				//return *n;
			}
			if (c == 80) //down
			{
				(*n)++;
				*m = *m;
				x = *m % 3 * 2 + 1;
				y = *n % 3 * 2 + 3;
				gotoxy(x, y);

				//return *n;
			}
			if (c == 75) //left
			{
				*n = *n;
				(*m)--;
				x = *m % 3 * 2 + 1;
				y = *n % 3 * 2 + 3;
				gotoxy(x, y);
				//return *m;
			}
			break;

		case 32:
			printf(""); //nobat kodom?
			//or goto game_check func
			return;
		}


	}

}

char game_check()
{
	//_getch();
	int turn = 1, to = 0, tx = 0, i = 0, j = 0;
	int x, y;


	while (1)
	{
		game_coord(&i, &j);
		//x = (j % 3) * 2 + 1;
		//y = (i % 3) * 2 + 3;
		//gotoxy(x, y);

		if (g[i % 3][j % 3] != 'X' && g[i % 3][j % 3] != 'O')
		{
			if (turn == 1 || turn == -1)  //its always correct
			{
				if (turn == 1)
				{

					g[i % 3][j % 3] = 'X';
					printf("X");
					tx++;
				}
				if (turn == -1)
				{
					g[i % 3][j % 3] = 'O';
					printf("O");
					to++;
				}
			}
			if (tx >= 3 || to >= 3)
			{
				if (game_win() != 0)
				{
					return game_win();
				}
				else if (game_win() == 0 && tx + to == 9)
				{
					return 'k';
				}
			}
		}
		turn *= -1;
	}
	return game_win();
}

int game_play()
{
	char ans[1001];
	while (1)
	{
		// display of game
		game_display();

		gotoxy(1, 3);

		char c = game_check();
		gotoxy(0, 13);
		if (c == 'k')
		{
			printf("\nThere is no winner!");
		}
		else if (c == 'X')
		{
			printf("\nPlayer X win!\n");
		}
		else if(c == 'O')
		{
			printf("\nPlayer O win!\n");
		}

		// check to play again
		printf("\nDo you want to play again? (yes / no / q)\n");
		while (1)
		{
			// as same as game start by little difference
			gets_s(ans);
			if (strcmp(ans, "q") == 0) { return 1; }
			else if (strcmp(ans, "yes") == 0) { break; }
			else if (strcmp(ans, "no") == 0) { return 0; }
			else
			{
				gotoxy(0, 13);
				printf("                                                  \r");
			}
		}
	}
}

int game_start()
{
	char ans[1001];
	while (1)
	{
		// enter name of players
		system("cls");
		printf("Enter names of players\n");
		printf("Player 1: ");
		gets_s(name[0]);
		printf("Player 2: ");
		gets_s(name[1]);
		// check for start game
		printf("Do you want to continue? (yes / no / q)\n");
		while (1)
		{
			gets_s(ans);
			// exit prog
			if (strcmp(ans, "q") == 0) { return 0; }
			// start prog
			else if (strcmp(ans, "yes") == 0) { return 1; }
			// input again
			else if (strcmp(ans, "no") == 0) { break; }
			else
			{
				gotoxy(0, 4);
				// delete last inputs
				printf("                                                  \r");
			}
		}
	}
}

int main()
{
	// start
	printf("Welcome to my GAME!\n");
	// stop to see message
	_getch();
	// program start
	while (1)
	{
		switch (game_start())
		{
		case 0:
			return 0; // finish prog
		case 1:
			if (game_play())
			{
				return 0; // finish prog
			}
		}
	}
}
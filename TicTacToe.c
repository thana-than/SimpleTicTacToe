// TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "cs50.h"

#define A1   coords[0][0]
#define A2   coords[1][0]
#define A3   coords[2][0]
#define B1   coords[0][1]
#define B2   coords[1][1]
#define B3   coords[2][1]
#define C1   coords[0][2]
#define C2   coords[1][2]
#define C3   coords[2][2]

//Programmed by Nathanael More
//Includes CS50.h header file for GetString() usage


//Controls are given by a 2 character alphanumeric code
/*
Grid Legend

X0 X1 X2
Y0 A1|A2|A3
Y1 B1|B2|B3
Y2 C1|C2|C3
*/

char coords[3][3]; //Used for checking and placing on grid
char wincoords[3][3]; //Used for showing winning line

int tempx, tempy, playercount, playerturn, compare, tally, hasmoved, threatwarning;
string input;

void draw(char playersymbol);
void lastdraw();
int turn();
int gamecheck();
int xcounter();
int tallycount(int x, int y, char symbol);
void cputurn();
int threatcheck();
int opportunitycheck();
int restart();

int restart()
{
	printf("Enter 'r' to restart, or hit enter to quit\n");
	//scanf_s("%s", input);
	input = GetString();

	compare = strcmp(input, "r");
	if (compare == 0)
		return 1;
	else
		return 0;
}

//GAME MANAGEMENT
//_______________

int main(void)
{
GAMESTART:
	srand(time(NULL)); //Sets randomizer to internal clock
	tempx = tempy = playercount = playerturn = hasmoved = threatwarning = 0; //Resets all potentially assigned variables back to zero

	for (int y = 0; y <3; y++) //Clears game board
	{
		for (int x = 0; x <3; x++)
		{
			coords[x][y] = '_';
			wincoords[x][y] = '_';
		}
	}

	printf("\n\n\n\n\n\nTIC TAC TOE\n\nBy Nathanael More\n\n1 for 1 Player\n2 for 2 Players\n\n\n\n\n\n\n");

START:
	//scanf_s("%d", playercount);
	playercount = GetInt();

	if (playercount < 1 || playercount > 2)
	{
		printf("\n\n\nERROR\n\nInvalid Input!\n\n1 for 1 Player\n2 for 2 Players\n\n\n\n\n");
		goto START;
	}

	playerturn = 1;

	//GAME LOOP

	while (1)
	{
		if (playerturn != 3) //CPU is referred to as 3 in the playerturn variable
		{
			if (turn() == 0) //If 'end' command is given during players turn, end the game
				return 0;
		}
		else
			cputurn();

		if (gamecheck() > 0) //If the game is won
		{
			lastdraw();
			if (restart() == 1)
				goto GAMESTART;
			else
				return 0;
		}

		if (playerturn == 4) //A tie game is referred to as 4 in the playerturn variable
		{
			lastdraw();
			if (restart() == 1)
				goto GAMESTART;
			else
				return 0;
		}

		if (playerturn > 1) //Switches turns between player 1 and 2, or player 1 and CPU
			playerturn = 1;
		else if (playercount == 2)
			playerturn = 2;
		else if (playercount == 1)
			playerturn = 3;

	}
}

//DRAW EVENTS

void draw(char playersymbol) //Straightforward grid draw function
{
	printf("\n\n\n\n\n   1 2 3\nA  %c|%c|%c\nB  %c|%c|%c\nC  %c|%c|%c\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPlayer %d's turn (%c):\n", A1, A2, A3, B1, B2, B3, C1, C2, C3, playerturn, playersymbol);
}

void lastdraw() //Draw's end of game results
{
	if (playerturn == 4)
		printf("\n\n\n\n\n   %c|%c|%c\n   %c|%c|%c\n   %c|%c|%c\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nTie game!\n", A1, A2, A3, B1, B2, B3, C1, C2, C3);
	else if (playerturn != 3)
		printf("\n\n\n\n   1 2 3\nA  %c|%c|%c\nB  %c|%c|%c\nC  %c|%c|%c\n\n\n\n   %c|%c|%c\n   %c|%c|%c\n   %c|%c|%c\n\n\n\n\n\n\n\n\nPlayer %d wins!\n", A1, A2, A3, B1, B2, B3, C1, C2, C3,
			wincoords[0][0], wincoords[1][0], wincoords[2][0], wincoords[0][1], wincoords[1][1], wincoords[2][1], wincoords[0][2], wincoords[1][2], wincoords[2][2], playerturn);
	else if (playerturn == 1)
		printf("\n\n\n\n   1 2 3\nA  %c|%c|%c\nB  %c|%c|%c\nC  %c|%c|%c\n\n\n\n   %c|%c|%c\n   %c|%c|%c\n   %c|%c|%c\n\n\n\n\n\n\n\n\nYou win!\n", A1, A2, A3, B1, B2, B3, C1, C2, C3,
			wincoords[0][0], wincoords[1][0], wincoords[2][0], wincoords[0][1], wincoords[1][1], wincoords[2][1], wincoords[0][2], wincoords[1][2], wincoords[2][2]);
	else
		printf("\n\n\n\n   1 2 3\nA  %c|%c|%c\nB  %c|%c|%c\nC  %c|%c|%c\n\n\n\n   %c|%c|%c\n   %c|%c|%c\n   %c|%c|%c\n\n\n\n\n\n\n\n\nYou lose!\n", A1, A2, A3, B1, B2, B3, C1, C2, C3,
			wincoords[0][0], wincoords[1][0], wincoords[2][0], wincoords[0][1], wincoords[1][1], wincoords[2][1], wincoords[0][2], wincoords[1][2], wincoords[2][2]);
}

//PLAYER TURN
//___________

int turn()
{
	if (playercount == 2 && playerturn == 2) //Assigns Player 1 to X and Player 2 to O
	{
		draw('O');
	}
	else
	{
		draw('X');
	}

RETRY:
	//scanf_s("%s", input);
	input = GetString(); //Receive input
	input[3] = '\0';

	compare = strcmp(input, "end"); //checks for end game input
	if (compare == 0)
		return 0;

	input[2] = '\0';

	//Controls are given by a 2 character alphanumeric code

	if (input[0] == 'a') //Converts alpha characters to CPU legible Y coordinate
		tempy = 0;
	else if (input[0] == 'b')
		tempy = 1;
	else if (input[0] == 'c')
		tempy = 2;
	else
	{
		printf("\nINVALID INPUT. Retry:");
		goto RETRY;
	}

	tempx = input[1] - 49; //Converts ASCII number to CPU legible X coordinate

	if (tempx > 2) //Checks for errors in input
	{
		printf("\nINVALID INPUT. Retry:");
		goto RETRY;
	}
	if (coords[tempx][tempy] != '_') //Checks to see if chosen space is clear
	{
		printf("\nSPOT TAKEN. Retry:");
		goto RETRY;
	}

	if (playercount == 2 && playerturn == 2) //Writes player mark in chosen space
	{
		coords[tempx][tempy] = 'O';
	}
	else
	{
		coords[tempx][tempy] = 'X';
	}
	return 1;
}

//CPU ARTIFICIAL INTELLIGENCE
//___________________________

int xcounter() //Counts how many moves in the game is. Only used to check for first turn
{
	int counter = 0;
	for (int y = 0; y <3; y++)
	{
		for (int x = 0; x <3; x++)
		{
			if (coords[x][y] == 'X')
				counter++;
		}
	}
	return counter;
}

//THREATCHECK FUNCTION

int threatcheck() //Checks for immediate threats and defends spaces
{
	int threatlvl = 0; //This variable tallys when the CPU counts the X's placed, if a true threat, the level will rise to 2

	threatwarning = 1; //Simple block that checks for game winning winning move to take instead of dealing will threat
	if (opportunitycheck() == 1)
		return 0;
	threatwarning = 0;

	if (hasmoved == 1) //If the opportunitycheck function manages to make a move, we don't want the threatcheck function to make a move within itself, this clarifies that a move has yet to be made this turn
		return 0;

	for (int y = 0; y <3; y++) //Checks for horizontal threats
	{
		for (int x = 0; x <3; x++)
		{
			if (coords[x][y] == 'X') //If it spots an X, tally up the threat level
				threatlvl++;
			else if (coords[x][y] == 'O') //If it finds an O (friendly) space, the threat level lowers to zero, as there is no way to get three in a row on this row
			{
				threatlvl = 0;
				break;
			}
			if (threatlvl > 1) //If the threat level rises high enough, clarify that there are no O's and place an O on the nearest open space to eliminate the threat
			{
				for (x = 0; x <3; x++)
				{
					if (coords[x][y] == '_')
					{
						coords[x][y] = 'O';
						hasmoved = 1;
						return 1;
					}
					else if (coords[x][y] == 'O')
					{
						threatlvl = 0;
						break;
					}
				}
			}
		}
		threatlvl = 0;
	}

	for (int x = 0; x <3; x++) //Checks for vertical threats
	{
		for (int y = 0; y <3; y++)
		{
			if (coords[x][y] == 'X')
				threatlvl++;
			else if (coords[x][y] == 'O')
			{
				threatlvl = 0;
				break;
			}
			if (threatlvl > 1)
			{
				for (y = 0; y <3; y++)
				{
					if (coords[x][y] == '_')
					{
						coords[x][y] = 'O';
						hasmoved = 1;
						return 1;
					}
					else if (coords[x][y] == 'O')
					{
						threatlvl = 0;
						break;
					}
				}
			}
		}
		threatlvl = 0;
	}

	for (int x = 0, y = 0; x<3; x++, y++) //Checks for backslash diagonal threats
	{
		if (coords[x][y] == 'X')
			threatlvl++;
		else if (coords[x][y] == 'O')
		{
			threatlvl = 0;
			break;
		}
		if (threatlvl > 1)
		{
			for (x = 0, y = 0; x<3; x++, y++)
			{
				if (coords[x][y] == '_')
				{
					coords[x][y] = 'O';
					hasmoved = 1;
					return 1;
				}
				else if (coords[x][y] == 'O')
				{
					threatlvl = 0;
					break;
				}
			}
		}
	}
	threatlvl = 0;

	for (int x = 0, y = 2; x<3; x++, y--) //Checks for forward slash diagonal threats
	{
		if (coords[x][y] == 'X')
			threatlvl++;
		else if (coords[x][y] == 'O')
		{
			threatlvl = 0;
			break;
		}
		if (threatlvl > 1)
		{
			for (x = 0, y = 2; x<3; x++, y--)
			{
				if (coords[x][y] == '_')
				{
					coords[x][y] = 'O';
					hasmoved = 1;
					return 1;
				}
				else if (coords[x][y] == 'O')
				{
					threatlvl = 0;
					break;
				}
			}
		}
	}
	threatlvl = 0;

	return 0;
}

//OPPORTUNITYCHECK FUNCTION

int opportunitycheck() //Similar to the threatcheck function, this function sees if there are any pivitol moves to make. 
{                      //The priority of this function depends on how immediate the threat of losing is. If there are more than one opportunity, the space is chosen at random.
	int r, opplvl, blankcount;
	int op[4];
	op[0] = 5;
NEWOPP:
	blankcount = opplvl = 0;

	if (hasmoved == 1)
		return 0;

	if (op[0] == 0 && op[1] == 1 && op[2] == 2 && op[3] == 3) //Checks to see if all random choices have been made already, and if so there are no special opportunities
		return 0;

	r = rand() % 4; //Pull a random number from 0-3

	if (r == op[0] || r == op[1] || r == op[2] || r == op[3]) //If random number has already been pulled in this loop, pull another number
		goto NEWOPP;

	op[r] = r;

	switch (r) //Switch statement for dealing with horizontal, vertical, and diagonal opportunities in a more randomized manner.
	{
	case 0: //Checks for horizontal opportunities
		for (int y = 0; y <3; y++)
		{
			for (int x = 0; x <3; x++)
			{
				if (coords[x][y] != 'X') //If there is no X in the row, raise the opportunity level and count all the blankspaces in the row
				{
					if (coords[x][y] == '_')
						blankcount++;
					opplvl++;
				}
				else
				{
					opplvl = 0;
					break;
				}
				if (opplvl > 2) //If an entire row is clear of X's
				{
					if (blankcount > 1 && threatwarning == 1) //Used when threatcheck calls this function, establishes priority to threatcheck (if in immediate danger of losing) unless the next move is a game winning move
					{
						opplvl = 0;
						blankcount = 0;
						break;
					}
					blankcount = 0;

					for (x = 0; x <3; x++) //Checks for closest free space in opportunity row and fills it
					{
						if (coords[x][y] == '_')
						{
							coords[x][y] = 'O';
							hasmoved = 1;
							return 1;
						}
						else if (coords[x][y] == 'X') //Clarifies there is no X in the row
						{
							opplvl = 0;
							break;
						}
					}
				}
			}
			opplvl = 0;
		}
		break;

	case 1: //Checks for vertical opportunities
		for (int x = 0; x <3; x++)
		{
			for (int y = 0; y <3; y++)
			{
				if (coords[x][y] != 'X')
				{
					if (coords[x][y] == '_')
						blankcount++;
					opplvl++;
				}
				else
				{
					opplvl = 0;
					break;
				}
				if (opplvl > 2)
				{
					if (blankcount > 1 && threatwarning == 1)
					{
						opplvl = 0;
						blankcount = 0;
						break;
					}
					blankcount = 0;

					for (y = 0; y <3; y++)
					{
						if (coords[x][y] == '_')
						{
							coords[x][y] = 'O';
							hasmoved = 1;
							return 1;
						}
						else if (coords[x][y] == 'X')
						{
							opplvl = 0;
							break;
						}
					}
				}
			}
			opplvl = 0;
		}
		break;

	case 2: //Checks for backslash diagonal opportunities
		for (int x = 0, y = 0; x<3; x++, y++)
		{
			if (coords[x][y] != 'X')
			{
				if (coords[x][y] == '_')
					blankcount++;
				opplvl++;
			}
			else
			{
				opplvl = 0;
				break;
			}
			if (opplvl > 2)
			{
				if (blankcount > 1 && threatwarning == 1)
				{
					opplvl = 0;
					blankcount = 0;
					break;
				}
				blankcount = 0;

				for (x = 0, y = 0; x<3; x++, y++)
				{
					if (coords[x][y] == '_')
					{
						coords[x][y] = 'O';
						hasmoved = 1;
						return 1;
					}
					else if (coords[x][y] == 'X')
					{
						opplvl = 0;
						break;
					}
				}
			}
		}
		opplvl = 0;
		break;

	case 3: //Checks for forward slash diagonal opportunities
		for (int y = 0, x = 0; y<3; y++, x++)
		{
			if (coords[x][y] != 'X')
			{
				if (coords[x][y] == '_')
					blankcount++;
				opplvl++;
			}
			else
			{
				opplvl = 0;
				break;
			}
			if (opplvl > 2)
			{
				if (blankcount > 1 && threatwarning == 1)
				{
					blankcount = 0;
					opplvl = 0;
					break;
				}
				blankcount = 0;

				for (y = 0, x = 0; y<3; y++, x++)
				{
					if (coords[x][y] == '_')
					{
						coords[x][y] = 'O';
						hasmoved = 1;
						return 1;
					}
					else if (coords[x][y] == 'X')
					{
						opplvl = 0;
						break;
					}
				}
			}
		}
		opplvl = 0;
		break;
	}
	goto NEWOPP;
	return 0;
}

//AI MANAGEMENT
void cputurn()
{
	int r, r2;
	hasmoved = 0;
	threatwarning = 0;

	if (xcounter() == 1) //Performs strategic first move. If player chooses the center, the CPU chooses a corner. If the player chooses a anywhere else, the CPU will whoose the center.
	{
		if (B2 == 'X')
		{
			r = rand() % 4;

			switch (r)
			{
			case 0:
				A1 = 'O';
				break;
			case 1:
				A3 = 'O';
				break;
			case 2:
				C1 = 'O';
				break;
			case 3:
				C3 = 'O';
				break;
			}
		}
		else
			B2 = 'O';
	}
	else if (threatcheck() != 1) //Checks for threats
	{
		if (hasmoved != 1)
		{
			if (opportunitycheck() != 1) //Checks for lesser priority opporunities
			{
				for (int y = 0; y <3; y++)
				{
					for (int x = 0; x <3; x++)
					{
						if (coords[x][y] == '_')
							break;
						else if (x == 2 && y == 2 && coords[x][y] != '_') //If there are no more free spaces, call a tie game
							playerturn = 4;
					}
				}

				if (playerturn != 4)
				{
				RANDOM: //Failsafe block: if for some reason there are no threats or opportunities, choose a random space. Probably mathematically impossible to come to this point.
					r = rand() % 3;
					r2 = rand() % 3;

					if (coords[r][r2] == '_')
					{
						coords[r][r2] = 'O';
					}
					else
						goto RANDOM;
				}
			}
		}
	}
}

//GAMECHECKING AND REFEREE
//________________________

int gamecheck()
{
	char sym_check; //Checks for the current players symbol, saves CPU power by only processing the last players actions

	if ((playercount == 2 && playerturn == 2) || (playercount == 1 && playerturn != 1))
		sym_check = 'O';
	else
		sym_check = 'X';

	for (int y = 0; y <3; y++) //Checks for a horizontal win
	{
		for (int x = 0; x <3; x++)
		{
			if (tallycount(x, y, sym_check) == playerturn) //Counts a tally, and if value returns true, announces winning player
				return playerturn;
		}
		tally = 0;
	}

	for (int x = 0; x <3; x++) //Checks for vertical win
	{
		for (int y = 0; y <3; y++)
		{
			if (tallycount(x, y, sym_check) == playerturn)
				return playerturn;
		}
		tally = 0;
	}

	for (int x = 0, y = 0; x<3; x++, y++) //Checks for backslash diagonal win
	{
		if (tallycount(x, y, sym_check) == playerturn)
			return playerturn;
	}
	tally = 0;

	for (int x = 0, y = 2; x<3; x++, y--) //Checks for forward slash diagonal win
	{
		if (tallycount(x, y, sym_check) == playerturn)
			return playerturn;
	}
	tally = 0;

	for (int y = 0; y <3; y++) //Clarifies that if the game isn't won, there are still moves to be made
	{
		for (int x = 0; x <3; x++)
		{
			if (coords[x][y] == '_')
				return 0;
		}
	}

	playerturn = 4; //If all spaces are filled and there is no winner, call a tie game
	return 0;
}


//TALLYCOUNT FUNCTION
int tallycount(int x, int y, char symbol) //Counts symbols that match in lines
{
	if (coords[x][y] == symbol)
	{
		tally++; //Counts up a symbol, and adds each winning symbol onto a temporary winning grid
		wincoords[x][y] = coords[x][y];
		if (tally == 3) //If there is a winner, return the player number
			return playerturn;
	}
	else
	{
		for (int y1 = 0; y1 <3; y1++) //If there is no winner yet, clear the temporary winning grid
		{
			for (int x1 = 0; x1 <3; x1++)
			{
				wincoords[x1][y1] = '_';
			}
		}
		tally = 0;
	}
	return 0;
}
#include <iostream>
#include <cstring>
#include <ctime>
#include "Header.h"
using namespace std;


void fill_field(char field[sn][sl]);
void place_ship(char field[sn][sl], int length);
void place_ship_all(char field[sn][sl]);
void place_ship_user(char field[sn][sl], int length);
void place_ship_user_all(char field[sn][sl]);
bool valid_place(char field[sn][sl]);
void print_field(char field[sn][sl]);
void print_field_hidden_ships(char field[sn][sl]);
void make_move_user(char field[sn][sl]);
void make_move_PC_easy(char field[sn][sl]);
void make_move_PC_hard(char field[sn][sl]);
bool ship_is_killed(char field[sn][sl]);
bool game_over(char field[sn][sl]);


int main()
{
	char field1[sn][sl];
	char field2[sn][sl];

	int choice;
	cout << "--Hello Player! Do you want to play a game?--" << endl;
	cout << "--Choose 1 for yes and 2 for no!--" << endl;
	cin >> choice;

	if (choice == 1)
	{
		cout << "--Allright, let's start!--" << endl;
		cout << "--Choose the mode of the game!--" << endl;
		cout << "1- play with a friend" << endl;
		cout << "2- play with PC" << endl;
		cin >> choice;

		if (choice == 1)
		{
			game_with_human(field1, field2);
		}
		else if (choice == 2)
		{
			game_with_PC(field1, field2);
		}
		else {
			cout << "--Invalid choice--" << endl;
		}
	}
	else if (choice == 2) {
		cout << "--Okay, goodbye!--" << endl;
		return 0;
	}
	else {
		cout << "--Invalid choice. Goodbye!--" << endl;
	}

	return 0;
}
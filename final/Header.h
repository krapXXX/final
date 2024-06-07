#pragma once
#include<iostream>
using namespace std;
#define sn SIDE_Numbers
#define sl SIDE_Letters


const int SIDE_Numbers = 11;
const int SIDE_Letters = 11;
const char EMPTY = '0';
const char SHIP = '1';
const char HIT = 'X';
const char MISS = '-';
const char KILL = 'K';
int number;
char letter_side;
int letter;
int level;
char direction;
int length;


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


void fill_field(char field[sn][sl])
{
	// Заповнюємо верхній рядок літерами і перший стовпець цифрами
	for (int i = 0; i < sl - 1; i++)
	{
		field[0][i + 1] = 'A' + i;  // Заповнюємо літерами
		field[i + 1][0] = '0' + i;  // Заповнюємо цифрами
	}
	field[0][0] = ' ';  // Верхній лівий кут порожній

	// Заповнюємо поле '0'
	for (int i = 1; i < sl; i++)
	{
		for (int j = 1; j < sn; j++)
		{
			field[i][j] = '0';  // Порожня клітинка позначається '0'
		}
	}
}
void place_ship(char field[sn][sl], int length) {
	bool placed = false;  // Flag indicating whether the ship has been placed

	while (placed == false) {
		// Randomly determine starting coordinates and direction
		letter = rand() % 10;  // Column
		number = rand() % 10;  // Row
		char direction = rand() % 2 == 0 ? 'H' : 'V';  // Direction: 'H' - horizontal, 'V' - vertical

		// Check if the ship can be placed
		if (valid_place(field) == true)
		{
			// Place the ship on the field
			for (int i = 0; i < length; ++i) {
				if (direction == 'H') {
					field[number][letter + i] = SHIP;  // Horizontal placement
				}
				else {
					field[number + i][letter] = SHIP;  // Vertical placement
				}
			}
			placed = true;  // Ship successfully placed
		}
		else
		{
			placed = false;
		}
	}
}
void place_ship_all(char field[sn][sl])
{
	place_ship(field, 4);
	for (int i = 0; i < 2; i++)
	{
		place_ship(field, 3);
	}
	for (int i = 0; i < 3; i++)
	{
		place_ship(field, 2);
	}
	for (int i = 0; i < 4; i++)
	{
		place_ship(field, 1);
	}
}
void place_ship_user(char field[sn][sl], int length)
{
	char direction;
	bool placed = false;  // Прапорець, що вказує, чи було розміщено корабель

	while (!placed) {
		// Отримання початкових координат та напрямку від користувача
		cout << "Enter the starting position for a " << length << "box ship: ";
		cin >> letter_side >> number;
		cout << "Enter direction (H for horizontal, V for vertical): ";
		cin >> direction;

		// Перетворення літери на індекс
		for (int i = 0; i < sn; i++)
		{
			if (letter_side == field[0][i])
			{
				letter = i;
			}
		}
		number += 1;  // Збільшуємо номер, щоб узгодити з індексацією масиву

		// Перевірка коректності введених даних
		if (letter >= 0 && letter < sl && number >= 0 && number < sn && (direction == 'H' || direction == 'V'))
		{
			// Перевірка можливості розміщення корабля
			if (valid_place(field))
			{
				// Розміщення корабля
				if (direction == 'H')
				{
					for (int i = 0; i < length; i++)
					{
						field[number][letter + i] = SHIP;  // Горизонтальне розміщення
					}
				}
				else
				{
					for (int i = 0; i < length; i++)
					{
						field[number + i][letter] = SHIP;  // Вертикальне розміщення
					}
				}
				placed = true;  // Корабель успішно розміщено
				print_field(field);  // Виведення поля на екран
			}
			else
			{
				cout << "Invalid placement. Try again." << endl;
			}
		}
		else
		{
			cout << "Invalid input. Try again." << endl;
		}
	}
}
void place_ship_user_all(char field[sn][sl])
{

	place_ship_user(field, 4);
	/*for (int i = 0; i < 2; i++)
	{
	  place_ship_user(field, 3);
	}
	for (int i = 0; i < 3; i++)
	{
	  place_ship_user(field, 2);
	}
	for (int i = 0; i < 4; i++)
	{
	  place_ship_user(field, 1);
	}*/
}
bool valid_place(char field[sn][sl])
{
	if (letter == 0 || number == 0) {
		return false;  // Check if the position is valid
	}

	// Check if the ship fits within the grid boundaries
	if (direction == 'H') {
		if (letter + length > sl) return false;  // Horizontal placement out of bounds
		if (number < 1 || number > sn) return false;  // Vertical placement out of bounds
	}
	else if (direction == 'V') {
		if (number + length > sn) return false;  // Vertical placement out of bounds
		if (letter < 1 || letter > sl) return false;  // Horizontal placement out of bounds
	}

	// Check surrounding cells for adjacent ships
	for (int i = max(1, number - 1); i <= min(sn, number + (direction == 'V' ? length : 1)); ++i) {
		for (int j = max(1, letter - 1); j <= min(sl, letter + (direction == 'H' ? length : 1)); ++j) {
			if (field[i][j] == SHIP) {
				return false;  // Adjacent ship found
			}
		}
	}

	return true;
}
void print_field(char field[sn][sl])
{
	// Виведення ігрового поля на екран
	for (int i = 0; i < sn; i++)
	{
		for (int j = 0; j < sl; j++)
		{
			cout << field[i][j] << " ";
		}
		cout << endl;
	}
}
void print_field_hidden_ships(char field[sn][sl])
{
	for (int i = 0; i < sn; i++)
	{
		for (int j = 0; j < sl; j++)
		{
			if (field[i][j] == SHIP)
			{
				cout << "0" << " ";
			}
			else
			{
				cout << field[i][j] << " ";
			}
		}
		cout << endl;
	}
}
void make_move_user(char field[sn][sl])
{
	bool fire = true;

	while (fire) {
		cout << "Choose a box to fire: ";
		cin >> letter_side >> number;

		// Перетворення літери на індекс
		for (int i = 0; i < sn; i++)
		{
			if (letter_side == field[0][i])
			{
				letter = i;
			}
		}
		number += 1;  // Збільшуємо номер, щоб узгодити з індексацією масиву

		// Перевірка коректності введених даних
		if (letter >= 0 && letter < sl && number >= 0 && number < sn)
		{
			if (field[number][letter] == SHIP)
			{
				cout << "Hit!" << endl;
				field[number][letter] = HIT;
				ship_is_killed(field);
			}
			else
			{
				cout << "Miss!" << endl;
				field[number][letter] = MISS;
				fire = false;  // Завершуємо хід
			}
		}
		else
		{
			cout << "Invalid coordinates. Try again." << endl;
		}
	}
	print_field_hidden_ships(field);

}
void make_move_PC_easy(char field[sn][sl])
{
	bool fire = true;
	while (fire)
	{
		// Випадковий вибір координат
		letter = rand() % (sl - 1) + 1;
		number = rand() % (sn - 1) + 1;
		// Перевірка, чи не були ці координати вже використані
		if (field[number][letter] != HIT && field[number][letter] != MISS)
		{
			if (field[number][letter] == SHIP)
			{
				cout << "Hit!" << endl;
				field[number][letter] = HIT;
			}
			else
			{
				cout << "Miss!" << endl;
				field[number][letter] = MISS;
				fire = false;  // Завершуємо хід
			}
		}
	}
	print_field(field);
	ship_is_killed(field);
	game_over(field);

}
void make_move_PC_hard(char field[sn][sl])
{
	static bool new_move = true;
	static int hit_number = -1, hit_letter = -1;
	static int direction = -1;

	bool fire = true;

	while (fire)
	{
		int number, letter;

		if (new_move)
		{
			// Choose random coordinates
			letter = rand() % (sl - 1) + 1;
			number = rand() % (sn - 1) + 1;

			if (number >= 1 && number < sn && letter >= 1 && letter < sl && field[number][letter] != HIT && field[number][letter] != MISS)
			{
				if (field[number][letter] == SHIP)
				{
					cout << "Hit!" << endl;
					field[number][letter] = HIT;
					hit_number = number;
					hit_letter = letter;
					new_move = false;
					direction = rand() % 4; // Choose initial direction
				}
				else if (field[number][letter] == EMPTY)
				{
					cout << "Miss!" << endl;
					field[number][letter] = MISS;
					fire = false;  // End the turn
				}
			}
		}
		else
		{
			// Continue targeting the same ship
			if (direction == 0)
			{
				number = hit_number - 1;
				letter = hit_letter;
			}
			else if (direction == 1)
			{
				number = hit_number + 1;
				letter = hit_letter;
			}
			else if (direction == 2)
			{
				number = hit_number;
				letter = hit_letter - 1;
			}
			else
			{
				number = hit_number;
				letter = hit_letter + 1;
			}

			// Check if the coordinates are within the grid boundaries and not already hit or missed
			if (number >= 1 && number < sn && letter >= 1 && letter < sl && field[number][letter] != HIT && field[number][letter] != MISS)
			{
				if (field[number][letter] == SHIP)
				{
					cout << "Hit!" << endl;
					field[number][letter] = HIT;

					// Update hit coordinates
					hit_number = number;
					hit_letter = letter;

					// Check if the ship is sunk
					if (ship_is_killed(field))
					{
						new_move = true;
						hit_number = -1;
						hit_letter = -1;
						direction = -1;
					}
				}
				else if (field[number][letter] == EMPTY)
				{
					cout << "Miss!" << endl;
					field[number][letter] = MISS;
					direction = (direction + 1) % 4; // Try next direction
				}
			}
			else
			{
				direction = (direction + 1) % 4; // Try next direction if the current one is invalid
			}
		}

		if (new_move)
		{
			fire = false; // End the turn if a new random move is needed
		}
	}
	ship_is_killed(field);
	game_over(field);
	print_field(field);

}
bool ship_is_killed(char field[sn][sl])
{
	for (int i = 1; i < sn; i++)
	{
		for (int j = 1; j < sl; j++)
		{
			if (field[i][j] == HIT)
			{
				bool ship_killed = true;

				// Check horizontally to the right
				for (int col = j; col < sl && field[i][col] == HIT; col++)
				{
					if (col + 1 < sl && field[i][col + 1] == SHIP)
					{
						ship_killed = false;
						break;
					}
				}

				// Check horizontally to the left
				for (int col = j; col >= 0 && field[i][col] == HIT; col--)
				{
					if (col - 1 >= 0 && field[i][col - 1] == SHIP)
					{
						ship_killed = false;
						break;
					}
				}

				// Check vertically downwards
				for (int row = i; row < sn && field[row][j] == HIT; row++)
				{
					if (row + 1 < sn && field[row + 1][j] == SHIP)
					{
						ship_killed = false;
						break;
					}
				}

				// Check vertically upwards
				for (int row = i; row >= 0 && field[row][j] == HIT; row--)
				{
					if (row - 1 >= 0 && field[row - 1][j] == SHIP)
					{
						ship_killed = false;
						break;
					}
				}

				// If the ship is killed, mark it as such
				if (ship_killed)
				{
					cout << "You killed a ship!" << endl;

					// Mark horizontally to the right
					for (int col = j; col < sl && field[i][col] == HIT; col++)
					{
						field[i][col] = KILL;
					}

					// Mark horizontally to the left
					for (int col = j; col >= 0 && field[i][col] == HIT; col--)
					{
						field[i][col] = KILL;
					}

					// Mark vertically downwards
					for (int row = i; row < sn && field[row][j] == HIT; row++)
					{
						field[row][j] = KILL;
					}

					// Mark vertically upwards
					for (int row = i; row >= 0 && field[row][j] == HIT; row--)
					{
						field[row][j] = KILL;
					}
					return true;
				}
				game_over(field);
			}
		}
	}
	return false;
}
bool game_over(char field[sn][sl])
{
	int counter = 0;
	for (int i = 0; i < sn; i++)

	{
		for (int j = 0; j < sl; j++)
		{
			if (field[i][j] == 1)
			{
				counter++;
			}
		}
	}
	if (counter == 0)
	{
		cout << endl << "Game is over. Player on the " << field << " won!";
		return true;
	}
	return false;

}
void game_with_human(char field1[sn][sl], char field2[sn][sl])
{
	fill_field(field1);
	fill_field(field2);
	int choice;
	// Player one places ships
	cout << "--Player 1, press 1 if you wanna place your ships and 2 if you want the PC to do it--" << endl;
	cin >> choice;

	if (choice == 1)
	{
		cout << "--Player 1, place your ships--" << endl;
		place_ship_user_all(field1);  // Example call to place a 3-box ship
	}
	else if (choice == 2)
	{
		cout << "--Player 1, let the PC do it--" << endl;
		place_ship_all(field1);
		// Call a function to let PC place ships
	}
	else
	{
		cout << "--Invalid choice--" << endl;
	}

	// Player two places ships
	cout << "--Player 2, press 1 if you wanna place your ships and 2 if you want the PC to do it--" << endl;
	cin >> choice;
	if (choice == 1)
	{
		cout << "--Player 2, place your ships--" << endl;
		place_ship_user_all(field2);  // Example call to place a 3-box ship
	}
	else if (choice == 2)
	{
		cout << "--Player 2, let the PC do it--" << endl;
		place_ship_all(field2);
		// Call a function to let PC place ships
	}
	else
	{
		cout << "--Invalid choice--" << endl;
	}

	// Start the game loop
	do {
		// Player one makes a move
		cout << "--Player 1, make your move--" << endl;
		make_move_user(field2);


		// Player two makes a move
		cout << "--Player 2, make your move--" << endl;
		make_move_user(field1);
		// Call a function for player two's move

		// Check if the game is over
		// If not, continue the loop
	} while (!game_over(field1) && !game_over(field2));
}
void game_with_PC(char field1[sn][sl], char field2[sn][sl])
{
	fill_field(field1);
	fill_field(field2);
	int choice;
	cout << "--Press 1 if you wanna place your ships and 2 if you want the PC to do it--" << endl;
	cin >> choice;

	if (choice == 1)
	{
		cout << "--Player, place your ships--" << endl;
		place_ship_user_all(field1);  // Example call to place a 3-box ship
	}
	else if (choice == 2)
	{
		cout << "--Player, let the PC do it--" << endl;
		place_ship_all(field1);
		// Call a function to let PC place ships
	}
	else
	{
		cout << "--Invalid choice--" << endl;
	}


	// Let the PC place ships for player two
	cout << "--Computer has filled its field--" << endl;
	place_ship_all(field2);
	// Call a function to let PC place ships for player two

	// Determine the level of difficulty
	cout << "--Player, what level of difficulty do you want to play?--" << endl;
	cout << "--1-dumb PC--" << endl;
	cout << "--2-smart PC--" << endl;
	cin >> choice;

	if (choice == 1) {
		// Dumb PC logic
		// Start the game loop
		do {
			// Player makes a move
			cout << "--Player, make your move--" << endl;
			// Call a function for player's move
			make_move_user(field2);
			// PC makes a move
			cout << "--PC, making its move--" << endl;
			// Call a function for PC's move
			make_move_PC_easy(field1);
			// Check if the game is over
			// If not, continue the loop
		} while (!game_over(field1) && !game_over(field2));
	}
	else if (choice == 2)
	{
		// Smart PC logic
		// Start the game loop
		do {
			// Player makes a move
			cout << "--Player, make your move--" << endl;
			make_move_user(field2);
			// Call a function for player's move

			// PC makes a move
			cout << "--PC, making its move--" << endl;
			make_move_PC_hard(field1);
			// Call a function for PC's move

			// Check if the game is over
			// If not, continue the loop
		} while (!game_over(field1) && !game_over(field2));
	}
	else {
		cout << "--Invalid choice--" << endl;
	}
}
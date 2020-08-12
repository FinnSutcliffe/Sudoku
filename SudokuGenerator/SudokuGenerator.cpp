// SudokuGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <array>

//std::array<std::array<int, 9>, 9> grid = { 0 };
//std::array<std::array<int, 9>, 9> backup_grid = { 0 };

int grid[9][9]{ 0 };
int backup_grid[9][9]{ 0 };

int g_sln_count = 0;


void print_grid(int grid[9][9])								// Prints a 9x9 grid
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (grid[i][j] == 0) {
				std::cout << " " << " ";
			}
			else {
				std::cout << grid[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*bool contains_val(std::array<int,9> & list, int val)						// Checks if a 9-length list contains a val
{

	std::find(list.begin(), list.end(), val)

	for (int i = 0; i < 9; i++)
	{
		if (list[i] == val)
			return true;
	}
	return false;
}*/

bool contains_val(int list[9], int val)						// Checks if a 9-length list contains a val
{
	for (int i = 0; i < 9; i++)
	{
		if (list[i] == val)
			return true;
	}
	return false;
}


int find_number_of_solutions()
{
	for (int i = 0; i < 81; i++)							// Looks for the next blank (0) (loop terminates after that (eventually))
	{
		int row = floor(i / 9);
		int col = i % 9;
		if (grid[row][col] == 0)							// Check if the square is empty, and so needs filling
		{
			for (int val = 1; val < 10; val++)				// Check through the numbers 1-9 to see if they fit
			{
				if (contains_val(grid[row], val))			// Check if row already contains that value
				{
					//std::cout << "\nROW CONTAINS " << val << "\n";
					continue;
				}

				int column[9]{};
				for (int j = 0; j < 9; j++)					// Generate column as a list
				{
					column[j] = grid[j][col];
				}
				if (contains_val(column, val))				// Check if column already contains that value
				{
					//std::cout << "\nCOLUMN CONTAINS " << val << "\n";
					continue;
				}

				for (int j = 0; j < 3; j++)					// Generate list of values in the 3x3 section
				{
					for (int k = 0; k < 3; k++)
					{
						column[j * 3 + k] = grid[(int(floor(row / 3)) * 3) + j][(int(floor(col / 3)) * 3) + k];
					}
				}
				if (contains_val(column, val))
				{
					//std::cout << "3x3 CONTAINS " << val << "\n";
					continue;
				}
				grid[row][col] = val;						// This configuration seems to works so far
				//print_grid(grid);
				int next = find_number_of_solutions();					// Move on to next square
				if (next == 0)								// No solutions for next square with this arrangement
				{
					grid[row][col] = 0;
					continue;								// Try a different number
				}
				else										// Solution found, cascading out
				{
					return 1;
				}
			}
			return 0;										// If it has made it here, no solutions for this arrangement
		}
	}
	g_sln_count++;											// Solution found! (dont tell anyone)
	return 0;
}


int solve_grid_randomly()
{
	std::vector<int> options = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (int i = 0; i < 81; i++)							// Looks for the next blank (0) (loop terminates after that (eventually))
	{
		int row = floor(i / 9);
		int col = i % 9;
		if (grid[row][col] == 0)							// Check if the square is empty, and so needs filling
		{
			std::random_shuffle(options.begin(), options.end());  // Randomises the order in which it will test values - to produce more interesting sudokus (not just 1 2 3 4...)
			for (int val = 0; val < 9; val++)				// Check through the numbers 1-9 to see if they fit
			{
				if (contains_val(grid[row], options[val]))			// Check if row already contains that value
				{
					//std::cout << "\nROW CONTAINS " << val << "\n";
					continue;
				}

				int column[9]{};
				for (int j = 0; j < 9; j++)					// Generate column as a list
				{
					column[j] = grid[j][col];
				}
				if (contains_val(column, options[val]))				// Check if column already contains that value
				{
					//std::cout << "\nCOLUMN CONTAINS " << val << "\n";
					continue;
				}

				for (int j = 0; j < 3; j++)					// Generate list of values in the 3x3 section
				{
					for (int k = 0; k < 3; k++)
					{
						column[j * 3 + k] = grid[(int(floor(row / 3)) * 3) + j][(int(floor(col / 3)) * 3) + k];
					}
				}
				if (contains_val(column, options[val]))
				{
					//std::cout << "3x3 CONTAINS " << val << "\n";
					continue;
				}
				grid[row][col] = options[val];						// This configuration seems to works so far
				//print_grid(grid);
				int next = solve_grid_randomly();			// Move on to next square
				if (next == 0)								// No solutions for next square with this arrangement
				{
					grid[row][col] = 0;
					continue;								// Try a different number
				}
				else										// Solution found, cascading out
				{
					return 1;
				}
			}
			return 0;										// If it has made it here, no solutions for this arrangement
		}
	}
	return 1;												// Grid is already filled (initially or at top of recursion)
}


void seed_grid() {											// Sets a random element to a random number between 1 and 9 inc.
	grid[rand() % 9][rand() % 9] = (rand() % 9) + 1;
}


void set_grid(int template_grid[9][9], int target_grid[9][9]) {  // Copies one 9x9 grid to another
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			target_grid[x][y] = template_grid[x][y];
		}
	}
}


void remove_elements(int to_attempt) {						// Set one non-zero element in the grid to zero
	int attempts = 0;
	while (attempts < to_attempt) {
		int row = rand() % 9;
		int col = rand() % 9;
		int val = grid[row][col];
		if (val == 0) { continue; }							// If element to be selected was a 0 already, try again
		grid[row][col] = 0;
		set_grid(grid, backup_grid);
		find_number_of_solutions();							// Test sudoku having removed 1 element - fills out grid array
		set_grid(backup_grid, grid);						// Revert grid to normal state
		if (g_sln_count != 1) {								// If it no longer can be solved/has a unique soln then revert val to initial
//			g_sln_count = 0;								// Reset global val
			grid[row][col] = val;
		}
		g_sln_count = 0;								// Reset global val
		attempts++;
	}
}


int test() {
	return 1, 2, 3;
}


int main()
{
	srand(time(NULL));										// Set rand seed to current time to give different pseudorandom sequence every run
															
	seed_grid();											// Create seed grid with 1 non-zero element
	solve_grid_randomly();									// Create solved grid with a bit more pizzazz than regular
	remove_elements(50);
	print_grid(grid);

	return 0;
}
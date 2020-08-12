#include <iostream>

void print_grid(int grid[9][9])								// Prints a 9x9 grid
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << grid[i][j] << " ";
		}
		std::cout << "\n";
	}
}

bool contains_val(int list[9], int val)						// Checks if a 9-length list contains a val
{
	for (int i = 0; i < 9; i++)
	{
		if (list[i] == val)
			return true;
	}
	return false;
}

int grid[9][9]{ {8,0,2,7,0,0,4,0,0},
				{0,1,0,0,0,9,0,0,5},
				{0,4,0,0,8,0,2,0,0},
				{0,0,0,0,5,0,9,2,0},
				{0,0,0,8,0,7,0,0,6},
				{7,0,9,0,6,0,0,5,0},
				{0,0,3,0,0,5,7,0,9},
				{6,0,0,0,1,0,3,0,0},
				{4,0,0,2,0,0,0,0,8} };

int solve_grid()
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
				int next = solve_grid();					// Move on to next square
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
	return 1;												// Grid has been filled
}


int main()
{
	print_grid(grid);
	std::cout << "\n\n";
	solve_grid();
	print_grid(grid);
	return 0;
}

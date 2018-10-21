#include "Heuristic.hpp"

#include <random>
#include <cassert>

int     Heuristic::GetSnailFieldIndex(int *grid, int number_to_find, size_t size)
{
    for (size_t i = 0; i < size * size; i++)
        if (grid[i] == number_to_find)
            return (i);
    return (-1);
}

int Heuristic::Manhattan(int *field, size_t size)
{
	size_t 	heuristic;
	int 	*snail_grid;
	int 	*snail_grid_default;

	heuristic = 0;
	snail_grid = Field::CreateSnailGrid(field, size);
	snail_grid_default = Field::CreateSnailGrid(nullptr, size);
	for (size_t i = 0; i < size * size; i++)
	{

		int index = GetSnailFieldIndex(snail_grid_default, field[i], size);

		/*		
		std::cout << "\n--------------------------------------------------\n";
		std::cout << "Current elemet to view: " << field[i] << std::endl;
		std::cout << "i = " << i / size << " | j = " << i % size << std::endl;
		std::cout << "Where elemet " << field[i] << " needs to go" << std::endl;
		std::cout << "Index = " << index << std::endl;
		std::cout << "i = " << index / size << " | j = " << index % size << std::endl;
		std::cout << "\n--------------------------------------------------\n";
		int index = GetSnailFieldIndex(snail_grid, field[i], size);
		std::cout << "i = " << i / size << " | j = " << i % size << std::endl;
		*/

		if (field[i] != 0) 
		{
			heuristic += std::abs(static_cast<int>(index / size) - static_cast<int>(i / size));
			heuristic += std::abs(static_cast<int>(index % size) - static_cast<int>(i % size));
		}
	}
	delete[] snail_grid;
	delete[] snail_grid_default;
	return (heuristic);
}

int Heuristic::LinearConflictManhattanDistance(int *field, size_t size)
{
	size_t 	heuristic;
	size_t	linear_conflicts;
	int 	*snail_grid;
	int 	*snail_grid_default;

	heuristic = 0;
	linear_conflicts = 0;
	snail_grid = Field::CreateSnailGrid(field, size);
	snail_grid_default = Field::CreateSnailGrid(nullptr, size);

	heuristic = Manhattan(field, size);

	// std::cout << "Manhattan value: " << heuristic << std::endl;

	// Field::Print(field, size);
	// std::cout << std::endl;
	// Field::Print(snail_grid_default, size);
	// std::cout << std::endl;

	for (size_t i = 0; i < size * size; i++)
	{
		int row_1 = i / size;
		int col_1 = i % size;
		
		for (size_t k = i + 1; k < size * size; k++)
		{
			int row_2 = k / size;
			int col_2 = k % size;
			
			if ((row_1 == row_2 || col_1 == col_2) && (field[i] && field[k]))
			{
				int snail_index_1 = GetSnailFieldIndex(snail_grid_default, field[i], size);
				int snail_index_2 = GetSnailFieldIndex(snail_grid_default, field[k], size);
				int res_row_1 = snail_index_1 / size;
				int res_col_1 = snail_index_1 % size;
				int res_row_2 = snail_index_2 / size;
				int res_col_2 = snail_index_2 % size;
				if ((res_row_1 == res_row_2 || res_col_1 == res_col_2) && (snail_index_2 < snail_index_1))
				{

					// std::cout << "-------------------------------------------\n";
					// std::cout << "Element initial    : " << field[i] << " | row = " << row_1 << " | col = " << col_1 << " | res_row = " << res_row_1 << " | res_col = " << res_col_1 << std::endl;
					// std::cout << "Element to compare : " << field[k] << " | row = " << row_2 << " | col = " << col_2 << " | res_row = " << res_row_2 << " | res_col = " << res_col_2 << std::endl;
					// std::cout << "-------------------------------------------\n";
					linear_conflicts++;
				}
			}
		}
	}
	delete[] snail_grid;
	delete[] snail_grid_default;
	return (heuristic + 2 * linear_conflicts);
}
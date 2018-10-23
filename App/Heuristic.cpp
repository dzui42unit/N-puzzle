#include "Heuristic.hpp"

#include <random>
#include <cassert>
#include <algorithm>

int     Heuristic::GetSnailFieldIndex(int *grid, int number_to_find, size_t size)
{
    for (size_t i = 0; i < size * size; i++)
        if (grid[i] == number_to_find)
            return (i);
    return (-1);
}

int Heuristic::EuclideanDistance(int *field, size_t size)
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
		if (field[i] != 0) 
		{
			int dx = std::abs(static_cast<int>(index / size) - static_cast<int>(i / size));
			int dy = std::abs(static_cast<int>(index % size) - static_cast<int>(i % size));
			heuristic += (dx * dx + dy * dy);
		}
	}
	delete[] snail_grid;
	delete[] snail_grid_default;
	return (heuristic);
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
					linear_conflicts++;
			}
		}
	}
	delete[] snail_grid;
	delete[] snail_grid_default;
	return (heuristic + 2 * linear_conflicts);
}
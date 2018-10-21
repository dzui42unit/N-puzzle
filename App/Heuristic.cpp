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
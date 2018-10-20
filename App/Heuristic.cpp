#include "Heuristic.hpp"

#include <random>
#include <cassert>

int Heuristic::Manhattan(int *field, size_t size)
{
	size_t heuristic;

	heuristic = 0;

	// std::cout << "Hello from Heuristic function Manhattan" << std::endl;

	// int *snail_grid;

	// snail_grid = Field::CreateSnailGrid(field, )
	for (size_t i = 0; i < size * size; i++)
	{
		// std::cout << "i = " << i / size << " | j = " << i % size << std::endl;
		if (static_cast<int>(i) != (field[i] - 1) && field[i] != 0) {
			heuristic += std::abs(static_cast<int>(i / size) - static_cast<int>((field[i] - 1) / size));
			heuristic += std::abs(static_cast<int>(i % size) - static_cast<int>((field[i] - 1) % size));
		}
	}
	// std::cout << std::endl;
	std:: cout << heuristic << std::endl;
	// exit(0);
    return (heuristic);
}
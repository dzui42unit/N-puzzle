#pragma once

#include <stddef.h>
#include <iostream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include "../Tools/Field.hpp"

class Heuristic
{	
public:
    Heuristic() = delete;
    ~Heuristic() = delete;
    static int  Manhattan(int *field, size_t size);
    static int 	LinearConflictManhattanDistance(int *field, size_t size);
    static int  GetSnailFieldIndex(int *grid, int number_to_find, size_t size);
    static int	EuclideanDistance(int *field, size_t size);
};

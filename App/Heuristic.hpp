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
    // not implemented yet
};

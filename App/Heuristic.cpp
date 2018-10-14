#include "Heuristic.hpp"

#include <random>
#include <cassert>

/// Dummy implementation
int Heuristic::Manhattan(...)
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 10000); // distribution in range [0, 10000]

    return (distribution(rng));
}
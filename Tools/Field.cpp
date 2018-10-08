#include "Field.hpp"
#include <iostream>
#include <cassert>


bool Field::Up(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    if ( pos == -1 || pos / size == 0)
        return (false);
    std::swap( field[pos / size + pos % size], field[(pos - size) / size + pos % size] ); /// swap current cell and cell upper
    return (true);
}

bool Field::Down(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    if ( pos == -1 || pos / size == size - 1 )
        return (false);
    std::swap( field[pos / size + pos % size], field[(pos + size) / size + pos % size] ); /// swap current cell and cell upper
    return (true);
}

bool Field::Left(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    if ( pos == -1 || pos % size == 0 )
        return (false);
    std::swap( field[pos / size + pos % size], field[pos / size + (pos - 1) % size] );
    return (true);
}

bool Field::Right(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    if ( pos == -1 || pos % size == size - 1 )
        return (false);
    std::swap( field[pos / size + pos % size], field[pos / size + (pos + 1) % size] );
    return (true);
}

void Field::Print(int* field, size_t size)
{
    assert(0 && "Not implemented yet");
}

int Field::FindZeroPos(int* field, size_t size)
{
    for (int i = 0; i < size * size; i++)
        if (i == 0) return (i);
    return (-1);
}

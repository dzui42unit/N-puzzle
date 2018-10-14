#include "Field.hpp"
#include "Common.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>


bool Field::Up(int* field, size_t size)
{
    // Find the position of current empty cell
    int pos = FindZeroPos(field, size);

    // if we are blocked - return false
    if ( pos == -1 || pos / size == 0 )
        return (false);
    std::swap( field[pos], field[pos - size] );
    return (true);
}

bool Field::Down(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    if ( pos == -1 || pos / size == size - 1 )
        return (false);
    std::swap( field[pos], field[pos + size] );
    return (true);
}

bool Field::Left(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    if ( pos == -1 || pos % size == 0 )
        return (false);
    std::swap( field[pos], field[pos - 1] );
    return (true);
}

bool Field::Right(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    if ( pos == -1 || pos % size == size - 1 )
        return (false);
    std::swap( field[pos], field[pos + 1] );
    return (true);
}

void Field::Print(int* field, size_t size)
{
    int maxWidthInDigits = 0;

    // Find max width in digits to align data
    for (int i = 0; i < size * size; i++)
    {
        int digitNum = Common::tools::countDigit(field[i]);
        if (maxWidthInDigits < digitNum)
            maxWidthInDigits = digitNum;
    }

    // Init 'sections' needed for gamefield output
    std::string section(maxWidthInDigits, '-');
    section += "-|";
    auto showSections = [&](){ // Function to draw section
        std::cout << '|';
        for (int j = 0; j < size; j++)
        {
            std::cout << '-' << section;
        }
        std::cout << std::endl;
    };

    for (int i = 0; i < size; i++)
    {
        showSections();
        std::cout << "| ";
        for (int j = 0; j < size; j++)
        {
            if (field[i * size + j] == 0)
                std::cout << std::setw(maxWidthInDigits) << ' ' << " | ";
            else
                std::cout << std::setw(maxWidthInDigits) << field[i * size + j] << " | ";
        }
        std::cout << std::endl;
    }
    showSections();
}

bool Field::CanMoveUp(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    return ( pos != -1 && pos / size != 0);
}

bool Field::CanMoveDown(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    return ( pos != -1 && pos / size != size - 1 );
}

bool Field::CanMoveLeft(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    return (  pos != -1 && pos % size != 0  );
}

bool Field::CanMoveRight(int* field, size_t size)
{
    int pos = FindZeroPos(field, size);

    return (  pos != -1 && pos % size != size - 1  );
}

int Field::FindZeroPos(int* field, size_t size)
{
    for (int i = 0; i < size * size; i++)
    {
        if (field[i] == 0)
            return (i);
    }
    
    return (-1);
}

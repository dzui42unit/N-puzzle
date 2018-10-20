#include "Field.hpp"
#include "Common.hpp"
#include <iostream>
#include <iomanip>
#include <cstdio>
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
    for (size_t i = 0; i < size * size; i++)
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
        for (size_t j = 0; j < size; j++)
        {
            std::cout << '-' << section;
        }
        std::cout << std::endl;
    };

    for (size_t i = 0; i < size; i++)
    {
        showSections();
        std::cout << "| ";
        for (size_t j = 0; j < size; j++)
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

void Field::PrintPrintf(int* field, size_t size)
{
    int maxWidthInDigits = 0;

    // Find max width in digits to align data
    for (size_t i = 0; i < size * size; i++)
    {
        int digitNum = Common::tools::countDigit(field[i]);
        if (maxWidthInDigits < digitNum)
            maxWidthInDigits = digitNum;
    }

    // Init 'sections' needed for gamefield output
    std::string section(maxWidthInDigits, '-');
    section += "-|";
    auto showSections = [&](){ // Function to draw section
        printf("|");
        for (size_t j = 0; j < size; j++)
            printf("-%s", section.c_str());
        printf("\n");
    };

    for (size_t i = 0; i < size; i++)
    {
        showSections();
        printf("| ");
        for (size_t j = 0; j < size; j++)
        {
            if (field[i * size + j] == 0)
                printf("%*c | ", maxWidthInDigits, ' ');
            else
                printf("%*d | ", maxWidthInDigits, field[i * size + j]);
        }
        std::cout << std::endl;
    }
    showSections();
}

int Field::FindZeroPos(int* field, size_t size)
{
    static int zeroPos = 0;

    if (field[zeroPos] == 0)
        return (zeroPos);

    for (size_t i = 0; i < size * size; i++)
    {
        if (field[i] == 0)
        {
            zeroPos = i;
            return (i);
        }
    }
    
    return (-1);
}

int    *Field::CreateSnailGrid(size_t size)
{
    int *snail_grid;
    int iterator;
    int start_row;
    int start_col;
    int end_row;
    int end_col;
    int number;

    number = 0;
    iterator = 0;
    start_row = 0;
    start_col = 0;
    end_row = size;
    end_col = size;
    snail_grid = nullptr;
    snail_grid = new int[size * size];
    std::cout << size << std::endl;
    while (start_row < end_row && start_col < end_col) 
    { 
        // generate the first row from the remaining rows
        for (iterator = start_col; iterator < end_col; ++iterator) 
        {
            if (static_cast<size_t>(number + 1) == size * size)
                number = -1;
            snail_grid[size * start_row + iterator] = number + 1;
            number++;
        }
        start_row++; 

        // generate the last column from the remaining columns
        for (iterator = start_row; iterator < end_row; ++iterator) 
        {
            if (static_cast<size_t>(number + 1) == size * size)
                number = -1;
            snail_grid[size * iterator + (end_col-1)] = number + 1;
            number++; 
        }
        end_col--;

        // generate the last row from the remaining rows
        if ( start_row < end_row) 
        { 
            for (iterator = end_col-1; iterator >= start_col; --iterator) 
            {
                if (static_cast<size_t>(number + 1) == size * size)
                    number = -1;
                snail_grid[size * (end_row-1) + iterator] = number + 1;
                number++;
            } 
            end_row--; 
        } 

        // generate the first column from the remaining columns
        if (start_col < end_col) 
        { 
            for (iterator = end_row-1; iterator >= start_row; --iterator) 
            { 
                if (static_cast<size_t>(number + 1) == size * size)
                    number = -1;
                snail_grid[size * iterator + start_col] = number + 1;
                number++;
            } 
            start_col++;     
        }
    }

    return (snail_grid); 
}
